#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// #include <glib.h>

#include "../../include/Catalogs/Flight_Catalog.h"
#include "../../include/DataStructures/Flights.h"
#include "../../include/DataStructures/Functions.h"


typedef struct almanac_flight{
    Flight ** list_flights;
    Airport ** list_airports;
    SList ** passengers; 
}Almanac_Flights;

////////////////////////////////////////////////////////
static int hash_flight(const char *str) {
    int res = atoi(str);

    return res;
}
static int hash_airport(const char *str) {
    
    unsigned long hash = 1;
    int c;

    while ((c = *str++)) {
        hash = ((hash << 5) + hash) + c; // hash * 33 + c
    }

    return (hash%10000);
}
static int airport_finder(Almanac_Flights * box, const char *str){
    int key = hash_airport(str);

    char * new_id = Data.airport.get.id(box->list_airports[key]);
    for(int i = 0; strcmp(new_id,str)!=0; i++){
        free(new_id);

            if(i >500)
            return -1;

        key = (key + 1) % 10000;
        new_id = Data.airport.get.id(box->list_airports[key]);
    }

    free(new_id);
    return key;
}
static int airport_key_finder(Almanac_Flights * box, char * id){
    int key = hash_airport(id);

    char * new_id = Data.airport.get.id(box->list_airports[key]);
    for(int i = 0; strcmp(new_id,id)!=0; i++){
        free(new_id);

            if(i >500)
            return -1;

        key = (key + 1) % 10000;
        new_id = Data.airport.get.id(box->list_airports[key]);
    }

    free(new_id);
    return key;
}
static void insert_airport(Almanac_Flights * box,Flight * a){

    char * origin = Data.flight.get.origin(a);

    int key = airport_key_finder(box,origin);

    if(key!=-1)
    Data.airport.add_flight(box->list_airports[key],a);

    else{
        Airport * x = Data.airport.set(a);
        key = hash_airport(origin);

        box->list_airports[key] = x;
    }

    free(origin);
}
////////////////////////////////////////////////////////


////////////////////////////////////////////////////////
void catalog_add_passenger(Almanac_Flights * box, char * user ,char * flight){
    int key = hash_flight(flight);
    Data.slist.insert.F(box->passengers[key-1],user,flight);
}
void insert_flight(Almanac_Flights * box,Flight * a){
    char * id = Data.flight.get.id(a);
    int key = hash_flight(id);

    box->list_flights[key] = a;

    free(id);
}
void complement_flight(Almanac_Flights * box,Flight * a){
    char * id = Data.flight.get.id(a);
    int key = hash_flight(id);
    int passengers = Data.flight.get.passengers(box->list_flights[key]);

    free(box->list_flights[key]);
    box->list_flights[key] = a;

    Data.flight.add_passenger(box->list_flights[key],passengers);

    insert_airport(box,box->list_flights[key]);
    free(id);
}
void destroy_flight_almanac(Almanac_Flights * box){
    for(int i = 0; i<200000; i++){
        Data.flight.free(box->list_flights[i]);
    // if(box->list_airports[i]!=NULL)
        Data.airport.free(box->list_airports[i]);
        Data.slist.free(box->passengers[i]);
    }


    free(box->passengers);
    free(box->list_airports);
    free(box->list_flights);

    free(box);
}
Almanac_Flights * new_flight_almanac(){
    Almanac_Flights * a = malloc(sizeof(Almanac_Flights));
    
        a->list_airports = malloc(sizeof(Airport *) * 200000);
        a->list_flights = malloc(sizeof(Flight *) * 200000);
        a->passengers = malloc(sizeof(SList *) * 200000);

        for(int i = 0; i < 200000; i++){
            a->passengers[i] = Data.slist.set();
            a->list_flights[i] = NULL;
            a->list_airports[i] = NULL;
        }

    return a;
}
void airport_sort(Almanac_Flights * box){
    for(int i = 0; i < 200000; i++)
    if(box->list_airports[i]!=NULL)
    Data.airport.sort(box->list_airports[i]);
}
void remove_flight_catalog(Almanac_Flights * box, char * id){
    int key = hash_flight(id);
    
    Data.flight.free(box->list_flights[key]);
    box->list_flights[key] = NULL;
}
////////////////////////////////////////////////////////


////////////////////////////////////////////////////////
Airport * almanac_flights_airport_getter(Almanac_Flights * box, char * id){
    int key = airport_finder(box,id);

    Airport * a = Data.airport.get.airport(box->list_airports[key]);
    return a;
}
Flight * almanac_flights_flight_getter(Almanac_Flights * box, char * id, int x){

    int key = hash_flight(id);
    if(box->list_flights[key]!=NULL){
        Flight * a = Data.flight.get.flight(box->list_flights[key],x);

        return a;
    }

    return NULL;
}
SList * almanac_flights_passengers_getter(Almanac_Flights * box, int x){

    SList * a = Data.slist.set();
    Data.slist.copy(a,box->passengers[x-1]);

    return a;
}
////////////////////////////////////////////////////////