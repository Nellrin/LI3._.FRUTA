#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../../include/DataStructures/Users.h"
#include "../../include/DataStructures/Reservations.h"
#include "../../include/DataStructures/BTree.h"
#include "../../include/DataStructures/Flights.h"
#include "../../include/DataStructures/FHash.h"
#include "../../include/DataStructures/Stack.h"
#include "../../include/DataStructures/Trie.h"

#include "../../include/Catalogs/User_Catalog.h"


////////////////////////////////////////////////////////
struct node{
    void * user;
    
    Stack * flight;
    Stack * reservation;
    // TRie_Date * passenger_dates;
    BTree * passenger_dates;
};

struct u_almanac{
    FHash * global_user;
    
    TRie * prefix_tree;
};
////////////////////////////////////////////////////////


////////////////////////////////////////////////////////
static Node * init_node(User * user){
    Node * a = malloc(sizeof(Node));
    a->user = user;
    a->flight = init_stack();
    a->reservation = init_stack();
    // a->passenger_dates = init_trie_date();
    a->passenger_dates = NULL;

    return a;
}
static void free_nodes(void * info){
    Node * a = (Node *)info;

    free_user(a->user);
    free_stack(a->flight);
    free_stack(a->reservation);
    // destroy_date_trie(a->passenger_dates);
    free_tree(a->passenger_dates);

    free(a);
}
////////////////////////////////////////////////////////


////////////////////////////////////////////////////////
void free_user_almanac(User_Almanac * a){
    free_fhash(a->global_user,free_nodes);

    destroy_trie(a->prefix_tree);

    free(a);
}
User_Almanac * init_user_almanac(int amount_users){
    User_Almanac * a = malloc(sizeof(User_Almanac));

    a->global_user = fhash_init(amount_users);

    a->prefix_tree = init_trie('A','z');

    return a;
}
////////////////////////////////////////////////////////


////////////////////////////////////////////////////////
static int compare_node_user(const char * id, const void * info){
    const Node *node = (const Node *)info;
    return (compare_user(id, node->user));
}
static Node * user_almanac_get_user_node(User_Almanac *almanac, char * target){
    return fhash_get(almanac->global_user,target,1,compare_node_user);
}
////////////////////////////////////////////////////////


////////////////////////////////////////////////////////
void user_almanac_add_user(User_Almanac *almanac,char * id, char *name, char *birth_date, short sex, char *country_code, short account_status, char *account_creation,char * passport){
    void * user = set_user(id, name, birth_date, sex, country_code, account_status, account_creation,passport);
    Node * a = init_node(user);

    fhash_add(almanac->global_user,id,(void *)a, 1);
    insert_trie((almanac->prefix_tree),(char *)get_userNAME(user),(char *)get_userID(user));

}
static int compare(const void * s1, const void *s2){
    return strncmp((char *)s1,(char *)s2,10);
}
void user_almanac_add_flight(User_Almanac *almanac,char * id, void * flight, const char * passenger_date){
    Node * node = fhash_get(almanac->global_user,id,1,compare_node_user);
    push(node->flight,flight);

    // add_date(node->passenger_dates,passenger_date);
    insert(&(node->passenger_dates),(void *)passenger_date,compare);
}
int is_unique_passenger(User_Almanac *almanac,char * id, char * date){
    int n = 0;

    Node * node = fhash_get(almanac->global_user,id,1,compare_node_user);
    general_btree_function(node->passenger_dates,date,&n);

    return n;
}
void user_almanac_add_reservation(User_Almanac *almanac,char * id, void * reservation){
    Node * node = user_almanac_get_user_node(almanac,id);
    push(node->reservation,reservation);
}
////////////////////////////////////////////////////////


////////////////////////////////////////////////////////
void * user_almanac_get_prefix(User_Almanac *almanac){
    return almanac->prefix_tree;
}

void * user_almanac_get_individual_user(User_Almanac *almanac, char * target){
    Node * a = user_almanac_get_user_node(almanac,target);
    if(a==NULL) return NULL;
    return a->user;
}



static void get_all_reservations_from_user(void * a, char *** list, int i, int argumentos){
    (*list)[i*argumentos] = get_reservationID((Reservation *)a);
    (*list)[i*argumentos + 1] = get_reservationBEGIN((Reservation *)a);
}
static void get_all_flights_from_user(void * a, char *** list, int i, int argumentos){
    (*list)[i*argumentos] = get_flightID((Flight *)a);
    (*list)[i*argumentos + 1] = strdup(get_flightSDEPARTURE((Flight *)a));
}

char ** user_almanac_get_flights(User_Almanac *almanac, char * target, int * amount){
    Node * a = user_almanac_get_user_node(almanac,target);

    if(a==NULL)return NULL;
    
    return stack_to_char_array(a->flight,amount,2,get_all_flights_from_user);
}
char ** user_almanac_get_reservations(User_Almanac *almanac, char * target, int * amount){
    Node * a = user_almanac_get_user_node(almanac,target);
    if(a==NULL)return NULL;

    return stack_to_char_array(a->reservation,amount,2,get_all_reservations_from_user);
}
////////////////////////////////////////////////////////