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


////////////////////////////////////////////////////////
typedef struct almanac{
    User_Almanac * user;
    Reservation_Almanac * reservation;
    Flight_Almanac * flight;

    int * passenger;
    int valid_passengers_amount;
    int valid_passengers_start;
    int valid_passengers_id;
    int * valid_passengers_list;
    
    Calendar_Almanac * counter;
}Almanac;
////////////////////////////////////////////////////////


////////////////////////////////////////////////////////
static Almanac * init_almanac(int amount_f, int amount_u, int amount_r, int amount_p){
    Almanac * a = malloc(sizeof(Almanac));

    a->passenger = malloc(sizeof(int) * amount_f);
    a->valid_passengers_list = malloc(sizeof(int) * amount_p);

    for(int i = 0; i < amount_p; i++)
        a->valid_passengers_list[i] = 0;

    for(int i = 0; i < amount_f; i++)
        a->passenger[i] = 0;

    a->valid_passengers_id = 0;
    a->valid_passengers_amount = 0;
    a->valid_passengers_start = 0;
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
        free(a->valid_passengers_list);
        free_calendar_almanac(a->counter);
    
        free(a);
    }
}
////////////////////////////////////////////////////////


////////////////////////////////////////////////////////
static int aproximated_amount_of_lines_of_a_file(FILE *file, char * title) {
    int size;

    int start = ftell(file);

    fseek(file, 0, SEEK_END);
    size = ftell(file);
    fseek(file, start, SEEK_SET);

    int length = strlen(title);

    return (size/length);
}

Almanac * set_up_almanac(char * path){

    char * name_f = malloc(sizeof(char) * 256);
    char * name_r = malloc(sizeof(char) * 256);
    char * name_u = malloc(sizeof(char) * 256);
    char * name_p = malloc(sizeof(char) * 256);
    
    
    snprintf(name_f, 256, "%s/flights.csv",path);
    snprintf(name_r, 256, "%s/reservations.csv",path);
    snprintf(name_u, 256, "%s/users.csv",path);
    snprintf(name_p, 256, "%s/passengers.csv",path);

    FILE *file_f = fopen(name_f, "r");
    FILE *file_r = fopen(name_r, "r");
    FILE *file_u = fopen(name_u, "r");
    FILE *file_p = fopen(name_p, "r");

        if(file_f == NULL || file_r == NULL || file_u == NULL || file_p == NULL){
            free(name_f);free(name_r);free(name_u);free(name_p);

            if(file_f != NULL)fclose(file_f);
            if(file_r != NULL)fclose(file_r);
            if(file_u != NULL)fclose(file_u);
            if(file_p != NULL)fclose(file_p);

            printf("\nDiretoria inválida\n\n");
            return NULL;
        }

    int amount_f = aproximated_amount_of_lines_of_a_file(file_f,"id;airline;plane_model;seats;ori;des;schedule_departure_date;schedule_arrival_date;real_departure_date;real_arrival_date");
    int amount_u = aproximated_amount_of_lines_of_a_file(file_u,"id;name;sex;pass;ccid;name;sex;pass;cc");
    int amount_r = aproximated_amount_of_lines_of_a_file(file_r,"id;user;htarsin;end;ppn;breakfast;ratingid;user;htlid;name;stars;tax;begin;end;ppn;breakfast;ratingid;user;htlid;name;stars;tax;begin;end;ppn;breakfast;rating");
    int amount_p = aproximated_amount_of_lines_of_a_file(file_p,"flight_id;user_id");

        printf("\n\nFlights [%d]\nReservations [%d]\nUsers[%d]\n\n",amount_f,amount_r,amount_u);

            free(name_f);free(name_r);free(name_u);free(name_p);
            fclose(file_f);fclose(file_r);fclose(file_u);fclose(file_p);

    return init_almanac(amount_f,amount_u,amount_r,amount_p);

}

