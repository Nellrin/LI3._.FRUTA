#include "../../include/DataStructures/Flights.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
////////////////////////////////////////////////////////


////////////////////////////////////////////////////////
struct flight {
    char *id;
    char *airline;
    char *plane_model;
    char *origin;
    char *destination;
    char *schedule_departure_date;
    char *real_departure_date;
    char *schedule_arrival_date;

    int passengers;
};
////////////////////////////////////////////////////////


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
    printf("[PASSENGERS]: %d\n\n",a->passengers);


    printf("----------------------------------------------------\n");
}
////////////////////////////////////////////////////////


////////////////////////////////////////////////////////
void add_flightPASSENGER(Flight * a, int x){
    a->passengers = x;
}
Flight * set_flight(char * id,char * airline, char * plane_model, char * origin, char * destination, char * schedule_departure_date,char * real_departure_date, char * schedule_arrival_date, unsigned int passengers){    
    Flight * a = malloc(sizeof(Flight));
    
    a->id = strdup(id);
    a->airline = strdup(airline);
    a->plane_model = strdup(plane_model);
    a->origin = strdup(origin);
    a->destination = strdup(destination);
    a->schedule_departure_date = strdup(schedule_departure_date);
    a->schedule_arrival_date = strdup(schedule_arrival_date);
    a->real_departure_date = strdup(real_departure_date);

    a->passengers = (passengers);

    return a;

}
////////////////////////////////////////////////////////


////////////////////////////////////////////////////////
char * get_flightID(Flight * a){
    char * id = strdup(a->id);

    return id;
}
char * get_flightAIRLINE(Flight * a){
    char * airline = strdup(a->airline);

    return airline;
}
char * get_flightMODEL(Flight * a){
    char * plane_model = strdup(a->plane_model);

    return plane_model;
}
char * get_flightORIGIN(Flight * a){
    char * origin = strdup(a->origin);

    return origin;
}
char * get_flightDESTINATION(Flight * a){
    char * destination = strdup(a->destination);

    return destination;
}
char * get_flightSDEPARTURE(Flight * a){
    char * schedule_departure_date = strdup(a->schedule_departure_date);

    return schedule_departure_date;
}
char * get_flightSARRIVAL(Flight * a){
    char * schedule_arrival_date = strdup(a->schedule_arrival_date);

    return schedule_arrival_date;
}
char * get_flightRDEPARTURE(Flight * a){
    char * real_departure = strdup(a->real_departure_date);

    return real_departure;
}
int get_flightPASSENGERS(Flight * a){
    int x = a->passengers;

    return x;
}
////////////////////////////////////////////////////////


////////////////////////////////////////////////////////
int compare_flight(const char *id, const void *info){
    const Flight *flight = (const Flight *)info;
    return (strcmp(id, flight->id) == 0);
}
int compare_flight_date(const void *a, const void *b){
    const Flight *flightA = (const Flight *)a;
    const Flight *flightB = (const Flight *)b;
    
    // Compare flight numbers (assuming flightNumber is a string)
    return strcmp(flightA->schedule_departure_date, flightB->schedule_departure_date);
}
////////////////////////////////////////////////////////


////////////////////////////////////////////////////////
void free_flight(void  * flight){

    if (flight != NULL) {

    Flight *a = (Flight *)flight;

        free(a->id);
        
            free(a->airline);
            free(a->plane_model);
            free(a->origin);
            free(a->destination);
            free(a->schedule_departure_date);
            free(a->schedule_arrival_date);
            free(a->real_departure_date);
        
        free(a);
    }
}
////////////////////////////////////////////////////////
