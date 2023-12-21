#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../../include/DataStructures/Users.h"
#include "../../include/DataStructures/Reservations.h"
#include "../../include/DataStructures/Flights.h"
#include "../../include/DataStructures/FHash.h"
#include "../../include/DataStructures/BTree.h"
#include "../../include/Catalogs/User_Catalog.h"


////////////////////////////////////////////////////////
struct node{
    void * user;
    
    BTree * flight;
    BTree * reservation;
};

struct u_almanac{
    FHash * global_user;
    BTree * prefix;
};
////////////////////////////////////////////////////////


////////////////////////////////////////////////////////
User_Almanac * init_user_almanac(int amount_users){
    User_Almanac * a = malloc(sizeof(User_Almanac));

    a->global_user = fhash_init(amount_users);
    a->prefix = NULL;

    return a;
}
static Node * init_node(User * user){
    Node * a = malloc(sizeof(Node));
    a->user = user;
    a->flight = NULL;
    a->reservation = NULL;

    return a;
}
static void free_nodes(void * info){
    Node * a = (Node *)info;

    free_user(a->user);
    free_tree(a->flight);
    free_tree(a->reservation);

    free(a);
}
void free_user_almanac(User_Almanac * a){
    free_fhash(a->global_user,free_nodes);
    free_tree(a->prefix);

    free(a);
}
////////////////////////////////////////////////////////


////////////////////////////////////////////////////////
static int compare_node(const char * id, const void * info){
    const Node *node = (const Node *)info;
    return (compare_user(id, node->user));
}
////////////////////////////////////////////////////////


////////////////////////////////////////////////////////
void user_almanac_add_user(User_Almanac *almanac,char * id, char *name, char *birth_date, char *sex, char *country_code, short account_status, char *account_creation,char * passport){
    void * user = set_user(id, name, birth_date, sex, country_code, account_status, account_creation,passport);
    Node * a = init_node(user);

    fhash_add(almanac->global_user,id,(void *)a, 1);
    insert(&(almanac->prefix),user,compare_user_prefix);

}
void user_almanac_add_flight(User_Almanac *almanac,char * id, void * flight){
    Node * node = fhash_get(almanac->global_user,id,1,compare_node);
    insert(&(node->flight),flight,compare_flight_date);
}
void user_almanac_add_reservation(User_Almanac *almanac,char *id, void * reservation){
    Node * node = fhash_get(almanac->global_user,id,1,compare_node);
    insert(&(node->reservation),reservation,compare_reservation_date);

}
////////////////////////////////////////////////////////


// ////////////////////////////////////////////////////////
// unsigned int almanac_get_seats(Almanac *almanac, int target){
//     return almanac->passenger[target];
// }
void * user_almanac_get_user(User_Almanac *almanac, char * target){
    return fhash_get(almanac->global_user,target,1,compare_node);
}
void * user_almanac_get_prefix(User_Almanac *almanac){
    return almanac->prefix;
}
void * user_almanac_get_individual_user(User_Almanac *almanac, char * target){
    Node * a = (Node *)user_almanac_get_user(almanac,target);
    return a->user;
}

void * user_almanac_use_flights(User_Almanac *almanac, char * target){
    Node * a = (Node *)user_almanac_get_user(almanac,target);
    return a->flight;
}
void * user_almanac_use_reservations(User_Almanac *almanac, char * target){
    Node * a = (Node *)user_almanac_get_user(almanac,target);
    return a->reservation;
}

// void * almanac_get_flight(Almanac *almanac, char * target){
//     void * flight = fhash_get(almanac->flight,target,0,compare_flight);
//     return flight;
// }
// void * almanac_get_reservation(Almanac *almanac, char * target){
//     void * reservation =fhash_get(almanac->reservation,target,0,compare_reservation);
//     return reservation;
// }
////////////////////////////////////////////////////////