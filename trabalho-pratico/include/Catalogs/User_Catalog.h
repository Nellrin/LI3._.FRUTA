#ifndef USER_CATALOGS_H
#define USER_CATALOGS_H

typedef struct String_list SList;
typedef struct user User;

typedef struct almanac_users Almanac_Users;


////////////////////////////////////////////////////////
void insert_user(Almanac_Users * box,User * a);
void destroy_user_almanac(Almanac_Users * box);
Almanac_Users * new_user_almanac();
void prefix_sort(Almanac_Users * box);
////////////////////////////////////////////////////////


////////////////////////////////////////////////////////
SList * almanac_users_prefix_getter(Almanac_Users * box);
User * almanac_users_user_getter(Almanac_Users * box, char * id);
////////////////////////////////////////////////////////


////////////////////////////////////////////////////////
void almanac_users_add_reservation(Almanac_Users * box, char * id, char * hotel_id, char * date, float money);
void almanac_users_add_flight(Almanac_Users * box, char * id, char * flight, char * date);
void almanac_users_remove_flight(Almanac_Users * box, char * id, char * flight);
////////////////////////////////////////////////////////


#endif