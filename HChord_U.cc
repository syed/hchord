#include <cfloat>
#include <cfloat>
#include <assert.h>
#include <map>

#include <GlobalStatistics.h>
#include <Comparator.h>
#include <BootstrapList.h>

#include <HChordFingerTable.h>
#include <HChordSuccessorList.h>

#include "HChord_U.h"
#include "HChord_L.h"

using namespace std;

Define_Module(HChord_U);

HChord_U::HChord_U()
{
    stabilize_timer  = stabilize_timer =  NULL;
}


void HChord_U::initializeOverlay(int stage)
{
    // because of IPAddressResolver, we need to wait until interfaces
    // are registered, address auto-assignment takes place etc.
    if (stage != MIN_STAGE_OVERLAY)
        return;

    if (iterativeLookupConfig.merge == true) {
        throw new cRuntimeError("HChord_U::initializeOverlay(): "
              "HChord doesn't work with iterativeLookupConfig.merge = true!");
    }

    // HChord provides KBR services
    kbr = true;

    // fetch some parameters
    useCommonAPIforward = par("useCommonAPIforward");
    successorListSize = par("successorListSize");
    joinRetry = par("joinRetry");
    stabilizeRetry = par("stabilizeRetry");
    joinDelay = par("joinDelay");
    stabilizeDelay = par("stabilizeDelay");
    fixfingersDelay = par("fixfingersDelay");
    aggressiveJoinMode = par("aggressiveJoinMode");
    extendedFingerTable = par("extendedFingerTable");
    numFingerCandidates = par("numFingerCandidates");
    stabilizeSuperPeerDelay = par("stabilizeSuperPeerDelay");
    migrateDelay = par("migrateDelay");
    strong_peer = par("StrongPeer");

   std::stringstream str;
   str<<thisNode.ip;
   std::string node_ip = str.str(); 
   EV<<"Node ip is "<<node_ip<<endl;
    
  //  if(node_ip=="1.0.0.1"||node_ip=="1.0.0.8" ||node_ip=="1.0.0.14" ||node_ip=="1.0.0.15" ||node_ip=="1.0.0.22")
	//    strong_peer=1;

  if(node_ip=="1.0.0.1"||node_ip=="1.0.0.3"||node_ip=="1.0.0.27")
	    strong_peer=1;

	    

    keyLength = OverlayKey::getLength();
    missingPredecessorStabRequests = 0;
    missingSuccessorStabResponses = 0;


    // statistics
    joinCount = 0;
    stabilizeCount = 0;
    fixfingersCount = 0;
    notifyCount = 0;
    newsuccessorhintCount = 0;
    joinBytesSent = 0;
    stabilizeBytesSent = 0;
    notifyBytesSent = 0;
    fixfingersBytesSent = 0;
    newsuccessorhintBytesSent = 0;
    
    in_upper=0;

    // find friend modules
    findFriendModules();

    
    // add some watches
    WATCH(predecessorNode);
    WATCH(thisNode);
    WATCH(bootstrapNode);
    WATCH(joinRetry);
    WATCH(strong_peer);
    WATCH(super_peer);
    WATCH(in_upper);
    WATCH_MAP(StrongPeerSet);
    //WATCH(missingPredecessorStabRequests);
    //WATCH(missingSuccessorStabResponses);

    // self-messages
    join_timer = new cMessage("join_timer");
    stabilize_timer= new cMessage("stabilize_timer");
    fixfingers_timer = new cMessage("fixfingers_timer");
    stabilize_super_peer_timer = new cMessage("stabilize_super_peer_timer");
    if(strong_peer)
    {
    	migrate_timer = new cMessage("migrate_timer");
	}
	
    
   
}


HChord_U::~HChord_U()
{
    // destroy self timer messages
    cancelAndDelete(join_timer);
    cancelAndDelete(stabilize_timer);
    cancelAndDelete(fixfingers_timer);
    cancelAndDelete(stabilize_super_peer_timer);
    if(strong_peer)
    	cancelAndDelete(migrate_timer);
  
}


void HChord_U::joinOverlay()
{
    changeState(INIT);
    changeState(BOOTSTRAP);
}

void HChord_U::changeState(int toState)
{
    //
    // Defines tasks to be executed when a state change occurs.
    //

    switch (toState) {
    case INIT:
        state = INIT;

        setOverlayReady(false);

        if (thisNode.key.isUnspecified()) {
            thisNode.key = OverlayKey::random();
            callUpdate(thisNode, true);
        }

	    predecessorNode = NodeHandle::UNSPECIFIED_NODE;
        

        // initialize finger table and successor list
        initializeFriendModules();

        updateTooltip();

        // debug message
        if (debugOutput) {
            EV << "[HChord_U::changeState() @ " << thisNode.ip
            << " (" << thisNode.key.toString(16) << ")]\n"
            << "    Entered INIT stage"
            << endl;
        }

        parentModule()->parentModule()->bubble("Enter INIT state.");
        break;

    case BOOTSTRAP:
        state = BOOTSTRAP;

        // initiate bootstrap process
        cancelEvent(join_timer);
        // workaround: prevent notificationBoard from taking
        // ownership of join_timer message
        take(join_timer);
        scheduleAt(simulation.simTime(), join_timer);

        // debug message
        if (debugOutput) {
            EV << "[HChord_U::changeState() @ " << thisNode.ip
            << " (" << thisNode.key.toString(16) << ")]\n"
            << "    Entered BOOTSTRAP stage"
            << endl;
        }
        parentModule()->parentModule()->bubble("Enter BOOTSTRAP state.");

        // find a new bootstrap node and enroll to the bootstrap list
        bootstrapNode = bootstrapList->getBootstrapNode();

        // is this the first node?
        if (bootstrapNode.isUnspecified()) {
            // create new cord ring
            bootstrapNode = thisNode;
            super_peer=1;
	    	lower->SuperPeerNode=thisNode;
	    	LargestNode=thisNode;
	    	LargestNodeSuc=thisNode;
            StrongPeerSet.insert(make_pair(thisNode.key,thisNode));
            in_upper=1;
            changeState(READY);
            updateTooltip();
        }
        break;

    case READY:
        state = READY;

        setOverlayReady(true);

        //initiate stabilization protocol
        cancelEvent(stabilize_timer);
        scheduleAt(simulation.simTime() + stabilizeDelay, stabilize_timer);

        // initiate finger repair protocol
        cancelEvent(fixfingers_timer);
        scheduleAt(simulation.simTime() + fixfingersDelay,fixfingers_timer);
        
        cancelEvent(stabilize_super_peer_timer);
        scheduleAt(simulation.simTime() + stabilizeSuperPeerDelay, stabilize_super_peer_timer);

        
        //if strong peer initiate migrate protocol 
        if(strong_peer&&!super_peer)
        {
        	cancelEvent(migrate_timer);
        	scheduleAt(simulation.simTime()+migrateDelay,migrate_timer);
		}

       	// debug message
        if (debugOutput) {
            EV << "[HChord_U::changeState() @ " << thisNode.ip
            << " (" << thisNode.key.toString(16) << ")]\n"
            << "    Entered READY stage"
            << endl;
        }
        parentModule()->parentModule()->bubble("Enter READY state.");
        break;
    }
}

