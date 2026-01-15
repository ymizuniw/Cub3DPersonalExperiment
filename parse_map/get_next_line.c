#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define BUFFER_SIZE 6
typedef struct s_data	t_data;
typedef int				(*t_init_fn)(t_data *self, int fd, char **stash);
typedef void			(*t_destroy_fn)(t_data *self);
typedef char			*(*t_release_line_fn)(t_data *self);

typedef struct s_data
{
	int					fd;
	char				**stash;
	char				buf[BUFFER_SIZE + 1];
	ssize_t				br;
	char				*line;
	t_init_fn			init;
	t_destroy_fn		destroy;
	t_release_line_fn	release_line;
}						t_data;

static void	data_destroy(t_data *self)
{
	if (!self)
		return ;
	if (self->line)
	{
		free(self->line);
		self->line = NULL;
	}
	self->fd = -1;
	self->br = 0;
	self->buf[0] = '\0';
}

static int	data_init(t_data *self, int fd, char **stash)
{
	if (!self || !stash || fd < 0)
		return (-1);
	self->fd = fd;
	self->line = NULL;
	self->stash = stash;
	self->br = 0;
	self->buf[0] = '\0';
	return (0);
}

static char	*data_release_line(t_data *self)
{
	char	*out;

	if (!self)
		return (NULL);
	out = self->line;
	self->line = NULL;
	return (out);
}

static int	append_mem(char **dst, char const *src, size_t n)
{
	size_t	old;
	char	*p;

	old = 0;
	if (!dst || !src)
		return (-1);
	if (*dst)
		old = strlen(*dst);
	p = (char *)malloc(old + n + 1);
	if (!p)
		return (-1);
	if (*dst)
		memcpy(p, *dst, old);
	memcpy(p + old, src, n);
	p[old + n] = '\0';
	free(*dst);
	*dst = p;
	return (0);
}

static int	pop_line_from_stash(t_data *d)
{
	char	*nl;
	size_t	len;
	char	*rest;

	if (!d || !d->stash || !*d->stash)
		return (0);
	nl = strchr(*d->stash, '\n');
	if (!nl) // not found
		return (0);
	len = (size_t)(nl - *d->stash);
	if (append_mem(&d->line, *d->stash, len) < 0)
		return (-1);
	rest = strdup(*d->stash + len + 1);
	if (!rest)
		return (-1);
	free(*d->stash);
	*d->stash = rest;
	return (1);
}

static void	handle_fail(t_data *d, char **stash)
{
	if (stash && *stash)
	{
		free(*stash);
		*stash = NULL;
	}
	d->destroy(d);
}

char	*get_next_line(int fd)
{
	static char	*stash = NULL;
	static int	last_fd = -1;
	t_data		d;
	char		*out;
	int			pop_line;
	if (last_fd != -1 && last_fd != fd)
	{
		free(stash);
		stash = NULL;
	}
	last_fd = fd;
	out = NULL;
	d.init = data_init;
	d.destroy = data_destroy;
	d.release_line = data_release_line;
	if (d.init(&d, fd, &stash) < 0)
		return (NULL);
	pop_line = pop_line_from_stash(&d);
	if (pop_line < 0)
	{
		handle_fail(&d, &stash);
		return (out);
	}
	else if (pop_line == 1)
	{
		out = d.release_line(&d);
		d.destroy(&d);
		return (out);
	}
	while (1)
	{
		d.br = read(d.fd, d.buf, BUFFER_SIZE);
		if (d.br < 0)
		{
			handle_fail(&d, &stash);
			return (NULL);
		}
		else if (d.br == 0)
		{
			break ;
		}
		d.buf[d.br] = '\0';
		if (append_mem(d.stash, d.buf, (size_t)d.br) < 0)
		{
			handle_fail(&d, &stash);
			return (NULL);
		}
		pop_line = pop_line_from_stash(&d);
		if (pop_line < 0)
		{
			handle_fail(&d, &stash);
			return (NULL);
		}
		else if (pop_line == 1)
		{
			out = d.release_line(&d);
			break ;
		}
	}
	if (!out && stash && *stash)
	{
		if (append_mem(&d.line, stash, strlen(stash)) < 0)
		{
			handle_fail(&d, &stash);
			return (NULL);
		}
		free(stash);
		stash = NULL;
		out = d.release_line(&d);
	}
	if (stash && *stash == '\0')
	{
		free(stash);
		stash = NULL;
	}
	d.destroy(&d);
	return (out);
}
