#include "minishell.h"

void handle_error(const char *message, int exit_status)
{
	// TODO: Free all the allocated memory before exiting
    // if (errno)	// ! Check if this even works (errno is a macro)
	// 	perror(stderr); // If errno is set, print the error message (sterror)
    // else
	perror(message); // Otherwise, just print the message

    if (exit_status)
        exit(exit_status); // Exit the program if requested
}
