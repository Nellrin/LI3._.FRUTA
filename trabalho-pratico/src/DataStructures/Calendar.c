#include <stdio.h>
#include <stdlib.h>

#include "../../include/DataStructures/Calendar.h"
////////////////////////////////////////////////////////


////////////////////////////////////////////////////////
struct calendar{
    unsigned int * list;
};
////////////////////////////////////////////////////////


////////////////////////////////////////////////////////
Date_Counter *create_date() {
    Date_Counter *a = malloc(sizeof(Date_Counter));

    a->list = malloc(sizeof(unsigned int)*5); 
    for(int i = 0; i < 5; i++)
    a->list[i] = 0;
    return a;
}
////////////////////////////////////////////////////////


////////////////////////////////////////////////////////
void date_add_users(void * a,int amount) {

    ((Date_Counter *) a)->list[0]++;

}
void date_add_flights(void * a,int amount) {
    ((Date_Counter *) a)->list[1]++;
}
void date_add_reservations(void * a,int amount) {
    ((Date_Counter *) a)->list[2]++;
}
void date_add_passengers(void * a,int amount){
    ((Date_Counter *) a)->list[3]+=amount;
}
void date_add_unique_passengers(void * a,int amount){
    ((Date_Counter *) a)->list[4]++;
}
void date_subtract_unique_passengers(void * a,int amount){
    ((Date_Counter *) a)->list[4]-=amount;
}
////////////////////////////////////////////////////////


////////////////////////////////////////////////////////
int get_date_users(Date_Counter * a) {
    int x = a->list[0];
    return x;
}
int get_date_flights(Date_Counter * a) {
    int x = a->list[1];
    return x;
}
int get_date_reservations(Date_Counter * a) {
    int x = a->list[2];
    return x;
}
int get_date_passengers(Date_Counter * a) {
    int x = a->list[3];
    return x;
}
int get_date_unique_passengers(Date_Counter * a) {
    int x = a->list[4];
    return x;
}
////////////////////////////////////////////////////////


////////////////////////////////////////////////////////
void free_date(Date_Counter *a){
    if (a != NULL){
        free(a->list);
        free(a);
    }
}
////////////////////////////////////////////////////////