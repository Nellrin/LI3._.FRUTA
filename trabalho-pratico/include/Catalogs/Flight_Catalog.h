#ifndef FLIGHT_CATALOGS_H
#define FLIGHT_CATALOGS_H

typedef struct String_list SList;
typedef struct flight Flight;
typedef struct airport Airport;

typedef struct almanac_flight Almanac_Flights;


////////////////////////////////////////////////////////
void catalog_add_passenger(Almanac_Flights * box, char * user ,char * flight);
void insert_flight(Almanac_Flights * box,Flight * a);
void complement_flight(Almanac_Flights * box,Flight * a);
void destroy_flight_almanac(Almanac_Flights * box);
Almanac_Flights * new_flight_almanac();
void airport_sort(Almanac_Flights * box);
void remove_flight_catalog(Almanac_Flights * box, char * id);
////////////////////////////////////////////////////////


////////////////////////////////////////////////////////
Airport * almanac_flights_airport_getter(Almanac_Flights * box, char * id);
SList * almanac_flights_passengers_getter(Almanac_Flights * box, int x);
Flight * almanac_flights_flight_getter(Almanac_Flights * box, char * id, int x);
////////////////////////////////////////////////////////

#endif