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
static double get_rating(const void * reservation){
    char * y = get_reservationRATING((Reservation*) reservation);
    double x = strtod(y,NULL);
    
    free(y); 

    return x;
}
static char * query3_getter(Almanac * box, char * argument, char F){
    char * result = NULL;
    int nr = almanac_get_hotel_num_res(box,argument);
    
    void * hotels = almanac_get_hotel(box,argument);
    double value = do_something(hotels, get_rating);
    
    value /= nr;
    result = strcat_list(F,value);

    return result;
}


char * query3(Almanac * box, char * argument, short F){

    if(almanac_get_hotel(box,argument)!=NULL)
    return query3_getter(box,argument,F);

    return NULL;
}