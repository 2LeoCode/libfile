#ifndef FILE_H
# define FILE_H

# include <stdlib.h>
# include <stdint.h>
# include <limits.h>

# define BUFFER_SIZE 64
# include "get_next_line.h"

typedef struct s_file
{
	int				fd;
	char			**line;
	unsigned int	flags;
	size_t			cursor;
	size_t			size;
	size_t			number_of_lines;
	size_t			capacity;
}	t_file;

t_file		*file_open(const char *path);
void		file_close(t_file *file);
const char	*file_get_line(size_t line_index);
int			file_add_line(t_file *file, size_t line_index, char *new_line);
void		file_edit_line(t_file *file, size_t line_index, char *new_line);
int			file_delete_line(t_file *file, size_t line_index);
void		file_append_data(t_file *file);
int			file_seek(int offset);
char		*file_read(size_t size);
char		*file_write(const char *s);

#endif