void almanac_count_passengers(Almanac *almanac,char * path){

    char * passengers = malloc(sizeof(char) * 256);
    snprintf(passengers, 256, "%s/passengers.csv",path);

        
    char * line = NULL;
    char *flight_id = NULL;
    char *user_id = NULL;
    size_t len = 0;
    


    FILE * file = fopen(passengers, "r");


    for(int i = 0; getline(&line, &len, file) != -1; i++) {

        flight_id = NULL;
        user_id = NULL;


        flight_id = strsep(&line, ";");
        user_id = strsep(&line, ";");


        if(strlen(user_id)>0){
            user_id[strlen(user_id)-1] = '\0';
            if(user_almanac_get_individual_user(almanac->user,user_id) != NULL){

                if(strlen(flight_id)> 0){
                    (almanac)->passenger[atoi(flight_id)-1]++;
                    almanac->valid_passengers_list[almanac->valid_passengers_amount] = i;
                    almanac->valid_passengers_amount++;
                }
                // printf("(%d %d) ",almanac->valid_passengers_list[almanac->valid_passengers_amount-1], almanac->valid_passengers_amount);
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

    const char * sdeparture = get_flightSDEPARTURE(almanac_get_flight(almanac,flight_id));
    char * copy = strdup(sdeparture);
    // sdeparture[strlen(sdeparture)-9] = '\0';

    // int amount = 0;
    // char ** list = user_almanac_get_flights(almanac->user,user_id,&amount);

    calendar_add(almanac->counter,copy,1,is_unique_passenger(almanac->user,user_id,copy),date_add_unique_passengers);

    free(copy);

    // for(int i = 0; i < amount; i++)
    // free(list[i]); 

    // free(list);

    user_almanac_add_flight(almanac->user,
                            user_id,
                            almanac_get_flight(almanac,flight_id),
                            sdeparture); 

}
void almanac_add_user(Almanac *almanac,char * id, char *name, char *birth_date, short sex, char *country_code, short account_status, char *account_creation, char * passport){
    user_almanac_add_user(almanac->user,id, name, birth_date, sex, country_code, account_status, account_creation, passport);
    
    calendar_add(almanac->counter,account_creation,1,0,date_add_users);
}
void almanac_add_flight(Almanac *almanac,char * id,char * airline, char * plane_model, char * origin, char * destination, char * schedule_departure_date,char * real_departure_date, char * schedule_arrival_date, unsigned int passengers){

    flight_almanac_add_flight(almanac->flight,id,airline, plane_model, origin, destination, schedule_departure_date,real_departure_date, schedule_arrival_date, passengers);

    calendar_add(almanac->counter,schedule_departure_date,1,0,date_add_flights);
    calendar_add(almanac->counter,schedule_departure_date,passengers,0,date_add_passengers);


}
void almanac_add_reservation(Almanac *almanac,char *id, short id_hotel, char *user_id, char *hotel_name, short hotel_stars, char *begin_date, char *end_date, short includes_breakfast, short rating, short ppn, short city_tax){
    
    reservation_almanac_add_reservation(almanac->reservation, almanac->user,id, id_hotel, user_id, hotel_name, hotel_stars, begin_date, end_date, includes_breakfast, rating, ppn, city_tax);

    calendar_add(almanac->counter,begin_date,1,0,date_add_reservations);

}
////////////////////////////////////////////////////////


////////////////////////////////////////////////////////
unsigned int almanac_get_seats(Almanac *almanac, int target){
    unsigned int x = almanac->passenger[target];
    return x;
}

int almanac_get_valid_passenger(Almanac *almanac){

    
    if(almanac->valid_passengers_list[almanac->valid_passengers_id] == almanac->valid_passengers_start){
        almanac->valid_passengers_id++;
        almanac->valid_passengers_start++;
    // printf("(%d)[%d] == %d\n",(almanac->valid_passengers_list[almanac->valid_passengers_id]),almanac->valid_passengers_id,almanac->valid_passengers_start);
        return 1;
    }


    almanac->valid_passengers_start++;
    return 0;
}

void * almanac_get_user(Almanac *almanac, char * target){
    return user_almanac_get_individual_user(almanac->user,target);
}
void * almanac_get_prefix(Almanac *almanac){
    return user_almanac_get_prefix(almanac->user);
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
char ** almanac_get_hotel(Almanac *almanac, char * target, int * amount, int argumentos, void (*f)(void *,char ***,int i,int argumentos)){
    return reservation_almanac_get_hotel(almanac->reservation,target,amount,argumentos,f);
}

char ** almanac_get_user_reservations(Almanac * almanac, char * target, int * amount){
    return user_almanac_get_reservations(almanac->user,target,amount);
}
char ** almanac_get_user_flights(Almanac * almanac, char * target, int * amount){
    return user_almanac_get_flights(almanac->user,target,amount);
}


void almanac_get_dates(Almanac * almanac,char ** arguments,int num_arguments,int * amount,int ** year, int ** user, int ** fli, int ** res,int ** pas, int ** uni_pas){
    calendar_get(almanac->counter,arguments,num_arguments,amount,year, user, fli, res,pas, uni_pas);
}
////////////////////////////////////////////////////////