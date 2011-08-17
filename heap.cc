#include "heap.hh"

#include <algorithm>

#include <assert.h>

Heap::Heap(TStringIndex max_size):
    used(0)
{
    assert(max_size);
    heap.reserve(max_size);
}

void Heap::add(HeapPair item)
{
    assert(used <= heap.size());

    if (used == heap.size()) {
        heap.push_back(item);
    } else {
        heap[used] = item;
    }

    if (used++) {
        std::push_heap(heap.begin(), heap.begin() + used);
    }
}

HeapPair Heap::get_max() const
{
    assert(used);
    assert(used <= heap.size());

    return heap[0];
}

void Heap::del_max()
{
    assert(used);
    assert(used <= heap.size());

    if (used > 1) {
        std::pop_heap(heap.begin(), heap.begin() + used);
    }

    --used;
}

void Heap::replace_max(TStringIndex new_key)
{
    assert(used);
    assert(used <= heap.size());

    if (used == 1) {
        heap[0].set_key(new_key);
    } else {
        std::pop_heap(heap.begin(), heap.begin() + used);
	heap[used - 1].set_key(new_key);
        std::push_heap(heap.begin(), heap.begin() + used);
    }
}
