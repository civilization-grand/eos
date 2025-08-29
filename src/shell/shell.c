
#include "stdio/stdio.h"
#include "string/string.h"
#include "vga/vga.h"

extern int cp;
int shell_cursor = 0;

char message1[INPUT_BUFFER_MAX_SIZE] = "He chose the rejoice of being imbued, it is the will to calamity,\noblivion is his auguries. His fetid realm is misanthropy.\nPay heed, don't relinquish cosmos...\n"; // It's too long string, so I shouldn't uss the char * declaration.3
char message2[INPUT_BUFFER_MAX_SIZE] = "A lot, if not all, want to boost your fears.\nHowever, it is up to you to make them success or not.\n";
char story1[INPUT_BUFFER_MAX_SIZE] = "Someone was blessed with a new baby, and he asked the obstetrician: Does it have a brain?\nThe doctor replied, surprised: What makes you wonder about that?\nThe man: No! I want it without a brain!\nThe doctor: Why?\nThe man: That's our custom... We remove our brains, so we obey our parents, and they,\nwho lack brains, in turn obey their parents, and so on until obedience finally\nleads to something no one knows about.\n"; // It's too long string, so I shouldn't uss the char * declaration.

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

        clear_string(prompt_string);
        read_string(prompt_string);

        strcpy(command, first_token(prompt_string));
        //------------------------------------------------------------------------------------
        if (strcmp("m1\n", command))
        {
            print(message1);
        }

        else if (strcmp("m2\n", command))
        {
            print(message2);
        }

        else if (strcmp("s1\n", command))
        {
            print(story1);
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
            print("m2           : A message that the OS wants to provide.\n");
            print("s1           : Strange situation.\n");
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