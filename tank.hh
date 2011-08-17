#ifndef tank_hh
#define tank_hh

#include <set>
#include <utility>

#include "bottom.hh"

class GenSuffTree;

class Tank
{
private:
    typedef std::pair<TStringIndex, TString> TItem;
    typedef std::set<TItem> TTank;

    TTank tank;

public:
    void add(const TString &s);

    void fill(GenSuffTree &target) const;
};
  
#endif
