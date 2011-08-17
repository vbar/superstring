#ifndef greedyalgo_hh
#define greedyalgo_hh

#include "bottom.hh"
#include "heap.hh"
#include "mapping.hh"

class GenSuffTree;

class GreedyAlgo
{
private:
    TStringIndex n;
    Mapping left;
    Mapping right;
    Mapping leftend;
    Mapping rightend;
    Mapping overlap;
    Heap heap;

public:
    GreedyAlgo(TStringIndex n);

    TString compute(GenSuffTree &suffix_tree);

private:
    // not implemented
    GreedyAlgo(const GreedyAlgo &);
    GreedyAlgo &operator=(const GreedyAlgo &);
};

#endif
