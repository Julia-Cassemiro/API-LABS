#ifndef CLI_H
# define CLI_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <math.h>
# include <curl/curl.h>
# include <time.h>
# include <signal.h>
# include <fcntl.h>
# include "libft.h"
# include "get_next_line.h"
# include "table.h"

typedef struct s_list_2
{
    struct s_list_2    *next;
	
    char               		 *method;
    char               		 *uri;
	
}    t_list_2;

void    free_split(char ***str);

#endif