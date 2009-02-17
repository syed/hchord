#include <cfloat>
#include <assert.h>

#include <GlobalStatistics.h>
#include <Comparator.h>
#include <BootstrapList.h>

#include <HChordFingerTable.h>
#include <HChordSuccessorList.h>

#include "HChord_L.h"
#include "HChord_U.h"

Define_Module(HChord_L);

HChord_L::HChord_L()
{
    stabilize_timer  = stabilize_timer =  NULL;
}


void HChord_L::initializeOverlay(int stage,NodeHandle node)
{
  
    Enter_Method("initializeOverlay");
   
    successorListSize = par("successorListSize");
    joinRetry = par("joinRetry");
    stabilizeRetry = par("stabilizeRetry");
    joinDelay = par("joinDelay");
    stabilizeDelay = par("stabilizeDelay");
    fixfingersDelay = par("fixfingersDelay");
    aggressiveJoinMode = par("aggressiveJoinMode");
    extendedFingerTable = par("extendedFingerTable");
    numFingerCandidates = par("numFingerCandidates");


    keyLength = OverlayKey::getLength();
    missingPredecessorStabRequests = 0;
    missingSuccessorStabResponses = 0;
    thisNode = node;


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
    

    // find friend modules
    findFriendModules();
//	initializeFriendModules();
    
    // add some watches
    WATCH(predecessorNode);
    WATCH(thisNode);
    WATCH(bootstrapNode);
    WATCH(joinRetry);
    WATCH(SuperPeerNode);
    WATCH(SuperPeerPre);
    //WATCH(missingPredecessorStabRequests);
    //WATCH(missingSuccessorStabResponses);

    // self-messages
//  join_timer = new cMessage("join_timer");
    stabilize_timer= new cMessage("stabilize_timer");
    fixfingers_timer = new cMessage("fixfingers_timer");
    
    predecessorNode = NodeHandle::UNSPECIFIED_NODE;
    this->state = READY;
    
    
	//initiate stabilization protocol
    cancelEvent(stabilize_timer);
    scheduleAt(simulation.simTime() + stabilizeDelay, stabilize_timer);

	// initiate finger repair protocol
    cancelEvent(fixfingers_timer);
    scheduleAt(simulation.simTime() + fixfingersDelay,fixfingers_timer);

   
}


HChord_L::~HChord_L()
{
    // destroy self timer messages
//    cancelAndDelete(join_timer);
    cancelAndDelete(stabilize_timer);
    cancelAndDelete(fixfingers_timer);
  
}



void HChord_L::handleMessage(cMessage* msg)
{
    // catch JOIN timer
    //if (msg->isName("join_timer")) {
      //  handleJoinTimerExpired(msg);
    //
    // catch STABILIZE timer
    if (msg->isName("stabilize_timer")) {
        handleStabilizeTimerExpired(msg);
    }

    // catch FIX_FINGERS timer
    else if (msg->isName("fixfingers_timer")) {
        handleFixFingersTimerExpired(msg);
    }
    // unknown self message
    else {
    	handleUDPMessage(msg);
       // error("HChord_L::handleTimerEvent(): received self message of "
         //     "unknown type!");
    }
}

void HChord_L::handleUDPMessage(cMessage* msg)
{
    HChordMessage* hchordMsg = check_and_cast<HChordMessage*>(msg);
    switch(hchordMsg->getMesg_type()) {
    case JOIN_REQUEST :
	{
       HJoinCall * hcjoin = check_and_cast<HJoinCall *>(msg);
	   handleJoinRequest(hcjoin);
	}
	break;
    case JOIN_RESPONSE :
	{
	   HJoinResponse *hcresp = check_and_cast<HJoinResponse *>(msg);
	   handleJoinResponse(hcresp);
	}
	break;
    case NEW_SUCCESSOR_HINT :
	{
	   HNewSuccessorHintMsg  *newSucc = check_and_cast<HNewSuccessorHintMsg *>(msg);
	   handleNewSuccessorHint(newSucc);
	}
	break;
    case STABILIZE_CALL :
	{
	   HStabilizeCall *stab = check_and_cast<HStabilizeCall *>(msg);
	   handleStabilizeCall(stab);
	}
	break;
    case STABILIZE_RESPONSE :
	{
	   HStabilizeResponse *stabr = check_and_cast<HStabilizeResponse *>(msg);
	   handleStabilizeResponse(stabr);
	}
	break;
    case NOTIFY_CALL :
	{
	   HNotifyCall  *call = check_and_cast<HNotifyCall *>(msg);
	   handleNotifyCall(call);
	}
	break;
    case NOTIFY_RESPONSE :
	{
	   HNotifyResponse *notr = check_and_cast<HNotifyResponse *>(msg);
	   handleNotifyResponse(notr);
	}
	break;
    case FIXFINGERS_CALL :
	{
	   HFixfingersCall  *fix = check_and_cast<HFixfingersCall *>(msg);
	   handleFixfingersCall(fix);
	}
	break;
    case FIXFINGERS_RESPONSE:
	{
	   HFixfingersResponse *fixr = check_and_cast<HFixfingersResponse *>(msg);
	   handleFixfingersResponse(fixr);
	}
	break;
	default:
        error("handleUDPMessage(): Unknown message type!");
        break;
    }

    //delete chordMsg;
}

