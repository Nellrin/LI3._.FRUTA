#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../../include/Catalogs/Reservation_Catalog.h"
#include "../../include/DataStructures/Reservations.h"
#include "../../include/DataStructures/Hotel.h"
#include "../../include/DataStructures/Functions.h"


typedef struct almanac_reservation{
    Reservation ** list_reservations;
    Hotel ** list_hotels;
}Almanac_Reservation;

////////////////////////////////////////////////////////
static int hash_reservation(char *str) {
    char * new_str = str + 4;

    char * good_id = strdup(new_str);
    int res = atoi(good_id);
    res--;
    free(good_id);

    return res;
}
static int hash_hotel(char *str) {
    char * new_str = str + 3;


    char * good_id = strdup(new_str);
    int res = atoi(good_id);
    free(good_id);
    res--;
    return res;
}
////////////////////////////////////////////////////////


////////////////////////////////////////////////////////
void insert_reservation(Almanac_Reservation * box,Reservation * a, char * ppn, char * rating){

    char * hotel_id = Data.reservation.get.hotel_id(a);

    int hotel_key = hash_hotel(hotel_id);


    if(box->list_hotels[hotel_key] != NULL)
    hotel_add_reservation(box->list_hotels[hotel_key],a);

    else{
        Hotel * x = Data.hotel.set(ppn,rating,a);
        hotel_key = hash_hotel(hotel_id);
        box->list_hotels[hotel_key] = x;
    }

    free(hotel_id);



    char * id = Data.reservation.get.id(a);
    int key = hash_reservation(id);
    box->list_reservations[key] = a;
    free(id);
}
void destroy_reservation_almanac(Almanac_Reservation * box){
    for(int i = 0; i<10000; i++)
    Data.hotel.free(box->list_hotels[i]);

    for(int i = 0; i<6000396; i++)
    Data.reservation.free(box->list_reservations[i]);


    free(box->list_hotels);
    free(box->list_reservations);
    free(box);
}
Almanac_Reservation * new_reservation_almanac(){
    Almanac_Reservation * a = malloc(sizeof(Almanac_Reservation));
    
        a->list_reservations = malloc(sizeof(Reservation *) * 6000396);
        a->list_hotels = malloc(sizeof(Hotel *) * 10000);

        for(int i = 0; i < 6000396; i++)
            a->list_reservations[i] = NULL;

        for(int i = 0; i < 10000; i++)
            a->list_hotels[i] = NULL;

    return a;
}
void hotel_sort(Almanac_Reservation * box){
    for(int i = 0; i < 10000; i++)
    if(box->list_hotels[i]!=NULL)
    Data.hotel.sort(box->list_hotels[i]);
}
////////////////////////////////////////////////////////


////////////////////////////////////////////////////////
Hotel * almanac_reservations_hotel_getter(Almanac_Reservation * box, char * id){
    int key = hash_hotel(id);

    if(box->list_reservations[key]!=NULL){
        
        Hotel * a = Data.hotel.get.hotel(box->list_hotels[key]);
        return a;
    }
    return NULL;
}
Reservation * almanac_reservations_reservations_getter(Almanac_Reservation * box, char * id){

    int key = hash_reservation(id);
    if(box->list_reservations[key]!=NULL){
        Reservation * a = Data.reservation.copy(box->list_reservations[key]);

        return a;
    }

    return NULL;
}
////////////////////////////////////////////////////////