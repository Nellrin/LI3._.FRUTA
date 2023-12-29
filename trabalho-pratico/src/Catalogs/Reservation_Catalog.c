#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../../include/DataStructures/Reservations.h"
#include "../../include/DataStructures/FHash.h"
#include "../../include/DataStructures/BTree.h"
#include "../../include/Catalogs/Reservation_Catalog.h"
#include "../../include/Catalogs/User_Catalog.h"
#include "../../include/Utilities.h"

////////////////////////////////////////////////////////
struct rnode{
    short id;
    int amount;
    BTree * reserva;
};

struct r_almanac{
    FHash * reservations;
    FHash * hotels;
};
////////////////////////////////////////////////////////


////////////////////////////////////////////////////////
static int compare_node(const char * id, const void * info){
    const RNode *Node = (const RNode *)info;
    
    char * helpy = malloc(sizeof(char)*20);
    snprintf(helpy,20,"HTL%d",Node->id);
    short res = (strcmp(id,helpy) == 0);
    free(helpy);

    return res;
}
static RNode * init_node(short hotel_id){
    RNode * a = malloc(sizeof(RNode));
    a->id = (hotel_id);
    a->reserva = NULL;
    a->amount = 0;

    return a;
}
static void free_nodes(void * info){
    RNode * a = (RNode *)info;

    free_tree(a->reserva);

    free(a);
}
////////////////////////////////////////////////////////


////////////////////////////////////////////////////////
Reservation_Almanac * init_reservation_almanac(int amount){
    Reservation_Almanac * a = malloc(sizeof(Reservation_Almanac));

    a->reservations = fhash_init(amount);
    a->hotels = fhash_init(amount/1000);

    return a;
}
void free_reservation_almanac(Reservation_Almanac * a){
    free_fhash(a->reservations,free_reservation);
    free_fhash(a->hotels,free_nodes);

    free(a);
}
////////////////////////////////////////////////////////


////////////////////////////////////////////////////////
void reservation_almanac_add_reservation(Reservation_Almanac *almanac, User_Almanac *user, char *id, short id_hotel, char *user_id, char *hotel_name, short hotel_stars, char *begin_date, char *end_date, short includes_breakfast, short rating, short ppn, short city_tax){
    void * reservation = set_reservation(id, id_hotel, user_id, hotel_name, hotel_stars, begin_date, end_date, includes_breakfast, rating, ppn, city_tax);
    
    fhash_add(almanac->reservations,id,reservation,0);

    char * finder = malloc(sizeof(char) * 20);
    snprintf(finder,20,"HTL%d",id_hotel);
    
    RNode * node = fhash_get(almanac->hotels,finder,1,compare_node);

    if(node == NULL){    
        node = init_node(id_hotel);
        fhash_add(almanac->hotels,finder,node,1);
    }

        insert(&(node->reserva),reservation,compare_reservation_date);
        node->amount++;


    user_almanac_add_reservation(user,user_id,reservation);


    free(finder);


}
////////////////////////////////////////////////////////


////////////////////////////////////////////////////////
void * reservation_almanac_get_reservation(Reservation_Almanac *almanac, char * target){
    return fhash_get(almanac->reservations,target,0,compare_reservation);
}
static void * helpy(void * info){
    RNode * a = (RNode *)info;
    return a->reserva;
}
void * reservation_almanac_get_hotel(Reservation_Almanac *almanac, char * target){
    void * result = fhash_get(almanac->hotels,target,1,compare_node);
    return helpy(result);
}
int reservation_almanac_get_hotel_num_res(Reservation_Almanac *almanac, char * target){
    void * result = fhash_get(almanac->hotels,target,1,compare_node);
    return (((RNode *)result)->amount);
}
////////////////////////////////////////////////////////