#ifndef stringtable_hh
#define stringtable_hh

#include <vector>

#include "bottom.hh"

class StringTable
{
private:
    typedef std::vector<TString> TStringTable;

    TStringTable table;

public:
    StringTable();

    TStringIndex last_idx() const;

    const TString &at(TStringIndex idx) const;

    void add(const TString &s);
};

inline TStringIndex StringTable::last_idx() const
{
    return table.size();
}

#endif
