#ifndef trace_hh
#define trace_hh

#include <iostream>
#include <iomanip>

#ifndef NOTRACE

#define TRACE1(trace_msg) std::cerr << trace_msg << std::endl

#define TRACE2(trace_fac, trace_msg) do { \
        if (TRACE_##trace_fac) { \
	    std::cerr << trace_msg << std::endl; \
	} \
    } while(false)

#else

#define TRACE1(trace_msg)

#define TRACE2(trace_fac, trace_msg)

#endif

#endif
