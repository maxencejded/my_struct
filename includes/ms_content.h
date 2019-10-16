#ifndef MS_CONTENT_H
# define MS_CONTENT_H

# include <ms_struct.h>

/*----------------------------------- STRUCTURES ------------------------------------*/

struct s_content
{
	void             * data;
	struct s_content * next;
};

typedef struct s_content t_content;

/*-------------------------------- CONSTRUCTOR/DESTR --------------------------------*/

/*! Content init
 *
 * @brief Initialize a content
 *
 * @param data
 *     (input) data to add to the structure
 * @param size
 *     (input) size of the content to allocate.
 *             If the size is 0, no copy occurs
 *
 * @result Return a new content.
*/
t_content	*content_init(
	  void * data
	, size_t size
);

#endif /* !MS_CONTENT_H */

/* EOF */