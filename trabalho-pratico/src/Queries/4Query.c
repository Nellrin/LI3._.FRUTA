#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "../../include/Catalogs/Catalog.h"
#include "../../include/IO/Output.h"
#include "../../include/Tools/Utilities.h"

#include "../../include/DataStructures/BTree.h"
#include "../../include/DataStructures/Reservations.h"
#include "../../include/Queries/4Query.h"


static void get_all_reservations_from_hotel_F(void * a, char *** list, int i, int argumentos){
    // id;begin_date;end_date;user_id;rating;total_price

    (*list)[i*argumentos] = malloc(sizeof(char) * 600);
    (*list)[i*argumentos + 1] = get_reservationBEGIN((Reservation *)a);
    
    char * b = get_reservationID((Reservation *)a);
    char * d = get_reservationEND((Reservation *)a);
    char * c = get_reservationUSERID((Reservation *)a);
    
    double rating = get_reservationRATING((Reservation *)a);
    double cash_money = total_got_from_reservation((Reservation *)a);


                snprintf((*list)[i*argumentos],600,
                                                "id: %s\n"
                                                "begin_date: %s\n"
                                                "end_date: %s\n"
                                                "user_id: %s\n"
                                                "rating: %d\n"
                                                "total_price: %.3f\n",
                                                b,(*list)[i*argumentos + 1],d,c,(int)rating,cash_money);

    free(b);
    free(c);
    free(d);
}

static void get_all_reservations_from_hotel(void * a, char *** list, int i, int argumentos){
    // id;begin_date;end_date;user_id;rating;total_price

    (*list)[i*argumentos] = malloc(sizeof(char) * 600);
    (*list)[i*argumentos + 1] = get_reservationBEGIN((Reservation *)a);
    
    char * b = get_reservationID((Reservation *)a);
    char * d = get_reservationEND((Reservation *)a);
    char * c = get_reservationUSERID((Reservation *)a);
    
    double rating = get_reservationRATING((Reservation *)a);
    double cash_money = total_got_from_reservation((Reservation *)a);


                snprintf((*list)[i*argumentos],100,"%s;%s;%s;%s;%d;%.3f\n",
                                                        b,(*list)[i*argumentos + 1],d,c,(int)rating,cash_money);

    free(b);
    free(c);
    free(d);
}


static int strcmp_q4(char* str1, char* str2, char* id1, char* id2) {

    int date_compare = strcmp(str2, str1);
    if (date_compare == 0) {
        return strcmp(id1, id2);
    }
    return date_compare;
}

char * query4(FILE * file, Almanac * box, char * argument, short F){
    
    int amount = 0;
    char ** lines = NULL;
    
    
            if(F) lines = almanac_get_hotel(box,argument,&amount,2,get_all_reservations_from_hotel_F);
            
            else lines = almanac_get_hotel(box,argument,&amount,2,get_all_reservations_from_hotel);


    if(lines==NULL) return NULL;




    char ** dates = malloc(sizeof(char *) * amount);
    char ** ids = malloc(sizeof(char *) * amount);

            for(int i = 0; i < amount * 2; i+=2){
                dates[i/2] = lines[i+1];
                ids[i/2] = lines[i];
            }

    free(lines);
    
    
            sort_strings(&dates,&ids,amount,strcmp_q4);
    




    if(!F)
    for(int i = 0; i < amount; i++){
        write_line(file,ids[i]);
        free(ids[i]);
        free(dates[i]);
    }

    else{
        char * result = malloc(sizeof(char) * 700);
        
        snprintf(result,700,"--- 1 ---\n%s",ids[0]);
        write_line(file,result);
            free(ids[0]);
            free(dates[0]);
        
        for(int i = 1; i < amount; i++){
            snprintf(result,700,"\n--- %d ---\n%s",i+1,ids[i]);
            write_line(file,result);
            free(ids[i]);
            free(dates[i]);
        }

        free(result);
    }

    free(ids);
    free(dates);

    return NULL;
}