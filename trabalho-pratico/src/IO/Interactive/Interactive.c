#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include "../../../include/Catalogs/Catalog.h"
#include "../../../include/IO/Interactive/Interactive.h"
#include "../../../include/IO/Output.h"
#include "../../../include/Tools/Utilities.h"
#include "../../../include/IO/Interpreter.h"
#include "../../../include/IO/Interactive/UI.h"

static void reset_input(){
    int c;
    while ((c = getchar()) != '\n' && c != EOF);}
static void copy_file(FILE *source, FILE *destination, int *amount) {
    char * line = malloc(sizeof(char) * 1024);

    while (fgets(line, 1024, source) != NULL) {
        fputs(line, destination);
        (*amount)++;
    }

    free(line);
}
static char ** query_files_name_getter(int page,int limit){

    if(limit == 0)return NULL;
    char ** list = malloc(sizeof(char *) * (limit+1));


    for(int i = 0; i < limit + 1; i++)
    list[i] = NULL;

    FILE * input = fopen("Resultados/input.txt","r");

    char * query_line = malloc(sizeof(char) * 128);
    
    for(int j = 0; j < page && fgets(query_line, 128, input) != NULL; j++);
    

    for(int i = 0; i < limit && fgets(query_line, 128, input) != NULL; i++){
        list[i] = strdup(query_line);
    }

    fclose(input);
    free(query_line);

    return list;
}

static int start_menu(){
    int amount = 0, option = -1;
    char * input = malloc(sizeof(char)*512);
    char * whats_gonna_get_printed = malloc(sizeof(char) * 2048*2);
    
    whats_gonna_get_printed[0] = '\0';



    strcat(whats_gonna_get_printed, "000@-1;"
                                     "002@-1;"
                                     "000+;"
                                     "002+;"
                                     "003|;"
                                     "009@-1;"
                                     "009+;"
                                     "001|  \033[1mInteractive Mode\033[0m ;"
                                     "004|   0. Exit;"
                                     "005|      1. Execute Query;"
                                     "006|      2. Check Queries;"
                                     "007|      3. Add input.txt;"
                                     "008|");

    char ** list = line_to_lines(whats_gonna_get_printed,&amount);


    while(option < 0 || option > 3){

    better_UI(list,amount);

            bottom_of_terminal();
            printf("Executar [0..3]: ");

            if(fgets(input, sizeof(input), stdin)!=NULL)
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
static int add_input(int * amount_queries){

    char * input = malloc(sizeof(char) * 1024);

    printf("Already existing Queries: \033[1m%d\033[0m\n",(*amount_queries));
    printf("\n[Input]\n|> ");

        if(scanf("%s",input)==1)
            clear_terminal();




    FILE * input_source = fopen(input,"r");
    FILE * input_destination = fopen("Resultados/input.txt","a");

    if(input_source != NULL){
        copy_file(input_source,input_destination, amount_queries);
        fclose(input_source);
    }

    fclose(input_destination);
    free(input);



    return 1;
}
static int check_query_menu(int * amount_of_queries, int * first_query_shown){
    int amount = 0, i = 0, terminal_window_size = terminal_height()-8;

    char * input = malloc(sizeof(char)*128);
    char * whats_gonna_get_printed = malloc(sizeof(char) * 4096);
    char * formated_text = malloc(sizeof(char) * 100);
    
    formated_text[0] = '\0';
    whats_gonna_get_printed[0] = '\0';





    char ** list_of_queries = query_files_name_getter((*first_query_shown),terminal_window_size);


    for(; list_of_queries[i]!=NULL && i < terminal_window_size; i++){
        snprintf(formated_text,100,"%03d|   %3.d)  %s;",i+3,1+i+(*first_query_shown), list_of_queries[i]);
        strcat(whats_gonna_get_printed,formated_text);    
    }
  
        i++;

        snprintf(formated_text,100,  "%03d@-1;%03d+----------+--------------+----------+-------------------+;",i+2,i+2);
        strcat(whats_gonna_get_printed,formated_text);

                snprintf(formated_text,100,  "%03d+----------+--------------+---+------+----+--------------+;",i+4);
        strcat(whats_gonna_get_printed,formated_text);

                snprintf(formated_text,100,  "%03d                              +-----------+--------------+;",i+6);
        strcat(whats_gonna_get_printed,formated_text);

                snprintf(formated_text,100,  "%03d                              | (R) Reset | (J_) Jump to |;",i+5);
        strcat(whats_gonna_get_printed,formated_text);

        snprintf(formated_text,100,  "%03d| (B) Back | (P) Previous | (N) Next | (S_) Select query |;",i+3);
        strcat(whats_gonna_get_printed,formated_text);

        strcat(whats_gonna_get_printed, "000@-1;"
                                        "002@-1;"
                                        "000+;"
                                        "002+;"
                                        "001|  \033[1mInteractive Mode\033[0m");




    char ** UI_text = line_to_lines(whats_gonna_get_printed,&amount);


        free(formated_text);
        free(whats_gonna_get_printed);




    int valid_option = 0;
    int selected_option = 2;

            while(!valid_option){

            better_UI(UI_text,amount);

                    bottom_of_terminal();
                    printf("Execute: ");

                if(scanf("%s",input)==1)
                    switch (toupper(input[0])){
                    case 'B':
                        selected_option = 1;
                        valid_option++;
                        break;



                    case 'J':
                        if(strlen(input)>1){
                            int jump = atoi(input+1) - 1;
                                if(jump >= 0 && jump < (*amount_of_queries)){
                                    (*first_query_shown) = jump;
                                    valid_option++;
                                }
                        }
                        break;


                    
                    case 'S':
                        selected_option = 1000 + atoi(input+1);
                        valid_option++;
                        break;



                    case 'P':
                        if((*first_query_shown) - terminal_window_size>0)
                        (*first_query_shown)-=terminal_window_size;

                        else
                        (*first_query_shown) = 0;

                        valid_option++;
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

                        valid_option++;
                        break;



                    case 'R':
                        FILE *file = fopen("Resultados/input.txt", "w");
                        fclose(file);
                        valid_option++;
                        (*amount_of_queries) = 0;
                        (*first_query_shown) = 0;
                        break;
                    


                    default:
                        break;
                    }


                

                clear_terminal();
            }



        for(i = 0; i <= amount; i++)
        free(UI_text[i]);

        for(i = 0; i <= terminal_window_size; i++)
        if(list_of_queries[i] != NULL)
        free(list_of_queries[i]);

        free(input);
        free(UI_text);
        free(list_of_queries);

    return selected_option;

}
///////////////////////////////////////////////////////////////
void interactive_mode(Almanac * (*f)(char *)){
    
    clear_terminal();
    
    char * path = malloc(sizeof(char)*256);

    int amount_queries = 0, first_query_shown = 0;    
    
    
    printf("[Dataset Directory]\n|> ");
    if(scanf("%s",path) != 1){perror("Erro ao receber datasets");}
        reset_input();


    clear_terminal();
    
    Almanac * u = NULL;
    u = f(path);

    FILE * file = fopen("Resultados/input.txt","w");
    fclose(file);

    free(path);

        int option = 1;
        while (option!=0){
            
            
            
            switch (option){
            case 1:
                option = start_menu();
                break;

            case 2:
                option = check_query_menu(&amount_queries,&first_query_shown);
                break;

            case 3:
                option = add_input(&amount_queries);
                break;


            default:
                continue;
                break;
            }
    
            clear_terminal();
        }



        free_almanac(u);

}
///////////////////////////////////////////////////////////////