#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include "../../../include/Tools/Utilities.h"
#include "../../../include/Catalogs/Catalog.h"
#include "../../../include/IO/Output.h"
#include "../../../include/IO/Interpreter.h"
#include "../../../include/IO/Interactive/Interactive.h"
#include "../../../include/IO/Interactive/UI.h"
#include "../../../include/IO/Interactive/Add_Input.h"
#include "../../../include/IO/Interactive/Start_Menu.h"
#include "../../../include/IO/Interactive/Check_Queries.h"
///////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////
static char ** query_files_name_getter(int page,int limit){
    char ** list = malloc(sizeof(char *) * (limit+1));

    for(int i = 0; i < limit + 1; i++)
    list[i] = NULL;

    FILE * input = fopen("Resultados/input.txt","r");
    char * query_line = malloc(sizeof(char) * 128);
    
    for(int j = 0; j < page && fgets(query_line, 128, input) != NULL; j++);

    for(int i = 0; i < limit && fgets(query_line, 128, input) != NULL; i++)
    list[i] = strdup(query_line);

    fclose(input);
    free(query_line);

    return list;
}
static int pick_option(char * input, int * selected_option, int * amount_of_queries, int * first_query_shown, int terminal_window_size){
    
    switch (toupper(input[0])){
        case 'B':
            (*selected_option) = 1;
            return 1;;
            break;


        case 'J':
            if(strlen(input)>1){
                int jump = atoi(input+1) - 1;
                if(jump >= 0 && jump < (*amount_of_queries)){
                    (*first_query_shown) = jump;
                    return 1;
                }
            }
            break;


        case 'S':
            // selected_option = 1000 + atoi(input+1);
            // valid_option++;
            break;


        case 'P':
            if((*first_query_shown) > terminal_window_size)
            (*first_query_shown)-=terminal_window_size;

            else
            (*first_query_shown) = 0;

            return 1;
            break;


        case 'N':
            if((*first_query_shown) + (terminal_window_size) <(*amount_of_queries)
                && (*amount_of_queries) > (terminal_window_size))
            (*first_query_shown) += (terminal_window_size);

            else{
                if((*amount_of_queries) > terminal_window_size)
                (*first_query_shown) = (*amount_of_queries) - (terminal_window_size);

                else
                (*first_query_shown) = 0;
            }

            return 1;
            break;


        case 'R':
            FILE *file = fopen("Resultados/input.txt", "w");
            fclose(file);
            (*amount_of_queries) = 0;
            (*first_query_shown) = 0;
            return 1;
            break;


        default:
            break;
    }
    return 0;
}
static char ** draw_UI(int * amount, int terminal_window_size, int first_query_shown){
    int i = 0;

    char * whats_gonna_get_printed = malloc(sizeof(char) * 4096);
    char * formated_text = malloc(sizeof(char) * 100);
    
    formated_text[0] = '\0';
    whats_gonna_get_printed[0] = '\0';

    char ** list_of_queries = query_files_name_getter(first_query_shown,terminal_window_size+1);


    for(; list_of_queries[i]!=NULL && i <= terminal_window_size; i++){
        snprintf(formated_text,100,"%03d|   %3.d)  %s;",i+3,1+i+first_query_shown, list_of_queries[i]);
        strcat(whats_gonna_get_printed,formated_text);    
    }

        i++;

        snprintf(formated_text,100,  "%03d@-1;%03d+----------+--------------+----------+-------------------+;",i+2,i+2);strcat(whats_gonna_get_printed,formated_text);
                snprintf(formated_text,100,  "%03d| (B) Back | (P) Previous | (N) Next | (S_) Select query |;",i+3);strcat(whats_gonna_get_printed,formated_text);
                snprintf(formated_text,100,  "%03d+----------+--------------+---+------+----+--------------+;",i+4);strcat(whats_gonna_get_printed,formated_text);
                snprintf(formated_text,100,  "%03d                              | (R) Reset | (J_) Jump to |;",i+5);strcat(whats_gonna_get_printed,formated_text);
                snprintf(formated_text,100,  "%03d                              +-----------+--------------+;",i+6);strcat(whats_gonna_get_printed,formated_text);

        strcat(whats_gonna_get_printed, "000@-1;002@-1;000+;002+;001|  \033[1mInteractive Mode\033[0m");


    char ** result = line_to_lines(whats_gonna_get_printed,amount);


        for(int i = 0; i <= terminal_window_size; i++)
            if(list_of_queries[i] != NULL)
            free(list_of_queries[i]);
        
        free(formated_text);
        free(list_of_queries);
        free(whats_gonna_get_printed);

    return result;
}
///////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////
int check_query_menu(int * amount_of_queries, int * first_query_shown){
    int amount = 0, terminal_window_size = terminal_height()-8, valid_option = 0, selected_option = 2;
        char * input = malloc(sizeof(char)*128);
    char ** UI_text = draw_UI(&amount, terminal_window_size-1, (*first_query_shown));

            while(!valid_option){
                better_UI(UI_text,amount);

                bottom_of_terminal();
                printf("Execute: ");

                    if(scanf("%s",input)==1)
                    valid_option = pick_option(input,&selected_option,amount_of_queries,first_query_shown,terminal_window_size);
                
                clear_terminal();
            }

        for(int i = 0; i <= amount; i++)
        free(UI_text[i]);


        free(UI_text);
        free(input);

    return selected_option;
}
///////////////////////////////////////////////////////////////