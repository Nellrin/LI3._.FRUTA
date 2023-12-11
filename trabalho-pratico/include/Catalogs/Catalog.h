#ifndef CATALOGS_H
#define CATALOGS_H

////////////////////////////////////////////////////////
typedef struct String_list SList;
typedef struct user User;
typedef struct almanac Almanac;
////////////////////////////////////////////////////////

////////////////////////////////////////////////////////
void almanac_insert_user(Almanac * box,User * a);
void destroy_almanac(Almanac * box);
Almanac * new_almanac();
void user_prefix_sort(Almanac * box);
////////////////////////////////////////////////////////
////////////////////////////////////////////////////////
SList * almanac_prefix_getter(Almanac * box);
User * almanac_user_getter(Almanac * box, char * id);
////////////////////////////////////////////////////////
////////////////////////////////////////////////////////
void almanac_add_reservation_of_user(Almanac * box, char * id, char * hotel_id, char * date, float money);
void almanac_add_flight_to_user(Almanac * box, char * id, char * flight, char * date);
void almanac_remove_flight_of_users(Almanac * box, char * id, char * flight);
////////////////////////////////////////////////////////






////////////////////////////////////////////////////////
void almanac_add_passenger(Almanac * box, char * id ,char * x);
void almanac_insert_flight(Almanac * box,Flight * a);
void almanac_complement_flight(Almanac * box,Flight * a);
void almanac_airport_sort(Almanac * box);
void almanac_remove_flight_catalog(Almanac * box, char * id);
////////////////////////////////////////////////////////
////////////////////////////////////////////////////////
Airport * almanac_Almanac_airport_getter(Almanac * box, char * id);
Flight * almanac_Almanac_flight_getter(Almanac * box, char * id,int x);
SList * almanac_Almanac_passengers_getter(Almanac * box, int x);
////////////////////////////////////////////////////////






////////////////////////////////////////////////////////
void almanac_insert_reservation(Almanac * box,Reservation * a, char * ppn, char * rating);
void almanac_hotel_sort(Almanac * box);
////////////////////////////////////////////////////////
////////////////////////////////////////////////////////
Hotel * almanac_Almanac_hotel_getter(Almanac * box, char * id);
Reservation * almanac_Almanac_reservations_getter(Almanac * box, char * id);
////////////////////////////////////////////////////////


#endif