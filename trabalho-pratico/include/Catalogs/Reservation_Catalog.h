#ifndef HOTEL_CATALOGS_H
#define HOTELmoinenvalo_CATALOGS_H

typedef struct String_list SList;
typedef struct reservation Reservation;
typedef struct hotel Hotel;

typedef struct almanac_reservation Almanac_Reservation;


////////////////////////////////////////////////////////
void insert_reservation(Almanac_Reservation * box,Reservation * a, char * ppn, char * rating);
void destroy_reservation_almanac(Almanac_Reservation * box);
Almanac_Reservation * new_reservation_almanac();
void hotel_sort(Almanac_Reservation * box);
////////////////////////////////////////////////////////


////////////////////////////////////////////////////////
Hotel * almanac_reservations_hotel_getter(Almanac_Reservation * box, char * id);
Reservation * almanac_reservations_reservations_getter(Almanac_Reservation * box, char * id);
////////////////////////////////////////////////////////

#endif