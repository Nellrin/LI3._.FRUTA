#include "../../include/DataStructures/Airport.h"
#include "../../include/DataStructures/Flights.h"
#include "../../include/DataStructures/SLists.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

////////////////////////////////////////////////////////
typedef struct airport {
    char *id;

    SList * dates_flights;
    
    int years;
    int * passengers; // por ano: 0 = 2023 1 = 2022-
    
    int median_amount;
    int * median;
} Airport;
////////////////////////////////////////////////////////
void print_airport(Airport * a){
    int amount = slists_amount_getter(a->dates_flights);
    printf("\n----------------------------------------------------\n");
    printf("[NAME]: %s\n",a->id);
    printf("\n[PASSENGERS PER YEAR] (2023 - %d)\n",2023-a->years);

    for(int i = 0; i < a->years; i++)
    printf("[[%d] %d]\n",2023-i,a->passengers[i]);


    char ** flights = slists_listB_getter(a->dates_flights);
    printf("\n\n[FLIGHTS]\n");
    for(int i = 0; i < amount; i++){
        printf("[%s]\n",flights[i]);
        free(flights[i]);
    }
    free(flights);

    printf("\n\n");
    
    for(int i = 0; i < amount; i++)
    printf("[MEDIAN %d]: %d\n",i,a->median[i]);

    printf("----------------------------------------------------\n");
}
////////////////////////////////////////////////////////
static void airport_add_passengers_years(Airport * a, int passengers, char * begin){
    char * copy = strdup(begin);
    int year = 0;

    for(int i = 0; copy[i] != '/';i++){
        year *= 10;
        year += copy[i] - '0';
    }

    printf("\n\n\n%d\n\n\n",year);


    if(2023-year>a->years){
        a->years = 2023 - year + 1;
        int *temp = realloc(a->passengers, a->years * sizeof(int));

        for (int i = a->years - 2; i < a->years; i++) {
            temp[i] = 0;
        }

        a->passengers = temp;

    }

    a->passengers[2023-year] += passengers;

    
    free(copy);
    // free(token);
    // free(year);
}
////////////////////////////////////////////////////////
Airport * new_airport(Flight * b){

    char * flight_begin = flight_schedule_departure_date_getter(b);
    char * flight_id = flight_id_getter(b);
    char * origin = flight_origin_getter(b);

    int flight_passengers = flight_passengers_getter(b);

    Airport * a = malloc(sizeof(Airport));

    a->years = 34;
    a->id = strdup(origin);
    
    a->dates_flights = slist_setter();
    // insert_slistB(a->dates_flights, flight_id);
    insert_slistF(a->dates_flights, flight_begin, flight_id);
    
    a->passengers = malloc(sizeof(int)*a->years);
    for(int i = 0; i < a->years; i++)
        a->passengers[i] = 0;

    airport_add_passengers_years(a,flight_passengers,flight_begin);
    

    a->median_amount = 1;
    a->median = malloc(sizeof(int));
    a->median[0] = flight_delay_date_getter(b);
    
    free(flight_begin);
    free(origin);
    free(flight_id);

    return a;
}
////////////////////////////////////////////////////////

////////////////////////////////////////////////////////
void free_airport(Airport *a) {
    if (a != NULL) {
        free(a->id);
        free(a->passengers);
        free(a->median);


        free_slists(a->dates_flights);

        free(a);
    }
}
////////////////////////////////////////////////////////
static void insertSorted(int * arr, int size, int value) {
    int i, j;

    for (i = 0; i < size && arr[i] < value; i++);

    for (j = size; j > i; j--)
        arr[j] = arr[j - 1];

    arr[i] = value;
}
int median(Airport * a){
    if(!(a->median_amount%2))
    return a->median[a->median_amount/2];

    int x = a->median[a->median_amount/2] + a->median[(a->median_amount/2) - 1];
    x/=2;

    return x;
}
////////////////////////////////////////////////////////

////////////////////////////////////////////////////////
void add_flight(Airport *a, Flight * b){

    char * flight_begin = flight_schedule_departure_date_getter(b);
    char * flight_id = flight_id_getter(b);

    int flight_passengers = flight_passengers_getter(b), p = flight_delay_date_getter(b);   
    
    insert_slistB(a->dates_flights,flight_id);
    insert_slistA(a->dates_flights,flight_begin,flight_id);


    airport_add_passengers_years(a,flight_passengers,flight_begin);
    
    a->median = realloc(a->median, (a->median_amount + 1) * sizeof(int));


    insertSorted(a->median,a->median_amount,p);

    a->median_amount++;

    free(flight_begin);
    free(flight_id);
}
int airport_median_getter(Airport *a){
    int amount = slists_amount_getter(a->dates_flights);
    return median(a);
}
int airport_passenger_year_getter(Airport *a,int x){
    int y = a->passengers[2023-x];
    return y;
}
char * airport_id_getter(Airport *a){
    char * x = strdup(a->id);
    return x;
}
SList * airport_dates_flights_getter(Airport *a){
    SList * x = slist_setter();
    slist_copy(x,a->dates_flights);
    return x;
}
int airport_flights_amount_getter(Airport *a){
    
    SList * x = slist_setter();
    slist_copy(x,a->dates_flights);
    
    int r = slists_amount_getter(x);
    free_slists(x);
    
    return r;
}
char ** airport_flights_getter(Airport *a){
    
    SList * x = slist_setter();
    slist_copy(x,a->dates_flights);
    
    char ** r = slists_listB_getter(x);
    free_slists(x);
    
    return r;
}
char ** airport_dates_getter(Airport *a){
    
    SList * x = slist_setter();
    slist_copy(x,a->dates_flights);
    
    char ** r = slists_listA_getter(x);
    free_slists(x);
    
    return r;
}
void sort_airport_slists(Airport * a){
    slist_sort(a->dates_flights);
}
Airport * get_airport(Airport * a){
    Airport * x = malloc(sizeof(Airport));
    x->dates_flights = airport_dates_flights_getter(a);
    x->id = airport_id_getter(a);
    x->median = malloc(sizeof(int));
    x->median[0] = airport_median_getter(a);
    x->years = a->years;
    x->passengers = malloc(sizeof(int) * a->years);

    for(int i = 0; i < x->years;i++)
    x->passengers[i] = a->passengers[i];

    return x;
}
////////////////////////////////////////////////////////