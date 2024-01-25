#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include "../../../include/Tools/Utilities.h"
#include "../../../include/Catalogs/Catalog.h"
#include "../../../include/IO/Output.h"
#include "../../../include/IO/Interpreter.h"
#include "../../../include/IO/Interactive/Instructions.h"
#include "../../../include/IO/Interactive/Check_Queries.h"
#include "../../../include/IO/Interactive/UI.h"
///////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////
static int pick_option(char * input, int * selected_option, int amount_of_queries, int * first_query_shown, int terminal_window_size){
    switch (toupper(input[0])){
        case 'B':
            (*selected_option) = 10;
            (* first_query_shown) = 0;
            return 1;
            break;


        case 'J':
            if(strlen(input)>1){
                int jump = atoi(input+1) - 1;
                if(jump >= 0 && jump < amount_of_queries){
                    (*first_query_shown) = jump;
                    return 1;
                }
            }
            break;


        case 'P':
            if((*first_query_shown) > terminal_window_size)
            (*first_query_shown)-=terminal_window_size;

            else
            (*first_query_shown) = 0;

            return 1;
            break;


        case 'N':
            if((*first_query_shown) + (terminal_window_size) <amount_of_queries
                && amount_of_queries > (terminal_window_size))
            (*first_query_shown) += (terminal_window_size);

            else{
                if(amount_of_queries > terminal_window_size)
                (*first_query_shown) = amount_of_queries - (terminal_window_size);

                else
                (*first_query_shown) = 0;
            }

            return 1;
            break;

        default:
            break;
    }
    return 0;
}
///////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////
int instructions(int * first_query_shown){
    
    char * input = malloc(sizeof(char)*128);
    char * path = malloc(sizeof(char)*128);
    snprintf(path,128,"src/IO/Interactive/Cool_text_B)");
    
    int amount = 0,
        amount_lines = count_lines(path), 
        terminal_window_size = terminal_height()-8, 
        valid_option = 0, 
        selected_option = 5;


    char ** UI_text = draw_UI(path,&amount, terminal_window_size-1, (*first_query_shown), 1);
        free(path);

            while(!valid_option){
                better_UI(UI_text,amount);

                bottom_of_terminal();
                printf("Execute: ");

                    if(fgets(input,128,stdin)!=NULL)
                    input[strlen(input)-1] = '\0';

                    valid_option = pick_option(input,&selected_option,amount_lines,first_query_shown,terminal_window_size);
                
                clear_terminal();
            }


        for(int i = 0; i <= amount; i++)
        free(UI_text[i]);

        free(UI_text);
        free(input);

    return selected_option;
}
///////////////////////////////////////////////////////////////