void HChord_U::handleMessage(cMessage* msg)
{
	if(msg->arrivedOn("from_lower"))
	{
		HChordMessage *m  = check_and_cast<HChordMessage*>(msg);
		sendMessageToUDP(m->getDest(),m);
	}
	else
	{
		BaseOverlay::handleMessage(msg);
	}
}


void HChord_U::handleTimerEvent(cMessage* msg)
{
    // catch JOIN timer
    if (msg->isName("join_timer")) {
        handleJoinTimerExpired(msg);
    }
    // catch STABILIZE timer
    else if (msg->isName("stabilize_timer")) {
        handleStabilizeTimerExpired(msg);
    }

    // catch FIX_FINGERS timer
    else if (msg->isName("fixfingers_timer")) {
        handleFixFingersTimerExpired(msg);
    }
    else if (msg->isName("migrate_timer")){
    	handleMigrateTimerExpired(msg);
	}
	else if( msg->isName("stabilize_super_peer_timer")){
		handleStabilizeSuperPeerTimerExpired(msg);
	}
	else if (msg->isName("upper_join_timer")){
		handleUpperJoinTimerExpired(msg);
	}
	
    // unknown self message
    else {
        error("HChord_U::handleTimerEvent(): received self message of "
              "unknown type!");
    }
}


void HChord_U::handleUDPMessage(BaseOverlayMessage* msg)
{
    HChordMessage* hchordMsg = check_and_cast<HChordMessage*>(msg);
    switch(hchordMsg->getMesg_type()) {
    case JOIN_REQUEST :
	{
       HJoinCall * hcjoin = check_and_cast<HJoinCall *>(msg);
       //UHJoinCall *uj = dynamic_cast<UHJoinCall *>(msg);
       //if(uj != NULL )
	  		handleJoinRequest(hcjoin);
		//else
			//send(hcjoin,"to_lower");
	}
	break;
    case JOIN_RESPONSE :
	{
	   HJoinResponse *hcresp = check_and_cast<HJoinResponse *>(msg);
	   UHJoinResponse *ur = dynamic_cast<UHJoinResponse *>(msg);
	   if(ur != NULL)
	   {
	   		handleJoinResponse(ur);
	    }
		else
		{
			//checks here
			changeState(READY);
			bootstrapList->removeBootstrapNode(thisNode);
			send(hcresp,"to_lower");
		}
				
	}
	break;
    case NEW_SUCCESSOR_HINT :
	{
	   HNewSuccessorHintMsg  *newSucc = check_and_cast<HNewSuccessorHintMsg *>(msg);
	   UHNewSuccessorHintMsg *ns = dynamic_cast<UHNewSuccessorHintMsg*>(msg);
	   if(ns!=NULL)
	   {
	   	
	   	handleNewSuccessorHint(newSucc);
		}
	else
		send(newSucc,"to_lower");
	}
	break;
    case STABILIZE_CALL :
	{
	   HStabilizeCall *stab = check_and_cast<HStabilizeCall *>(msg);
	   UHStabilizeCall *us = dynamic_cast<UHStabilizeCall*>(msg);
	   if(us != NULL)
	   
	   handleStabilizeCall(stab);
	   else
	   send(stab,"to_lower");
	}
	break;
    case STABILIZE_RESPONSE :
	{
	   HStabilizeResponse *stabr = check_and_cast<HStabilizeResponse *>(msg);
	   UHStabilizeResponse *sr = dynamic_cast<UHStabilizeResponse *>(msg);
	   if(sr!=NULL)
	   
	   handleStabilizeResponse(stabr);
	   else 
	   	send(stabr,"to_lower");
	}
	break;
    case NOTIFY_CALL :
	{
	   HNotifyCall  *call = check_and_cast<HNotifyCall *>(msg);
	   UHNotifyCall *nc = dynamic_cast<UHNotifyCall*>(msg);
	   if(nc!=NULL)
	   {
	   		handleNotifyCall(call);
	   	}
	   	else
	   		send(call,"to_lower");
	}
	break;
    case NOTIFY_RESPONSE :
	{
	   HNotifyResponse *notr = check_and_cast<HNotifyResponse *>(msg);
	   UHNotifyResponse *nr = dynamic_cast<UHNotifyResponse *>(msg);
	   if(nr !=NULL)
	   
	   		handleNotifyResponse(notr);
	   	else
	   		send(notr,"to_lower");
	   		
	}
	break;
    case FIXFINGERS_CALL :
	{
	   HFixfingersCall  *fix = check_and_cast<HFixfingersCall *>(msg);
	   UHFixfingersCall *fc = dynamic_cast<UHFixfingersCall *>(msg);
	   if(fc!=NULL)
	   handleFixfingersCall(fix);
	   else
	   send(fix,"to_lower");
	   
	}
	break;
    case FIXFINGERS_RESPONSE:
	{
	   HFixfingersResponse *fixr = check_and_cast<HFixfingersResponse *>(msg);
	   UHFixfingersResponse *fr = dynamic_cast<UHFixfingersResponse *>(msg);
	   if(fr!=NULL)
	   handleFixfingersResponse(fixr);
	   else
	   send(fixr,"to_lower");
	   
	}
	break;
	case MIGRATE_REQUEST :
	{
		HMigrateRequest *migr = check_and_cast<HMigrateRequest *>(msg);
		handleMigrateRequest(migr);
	}
	break;
	case MIGRATE_RESPONSE :
	{
		HMigrateResponse *migr = check_and_cast<HMigrateResponse *>(msg);
		handleMigrateResponse(migr);
	}
	break;
	case STABILIZE_SUPER_PEER_CALL:
	{
		HStabilizeSuperPeerCall *spstab = check_and_cast<HStabilizeSuperPeerCall *>(msg);
		handleStabilizeSuperPeerCall(spstab);
	}
	break;
	case STABILIZE_SUPER_PEER_RESPONSE:
	{
		HStabilizeSuperPeerResponse *spstabr = check_and_cast<HStabilizeSuperPeerResponse *>(msg);
		handleStabilizeSuperPeerResponse(spstabr);
	}
	break;
	case LARGEST_NODE_REQUEST:
	{
		HLargestNodeRequest *lnreq = check_and_cast<HLargestNodeRequest *>(msg);
		handleLargestNodeRequest(lnreq);
	}
	break;
	case LARGEST_NODE_RESPONSE:
	{
		HLargestNodeResponse *lnrep = check_and_cast<HLargestNodeResponse *>(msg);
		handleLargestNodeResponse(lnrep);
	}
	break;
	case CHANGE_SUC_REQ :
	{
		HChangeSuccessorRequest *suc = check_and_cast<HChangeSuccessorRequest *>(msg);
		handleChangeSuccessorRequest(suc);
	}
	break;
	case CHANGE_SUC_RES :
	{
		HChangeSuccessorResponse *suc = check_and_cast<HChangeSuccessorResponse *>(msg);
		handleChangeSuccessorResponse(suc);
	}
	break;
	case CHANGE_PRE :
	{
		HChangePredecessor *pre = check_and_cast<HChangePredecessor *>(msg);
		handleChangePredecessor(pre);
	}
	break;
	default:
        error("handleUDPMessage(): Unknown message type!");
        break;
    }

    //delete chordMsg;
}

int HChord_U::getMaxNumSiblings()
{
    return successorListSize;
}

int HChord_U::getMaxNumRedundantNodes()
{
    return extendedFingerTable ? numFingerCandidates : 1;
}


