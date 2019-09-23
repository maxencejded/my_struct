#ifndef MS_TREE_H
# define MS_TREE_H

# ifndef MS_STRUCT_H
# include <ms_struct.h>
# endif

typedef struct			s_tree
{
	void				*data;
	struct s_tree		*left;
	struct s_tree		*right;
}						t_tree;

/*! Tree node init
 *
 * @brief Create a node for the tree
 *
 * @param data
 *     (input) data to add to the tree
 *
 * @result If successful, the node is returned.
 *         Otherwise, NULL is returned.
*/
static inline
t_tree		*tree_leef(void *data)
{
	t_tree *tree;

	tree = MS_CAST(t_tree *, MS_ALLOC(sizeof(t_tree)));
	if (MS_ADDRK(tree)) {
		MS_MEMSET(tree, 0, sizeof(t_tree));
		tree->data = data;
	}
	return (tree);
}

/*! Tree free
 *
 * @brief Dealloc a tree
 *
 * @param tree
 *     (input) tree to free
 * @param f_free
 *     (input) function to free the data
 *             @param data
 *                 (input) data to free
 *             @result NaN
 *
 * @result NaN.
*/
static inline
void			tree_free(
	  t_tree **tree
	, void (*f_free)(void *data)
) {
	if (
		   MS_ADDRK(tree)
		&& MS_ADDRK(*tree)
	) {
		tree_free(&(*tree)->left, f_free);
		tree_free(&(*tree)->right, f_free);
		if (MS_ADDRK(f_free)) {
			f_free((*tree)->data);
		}
		MS_DEALLOC(*tree);
		*tree = NULL;
	}
}

/*! Tree is empty
 *
 * @brief Check if the tree is empty
 *
 * @param tree
 *     (input) tree
 *
 * @result If successful, 1 is returned.
 *         Otherwise, a 0 is returned.
*/
static inline
int			tree_is_empty(t_tree *tree)
{
	if (MS_ADDRK(tree)) {
		if (MS_ADDRK(tree->data)) {
			return (0);
		}
	}
	return (1);
}

/*! Tree function (pre-order)
 *
 * @brief Apply a function to each leef of tree
 *
 * @param tree
 *     (input) tree
 * @param content
 *     (output) data to retrieve
 * @param f_fct
 *     (input) function to apply on the data
 *             @param data
 *                 (input) data
 *             @param content
 *                 (output) data to retrieve
 *             @result If successful, 0 is returned.
 *                     Otherwise, a number is returned.
 *
 * @result If successful, 0 is returned.
 *         Otherwise, a number is returned.
*/
static inline
int				tree_fct_pre_order(
	  t_tree **tree
	, void **content
	, int (*f_fct)(void *data, void **content)
) {
	int ret;

	if (
		   MS_ADDRK(tree)
		&& MS_ADDRK(f_fct)
		&& MS_ADDRK(*tree)
	) {
		ret = f_fct((*tree)->data, content);
		if (0 != ret)
			return (ret);
		tree_fct_pre_order(&(*tree)->left, content, f_fct);
		tree_fct_pre_order(&(*tree)->right, content, f_fct);
	}
	return (0);
}

/*! Tree function (in-order)
 *
 * @brief Apply a function to each leef of tree
 *
 * @param tree
 *     (input) tree
 * @param content
 *     (output) data to retrieve
 * @param f_fct
 *     (input) function to apply on the data
 *             @param data
 *                 (input) data
 *             @param content
 *                 (output) data to retrieve
 *             @result If successful, 0 is returned.
 *                     Otherwise, a number is returned.
 *
 * @result If successful, 0 is returned.
 *         Otherwise, a number is returned.
*/
static inline
int				tree_fct_in_order(
	  t_tree **tree
	, void **content
	, int (*f_fct)(void *data, void **content)
) {
	int ret;

	if (
		   MS_ADDRK(tree)
		&& MS_ADDRK(f_fct)
		&& MS_ADDRK(*tree)
	) {
		tree_fct_in_order(&(*tree)->left, content, f_fct);
		ret = f_fct((*tree)->data, content);
		if (0 != ret)
			return (ret);
		tree_fct_in_order(&(*tree)->right, content, f_fct);
	}
	return (0);
}

