#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include "../../../include/IO/Interactive/Start_Menu.h"
#include "../../../include/IO/Output.h"
#include "../../../include/IO/Interactive/UI.h"


int start_menu(){
    int amount = 0, option = -1;
    char * input = malloc(sizeof(char)*512);
    char * whats_gonna_get_printed = malloc(sizeof(char) * 2048*2);
    
    whats_gonna_get_printed[0] = '\0';

    strcat(whats_gonna_get_printed, "000@-1\\"
                                     "002@-1\\"
                                     "000+\\"
                                     "002+\\"
                                     "003|\\"
                                     "011@-1\\"
                                     "011+\\"
                                     "001|  \033[1mInteractive Mode\033[0m \\"
                                     "004|   0. Exit\\"
                                     "005|      1. Execute Query\\"
                                     "006|      2. Check Queries\\"
                                     "007|      3. Add input.txt\\"
                                     "008|      4. Add dataset\\"
                                     "009|      5. Instructions\\"
                                     "010|");

    char ** list = line_to_lines(whats_gonna_get_printed,&amount);


    while(option < 0 || option > 5){

    better_UI(list,amount);

            bottom_of_terminal();
            printf("Executar [0..5]: ");

            if(fgets(input, 512, stdin)!=NULL)
                if(isdigit(input[0]))
                    option = atoi(input);

            clear_terminal();
    }

        for(int i = 0; i < amount; i++)
        free(list[i]);

        free(input);
        free(list);
        free(whats_gonna_get_printed);

    return option;
}