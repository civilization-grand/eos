
#include "stdio/stdio.h"
#include "string/string.h"
#include "vga/vga.h"

extern int cp;
int shell_cursor = 0;

char message1[INPUT_BUFFER_MAX_SIZE] = "He chose the rejoice of being imbued, it is the will to calamity,\noblivion is his auguries. His fetid realm is misanthropy.\nPay heed, don't relinquish cosmos...\n";

void display_prompt()
{
    char *prompt_msg = "user-prompt>>";
    fb_write(prompt_msg, strlen(prompt_msg), 0, BLUE);
}

int shell_main()
{
    char command[INPUT_BUFFER_MAX_SIZE];
    char prompt_string[INPUT_BUFFER_MAX_SIZE];
    while (1)
    {
        print("\n");

        display_prompt();
        shell_cursor = cp;

        read_string(prompt_string);

        strcpy(command, first_token(prompt_string));
        //------------------------------------------------------------------------------------
        if (strcmp("m1\n", prompt_string))
        {
            print(message1);
        }
        //------------------------------------------------------------------------------------
        else if (strcmp("print", command))
        {
            for (int i = (strlen(command) + 1); i < strlen(prompt_string); i++)
            {
                write_char(prompt_string[i], 0, LIGHT_GRAY);
            }
        }
        //------------------------------------------------------------------------------------
        else if (strcmp("help\n", prompt_string))
        {
            print("Command -arg-| Describtion\n");
            print("-----------------------------------------------------\n");
            print("m1           : A message that the OS wants to provide.\n");
            print("print -txt-  : To print a string.\n");
            print("-----------------------------------------------------\n");
        }
        //------------------------------------------------------------------------------------
        else
        {
            /*Do nothin*/
        }
    }

    return 0;
}