bool HChord_U::isSiblingFor(const NodeHandle& node,
                         const OverlayKey& key,
                         int numSiblings,
                         bool* err)
{

    EV<<"is sibling for key looking for "<<key<<"num = "<<numSiblings<<"node is "<<node<<endl;

    if (key.isUnspecified())
        error("HChord_U::isSiblingFor(): key is unspecified!");

    if (state != READY) 
    {
        *err = true;
        return false;
    }

    if (numSiblings > getMaxNumSiblings()) 
    {
        opp_error("HChord_U::isSiblingFor(): numSiblings too big!");
    }
    // set default number of siblings to consider
    if (numSiblings == -1) numSiblings = getMaxNumSiblings();

    // if this is the first and only node on the ring, it is responsible 
    if ((predecessorNode.isUnspecified()) && (node == thisNode)) 
    {
        if(successorList->isEmpty() || (node.key == key)) 
        {
        	*err = false;
		    EV<<"issibling pre uns and thisNode and suc empty or key=thiskey ret true "<<endl;
        	return true;
        }
        else 
        {
        	*err = true;
		    EV<<"issibling pre uns and thisNode and suc empty or key=thiskey ret false"<<endl;
        	return false;
        }
	}
    	
    	
	if ((node == thisNode) && (key.isBetweenR(predecessorNode.key, thisNode.key))) 
	{
       	*err = false;
		EV<<"node is this key btwn pre and this"<<endl;
       	return true;
   	}	
	NodeHandle prevNode = predecessorNode;
    NodeHandle curNode;
   	for (int i = -1; i < (int)successorList->getSize(); i++, prevNode = curNode) 
   	{
		if (i < 0) 
		{
            curNode = thisNode;
        }
        else 
        {
        	curNode = successorList->getSuccessor(i);
        }	
		if (node == curNode) 
		{
            // is the message destined for curNode?
            if (key.isBetweenR(prevNode.key, curNode.key)) 
            {
            	if (numSiblings <= ((int)successorList->getSize() - i)) 
            	{
                    *err = false;
			EV<<"key btwn suc "<<i<<endl;
                   	return true;
                } 
                else 
                {
                	*err = true;
                	return false;
                }
            }
            else 
            {
      		     // the key doesn't directly belong to this node, but
            	// the node could be a sibling for this key
            	if (numSiblings <= 1) 
            	{
                    *err = false;
                    return false;
                }
                else 
                {
                 // In Chord we don't know if we belong to the
                 // replicaSet of one of our predecessors
                 	*err = true;
                 	return false;
                }
            }
        }
    }
   // node is not in our neighborSet
    *err = true;
    return false;
}



NodeHandle HChord_U::findNode_h(const OverlayKey& key,int numSiblings,int numRedundantNodes , BaseOverlayMessage* msg)
{
    bool err;
    EV<<endl<<"FindNode() called sibligs "<<numSiblings<<" with key "<<key<<endl;
    NodeHandle nextHop=NodeHandle::UNSPECIFIED_NODE;
    
    if (state != READY)
        return nextHop;

    // if key is unspecified, the message is for this node
    if (key.isUnspecified()) 
    {
        nextHop = thisNode;    
    }
  	// the message is destined for this node 
    else if (isSiblingFor(thisNode, key, 1, &err)) 
    {
        nextHop = thisNode;
    }
    // the message destined for our successor
	else if (key.isBetweenR(thisNode.key,successorList->getSuccessor().key)) 
	{
        nextHop = successorList->getSuccessor();      
    }
	// find next hop with finger table and/or successor list
    else 
    {
    	nextHop = closestPreceedingNode(key);
    }
	return nextHop;
}


NodeHandle HChord_U::closestPreceedingNode(const OverlayKey& key)
{
    NodeHandle tempHandle = NodeHandle::UNSPECIFIED_NODE;

    EV<<"Closestpreceeding node "<<key<<endl;
    // find the closest preceding node in the successor list of upper overlay 
    for (int j = successorList->getSize() - 1; j >= 0; j--) 
    {
    	if(successorList->getSuccessor(j).key.isBetweenR(thisNode.key, key)) 
    	{
                tempHandle = successorList->getSuccessor(j);
                break;
        }
    }
	if(tempHandle.isUnspecified()) 
	{
        std::stringstream temp;
        temp << "HChord_U::closestPreceedingNode(): Successor list broken "
        	<< thisNode.key << " " << key;
	    EV<<"HChord_U::closestPreceedingNode(): Successor list broken "<<thisNode.key<<"  "<<key;
        throw new cRuntimeError(temp.str().c_str());
    }

    NodeHandle nextHop;
    //look in finger table
    for (int i = fingerTable->getSize() - 1; i >= 0; i--) 
    {
    	if (fingerTable->getFinger(i).key.isBetweenLR(tempHandle.key, key)) 
    	{
        	if(!extendedFingerTable) 
        	{
                        //nextHop = new NodeVector();
            	nextHop=fingerTable->getFinger(i);
			
                EV << "[HChord_U::closestPreceedingNode() @ " << thisNode.ip
                << " (" << thisNode.key.toString(16) << ")]\n"
                << "    ClosestPreceedingNode: node " << thisNode
                << " for key " << key << "\n"
                << "    finger " << fingerTable->getFinger(i).key
                << " better than \n"
                << "    " << tempHandle.key
                << endl;
                return nextHop;
            } 
            else 
            {
            	//return fingerTable_upper->getFinger(i, key);
            }
       }
    }

    EV << "[HChord_U::closestPreceedingNode() @ " << thisNode.ip
    <<" (" << thisNode.key.toString(16) << ")]\n"
    << "    No finger found"
    << endl;
	
   	// if no finger is found lookup the rest of the successor list
   	for(int i = successorList->getSize() - 1; i >= 0; i--) 
   	{
   	   	if(successorList->getSuccessor(i).key.isBetween(thisNode.key, key)) 
   	   	{
   	       	nextHop=successorList->getSuccessor(i);
   	   	}
   	}

   	if(!nextHop.isUnspecified())
   	     return nextHop;

   	// if this is the first and only node on the ring, it is responsible
   	if ((predecessorNode.isUnspecified()) &&(successorList->getSuccessor() == thisNode)) 
   	{
   		nextHop=(thisNode);
   	    return nextHop;
   	}

	// if there is still no node found return NodeHandle::UNSPECIFIED_NODE
	std::stringstream temp("Error in HChord_U::closestPreceedingNode()!\n");
	temp << thisNode.key << " " << key;
	error(temp.str().c_str());
	nextHop=(NodeHandle::UNSPECIFIED_NODE);
	return nextHop;
	
}


