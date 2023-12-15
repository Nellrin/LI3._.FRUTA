#ifndef HOTEL_CATALOGS_H
#define HOTEL_CATALOGS_H

typedef struct reservation Reservation;

typedef struct alm_re Almanac_Reservation;


////////////////////////////////////////////////////////
Almanac_Reservation * new_RESCAT(int amount);
void destroy_RESCAT(Almanac_Reservation * box);
void insert_RESCAT(Almanac_Reservation * box,char * id,char * id_hotel, char * user_id, char * hotel_name, char * hotel_stars, char * begin_date, char * end_date, char * includes_breakfast, char * rating, char * ppn, char * city_tax);
////////////////////////////////////////////////////////


#endif