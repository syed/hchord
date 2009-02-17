

cplusplus {{
#include <IPvXAddress.h>
#include <NodeHandle.h>
#include <CommonMessages_m.h>

// constants for message length in bit
static const int HCHORDCOMMAND_L = 8;
static const int SUCNUM_L = 8;
static const int FINGER_L = 8;
static const int STEP_L = 8;
static const int DBNODESET_L = 1;
static const int OTHERLOOKUP_L = 1;
static const int PRENODESET_L = 1;
static const int OVERLAY_L=8;
//static const int OVERLAY_CTRL_L=sizeof(OverlayCtrlInfo);

#define HCHORD_L(msg)  (BASEOVERLAY_L(msg) + NODEHANDLE_L*2 + OVERLAY_L*2 )

#define HNEWSUCCESSORHINT_L(msg) (BASEOVERLAY_L(msg) + NODEHANDLE_L*3 + OVERLAY_L*2 )
#define HNOTIFYCALL_L(msg) (HCHORD_L(msg) + DBNODESET_L)
#define HNOTIFYRESPONSE_L(msg) (HCHORD_L(msg) + SUCNUM_L + NODEHANDLE_L + (msg->getSucNodeArraySize() * NODEHANDLE_L) )
#define HJOINCALL_L(msg) (BASEOVERLAY_L(msg) + NODEHANDLE_L*2 + OVERLAY_L*2 )
#define HJOINRESPONSE_L(msg) (BASEOVERLAY_L(msg) + NODEHANDLE_L*2 + OVERLAY_L*2 + SUCNUM_L + NODEHANDLE_L + (msg->getSucNodeArraySize() * NODEHANDLE_L))
#define HSTABILIZECALL_L(msg) ( BASEOVERLAY_L(msg) + NODEHANDLE_L*2 + OVERLAY_L*2)

#define HSTABILIZERESPONSE_L(msg) (HCHORD_L(msg) + NODEHANDLE_L)
#define HFIXFINGERSCALL_L(msg) (BASEOVERLAY_L(msg) + NODEHANDLE_L*2 + OVERLAY_L*2 + FINGER_L)
#define HFIXFINGERSRESPONSE_L(msg) (HCHORD_L(msg) + FINGER_L + (msg->getSucNodeArraySize() * NODEHANDLE_L))


#define JOIN_REQUEST 0
#define JOIN_RESPONSE 1
#define NEW_SUCCESSOR_HINT 2
#define STABILIZE_CALL 3
#define STABILIZE_RESPONSE 4
#define FIXFINGERS_CALL 5
#define FIXFINGERS_RESPONSE 6
#define NOTIFY_CALL 7
#define NOTIFY_RESPONSE 8
#define MIGRATE_REQUEST 9
#define MIGRATE_RESPONSE 10
#define STABILIZE_SUPER_PEER_CALL 11
#define STABILIZE_SUPER_PEER_RESPONSE 12
#define LARGEST_NODE_REQUEST 13
#define LARGEST_NODE_RESPONSE 14
#define CHANGE_PRE 15
#define CHANGE_SUC_REQ 16
#define CHANGE_SUC_RES 17


}};

class noncobject IPvXAddress;
class noncobject NodeHandle;
class noncobject OverlayKey;
class BaseOverlayMessage;

//
// Base message for all messages used by HChord
//
message  HChordMessage extends BaseOverlayMessage
{
    fields:
	NodeHandle src;
	NodeHandle dest;
	int mesg_type;
};

//
// Message used to inform about a new successor node
//
message HJoinCall extends HChordMessage
{
    
};

//
// Message used to answer to a JoinCall message
//
message HJoinResponse extends HChordMessage
{
    fields:
        int sucNum;    // number of entries in the successor list
        NodeHandle sucNode[];    // successor list of the message originator
        NodeHandle preNode;    // in aggressiveJoinMode: predecessor hint
        NodeHandle superPeerNode;
        NodeHandle superPeerPre;
};

message HNotifyCall extends HChordMessage
{

};
message HNotifyResponse extends HChordMessage
{
    fields:
	NodeHandle srcNode;
	NodeHandle sucNode[];
	int sucNum; 
};

message HNewSuccessorHintMsg  extends HChordMessage
{
    fields:
	NodeHandle pre;
}

message HStabilizeCall extends HChordMessage
{

};

message HStabilizeResponse extends HChordMessage
{
    fields:
	NodeHandle pre;
};

message HFixfingersCall extends HChordMessage
{
    fields: 
	int finger;
	OverlayKey lookupKey;
};

message HFixfingersResponse extends HChordMessage
{
    fields:
	int finger;
	NodeHandle sucNode;
};

message HMigrateRequest extends HChordMessage
{
	
};

message HMigrateResponse extends HChordMessage
{
	
};

message HStabilizeSuperPeerCall extends HChordMessage
{
	fields:
	bool largest;
	NodeHandle Suc;
};

message HStabilizeSuperPeerResponse extends HChordMessage
{
    fields:
	NodeHandle strongPeers[];
	NodeHandle preNode;
	int num;
};

message HLargestNodeRequest extends HChordMessage
{

};

message HLargestNodeResponse extends HChordMessage
{
	fields:
	NodeHandle node;
	NodeHandle suc;
};

message HChangePredecessor extends HChordMessage
{
	fields:
	NodeHandle newPre;
};

message HChangeSuccessorRequest extends HChordMessage
{
	fields:
	NodeHandle newSuc;
	NodeHandle newPre;
}

message HChangeSuccessorResponse extends HChordMessage
{
	fields:
	NodeHandle newSuc;
	NodeHandle newPre;
}


message UHJoinCall extends HJoinCall
{
	fields:
	NodeHandle LowerNewSuc;

};

message UHJoinResponse extends HJoinResponse
{
	fields:
		NodeHandle LowerNewSuc;

};

message UHNotifyCall extends HNotifyCall
{

};
message UHNotifyResponse extends HNotifyResponse
{

};


message UHStabilizeCall extends HStabilizeCall
{

};

message UHStabilizeResponse extends HStabilizeResponse
{
    
};

message UHFixfingersCall extends HFixfingersCall
{
   
};

message UHFixfingersResponse extends HFixfingersResponse
{
    
};

message UHNewSuccessorHintMsg  extends  HNewSuccessorHintMsg
{
    
};


message LHStabilizeCall extends HStabilizeCall
{

};

message LHStabilizeResponse extends HStabilizeResponse
{
    
};

message LHFixfingersCall extends UHFixfingersCall
{
   
};

message LHFixfingersResponse extends HFixfingersResponse
{
    
};

