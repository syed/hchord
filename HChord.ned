simple HChord_U

    parameters:
        localPort : numeric,             // UDP port for Chord messages
        debugOutput : bool,              // enable debug output
        keyLength : numeric,             // overlay key length in bits
        useCommonAPIforward : bool,      // enable CommonAPI forward() calls
        drawOverlayTopology : bool,      // draw arrow to successor node?
        hopCountMax : numeric,           // maximum number of overlay hops
        recNumRedundantNodes : numeric, // numRedundantNodes for recursive routing
        // only join the overlay on application request
        joinOnApplicationRequest : bool,
        collectPerHopDelay : bool,       // delay statistics for single hops
        routeMsgAcks : bool,             // use RPCs for route messages

        lookupRedundantNodes : numeric,  // number of next hops in each step
        lookupParallelPaths : numeric,   // number of parallel paths
        lookupParallelRpcs : numeric,    // number of nodes to ask in parallel
        // true, if all nodes should be identified with a ping
        lookupSecure : bool, 
        // true, if parallel Rpc results should be merged
        lookupMerge : bool,
        lookupFailedNodeRpcs : bool,     // communicate failed nodes
        lookupStrictParallelRpcs: bool,  // limited the number of concurrent rpcs to parameter parallelRpcs
        lookupUseAllParallelResponses: bool, // merge all parallel responses from earlier steps
        lookupNewRpcOnEveryTimeout: bool, // send a new RPC immediately after an RPC timeouts
        lookupNewRpcOnEveryResponse: bool,  // send a new RPC after every response, even if there was no progress
        lookupFinishOnFirstUnchanged: bool, // finish lookup, if the last pending RPC returned without progress    
        routingType : string, // default routing mode (iterative, semi-recursive,...)         

        // max number of successors in the SuccessorList
        successorListSize : numeric,

        // after joinRetry unsuccessful join requests, we fetch
        // a need bootstrap node from the BootstrapOracle
        joinRetry : numeric,

        // retries before a successor is considered failed
        stabilizeRetry : numeric,

        joinDelay : numeric,           // delay between join retries (sec)
        stabilizeDelay : numeric,      // stabilize interval (sec)
        fixfingersDelay : numeric,     // fix_fingers interval (sec)
        aggressiveJoinMode : bool,     // use modified (faster) JOIN protocol
        extendedFingerTable : bool,    // use the extended finger table?
        // number of fingers when using extended finger table
        numFingerCandidates : numeric,
        //proximityRouting : bool,    // use proximity routing
	StrongPeer : bool,
	migrateDelay:numeric,
	stabilizeSuperPeerDelay : numeric;


        //mergeOptimizationL1 : bool, // enable merge optimization OPL1
        //mergeOptimizationL2 : bool, // activate merge optimization OPL2
        //mergeOptimizationL3 : bool, // activate merge optimization OPL3
        //mergeOptimizationL4 : bool; // activate merge optimization OPL4
        
    gates:
        in: from_udp[]; // gate from the UDP layer
        out: to_udp[];  // gate to the UDP layer
        in: from_app;   // gate from the application
        out: to_app;    // gate to the application
        in: direct_in;  // gate for sendDirect
        in:from_lower;
        out:to_lower;
        
endsimple


simple HChord_L

    parameters:
         successorListSize : numeric,

        // after joinRetry unsuccessful join requests, we fetch
        // a need bootstrap node from the BootstrapOracle
        joinRetry : numeric,

        // retries before a successor is considered failed
        stabilizeRetry : numeric,

        joinDelay : numeric,           // delay between join retries (sec)
        stabilizeDelay : numeric,      // stabilize interval (sec)
        fixfingersDelay : numeric,     // fix_fingers interval (sec)
        aggressiveJoinMode : bool,     // use modified (faster) JOIN protocol
        extendedFingerTable : bool,    // use the extended finger table?
        // number of fingers when using extended finger table
        numFingerCandidates : numeric;
    
    gates:
    
    in: from_upper;
    out: to_upper;
    
    
endsimple


simple HChordSuccessorList
endsimple


simple HChordFingerTable
endsimple    
    
module HChordModules
    gates:
        in: from_udp;   // gate from the UDP layer
        out: to_udp;    // gate to the UDP layer
        in: from_app;   // gate from the application
        out: to_app;    // gate to the application

    submodules:
        hchord_u: HChord_U;
            display: "p=60,60;i=block/circle";

        fingerTable_u: HChordFingerTable;  //finger table topmost overlay
            display: "p=150,60;i=block/table";

        successorList_u: HChordSuccessorList;//suc list upper overlay
            display: "p=240,60;i=block/table";

        hchord_l: HChord_L;
            display: "p=60,120;i=block/circle,gold";

        fingerTable_l: HChordFingerTable;  //finger table topmost overlay
            display: "p=150,120;i=block/table,gold";

        successorList_l: HChordSuccessorList;//suc list upper overlay
            display: "p=240,120;i=block/table,gold";



	connections nocheck:
                from_udp --> hchord_u.from_udp++;
                to_udp <-- hchord_u.to_udp++;
                from_app --> hchord_u.from_app;
                to_app <-- hchord_u.to_app;
		hchord_u.to_lower --> hchord_l.from_upper;
		hchord_u.from_lower <-- hchord_l.to_upper;

endmodule
