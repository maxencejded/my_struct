#ifndef MS_TREE_H
# define MS_TREE_H

# include <ms_struct.h>

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
t_tree * tree_leef(
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

/*! Tree size
 *
 * @brief Return the size of the tree
 *
 * @param tree
 *     (input) tree
 *
 * @result If successful, size is returned.
 *         Otherwise, a 0 is returned.
*/
size_t tree_size(const t_tree * tree);

/*! Tree depth
 *
 * @brief Return the depth of the tree
 *
 * @param tree
 *     (input) tree
 *
 * @result If successful, depth is returned.
 *         Otherwise, a 0 is returned.
*/
size_t tree_depth(const t_tree * tree);

/*! Tree is between range
 *
 * @brief Verify if the tree is between a range of values
 * 
 * @note Can be use to check if it's a BST by setting the
 *       minimum and the maximum to the range of your time
 *       exemple for `int`:
 *           tree_is_between_range(
 *                 ...
 *               , INT_MIN
 *               , INT_MAX
 *               , ...
 *           )
 *
 * @param tree
 *     (input) tree
 * @param min_val
 *     (input) minimum value of the tree
 * @param max_val
 *     (input) maximum value of the tree
 * @param f_compare
 *     (input) function use to compare two data
 *             @param elem
 *                 (input) elem to compare
 *             @param value
 *                 (input) value to compare
 *
 *             @result If equals, 0 is returned.
 *                     If greater, 1 is returned.
 *                     If smaller, -1 is returned.
 *
 * @result If successful, 0 is returned.
 *         Otherwise, a number is returned.
*/
int tree_is_between_range(
	  const t_tree * tree
	, void * min_val
	, void * max_val
	, int (*f_compare)(void * elem, void * value)
);

/*! Tree insert
 *
 * @brief Insert a node on the tree
 *
 * @param tree
 *     (input) tree
 * @param data
 *     (input) data to insert on the tree
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
int tree_insert(
	  t_tree ** tree
	, void * data
	, size_t size
	, int (*f_compare)(void * elem, void * data)
);

/*! Tree search
 *
 * @brief Find an element on the tree
 *
 * @param tree
 *     (input) tree
 * @param data
 *     (input) data to find on the tree
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
 * @result If successful, the element is returned.
 *         Otherwise, NULL is returned.
*/
void * tree_search(
	  t_tree ** tree
	, void * data
	, int (*f_compare)(void * elem, void * data)
);

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
int tree_pre_order(
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
int tree_in_order(
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
int tree_out_order(
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
int tree_post_order(
	  t_tree ** tree
	, void ** content
	, int (*f_fct)(void * data, void ** content)
);

#endif /* !MS_TREE_H */

/* EOF */