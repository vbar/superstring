#include "greedyalgo.hh"
#include "gensufftree.hh"
#include "heappair.hh"
#include "output.hh"
#include "trace.hh"

#include <assert.h>

#define TRACE_debug 0

GreedyAlgo::GreedyAlgo(TStringIndex n):
    n(n),
    heap(n)
{
    assert(n > 1);
}

TString GreedyAlgo::compute(GenSuffTree &suffix_tree)
{
    for (TStringIndex i = 1; i <= n; ++i) {
	leftend.set(i, i);
	rightend.set(i, i);

	TLookupResult r = suffix_tree.lookup(i, i);
	heap.add(HeapPair(r.first, i));
    }

    while (heap.get_size() > 1) {
	TRACE2(debug, "heap size = " << heap.get_size());
	HeapPair p = heap.get_max();
	TStringIndex i = p.get_index();
	TLookupResult r = suffix_tree.lookup(i, rightend.get(i));	
	if (r.first == p.get_key()) {
	    TStringIndex j = r.second;
	    TRACE2(debug, "chaining " << j << " -> " << i);
	    left.set(i, j);
	    TRACE2(debug, "left = " << left);
	    // left.ensure_no_cycle();
	    right.set(j, i);
	    TRACE2(debug, "right = " << right);
	    overlap.set(i, r.first);
	    leftend.set(rightend.get(i), leftend.get(j));
	    TRACE2(debug, "leftend = " << leftend);
	    rightend.set(leftend.get(j),
			 rightend.get(i)); // pseudocode has "j"
	    TRACE2(debug, "rightend = " << rightend);
	    suffix_tree.del(j);
	    heap.del_max();
	} else if (r.first < p.get_key()) {
	    heap.replace_max(r.first);
	}
    }

    TStringIndex p = 1;
    TStringIndex q = left.get(p);
    assert(q != p);
    while (q) {
        p = q;
	q = left.get(p);
	assert(q != p);
    }

    Output output;
    for (TStringIndex i = p; i;	i = right.get(i)) {
	output.add(suffix_tree.get(i), overlap.get(i));
    }

    return output.get();
}
