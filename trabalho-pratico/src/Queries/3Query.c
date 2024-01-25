#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "../../include/Catalogs/Catalog.h"

#include "../../include/DataStructures/BTree.h"
#include "../../include/DataStructures/Reservations.h"
#include "../../include/Queries/3Query.h"



static char * strcat_list(short F, double n){

    char * line = malloc(sizeof(char) * 40);
    line[0] = '\0';
    
    if(F)
    snprintf(line,40, "--- 1 ---\nrating: %.3f\n", n);

    else 
    snprintf(line,40, "%.3f\n", n);


    return line;

}

static void get_all_ratings(void * a, char *** list, int i, int argumentos){
    double number = get_reservationRATING((Reservation *)a);
    (*list)[i*argumentos] = malloc(sizeof(char) * 20);
    snprintf((*list)[i*argumentos],20,"%.3f",number);
}



char * query3(Almanac * box, char * argument, short F){

    int amount = 0;
    char ** lines = almanac_get_hotel(box,argument,&amount,1,get_all_ratings);

    if(lines==NULL) return NULL;

    double result = 0;

    for(int i = 0; i < amount; i++){
        result += strtod(lines[i],NULL);
        free(lines[i]);
    }

    free(lines);

    return strcat_list(F,result/amount);
}