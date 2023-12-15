#ifndef USER_CATALOGS_H
#define USER_CATALOGS_H

typedef struct user User;

typedef struct alm_u Almanac_Users;


////////////////////////////////////////////////////////
void insert_USERALM(Almanac_Users * box,char * id,char * name, char * birth_date, char * sex, char * country_code, char * account_status, char * account_creation);
void destroy_USERALM(Almanac_Users * box);
Almanac_Users * new_USERALM(int amount);
////////////////////////////////////////////////////////


#endif