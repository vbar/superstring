#include "tank.hh"
#include "gensufftree.hh"

#include <stdexcept>

using std::runtime_error;

void Tank::add(const TString &s)
{
    TStringIndex sz = static_cast<TStringIndex>(s.length());
    if (sz != s.length()) {
        throw runtime_error("string number overflow");
    }

    tank.insert(TItem(sz, s));
}

void Tank::fill(GenSuffTree &target) const
{
    for (TTank::const_reverse_iterator i = tank.rbegin();
        i != tank.rend();
	++i) {
        target.add(i->second);
    }
}
