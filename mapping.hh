#ifndef mapping_hh
#define mapping_hh

#include <map>
#include <ostream>

#include "bottom.hh"

class Mapping
{
public:
    typedef std::map<TStringIndex, TStringIndex> TMapping;
    typedef TMapping::const_iterator TConstIter;

private:
    friend std::ostream &operator<<(std::ostream &os, const Mapping &m);

    TMapping mapping;

public:
    // returns 0 when from not mapped
    TStringIndex get(TStringIndex from) const;

    TConstIter begin() const;

    TConstIter end() const;

    void set(TStringIndex from, TStringIndex to);

    void ensure_no_cycle();

private:
    void check_from(TStringIndex from);
};

inline Mapping::TConstIter Mapping::begin() const
{
    return mapping.begin();
}

inline Mapping::TConstIter Mapping::end() const
{
    return mapping.end();
}

std::ostream &operator<<(std::ostream &os, const Mapping &m);

#endif
