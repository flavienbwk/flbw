/*
** my_strtolower.c
** 
** Made by Berwick Flavien
** Login   <berwic_f@etna-alternance.net>
** 
** Started on  Jul 27 11:47:14 2018 Berwick Flavien
** Last update Jul 27 11:47:16 2018 Berwick Flavien
*/

#include <unistd.h>
#include <cstdlib>
#include <ctype.h>

int my_strlen(char *str);

char *my_strtolower(char *str)
{
    char *str_m;
    int i;

    i = 0;
    if ((str_m = (char *)std::malloc(sizeof(str_m) * my_strlen(str))))
        while (i < my_strlen(str))
        {
            str_m[i] = tolower(str[i]);
            i++;
        }
    return (str_m);
}
