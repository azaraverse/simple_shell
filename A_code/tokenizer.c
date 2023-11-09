#include "shell.h"

char **tokenizer(char *line)
{
	char *token, delim[] = " \t\n", *tmp = NULL;
	char **command = NULL;
	int cpt = 0, i = 0;


	if  (!line)
		return(NULL);
	tmp = _strdup(line);

	token = strtok(tmp, delim);
	if (token == NULL)
	{
		free(line), line = NULL;
		free(tmp), tmp = NULL;
		return(NULL);
	}
	
	while (token)
	{
		cpt++;
		token = strtok(NULL, delim);
	}
	free(tmp), tmp = NULL;
	

	command = malloc(sizeof(char *) * (cpt + 1));
	if(!command)
	{
		free(line), line = NULL;
		return(NULL);
	}

	token = strtok(tmp, delim);
	while (token)
	{
		command[i] = _strdup(token);
		token = strtok(NULL, delim);
		i++;
	}
	free(line), line = NULL;
	command[i] = NULL;
	return (command);
}
