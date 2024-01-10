#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

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
static void reset_input(){
    int c;
    while ((c = getchar()) != '\n' && c != EOF);}
///////////////////////////////////////////////////////////////


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