#include "heappair.hh"

HeapPair::HeapPair():
    key(0),
    index(0)
{
}

HeapPair::HeapPair(TStringIndex k, TStringIndex i):
    key(k),
    index(i)
{
}

void HeapPair::set_key(TStringIndex k)
{
    key = k;
}
