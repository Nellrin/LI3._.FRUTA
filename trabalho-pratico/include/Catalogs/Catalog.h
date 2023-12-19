#ifndef CATALOGS_H
#define CATALOGS_H
////////////////////////////////////////////////////////


////////////////////////////////////////////////////////
typedef struct user User;
typedef struct flight Flight;
typedef struct reservation Reservation;
typedef struct h FHash;

typedef struct almanac Almanac;
////////////////////////////////////////
#define amount_flights 2000
#define amount_users 10000
#define amount_reservations 60000
////////////////////////////////////////////////////////


////////////////////////////////////////////////////////
Almanac * init_almanac();
void free_almanac(Almanac * a);
////////////////////////////////////////////////////////


////////////////////////////////////////////////////////
void nulls(Almanac * a, char * string);
void almanac_add_passengers(Almanac *almanac,char * path);
void almanac_add_user(Almanac *almanac,char * id, char *name, char *birth_date, char *sex, char *country_code, char *account_status, char *account_creation);
void almanac_add_flight(Almanac *almanac,char * id,char * airline, char * plane_model, char * origin, char * destination, char * schedule_departure_date,char * real_departure_date, char * schedule_arrival_date, unsigned int passengers);
void almanac_add_reservation(Almanac *almanac,char *id, char *id_hotel, char *user_id, char *hotel_name, char *hotel_stars, char *begin_date, char *end_date, int includes_breakfast, char *rating, char *ppn, char *city_tax);
////////////////////////////////////////////////////////


////////////////////////////////////////////////////////
unsigned int almanac_get_seats(Almanac *almanac, int target);
void * almanac_get_user(Almanac *almanac, char * target);
void * almanac_get_flight(Almanac *almanac, char * target);
void * almanac_get_reservation(Almanac *almanac, char * target);
////////////////////////////////////////////////////////


#endif