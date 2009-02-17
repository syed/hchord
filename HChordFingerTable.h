//
// Copyright (C) 2006 Institut fuer Telematik, Universitaet Karlsruhe (TH)
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
//

/**
 * @file HChordFingerTable.h
 * @author Markus Mauch, Ingmar Baumgart
 */

#ifndef __HCHORDFINGERTABLE_H_
#define __HCHORDFINGERTABLE_H_

#include <vector>
#include <map>

#include <omnetpp.h>

#include <NodeVector.h>
#include <InitStages.h>

class BaseOverlay;


class HChordFingerTable : public cSimpleModule
{
  public:

    virtual int numInitStages() const
    {
        return MAX_STAGE_OVERLAY + 1;
    }

    virtual void initialize(int stage);
    virtual void handleMessage(cMessage* msg);

    virtual void initializeTable(uint size, const NodeHandle& owner,
	BaseOverlay* overlay);
    virtual void setFinger(uint pos, const NodeHandle& node);

    virtual bool updateFinger(uint pos, const NodeHandle& node, double rtt);

    virtual const NodeHandle& getFinger(uint pos);

  //  virtual NodeHandle getFinger(uint pos, const OverlayKey& key);
    virtual uint getSize();

  protected:

    std::vector<NodeHandle> fingerTable; /**< the finger table vector */

    BaseOverlay* overlay; /**< pointer to the main chord module */
    
};

#endif
