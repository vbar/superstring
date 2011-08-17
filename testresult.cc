#include "trace.hh"

#include <exception>
#include <fstream>
#include <iostream>
#include <string>

using std::cin;
using std::exception;
using std::getline;
using std::ifstream;
using std::string;

int main(int argc, char *argv[])
{
    try {
        if (argc != 2) {
	    TRACE1("usage: " << argv[0] << " result-file");
	    return -1;
	}

	ifstream ss(argv[1]);
	string superstring;
	if (getline(ss, superstring)) {
	    string substring;
	    int n = 0;
	    bool ok = true;
	    while (getline(cin, substring)) {
	        if (!substring.empty()) {
		    if (superstring.find(substring) == string::npos) {
			TRACE1(substring << " not in " << superstring);
			ok = false;
		    } else {
		        ++n;
		    }
		}
	    }

	    if (ok) {
	        TRACE1(n << " substrings found");
	    }
	} else {
	    TRACE1("can't read " << argv[1]);
	    return -1;
	}
    } catch (exception& x) {
        TRACE1(x.what());
	return -1;
    }
}
