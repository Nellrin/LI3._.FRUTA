#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../../include/IO/Output.h"

FILE * create_file(char * title,char * type){
    FILE *file = fopen(title, type);

    if (file == NULL) {
        printf("Error opening %s\n",title);
        return NULL;
    }

    return file;
}

void write_line(FILE * file, char * line){
    if (line != NULL)
    fprintf(file, "%s",line);
}