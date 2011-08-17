#include "testsuite.hh"
#include "bottom.hh"
#include "gensufftree.hh"
#include "greedyalgo.hh"
#include "trace.hh"

#include <sstream>
#include <stdexcept>

#include <assert.h>

using std::stringstream;
using std::runtime_error;

struct Test
{
    const char **inset;
    const char *outss;
};

static void test(size_t testno, Test *t)
{
    assert(t && t->inset && t->outss);

    GenSuffTree suffix_tree;
    const char **p = t->inset;
    while (*p) {
        suffix_tree.add(TString(*p));
	++p;
    }

    suffix_tree.dump();

    GreedyAlgo algo(p - t->inset);
    TString res = algo.compute(suffix_tree);
    if (res != t->outss) {
        stringstream ss;
	ss << "test " << testno << ": expected " << t->outss
	   << ", got " << res;
	throw runtime_error(ss.str());
    }
}

void test_greedy_algo()
{
    const char *t0[] = { "a", "b", 0 };
    const char *t1[] = { "bc", "ab", 0 };
    const char *t2[] = { "a", "b", "c", 0 };
    const char *t3[] = { "ab", "bc", "ac", 0 };
    const char *t4[] = { "bc", "ac", "ab", 0 };
    const char *t5[] = { "abaa", "aaba", 0 };
    const char *t6[] = { "aab", "bcc", "abc", 0 };
    const char *t7[] = { "aab", "abc", "bcc", 0 };
    const char *t7p[] = { "aabc", "abbc", "abcc", "d", 0 };
    const char *t8[] = { "00", "01", "10", "11", 0 };
    const char *t9[] = { "23", "42", "12", "34", 0 };
    const char *t10[] = { "abcd", "bcde", "deab", 0 };
    const char *t11[] = { "abc", "acb", "bac", "bca", "cab", "cba", 0 };
    const char *t12[] = { "egiach", "bfgiak", "hfdegi", "iakhfd", "fgiakh", 0 };
    const char *t13[] = { "abcbcbcbcb", "cbcbcbcbc", "bcbcbcbcbd", 0 };

    Test test_suite[] = {
        { t0, "ba" }, 
	{ t1, "abc" },
	{ t2, "cab" },
	{ t3, "acabc" },
	{ t4, "abcac" },
	{ t5, "aabaa" },
	{ t6, "aabcc" },
	{ t7, "aabcc" },
	{ t7p, "daabccabbc" },
	{ t8, "11001" },
	{ t9, "12342" },
	{ t10, "deabcde" },
	{ t11, "bcabcacbac" },
	{ t12, "bfgiakhfdegiach" },
	{ t13, "cbcbcbcbcabcbcbcbcbd" } // sub-optimal
    };
    for (size_t i = 0; i < sizeof(test_suite) / sizeof(test_suite[0]); ++i) {
        test(i, test_suite + i);
    }

    TRACE1("passed " << (sizeof(test_suite) / sizeof(test_suite[0])) << " test(s)");
}

