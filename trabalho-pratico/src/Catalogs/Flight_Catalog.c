#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "../../include/DataStructures/Flights.h"
#include "../../include/DataStructures/FHash.h"
#include "../../include/DataStructures/BTree.h"
#include "../../include/DataStructures/Stack.h"
#include "../../include/Catalogs/Flight_Catalog.h"
#include "../../include/Utilities.h"

////////////////////////////////////////////////////////
struct f_almanac{
    FHash * flight;

    FHash * direct_airport;
    FHash * years;
    
    Stack * general_airport;

    int amount_airports;
    char ** airport_names_delay;
    int * airport_median_delays;


};

struct airport{
    char * id;
    BTree * flights;

    short amount;
    int * delays;;
};

struct year_of_airport{
    char * year;

    int amount;
    int * passengers;
    char ** airports;
};

////////////////////////////////////////////////////////


////////////////////////////////////////////////////////
static int compare_node_year(const char * id, const void * info){
    const Year_Airport *Node = (const Year_Airport *)info;
    return (strcmp(id, Node->year)==0);
}
static int compare_node_airport(const char * id, const void * info){
    const Airport *Node = (const Airport *)info;
    return (strcasecmp(id, Node->id)==0);
}
////////////////////////////////////////////////////////


////////////////////////////////////////////////////////
static Year_Airport * init_node_year_airport(char * year, char * origin,int passengers){
    
    Year_Airport * a = malloc(sizeof(Year_Airport));
    a->year = strdup(year);

    a->passengers = malloc(sizeof(int)*5);
    a->airports = malloc(sizeof(char *)*5);

    for(int i = 1; i < 5; i++){
        a->passengers[i] = 0;
        a->airports[i] = NULL;
    }

    a->passengers[0] = passengers;
    a->airports[0] = strdup(origin);


    a->amount = 1;


    return a;
}
static Airport * init_node_airport(char * id, char *real_departure, char * schedule_departure, void * flight){
    
    Airport * a = malloc(sizeof(Airport));
    a->id = strdup(id);


    a->flights = createNode(flight);
    a->amount = 0;

    a->delays = malloc(sizeof(int)*5);
    a->delays[a->amount] = string_to_time("%d/%d/%d %d:%d:%d",schedule_departure,real_departure);
    a->amount ++;
    
    return a;
}
Flight_Almanac * init_flight_almanac(int amount){
    Flight_Almanac * a = malloc(sizeof(Flight_Almanac));
    
    a->flight = fhash_init(amount);
    a->general_airport = init_stack();
    a->direct_airport = fhash_init(amount/30);
    a->years = fhash_init(20);

    return a;
}
////////////////////////////////////////////////////////


////////////////////////////////////////////////////////
static void insert_flight(Airport * airport, void * flight, char * rdeparture, char * sdeparture){

    insert(&(airport->flights),flight,compare_flight_date);

    if((airport->amount)%5 == 0){
        int * list = (int *)realloc(airport->delays, sizeof(int) * (airport->amount+5));
        airport->delays = list;
    }
    airport->delays[airport->amount] = string_to_time("%d/%d/%d %d:%d:%d",sdeparture,rdeparture);
    airport->amount++;    
}
////////////////////////////////////////////////////////


////////////////////////////////////////////////////////
static void free_node_year(void * info){
    Year_Airport * a = (Year_Airport *)info;

    free(a->year);

    free(a->passengers);

    for(int i = 0; i < a->amount; i++)
    free(a->airports[i]);

    free(a->airports);

    free(a);
}
static void free_node_airport(void * info){
    Airport * a = (Airport *)info;

    free(a->delays);
    
    free_tree(a->flights);

    free(a->id);

    free(a);
}
void free_flight_almanac(Flight_Almanac * a){
    
    free_fhash(a->direct_airport,free_node_airport);
    free_fhash(a->flight,free_flight);
    free_fhash(a->years,free_node_year);
    freeStack(a->general_airport);

    for(int i = 0; i < a->amount_airports; i++)
    free(a->airport_names_delay[i]);

    free(a->airport_names_delay);
    free(a->airport_median_delays);


    
    free(a);
}
////////////////////////////////////////////////////////


