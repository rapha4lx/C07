#include <stdlib.h>
#include <stdio.h>

int	get_split_count(char *str, char *charset)
{
	int		count;
	int		charset_walk;
	
	count = 0;
	charset_walk = 0;
	if (*charset == '\0')
		return (1);
	while (*str)
	{
		while (charset[charset_walk])
		{
			if (*str == charset[charset_walk] )
				count++;
			charset_walk++;
		}
		charset_walk = 0;
		str++;
	}
	return (count);
}

int	get_next_split(char* str, char* charset)
{
	int		count;
	int		walk_charset;

	count = 0;
	walk_charset = 0;
	while (*str)
	{
		while (charset[walk_charset])
		{
			if (charset[walk_charset] == *str && count > 0)
			{
				return (count);
			}
			walk_charset++;
		}
		count++;
		walk_charset = 0;
		str++;
	}
	return (count);
}

int	set_next_split(char **str, int count, char **buffer, int *buffer_count)
{
	int	pass;

	pass = 0;
	while (count > pass)
	{
		buffer[*buffer_count][pass] = **str;
		(*str)++;
		pass++;
	}
	buffer[*buffer_count][pass] = '\0';
	*buffer_count = *buffer_count + 1;
	if (**str == '\0')
		return (1);
	return (0);
}

char	**ft_split(char* str, char* charset)
{
	char** buffer;
	int	split_count;
	int	buffer_count;

	split_count = 0;
	buffer_count = 0;
	//printf("get_split_count: %d\n", get_split_count(str, charset));
	buffer = (char**)malloc(sizeof(char*) * get_split_count(str, charset));
	if (buffer == NULL)
	{
		printf("Buffer not allocated\n");
		return (NULL);
	}
	while (*str != '\0')
	{
		split_count = get_next_split(str, charset);
		buffer[buffer_count] = (char*)malloc(split_count + 1);
		if (set_next_split(&str, split_count, buffer, &buffer_count) > 1)
			break;
		str++;
	}

	//for (int i = 0; i < buffer_count; i++)
	//	printf("[%d] %s\n", i, buffer[i]);
	return (buffer);
}