/*void HChord_U::recordOverlaySentStats(BaseOverlayMessage* msg)
{
    BaseOverlayMessage* innerMsg;

    if (msg->getType() == OVERLAYROUTE)
        innerMsg = dynamic_cast<BaseOverlayMessage*>(msg->encapsulatedMsg());
    else
        innerMsg = msg;

    switch (innerMsg->getType()) {

    case OVERLAYSIGNALING: {
        HChordMessage* chordMsg = dynamic_cast<HChordMessage*>(innerMsg);
        switch(chordMsg->getCommand()) {
        case NEWSUCCESSORHINT:
            RECORD_STATS(newsuccessorhintCount++; newsuccessorhintBytesSent +=
                             msg->byteLength());
            break;
        }
        break;
    }

    case RPC: {
        if ((dynamic_cast<StabilizeCall*>(innerMsg) != NULL) ||
            (dynamic_cast<StabilizeResponse*>(innerMsg) != NULL)) {
            RECORD_STATS(stabilizeCount++; stabilizeBytesSent +=
                             msg->byteLength());
        } else if ((dynamic_cast<NotifyCall*>(innerMsg) != NULL) ||
                   (dynamic_cast<NotifyResponse*>(innerMsg) != NULL)) {
            RECORD_STATS(notifyCount++; notifyBytesSent +=
                             msg->byteLength());
        } else if ((dynamic_cast<FixfingersCall*>(innerMsg) != NULL) ||
                   (dynamic_cast<FixfingersResponse*>(innerMsg) != NULL)) {
            RECORD_STATS(fixfingersCount++; fixfingersBytesSent +=
                             msg->byteLength());
        } else if ((dynamic_cast<JoinCall*>(innerMsg) != NULL) ||
                   (dynamic_cast<JoinResponse*>(innerMsg) != NULL)) {
            RECORD_STATS(joinCount++; joinBytesSent += msg->byteLength());
        }
        break;
    }
    }
}
*/

void HChord_U::finishOverlay()
{
    // remove this node from the bootstrap list
    bootstrapList->removeBootstrapNode(thisNode);

}
 
/*    simtime_t time = globalStatistics->calcMeasuredLifetime(creationTime);
    if(time == 0) return;

    globalStatistics->addStdDev("HChord: Sent JOIN Messages/s",
                                joinCount / time);
    globalStatistics->addStdDev("HChord: Sent NEWSUCCESSORHINT Messages/s",
                                newsuccessorhintCount / time);
    globalStatistics->addStdDev("HChord: Sent STABILIZE Messages/s",
                                stabilizeCount / time);
    globalStatistics->addStdDev("HChord: Sent NOTIFY Messages/s",
                                notifyCount / time);
    globalStatistics->addStdDev("HChord: Sent FIX_FINGERS Messages/s",
                                fixfingersCount / time);
    globalStatistics->addStdDev("HChord: Sent JOIN Bytes/s",
                                joinBytesSent / time);
    globalStatistics->addStdDev("HChord: Sent NEWSUCCESSORHINT Bytes/s",
                                newsuccessorhintBytesSent / time);
    globalStatistics->addStdDev("HChord: Sent STABILIZE Bytes/s",
                                stabilizeBytesSent / time);
    globalStatistics->addStdDev("HChord: Sent NOTIFY Bytes/s",
                                notifyBytesSent / time);
    globalStatistics->addStdDev("HChord: Sent FIX_FINGERS Bytes/s",
                                fixfingersBytesSent / time);
}

*/

void HChord_U::handleJoinTimerExpired(cMessage* msg)
{
    // only process timer, if node is not bootstrapped yet
    if (state == READY)
        return;

    // enter state BOOTSTRAP
    if (state != BOOTSTRAP)
        changeState(BOOTSTRAP);

    // change bootstrap node from time to time
    joinRetry--;
    if (joinRetry == 0) {
        joinRetry = par("joinRetry");
        changeState(BOOTSTRAP);
        return;
    }

    // call JOIN 
    HJoinCall * call = new HJoinCall("HJoinCall");
   // call->setOverlay(UPPER_OVERLAY);
    call->setLength(HJOINCALL_L(call));
    call->setSrc(thisNode);
    call->setDest(bootstrapNode);
    call->setMesg_type(JOIN_REQUEST);

    sendMessageToUDP( bootstrapNode,call);

    // schedule next bootstrap process in the case this one fails
    cancelEvent(join_timer);
    scheduleAt(simulation.simTime() + joinDelay, msg);
}


void HChord_U::handleStabilizeTimerExpired(cMessage* msg)
{
    if (state != READY)
        return;

    if (missingPredecessorStabRequests >= stabilizeRetry) {
        // predecessor node seems to be dead
        // remove it from the predecessor / successor lists
        successorList ->removeSuccessor(predecessorNode);
        //predecessorIsDead();

        callUpdate(predecessorNode, false);
        predecessorNode  = NodeHandle::UNSPECIFIED_NODE;

        missingPredecessorStabRequests = 0;
        updateTooltip();
    }

    if (missingSuccessorStabResponses >= stabilizeRetry) {
        // successor node seems to be dead
        // remove it from the predecessor / successor list
        //successorIsDead();
        NodeHandle successor = successorList->popSuccessor();

        // if we had a ring consisting of 2 nodes and our successor seems
        // to be dead. Remove also predecessor because the successor
        // and predecessor are the same node
        if ((!predecessorNode.isUnspecified()) &&
            predecessorNode  == successor) {
            //predecessorIsDead();
            callUpdate(predecessorNode, false);
            predecessorNode = NodeHandle::UNSPECIFIED_NODE;
        }

        missingSuccessorStabResponses = 0;
        updateTooltip();

        if (successorList->isEmpty()) {
            changeState(INIT);
            changeState(BOOTSTRAP);
            return;
        }
    }

    if (!successorList->isEmpty()) {
        // call STABILIZE RPC
        UHStabilizeCall* call = new UHStabilizeCall("UHStabilizeCall");
        call->setLength(HSTABILIZECALL_L(call));
	//call->setOverlay(UPPER_OVERLAY);
	call->setMesg_type(STABILIZE_CALL);
	call->setSrc(thisNode);
        call->setLength(HSTABILIZECALL_L(call));
	call->setDest(successorList->getSuccessor());

        sendMessageToUDP(successorList->getSuccessor(), call);

        missingPredecessorStabRequests++;
        missingSuccessorStabResponses++;
    }

    // check if fingers are still alive and remove unreachable finger nodes

    // schedule next stabilization process
    cancelEvent(stabilize_timer);
    scheduleAt(simulation.simTime() + stabilizeDelay, msg);
}


void HChord_U::handleFixFingersTimerExpired(cMessage* msg)
{
    EV<<endl<<endl<<thisNode<<":Fix fingers timer reached "<<endl;
    if ((state != READY) || successorList->isEmpty())
        return;

    OverlayKey offset, lookupKey;
    for (uint nextFinger = 0; nextFinger < thisNode.key.getLength()-1;nextFinger++) 
    {
        // calculate "n + 2^(i - 1)"
		OverlayKey k=thisNode.key;
        offset = OverlayKey::pow2(nextFinger);
        lookupKey = k + offset;

        // send message only for non-trivial fingers
        if (offset > successorList->getSuccessor().key - k) 
        {
	     EV<<thisNode<<": lookup key "<<lookupKey<<" sending fix fingers call fingerno "<<nextFinger<<endl;
            // call FIXFINGER RPC
            UHFixfingersCall* call = new UHFixfingersCall("UHFixfingersCall");
            call->setFinger(nextFinger);
	    	call->setSrc(thisNode);
	    	call->setLookupKey(lookupKey);
	    //call->setOverlay(UPPER_OVERLAY);
	    	call->setMesg_type(FIXFINGERS_CALL);
            call->setLength(HFIXFINGERSCALL_L(call));

	    	NodeHandle nextHop = findNode_h(lookupKey,1,1,call);
	    	call->setDest(nextHop);
            sendMessageToUDP(nextHop,call);

        } 
        else 
        {
            // let trivial fingers point to the successor node
	    EV<<thisNode<<" lookup key "<<lookupKey<<" setting to successor fingr no "<<nextFinger<<endl;
            fingerTable->setFinger(nextFinger, successorList->getSuccessor());
        }
    }

    // schedule next finger repair process
    cancelEvent(fixfingers_timer);
    scheduleAt(simulation.simTime() + fixfingersDelay, msg);
}