////////////////////////////////////////////////////////
void flight_almanac_add_flight(Flight_Almanac *almanac, char * id,char * airline, char * plane_model, char * origin, char * destination, char * schedule_departure_date,char * real_departure_date, char * schedule_arrival_date, unsigned int passengers){
    
    for(int i = 0; i < strlen(origin);i++)
    origin[i] = toupper(origin[i]);

    for(int i = 0; i < strlen(origin);i++)
    destination[i] = toupper(destination[i]);


    void * flight = set_flight(id,airline, plane_model, origin, destination, schedule_departure_date,real_departure_date, schedule_arrival_date, passengers);

    fhash_add(almanac->flight,id,flight,0);



    Airport * airport = fhash_get(almanac->direct_airport,origin,1,compare_node_airport);
    
    if(airport==NULL){
        airport = init_node_airport(origin,real_departure_date,schedule_departure_date,flight);
        fhash_add(almanac->direct_airport,origin,airport,1);
        push(almanac->general_airport,airport);
    }

    else
    insert_flight(airport,flight,real_departure_date,schedule_departure_date);




    char * copy = strdup(schedule_departure_date);
    char * token = NULL; 
    token = strsep(&copy, "/");
    char * year_date = strdup(token);

    Year_Airport * x = fhash_get(almanac->years,year_date,1,compare_node_year);

    if(x==NULL){
        
        x = init_node_year_airport(year_date,origin,passengers);        
        fhash_add(almanac->years,year_date,x,1);

    }

    else{
        int i = 0;
        for(i = 0; i < x->amount; i++)
            if(strcmp(x->airports[i],origin)==0){
                x->passengers[i] += passengers;
                break;
            }

        if(i == x->amount){


                    if((x->amount)%5 == 0){
                        int * list_num = (int *)realloc(x->passengers, sizeof(int) * (x->amount+5));
                        x->passengers = list_num;

                        char ** list_nam = (char **)realloc(x->airports, sizeof(char *) * (x->amount+5));
                        x->airports = list_nam;
                    
                        for(int i = 1; i < 5; i++){
                            x->airports[x->amount+i] = NULL;
                            x->passengers[x->amount+i] = 0;
                        }
                    }


            x->airports[x->amount] = strdup(origin);
            x->passengers[x->amount] = passengers;
            x->amount++;
        }
    }


    free(token);
    free(year_date);

}
////////////////////////////////////////////////////////


////////////////////////////////////////////////////////
void * flight_almanac_get_flight(Flight_Almanac *almanac, char * target){
    return fhash_get(almanac->flight,target,0,compare_flight);
}

void * flight_almanac_get_airport_direct(Flight_Almanac *almanac, char * target){
    void * result = fhash_get(almanac->direct_airport,target,1,compare_node_airport);
    return result;
}
void * flight_almanac_get_airport_flights(Flight_Almanac *almanac, char * target){

    Airport * result = fhash_get(almanac->direct_airport,target,1,compare_node_airport);
    return result->flights;
}

void ** flight_almanac_get_airport_general(Flight_Almanac *almanac, int * amount){
    return getStackMembers(almanac->general_airport,amount);
}


void flight_almanac_sort_airport_delays(Flight_Almanac *almanac){

    int amount = 0;
    Airport ** airport_list = (Airport **)getStackMembers(almanac->general_airport,&amount);
    
    int * med = malloc(sizeof(int) * (amount));
    char ** names = malloc(sizeof(char *) * (amount));

    for(int i = 0; i < amount; i++){
                for(int j = 0; j < airport_list[i]->amount; j++)
                for(int k = j+1; k < airport_list[i]->amount; k++)
                    if(airport_list[i]->delays[j]>airport_list[i]->delays[k]){
                        int temp = airport_list[i]->delays[j];
                        airport_list[i]->delays[j] = airport_list[i]->delays[k];
                        airport_list[i]->delays[k] = temp;
                    }

        med[i] = median(airport_list[i]->delays,airport_list[i]->amount);
        names[i] = strdup(airport_list[i]->id);
    }


    for(int i = 0; i < amount; i++)
    for(int j = i+1; j < amount; j++){
        if((med[i]<med[j]) || ((med[i]==med[j] && (strcmp(names[i],names[j])>0)))){
            int temp = med[i];
            med[i] = med[j];
            med[j] = temp;

            swap_strings(&names[i],&names[j]);
        }

    }


    almanac->amount_airports = amount;
    almanac->airport_median_delays = med;
    almanac->airport_names_delay = names;

    free(airport_list);

}

void flight_almanac_get_airport_delays(Flight_Almanac *almanac, char *** list_of_names, int ** list_of_med, int * amount){

    (*amount) = almanac->amount_airports;

    char ** names = malloc(sizeof(char *) * (*amount));
    int * med = malloc(sizeof(int) * (*amount));


    for(int i = 0; i < (*amount); i++){


        (names)[i] = strdup(almanac->airport_names_delay[i]);
        (med)[i] = almanac->airport_median_delays[i];
    }



    *list_of_names = names;
    *list_of_med = med;
}
////////////////////////////////////////////////////////