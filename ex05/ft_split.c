#include <stdlib.h>
#include <stdio.h>



int		get_split_count(char *str, char *charset)
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
			if (*str == charset[charset_walk] && str[1] != '\0')
				count++;
			charset_walk++;
		}
		charset_walk = 0;
		str++;
	}
	if (count == 0)
		count++;
	return (count);
}

int		get_next_split(char* str, char* charset)
{
	int		count;
	int		walk_charset;

	count = 0;
	walk_charset = 0;
	while (*str)
	{
		while (charset[walk_charset])
		{
			if (charset[walk_charset] == *str)
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

int		set_next_split(char **str, int count, char **buffer, int *buffer_count)
{
	int pass;

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
	int		split_count;
	int		buffer_count;

	split_count = 0;
	buffer_count = 0;
	printf("get_split_count: %d\n", get_split_count(str, charset));
	buffer = (char**)malloc(sizeof(char) * get_split_count(str, charset));
	if (buffer == NULL)
	{
		printf("Buffer not allocated\n");
		return (NULL);
	}
	while (*str != '\0')
	{
		split_count = get_next_split(str, charset);
		if (split_count == 0)
		{
			str++;
			continue;
		}
		buffer[buffer_count] = (char*)malloc(split_count + 1);
		if (set_next_split(&str, split_count, buffer, &buffer_count) > 0)
			break;
		str++;
	}


	return (buffer);
}

int main()
{
	//char str[] = ",eu gos#to de arr,oz"; //esperado 6
	//char charset[] = " #,";
	//int waiting = 6;

	//char str[] = ",hello,"; //esperado 1
	//char charset[] = ",";
	//int waiting = 1;

	char str[] = "hello word"; //esperado 1
	char charset[] = "";
	int waiting = 1;



	char **buffer = ft_split(str, charset);
	for (int i = 0; i < waiting; i++)
	{
		printf("[%d] %s\n", i, buffer[i]);
		//free(buffer[i]);
	}
	free(*buffer);
}