void HChord_U::handleMigrateTimerExpired(cMessage *msg)
{
	if(super_peer)
	{
		//delete msg;
		return ;
		
	}
	//send migrate req to super peer
	HMigrateRequest *migr = new  HMigrateRequest("Migrate Request");
	migr->setSrc(thisNode);
	migr->setDest(lower->SuperPeerNode);
	migr->setMesg_type(MIGRATE_REQUEST);
	sendMessageToUDP(migr->getDest(),migr);
	
	cancelEvent(migrate_timer);
    scheduleAt(simulation.simTime() + migrateDelay, msg);
}

void HChord_U::handleStabilizeSuperPeerTimerExpired(cMessage *msg)
{
	if(lower->SuperPeerNode == thisNode)
		return;
	//send stabilize super peer req to super peer

		HStabilizeSuperPeerCall *spstab = new HStabilizeSuperPeerCall("StabilizeSuperPeerCall");
		spstab->setSrc(thisNode);
		spstab->setDest(lower->SuperPeerNode);
		spstab->setMesg_type(STABILIZE_SUPER_PEER_CALL);
		sendMessageToUDP(lower->SuperPeerNode,spstab);
	
	cancelEvent(stabilize_super_peer_timer);
	scheduleAt(simulation.simTime() + stabilizeSuperPeerDelay, stabilize_super_peer_timer);
}


void HChord_U::handleUpperJoinTimerExpired(cMessage *msg)
{
	
	
	UHJoinCall *ujoincall = new UHJoinCall("UHJoinCall");
	ujoincall->setSrc(thisNode);
	//send new successor hint should have sent succ list in case of churn
	ujoincall->setLowerNewSuc(successorList_lower->getSuccessor());
	ujoincall->setDest(lower->SuperPeerNode);
	ujoincall->setMesg_type(JOIN_REQUEST);
	sendMessageToUDP(lower->SuperPeerNode,ujoincall);
	/*HLargestNodeRequest *req = new HLargestNodeRequest("LargestNodeReq");
	req->setSrc(thisNode);
	req->setDest(lower->SuperPeerNode);
	req->setMesg_type(LARGEST_NODE_REQUEST);
	sendMessageToUDP(lower->SuperPeerNode,req);*/
    cancelEvent(join_timer);
    scheduleAt(simulation.simTime() + joinDelay, msg);

	
	//delete msg;
	
}	

void HChord_U::handleNewSuccessorHint(HNewSuccessorHintMsg* hchordMsg)
{
    UHNewSuccessorHintMsg* newSuccessorHintMsg =
        check_and_cast<UHNewSuccessorHintMsg*>(hchordMsg);

    // fetch the successor's predecessor
    NodeHandle predecessor = newSuccessorHintMsg->getPre();

    // is the successor's predecessor a new successor for this node?
    // look here 
    OverlayKey tempkey=successorList->getSuccessor().key;

    
    NodeHandle curr_node=thisNode;

    if (predecessor.key.isBetween(curr_node.key,tempkey)||(curr_node.key == tempkey)) 
    {
        // add the successor's predecessor to the successor list
        successorList->addSuccessor(predecessor);
        updateTooltip();
    }
	delete hchordMsg;
}


void HChord_U::handleJoinRequest(HJoinCall *joinCall )
{
    NodeHandle requestor = joinCall->getSrc();
    bool err;
	UHJoinCall *ujoin = dynamic_cast<UHJoinCall *>(joinCall);
	if(ujoin!=NULL)//its a upper join req
	{
		if(in_upper)
		{
			processJoinRequest(ujoin);
		}
		else
		{
			sendMessageToUDP(lower->SuperPeerNode,joinCall);
			return;
		}
				
	}
   	else
   	{
		if(isSiblingFor(thisNode,requestor.key,1,&err))//message is destined for this node
		{
			
			//send to sub overlay
			//if it is not upper join req
			
			//else
			{
				//last ring needs to store min,max
				send(joinCall,"to_lower");
			}
			
		}
		else
		{
			//node is destined for anoter node 
			//find it and send it
			NodeHandle nextHop = findNode_h(requestor.key,1,1,joinCall);

			if(!nextHop.isUnspecified())
				sendMessageToUDP(nextHop,joinCall);
		}
	}

}


void HChord_U::processJoinRequest(UHJoinCall *joinCall)
{

//	UHJoinCall *ujoin = dynamic_cast<UHJoinCall *>(joinCall);		
    UHJoinResponse* joinResponse = new UHJoinResponse("UHJoinResponse");
	NodeHandle src = joinCall->getSrc();
	joinResponse->setMesg_type(JOIN_RESPONSE);
	joinResponse->setSrc(thisNode);
    int sucNum = successorList->getSize();
    joinResponse->setSucNum(sucNum);
    joinResponse->setSucNodeArraySize(sucNum);
	joinResponse->setDest(src);

	NodeHandle n; 
    for (int k = 0; k < sucNum; k++) 
    {
	    n = successorList->getSuccessor(k);
	    joinResponse->setSucNode(k,n);
    }

        // sent our predecessor as hint to the joining node
    if (predecessorNode.isUnspecified() && successorList->isEmpty()) 
    {
        // we are the only node in the ring
	    n = thisNode;
        joinResponse->setPreNode(n);
	} 
    else 
    {
       joinResponse->setPreNode(predecessorNode);
    }
    joinResponse->setLength(HJOINRESPONSE_L(joinResponse));
	//add to peer list
	
	//code for lower overlay
	NodeHandle suc = joinCall->getLowerNewSuc();
	NodeHandle old = successorList_lower->getSuccessor();
	while(!successorList_lower->isEmpty())				
	{
		successorList_lower->popSuccessor();
	}
	successorList_lower->addSuccessor(suc);
	//send suc to change pre to sp
	HChangePredecessor *cp = new HChangePredecessor("ChangePre");
	cp->setSrc(thisNode);
	cp->setDest(old);
	cp->setMesg_type(CHANGE_PRE);
	cp->setNewPre(joinCall->getSrc());	
	joinResponse->setLowerNewSuc(old);

	sendMessageToUDP(src,joinResponse);
	sendMessageToUDP(old,cp);

    if(aggressiveJoinMode) 
    {
            // aggressiveJoinMode differs from standard join operations:
            // 1. set our predecessor pointer to the joining node
            // 2. send our old predecessor as hint in JoinResponse msgs
            // 3. send a NEWSUCCESSORHINT to our old predecessor to update
            //    its successor pointer

            // send NEWSUCCESSORHINT to our old predecessor

        if (!predecessorNode.isUnspecified()) 
        {
            UHNewSuccessorHintMsg * newSuccessorHintMsg = new UHNewSuccessorHintMsg ("UPPERNEWSUCCESSORHINT");
            newSuccessorHintMsg->setMesg_type(NEW_SUCCESSOR_HINT);
			//newSuccessorHintMsg->setOverlay(LOWER_OVERLAY);
			n = thisNode;
	    	newSuccessorHintMsg->setSrc(n);
			n = src;
	   		newSuccessorHintMsg->setDest(predecessorNode);
            newSuccessorHintMsg->setPre(n);
            newSuccessorHintMsg->setLength(HNEWSUCCESSORHINT_L(newSuccessorHintMsg));
			sendMessageToUDP(predecessorNode, newSuccessorHintMsg);
        }

        if (predecessorNode.isUnspecified() || (predecessorNode != src )) 
        {
                // send update to application if we've got a new predecessor
            if (!predecessorNode.isUnspecified()) 
            {
                callUpdate(predecessorNode, false);
            }
            callUpdate(src, true);
            // the requestor is our new predecessor
            predecessorNode  = src;
        }

        // if we don't have a successor, the requestor is also our new successor
        if (successorList->isEmpty())
        {
            successorList->addSuccessor(src);
		}
		
		
        updateTooltip();
    }
    
    delete joinCall;
}

