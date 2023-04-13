#include "simple_shell.h"

/**
 * exit_interactive_shell - quit interactive mode
 * @shell: double pointer back to shell interpreter
 * Description: PLACEHOLDER
 */
void exit_interactive_shell(SimpleShell_t *shell)
{
	(shell->is_active) = FALSE;
}

/**
 * display_environment_variables - print list of enviornmental variables.
 * @shell: double pointer back to shell interpreter
 * Description: PLACEHOLDER
 */
void display_environment_variables(SimpleShell_t *shell)
{
	int i = 0;

	do {
		printf("%s\n", shell->enviornment[i++]);
	} while (shell->enviornment[i]);
}