int HChord_L::getMaxNumSiblings()
{
    return successorListSize;
}

int HChord_L::getMaxNumRedundantNodes()
{
    return extendedFingerTable ? numFingerCandidates : 1;
}


bool HChord_L::isSiblingFor(const NodeHandle& node,
                         const OverlayKey& key,
                         int numSiblings,
                         bool* err)
{

    EV<<"is sibling for key looking for "<<key<<"num = "<<numSiblings<<"node is "<<node<<endl;

    if (key.isUnspecified())
        error("HChord_L::isSiblingFor(): key is unspecified!");

    if (state != READY) 
    {
        *err = true;
        return false;
    }

    if (numSiblings > getMaxNumSiblings()) 
    {
        opp_error("HChord_L::isSiblingFor(): numSiblings too big!");
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



NodeHandle HChord_L::findNode_h(const OverlayKey& key,int numSiblings,int numRedundantNodes , BaseOverlayMessage* msg)
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


NodeHandle HChord_L::closestPreceedingNode(const OverlayKey& key)
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
        temp << "HChord_L::closestPreceedingNode(): Successor list broken "
        	<< thisNode.key << " " << key;
	    EV<<"HChord_L::closestPreceedingNode(): Successor list broken "<<thisNode.key<<"  "<<key;
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
			
                EV << "[HChord_L::closestPreceedingNode() @ " << thisNode.ip
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

    EV << "[HChord_L::closestPreceedingNode() @ " << thisNode.ip
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
	std::stringstream temp("Error in HChord_L::closestPreceedingNode()!\n");
	temp << thisNode.key << " " << key;
	error(temp.str().c_str());
	nextHop=(NodeHandle::UNSPECIFIED_NODE);
	return nextHop;
	
}


/*void HChord_L::recordOverlaySentStats(BaseOverlayMessage* msg)
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

void HChord_L::finishOverlay()
{
    // remove this node from the bootstrap list
//    bootstrapList->removeBootstrapNode(thisNode);

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

void HChord_L::handleStabilizeTimerExpired(cMessage* msg)
{
    if (state != READY)
        return;

    if (missingPredecessorStabRequests >= stabilizeRetry) {
        // predecessor node seems to be dead
        // remove it from the predecessor / successor lists
        successorList ->removeSuccessor(predecessorNode);
        //predecessorIsDead();

        ////callUpdate(predecessorNode, false);
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
            //callUpdate(predecessorNode, false);
            predecessorNode = NodeHandle::UNSPECIFIED_NODE;
        }

        missingSuccessorStabResponses = 0;
        updateTooltip();

        if (successorList->isEmpty()) {
            //changeState(INIT);
            //changeState(BOOTSTRAP);
            return;
        }
    }

    if (!successorList->isEmpty()) {
        // call STABILIZE RPC
        HStabilizeCall* call = new HStabilizeCall("HStabilizeCall");
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


void HChord_L::handleFixFingersTimerExpired(cMessage* msg)
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
	     //if we have offset > super peer then point it to super peer as 
	     //all nodes in sub overlay have less id than sp
	     //special case is last sp
	     	if(offset>=SuperPeerNode.key&&thisNode.key<=SuperPeerNode.key)
	     	{
	     		fingerTable->setFinger(nextFinger,SuperPeerNode);
	     		EV<<thisNode<<" lookup key "<<lookupKey<<" setting to super peer fingr no "<<nextFinger<<endl;
			}
			else if(!SuperPeerPre.isUnspecified()&&offset<SuperPeerPre.key &&thisNode.key<=SuperPeerNode.key)//less than the predecessor
			{
					fingerTable->setFinger(nextFinger,SuperPeerNode);
					EV<<thisNode<<" lookup key "<<lookupKey<<" setting to super peer pre finger no "<<nextFinger<<endl;
			}
			
			else if(offset<=SuperPeerNode.key && thisNode.key>SuperPeerNode.key)//this is exeption condition
			{
				fingerTable->setFinger(nextFinger,SuperPeerNode);
				EV<<thisNode<<" lookup key "<<lookupKey<<" setting to super peer fingr no "<<nextFinger<<endl;
			}
			else
			{				
            // call FIXFINGER RPC
            	HFixfingersCall* call = new HFixfingersCall("HFixfingersCall");
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



void HChord_L::handleNewSuccessorHint(HNewSuccessorHintMsg* hchordMsg)
{
    HNewSuccessorHintMsg* newSuccessorHintMsg =
        check_and_cast<HNewSuccessorHintMsg*>(hchordMsg);

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


void HChord_L::handleJoinRequest(HJoinCall *joinCall )
{
    NodeHandle requestor = joinCall->getSrc();
    bool err;
    
	if(isSiblingFor(thisNode,requestor.key,1,&err))//message is destined for this node
	{
		processJoinRequest(joinCall);
	}
	else
	{
		//node is destined for anoter node 
		//find it and send it
		NodeHandle nextHop = findNode_h(requestor.key,1,1,joinCall);

		if(!nextHop.isUnspecified())
		{
			joinCall->setDest(nextHop);
			sendMessageToUDP(nextHop,joinCall);
		}
	}

}


void HChord_L::processJoinRequest(HJoinCall *joinCall)
{

	//SuperPeerNode = joinCall->getSuperPeerNode();
	
	if(joinCall->getSrc()==thisNode)
	{
		delete joinCall;
		return;
	}
		
    HJoinResponse* joinResponse = new HJoinResponse("HJoinResponse");
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
	//add super peer
	joinResponse->setSuperPeerNode(SuperPeerNode);

	sendMessageToUDP(src,joinResponse);


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
            HNewSuccessorHintMsg * newSuccessorHintMsg = new HNewSuccessorHintMsg ("NEWSUCCESSORHINT");
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
                //callUpdate(predecessorNode, false);
            }
            //callUpdate(src, true);
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

void HChord_L::handleJoinResponse(HJoinResponse* joinResponse)
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
    SuperPeerNode = joinResponse->getSuperPeerNode();
    SuperPeerPre  = joinResponse->getSuperPeerPre();
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
                //callUpdate(predecessorNode, false);
            }
            predecessorNode = joinResponse->getPreNode();
            //callUpdate(predecessorNode, true);
        }
    }

    updateTooltip();

    //changeState(READY);
    //bootstrapList->removeBootstrapNode(thisNode);

    // immediate stabilization protocol
    cancelEvent(stabilize_timer);
    scheduleAt(simulation.simTime(), stabilize_timer);

    // immediate finger repair protocol
    cancelEvent(fixfingers_timer);
    scheduleAt(simulation.simTime(), fixfingers_timer);
    
    //immidiate stabilize super peer
    if(SuperPeerNode == thisNode)
		return;
	HStabilizeSuperPeerCall *spstab = new HStabilizeSuperPeerCall("StabilizeSuperPeerCall");
	spstab->setSrc(thisNode);
	spstab->setDest(SuperPeerNode);
	spstab->setMesg_type(STABILIZE_SUPER_PEER_CALL);
	sendMessageToUDP(SuperPeerNode,spstab);
    
    delete joinResponse;
}


void HChord_L::handleStabilizeCall(HStabilizeCall* call)
{
    // our predecessor seems to be alive
    missingPredecessorStabRequests = 0;

    // reply with StabilizeResponse message
    HStabilizeResponse* stabilizeResponse = new HStabilizeResponse("HStabilizeResponse");
    stabilizeResponse->setPre(predecessorNode);
    stabilizeResponse->setDest(call->getSrc());
    stabilizeResponse->setSrc(thisNode);
   // stabilizeResponse->setOverlay(UPPER_OVERLAY);
    stabilizeResponse->setMesg_type(STABILIZE_RESPONSE);
    stabilizeResponse->setLength(HSTABILIZERESPONSE_L(stabilizeResponse));

    sendMessageToUDP(call->getSrc(), stabilizeResponse);
    
    delete call;

}

void HChord_L::handleStabilizeResponse(HStabilizeResponse* stabilizeResponse)
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
    HNotifyCall* notifyCall = new HNotifyCall("NotifyCall");
    notifyCall->setLength(HNOTIFYCALL_L(notifyCall));
	notifyCall->setSrc(thisNode);
	notifyCall->setDest(successorList->getSuccessor());
	notifyCall->setMesg_type(NOTIFY_CALL);
	//notifyCall->setOverlay(UPPER_OVERLAY);
    sendMessageToUDP(successorList->getSuccessor(), notifyCall);

    delete stabilizeResponse;

}

void HChord_L::handleNotifyCall(HNotifyCall* call)
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
        	        //callUpdate(predecessorNode, false);
        	}
        	//callUpdate(newPredecessor, true);

        	// inform the original predecessor about the new predecessor

        	// set up new predecessor
        	predecessorNode = newPredecessor;
        	updateTooltip();

        	newPredecessorSet = true;
        }
    }

  	// compile NOTIFY response
  	HNotifyResponse* notifyResponse = new HNotifyResponse("HNotifyResponse");
	if(upper->super_peer||successorList->getSuccessor().key<thisNode.key)//last node special
	{
		notifyResponse->setSucNum(0);
		notifyResponse->setSucNodeArraySize(0);
		notifyResponse->setSrcNode(thisNode);
	}
	else
	{
		
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
	}	
    
    notifyResponse->setSrc(thisNode);
    notifyResponse->setDest(call->getSrc());
//    notifyResponse->setOverlay(UPPER_OVERLAY);
    notifyResponse->setMesg_type(NOTIFY_RESPONSE);
	notifyResponse->setLength(HNOTIFYRESPONSE_L(notifyResponse));
	
    sendMessageToUDP(call->getSrc(), notifyResponse);
    delete call;
}


void HChord_L::handleNotifyResponse(HNotifyResponse* notifyResponse)
{
    if (successorList->getSuccessor() != notifyResponse->getSrc()) 
    {
    	    EV << "[HChord_L::handleRpcNotifyResponse() @ " << thisNode.ip
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


void HChord_L::handleFixfingersCall(HFixfingersCall* call)
{
    NodeHandle requestor = call->getSrc();
    bool err;
    
	if(isSiblingFor(thisNode,call->getLookupKey(),1,&err))//message is destined for this node
	{
		HFixfingersResponse* fixfingersResponse =new HFixfingersResponse("FixfingersResponse");
	
	
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
		{
			call->setDest(nextHop);
			sendMessageToUDP(nextHop,call);
		}
	}

		
}



void HChord_L::handleFixfingersResponse(HFixfingersResponse* fixfingersResponse)
{
    // set new finger pointer#
	
       if(fixfingersResponse->getSucNode().isUnspecified())
       		return;

       fingerTable->setFinger(fixfingersResponse->getFinger(), fixfingersResponse->getSucNode());
       delete fixfingersResponse;
       
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
    



/*void HChord_L::pingResponse(PingResponse* pingResponse, cPolymorphic* context,
                         int rpcId, simtime_t rtt)
{
    EV << "[HChord_L::pingResponse() @ " << thisNode.ip
       << " (" << thisNode.key.toString(16) << ")]\n"
       << "    Received a Ping RPC Response: id=" << rpcId << "\n"
       << "    msg=" << *pingResponse << " rtt=" << rtt
       << endl;

    fingerTable->updateFinger(rpcId, pingResponse->getSrcNode(), rtt);
}

void HChord_L::pingTimeout(PingCall* pingCall,
                        const TransportAddress& dest,
                        cPolymorphic* context, int rpcId)
{
    EV << "[HChord_L::pingTimeout() @ " << thisNode.ip
       << " (" << thisNode.key.toString(16) << ")]\n"
       << "    Ping RPC timeout: id=" << rpcId << endl;

    if (dest == fingerTable->getFinger(rpcId))
        fingerTable->setFinger(rpcId, NodeHandle::UNSPECIFIED_NODE);
}*/

void HChord_L::findFriendModules()
{
    fingerTable = check_and_cast<HChordFingerTable*>
                  (parentModule()->submodule("fingerTable_l"));

    successorList = check_and_cast<HChordSuccessorList*>
                    (parentModule()->submodule("successorList_l"));
   
   upper = check_and_cast<HChord_U*>
   					(parentModule()->submodule("hchord_u"));

}


void HChord_L::initializeFriendModules()
{
    // initialize finger table

//    fingerTable->initializeTable(thisNode.key.getLength(), thisNode,upper);
    //fingerTable_lower->initializeTable(thisNode.key.getLength(), thisNode, this);
    // initialize successor list
 //   successorList->initializeList(par("successorListSize"), thisNode, upper);
   // successorList_lower->initializeList(par("successorListSize"), thisNode, this,LOWER_OVERLAY);

}


void HChord_L::updateTooltip()
{
 	upper->updateTooltip();  
}

/*OverlayKey HChord_L::distance(const OverlayKey& x, const OverlayKey& y) const
{
    return KeyUniRingMetric().distance(x, y);
}*/


void HChord_L::sendMessageToUDP(NodeHandle dest, cMessage *msg)
{
	send(msg,"to_upper");
}
/*void HChord_L::predecessorIsDead()
{}

void HChord_L::successorIsDead()
{}*/
