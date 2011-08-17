#ifndef gensufftree_hh
#define gensufftree_hh

#include <set>
#include <utility>
#include <vector>

#include <libstree.h>

#include "bottom.hh"

typedef std::pair<TStringIndex, TStringIndex> TLookupResult;

class GenSuffTree
{
private:
    typedef std::vector<LST_String *> TConverter;
    typedef std::set<TStringIndex> TLiveSet;

    TConverter converter;
    LST_STree *tree;
    TLiveSet liveSet;

public:
    GenSuffTree();
    ~GenSuffTree();

    TStringIndex get_size() const;

    TString get(TStringIndex i) const;

    void add(const TString &s);

    // may not be called on tree w/ less than 2 strings
    TLookupResult lookup(TStringIndex i, TStringIndex j);

    void del(TStringIndex i);

    void dump();

private:
    bool is_live(TStringIndex i) const;

    // may not be called on tree w/ less than 2 strings
    TLookupResult backtrack(LST_Node *node, TStringIndex depth,
	TStringIndex exc);

    // may not be called on tree w/ less than 2 strings
    TStringIndex get_other(TStringIndex i) const;

    // not implemented
    GenSuffTree(const GenSuffTree &);
    GenSuffTree &operator=(const GenSuffTree &);
};

inline bool GenSuffTree::is_live(TStringIndex i) const
{
    return liveSet.find(i) != liveSet.end();
}

#endif
