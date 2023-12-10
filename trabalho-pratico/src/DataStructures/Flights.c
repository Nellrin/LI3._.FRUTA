#include "../../include/DataStructures/Flights.h"
#include "../../include/DataStructures/SLists.h"
#include "../../include/Utilities.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

typedef struct flight {
    char *id;
    char *airline;
    char *plane_model;
    char *origin;
    char *destination;
    char *schedule_departure_date;
    char *schedule_arrival_date;
    int delay;

    int passengers;
} Flight;
////////////////////////////////////////////////////////
void print_flight(Flight * a){
    
    printf("\n----------------------------------------------------\n");
    printf("[ID]: %s\n",a->id);
    printf("[AIRLINE]: %s\n",a->airline);
    printf("[PLANE MODEL]: %s\n",a->plane_model);
    printf("[ORIGIN]: %s\n",a->origin);
    printf("[DESTINATION]: %s\n",a->destination);
    printf("[SCHEDULE DEPARTURE DATE]: %s\n",a->schedule_departure_date);
    printf("[SCHEDULE ARRIVAL DATE]: %s\n",a->schedule_arrival_date);
    printf("[DELAY]: %d\n\n",a->delay);
    printf("[PASSENGERS]: %d\n\n",a->passengers);


    printf("----------------------------------------------------\n");
}
////////////////////////////////////////////////////////
Flight * new_flight(char * id){
    Flight * a = malloc(sizeof(Flight));
    a->id = strdup(id);
    a->delay = 0;
    a->passengers = 1;

    return a;
}
void add_passenger(Flight * a, int x){
    a->passengers+= x;
}
void flight_setter(Flight * a,char * airline, char * plane_model, char * origin, char * destination, char * schedule_departure_date,char * real_departure_date, char * schedule_arrival_date){    
    initialize_utilities();
    
    a->airline = strdup(airline);
    a->plane_model = strdup(plane_model);
    a->origin = strdup(origin);
    a->destination = strdup(destination);
    a->schedule_departure_date = strdup(schedule_departure_date);
    a->schedule_arrival_date = strdup(schedule_arrival_date);

    a->delay = Util.time_diff("%d/%d/%d %d:%d:%d",schedule_departure_date,real_departure_date);
}
////////////////////////////////////////////////////////
char * flight_id_getter(Flight * a){
    char * id = strdup(a->id);

    return id;
}
char * flight_airline_getter(Flight * a){
    char * airline = strdup(a->airline);

    return airline;
}
char * flight_plane_model_getter(Flight * a){
    char * plane_model = strdup(a->plane_model);

    return plane_model;
}
char * flight_origin_getter(Flight * a){
    char * origin = strdup(a->origin);

    return origin;
}
char * flight_destination_getter(Flight * a){
    char * destination = strdup(a->destination);

    return destination;
}
char * flight_schedule_departure_date_getter(Flight * a){
    char * schedule_departure_date = strdup(a->schedule_departure_date);

    return schedule_departure_date;
}
char * flight_schedule_arrival_date_getter(Flight * a){
    char * schedule_arrival_date = strdup(a->schedule_arrival_date);

    return schedule_arrival_date;
}
int flight_passengers_getter(Flight * a){
    int x = a->passengers;

    return x;
}
int flight_delay_date_getter(Flight * a){
    int delay = a->delay;

    return delay;
}
Flight * flight_flight_getter(Flight * a, int num){
    
    if(a != NULL){

        Flight * x = malloc(sizeof(Flight));
        x->id = flight_id_getter(a);
        x->passengers = a->passengers;
        
        if(num){
            x->airline = flight_airline_getter(a);
            x->delay = a->delay;
            x->destination = flight_destination_getter(a);
            x->origin = flight_origin_getter(a);
            x->plane_model = flight_plane_model_getter(a);
            x->schedule_arrival_date = flight_schedule_arrival_date_getter(a);
            x->schedule_departure_date = flight_schedule_departure_date_getter(a);
        }
    
        return x;
    }

    return NULL;
}
////////////////////////////////////////////////////////
void free_flight(Flight *a) {
    if (a != NULL) {
        free(a->id);
        if(a->airline!=NULL){
            free(a->airline);
            free(a->plane_model);
            free(a->origin);
            free(a->destination);
            free(a->schedule_departure_date);
            free(a->schedule_arrival_date);
        }

        free(a);
    }
}
////////////////////////////////////////////////////////
