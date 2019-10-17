#ifndef MS_RED_BLACK_TREE
# define MS_RED_BLACK_TREE

# include <ms_struct.h>

/*----------------------------------- STRUCTURES ------------------------------------*/

struct s_tree_rb;

/* Type opaque */
typedef struct s_tree_rb t_tree_rb;

/*-------------------------------- CONSTRUCTOR/DESTR --------------------------------*/

/*! Red Black Tree node init
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
t_tree_rb *tree_rb_leef(
	  void * data
	, size_t size
);

/*! Red Black Tree free
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
void tree_rb_free(
	  t_tree_rb ** tree
	, void (*f_free)(void * data)
);

/*------------------------------------- METHODS -------------------------------------*/

/*! Red Black Tree is empty
 *
 * @brief Check if the tree is empty
 *
 * @param tree
 *     (input) tree
 *
 * @result If successful, 1 is returned.
 *         Otherwise, a 0 is returned.
*/
int tree_rb_is_empty(const t_tree_rb * tree);


/*! Red Black Tree insert
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
int tree_rb_insert(
	  t_tree_rb ** tree
	, void * data
	, size_t size
	, int (*f_compare)(void * elem, void * data)
);

/*! Red Black Tree search
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
void * tree_rb_search(
	  t_tree_rb ** tree
	, void * data
	, int (*f_compare)(void * elem, void * data)
);

/*! Red Black Tree function (pre-order)
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
int tree_rb_pre_order(
	  t_tree_rb ** tree
	, void ** content
	, int (*f_fct)(void * data, void ** content)
);

/*! Red Black Tree function (in-order)
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
int tree_rb_in_order(
	  t_tree_rb ** tree
	, void ** content
	, int (*f_fct)(void * data, void ** content)
);

/*! Red Black Tree function (out-order)
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
int tree_rb_out_order(
	  t_tree_rb ** tree
	, void ** content
	, int (*f_fct)(void * data, void ** content)
);

/*! Red Black Tree function (post-order)
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
int tree_rb_post_order(
	  t_tree_rb ** tree
	, void ** content
	, int (*f_fct)(void * data, void ** content)
);

#endif /* !MS_RED_BLACK_TREE */

/* EOF */