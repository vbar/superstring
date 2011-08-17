#include "stringtable.hh"

#include <limits>
#include <stdexcept>

#include <assert.h>

using std::runtime_error;

StringTable::StringTable()
{
}

const TString &StringTable::at(TStringIndex idx) const
{
    assert(idx);
    return table.at(idx - 1);
}

void StringTable::add(const TString &s)
{
    table.push_back(s);
    
    if (table.size() >= std::numeric_limits<TStringIndex>::max()) {
        throw runtime_error("too many strings");
    }
}
