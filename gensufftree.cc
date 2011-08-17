#include "gensufftree.hh"
#include "ch_debug.hh"
#include "trace.hh"

#include <stdexcept>

#include <assert.h>

#define TRACE_backtrack 1
#define TRACE_debug 1
#define TRACE_find 0
#define TRACE_lookup 1

using std::runtime_error;

static LST_Edge *node_find_edge(LST_Node *node, LST_String *string,
    u_int index)
{
    assert(node);
    assert(string);

    for (LST_Edge *edge = node->kids.lh_first;
	edge;
	edge = edge->siblings.le_next) {
        TRACE2(find, "checking " << string->sclass->print_func(&(edge->range)));
        if (lst_string_eq(edge->range.string, edge->range.start_index,
                string, index)) {
	    TRACE2(find, "found match");
	    return edge;
	}
    }

    return 0;
}

GenSuffTree::GenSuffTree()
{
    tree = lst_stree_new(0);

    // libstree documents this as skipping duplicates when adding a
    // string, but it actually skips all substrings
    lst_stree_allow_duplicates(tree, 0);
}

GenSuffTree::~GenSuffTree()
{
    lst_stree_free(tree);
}

TStringIndex GenSuffTree::get_size() const
{
    TStringIndex sz = static_cast<TStringIndex>(converter.size());
    if (sz != converter.size()) {
        throw runtime_error("string number overflow");
    }

    return sz;
}

TString GenSuffTree::get(TStringIndex i) const
{
    assert(i);
    --i;
    LST_String *string = converter.at(i);
    assert(string);
    char *data = reinterpret_cast<char *>(string->data);
    return TString(data, data + lst_string_get_length(string));
}

void GenSuffTree::add(const TString &s)
{
    // TRACE2(chimera, "enter GenSuffTree::add");
    LST_String *t = lst_string_new(const_cast<char *>(s.data()),
				   1, s.length());

    // this program might use more than one suffix tree (i.e. when
    // testing), but not at the same time
    t->id = converter.size() + 1;
    u_int old_n = tree->num_strings;
    lst_stree_add_string(tree, t);
    if (old_n < tree->num_strings) {
	converter.push_back(t);

        std::pair<TLiveSet::iterator, bool> inres = liveSet.insert(t->id);
	assert(inres.second);	
    } else {
        lst_string_free(t);
    }
}

TLookupResult GenSuffTree::lookup(TStringIndex i, TStringIndex j)
{
    TRACE2(lookup, "enter GenSuffTree::lookup(" << i << ", " << j << ')');
    assert(i);
    assert(j);

    LST_Node *node = tree->root_node;
    assert(node);

    LST_String *string = converter.at(i - 1);
    assert(string);

    u_int items_todo = string->num_items;
    assert(items_todo >= 2);

    u_int items_done = 0;
    while (items_todo > 0) {
        LST_Edge *edge = node_find_edge(node, string, items_done);

	if (!edge) {
	    TRACE2(lookup, "mismatch at node " << node->id << ", at " << debug_print_substring(string, 0, items_done, 0));
	    return backtrack(node, items_done, j);
	}

	u_int common = lst_string_items_common(edge->range.string,
	    edge->range.start_index, string, items_done, items_todo);
	int edge_len = lst_edge_get_length(edge);
	if (common < edge_len) {
	    TRACE2(lookup, "mismatch in edge at " << debug_print_substring(string, 0, items_done + common, 0));
	    return backtrack(node, items_done, j);
	}
      
	TRACE2(lookup, "skipping to node " << node->id);
	node = edge->dst_node;
	assert(node);
	items_done += edge_len;
	items_todo -= edge_len;
    }
  
    return backtrack(node, items_done, j);
}

void GenSuffTree::del(TStringIndex i)
{
    assert(i);
    TRACE2(debug, "enter GenSuffTree::del(" << i << ')');

    liveSet.erase(i);
}

void GenSuffTree::dump()
{
    TStringIndex sz = get_size();
    for (TStringIndex i = 1; i <= sz; ++i) {
        TRACE2(debug, i << ": " << get(i));
    }

    debug_print_tree(tree);
}

TLookupResult GenSuffTree::backtrack(LST_Node *node, TStringIndex depth,
    TStringIndex exc)
{
    assert(node);

    while (true) {
	for (LST_Edge *edge = node->kids.lh_first;
	    edge;
	    edge = edge->siblings.le_next) {
	    LST_StringIndex *rng = &(edge->range);
	    TRACE2(find, "checking " << rng->string->sclass->print_func(rng));
	    if ((rng->start_index == *(rng->end_index)) &&
		lst_node_is_leaf(edge->dst_node) &&
		(rng->string->id != exc) &&
		is_live(rng->string->id)) {
		TRACE2(backtrack, "found [" << depth << ", " << rng->string->id << ']');
		return TLookupResult(depth, rng->string->id);
	    }
	}

	LST_Edge *up_edge = node->up_edge;
	if (!up_edge) {
	    assert(!depth);
	    TStringIndex other = get_other(exc);
	    TRACE2(backtrack, "no match, returning [0, " << other << ']');
	    return TLookupResult(0, other);
	}

	int up_len = lst_edge_get_length(up_edge);
	assert(up_len <= depth);
	depth -= up_len;
	node = up_edge->src_node;
	assert(node);
	TRACE2(backtrack, "up to node " << node->id);
    }
}

TStringIndex GenSuffTree::get_other(TStringIndex i) const
{
    assert(i);
    assert(!liveSet.empty());

    TStringIndex j = *(liveSet.begin());
    if (j == i) {
        j = *(liveSet.rbegin());
	assert(j != i);
    }

    return j;
}
