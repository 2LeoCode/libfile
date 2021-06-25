#include <file.h>

static unsigned int	get_flags(const char *mode)
{
	unsigned int	flags;

	flags = 0;
	while (*mode)
	{
		if (*mode == 'r')
			flags |= O_RDONLY;
		else if (*mode == 'w')
			flags |= O_WRONLY;
		else if (*mode == 't')
			flags |= O_TRUNC;
		else if (*mode == 'a')
			flags |= O_APPEND;
		else
			return (invalid_flag(*mode));
	}
	return (flags);
}

static size_t	get_file_size(const char *path)
{
	int		fd;
	char	buf[BUFFER_SIZE];
	int		ret;
	size_t	size;

	fd = open(path, O_RDONLY);
	if (!fd)
		return (-1);
	ret = 1;
	size = 0;
	while (ret)
	{
		ret = read(fd, buf, BUFFER_SIZE);
		size += (size_t)ret;
	}
	close(fd);
	return (size);
}

size_t	get_line_cnt(const char *path)
{
	size_t	line_cnt;
	char	*line;
	int		fd;
	int		ret;

	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (-1);
	line_cnt = 0;
	ret = 1;
	while (ret)
	{
		ret = get_next_line(fd, &line);
		if (ret == -1)
			return (-1);
		line_cnt++;
		free(line);
	}
	close(fd);
	return (line_cnt);
}

static char	**get_file_content(const char *path, size_t line_cnt,
				size_t capacity)
{
	char	**file_content;
	char	**it;
	char	*line;
	int		ret;

	file_content = malloc(sizeof(char *) * (capacity + 1));
	if (!file_content)
		return (NULL);
	file_content[line_cnt] = NULL;
	it = file_content;
	ret = 1;
	while (ret)
	{
		ret = get_next_line(fd, &line);
		if (ret == -1)
			return (get_file_error(file_content));
		*it++ = line;
	}
	close(fd);
	return (file_content);
}

t_file	*file_open(const char *path, const char *mode)
{
	t_file	*file;

	file = malloc(sizeof(t_file));
	if (!file)
		return (NULL);
	file->line = NULL;
	file->flags = get_flags(mode);
	if (file->flags == UINT_MAX)
		return (file_error(file));
	if ((flags & O_CREAT) == O_CREAT)
		file->fd = open(path, flags, 666);
	else
		file->fd = open(path, flags);
	if (file->fd == -1)
		return (file_error(file));
	file->size = get_file_size(path);
	if (file->size == SIZE_MAX)
		return (file_error(file));
	file->number_of_lines = get_line_cnt(path);
	if (file->number_of_lines == SIZE_MAX)
		return (file_error(file));
	line = get_file_content(path);
	if (!line)
		return (file_error(file));
	return (file);
}
