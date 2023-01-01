#include "main.h"

/**
 * main - command line interface
 *@argc : command line arguments
 *@argv : command line arguments
 * Return: EXIT_SUCCESS, or exit code
 */
int main(int __attribute__((unused)) argc, char __attribute__((unused)) * *argv)
{
	char *line;
	char **args;
	int status;

	do
	{

		printf("hsh>> ");
		line = read_line();
		if (line == NULL)
		{
			printf("\n");
			break;
		}
		args = split_line(line);
		status = execute_command(args);
		free(line);
		free(args);

	} while (status);

	return (EXIT_SUCCESS);
}
