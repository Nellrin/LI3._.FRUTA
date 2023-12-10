#ifndef FLIGHTS_H
#define FLIGHTS_H

////////////////////////////////////////////////////////
typedef struct flight Flight;
typedef struct String_list SList;
////////////////////////////////////////////////////////

////////////////////////////////////////////////////////
void print_flight(Flight * a);
////////////////////////////////////////////////////////

////////////////////////////////////////////////////////
Flight * new_flight(char * id);
void flight_setter(Flight * a,char * airline, char * plane_model, char * origin, char * destination, char * schedule_departure_date,char * real_departure_date, char * schedule_arrival_date);
void add_passenger(Flight * a, int x);
////////////////////////////////////////////////////////

////////////////////////////////////////////////////////
char * flight_id_getter(Flight * a);
char * flight_airline_getter(Flight * a);
char * flight_plane_model_getter(Flight * a);
char * flight_origin_getter(Flight * a);
char * flight_destination_getter(Flight * a);
char * flight_schedule_departure_date_getter(Flight * a);
char * flight_schedule_arrival_date_getter(Flight * a);
int flight_passengers_getter(Flight * a);
int flight_delay_date_getter(Flight * a);
Flight * flight_flight_getter(Flight * a, int x);
////////////////////////////////////////////////////////

////////////////////////////////////////////////////////
void free_flight(Flight *a);
////////////////////////////////////////////////////////

#endif