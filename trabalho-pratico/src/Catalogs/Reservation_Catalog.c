#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../../include/DataStructures/Reservations.h"
#include "../../include/DataStructures/FHash.h"
#include "../../include/DataStructures/Stack.h"
#include "../../include/Catalogs/Reservation_Catalog.h"
#include "../../include/Catalogs/User_Catalog.h"
#include "../../include/Tools/Utilities.h"

////////////////////////////////////////////////////////
struct rnode{
    short id;
    Stack * reserva;
};

struct r_almanac{
    FHash * reservations;
    FHash * hotels;
};
////////////////////////////////////////////////////////


////////////////////////////////////////////////////////
static int compare_node(const char * id, const void * info){
    const RNode *Node = (const RNode *)info;
    
    return (Node->id == atoi(id+3));
}
static RNode * init_node(short hotel_id){
    RNode * a = malloc(sizeof(RNode));
    a->id = (hotel_id);
    a->reserva = init_stack();

    return a;
}
static void free_nodes(void * info){
    RNode * a = (RNode *)info;

    free_stack(a->reserva);

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

        push((node->reserva),reservation);


    user_almanac_add_reservation(user,user_id,reservation);


    free(finder);


}
////////////////////////////////////////////////////////


////////////////////////////////////////////////////////
void * reservation_almanac_get_reservation(Reservation_Almanac *almanac, char * target){
    return fhash_get(almanac->reservations,target,0,compare_reservation);
}
char ** reservation_almanac_get_hotel(Reservation_Almanac *almanac, char * target, int * amount, int argumentos, void (*f)(void *,char ***,int i,int argumentos)){
    RNode * result = fhash_get(almanac->hotels,target,1,compare_node);
    
    if(result == NULL) return NULL;
    return stack_to_char_array(result->reserva,amount,argumentos,f);
}
////////////////////////////////////////////////////////