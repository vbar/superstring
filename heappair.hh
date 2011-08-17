#ifndef heappair_hh
#define heappair_hh

#include "bottom.hh"

class HeapPair
{
private:
    TStringIndex key;
    TStringIndex index;

public:
    HeapPair();
    HeapPair(TStringIndex k, TStringIndex i);
    // copy ctor & assignment op are used

    bool operator<(HeapPair other) const;

    TStringIndex get_key() const;
    TStringIndex get_index() const;

    void set_key(TStringIndex k);
};

inline bool HeapPair::operator<(HeapPair other) const
{
    return key < other.key;
}

inline TStringIndex HeapPair::get_key() const
{
    return key;
}

inline TStringIndex HeapPair::get_index() const
{
    return index;
}
  
#endif
