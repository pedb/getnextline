/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: pde-bakk <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/22 15:02:02 by pde-bakk      #+#    #+#                 */
/*   Updated: 2019/11/22 21:29:20 by pde-bakk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int		ft_newlinecheck(char *str, int k)
{
	int	i;

	i = 0;
	if (k == 0 || k == 1)
		while (str[i])
		{
			if (str[i] == '\n')
				return (i);
			i++;
		}
	if (k == 1)
	{
		while (str[i])
			i++;
		return (i);
	}
	return (-1);
}

char	*ft_bufferfixer(char *buf)
{
	int i;
	int len;

	i = 0;
	len = ft_newlinecheck(buf, 0) + 1;
	while (buf[i] && buf[len + i])
	{
		buf[i] = buf[len + i];
		i++;
	}
	while (buf[i])
	{
		buf[i] = 0;
		i++;
	}
	return (buf);
}

char	*ft_the_finisher(char *str, char *buf, char *line, int ret)
{
	int		i;

	i = 0;
	while (str && str[i])
	{
		if (str[i] == '\n' || str[i] == 0)
			break ;
		i++;
	}
	line = ft_strdup(str, i, 0);
	free(str);
	if (ret == 0 && buf)
		free(buf);
	else
		ft_bufferfixer(buf);
	return (line);
}

int		get_next_line(int fd, char **line)
{
	static char	*buf;
	char		*str;
	int			ret;

	ret = 1;
	str = ft_calloc(0, 0);
	if (buf != NULL && buf[0] != 0)
		ret = ft_strlen(buf);
	while (ret > 0)
	{
		str = ft_strjoiner(str, buf, ret);
		if (ft_newlinecheck(str, 0) > -1)
		{
			*line = ft_the_finisher(str, buf, *line, ret);
			return (1);
		}
		free(buf);
		buf = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
		ret = read(fd, buf, BUFFER_SIZE);
		if (ret == -1)
			return (ret);
	}
	if (ret == 0) //&& ft_strlen(str) > 0)
		*line = ft_the_finisher(str, buf, *line, ret);
	return (0);
}

int	main(void)
{
	char	*line;
	int		fd;
	int		i;


	line = NULL;
	i = 1;
	fd = open("42", O_RDONLY);
	while (i)
	{
		i = get_next_line(fd, &line);
		printf("%d-%s\n", i, line);
		free(line);
	}
	while (1)
	{}
	return (0);
}
