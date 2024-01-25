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
static double bill_collector(char ** list, char * start, char * end, int amount){
    char * S1 = NULL;
    char * S2 = NULL;
    double result = 0;
    int nights = 0;

    for(int i = 0; i < amount * 3; i+=3){
        nights = 0;
        
        if(!((strcmp(list[i + 1],start) < 0 || strcmp(list[i],end) > 0))){

            if(strcmp(list[i], start) < 0) S1 = start;
            else S1 = list[i];
        
                        if(strcmp(list[i + 1], end) > 0){
                            S2 = end;
                            nights = 1;
                        }
                        else S2 = list[i + 1];


            nights += string_to_time("%d/%d/%d",S1, S2);


            result += nights * atoi(list[i + 2]);
        }
    }
    return result;
}
static void get_them_bands(void * a, char *** list, int i, int argumentos){
    (*list)[i*argumentos] = get_reservationBEGIN((Reservation*) a);
    (*list)[i*argumentos + 1] = get_reservationEND((Reservation*) a);

    (*list)[i*argumentos + 2] = malloc(sizeof(char) * 8);
    snprintf((*list)[i*argumentos + 2],8,"%d",get_reservationPPN((Reservation*) a));
}
char * query8(Almanac * box, char ** arguments, short F){

    int amount = 0;
    char ** lines = almanac_get_hotel(box,arguments[1],&amount,3,get_them_bands);

    if(lines==NULL) return NULL;

    if(strcmp(arguments[2],arguments[3])>0)
    swap_strings((&arguments[2]),(&arguments[3]));

    char * result = strcat_list(F,bill_collector(lines,arguments[2],arguments[3],amount));

    for(int i = 0; i < amount * 3; i +=3){
        free(lines[i]);
        free(lines[i + 1]);
        free(lines[i + 2]);
    }

    free(lines);

    return result;
}