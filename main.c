#include "simple_shell.h"


/**
 * main - entry pointer for program
 * @argc: number of arguments passed to program.
 * @argv: what arguments there were, if any.
 * @envp: complete list of enviornmental variables.
 *
 * Return: EXIT_SUCCESS (0) or EXIT_FAILURE (1)
 */
int main(
	__attribute__ ((unused)) int argc,
	__attribute__ ((unused)) char *argv[],
	char **envp
)
{
	SimpleShell_t *shell = NULL;
	int exit_status = 0;
	int is_interactive = isatty(STDIN_FILENO);

	initialize_shell(&shell, envp);

	if (is_interactive)
		start_interactive_shell(shell);
	else
		process_input_script(shell);

	cleanup_shell(shell);

	return (exit_status);
}

/**
 * start_interactive_shell - open a READ-EVALUATE-PRINT-LOOP with interpreter
 * @shell: double pointer back to the interpreter
 *
 * Return: void (for now)
 */
void start_interactive_shell(SimpleShell_t *shell)
{
	char *line = NULL;

	while (shell->is_active == TRUE)
	{
		printf("($) ");
		line = get_user_input();
		process_line(shell, line);
		free(line);
		fflush(NULL);
	}
}


/**
 * process_input_script - read a script as piped in from stdin
 * @shell: douple pointer back to the interprert
 *
 * Return: void.
 */
void process_input_script(SimpleShell_t *shell)
{
	char *current_line = NULL;

	do {

		current_line = get_user_input();

		if (current_line != NULL)
			process_line(shell, current_line);
		else
			(shell->is_active) = FALSE;

		free(current_line);
		fflush(NULL);

	} while (shell->is_active == TRUE);
}