void HChord_U::handleJoinResponse(UHJoinResponse* joinResponse)
{
	
   // determine the numer of successor nodes to add
    int sucNum = successorListSize - 1;

    if (joinResponse->getSucNum() < successorListSize - 1) 
    {
        sucNum = joinResponse->getSucNum();
    }

    // add successor node(s)
    for (int k = 0; k < sucNum; k++) 
    {
        NodeHandle successor = joinResponse->getSucNode(k);
        successorList->addSuccessor(successor);
    }

    // \todo {check commented out addSuccessor (Schenk)}
    //successorList->addSuccessor(joinResponse->getSrcNode());

    // the sender of this message is our new successor
    NodeHandle n = joinResponse->getSrc();
    successorList->addSuccessor(n);

	lower->SuperPeerNode=thisNode;
	
	
	in_upper=1;
    //new suc in lower overlay frm join resp
    NodeHandle suc = joinResponse->getLowerNewSuc();
	NodeHandle old = successorList_lower->getSuccessor();
	while(!successorList_lower->isEmpty())				
	{
		successorList_lower->popSuccessor();
	}
	successorList_lower->addSuccessor(suc);
	//send change pre to its suc
	HChangePredecessor *cp = new HChangePredecessor("ChangePre");
	cp->setSrc(thisNode);
	cp->setDest(old);
	cp->setMesg_type(CHANGE_PRE);
	cp->setNewPre(joinResponse->getSrc());
	
    
    // in aggressiveJoinMode: use hint in JoinResponse
    // to set our new predecessor
    if (aggressiveJoinMode) 
    {
        // it is possible that the joinResponse doesn't contain a valid
        // predecessor especially when merging two partitions
        if (!joinResponse->getPreNode().isUnspecified()) 
        {
            if (!predecessorNode.isUnspecified()) 
            {


                // inform the original predecessor about the new predecessor
               /* if (mergeOptimizationL2) {
                    NewSuccessorHintMessage* newSuccessorHintMsg =
                        new NewSuccessorHintMessage("NEWSUCCESSORHINT");
                    newSuccessorHintMsg->setCommand(NEWSUCCESSORHINT);
                    newSuccessorHintMsg->setSrcNode(thisNode);
                    newSuccessorHintMsg->setPreNode(joinResponse->getPreNode());
                    newSuccessorHintMsg->
                        setLength(NEWSUCCESSORHINT_L(newSuccessorHintMsg));

                    sendMessageToUDP(predecessorNode, newSuccessorHintMsg);
                }*/
            }

            if (!predecessorNode.isUnspecified() && !joinResponse->getPreNode().isUnspecified()&& predecessorNode!= joinResponse->getPreNode()) 
            {
                callUpdate(predecessorNode, false);
            }
            predecessorNode = joinResponse->getPreNode();
            callUpdate(predecessorNode, true);
        }
    }

    updateTooltip();
    
    sendMessageToUDP(cp->getDest(),cp);

    //changeState(READY);
//    bootstrapList->addBootstrapNode(thisNode);

    // immediate stabilization protocol
    cancelEvent(stabilize_timer);
    scheduleAt(simulation.simTime(), stabilize_timer);

    // immediate finger repair protocol
    cancelEvent(fixfingers_timer);
    scheduleAt(simulation.simTime(), fixfingers_timer);
    delete joinResponse;
}


void HChord_U::handleStabilizeCall(HStabilizeCall* call)
{
    // our predecessor seems to be alive
    missingPredecessorStabRequests = 0;

    // reply with StabilizeResponse message
    UHStabilizeResponse* stabilizeResponse = new UHStabilizeResponse("HStabilizeResponse");
    stabilizeResponse->setPre(predecessorNode);
    stabilizeResponse->setDest(call->getSrc());
    stabilizeResponse->setSrc(thisNode);
   // stabilizeResponse->setOverlay(UPPER_OVERLAY);
    stabilizeResponse->setMesg_type(STABILIZE_RESPONSE);
    stabilizeResponse->setLength(HSTABILIZERESPONSE_L(stabilizeResponse));

    sendMessageToUDP(call->getSrc(), stabilizeResponse);
    
    delete call;

}

void HChord_U::handleStabilizeResponse(HStabilizeResponse* stabilizeResponse)
{
    
    // our successor seems to be alive
    missingSuccessorStabResponses= 0;

    // fetch the successor's predecessor
    NodeHandle predecessor = stabilizeResponse->getPre();

    // is the successor's predecessor a new successor for this node?
    if (successorList->isEmpty() || predecessor.key.isBetween(thisNode.key,successorList->getSuccessor().key)) 
    {
        // add the successor's predecessor to the successor list
        successorList->addSuccessor(predecessor);
        updateTooltip();
    }

    // compile NOTIFY RPC
    UHNotifyCall* notifyCall = new UHNotifyCall("UNotifyCall");
    notifyCall->setLength(HNOTIFYCALL_L(notifyCall));
	notifyCall->setSrc(thisNode);
	notifyCall->setDest(successorList->getSuccessor());
	notifyCall->setMesg_type(NOTIFY_CALL);
	//notifyCall->setOverlay(UPPER_OVERLAY);
    sendMessageToUDP(successorList->getSuccessor(), notifyCall);

    delete stabilizeResponse;

}

void HChord_U::handleNotifyCall(HNotifyCall* call)
{
    // our predecessor seems to be alive
    missingPredecessorStabRequests = 0;
    bool newPredecessorSet = false;

    NodeHandle newPredecessor = call->getSrc();

 	// is the new predecessor closer than the current one?
   if (predecessorNode.isUnspecified() ||newPredecessor.key.isBetween(predecessorNode.key, thisNode.key)) 
   {

    	if ((predecessorNode.isUnspecified()) ||(newPredecessor != predecessorNode)) 
    	{
            // send update to application if we've got a new predecessor
            if (!predecessorNode.isUnspecified()) 
            {
        	        callUpdate(predecessorNode, false);
        	}
        	callUpdate(newPredecessor, true);

        	// inform the original predecessor about the new predecessor

        	// set up new predecessor
        	predecessorNode = newPredecessor;
        	updateTooltip();

        	newPredecessorSet = true;
        }
    }

  	// compile NOTIFY response
  	UHNotifyResponse* notifyResponse = new UHNotifyResponse("UHNotifyResponse");
	
	int sucNum = successorList->getSize();
	notifyResponse->setSucNum(sucNum);
	notifyResponse->setSucNodeArraySize(sucNum);
	notifyResponse->setSrcNode(thisNode);
	
	// can't accept the notify sender as predecessor,
	// tell it about my correct predecessor
	for (int k = 0; k < sucNum; k++) 
	{
		notifyResponse->setSucNode(k, successorList->getSuccessor(k));
	}
	
    
    notifyResponse->setSrc(thisNode);
    notifyResponse->setDest(call->getSrc());
//    notifyResponse->setOverlay(UPPER_OVERLAY);
    notifyResponse->setMesg_type(NOTIFY_RESPONSE);
	notifyResponse->setLength(HNOTIFYRESPONSE_L(notifyResponse));
	
    sendMessageToUDP(call->getSrc(), notifyResponse);
    delete call;
}


