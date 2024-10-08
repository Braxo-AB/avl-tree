/*
 * Copyright (c) 2019 xieqing. https://github.com/xieqing
 * May be freely redistributed, but copyright notice must be retained.
 */

#ifndef _AVL_BF_HEADER
#define _AVL_BF_HEADER

#define AVL_DUP 1
#define AVL_MIN 1

/*
 * node->bf = height(node->right) - height(node->left)
 * balance factors can be kept up-to-date by knowning the previous balance factors and the change in height
 * it is not necesary to know the absolute height
 */

enum avlbf {
	LEFTHEAVY = -1,
	BALANCED = 0,
	RIGHTHEAVY = 1
};

enum avltraversal {
	PREORDER,
	INORDER,
	POSTORDER
};

typedef struct avlnode {
	struct avlnode *left;
	struct avlnode *right;
	struct avlnode *parent;
	char bf;
	void *data;
} avlnode;

typedef	int (*avltree_compare_func_t)(const void *, const void *);
typedef void (*avltree_destroy_func_t)(void *);
typedef int (*avltree_apply_func_t)(void* data, void* cookie);

typedef struct {
	avltree_compare_func_t compare;
	void (*print)(void *);
	avltree_destroy_func_t destroy;

	avlnode root;
	avlnode nil;

	#ifdef AVL_MIN
	avlnode *min;
	#endif
} avltree;

#define AVL_ROOT(avlt) (&(avlt)->root)
#define AVL_NIL(avlt) (&(avlt)->nil)
#define AVL_FIRST(avlt) ((avlt)->root.left)
#define AVL_MINIMAL(avlt) ((avlt)->min)

#define AVL_ISEMPTY(avlt) ((avlt)->root.left == &(avlt)->nil && (avlt)->root.right == &(avlt)->nil)
#define AVL_APPLY(avlt, func, cookie, order) avl_apply((avlt), (avlt)->root.left, (func), (cookie), (order))

avltree *avl_create(avltree_compare_func_t compare_func, avltree_destroy_func_t destroy_func);
void avl_destroy(avltree *avlt);

avlnode *avl_find(avltree *avlt, const void *data);
avlnode *avl_successor(avltree *avlt, avlnode *node);

int avl_apply(avltree *avlt, avlnode *node, avltree_apply_func_t func, void *cookie, enum avltraversal order);
void avl_print(avltree *avlt, void (*print_func)(void *));

avlnode *avl_insert(avltree *avlt, void *data);
void *avl_delete(avltree *avlt, avlnode *node, int keep);

void*
avl_delete_and_continue(
	avltree* avlt,
	avlnode* node,
	int keep,
	avlnode** next_p);

int avl_check_order(avltree *avlt, void *min, void *max);
int avl_check_height(avltree *avlt);

#endif /* _AVL_BF_HEADER */
