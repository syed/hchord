
#ifndef __HCHORD_L_H_
#define __HCHORD_L_H_

#include <BaseOverlay.h>


#include "HChordMessage_m.h"
//#include "HChord_U.h"
//
class HChord_U;

class HChordSuccessorList;
class HChordFingerTable;




    enum States {
        INIT = 0,
        JOINING_1 = 1,
        JOINING_2 = 2,
        JOINING_3 = 3,
        READY = 4,
        REFRESH = 5,
        SHUTDOWN = 6,

        //some aliases for compatibility
        JOINING = JOINING_1,
        JOIN = JOINING_1,
        BOOTSTRAP = JOINING_1,
        RSET = JOINING_2,
        BSET = JOINING_3
    };


class HChord_L : public cSimpleModule
{
public:

    HChord_L();
    virtual ~HChord_L();
    virtual void finishOverlay();

    virtual void initializeOverlay(int stage,NodeHandle curr_node);


    virtual void handleMessage(cMessage* msg);


    //virtual void handleUDPMessage(cMessage* msg);


//    virtual void recordOverlaySentStats(BaseOverlayMessage* msg);


//    virtual void finishOverlay();


    //OverlayKey distance(const OverlayKey& x, const OverlayKey& y) const;

    virtual void updateTooltip();

protected:
    int joinRetry; /**< */
    int stabilizeRetry; /**< // retries before neighbor considered failed */
    double joinDelay; /**< */
    double stabilizeDelay; /**< stabilize interval (secs) */
    double fixfingersDelay; /**< */
    int successorListSize; /**< */
    bool aggressiveJoinMode; /**< use modified (faster) JOIN protocol */
    bool extendedFingerTable;
    unsigned int numFingerCandidates;
    

    // timer messages
    cMessage* join_timer; /**< */
    cMessage* stabilize_timer; /**< */
    cMessage* fixfingers_timer; /**< */
    
    

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

    
    // node references
    NodeHandle thisNode;
    NodeHandle predecessorNode;
    NodeHandle bootstrapNode; 
    NodeHandle SuperPeerNode;
    NodeHandle SuperPeerPre;

    // module references
    HChordFingerTable* fingerTable;
   	HChordSuccessorList* successorList;
    

	HChord_U *upper;
    // chord routines
    
    void handleUDPMessage(cMessage *msg);
    void sendMessageToUDP(NodeHandle dest , cMessage *msg);

    //virtual void joinOverlay();
    //virtual void changeState(int toState);

 	virtual void findFriendModules();
    virtual void initializeFriendModules();
   
    
    //virtual void handleJoinTimerExpired(cMessage* msg);
    virtual void handleStabilizeTimerExpired(cMessage* msg);
    virtual void handleFixFingersTimerExpired(cMessage* msg);

    
    virtual void handleNewSuccessorHint(HNewSuccessorHintMsg * Msg);
    
    virtual NodeHandle closestPreceedingNode(const OverlayKey& key);
    NodeHandle findNode_h(const OverlayKey& key,int numRedundantNodes,int numSiblings,BaseOverlayMessage* msg);
	//NodeVector * findNode(const OverlayKey& key, int numRedundantNodes, int numSiblings, BaseOverlayMessage* msg=NULL);
    virtual bool isSiblingFor(const NodeHandle& node,const OverlayKey& key,int numSiblings, bool* err);
	int getMaxNumSiblings();
    int getMaxNumRedundantNodes();
    
    
    virtual void handleJoinRequest(HJoinCall *call);
    virtual void handleJoinResponse(HJoinResponse * joinResponse);
    virtual void processJoinRequest(HJoinCall *joinCall);
    
    virtual void handleNotifyCall ( HNotifyCall* call );
    virtual void handleNotifyResponse(HNotifyResponse* notifyResponse);
    
    virtual void handleStabilizeCall( HStabilizeCall* call );
    virtual void handleStabilizeResponse(HStabilizeResponse* stabilizeResponse);
    
    virtual void handleFixfingersCall ( HFixfingersCall* call );
    virtual void handleFixfingersResponse(HFixfingersResponse* fixfingersResponse);
   
 	friend class HChordSuccessorList;
	friend class HChord_U;
};

#endif


