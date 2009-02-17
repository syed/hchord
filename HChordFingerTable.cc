#include <cfloat>

#include "HChordFingerTable.h"

Define_Module(HChordFingerTable);

void HChordFingerTable::initialize(int stage)
{
    // because of IPAddressResolver, we need to wait until interfaces
    // are registered, address auto-assignment takes place etc.
    if(stage != MIN_STAGE_OVERLAY)
        return;

    WATCH_VECTOR(fingerTable);
}

void HChordFingerTable::handleMessage(cMessage* msg)
{
    error("this module doesn't handle messages, it runs only in initialize()");
}

void HChordFingerTable::initializeTable(uint size, const NodeHandle& owner,BaseOverlay* overlay)
{
   
    fingerTable.assign(size,owner);
    this->overlay = overlay;
}

uint HChordFingerTable::getSize()
{
    return fingerTable.size();
}

void HChordFingerTable::setFinger(uint pos, const NodeHandle& node)
{
    if (pos < fingerTable.size()) {
        fingerTable[pos] = node;
    } else {
        error("Index out of bound (HChordFingerTable, setFinger())");
    }
}

bool HChordFingerTable::updateFinger(uint pos, const NodeHandle& node, double rtt)
{
    if(rtt < 0)
        return false;

	if(fingerTable[pos]==node)
	{
		return false;
	}
	else
	{
    	fingerTable[pos]=node;
	}
	return true;
}

const NodeHandle& HChordFingerTable::getFinger(uint pos)
{
    if (pos >= fingerTable.size())
        error("Index out of bound (HChordFingerTable, getFinger())");

    return fingerTable[pos];
}

/*std::ostream& operator<<(std::ostream& os, const Successors& suc)
{
    for (Successors::const_iterator i = suc.begin(); i != suc.end(); i++) {
        if(i != suc.begin())
            os << endl;
        os << i->second;
        if(i->first == -1)
            continue;
        else if(i->first == DBL_MAX)
            os << "; RTT:  --- ";
        else
            os << "; RTT: " << i->first;
    }

    return os;
}

std::ostream& operator<<(std::ostream& os, const FingerEntry& entry)
{
    if(entry.second.size() > 0)
        os << "[ " << entry.first << " ]\n" << entry.second;
    else
        os << entry.first;

    return os;
}*/
