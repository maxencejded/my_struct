# include <ms_tree_rb.h>

/*----------------------------------- STRUCTURES ------------------------------------*/

struct s_tree_rb
{
	void        * data;
	t_tree_rb   * left;
	t_tree_rb   * right;
	t_tree_rb   * parent;
	enum colors {
		RED, BLACK
	}             color;
};

/*-------------------------------- CONSTRUCTOR/DESTR --------------------------------*/

t_tree_rb * tree_rb_leef(
	  void * data
	, size_t size
) {
	void      * copy;
	t_tree_rb * tree;

	tree = MS_CAST(t_tree_rb *, MS_ALLOC(sizeof(t_tree_rb)));
	if (MS_ADDRCK(tree)) {
		MS_MEMSET(tree, 0, sizeof(t_tree_rb));
		tree->color = RED;
		if (0 == size) {
			tree->data = data;
		} else {
			copy = MS_ALLOC(size);
			if (MS_ADDRCK(copy)) {
				MS_MEMCPY(copy, data, size);
				tree->data = copy;
			} else {
				MS_DEALLOC(tree);
				return (NULL);
			}
		}
	}
	return (tree);
}

void tree_rb_destroy(
	  t_tree_rb ** tree
	, void (*f_free)(void * data)
) {
	if (
		   MS_ADDRCK(tree)
		&& MS_ADDRCK(*tree)
	) {
		tree_rb_destroy(&(*tree)->left, f_free);
		tree_rb_destroy(&(*tree)->right, f_free);
		if (MS_ADDRCK(f_free)) {
			f_free((*tree)->data);
		}
		MS_DEALLOC(*tree);
		*tree = NULL;
	}
}

/*--------------------------------- PRIVATE METHODS ---------------------------------*/

static inline
void __tree_rb_rotate_left(t_tree_rb * leef)
{
	t_tree_rb * nleef;
	t_tree_rb * parent;

	if (MS_ADDRCK(leef)) {
		nleef = leef->right;
		parent = leef->parent;
		if (MS_ADDRCK(nleef)) {
			leef->right = nleef->left;
			nleef->left = leef;
			leef->parent = nleef;
			if (MS_ADDRCK(leef->right)) {
				leef->right->parent = leef;
			}
			if (MS_ADDRCK(parent)) {
				if (parent->left == leef) {
					parent->left = nleef;
				} else if (parent->right == leef) {
					parent->right = nleef;
				}
			}
			nleef->parent = parent;
		}
	}
}

static inline
void __tree_rb_rotate_right(t_tree_rb * leef)
{
	t_tree_rb * nleef;
	t_tree_rb * parent;

	if (MS_ADDRCK(leef)) {
		nleef = leef->left;
		parent = leef->parent;
		if (MS_ADDRCK(nleef)) {
			leef->left = nleef->right;
			nleef->right = leef;
			leef->parent = nleef;
			if (MS_ADDRCK(leef->left)) {
				leef->left->parent = leef;
			}
			if (MS_ADDRCK(parent)) {
				if (parent->left == leef) {
					parent->left = nleef;
				} else if (parent->right == leef) {
					parent->right = nleef;
				}
			}
			nleef->parent = parent;
		}
	}
}

static inline
t_tree_rb * __tree_rb_grandparent(t_tree_rb * leef)
{
	if (
		   MS_ADDRCK(leef)
		&& MS_ADDRCK(leef->parent)
	) {
		return (leef->parent->parent);
	}
	return (NULL);
}

static inline
t_tree_rb * __tree_rb_oncle(t_tree_rb * leef, t_tree_rb * parent)
{
	if (
		   MS_ADDRCK(leef)
		&& MS_ADDRCK(parent)
	) {
		if (leef->parent == parent->right) {
			return (parent->left);
		} else {
			return (parent->right);
		}
	}
	return (NULL);
}

