#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// #include <glib.h>

#include "../../include/Catalogs/User_Catalog.h"
#include "../../include/DataStructures/Users.h"
#include "../../include/DataStructures/SLists.h"
#include "../../include/DataStructures/Functions.h"


typedef struct almanac_users{
    User ** list_users;
    SList * list_prefix; 
}Almanac_Users;
////////////////////////////////////////////////////////
static unsigned long hash_user(const char *str) {
    unsigned long hash = 1;
    int c;

    while ((c = *str++)) {
        hash = ((hash << 5) + hash) + c; // hash * 33 + c
    }

    return (hash%10000000);
}
static void insert_prefix(Almanac_Users * box,User * a){

    char * id = Data.user.get.id(a);
    char * name = Data.user.get.name(a);

    Data.slist.insert.F(box->list_prefix,name,id);

    free(id);
    free(name);
}
////////////////////////////////////////////////////////


////////////////////////////////////////////////////////
void insert_user(Almanac_Users * box,User * a){
    char * id = Data.user.get.id(a);
    int key = hash_user(id);

    while(box->list_users[key] != NULL)
    key = (key+1)%10000000;

    box->list_users[key] = a;

    insert_prefix(box,a);
    free(id);
}
void destroy_user_almanac(Almanac_Users * box){
    for(int i = 0; i<10000000; i++)
    // if(box->list_users[i]!=NULL)
    Data.user.free(box->list_users[i]);

    free(box->list_users);

    Data.slist.free(box->list_prefix);

    free(box);
}
Almanac_Users * new_user_almanac(){
    Almanac_Users * a = malloc(sizeof(Almanac_Users));
    
        a->list_prefix = Data.slist.set();
        a->list_users = malloc(sizeof(User *) * 10000000);

        for(int i = 0; i < 10000000; i++)
        a->list_users[i] = NULL;

    return a;
}
void prefix_sort(Almanac_Users * box){
    Data.slist.sort(box->list_prefix);
}
////////////////////////////////////////////////////////


////////////////////////////////////////////////////////
static int key_finder(Almanac_Users * box, char * id){
    int key = hash_user(id);

    char * new_id = Data.user.get.id(box->list_users[key]);
    for(int i = 0; strcmp(new_id,id)!=0; i++){
        free(new_id);

            if(i >500)
            return -1;

        key = (key + 1) % 10000000;
        new_id = Data.user.get.id(box->list_users[key]);
    }

    free(new_id);
    return key;
}
////////////////////////////////////////////////////////
SList * almanac_users_prefix_getter(Almanac_Users * box){
    SList * a = Data.slist.set();
    Data.slist.copy(a,box->list_prefix);
    return a;
}
User * almanac_users_user_getter(Almanac_Users * box, char * id){

    int key = key_finder(box,id);

    if(key == -1)
    return NULL;

    User * a = Data.user.get.user(box->list_users[key]);

    return a;
}
////////////////////////////////////////////////////////
void almanac_users_add_reservation(Almanac_Users * box, char * id, char * hotel_id, char * date, float money){
    
    int key = hash_user(id);

    if(key == -1)
    return;

    User * a = box->list_users[key];

    if(a!=NULL)
    Data.user.add.reservation(a,hotel_id,date,money);
}
void almanac_users_add_flight(Almanac_Users * box, char * id, char * flight, char * date){
    
    int key = hash_user(id);

    if(key == -1)
    return;

    User * a = box->list_users[key];

    if(a!=NULL)
    Data.user.add.flight(a,flight,date);
}
void almanac_users_remove_flight(Almanac_Users * box, char * id, char * flight){
    
    int key = hash_user(id);

    if(key == -1)
    return;
    
    User * a = box->list_users[key];

    if(a!=NULL)
    Data.user.remove_flight(a,flight);
}
////////////////////////////////////////////////////////