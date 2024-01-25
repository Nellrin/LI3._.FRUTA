#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <dirent.h>

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
static void reset_results(char *path) {
    DIR *dir = opendir(path);
    char * file = malloc(sizeof(char) * 1024);
    if (dir == NULL)return;

    struct dirent *entry;

    while ((entry = readdir(dir)) != NULL)
        if (entry->d_type == DT_REG){
            snprintf(file, 1024, "%s/%s", path, entry->d_name);

            if (remove(file) != 0)
            return;
        }

    free(file);
    closedir(dir);
}
///////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////
static char ** query_files_name_getter(char * path,int page,int limit){
    char ** list = malloc(sizeof(char *) * (limit+1));

    for(int i = 0; i < limit + 1; i++)
    list[i] = NULL;

    FILE * input = fopen(path,"r");
    char * query_line = malloc(sizeof(char) * 256);
    
    for(int j = 0; j < page && fgets(query_line, 256, input) != NULL; j++);

    for(int i = 0; i < limit && fgets(query_line, 256, input) != NULL; i++){
        query_line[strlen(query_line)-1] = '\0';
        list[i] = strdup(query_line);
    }

    fclose(input);
    free(query_line);

    return list;
}
static int pick_option(char * input, int * selected_option, int * amount_of_queries, int * first_query_shown, int * selected_query, int terminal_window_size){
    
    switch (toupper(input[0])){
        case 'B':
            (*selected_option) = 10;
            return 1;
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
            if(strlen(input)>1){
                int selected = atoi(input+1);
                if(selected > 0 && selected <= (*amount_of_queries)){
                    (*selected_query) = selected;
                    (*first_query_shown) = 0;
                    (*selected_option) = 6;
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
            reset_results("Resultados");
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
char ** draw_UI(char * path, int * amount, int terminal_window_size, int first_query_shown, int query){
    int i = 0;

    char * whats_gonna_get_printed = malloc(sizeof(char) * 4096);
    char * formated_text = malloc(sizeof(char) * 100);
    
    whats_gonna_get_printed[0] = '\0';
    formated_text[0] = '\0';

    char ** list_of_queries = query_files_name_getter(path,first_query_shown,terminal_window_size+1);


    for(; list_of_queries[i]!=NULL && i <= terminal_window_size; i++){
        snprintf(formated_text,100,"%03d|   %3.d)  %s\\",i+3,1+i+first_query_shown, list_of_queries[i]);
        strcat(whats_gonna_get_printed,formated_text);    
    }

        i++;

        snprintf(formated_text,100,  "%03d@-1\\%03d+----------+--------------+----------+--------------+\\",i+2,i+2);strcat(whats_gonna_get_printed,formated_text);
                snprintf(formated_text,100,  "%03d| (B) Back | (P) Previous | (N) Next | (J_) Jump to |\\",i+3);strcat(whats_gonna_get_printed,formated_text);
                snprintf(formated_text,100,  "%03d+----------+--------------+----------+--------------+\\",i+4);strcat(whats_gonna_get_printed,formated_text);


        if(!query){
                snprintf(formated_text,100,  "%03d+----------+--------+-----+-----+\\",i+4);strcat(whats_gonna_get_printed,formated_text);
                snprintf(formated_text,100,  "%03d                    | (R) Reset | (S_) Select query |\\",i+5);strcat(whats_gonna_get_printed,formated_text);
                snprintf(formated_text,100,  "%03d                    +-----------+-------------------+\\",i+6);strcat(whats_gonna_get_printed,formated_text);
        }

        strcat(whats_gonna_get_printed, "000@-1\\002@-1\\000+\\002+\\001|  \033[1mInteractive Mode\033[0m");


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
int check_query_menu(int * amount_of_queries, int * first_query_shown, int * selected_query){
    int amount = 0, terminal_window_size = terminal_height()-8, valid_option = 0, selected_option = 2;
        char * input = malloc(sizeof(char)*128);
        char * path = strdup("Resultados/input.txt");
    char ** UI_text = draw_UI(path,&amount, terminal_window_size-1, (*first_query_shown), 0);
        free(path);

            while(!valid_option){
                better_UI(UI_text,amount);

                bottom_of_terminal();
                printf("Execute: ");

                    if(fgets(input,128,stdin)!=NULL)
                    input[strlen(input)-1] = '\0';

                    valid_option = pick_option(input,&selected_option,amount_of_queries,first_query_shown,selected_query,terminal_window_size);
                
                clear_terminal();
            }

        for(int i = 0; i <= amount; i++)
        free(UI_text[i]);


        free(UI_text);
        free(input);

    return selected_option;
}
///////////////////////////////////////////////////////////////