#include "HChordSuccessorList.h"

#include "HChord_U.h"

Define_Module(HChordSuccessorList);

using namespace std;

/*std::ostream& operator<<(std::ostream& os, const SuccessorListEntry& e)
{
    os << e.nodeHandle << " " << e.newEntry;
    return os;
};*/

void HChordSuccessorList::initialize(int stage)
{
    // because of IPAddressResolver, we need to wait until interfaces
    // are registered, address auto-assignment takes place etc.
    if (stage != MIN_STAGE_OVERLAY)
        return;

    WATCH_MAP(successorMap);
}

void HChordSuccessorList::handleMessage(cMessage* msg)
{
    error("this module doesn't handle messages, it runs only in initialize()");
}

void HChordSuccessorList::initializeList(uint size, NodeHandle owner,
					HChord_U *overlay)
{
    successorMap.clear();
    successorListSize = size;
    thisNode = owner;
    keyLength=OverlayKey::getLength();
    this->overlay = overlay;
    addSuccessor(thisNode);
    
}

void HChordSuccessorList::clear()
{
    successorMap.clear();
}


uint HChordSuccessorList::getSize()
{
    return successorMap.size();
}

bool HChordSuccessorList::isEmpty()
{
    if (successorMap.size() == 1 && getSuccessor() == thisNode)
        return true;
    else
        return false;
}

const NodeHandle& HChordSuccessorList::getSuccessor(uint pos)
{
    // check boundaries
    if (pos == 0 && successorMap.size() == 0)
        return NodeHandle::UNSPECIFIED_NODE;

    if (pos >= successorMap.size()) {
        error("Index out of bound (HChordSuccessorList, getSuccessor())");
    }

    std::map<OverlayKey, SuccessorListEntry>::iterator it =
        successorMap.begin();

    for (uint i= 0; i < pos; i++) {
        it++;
        if (i == (pos-1))
            return it->second.nodeHandle;
    }
    return it->second.nodeHandle;
}

void HChordSuccessorList::updateList(HNotifyResponse* notifyResponse)
{
    addSuccessor(notifyResponse->getSrcNode(), false);

    for (uint k = 0; ((k < static_cast<uint>(notifyResponse->getSucNum()))
                     && (k < (successorListSize - 1))); k++) {
        NodeHandle successor = notifyResponse->getSucNode(k);

        // don't add nodes, if this would change our successor
        if (successor.key.isBetweenLR(thisNode.key,notifyResponse->getSrcNode().key))
            continue;

        addSuccessor(successor, false);
    }

    removeOldSuccessors();
}


void HChordSuccessorList::addSuccessor(NodeHandle successor, bool resize)
{
    OverlayKey sum = successor.key - (thisNode.key + OverlayKey::ONE);

    std::map<OverlayKey, SuccessorListEntry>::iterator it =
        successorMap.find(sum);

    // Make a CommonAPI update() upcall to inform application
    // about our new neighbor in the successor list

    if (it == successorMap.end()) {
      //  overlay->callUpdate(successor, true);
    } else {
        successorMap.erase(it);
    }

    SuccessorListEntry entry;
    entry.nodeHandle = successor;
    entry.newEntry = true;

    successorMap.insert(make_pair(sum, entry));

    if ((resize == true) && (successorMap.size() > (uint)successorListSize)) {
        it = successorMap.end();
        it--;
       // overlay->callUpdate(it->second.nodeHandle, false);
        successorMap.erase(it);
    }
}

// todo: how to deal with references
NodeHandle HChordSuccessorList::popSuccessor()
{
    OverlayKey succKey = successorMap.begin()->first;
    NodeHandle succNode = successorMap.begin()->second.nodeHandle;
    successorMap.erase(successorMap.find(succKey));

    //overlay->callUpdate(succNode, false);

    // ensure that thisNode is always in the successor list
    if (getSize() == 0) {
        addSuccessor(thisNode);
        succNode = thisNode;
    }

    return succNode;
}

void HChordSuccessorList::removeSuccessor(NodeHandle successor)
{
    OverlayKey tmp = successor.key - (thisNode.key + OverlayKey::ONE);
    std::map<OverlayKey, SuccessorListEntry>::iterator iter =
        successorMap.find(tmp);
    if (iter != successorMap.end()) {
        if (iter->second.nodeHandle != successor)
            cout << "wrong mapping" << endl;
        successorMap.erase(iter);
        //overlay->callUpdate(successor, false);
    }

    // ensure that thisNode is always in the successor list
    if (getSize() == 0)
        addSuccessor(thisNode);
}

void HChordSuccessorList::removeOldSuccessors()
{
    std::map<OverlayKey,SuccessorListEntry>::iterator it;

    for (it = successorMap.begin(); it != successorMap.end();) {

        if (it->second.newEntry == false) {
            //overlay->callUpdate(it->second.nodeHandle, false);
            successorMap.erase(it++);
        } else {
            it->second.newEntry = false;
            it++;
        }
    }

    it = successorMap.end();
    it--;

    while (successorMap.size() > successorListSize) {
        successorMap.erase(it--);
    }

    if (getSize() == 0)
        addSuccessor(thisNode);
}


void HChordSuccessorList::updateDisplayString()
{
    // FIXME: doesn't work without tcl/tk
    //    	if (ev.isGUI()) {
    if (1) {
        char buf[80];

        if (successorMap.size() == 1) {
            sprintf(buf, "1 successor");
        } else {
            sprintf(buf, "%zi successors", successorMap.size());
        }

        displayString().setTagArg("t", 0, buf);
        displayString().setTagArg("t", 2, "blue");
    }

}

void HChordSuccessorList::updateTooltip()
{
    if (ev.isGUI()) {
        std::stringstream str;
        for (uint i = 0; i < successorMap.size(); i++)	{
            str << getSuccessor(i);
            if ( i != successorMap.size() - 1 )
                str << endl;
        }


        char buf[1024];
        sprintf(buf, "%s", str.str().c_str());
        displayString().setTagArg("tt", 0, buf);
    }
}

void HChordSuccessorList::display()
{
    cout << "Content of HChordSuccessorList:" << endl;
    for (std::map<OverlayKey,SuccessorListEntry>::iterator it =
        successorMap.begin(); it != successorMap.end(); it++)
        cout << it->first << " with Node: " << it->second.nodeHandle << endl;
}