/*! Tree function (out-order)
 *
 * @brief Apply a function to each leef of tree
 *
 * @param tree
 *     (input) tree
 * @param data
 *     (output) data to retrieve
 * @param f_fct
 *     (input) function to apply on the data
 *             @param data
 *                 (input) data
 *             @param content
 *                 (output) data to retrieve
 *             @result If successful, 0 is returned.
 *                     Otherwise, a number is returned.
 *
 * @result If successful, 0 is returned.
 *         Otherwise, a number is returned.
*/
static inline
int				tree_fct_out_order(
	  t_tree **tree
	, void **content
	, int (*f_fct)(void *data, void **content)
) {
	int ret;

	if (
		   MS_ADDRK(tree)
		&& MS_ADDRK(f_fct)
		&& MS_ADDRK(*tree)
	) {
		tree_fct_out_order(&(*tree)->right, content, f_fct);
		ret = f_fct((*tree)->data, content);
		if (0 != ret)
			return (ret);
		tree_fct_out_order(&(*tree)->left, content, f_fct);
	}
	return (0);
}

/*! Tree function (post-order)
 *
 * @brief Apply a function to each leef of tree
 *
 * @param tree
 *     (input) tree
 * @param data
 *     (output) data to retrieve
 * @param f_fct
 *     (input) function to apply on the data
 *             @param data
 *                 (input) data
 *             @param content
 *                 (output) data to retrieve
 *             @result If successful, 0 is returned.
 *                     Otherwise, a number is returned.
 *
 * @result If successful, 0 is returned.
 *         Otherwise, a number is returned.
*/
static inline
int				tree_fct_post_order(
	  t_tree **tree
	, void **content
	, int (*f_fct)(void *data, void **content)
) {
	int ret;

	if (
		   MS_ADDRK(tree)
		&& MS_ADDRK(f_fct)
		&& MS_ADDRK(*tree)
	) {
		tree_fct_post_order(&(*tree)->left, content, f_fct);
		tree_fct_post_order(&(*tree)->right, content, f_fct);
		ret = f_fct((*tree)->data, content);
		if (0 != ret)
			return (ret);
	}
	return (0);
}

/*! Tree push
 *
 * @brief Push a node on the tree
 *
 * @param tree
 *     (input) tree
 * @param data
 *     (input) data to push on the tree
* @param f_compare
 *     (input) function use to compare two data
 *             @param elem
 *                 (input) elem to compare
 *             @param data
 *                 (input) data to compare
 *
 *             @result If equals, 0 is returned.
 *                     If greater, 1 is returned.
 *                     If smaller, -1 is returned.
 *
 * @result If successful, 0 is returned.
 *         Otherwise, a number is returned.
*/
static inline
int				tree_push(
	  t_tree **tree
	, void *data
	, int (*f_compare)(void *elem, void *data)
) {
	int    ret;

	if (
		   MS_ADDRK(tree)
		&& MS_ADDRK(f_compare)
	) {
		if (MS_ADDRK(*tree)) {
			ret = f_compare((*tree)->data, data);
			if (ret < 0) {
				if (MS_ADDRK((*tree)->left)) {
					return (tree_push(&(*tree)->left, data, f_compare));
				} else {
					(*tree)->left = tree_leef(data);
					if (MS_ADDRK((*tree)->left)) {
						return (0);
					}
				}
			} else {
				if (MS_ADDRK((*tree)->right)) {
					return (tree_push(&(*tree)->right, data, f_compare));
				} else {
					(*tree)->right = tree_leef(data);
					if (MS_ADDRK((*tree)->right)) {
						return (0);
					}
				}
			}
		} else {
			*tree = tree_leef(data);
			if (MS_ADDRK(*tree)) {
				return (0);
			}
		}
	}
	return (1);
}

#endif