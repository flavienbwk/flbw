/*
** my_strlen.c
** 
** Made by Berwick Flavien
** Login   <berwic_f@etna-alternance.net>
** 
** Started on  Jul 27 11:47:14 2018 Berwick Flavien
** Last update Jul 27 11:47:16 2018 Berwick Flavien
*/

void        my_putchar(char c);

int         my_strlen(char *str)
{
	int i;

	i = 0;
	while (str[i] != '\0')
	{
		i++;
	}
	return (i);
}