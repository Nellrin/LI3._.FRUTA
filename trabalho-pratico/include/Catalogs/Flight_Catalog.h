#ifndef FLIGHT_CATALOGS_H
#define FLIGHT_CATALOGS_H
////////////////////////////////////////////////////////


////////////////////////////////////////////////////////
typedef struct h FHash;
typedef struct airport Airport;
typedef struct year_of_airport Year_Airport;
// typedef struct btree BTree;


typedef struct f_almanac Flight_Almanac;
////////////////////////////////////////////////////////


////////////////////////////////////////////////////////
Flight_Almanac * init_flight_almanac(int amount);
void free_flight_almanac(Flight_Almanac * a);
////////////////////////////////////////////////////////


////////////////////////////////////////////////////////
void flight_almanac_add_flight(Flight_Almanac *almanac, char * id,char * airline, char * plane_model, char * origin, char * destination, char * schedule_departure_date,char * real_departure_date, char * schedule_arrival_date, unsigned int passengers);
////////////////////////////////////////////////////////


////////////////////////////////////////////////////////
void * flight_almanac_get_flight(Flight_Almanac *almanac, char * target);

void * flight_almanac_get_airport_direct(Flight_Almanac *almanac, char * target);
void * flight_almanac_get_airport_flights(Flight_Almanac *almanac, char * target);

void ** flight_almanac_get_airport_general(Flight_Almanac *almanac, int * amount);
void flight_almanac_sort_airport_delays(Flight_Almanac *almanac);
void flight_almanac_get_airport_delays(Flight_Almanac *almanac, char *** list_of_names, int ** list_of_med, int * amount);
////////////////////////////////////////////////////////

#endif