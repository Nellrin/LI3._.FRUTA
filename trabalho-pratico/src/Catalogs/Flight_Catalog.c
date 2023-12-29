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

    short amount_years;
    int * years_id;
    FHash * years;
    
    FHash * direct_airport;
    Stack * general_airport;

    int amount_airports;
    char ** airport_names_delay;
    int * airport_median_delays;


};

struct airport{
    char * id;
    BTree * flights;

    short amount;
    int * delays;
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
    return (strcasecmp(id, Node->year)==0);
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

    for(int i = 0; i < 5; i++){
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


    a->flights = create_node(flight);
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
    
    a->amount_years = 0;
    a->years_id = NULL;
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
    free_stack(a->general_airport);

    for(int i = 0; i < a->amount_airports; i++)
    free(a->airport_names_delay[i]);

    free(a->airport_names_delay);
    free(a->airport_median_delays);

    free(a->years_id);


    
    free(a);
}
////////////////////////////////////////////////////////


////////////////////////////////////////////////////////
static void add_passengers_to_year(Year_Airport * year, int passengers, char * origin){
        int found = 0;
        for(int i = 0; i < year->amount; i++)
            if(strcasecmp(year->airports[i],origin)==0){
                year->passengers[i] += passengers;
                found ++;
            }

        if(found == 0){


                    if((year->amount)%5 == 0){
                        int * list_num = (int *)realloc(year->passengers, sizeof(int) * (year->amount+5));
                        year->passengers = list_num;

                        char ** list_nam = (char **)realloc(year->airports, sizeof(char *) * (year->amount+5));
                        year->airports = list_nam;
                    
                        for(int i = 0; i < 5; i++){
                            year->airports[year->amount+i] = NULL;
                            year->passengers[year->amount+i] = 0;
                        }
                    }


            year->airports[year->amount] = strdup(origin);
            year->passengers[year->amount] += passengers;
            year->amount++;
        }
    }

void flight_almanac_add_flight(Flight_Almanac *almanac, char * id,char * airline, char * plane_model, char * origin, char * destination, char * schedule_departure_date,char * real_departure_date, char * schedule_arrival_date, unsigned int passengers){
    
    for(int i = 0; i < (int)strlen(origin);i++)
    origin[i] = toupper(origin[i]);

    for(int i = 0; i < (int)strlen(origin);i++)
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
        int * list_years = (int *)realloc(almanac->years_id, sizeof(int) * (almanac->amount_years+1));
        almanac->years_id = list_years;

        almanac->years_id[almanac->amount_years] = atoi(year_date);

        almanac->amount_years++;

        x = init_node_year_airport(year_date,origin,passengers);        
        fhash_add(almanac->years,year_date,x,1);
        add_passengers_to_year(x,passengers,destination);

    }

    else{
        add_passengers_to_year(x,passengers,origin);
        add_passengers_to_year(x,passengers,destination);
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
    return stack_to_array(almanac->general_airport,amount);
}


void flight_almanac_sort_airport_delays(Flight_Almanac *almanac){

    int amount = 0;
    Airport ** airport_list = (Airport **)stack_to_array(almanac->general_airport,&amount);
    
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


    for(int i = 0; i < almanac->amount_years; i++){
        char * id_year = malloc(sizeof(char)*5);
        id_year[0]='\0';
        
        snprintf(id_year,5,"%d",almanac->years_id[i]);

        Year_Airport * y  = fhash_get(almanac->years,id_year,1,compare_node_year);

        for(int j = 0; j < y->amount; j++){

            for(int k = j+1; k < y->amount; k++){
                if((y->passengers[j]<y->passengers[k]) || ((y->passengers[j]==y->passengers[k] && (strcasecmp(y->airports[j],y->airports[k])>0)))){
                
                int temp = y->passengers[j];
                y->passengers[j] = y->passengers[k];
                y->passengers[k] = temp;

                swap_strings(&y->airports[k],&y->airports[j]);
                }


            }

        }

        free(id_year);
    }

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

void flight_almanac_get_airport_years(Flight_Almanac *almanac, char * target, char *** list_of_names, int ** list_of_passengers, int * amount){


    Year_Airport * y = fhash_get(almanac->years,target,1,compare_node_year);

    (*amount) = y->amount;
    char ** names = malloc(sizeof(char *) * (*amount));
    int * passengers = malloc(sizeof(int) * (*amount));

    for(int i = 0; i < (*amount); i++){

        (names)[i] = strdup(y->airports[i]);
        (passengers)[i] = y->passengers[i];

    }



    *list_of_names = names;
    *list_of_passengers = passengers;
}
////////////////////////////////////////////////////////




// DUB 2763
// LHR 2439
// AMS 1999
// MAN 1931
// FRA 1909
// VIE 1538
// MAD 1537
// CDG 1483
// OSL 1315
// FCO 1222
// SVO 1191
// ARN 1165
// LIS 1126
// KBP 1120
// CPH 1108
// IST 1049
// ZRH 636
// WAW 583
// BCN 528
