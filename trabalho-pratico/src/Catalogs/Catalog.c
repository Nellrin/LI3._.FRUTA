#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../../include/Catalogs/User_Catalog.h"
#include "../../include/Catalogs/Flight_Catalog.h"
#include "../../include/Catalogs/Reservation_Catalog.h"
#include "../../include/Catalogs/Catalog.h"
#include "../../include/DataStructures/Functions.h"


typedef struct almanac{
    Almanac_Users * user;
    Almanac_Flights * flight;
    Almanac_Reservation * reservation;
}Almanac;
////////////////////////////////////////////////////////


////////////////////////////////////////////////////////
void almanac_insert_user(Almanac * box,User * a){
    insert_user(box->user,a);
}
void destroy_almanac(Almanac * box){
    destroy_user_almanac(box->user);
    destroy_flight_almanac(box->flight);
    destroy_reservation_almanac(box->reservation);
    free(box);
}
Almanac * new_almanac(){
    Almanac * a = malloc(sizeof(Almanac));
    
    a->user = new_user_almanac();
    a->flight = new_flight_almanac();
    a->reservation = new_reservation_almanac();

    return a;
}
void user_prefix_sort(Almanac * box){
    prefix_sort(box->user);
}
void user_user_sort(Almanac * box){
    user_sort(box->user);
}
////////////////////////////////////////////////////////
////////////////////////////////////////////////////////
SList * almanac_prefix_getter(Almanac * box){
    SList * a = almanac_users_prefix_getter(box->user);
    return a;
}
User * almanac_user_getter(Almanac * box, char * id){

    User * a = almanac_users_user_getter(box->user,id);

    return a;
}
////////////////////////////////////////////////////////
////////////////////////////////////////////////////////
void almanac_add_reservation_of_user(Almanac * box, char * id, char * hotel_id, char * date, float money){
        
    almanac_users_add_reservation(box->user,id,hotel_id,date,money);

}
void almanac_add_flight_to_user(Almanac * box, char * id, char * flight, char * date){
    
    almanac_users_add_flight(box->user,id,flight,date);
    
}
void almanac_remove_flight_of_users(Almanac * box, char * id, char * flight){
    
    almanac_users_remove_flight(box->user,id,flight);
    
}
////////////////////////////////////////////////////////






////////////////////////////////////////////////////////
void almanac_add_passenger(Almanac * box, char * id ,char * x){
    catalog_add_passenger(box->flight,id,x);
}
void almanac_insert_flight(Almanac * box,Flight * a){
    insert_flight(box->flight,a);
}
void almanac_complement_flight(Almanac * box,Flight * a){
    complement_flight(box->flight,a);
}
void almanac_airport_sort(Almanac * box){
    airport_sort(box->flight);
}
void almanac_remove_flight_catalog(Almanac * box, char * id){
    remove_flight_catalog(box->flight,id);
}
////////////////////////////////////////////////////////
////////////////////////////////////////////////////////
Airport * almanac_Almanac_airport_getter(Almanac * box, char * id){
    Airport * a = almanac_flights_airport_getter(box->flight,id);
    
    return a;
}
Flight * almanac_Almanac_flight_getter(Almanac * box, char * id, int x){
    Flight * a = almanac_flights_flight_getter(box->flight,id,x);

    return a;
}
SList * almanac_Almanac_passengers_getter(Almanac * box, int x){
    SList * a = almanac_flights_passengers_getter(box->flight,x);
}
////////////////////////////////////////////////////////


////////////////////////////////////////////////////////
void almanac_insert_reservation(Almanac * box,Reservation * a, char * ppn, char * rating){
    insert_reservation(box->reservation,a,ppn,rating);
}
void almanac_hotel_sort(Almanac * box){
    hotel_sort(box->reservation);
}
////////////////////////////////////////////////////////
////////////////////////////////////////////////////////
Hotel * almanac_Almanac_hotel_getter(Almanac * box, char * id){
    Hotel * a = almanac_reservations_hotel_getter(box->reservation,id);
    
    return a;
}
Reservation * almanac_Almanac_reservations_getter(Almanac * box, char * id){
    Reservation * a = almanac_reservations_reservations_getter(box->reservation,id);

    return a;
}
////////////////////////////////////////////////////////


void sort_almanac(Almanac * box){
    almanac_airport_sort(box);
    user_prefix_sort(box);
    user_user_sort(box);
    destroy_passengers_almanac(box->flight);
}