static inline
int __tree_rb_set(t_tree_rb * leef)
{
	t_tree_rb * parent;
	t_tree_rb * oncle;
	t_tree_rb * grandparent;

	parent      = leef->parent;
	grandparent = __tree_rb_grandparent(leef);
	oncle       = __tree_rb_oncle(leef, grandparent);
	if (MS_ADDRNULL(parent)) {
		leef->color = BLACK;
	} else if (BLACK == parent->color) {
		return (0);
	} else if (
		   RED == parent->color
		&& MS_ADDRCK(oncle)
	) {
		oncle->color = BLACK;
		parent->color = BLACK;
		grandparent->color = RED;
		return (__tree_rb_set(grandparent));
	} else {
		if (
			   MS_ADDRCK(parent)
			&& MS_ADDRCK(grandparent)
		) {
			if (
				   parent->right == leef
				&& grandparent->left == parent
			) {
				__tree_rb_rotate_left(leef);
				leef = leef->left;
			} else if (
				   parent->left == leef
				&& grandparent->right == parent
			) {
				__tree_rb_rotate_right(leef);
				leef = leef->right;
			}
			if (MS_ADDRCK(leef)) {
				parent = leef->parent;
			}
			grandparent = __tree_rb_grandparent(leef);
			if (
				   MS_ADDRCK(parent)
				&& MS_ADDRCK(grandparent)
			) {
				if (parent->left == leef) {
					__tree_rb_rotate_right(grandparent);
				} else {
					__tree_rb_rotate_left(grandparent);
				}
				parent->color = BLACK;
				grandparent->color = RED;
			}
		}
	}
	return (0);
}

static inline
int __tree_rb_insert_recurse(
	  t_tree_rb * root
	, t_tree_rb * leef
	, int (*f_compare)(void * elem, void * data)
) {
	int ret;

	ret = f_compare(root->data, leef->data);
	if (ret < 0) {
		if (MS_ADDRCK(root->left)) {
			ret = __tree_rb_insert_recurse(
				  root->left
				, leef
				, f_compare
			);
		} else {
			root->left = leef;
			leef->parent = root;
			ret = 0;
		}
	} else {
		if (MS_ADDRCK(root->right)) {
			ret = __tree_rb_insert_recurse(
				  root->right
				, leef
				, f_compare
			);
		} else {
			root->right = leef;
			leef->parent = root;
			ret = 0;
		}
	}
	return (ret);
}

/*------------------------------------- METHODS -------------------------------------*/

int tree_rb_is_empty(const t_tree_rb * tree)
{
	if (MS_ADDRCK(tree)) {
		if (MS_ADDRCK(tree->data)) {
			return (0);
		}
	}
	return (1);
}

size_t tree_rb_size(const t_tree_rb * tree)
{
	if (MS_ADDRCK(tree)) {
		return (tree_rb_size(tree->left) + 1 + tree_rb_size(tree->right));
	}
	return (0);
}

size_t tree_rb_depth(const t_tree_rb * tree)
{
	size_t depth_left;
	size_t depth_right;

	if (MS_ADDRCK(tree)) {
		depth_left  = tree_rb_depth(tree->left);
		depth_right = tree_rb_depth(tree->right);
		if (depth_left > depth_right) {
			return (depth_left + 1);
		} else {
			return (depth_right + 1);
		}
	}
	return (0);
}

int tree_rb_insert(
	  t_tree_rb ** tree
	, void * data
	, size_t size
	, int (*f_compare)(void * elem, void * data)
) {
	int         ret;
	t_tree_rb * leef;

	ret = 1;
	if (
		   MS_ADDRCK(tree)
		&& MS_ADDRCK(data)
		&& MS_ADDRCK(f_compare)
	) {
		leef = tree_rb_leef(data, size);
		if (MS_ADDRCK(leef)) {
			if (MS_ADDRCK(*tree)) {
				ret = __tree_rb_insert_recurse(
					  *tree
					, leef
					, f_compare
				);
				if (0 == ret) {
					ret = __tree_rb_set(leef);
					if (0 == ret) {
						*tree = leef;
						while (MS_ADDRCK((*tree)->parent)) {
							*tree = (*tree)->parent;
						}
					}
				}
			} else {
				*tree = leef;
				(*tree)->color = BLACK;
				ret = 0;
			}
		}
	}
	return (ret);
}

