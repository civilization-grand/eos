
#include "stdio/stdio.h"
#include "string/string.h"
#include "vga/vga.h"

extern int cp;
int shell_cursor = 0;

char *message1 = "He chose the rejoice of being imbued, it is the will to calamity,\noblivion is his auguries. His fetid realm is misanthropy.\nPay heed, don't relinquish cosmos...\n";
char *story1 = "Someone was blessed with a new baby, and he asked the obstetrician: Does it have a brain?\nThe doctor replied, surprised: What makes you wonder about that?\nThe man: No! I want it without a brain!\nThe doctor: Why?\nThe man: That's our custom... We remove our brains, so we obey our parents, and they,\nwho lack brains, in turn obey their parents, and so on until obedience finally\nleads to something no one knows about.\n";
char *poem1_1 = "    I met a traveller from an antique land\n";
char *poem1_2 = "    Who said: Two vast and trunkless legs of stone\n";
char *poem1_3 = "    Stand in the desart. Near them, on the sand,\n";
char *poem1_4 = "    Half sunk, a shattered visage lies, whose frown,\n";
char *poem1_5 = "    And wrinkled lip, and sneer of cold command,\n";
char *poem1_6 = "    Tell that its sculptor well those passions read\n";
char *poem1_7 = "    Which yet survive, stamped on these lifeless things,\n";
char *poem1_8 = "    The hand that mocked them and the heart that fed:\n";
char *poem1_9 = "    And on the pedestal these words appear:\n";
char *poem1_10 = "    'My name is Ozymandias, King of Kings:\n";
char *poem1_11 = "    Look on my works, ye Mighty, and despair!'\n";
char *poem1_12 = "    No thing beside remains. Round the decay\n";
char *poem1_13 = "    Of that colossal wreck, boundless and bare\n";
char *poem1_14 = "    The lone and level sands stretch far away.\n";
char *poem1_15 = "-Percy Shelley, Ozymandias, 1819 edition\n";

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

        if (strcmp("s1\n", prompt_string))
        {
            print(story1);
        }

        if (strcmp("p1\n", prompt_string))
        {
            print(poem1_1);
            print(poem1_2);
            print(poem1_3);
            print(poem1_4);
            print(poem1_5);
            print(poem1_6);
            print(poem1_7);
            print(poem1_8);
            print(poem1_9);
            print(poem1_10);
            print(poem1_12);
            print(poem1_13);
            print(poem1_14);
            print(poem1_15);
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
            print("s1           : Strange situation.\n");
            print("p1           : Ozymandias poem by Percy Shelley.\n");
            print("print -txt-  : To print a string.\n");
            print("-----------------------------------------------------\n");
        }
        //------------------------------------------------------------------------------------
        else
        {
            /*
            for (int i = 0; i < strlen(prompt_string); i++)
            {
                write_char(prompt_string[i], 0, BROWN);
                if (prompt_string[i] == '\n')
                {
                    print("new line\n");
                }

                print("\n");
            }
            */

            /*Do nothin*/
        }
    }

    return 0;
}