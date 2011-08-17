#include "ch_debug.hh"
#include "trace.hh"

#include <sys/queue.h>

#define TRACE_chimera 0

struct lst_stree_qi
{
    TAILQ_ENTRY(lst_stree_qi) entries;

    LST_Node *node;
};

static struct lst_stree_qi *lst_debug_qi_new(LST_Node *node)
{
    struct lst_stree_qi *qi;

    qi = static_cast<lst_stree_qi *>(calloc(1, sizeof(struct lst_stree_qi)));
    qi->node = node;

    return qi;
}

void debug_print_tree(LST_STree *tree)
{
  LST_Edge *edge;
  struct lst_stree_qi *qi, *dummy_qi;
  TAILQ_HEAD(tailhead, lst_stree_qi) queue;

  dummy_qi = lst_debug_qi_new(NULL);
  qi = lst_debug_qi_new(tree->root_node);

  TAILQ_INIT(&queue);
  TAILQ_INSERT_HEAD(&queue, qi, entries);
  TAILQ_INSERT_TAIL(&queue, dummy_qi, entries);

  while (queue.tqh_first)
    {
      qi = queue.tqh_first;

      TAILQ_REMOVE(&queue, queue.tqh_first, entries);

      if (qi->node == NULL)
	{
	  if (queue.tqh_first)
	    {
	      dummy_qi = lst_debug_qi_new(NULL);
	      TAILQ_INSERT_TAIL(&queue, dummy_qi, entries);
	    }
	  continue;
	}


      /* Output current node: */
      fprintf(stderr, "[%u (%u)", qi->node->id, qi->node->visitors);
      
      if (qi->node->suffix_link_node)
	fprintf(stderr, " -> %u]\n", qi->node->suffix_link_node->id);
      else
	fprintf(stderr, "]\n");

      /* Now output edge labels and adjacent-node ids: */
      if (!qi->node->kids.lh_first)
	{
	  fprintf(stderr, "\t(leaf)\n");
	}
      else
	{
	  for (edge = qi->node->kids.lh_first; edge; edge = edge->siblings.le_next)
	    {
	      if (edge->dst_node->kids.lh_first)
		{
		  fprintf(stderr, "\t'%s' %u (%s)\n",
			  edge->range.string->sclass->print_func(&edge->range),
			  edge->dst_node->id,
			  lst_string_print(edge->range.string));
		  qi = lst_debug_qi_new(edge->dst_node);
		  TAILQ_INSERT_TAIL(&queue, qi, entries);
		}
	      else
		{
		  fprintf(stderr, "\t'%s' [%i] %u%c%c (%s)\n",
			  edge->range.string->sclass->print_func(&edge->range),
			  edge->dst_node->index,
			  edge->dst_node->id,
			  (edge->range.end_index == &edge->range.end_index_local) ? 'l' : 't',
			  (edge->range.end_index == tree->phase) ? 'c' : ' ',
			  lst_string_print(edge->range.string));
		}
	    }
	}
    }
}

char *debug_print_substring(LST_String *string, u_int start_index,
    u_int end_index, u_int extra_index)
{
  LST_StringIndex tmp_range;

  lst_string_index_init(&tmp_range);

  tmp_range.string = string;
  tmp_range.start_index = start_index;
  *(tmp_range.end_index) = end_index;
  tmp_range.extra_index = extra_index;

  return string->sclass->print_func(&tmp_range);
}
