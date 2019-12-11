# include <ms_tree/ms_binary.h>

/*----------------------------------- STRUCTURES ------------------------------------*/

struct s_tree
{
	void   * data;
	t_tree * left;
	t_tree * right;
};

/*-------------------------------- CONSTRUCTOR/DESTR --------------------------------*/

t_tree * tree_leef(
	  void * data
	, size_t size
) {
	void   * copy;
	t_tree * tree;

	tree = MS_CAST(t_tree *, MS_ALLOC(sizeof(t_tree)));
	if (MS_ADDRCK(tree)) {
		MS_MEMSET(tree, 0, sizeof(t_tree));
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

void tree_destroy(
	  t_tree ** tree
	, void (*f_free)(void * data)
) {
	if (
		   MS_ADDRCK(tree)
		&& MS_ADDRCK(*tree)
	) {
		tree_destroy(&((*tree)->left), f_free);
		tree_destroy(&((*tree)->right), f_free);
		if (MS_ADDRCK(f_free)) {
			f_free((*tree)->data);
		}
		MS_DEALLOC(*tree);
		*tree = NULL;
	}
}

/*------------------------------------- METHODS -------------------------------------*/

int tree_is_empty(const t_tree * tree)
{
	if (MS_ADDRCK(tree)) {
		if (MS_ADDRCK(tree->data)) {
			return (0);
		}
	}
	return (1);
}

size_t tree_size(const t_tree * tree)
{
	if (MS_ADDRCK(tree)) {
		return (tree_size(tree->left) + 1 + tree_size(tree->right));
	}
	return (0);
}

size_t tree_depth(const t_tree * tree)
{
	size_t depth_left;
	size_t depth_right;

	if (MS_ADDRCK(tree)) {
		depth_left  = tree_depth(tree->left);
		depth_right = tree_depth(tree->right);
		if (depth_left > depth_right) {
			return (depth_left + 1);
		} else {
			return (depth_right + 1);
		}
	}
	return (0);
}

int tree_is_between_range(
	  const t_tree * tree
	, void * min_val
	, void * max_val
	, int (*f_compare)(void * elem, void * value)
) {
	if (MS_ADDRCK(f_compare)) {
		if (MS_ADDRCK(tree)) {
			if (
				   f_compare(tree->data, min_val) < 0
				&& f_compare(tree->data, max_val) > 0
			) {
				return (0);
			}
			return (
				   tree_is_between_range(tree->left, min_val, tree->data, f_compare)
				&& tree_is_between_range(tree->right, tree->data, max_val, f_compare)
			);
		}
		return (1);
	}
	return (-1);
}

int tree_insert(
	  t_tree ** tree
	, void * data
	, size_t size
	, int (*f_compare)(void * elem, void * data)
) {
	int ret;

	ret = 1;
	if (
		   MS_ADDRCK(tree)
		&& MS_ADDRCK(f_compare)
	) {
		if (MS_ADDRCK(*tree)) {
			ret = f_compare((*tree)->data, data);
			if (ret < 0) {
				if (MS_ADDRCK((*tree)->left)) {
					ret = tree_insert(
						  &((*tree)->left)
						, data
						, size
						, f_compare
					);
				} else {
					(*tree)->left = tree_leef(data, size);
					if (MS_ADDRCK((*tree)->left)) {
						return (0);
					}
				}
			} else {
				if (MS_ADDRCK((*tree)->right)) {
					ret = tree_insert(
						  &((*tree)->right)
						, data
						, size
						, f_compare
					);
				} else {
					(*tree)->right = tree_leef(data, size);
					if (MS_ADDRCK((*tree)->right)) {
						return (0);
					}
				}
			}
		} else {
			*tree = tree_leef(data, size);
			if (MS_ADDRCK(*tree)) {
				return (0);
			}
		}
	}
	return (ret);
}

void * tree_search(
	  t_tree ** tree
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
				elem = tree_search(
					  &((*tree)->left)
					, data
					, f_compare
				);
			} else if (ret > 0) {
				elem = tree_search(
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

int tree_pre_order(
	  t_tree ** tree
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
			ret = tree_pre_order(
				  &((*tree)->left)
				, content
				, f_fct
			);
			if (0 == ret) {
				ret = tree_pre_order(
					  &((*tree)->right)
					, content
					, f_fct
				);
			}
		}
	}
	return (0);
}

int tree_in_order(
	  t_tree ** tree
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
		ret = tree_in_order(
			  &((*tree)->left)
			, content
			, f_fct
		);
		if (0 == ret) {
			ret = f_fct((*tree)->data, content);
			if (0 == ret) {
				ret = tree_in_order(
					  &((*tree)->right)
					, content
					, f_fct
				);
			}
		}
	}
	return (ret);
}

int tree_out_order(
	  t_tree ** tree
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
		ret = tree_out_order(
			  &((*tree)->right)
			, content
			, f_fct
		);
		if (0 == ret) {
			ret = f_fct((*tree)->data, content);
			if (0 == ret) {
				ret = tree_out_order(
					  &((*tree)->left)
					, content
					, f_fct
				);
			}
		}
	}
	return (ret);
}

int tree_post_order(
	  t_tree ** tree
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
		ret = tree_post_order(
			  &((*tree)->left)
			, content
			, f_fct
		);
		if (0 == ret) {
			ret = tree_post_order(
				  &((*tree)->right)
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