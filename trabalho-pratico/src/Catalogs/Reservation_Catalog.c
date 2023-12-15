#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../../include/Catalogs/Reservation_Catalog.h"
#include "../../include/DataStructures/Reservations.h"


struct alm_re{
    Reservation ** list_reservations;
    int amount;
};

////////////////////////////////////////////////////////
static int hash_reservation(const char *str) {
    char * new_str = str + 4;

    int res = atoi(new_str) - 1;

    return res;
}
////////////////////////////////////////////////////////


////////////////////////////////////////////////////////
void insert_RESCAT(Almanac_Reservation * box,char * id,char * id_hotel, char * user_id, char * hotel_name, char * hotel_stars, char * begin_date, char * end_date, char * includes_breakfast, char * rating, char * ppn, char * city_tax){

    Reservation * a = set_reservation(id,id_hotel,user_id,hotel_name,hotel_stars,begin_date,end_date,includes_breakfast,rating,ppn,city_tax);

    int key = hash_reservation(id);
    box->list_reservations[key] = a;

}
void destroy_RESCAT(Almanac_Reservation * box){
    for(int i = 0; i<box->amount; i++)
    free_reservation(box->list_reservations[i]);


    free(box->list_reservations);
    free(box);
}
Almanac_Reservation * new_RESCAT(int amount){
    Almanac_Reservation * a = malloc(sizeof(Almanac_Reservation));
    
        a->list_reservations = malloc(sizeof(Reservation *) * amount);

        for(int i = 0; i < amount; i++)
            a->list_reservations[i] = NULL;

        a->amount = amount;

    return a;
}
////////////////////////////////////////////////////////