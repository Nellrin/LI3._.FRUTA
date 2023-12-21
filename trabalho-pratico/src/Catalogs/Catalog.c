#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../../include/DataStructures/Users.h"
#include "../../include/DataStructures/BTree.h"
#include "../../include/DataStructures/Flights.h"
#include "../../include/DataStructures/Reservations.h"
#include "../../include/DataStructures/FHash.h"
#include "../../include/Catalogs/Catalog.h"
#include "../../include/Catalogs/User_Catalog.h"


////////////////////////////////////////////////////////
typedef struct almanac{
    User_Almanac * user;
    FHash * flight;
    FHash * reservation;
    unsigned int * passenger;
}Almanac;
////////////////////////////////////////////////////////


////////////////////////////////////////////////////////
Almanac * init_almanac(){
    Almanac * a = malloc(sizeof(Almanac));

    a->passenger = malloc(sizeof(unsigned int) * amount_flights);
    a->user = init_user_almanac(amount_users);
    a->flight = fhash_init(amount_flights);
    a->reservation = fhash_init(amount_reservations);

    return a;
}
void free_almanac(Almanac * a){
    free_fhash(a->flight,free_flight);
    free_fhash(a->reservation,free_reservation);
    free_user_almanac(a->user);
    free(a->passenger);

    free(a);
}
////////////////////////////////////////////////////////


////////////////////////////////////////////////////////
void almanac_count_passengers(Almanac *almanac,char * path){

    FILE *file = fopen(path, "r");
    
    char * line = NULL;
    char *flight_id = NULL;
    char *user_id = NULL;
    size_t len = 0;
    
    for(int i = 0; i < amount_flights; i++)
    almanac->passenger[i] = 0;

    while (getline(&line, &len, file) != -1) {

        flight_id = NULL;
        user_id = NULL;


        flight_id = strsep(&line, ";");
        user_id = strsep(&line, ";");


        if(strlen(user_id)>0){
            user_id[strlen(user_id)-1] = '\0';
            if(almanac_get_user_node(almanac,user_id) != NULL){

                if(strlen(flight_id)> 0){
                    almanac->passenger[atoi(flight_id)-1]++;

                }
            }
        }
                if(flight_id!=NULL)
                free(flight_id);
                // if(user_id!=NULL)
                // free(user_id);
        
    }
        // free(user_id);
        // free(flight_id);

            printf("\n\nSAFE\n\n");

            
    // for(int i = 0; i < amount_flights; i++)
    // printf("\n%d",almanac->passenger[i]);


    fclose(file);


    // if(line!=NULL)
    free(line);
}
void almanac_add_passengers(Almanac * almanac, char * user_id, char * flight_id){
    user_almanac_add_flight(almanac->user,user_id,almanac_get_flight(almanac,flight_id));
}
void almanac_add_user(Almanac *almanac,char * id, char *name, char *birth_date, char *sex, char *country_code, short account_status, char *account_creation, char * passport){
    user_almanac_add_user(almanac->user,id, name, birth_date, sex, country_code, account_status, account_creation, passport);
}
void almanac_add_flight(Almanac *almanac,char * id,char * airline, char * plane_model, char * origin, char * destination, char * schedule_departure_date,char * real_departure_date, char * schedule_arrival_date, unsigned int passengers){

    Flight * a = set_flight(id,airline, plane_model, origin, destination, schedule_departure_date,real_departure_date, schedule_arrival_date, passengers);

    fhash_add(almanac->flight,id,a, 0);

}
void almanac_add_reservation(Almanac *almanac,char *id, char *id_hotel, char *user_id, char *hotel_name, char *hotel_stars, char *begin_date, char *end_date, int includes_breakfast, char *rating, char *ppn, char *city_tax){
    
    Reservation * a; 

    if(includes_breakfast == 1)
    a = set_reservation(id, id_hotel, user_id, hotel_name, hotel_stars, begin_date, end_date, "True", rating, ppn, city_tax);

    else    
    a = set_reservation(id, id_hotel, user_id, hotel_name, hotel_stars, begin_date, end_date, "False", rating, ppn, city_tax);

    fhash_add(almanac->reservation,id,(void *)a, 0);
    user_almanac_add_reservation(almanac->user,user_id,a);
}
////////////////////////////////////////////////////////


////////////////////////////////////////////////////////
unsigned int almanac_get_seats(Almanac *almanac, int target){
    return almanac->passenger[target];
}
void * almanac_get_user(Almanac *almanac, char * target){
    return user_almanac_get_individual_user(almanac->user,target);
}
void * almanac_get_prefix(Almanac *almanac){
    return user_almanac_get_prefix(almanac->user);
}
void * almanac_get_user_node(Almanac *almanac, char * target){
    return user_almanac_get_user(almanac->user,target);
}
void * almanac_get_flight(Almanac *almanac, char * target){
    void * flight = fhash_get(almanac->flight,target,0,compare_flight);
    return flight;
}
void * almanac_get_reservation(Almanac *almanac, char * target){
    void * reservation =fhash_get(almanac->reservation,target,0,compare_reservation);
    return reservation;
}


void * almanac_get_user_flights(Almanac * almanac, char * target){
    return user_almanac_use_flights(almanac->user, target);
}
void * almanac_get_user_reservations(Almanac * almanac, char * target){
    return user_almanac_use_reservations(almanac->user, target);
}

void almanac_get_user_reservations_flights(Almanac * almanac, char * target, int * n_flights, int * n_reservations){

    void * x = user_almanac_use_flights(almanac->user,target);
    void * y = user_almanac_use_reservations(almanac->user,target);

    *n_flights = (int) do_something(x,exists);
    *n_reservations = (int) do_something(y,exists);
}
////////////////////////////////////////////////////////