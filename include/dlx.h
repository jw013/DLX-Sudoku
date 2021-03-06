/**
 * @file
 * @author Jimmy Wu
 * @date 2011-12-02
 * @brief DLX stands for Donald Knuth's 
 * <a href="http://en.wikipedia.org/wiki/Dancing_Links">"Dancing Links"</a>
 * algorithm.
 */

#ifndef DLX_H
#define DLX_H

#include <stddef.h>

struct headnode_s;

struct node_s {
    struct node_s     *left;  
    struct node_s     *right;
    struct node_s     *up;
    struct node_s     *down;    
    struct headnode_s *chead;   /**< column header node */
};

/** header node */
struct headnode_s {
    struct node_s base_node;
    size_t        s;    /**< number of nodes in the list, excluding itself  */
    const void    *id;  /**< pointer to unique identifier for the node list */
};

typedef struct node_s       node;
typedef struct headnode_s   hnode;

typedef struct {
    node *row;          /**< row being included in the solution */
    const void *id;     /**< id of column constraint being filled */
    size_t s;           /**< number of other rows in the column at the time */
} dlx_hint;

size_t dlx_exact_cover(node *solution[], hnode *root, size_t k);
size_t dlx_has_covers(hnode *root, size_t k);
size_t dlx_exact_cover_hints(dlx_hint solution[], hnode *root, size_t k);

int dlx_force_row(node *r);
int dlx_unselect_row(node *r);

hnode *dlx_make_headers(hnode *root, hnode *headers, size_t n);
void  dlx_make_row(node *nodes, hnode *headers, int cols[], size_t n);

#endif
