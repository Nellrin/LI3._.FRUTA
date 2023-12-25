// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>

// #include "../../include/DataStructures/Flights.h"
// #include "../../include/DataStructures/FHash.h"
// #include "../../include/DataStructures/BTree.h"
// #include "../../include/DataStructures/Stack.h"
// #include "../../include/Catalogs/Flight_Catalog.h"
// #include "../../include/Utilities.h"

// ////////////////////////////////////////////////////////
// struct f_almanac{
//     FHash * flight;
//     FHash * hotels;
// };

// struct ht{
//     char * id;
//     BTree * reservations;

//     Stack * delays;
// };

// struct htq6{
//     char * year;
// };

// /*

//     FNode
//         char * id
//         BTree flights

//         int atrasos
//         int num_atrasos


//     Q5: 
//         FHash a 
//             FNode
//                 char * id
//                 BTree flights
                
//     Q6: 
//         FNode * lista_ordenada_por_num_passageiros
//     Q7: 
// */
// ////////////////////////////////////////////////////////


// ////////////////////////////////////////////////////////
// static int compare_node(const char * id, const void * info){
//     const RNode *Node = (const RNode *)info;
//     return (strcmp(id, Node->id)==0);
// }
// static RNode * init_node(char * hotel_id){
//     RNode * a = malloc(sizeof(RNode));
//     a->id = strdup(hotel_id);
//     a->reserva = NULL;
//     a->amount = 0;

//     return a;
// }
// static void free_nodes(void * info){
//     RNode * a = (RNode *)info;

//     free(a->id);
//     free_tree(a->reserva);

//     free(a);
// }
// ////////////////////////////////////////////////////////


// ////////////////////////////////////////////////////////
// Flight_Almanac * init_reservation_almanac(int amount){
//     Flight_Almanac * a = malloc(sizeof(Flight_Almanac));

//     a->reservations = fhash_init(amount);
//     a->hotels = fhash_init(amount/1000);

//     return a;
// }
// void free_reservation_almanac(Flight_Almanac * a){
//     free_fhash(a->reservations,free_reservation);
//     free_fhash(a->hotels,free_nodes);

//     free(a);
// }
// ////////////////////////////////////////////////////////


// ////////////////////////////////////////////////////////
// void reservation_almanac_add_reservation(Reservation_Almanac *almanac, User_Almanac *user, char *id, char *id_hotel, char *user_id, char *hotel_name, char *hotel_stars, char *begin_date, char *end_date, char *includes_breakfast, char *rating, char *ppn, char *city_tax){
//     void * reservation = set_reservation(id, id_hotel, user_id, hotel_name, hotel_stars, begin_date, end_date, includes_breakfast, rating, ppn, city_tax);
    
//     fhash_add(almanac->reservations,id,reservation,1);
    
//     RNode * node = fhash_get(almanac->hotels,id_hotel,0,compare_node);

//     if(node == NULL){    
//         node = init_node(id_hotel);
//         fhash_add(almanac->hotels,id_hotel,node,0);
//     }

//         insert(&(node->reserva),reservation,compare_reservation_date);
//         node->amount++;


//     user_almanac_add_reservation(user,user_id,reservation);


// }
// ////////////////////////////////////////////////////////


// ////////////////////////////////////////////////////////
// void * reservation_almanac_get_reservation(Reservation_Almanac *almanac, char * target){
//     return fhash_get(almanac->reservations,target,1,compare_reservation);
// }
// static void * helpy(void * info){
//     RNode * a = (RNode *)info;
//     return a->reserva;
// }
// void * reservation_almanac_get_hotel(Reservation_Almanac *almanac, char * target){
//     void * result = fhash_get(almanac->hotels,target,0,compare_node);
//     return helpy(result);
// }
// int reservation_almanac_get_hotel_num_res(Reservation_Almanac *almanac, char * target){
//     void * result = fhash_get(almanac->hotels,target,0,compare_node);
//     return (((RNode *)result)-> amount);
// }
// ////////////////////////////////////////////////////////