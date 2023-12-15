#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// #include <glib.h>

#include "../../include/Catalogs/Flight_Catalog.h"
#include "../../include/DataStructures/Flights.h"


struct alm_flight{
    Flight ** list_flights;
    int amount
};

////////////////////////////////////////////////////////
static int hash_flight(const char *str) {
    int res = atoi(str) - 1;

    return res;
}
////////////////////////////////////////////////////////
    //pode ser preciso adaptar isto para aceitar vários datasets
  
////////////////////////////////////////////////////////
void insert_FLCAT(Almanac_Flights * box,char * id,char * airline, char * plane_model, char * origin, char * destination, char * schedule_departure_date,char * real_departure_date, char * schedule_arrival_date, char * passengers){

    Flight * a = set_flight(id,airline,plane_model,origin,destination,schedule_departure_date,real_departure_date,schedule_arrival_date,passengers);

    int key = hash_flight(id);

    box->list_flights[key] = a;

}
void add_flcatPASSENGER(Almanac_Flights * box,char * id,int x){

    int key = hash_flight(id);

    add_flightPASSENGER(box->list_flights[key],x);

}

void destroy_FLIGHTCAT(Almanac_Flights * box){
    for(int i = 0; i<box->amount; i++)
        free_flight(box->list_flights[i]);


    free(box->list_flights);

    free(box);
}
Almanac_Flights * new_FLIGHTCAT(int amount){
    Almanac_Flights * a = malloc(sizeof(Almanac_Flights));
    
        a->list_flights = malloc(sizeof(Flight *) * amount);

        for(int i = 0; i < amount; i++)
        a->list_flights[i] = NULL;

        a->amount = amount;

    return a;
}
void remove_FLIGHTCAT(Almanac_Flights * box, char * id){
    int key = hash_flight(id);
    
    free_flight(box->list_flights[key]);
    box->list_flights[key] = NULL;
}
////////////////////////////////////////////////////////