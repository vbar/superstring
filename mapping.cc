#include "mapping.hh"

#include <set>
#include <string>
#include <utility>

#include <assert.h>

using std::ostream;
using std::string;

TStringIndex Mapping::get(TStringIndex from) const
{
    TMapping::const_iterator i = mapping.find(from);
    return (i == mapping.end()) ? 0 : i->second;
}

void Mapping::set(TStringIndex from, TStringIndex to)
{
    if (!to) {
        mapping.erase(from);
    } else {
	std::pair<TMapping::iterator, bool> inres = mapping.insert(
	    TMapping::value_type(from, to));
	if (!inres.second) {
	    inres.first->second = to;
	}
    }
}

void Mapping::ensure_no_cycle()
{
    for (Mapping::TMapping::const_iterator i = begin();
	i != end();
	++i) {
        check_from(i->first);
    }
}

void Mapping::check_from(TStringIndex i)
{
    typedef std::set<TStringIndex> TKnown;

    assert(i);
    TKnown known;
    while (i) {
        std::pair<TKnown::iterator, bool> inres = known.insert(i);
	assert(inres.second);
	i = get(i);
    }
}

ostream &operator<<(ostream &os, const Mapping &m)
{
    os << "{\n";
    std::string delim = "\t";
    for (Mapping::TMapping::const_iterator i = m.begin();
	i != m.end();
	++i) {
        os << delim;
	delim = ",\n\t";
	os << i->first << " -> " << i->second;
    }

    os << "\n}";
    return os;
}
