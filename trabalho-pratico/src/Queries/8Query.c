#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "../../include/Catalogs/Catalog.h"
#include "../../include/Utilities.h"

#include "../../include/DataStructures/BTree.h"
#include "../../include/DataStructures/Reservations.h"
#include "../../include/Queries/8Query.h"



static char * strcat_list(short F, double n){

    char * line = malloc(sizeof(char) * 40);
    line[0] = '\0';
    
    if(F)
    snprintf(line,40, "--- 1 ---\nrevenue: %.0f\n", n);

    else 
    snprintf(line,40, "%.0f\n", n);


    return line;

}
static double get_revenue(const void * reservation, char * begin, char * end){
    char * ppn = get_reservationPPN((Reservation*) reservation);
    char * res_begin = get_reservationBEGIN((Reservation*) reservation);
    char * res_end = get_reservationEND((Reservation*) reservation);
    double x = strtod(ppn,NULL), result;
    


    if(strcmp(begin,end)>0)
    swap_strings(&begin,&end);
    

    if(strcmp(res_end,begin)>=0 && strcmp(end,res_begin)>=0){
        char * start = NULL;
        char * finish = NULL;
        int days = 0;

                if(strcmp(res_begin,begin)>0)
                start = (res_begin);
                
                else{
                    start = (begin);
                    days++;
                }


                if(strcmp(res_end,end)>=0)
                    finish = (end);
                
                
                else{
                    finish = (res_end);
                    // if(days==0)days++;
                }

                // printf("__________\nSTART: %s  (REAL: %s    HOTEL:%s)\nFINISH: %s  (REAL: %s    HOTEL:%s)\n_________\n\n",start,begin,res_begin,finish,end,res_end);


        days += string_to_time("%d/%d/%d",start,finish);
        result = days * x;

    }

    free(ppn); 
    free(res_begin); 
    free(res_end); 

    return result;
}
static char * query8_getter(Almanac * box, char ** arguments, char F){
    char * result = NULL;

    void * hotels = almanac_get_hotel(box,arguments[1]);
    double value = money_trees(hotels,arguments[2],arguments[3], get_revenue);
    
    printf("%f\n",value);

    result = strcat_list(F,value);

    return result;
}


char * query8(Almanac * box, char ** arguments, short F){

    if(almanac_get_hotel(box,arguments[1])!=NULL)
    return query8_getter(box,arguments,F);

    return NULL;
}