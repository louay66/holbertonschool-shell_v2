#include "main.h"

#define TOKEN_BUFFER_SIZE 64
#define TOKEN_DELIMITERS " \t\r\n\a"

/**
 * read_line - read_line from user
 * Return: line or NUll in case of error
 */
char *read_line(void)
{
	char *line = NULL;
	size_t buffer_size = 0;
	int line_len = 0;

	line_len = getline(&line, &buffer_size, stdin);
	if (line_len == EOF)
	{
		return (NULL);
	}
	else
	{
		return (line);
	}
}
/**
 * split_line - split line
 * @line : line to split
 * Return: pointer of the split line
 */
char **split_line(char *line)
{
	int buffer_size = TOKEN_BUFFER_SIZE;
	int position = 0;
	char **tokens = malloc(buffer_size * sizeof(char *));
	char *token;

	if (!tokens)
	{
		fprintf(stderr, "hsh: allocation error\n");
		exit(EXIT_FAILURE);
	}

	token = strtok(line, TOKEN_DELIMITERS);
	while (token != NULL)
	{
		tokens[position] = token;
		position++;

		if (position >= buffer_size)
		{
			buffer_size += TOKEN_BUFFER_SIZE;
			tokens = my_realloc(tokens, buffer_size * sizeof(char *));
			if (!tokens)
			{
				fprintf(stderr, "hsh: allocation error\n");
				exit(EXIT_FAILURE);
			}
		}

		token = strtok(NULL, TOKEN_DELIMITERS);
	}
	tokens[position] = NULL;
	return (tokens);
}
/**
 * execute_builtin_command - run the command specified like cd and env and exit
 * @args : command arguments
 * Return: 1 to complete desply prompt or 0 to stop execution
 */
int execute_builtin_command(char **args)
{

	if (_strcmp(args[0], "exit") == 0)
	{
		return (0);
	}

	else if (_strcmp(args[0], "env") == 0)
	{
		int i = 0;

		while (environ[i])
		{
			printf("%s\n", environ[i]);
			i++;
		}
		return (1);
	}
	else
	{
		return (-1);
	}
}
/**
 * execute - execute a command
 * @args : command arguments
 * Return: 1 to complete desply prompt
 */
int execute(char **args)
{
	pid_t pid, __attribute__((__unused__)) wpid;
	int status;

	pid = fork();
	if (pid == 0)
	{
		/* Child process */
		if (execve(args[0], args, NULL) == -1)
		{
			fprintf(stderr, "%s: command not found\n", args[0]);
		}
		exit(EXIT_FAILURE);
	}
	else if (pid < 0)
	{
		/* Error forking */
		perror("hsh");
	}
	else
	{
		/* Parent process */
		do
		{
			wpid = waitpid(pid, &status, WUNTRACED);
		} while (!WIFEXITED(status) && !WIFSIGNALED(status));
	}

	return (1);
}

/**
 * execute_command - check if command is built in or not and execute it
 * @args : command arguments
 * Return: 1 to complete desply prompt or 0 to stop execution
 */
int execute_command(char **args)
{
	if (args[0] == NULL)
	{
		/* Empty command */
		return (1);
	}
	else if (_strcmp(args[0], "cd") == 0)
	{
		if (args[1] == NULL)
		{
			fprintf(stderr, "hsh: expected argument to \"cd\"\n");
		}
		else
		{
			if (chdir(args[1]) != 0)
			{
				perror("hsh process");
			}
		}
		return (1);
	}
	if (execute_builtin_command(args) == 0)
	{
		return (0);
	}
	else if (execute_builtin_command(args) == 1)
	{
		return (1);
	}
	else
	{
		return (execute(args));
	}
}
