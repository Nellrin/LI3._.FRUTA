#ifndef RESERVATION_CATALOGS_H
#define RESERVATION_CATALOGS_H
////////////////////////////////////////////////////////


////////////////////////////////////////////////////////
typedef struct h FHash;
typedef struct btree BTree;
typedef struct rnode RNode;


typedef struct r_almanac Reservation_Almanac;
typedef struct u_almanac User_Almanac;
////////////////////////////////////////////////////////


////////////////////////////////////////////////////////
Reservation_Almanac * init_reservation_almanac(int amount);
void free_reservation_almanac(Reservation_Almanac * a);
////////////////////////////////////////////////////////


////////////////////////////////////////////////////////
void reservation_almanac_add_reservation(Reservation_Almanac *almanac, User_Almanac *user, char *id, short id_hotel, char *user_id, char *hotel_name, short hotel_stars, char *begin_date, char *end_date, short includes_breakfast, short rating, short ppn, short city_tax);
////////////////////////////////////////////////////////


////////////////////////////////////////////////////////
void * reservation_almanac_get_reservation(Reservation_Almanac *almanac, char * target);
char ** reservation_almanac_get_hotel(Reservation_Almanac *almanac, char * target, int * amount, int argumentos, void (*f)(void *,char ***,int i,int argumentos));
////////////////////////////////////////////////////////

#endif