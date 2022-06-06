#ifndef INCLUDE_H
# define INCLUDE_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <math.h>
# include <curl/curl.h>
# include <time.h>
# include <signal.h>
# include "mongoose.h"
# include "mjson.h"
# include "libft.h"
# include "get_next_line.h"

typedef struct s_list_env
{
    struct s_list_env    *next;
    char                *key;
    char                *value;
}    t_list_env;

void 	ft_cli();

#endif