void HChord_U::handleNotifyResponse(HNotifyResponse* notifyResponse)
{
    if (successorList->getSuccessor() != notifyResponse->getSrc()) 
    {
    	    EV << "[HChord_U::handleRpcNotifyResponse() @ " << thisNode.ip
    	       << " (" << thisNode.key.toString(16) << ")]\n"
    	       << "    The srcNode of the received NotifyResponse is not our "
    	       << " current successor"
        	   << endl;
        	 delete notifyResponse;
       		 return;
    	
    }	

    	// if the NotifyResponse sender couldn't accept me as predecessor,
    	// put its predecessor into the successor list and starts stabilizing

    	// replace our successor list by our successor's successor list
    	successorList->updateList(notifyResponse);

    	updateTooltip();
		delete notifyResponse;
}


void HChord_U::handleFixfingersCall(HFixfingersCall* call)
{
    NodeHandle requestor = call->getSrc();
    bool err;
    
	if(isSiblingFor(thisNode,call->getLookupKey(),1,&err))//message is destined for this node
	{
		UHFixfingersResponse* fixfingersResponse =new UHFixfingersResponse("UFixfingersResponse");
	
	
		fixfingersResponse->setSucNode(thisNode);
		
		fixfingersResponse->setFinger(call->getFinger());
		//fixfingersResponse->setLength(HFIXFINGERSRESPONSE_L(fixfingersResponse));
		//fixfingersResponse->setOverlay(UPPER_OVERLAY);
		fixfingersResponse->setSrc(thisNode);
		fixfingersResponse->setDest(call->getSrc());
		fixfingersResponse->setMesg_type(FIXFINGERS_RESPONSE);

	
	    sendMessageToUDP(call->getSrc(), fixfingersResponse);
	    delete call;
	}
	else
	{
		//node is destined for anoter node 
		//find it and send it
		NodeHandle nextHop = findNode_h(call->getLookupKey(),1,1,call);
		if(!nextHop.isUnspecified())
			sendMessageToUDP(nextHop,call);
	}

}


void HChord_U::handleFixfingersResponse(HFixfingersResponse* fixfingersResponse)
{
    // set new finger pointer#
	
       if(fixfingersResponse->getSucNode().isUnspecified())
       		return;

       fingerTable->setFinger(fixfingersResponse->getFinger(), fixfingersResponse->getSucNode());
       delete fixfingersResponse;
       
}
 
void HChord_U::handleStabilizeSuperPeerCall (HStabilizeSuperPeerCall *spstab)
{	
	//if it is a super peer then send the strong peer list
	if(super_peer)
	{
		HStabilizeSuperPeerResponse *spstabr = new HStabilizeSuperPeerResponse("SuperPeerStabResponse");
		spstabr->setSrc(thisNode);
		spstabr->setDest(spstab->getSrc());
		spstabr->setMesg_type(STABILIZE_SUPER_PEER_RESPONSE);
		spstabr->setNum(StrongPeerSet.size());
		
		std::map<OverlayKey,NodeHandle>::iterator it = StrongPeerSet.begin();
		spstabr->setStrongPeersArraySize(StrongPeerSet.size());
		for(int i=0;it!=StrongPeerSet.end();it++,i++)
		{
			spstabr->setStrongPeers(i,it->second); 
		}
		spstabr->setPreNode(predecessorNode);
/*		if(SmallestNode.key>spstab->getSrc().key)//a new small node has come
		{
			SmallestNode = spstab->getSrc();
		}
		*/
		//send
		sendMessageToUDP(spstabr->getDest(),spstabr);
	}
	delete spstab;
}

void HChord_U::handleStabilizeSuperPeerResponse (HStabilizeSuperPeerResponse *res)
{//big changes
	if(super_peer)
	{
		delete res;
		return;
	}
	if(res->getNum()==1)//no new super peer has come
	{
		delete res;
		return;
	}
	else
	{
		NodeHandle sp1,sp2;
		sp1=res->getStrongPeers(0);
		sp2=res->getStrongPeers(1);
		EV<<"Strong peer 1 "<<sp1<<"   Strong peer 2 "<<sp2<<endl;
		if(thisNode.key.isBetweenR(sp1.key,sp2.key))
		{
			lower->SuperPeerNode=sp2;
		}
		else if(thisNode.key.isBetweenR(sp2.key,sp1.key))
		{
			lower->SuperPeerNode=sp1;
		}
		updateTooltip();
		delete res;
	}
}
		

void HChord_U::handleMigrateRequest(HMigrateRequest *migr)
{
	NodeHandle requestor = migr->getSrc();
	if(super_peer&&in_upper&&StrongPeerSet.size()<2)
	{
		//add this node to set of strong peers 
		StrongPeerSet.insert(make_pair(requestor.key,requestor));
		//send migrate response
		HMigrateResponse *migres = new HMigrateResponse("HMigrateResponse");
		migres->setSrc(thisNode);
		migres->setDest(requestor);
		migres->setMesg_type(MIGRATE_RESPONSE);
		sendMessageToUDP(requestor,migres);
	}
	delete migr;
}


void HChord_U::handleMigrateResponse(HMigrateResponse *migres)
{
	//become super peer and after fingerDelay*2 
	//schedule a upper join request
	super_peer=1;
	//add self to strong peer set
	StrongPeerSet.insert(make_pair(thisNode.key,thisNode));
	
	cMessage *upper_join_timer= new cMessage("upper_join_timer");
	scheduleAt(simulation.simTime()+2*fixfingersDelay,upper_join_timer);
	
	delete migres;
	cancelEvent(migrate_timer);
	
}


void HChord_U::handleLargestNodeRequest(HLargestNodeRequest *lnreq)	
{
	if(super_peer)
	{
		if(thisNode.key<lower->SuperPeerNode.key)//less than its sp
		{
			sendMessageToUDP(lower->SuperPeerNode,lnreq);
		}
		else
		{
			std::map<OverlayKey,NodeHandle>::reverse_iterator it=StrongPeerSet.rbegin();
			NodeHandle strp = it->second;
			if(strp==thisNode)
			{
				//reply with largest peer
				HLargestNodeResponse *lnres = new HLargestNodeResponse("LargestResponse");
				lnres->setSrc(thisNode);
				lnres->setDest(lnreq->getSrc());
				lnres->setMesg_type(LARGEST_NODE_RESPONSE);
				lnres->setNode(LargestNode);
				lnres->setSuc(LargestNodeSuc);
				sendMessageToUDP(lnreq->getSrc(),lnres);
				delete lnreq;
				
			}
			else
			{
				sendMessageToUDP(strp,lnreq);
			}
		}
	}
}

