#ifndef USER_CATALOGS_H
#define USER_CATALOGS_H
////////////////////////////////////////////////////////


////////////////////////////////////////////////////////
typedef struct h FHash;
typedef struct btree BTree;
typedef struct node Node;


typedef struct u_almanac User_Almanac;
////////////////////////////////////////////////////////


////////////////////////////////////////////////////////
User_Almanac * init_user_almanac(int amount);
void free_user_almanac(User_Almanac * a);
////////////////////////////////////////////////////////


////////////////////////////////////////////////////////
void user_almanac_add_user(User_Almanac *almanac,char * id, char *name, char *birth_date, char *sex, char *country_code, short account_status, char *account_creation, char * passport);
void user_almanac_add_flight(User_Almanac *almanac,char * id, void * flight);
void user_almanac_add_reservation(User_Almanac *almanac,char *id, void * reservation);
////////////////////////////////////////////////////////


////////////////////////////////////////////////////////
void * user_almanac_use_reservations(User_Almanac *almanac, char * target);
void user_almanac_get_amount_flights(User_Almanac *almanac, char * target, int * amount);
void * user_almanac_use_flights(User_Almanac *almanac, char * target);

void * user_almanac_get_user(User_Almanac *almanac, char * target);
void * user_almanac_get_prefix(User_Almanac *almanac);
void * user_almanac_get_individual_user(User_Almanac *almanac, char * target);
////////////////////////////////////////////////////////

#endif