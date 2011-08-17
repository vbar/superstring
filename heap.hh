#ifndef heap_hh
#define heap_hh

#include <vector>

#include "bottom.hh"
#include "heappair.hh"

class Heap
{
private:
    typedef std::vector<HeapPair> THeap;
    THeap heap;
    TStringIndex used;

public:
    Heap(TStringIndex max_size);

    void add(HeapPair item);

    TStringIndex get_size() const;

    // may not be called on empty instance
    HeapPair get_max() const;

    // may not be called on empty instance
    void del_max();

    // may not be called on empty instance
    void replace_max(TStringIndex new_key);
};

inline TStringIndex Heap::get_size() const
{
    return used;
}

#endif
