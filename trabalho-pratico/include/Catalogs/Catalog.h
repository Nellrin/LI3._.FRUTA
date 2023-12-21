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
#define amount_flights 200000
#define amount_users 1000000
#define amount_reservations 6000000
#define CURRENT_DATE "2023/10/01"
////////////////////////////////////////////////////////


////////////////////////////////////////////////////////
Almanac * init_almanac();
void free_almanac(Almanac * a);
////////////////////////////////////////////////////////


////////////////////////////////////////////////////////
void almanac_count_passengers(Almanac *almanac,char * path);
void almanac_add_passengers(Almanac * almanac, char * user_id, char * flight_id);
void almanac_add_user(Almanac *almanac,char * id, char *name, char *birth_date, char *sex, char *country_code, short account_status, char *account_creation, char * passport);
void almanac_add_flight(Almanac *almanac,char * id,char * airline, char * plane_model, char * origin, char * destination, char * schedule_departure_date,char * real_departure_date, char * schedule_arrival_date, unsigned int passengers);
void almanac_add_reservation(Almanac *almanac,char *id, char *id_hotel, char *user_id, char *hotel_name, char *hotel_stars, char *begin_date, char *end_date, int includes_breakfast, char *rating, char *ppn, char *city_tax);
////////////////////////////////////////////////////////


////////////////////////////////////////////////////////
unsigned int almanac_get_seats(Almanac *almanac, int target);
void * almanac_get_user_node(Almanac *almanac, char * target);
void * almanac_get_prefix(Almanac *almanac);
void * almanac_get_user(Almanac *almanac, char * target);
void * almanac_get_flight(Almanac *almanac, char * target);
void * almanac_get_reservation(Almanac *almanac, char * target);
void almanac_get_user_reservations_flights(Almanac * almanac, char * target, int * n_flights, int * n_reservations);
void * almanac_get_user_flights(Almanac * almanac, char * target);
void * almanac_get_user_reservations(Almanac * almanac, char * target);
////////////////////////////////////////////////////////


#endif