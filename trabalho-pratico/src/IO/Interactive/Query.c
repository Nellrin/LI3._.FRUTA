#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include "../../../include/Tools/Utilities.h"
#include "../../../include/Catalogs/Catalog.h"
#include "../../../include/IO/Output.h"
#include "../../../include/IO/Interpreter.h"
#include "../../../include/IO/Interactive/Query.h"
#include "../../../include/IO/Interactive/Check_Queries.h"
#include "../../../include/IO/Interactive/UI.h"
///////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////
static int get_query(char * input){

    switch (atoi(input)){
        case 1:
            return (count_chars(input,' ') == 1);
            break;
        
        case 2:
            return (count_chars(input,' ') >= 1);
            break;
        
        case 3:
            return (count_chars(input,' ') == 1);
            break;
        
        case 4:
            return (count_chars(input,' ') == 1);
            break;
        
        case 5:
            return (count_chars(input,' ') == 3);
            break;
        
        case 6:
            return (count_chars(input,' ') == 2);
            break;
        
        case 7:
            return (count_chars(input,' ') == 1);
            break;
        
        case 8:
            return (count_chars(input,' ') == 3);
            break;
        
        case 9:
            return (count_chars(input,' ') == 1);
            break;
        
        case 10:
            return (count_chars(input,' ') >= 0);
            break;
        
        default:
            return 0;
            break;
        }

}
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
int show_query(int selected_query, int * first_query_shown){
    
    char * input = malloc(sizeof(char)*128);
    char * path = malloc(sizeof(char)*128);
    snprintf(path,128,"Resultados/command%d_output.txt",selected_query);
    
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

int execute_query(Almanac * u, int * amount_of_queries, int * selected_query, int * first_query_shown){

    clear_terminal();
    bottom_of_terminal();

    if(u==NULL) return 10;

    printf("[Query]\n|> ");

    char * input = malloc(sizeof(char) * 1024);

        if(fgets(input, 1024, stdin) != NULL)
        input[strlen(input)-1] = '\0';

        printf("%s",input);




        if(get_query(input)){
            FILE * input_file = fopen("Resultados/input.txt","a");
            fputs(input,input_file);
            fputs("\n",input_file);


            (*amount_of_queries)++;
            (* selected_query) = (*amount_of_queries);
            (* first_query_shown) = 0;
            filter_querys(u,input,(*amount_of_queries));
            
            fclose(input_file);
        }

        clear_terminal();
        free(input);

        return 5;
}
///////////////////////////////////////////////////////////////