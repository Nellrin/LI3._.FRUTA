#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../../include/DataStructures/Users.h"
#include "../../include/DataStructures/Flights.h"
#include "../../include/DataStructures/Reservations.h"
#include "../../include/DataStructures/FHash.h"
#include "../../include/Catalogs/Catalog.h"


////////////////////////////////////////////////////////
typedef struct almanac{
    FHash * user;
    FHash * flight;
    FHash * reservation;
    unsigned int * passenger;
}Almanac;
////////////////////////////////////////////////////////


////////////////////////////////////////////////////////
Almanac * init_almanac(){
    Almanac * a = malloc(sizeof(Almanac));

    a->passenger = malloc(sizeof(unsigned int) * amount_flights);
    a->user = fhash_init(amount_users);
    a->flight = fhash_init(amount_flights);
    a->reservation = fhash_init(amount_reservations);

    return a;
}
void free_almanac(Almanac * a){
    free_fhash(a->flight,free_flight);
    free_fhash(a->reservation,free_reservation);
    free_fhash(a->user,free_user);
    free(a->passenger);

    free(a);
}
////////////////////////////////////////////////////////


////////////////////////////////////////////////////////
void nulls(Almanac * a, char * string){
    check_nulls(a->user);
    check_nulls(a->flight);
    check_nulls(a->reservation);
}

void almanac_add_passengers(Almanac *almanac,char * path){

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
            if(almanac_get_user(almanac,user_id) != NULL){

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

            
    for(int i = 0; i < amount_flights; i++)
    printf("\n%d",almanac->passenger[i]);


    fclose(file);


    // if(line!=NULL)
    free(line);
}
void almanac_add_user(Almanac *almanac,char * id, char *name, char *birth_date, char *sex, char *country_code, char *account_status, char *account_creation){
    User * a = set_user(id, name, birth_date, sex, country_code, account_status, account_creation);
    
    fhash_add(almanac->user,id,(void *)a, 1);
}
void almanac_add_flight(Almanac *almanac,char * id,char * airline, char * plane_model, char * origin, char * destination, char * schedule_departure_date,char * real_departure_date, char * schedule_arrival_date, char * passengers){

    Flight * a = set_flight(id,airline, plane_model, origin, destination, schedule_departure_date,real_departure_date, schedule_arrival_date, passengers);

    fhash_add(almanac->flight,id,a, 0);
}
void almanac_add_reservation(Almanac *almanac,char *id, char *id_hotel, char *user_id, char *hotel_name, char *hotel_stars, char *begin_date, char *end_date, char *includes_breakfast, char *rating, char *ppn, char *city_tax){
    
    Reservation * a = set_reservation(id, id_hotel, user_id, hotel_name, hotel_stars, begin_date, end_date, includes_breakfast, rating, ppn, city_tax);
    
    fhash_add(almanac->reservation,id,(void *)a, 0);
}
////////////////////////////////////////////////////////


////////////////////////////////////////////////////////
unsigned int almanac_get_seats(Almanac *almanac, int target){
    return almanac->passenger[target];
}
void * almanac_get_user(Almanac *almanac, char * target){
    return fhash_get(almanac->user,target,1,compare_user);
}
void * almanac_get_flight(Almanac *almanac, char * target){
    void * flight = fhash_get(almanac->flight,target,0,compare_flight);
    return flight;
}
void * almanac_get_reservation(Almanac *almanac, char * target){
    void * reservation =fhash_get(almanac->reservation,target,0,compare_reservation);
    return reservation;
}
////////////////////////////////////////////////////////