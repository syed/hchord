#ifndef __HCHORDSUCCESSORLIST_H_
#define __HCHORDSUCCESSORLIST_H_

#include <map>

#include <omnetpp.h>

#include <InitStages.h>
#include <NodeHandle.h>

class HChord_U;
class OverlayKey;
class HNotifyResponse;

struct SuccessorListEntry
{
    NodeHandle nodeHandle ;//*< the nodehandle
    bool newEntry;  //*< true, if this entry has just been added
};

std::ostream& operator<<(std::ostream& os, const SuccessorListEntry& e);


class HChordSuccessorList : public cSimpleModule
{
  public:
    virtual int numInitStages() const
    {
        return MAX_STAGE_OVERLAY + 1;
    }
    virtual void initialize(int stage);
    virtual void handleMessage(cMessage* msg);

    virtual void initializeList(uint size, NodeHandle owner,HChord_U* overlay);

    virtual uint getSize();

    virtual void clear();

    virtual bool isEmpty();

    virtual const NodeHandle& getSuccessor(uint pos = 0);

    virtual void addSuccessor(NodeHandle successor, bool resize = true);

    virtual NodeHandle popSuccessor();

    virtual void removeSuccessor(NodeHandle successor);

    virtual void updateList(HNotifyResponse* notify);

    void display ();


  protected:
    NodeHandle thisNode; 
    std::map<OverlayKey, SuccessorListEntry> successorMap;

    uint successorListSize; 

    HChord_U* overlay; 
    int keyLength;

    void removeOldSuccessors();


    void buildSuccessorList();

    void updateDisplayString();
    void updateTooltip();
};

#endif
