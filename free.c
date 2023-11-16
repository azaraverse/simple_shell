#include "a_shell.h"

/**
 * freesplit - a function that frees a tokenised string
 * @split: double pointer to the tokenised string
 *
 * Return: Void.
 */

void freesplit(char **split)
{
	int i;

	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	/* free(split); */
}

/**
 * freelist - a function that frees a linked list
 * @head: pointer to list head
 */

void freelist(PathNode *head)
{
	PathNode *temp;

	while (head)
	{
		temp = head;
		head = head->next;
		free(temp->directory);
		free(temp);
	}
}
