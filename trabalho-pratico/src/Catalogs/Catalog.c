#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../../include/DataStructures/Users.h"
#include "../../include/DataStructures/BTree.h"
#include "../../include/DataStructures/Flights.h"
#include "../../include/DataStructures/Reservations.h"
#include "../../include/DataStructures/FHash.h"
#include "../../include/DataStructures/Calendar.h"

#include "../../include/Catalogs/Catalog.h"
#include "../../include/Catalogs/User_Catalog.h"
#include "../../include/Catalogs/Reservation_Catalog.h"
#include "../../include/Catalogs/Flight_Catalog.h"
#include "../../include/Catalogs/Calendar_Catalog.h"

#include "../../include/Output.h"


////////////////////////////////////////////////////////
typedef struct almanac{
    User_Almanac * user;
    Reservation_Almanac * reservation;
    Flight_Almanac * flight;
    unsigned int * passenger;
    Calendar_Almanac * counter;
}Almanac;
////////////////////////////////////////////////////////


////////////////////////////////////////////////////////
Almanac * init_almanac(int amount_f, int amount_u, int amount_r){
    Almanac * a = malloc(sizeof(Almanac));

    a->passenger = malloc(sizeof(unsigned int) * amount_f);
    a->user = init_user_almanac(amount_u);
    a->reservation = init_reservation_almanac(amount_r);
    a->flight = init_flight_almanac(amount_f);
    a->counter = init_calendar_almanac();

    return a;
}
void free_almanac(Almanac * a){
    if(a!=NULL){
        free_flight_almanac(a->flight);
        free_reservation_almanac(a->reservation);
        free_user_almanac(a->user);
        free(a->passenger);
        free_calendar_almanac(a->counter);


    
        free(a);
    }
}
////////////////////////////////////////////////////////


////////////////////////////////////////////////////////
Almanac * set_up_almanac(char * path){

    int amount_f = 0;//200000;
    int amount_u = 0;//100000;
    int amount_r = 0;// 600000;



    char * flights = malloc(sizeof(char) * 256);
    snprintf(flights, 256, "%s/flights.csv",path);

    FILE *file = create_file(flights, "r");

    char * line = NULL;
    char *flight_id = NULL;
    char *user_id = NULL;
    size_t len = 0;

    while (getline(&line, &len, file) != -1)
    amount_f++;

    fclose(file);

    amount_u = 4 * amount_f; 
    amount_r = 6 * amount_u; 

    Almanac * almanac = init_almanac(amount_f,amount_u,amount_r);


    for(int i = 0; i < amount_f; i++)
    almanac->passenger[i] = 0;


    free(line);
    free(flights);

    return almanac;
}

void almanac_count_passengers(Almanac *almanac,char * path){

    char * passengers = malloc(sizeof(char) * 256);
    snprintf(passengers, 256, "%s/passengers.csv",path);

        
    char * line = NULL;
    char *flight_id = NULL;
    char *user_id = NULL;
    size_t len = 0;
    


    FILE * file = create_file(passengers, "r");


    while (getline(&line, &len, file) != -1) {

        flight_id = NULL;
        user_id = NULL;


        flight_id = strsep(&line, ";");
        user_id = strsep(&line, ";");


        if(strlen(user_id)>0){
            user_id[strlen(user_id)-1] = '\0';
            if(almanac_get_user_node(almanac,user_id) != NULL){

                if(strlen(flight_id)> 0){
                    (almanac)->passenger[atoi(flight_id)-1]++;

                }
            }
        }
        
                if(flight_id!=NULL)
                free(flight_id);        
    }

    free(passengers);
    free(line);
    fclose(file);
}
void almanac_add_passengers(Almanac * almanac, char * user_id, char * flight_id){
    user_almanac_add_flight(almanac->user,user_id,almanac_get_flight(almanac,flight_id));   
}
void almanac_add_user(Almanac *almanac,char * id, char *name, char *birth_date, char *sex, char *country_code, short account_status, char *account_creation, char * passport){
    user_almanac_add_user(almanac->user,id, name, birth_date, sex, country_code, account_status, account_creation, passport);
    
    calendar_add(almanac->counter,account_creation,1,date_add_users);
}
void almanac_add_flight(Almanac *almanac,char * id,char * airline, char * plane_model, char * origin, char * destination, char * schedule_departure_date,char * real_departure_date, char * schedule_arrival_date, unsigned int passengers){

    flight_almanac_add_flight(almanac->flight,id,airline, plane_model, origin, destination, schedule_departure_date,real_departure_date, schedule_arrival_date, passengers);

    calendar_add(almanac->counter,schedule_departure_date,1,date_add_flights);
    calendar_add(almanac->counter,schedule_departure_date,passengers,date_add_passengers);


}
void almanac_add_reservation(Almanac *almanac,char *id, char *id_hotel, char *user_id, char *hotel_name, char *hotel_stars, char *begin_date, char *end_date, int includes_breakfast, char *rating, char *ppn, char *city_tax){
    
    if(includes_breakfast == 1)
    reservation_almanac_add_reservation(almanac->reservation, almanac->user,id, id_hotel, user_id, hotel_name, hotel_stars, begin_date, end_date, "True", rating, ppn, city_tax);

    else    
    reservation_almanac_add_reservation(almanac->reservation, almanac->user,id, id_hotel, user_id, hotel_name, hotel_stars, begin_date, end_date, "False", rating, ppn, city_tax);

    calendar_add(almanac->counter,begin_date,1,date_add_reservations);

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
    void * flight = flight_almanac_get_flight(almanac->flight,target);
    return flight;
}
void * almanac_get_airport(Almanac *almanac, char * target){
    void * airport = flight_almanac_get_airport_direct(almanac->flight,target);
    return airport;
}
void * almanac_get_airport_flights(Almanac *almanac, char * target){
    void * airport = flight_almanac_get_airport_flights(almanac->flight,target);
    return airport;
}
void ** almanac_get_all_airport(Almanac *almanac, int * amount){
    void ** airports = flight_almanac_get_airport_general(almanac->flight,amount);
    return airports;
}
void almanac_get_airport_delays(Almanac *almanac, char *** list_of_names, int ** list_of_med, int * amount){
    flight_almanac_get_airport_delays(almanac->flight,list_of_names,list_of_med,amount);
}
void almanac_get_airport_year(Almanac *almanac,char * target, char *** list_of_names, int ** list_of_passengers, int * amount){
    flight_almanac_get_airport_years(almanac->flight,target,list_of_names,list_of_passengers,amount);
}
void almanac_sort_flight_delays(Almanac * almanac){
    flight_almanac_sort_airport_delays(almanac->flight);
}

void * almanac_get_reservation(Almanac *almanac, char * target){
    void * reservation = reservation_almanac_get_reservation(almanac->reservation,target);
    return reservation;
}
void * almanac_get_hotel(Almanac *almanac, char * target){
    void * hotel = reservation_almanac_get_hotel(almanac->reservation,target);
    return hotel;
}
int almanac_get_hotel_num_res(Almanac *almanac, char * target){
    int hotel = reservation_almanac_get_hotel_num_res(almanac->reservation,target);
    return hotel;
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
void almanac_get_dates(Almanac * almanac,char ** arguments,int num_arguments,int * amount,int ** year, int ** user, int ** fli, int ** res,int ** pas, int ** uni_pas){

    calendar_get(almanac->counter,arguments,num_arguments,amount,year, user, fli, res,pas, uni_pas);

}
////////////////////////////////////////////////////////