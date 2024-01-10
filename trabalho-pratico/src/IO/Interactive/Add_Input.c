#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../../../include/IO/Interactive/Add_Input.h"
#include "../../../include/IO/Interactive/UI.h"
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
int add_input(int * amount_queries){

    char * input = malloc(sizeof(char) * 1024);

    printf("Already existing Queries: \033[1m%d\033[0m\n",(*amount_queries));
    printf("\n[Input]\n|> ");

        if(scanf("%s",input)==1)
            clear_terminal();

        copy_file(input,"Resultados/input.txt", amount_queries);

    free(input);

    return 1;
}
///////////////////////////////////////////////////////////////