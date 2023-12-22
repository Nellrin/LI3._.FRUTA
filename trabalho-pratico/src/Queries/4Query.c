#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "../../include/Catalogs/Catalog.h"
#include "../../include/Output.h"

#include "../../include/DataStructures/BTree.h"
#include "../../include/DataStructures/Reservations.h"
#include "../../include/Queries/4Query.h"



static void str_reservation(FILE * file,void * reservation,int * n, char F){
    char * id = get_reservationID(reservation);
    char * begin = get_reservationBEGIN(reservation);
    char * end = get_reservationEND(reservation);
    char * user = get_reservationUSERID(reservation);
    char * rating = get_reservationRATING(reservation);
    double total_price = total_got_from_reservation(reservation);
    
    char * result = malloc(sizeof(char) * 1000); 

    if(F){
                if(!(*n))
                snprintf(result,1000,
                            "--- %d ---\n"
                            "id: %s\n"
                            "begin_date: %s\n"
                            "end_date: %s\n"
                            "user_id: %s\n"
                            "rating: %s\n"
                            "total_price: %.3f\n",
                            (*n)+1,id,begin,end,user,rating,total_price);

                else
                snprintf(result,1000,
                            "\n--- %d ---\n"
                            "id: %s\n"
                            "begin_date: %s\n"
                            "end_date: %s\n"
                            "user_id: %s\n"
                            "rating: %s\n"
                            "total_price: %.3f\n",
                            (*n)+1,id,begin,end,user,rating,total_price);
        }

    else
    snprintf(result,100,"%s;%s;%s;%s;%s;%.3f\n",id,begin,end,user,rating,total_price);


    (*n)++;


    write_line(file,result);

    free(result);
    free(id);
    free(begin);
    free(end);
    free(user);
    free(rating);
}

static void query4_getter(FILE * file,Almanac * box, char * argument, char F){

    void * hotels = almanac_get_hotel(box,argument);

    int nr = 0;
    get_every_node(file,hotels,&nr,F,str_reservation);
    
}


char * query4(FILE * file, Almanac * box, char * argument, short F){

    if(almanac_get_hotel(box,argument)!=NULL)
    query4_getter(file,box,argument,F);

    return NULL;
}