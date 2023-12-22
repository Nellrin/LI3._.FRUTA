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
void reservation_almanac_add_reservation(Reservation_Almanac *almanac, User_Almanac *user, char *id, char *id_hotel, char *user_id, char *hotel_name, char *hotel_stars, char *begin_date, char *end_date, char *includes_breakfast, char *rating, char *ppn, char *city_tax);
////////////////////////////////////////////////////////


////////////////////////////////////////////////////////
void * reservation_almanac_get_reservation(Reservation_Almanac *almanac, char * target);
void * reservation_almanac_get_hotel(Reservation_Almanac *almanac, char * target);
int reservation_almanac_get_hotel_num_res(Reservation_Almanac *almanac, char * target);
////////////////////////////////////////////////////////

#endif