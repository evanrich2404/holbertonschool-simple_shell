#include "simple_shell.h"

/**
 * initialize_shell - allocate memory for the simple shell and set inotal values
 * @shell: double pointer back to the simple shell
 * @envp: enviornmental variables passed directly from main
 *
 * Return: Whether or not the shell was sucessfully created.
 */
void initialize_shell(SimpleShell_t **shell, char **envp)
{
	*shell = malloc(sizeof(SimpleShell_t));
	if (shell == NULL)
		return;

	((*shell)->line_num) = 0;
	((*shell)->exit_status) = 0;
	((*shell)->is_active) = TRUE;
	(*shell)->enviornment = envp;
	(*shell)->path_variable = split_input(getenv("PATH"), ":");
	(*shell)->os_command_path = NULL;
	(*shell)->builtin = NULL;
}

/**
 * process_line - parses an individual line taken from a script or the REPL
 * @shell: double pointer back to the simple shell
 * @new_line: the new line to be parsed
 *
 * Description: WILL REQUIRE SIGNIFICANT OVERHALL TO SUPPORT PIPES!!!
*/
void process_line(SimpleShell_t *shell, char *new_line)
{
	shell->command_args = split_input(new_line, " ");

	shell->builtin = find_builtin_command(shell->command_args[0]);

	shell->os_command_path = locate_command_path(shell);

	if (shell->builtin != NULL)
		shell->builtin(shell);
	else if (shell->os_command_path != NULL)
		execute_command_process(shell);
	else
		display_error(shell, 2);

	release_array(shell->command_args);
	free(shell->os_command_path);
}
/**
 * cleanup_shell - deallocates memory for the interpreter and its properties
 * @shell: double pointer back to the simple shell
 */
void cleanup_shell(SimpleShell_t *shell)
{
	release_array(shell->path_variable);

	free(shell);
}

/**
 * release_array - deallocates memory allocated through split_input function
 * @an_array: the array that needs to be deallocated.
*/
void release_array(char **an_array)
{
	int i;

	for (i = 0; an_array[i]; i++)
		free(an_array[i]);

	free(an_array);
}

/**
 * find_builtin_command - runs through and tries to find built-in commands
 * @command: the command we're looking for as a string
 *
 * Return: funciton pointer to back to command to execute
*/
void (*find_builtin_command(char *command))(SimpleShell_t *)
{
	int i;
	BuiltInCommand_t builtins[] = {
		{"exit", exit_interactive_shell},
		{"quit", exit_interactive_shell},
		{"env", display_environment_variables},
		{NULL, NULL}
	};

	for (i = 0; builtins[i].name; i++)
	{
		if (strcmp(command, builtins[i].name) == 0)
			return (builtins[i].exec);
	}
	return (NULL);
}
