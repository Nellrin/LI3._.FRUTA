#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "../../../include/IO/Interactive/Add_Input.h"
#include "../../../include/IO/Interactive/UI.h"
#include "../../../include/IO/Interpreter.h"
#include "../../../include/Catalogs/Catalog.h"
///////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////
static void copy_file(char *source_dir, char *destination_dir, int *amount) {
    FILE * source = fopen(source_dir,"r");
    FILE * destination = fopen(destination_dir,"a");

    char * line = malloc(sizeof(char) * 1024);

    while (fgets(line, 1024, source) != NULL) {
        fputs(line, destination);
        (*amount)++;
    }

    free(line);
    fclose(source);
    fclose(destination);
}
int add_input(Almanac * u, int * amount_queries){

    if(u!=NULL){
        char * input = malloc(sizeof(char) * 1024);

        printf("Already existing Queries: \033[1m%d\033[0m\n",(*amount_queries));
        printf("\n[Input]\n|> ");


            if(fgets(input, 1024, stdin) != NULL)
            input[strlen(input)-1] = '\0';
                clear_terminal();
        
            if(access(input, F_OK) != -1){
                copy_file(input,"Resultados/input.txt", amount_queries);

                read_query_file(u, "Resultados/input.txt",0);
            }

        free(input);
    }

    return 10;
}
///////////////////////////////////////////////////////////////