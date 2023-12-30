#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "../../include/Catalogs/Catalog.h"
#include "../../include/Tools/Utilities.h"

#include "../../include/DataStructures/BTree.h"
#include "../../include/DataStructures/Reservations.h"
#include "../../include/DataStructures/Users.h"
#include "../../include/Queries/8Query.h"


static char * strcat_list(short F, double n){

    char * line = malloc(sizeof(char) * 100);
    line[0] = '\0';
    
    if(F)
    snprintf(line,100, "--- 1 ---\nrevenue: %d\n", (int)n);

    else 
    snprintf(line,100, "%d\n", (int)n);


    return line;

}
static double get_revenue(void * box, const void * reservation, char * begin, char * end){
    char * res_begin = get_reservationBEGIN((Reservation*) reservation);
    char * res_end = get_reservationEND((Reservation*) reservation);
    char * user_id = get_reservationUSERID((Reservation*) reservation);


    double result = 0;
    int nights = 0;    


    if(strcmp(begin,end)>0){
        swap_pointers((void *)(&begin),(void *)(&end));
        printf("YE\n");
    }
    

    
    if(!((strcmp(res_end,begin) < 0 || strcmp(res_begin,end) > 0)))
    // if(get_userASTATUS(almanac_get_user(box,user_id))==1)
    {
        char *start = NULL;

        
            if(strcmp(res_begin, begin) < 0){
                start = begin;
                // nights ++;
            }
    
            else
            start = res_begin;


        char *finish = NULL;
        
            if(strcmp(res_end, end) > 0){
                finish = end;
                nights =1;
            }
            
            else
            finish = res_end;

        nights += string_to_time("%d/%d/%d",start, finish);


        result = nights * get_reservationPPN((Reservation*) reservation);

    
/*
         
        +-----------------------+                       +-----------------------+-----------------------+ 
        |ppn        =       100€|                       |nights     =          0|total_cost   =     100€|
        +-----------------------+-----------------------+-----------------------+-----------------------+
        |res_begin  = 2023/10/01|begin      = 2023/10/01|start      = 2023/10/01|
        +-----------------------+-----------------------+-----------------------+
        |res_end    = 2023/10/02|end        = 2023/10/02|finish     = 2023/10/02|
        +-----------------------+-----------------------+-----------------------+

        caso um hotel tenha apenas uma reserva de 100€/noite de 2023/10/01 a 2023/10/10, e quisermos saber as 
        receitas entre 2023/10/01 a 2023/10/02, deverá ser retornado 200€ (duas noites). Por outro lado, caso 
        a reserva seja entre 2023/10/01 a 2023/10/02, deverá ser retornado 100€ (uma noite).
*/
    }

    free(user_id);
    free(res_begin); 
    free(res_end); 

    return result;
}
static char * query8_getter(Almanac * box, char ** arguments, char F){
    char * result = NULL;

        void * hotels = almanac_get_hotel(box,arguments[1]);
        double value = money_trees(box,hotels,arguments[2],arguments[3], get_revenue);
        
        result = strcat_list(F,value);

    return result;
}


char * query8(Almanac * box, char ** arguments, short F){

    if(almanac_get_hotel(box,arguments[1])!=NULL)
    return query8_getter(box,arguments,F);

    return NULL;
}