void * tree_rb_search(
	  t_tree_rb ** tree
	, void * data
	, int (*f_compare)(void * elem, void * data)
) {
	int    ret;
	void * elem;

	elem = NULL;
	if (
		   MS_ADDRCK(tree)
		&& MS_ADDRCK(data)
		&& MS_ADDRCK(f_compare)
	) {
		if (MS_ADDRCK(*tree)) {
			ret = f_compare((*tree)->data, data);
			if (ret < 0) {
				elem = tree_rb_search(
					  &((*tree)->left)
					, data
					, f_compare
				);
			} else if (ret > 0) {
				elem = tree_rb_search(
					  &((*tree)->right)
					, data
					, f_compare
				);
			} else {
				elem = (*tree)->data;
			}
		}
	}
	return (elem);
}

int tree_rb_pre_order(
	  t_tree_rb ** tree
	, void ** content
	, int (*f_fct)(void * data, void ** content)
) {
	int ret;

	ret = 0;
	if (
		   MS_ADDRCK(tree)
		&& MS_ADDRCK(f_fct)
		&& MS_ADDRCK(*tree)
	) {
		ret = f_fct((*tree)->data, content);
		if (0 == ret) {
			ret = tree_rb_pre_order(
				  &(*tree)->left
				, content
				, f_fct
			);
			if (0 == ret) {
				ret = tree_rb_pre_order(
			  		  &(*tree)->right
					, content
					, f_fct
				);
			}
		}
	}
	return (ret);
}

int tree_rb_in_order(
	  t_tree_rb ** tree
	, void ** content
	, int (*f_fct)(void * data, void ** content)
) {
	int ret;

	ret = 0;
	if (
		   MS_ADDRCK(tree)
		&& MS_ADDRCK(f_fct)
		&& MS_ADDRCK(*tree)
	) {
		ret = tree_rb_in_order(
			  &(*tree)->left
			, content
			, f_fct
		);
		if (0 == ret) {
			ret = f_fct((*tree)->data, content);
			if (0 == ret) {
				ret = tree_rb_in_order(
					  &(*tree)->right
					, content
					, f_fct
				);
			}
		}
	}
	return (ret);
}

int tree_rb_out_order(
	  t_tree_rb ** tree
	, void ** content
	, int (*f_fct)(void * data, void ** content)
) {
	int ret;

	ret = 0;
	if (
		   MS_ADDRCK(tree)
		&& MS_ADDRCK(f_fct)
		&& MS_ADDRCK(*tree)
	) {
		ret = tree_rb_out_order(
			  &(*tree)->right
			, content
			, f_fct
		);
		if (0 == ret) {
			ret = f_fct((*tree)->data, content);
			if (0 == ret) {
				ret = tree_rb_out_order(
					  &(*tree)->left
					, content
					, f_fct
				);
			}
		}
	}
	return (ret);
}

int tree_rb_post_order(
	  t_tree_rb ** tree
	, void ** content
	, int (*f_fct)(void * data, void ** content)
) {
	int ret;

	ret = 0;
	if (
		   MS_ADDRCK(tree)
		&& MS_ADDRCK(f_fct)
		&& MS_ADDRCK(*tree)
	) {
		ret = tree_rb_post_order(
			  &(*tree)->left
			, content
			, f_fct
		);
		if (0 == ret) {
			ret = tree_rb_post_order(
				  &(*tree)->right
				, content
				, f_fct
			);
			if (0 == ret) {
				ret = f_fct((*tree)->data, content);
			}
		}
	}
	return (ret);
}

/* EOF */