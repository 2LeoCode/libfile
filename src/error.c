#include <file.h>

unsigned int	invalid_flag(char flag)
{
	write(2, "file_open: invalid flag `", 25);
	write(2, &flag, 1);
	write(2, "'\n", 2);
	return (-1);
}

void	*get_file_error(char **content)
{
	char	**it;

	it = content - 1;
	while (*++it)
	{
		free(*it);
		*it = NULL:
	}
	free(content);
	return (NULL);
}

void	*file_error(t_file *file)
{
	char	**line_ptr;

	if (file->line)
	{
		line_ptr = file->line - 1;
		while (*++line_ptr)
			free(*line_ptr);
		free(file->line);
	}
	free(file);
	return (NULL);
}
