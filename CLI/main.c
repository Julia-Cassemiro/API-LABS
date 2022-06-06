#include "../include/cli.h"

t_list_2	*new_box2()
{
	t_list_2	*new;

	new = (t_list_2 *)ft_calloc(1, sizeof(t_list_2));
	if (new == NULL)
		exit(1);
	new->next = NULL;
	new->method = NULL;
	new->uri = NULL;
	return (new);
}

int	ft_cmp (const void *string1, const void *string2)
{
	unsigned char	*s1;
	unsigned char	*s2;
	size_t			i;

	if (!string1 || !string2)
		return (-1);
	s1 = (unsigned char *)string1;
	s2 = (unsigned char *)string2;
	i = 0;
	while (s1[i] || s2[i])
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i++;
	}
	return (0);
}

void	free_split(char ***str)
{
	int	x;

	x = 0;
	if (str[0] != NULL)
	{
		while (str[0][x] != NULL)
		{
			free(str[0][x]);
			str[0][x] = NULL;
			x++;
		}
		free(*str);
		*str = NULL;
	}
}

int	main()
{
	t_list_2 	*name;
	t_list_2 	*temp;
	struct table t;
	int 		file = open("../log.log", O_RDONLY);
	char 		*line;
	int 		value;
	char 		**box;
	int			count;

	name = new_box2();
	value = get_next_line(file, &line);
	temp = name;
	count = 0;
	
	table_init(&t,
				"HTTP Method",  "%s",
				"PATH",   "%s",
				NULL, NULL,
				NULL
		);
	while(value)
	{
		box = ft_split(line, ' ');
		if(count = 0)
		{
			name->method = strdup(box[1]);
			name->uri = strdup(box[2]);
			temp->next = new_box2();
			table_add(&t, name->method, name->uri);
			count++;
		}
		if (ft_cmp(box[0], "Method:") == 0)
		{
			temp->method = strdup(box[1]);
			temp->uri = strdup(box[2]);
			temp->next = new_box2();
			table_add(&t, name->method, name->uri);

		}
		free_split(&box);
		free(line);
		value = get_next_line(file, &line);

	}

	table_print(&t, 60, stdout);
	table_free(&t);

	free(line);
	close(file);
}