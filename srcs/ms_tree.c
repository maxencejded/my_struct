# include <ms_tree.h>

/*----------------------------------- STRUCTURES ------------------------------------*/

struct s_tree
{
	void   * data;
	t_tree * left;
	t_tree * right;
};

/*-------------------------------- CONSTRUCTOR/DESTR --------------------------------*/

t_tree *tree_leef(
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

void tree_free(
	  t_tree ** tree
	, void (*f_free)(void * data)
) {
	if (
		   MS_ADDRCK(tree)
		&& MS_ADDRCK(*tree)
	) {
		tree_free(&((*tree)->left), f_free);
		tree_free(&((*tree)->right), f_free);
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