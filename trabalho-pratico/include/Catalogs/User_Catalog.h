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
void user_almanac_add_user(User_Almanac *almanac,char * id, char *name, char *birth_date, short sex, char *country_code, short account_status, char *account_creation, char * passport);
int is_unique_passenger(User_Almanac *almanac,char * id, char * date);
void user_almanac_add_flight(User_Almanac *almanac,char * id, void * flight, const char * passenger_date);
void user_almanac_add_reservation(User_Almanac *almanac,char *id, void * reservation);
////////////////////////////////////////////////////////


////////////////////////////////////////////////////////
char ** user_almanac_get_reservations(User_Almanac *almanac, char * target, int * amount);
char ** user_almanac_get_flights(User_Almanac *almanac, char * target, int * amount);

void * user_almanac_get_prefix(User_Almanac *almanac);
void * user_almanac_get_individual_user(User_Almanac *almanac, char * target);
////////////////////////////////////////////////////////

#endif