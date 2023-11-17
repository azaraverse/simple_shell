#include "a_shell.h"

/**
 * add_PathNode_end - a function that adds a new node at the end of PathNode
 * list
 * @head: pointer to a memory location held by head
 * @dir: str to insert into head
 *
 * Return: head.
 */

PathNode *add_PathNode_end(PathNode *head, char *dir)
{
	PathNode *addNode, *current;

	if (!head)
		return (NULL);

	addNode = malloc(sizeof(PathNode));
	if (!addNode)
	{
		perror("Memory allocation failure");
		exit(EXIT_FAILURE);
	}

	addNode->directory = _strdup(dir);
	addNode->next = NULL;

	if (!head)
		head = addNode;
	else
	{
		current = head;
		while (current->next)
			current = current->next;
		current->next = addNode;
	}
	return (addNode);
}

/**
 * get_PathList - a function that gets the path list of a stated PATH
 * Return: pointer to the path list.
 */

PathNode *get_PathList(void)
{
	PathNode *pathList = NULL;
	char *path, *token;

	path = _getenv("PATH");
	if (path)
	{
		token = strtok(path, ":");
		while (token)
		{
			pathList = add_PathNode_end(pathList, token);
			token = strtok(NULL, ":");
		}
	}
	return (pathList);
}
