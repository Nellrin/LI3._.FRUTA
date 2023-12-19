#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/Parser.h"
#include "../include/Output.h"

void parser(char * path,char * type,Almanac * box, int (*f)(Almanac *,const char *)){
    char * name = malloc(sizeof(char)*200);

    int take_nl,amount = 0;

    snprintf(name, 200, "%s/%s.csv", path, type);
    FILE * file = create_file(name,"r");

    printf("%s\n",name);

    free(name);

    name = malloc(sizeof(char)*200);
    snprintf(name, 200, "Resultados/%s_errors.csv", type);


    FILE * errors = create_file(name,"w");


    char *head = NULL;
    size_t len = 0;
    if(getline(&head, &len, file));
    write_line(errors,head);
    
    
    while (getline(&head, &len, file) != -1) {
        char *line = strdup(head);
        take_nl = strlen(head)-1;
        head[take_nl] = '\0';

        if(f(box,head))
        amount++;

        else
        write_line(errors,line);
        
        
        free(line);
    }

    printf("\n\n%d\n\n",amount);

    free(head);
    free(name);
    fclose(file);
    fclose(errors);
}