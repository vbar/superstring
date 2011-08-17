#ifndef ch_debug_hh
#define ch_debug_hh

#include <libstree.h>

void debug_print_tree(LST_STree *tree);

char *debug_print_substring(LST_String *string, u_int start_index,
    u_int end_index, u_int extra_index);

#endif
