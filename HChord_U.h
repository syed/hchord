
#ifndef __HCHORD_U_H_
#define __HCHORD_U_H_

#include <BaseOverlay.h>

#include "HChordMessage_m.h"
//#include "HChord_L.h"

class HChord_L;
class HChordSuccessorList;
class HChordFingerTable;



class HChord_U : public BaseOverlay
{
public:

    HChord_U();
    virtual ~HChord_U();
    virtual void finishOverlay();

    // see BaseOverlay.h
    virtual void initializeOverlay(int stage);
    
    virtual void handleMessage(cMessage *msg);

    // see BaseOverlay.h
    virtual void handleTimerEvent(cMessage* msg);

    // see BaseOverlay.h
    virtual void handleUDPMessage(BaseOverlayMessage* msg);

    // see BaseOverlay.h
//    virtual void recordOverlaySentStats(BaseOverlayMessage* msg);

    // see BaseOverlay.h
//    virtual void finishOverlay();

    // see BaseOverlay.h
    OverlayKey distance(const OverlayKey& x, const OverlayKey& y) const;

    virtual void updateTooltip();

protected:
    int joinRetry; /**< */
    int stabilizeRetry; /**< // retries before neighbor considered failed */
    double joinDelay; /**< */
    double stabilizeDelay; /**< stabilize interval (secs) */
    double fixfingersDelay; /**< */
    double migrateDelay;
    int successorListSize; /**< */
    bool aggressiveJoinMode; /**< use modified (faster) JOIN protocol */
    bool extendedFingerTable;
    unsigned int numFingerCandidates;
    int stabilizeSuperPeerDelay;
    int strong_peer;
    

    // timer messages
    cMessage* join_timer; /**< */
    cMessage* stabilize_timer; /**< */
    cMessage* fixfingers_timer; /**< */
    cMessage* migrate_timer;
    cMessage* stabilize_super_peer_timer;
    cMessage* upper_join_timer;
    
    

    // statistics
    int joinCount; 
    int stabilizeCount; 
    int fixfingersCount;
    int notifyCount; 
    int newsuccessorhintCount; /**< */
    int joinBytesSent; /**< */
    int stabilizeBytesSent; /**< */
    int notifyBytesSent; /**< */
    int fixfingersBytesSent; /**< */
    int newsuccessorhintBytesSent; /**< */


    int state;
    int keyLength; 
    int missingPredecessorStabRequests;
    int missingSuccessorStabResponses;
    int super_peer; 
    int in_upper;

    
    // node references
    NodeHandle predecessorNode;
    NodeHandle bootstrapNode; 

	NodeHandle predecessorNode_lower;
	
	NodeHandle SmallestNode;
	NodeHandle LargestNodeSuc;
	NodeHandle LargestNode;

    // module references
    HChordFingerTable* fingerTable;
   	HChordSuccessorList* successorList;
 
   	HChordFingerTable* fingerTable_lower;
   	HChordSuccessorList* successorList_lower;
   	
  	HChord_L *lower;	
  	
  	
  	std::map<OverlayKey,NodeHandle> StrongPeerSet;
  	

    // chord routines

    virtual void joinOverlay();
    virtual void changeState(int toState);

 	virtual void findFriendModules();
    virtual void initializeFriendModules();
   
    
    virtual void handleJoinTimerExpired(cMessage* msg);
    virtual void handleStabilizeTimerExpired(cMessage* msg);
    virtual void handleFixFingersTimerExpired(cMessage* msg);
    virtual void handleMigrateTimerExpired(cMessage *msg);
    virtual void handleStabilizeSuperPeerTimerExpired(cMessage *msg);
    virtual void handleUpperJoinTimerExpired(cMessage *msg);

    
    virtual void handleNewSuccessorHint(HNewSuccessorHintMsg * Msg);
    
    virtual NodeHandle closestPreceedingNode(const OverlayKey& key);
    NodeHandle findNode_h(const OverlayKey& key,int numRedundantNodes,int numSiblings,BaseOverlayMessage* msg);
	//NodeVector * findNode(const OverlayKey& key, int numRedundantNodes, int numSiblings, BaseOverlayMessage* msg=NULL);
    virtual bool isSiblingFor(const NodeHandle& node,const OverlayKey& key,int numSiblings, bool* err);
	int getMaxNumSiblings();
    int getMaxNumRedundantNodes();
    
    
    virtual void handleJoinRequest(HJoinCall *call);
    virtual void handleJoinResponse(UHJoinResponse * joinResponse);
    virtual void processJoinRequest(UHJoinCall *joinCall);
    
    virtual void handleNotifyCall ( HNotifyCall* call );
    virtual void handleNotifyResponse(HNotifyResponse* notifyResponse);
    
    virtual void handleStabilizeCall( HStabilizeCall* call );
    virtual void handleStabilizeResponse(HStabilizeResponse* stabilizeResponse);
    
    virtual void handleFixfingersCall ( HFixfingersCall* call );
    virtual void handleFixfingersResponse(HFixfingersResponse* fixfingersResponse);
    
    virtual void handleMigrateRequest (HMigrateRequest *migr);
    virtual void handleMigrateResponse(HMigrateResponse *migres);
    
    virtual void handleStabilizeSuperPeerCall (HStabilizeSuperPeerCall *spstab);
    virtual void handleStabilizeSuperPeerResponse (HStabilizeSuperPeerResponse *spstabr);
    
    virtual void handleLargestNodeRequest(HLargestNodeRequest *lnreq);
    virtual void handleLargestNodeResponse(HLargestNodeResponse *lrep);
    
    virtual void handleChangeSuccessorRequest(HChangeSuccessorRequest *newsuc);
    virtual void handleChangeSuccessorResponse(HChangeSuccessorResponse *newsuc);
    
    virtual void handleChangePredecessor(HChangePredecessor *newpre);
   
 	friend class HChordSuccessorList;
 	friend class HChord_L;
};

#endif
