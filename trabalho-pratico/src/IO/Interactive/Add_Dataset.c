#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../../../include/IO/Interactive/Add_Dataset.h"
#include "../../../include/IO/Interactive/UI.h"
#include "../../../include/Catalogs/Catalog.h"
///////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////
int add_dataset(Almanac ** u, Almanac * (*f)(char *)){
    char * input = malloc(sizeof(char) * 1024);

    printf("\n[Dataset Directory]\n|> ");

        if(scanf("%s",input)==1)
            clear_terminal();

    free_almanac(*u);

    *u = f(input);
    free(input);

    if(*u==NULL)
    printf("NULL ALMANAC!\n");

    return 10;
}
///////////////////////////////////////////////////////////////