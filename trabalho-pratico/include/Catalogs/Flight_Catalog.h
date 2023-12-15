#ifndef FLIGHT_CATALOGS_H
#define FLIGHT_CATALOGS_H

typedef struct flight Flight;
typedef struct alm_flight Almanac_Flights;


////////////////////////////////////////////////////////
void insert_FLCAT(Almanac_Flights * box,char * id,char * airline, char * plane_model, char * origin, char * destination, char * schedule_departure_date,char * real_departure_date, char * schedule_arrival_date, char * passengers);
void add_flcatPASSENGER(Almanac_Flights * box,char * id,int x);

void destroy_FLIGHTCAT(Almanac_Flights * box);
Almanac_Flights * new_FLIGHTCAT(int amount);
void remove_FLIGHTCAT(Almanac_Flights * box, char * id);
////////////////////////////////////////////////////////


#endif