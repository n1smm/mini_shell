#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>

int main() {
    // Loop to keep the shell running until the user types "exit"
    while (1) {
        // Display the prompt and read the input
        char *input = readline("minishell> ");
        
        // Check if input is NULL (user pressed Ctrl+D)
        if (input == NULL) {
            printf("\n");
            break;
        }

        // Add the input to the history
        add_history(input);

        // Check if the user wants to exit
        if (strcmp(input, "exit") == 0) {
            free(input);
            break;
        }

        // Print the input back to the user (just for demonstration)
        printf("You entered: %s\n", input);

        // Free the input string allocated by readline
        free(input);
    }

    return 0;
}

