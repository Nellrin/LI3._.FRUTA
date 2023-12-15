#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// #include <glib.h>

#include "../../include/Catalogs/User_Catalog.h"
#include "../../include/DataStructures/Users.h"


typedef struct alm_u{
    User ** list_users;
    int amount; 
}Almanac_Users;

////////////////////////////////////////////////////////
static unsigned long hash_user(const char *str,int amount) {
    unsigned long hash = 1;
    int c;

    while ((c = *str++)) {
        hash = ((hash << 5) + hash) + c;
    }

    return (hash%amount);
}
////////////////////////////////////////////////////////


////////////////////////////////////////////////////////
void insert_USERALM(Almanac_Users * box,char * id,char * name, char * birth_date, char * sex, char * country_code, char * account_status, char * account_creation){

    User * a = set_user(id,name,birth_date,sex,country_code,account_status,account_creation);
    
    int key = hash_user(id,box->amount);

    while(box->list_users[key] != NULL)
    key = (key+1)%2000000;

    box->list_users[key] = a;

}
void destroy_USERALM(Almanac_Users * box){
    for(int i = 0; i<2000000; i++)
    free_user(box->list_users[i]);

    free(box->list_users);

    free(box);
}
Almanac_Users * new_USERALM(int amount){
    Almanac_Users * a = malloc(sizeof(Almanac_Users));
    
        a->list_users = malloc(sizeof(User *) * 2000000);

        for(int i = 0; i < 2000000; i++)
        a->list_users[i] = NULL;

        a->amount = amount;

    return a;
}
////////////////////////////////////////////////////////
