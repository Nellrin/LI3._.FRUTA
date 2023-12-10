#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/Output.h"

FILE * create_file(char * title,char * type){
    FILE *file = fopen(title, type);

    if (file == NULL) {
        perror(("Error opening %s\n",title));
        return NULL;
    }

    return file;
}

void write_line(FILE * file, char * line){
    fprintf(file, "%s",line);
}