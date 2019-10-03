#ifndef MS_TREE_H
# define MS_TREE_H

# ifndef MS_STRUCT_H
# include <ms_struct.h>
# endif /* !MS_STRUCT_H */

/*----------------------------------- STRUCTURES ------------------------------------*/

struct s_tree;

/* Type opaque */
typedef struct s_tree t_tree;

/*-------------------------------- CONSTRUCTOR/DESTR --------------------------------*/

/*! Tree node init
 *
 * @brief Create a node for the tree
 *
 * @param data
 *     (input) data to add to the tree
 * @param size
 *     (input) size of the content to allocate.
 *             If the size is 0, no copy occurs
 *
 * @result If successful, the node is returned.
 *         Otherwise, NULL is returned.
*/
t_tree *tree_leef(
	  void * data
	, size_t size
);

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
void tree_free(
	  t_tree ** tree
	, void (*f_free)(void * data)
);

/*------------------------------------- METHODS -------------------------------------*/

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
int tree_is_empty(const t_tree * tree);

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
int tree_fct_pre_order(
	  t_tree ** tree
	, void ** content
	, int (*f_fct)(void * data, void ** content)
);

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
int tree_fct_in_order(
	  t_tree ** tree
	, void ** content
	, int (*f_fct)(void * data, void ** content)
);

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
int tree_fct_out_order(
	  t_tree ** tree
	, void ** content
	, int (*f_fct)(void * data, void ** content)
);

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
int tree_fct_post_order(
	  t_tree ** tree
	, void ** content
	, int (*f_fct)(void * data, void ** content)
);

/*! Tree push
 *
 * @brief Push a node on the tree
 *
 * @param tree
 *     (input) tree
 * @param data
 *     (input) data to push on the tree
 * @param size
 *     (input) size of the content to allocate.
 *             If the size is 0, no copy occurs
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
int tree_push(
	  t_tree ** tree
	, void * data
	, size_t size
	, int (*f_compare)(void * elem, void * data)
);

#endif /* !MS_TREE_H */

/* EOF */