void HChord_U::handleLargestNodeResponse(HLargestNodeResponse *lnres)	
{
	NodeHandle largest = lnres->getNode();
	
	//send succ to change pre to largest node
	/*HChangePredecessor *cp = new HChangePredecessor("ChangePre");
	cp->setSrc(thisNode);
	cp->setDest(successorList_lower->getSuccessor());
	cp->setMesg_type(CHANGE_PRE);
	sendMessageToUDP(cp->getDest(),cp);	*/

	//send largest node to change suc
	HChangeSuccessorRequest *chsuc = new HChangeSuccessorRequest("ChangeSucREq");
	chsuc->setSrc(thisNode);
	chsuc->setDest(largest);
	chsuc->setMesg_type(CHANGE_SUC_REQ);
	chsuc->setNewPre(thisNode);//exception here
	chsuc->setNewSuc(successorList_lower->getSuccessor());
	sendMessageToUDP(largest,chsuc);
	
	//set its successor to largest's successor
	
	/*while(!successorList_lower->isEmpty())//empty the successor list
	{
		successorList_lower->popSuccessor();
	}
	successorList_lower->addSuccessor(lnres->getSuc());*/
	
	EV<<"got largest node response largest node "<<largest<<"  succ  "<<lnres->getSuc()<<endl;
	
	delete lnres;
}

void HChord_U::handleChangeSuccessorRequest(HChangeSuccessorRequest *call)
{
	
	//send sp to change suc to its suc
	HChangeSuccessorResponse *chsuc = new HChangeSuccessorResponse("ChangeSucResponse");
	chsuc->setSrc(thisNode);
	chsuc->setDest(call->getSrc());
	chsuc->setMesg_type(CHANGE_SUC_RES);
	//chsuc->setNewSuc(old);
	chsuc->setNewPre(thisNode);//exception here
	sendMessageToUDP(call->getSrc(),chsuc);
	updateTooltip();
	delete call;		
}

void HChord_U::handleChangeSuccessorResponse(HChangeSuccessorResponse *call)
{
	NodeHandle suc = call->getNewSuc();
	NodeHandle old = successorList_lower->getSuccessor();
	while(!successorList_lower->isEmpty())				
	{
		successorList_lower->popSuccessor();
	}
	successorList_lower->addSuccessor(suc);
	//send upper join to sp
	UHJoinCall *ujoincall = new UHJoinCall("UHJoinCall");
	ujoincall->setSrc(thisNode);
	ujoincall->setDest(lower->SuperPeerNode);
	ujoincall->setMesg_type(JOIN_REQUEST);
	sendMessageToUDP(lower->SuperPeerNode,ujoincall);
	//send suc to change pre to largest
	HChangePredecessor *cp = new HChangePredecessor("ChangePre");
	cp->setSrc(thisNode);
	cp->setDest(old);
	cp->setMesg_type(CHANGE_PRE);
	cp->setNewPre(call->getNewPre());
	sendMessageToUDP(old,cp);
	updateTooltip();
	delete call;
}
			
void HChord_U::handleChangePredecessor(HChangePredecessor *call)
{
	if(call->getNewPre()==thisNode)
		lower->predecessorNode=NodeHandle::UNSPECIFIED_NODE;
	EV<<"handle change predecessor "<<endl;
	NodeHandle pre = call->getNewPre();
	
	lower->predecessorNode = pre;
	updateTooltip();
	delete call;
}

	

        /*if (proximityRouting) {
            for (unsigned int i = 0;
                 i < fixfingersResponse->getSucNodeArraySize();
                 i++) {
                if (fixfingersResponse->getSucNode(i).isUnspecified())
                    continue;
                if (fixfingersResponse->getSucNode(i) == thisNode)
                    break;
                pingNode(fixfingersResponse->getSucNode(i), -1, 0, NULL,
                         NULL, NULL, fixfingersResponse->getFinger());
            }
        }*/
    



/*void HChord_U::pingResponse(PingResponse* pingResponse, cPolymorphic* context,
                         int rpcId, simtime_t rtt)
{
    EV << "[HChord_U::pingResponse() @ " << thisNode.ip
       << " (" << thisNode.key.toString(16) << ")]\n"
       << "    Received a Ping RPC Response: id=" << rpcId << "\n"
       << "    msg=" << *pingResponse << " rtt=" << rtt
       << endl;

    fingerTable->updateFinger(rpcId, pingResponse->getSrcNode(), rtt);
}

void HChord_U::pingTimeout(PingCall* pingCall,
                        const TransportAddress& dest,
                        cPolymorphic* context, int rpcId)
{
    EV << "[HChord_U::pingTimeout() @ " << thisNode.ip
       << " (" << thisNode.key.toString(16) << ")]\n"
       << "    Ping RPC timeout: id=" << rpcId << endl;

    if (dest == fingerTable->getFinger(rpcId))
        fingerTable->setFinger(rpcId, NodeHandle::UNSPECIFIED_NODE);
}*/

void HChord_U::findFriendModules()
{
    fingerTable = check_and_cast<HChordFingerTable*>
                  (parentModule()->submodule("fingerTable_u"));

    successorList = check_and_cast<HChordSuccessorList*>
                    (parentModule()->submodule("successorList_u"));
    fingerTable_lower = check_and_cast<HChordFingerTable*>
                  (parentModule()->submodule("fingerTable_l"));

    successorList_lower = check_and_cast<HChordSuccessorList*>
                    (parentModule()->submodule("successorList_l"));
   
    lower = check_and_cast<HChord_L *>
	    	   (parentModule()->submodule("hchord_l"));

}


void HChord_U::initializeFriendModules()
{
    // initialize finger table

    fingerTable->initializeTable(thisNode.key.getLength(), thisNode, this);
    fingerTable_lower->initializeTable(thisNode.key.getLength(), thisNode, this);
    // initialize successor list
    successorList->initializeList(par("successorListSize"), thisNode, this);
    successorList_lower->initializeList(par("successorListSize"), thisNode, this);

    lower->initializeOverlay(state,thisNode);
}


void HChord_U::updateTooltip()
{
    if (ev.isGUI()) {
        std::stringstream ttString;

        // show our predecessor and successor in tooltip
        ttString << predecessorNode << endl << thisNode << endl
                 << successorList->getSuccessor()<<endl
                 <<"------------------"<<endl<<lower->predecessorNode
                 <<endl<<thisNode
                 <<endl<<successorList_lower->getSuccessor()
                 <<endl<<"SP:"<<lower->SuperPeerNode;

        parentModule()->parentModule()->displayString().
        setTagArg("tt", 0, ttString.str().c_str());
        parentModule()->displayString().
        setTagArg("tt", 0, ttString.str().c_str());
        displayString().setTagArg("tt", 0, ttString.str().c_str());

        // draw an arrow to our current successor
        EV<<"Current successor "<<successorList->getSuccessor()<<endl;
        
        showOverlayNeighborArrow(successorList_lower->getSuccessor(), true,
          						"m=m,50,0,50,0;o=blue,1");
 
 	showOverlayNeighborArrow(successorList->getSuccessor(), false,
                                 "m=m,50,0,50,0;o=red,1");
        

	showOverlayNeighborArrow(predecessorNode, false,
                                 "m=m,50,100,50,100;o=green,1");

	showOverlayNeighborArrow(lower->predecessorNode, false,
                                 "m=m,50,100,50,100;o=yellow,1");

    }
}

OverlayKey HChord_U::distance(const OverlayKey& x, const OverlayKey& y) const
{
    return KeyUniRingMetric().distance(x, y);
}

/*void HChord_U::predecessorIsDead()
{}

void HChord_U::successorIsDead()
{}*/
