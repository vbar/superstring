#include "bottom.hh"
#include "gensufftree.hh"
#include "greedyalgo.hh"
#include "tank.hh"
#include "testsuite.hh"
#include "trace.hh"

#include <exception>
#include <iomanip>
#include <iostream>
#include <set>
#include <string>

#include <string.h>

using std::cin;
using std::cout;
using std::endl;
using std::exception;
using std::getline;
using std::string;

void fill_suffix_tree(GenSuffTree &suffix_tree)
{
    Tank tank;
    string qw;
    while (getline(cin, qw)) {
        if (!qw.empty()) {
	    tank.add(qw);
	}
    }

    tank.fill(suffix_tree);
}

int main(int argc, char *argv[])
{
    try {
        if ((argc == 2) && !strcmp(argv[1], "-t")) {
	    test_greedy_algo();
	    return 0;
	} else {
	    GenSuffTree suffix_tree;
	    fill_suffix_tree(suffix_tree);
	    // suffix_tree.dump();

	    TStringIndex n = suffix_tree.get_size();
	    if (!n) {
		TRACE1("no input");
		return 0;
	    } else if (n == 1) {
		cout << suffix_tree.get(1) << endl;
		return 0;
	    }

	    GreedyAlgo algo(n);
	    cout << algo.compute(suffix_tree) << endl;

	    return 0;
	}
    } catch (exception& x) {
        TRACE1(x.what());
	return -1;
    }
}
