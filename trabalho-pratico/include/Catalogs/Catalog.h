#ifndef CATALOGS_H
#define CATALOGS_H
////////////////////////////////////////////////////////


////////////////////////////////////////////////////////
typedef struct user User;
typedef struct flight Flight;
typedef struct h FHash;

typedef struct almanac Almanac;
////////////////////////////////////////
#define CURRENT_DATE "2023/10/01"
////////////////////////////////////////////////////////


////////////////////////////////////////////////////////
// Almanac * init_almanac(int amount_f, int amount_u, int amount_r);
Almanac * set_up_almanac(char * path);
void free_almanac(Almanac * a);
////////////////////////////////////////////////////////


////////////////////////////////////////////////////////
void almanac_count_passengers(Almanac *almanac,char * path);
void almanac_add_passengers(Almanac * almanac, char * user_id, char * flight_id);
void almanac_add_user(Almanac *almanac,char * id, char *name, char *birth_date, short sex, char *country_code, short account_status, char *account_creation, char * passport);
void almanac_add_flight(Almanac *almanac,char * id,char * airline, char * plane_model, char * origin, char * destination, char * schedule_departure_date,char * real_departure_date, char * schedule_arrival_date, unsigned int passengers);
void almanac_add_reservation(Almanac *almanac,char *id, short id_hotel, char *user_id, char *hotel_name, short hotel_stars, char *begin_date, char *end_date, short includes_breakfast, short rating, short ppn, short city_tax);
////////////////////////////////////////////////////////


////////////////////////////////////////////////////////
unsigned int almanac_get_seats(Almanac *almanac, int target);



void * almanac_get_flight(Almanac *almanac, char * target);

void * almanac_get_airport(Almanac *almanac, char * target);
void * almanac_get_airport_flights(Almanac *almanac, char * target);

void almanac_get_airport_delays(Almanac *almanac, char *** list_of_names, int ** list_of_med, int * amount);
void almanac_sort_flight_delays(Almanac * almanac);
void almanac_get_airport_year(Almanac *almanac,char * target, char *** list_of_names, int ** list_of_passengers, int * amount);

int almanac_get_valid_passenger(Almanac *almanac);

void * almanac_get_reservation(Almanac *almanac, char * target);
char ** almanac_get_hotel(Almanac *almanac, char * target, int * amount, int argumentos, void (*f)(void *,char ***,int i,int argumentos));



void * almanac_get_prefix(Almanac *almanac);
void * almanac_get_user(Almanac *almanac, char * target);
char ** almanac_get_user_flights(Almanac * almanac, char * target, int * amount);
char ** almanac_get_user_reservations(Almanac * almanac, char * target, int * amount);


void almanac_get_dates(Almanac * almanac,char ** arguments,int num_arguments,int * amount,int ** year, int ** user, int ** fli, int ** res,int ** pas, int ** uni_pas);
////////////////////////////////////////////////////////


#endif