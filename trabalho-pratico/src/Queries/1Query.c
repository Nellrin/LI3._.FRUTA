#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "../../include/Catalogs/Catalog.h"
#include "../../include/Utilities.h"

#include "../../include/DataStructures/Users.h"
#include "../../include/DataStructures/BTree.h"
#include "../../include/DataStructures/Flights.h"
#include "../../include/DataStructures/Reservations.h"
#include "../../include/Queries/1Query.h"


#define MAX_RESULT 20000
//como n posso assumir que o user_id n começa por numeros ("123Andre"), uso isto para confirmar

static int user_verifier(const char * id){

    while (*id) {
        if (!isdigit(*id))
        return 0;
    
        id++;
    }
    return 1;
}
static void query1_reservation(void * entity, char ** result,char F){
        char * hotel_id = get_reservationHOTELID(entity);
        char * hotel_name = get_reservationHOTELNAME(entity);
        char * hotel_stars = get_reservationSTARS(entity);
        char * begin_date = get_reservationBEGIN(entity);
        char * end_date = get_reservationEND(entity);
        char * includes_breakfast = get_reservationBREAKFAST(entity);

        int nights = string_to_time("%d/%d/%d",begin_date,end_date);
        float total_price = total_got_from_reservation(entity);

                        if(F)
                        snprintf(*result, MAX_RESULT ,
                                "--- 1 ---\n"
                                "hotel_id: %s\n"
                                "hotel_name: %s\n"
                                "hotel_stars: %s\n"
                                "begin_date: %s\n"
                                "end_date: %s\n"
                                "includes_breakfast: %s\n"
                                "nights: %d\n"
                                "total_price: %.3f\n",
                            hotel_id, hotel_name, hotel_stars, begin_date,
                            end_date, includes_breakfast, nights, total_price);



                        else
                        snprintf(*result, MAX_RESULT,
                                "%s;%s;%s;%s;%s;%s;%d;%.3f\n",
                            hotel_id, hotel_name, hotel_stars, begin_date,
                            end_date, includes_breakfast, nights, total_price);

        free(hotel_id);
        free(hotel_name);
        free(hotel_stars);
        free(begin_date);
        free(end_date);
        free(includes_breakfast);
}
static void query1_user(Almanac * box, char * string, void * entity, char ** result,char F){
        char * name = get_userNAME(entity);
        char * sex = get_userSEX(entity);
        char * age = get_userBDAY(entity);
        char * country = get_userCOUNTRY(entity);
        char * passport = get_userPASSPORT(entity);
        int number_of_flights = 0;
        int number_of_reservations = 0;

                almanac_get_user_reservations_flights(box,string,&number_of_flights,&number_of_reservations);


        void * reservation = almanac_get_user_reservations(box,string);


        float total_spent = do_something(reservation,total_got_from_reservation);

        int idade = (string_to_time("%d/%d/%d",age,CURRENT_DATE))/(365);

            
            // char * text = get_userID(almanac_get_user(box,"RodrigGonçalves260"));
            
            
            // if(!strcmp(text,name))
            // printf("%s\n\n\n",text);
            // printf("%s\n",name);
            // print_user(almanac_get_user(box,"RodrigGonçalves260"));

                        if(F)
                        snprintf(*result, MAX_RESULT ,
                                "--- 1 ---\n"
                                "name: %s\n"
                                "sex: %s\n"
                                "age: %d\n"
                                "country_code: %s\n"
                                "passport: %s\n"
                                "number_of_flights: %d\n"
                                "number_of_reservations: %d\n"
                                "total_spent: %.3f\n",
                            name, sex, idade, country,
                            passport, number_of_flights, 
                            number_of_reservations, total_spent);

                        else
                        snprintf(*result, MAX_RESULT,
                                "%s;%s;%d;%s;%s;%d;%d;%.3f\n",
                            name, sex, idade, country,
                            passport, number_of_flights, 
                            number_of_reservations, total_spent);

        free(name);
        free(sex);
        free(age);
        free(country);
        free(passport);
}
static void query1_flight(void * entity, char ** result,char F){
    char * airline = get_flightAIRLINE(entity);
    char * plane_model = get_flightMODEL(entity);
    char * origin = get_flightORIGIN(entity);
    char * destination = get_flightDESTINATION(entity);
    char * sdeparture = get_flightSDEPARTURE(entity);
    char * sarrival = get_flightSARRIVAL(entity);
    unsigned int passengers = get_flightPASSENGERS(entity);

    char * rdeparture = get_flightRDEPARTURE(entity);
    int delay = string_to_time("%d/%d/%d %d:%d:%d",sdeparture,rdeparture);

                    if(F)
                    snprintf(*result, MAX_RESULT ,
                            "--- 1 ---\n"
                            "airline: %s\n"
                            "plane_model: %s\n"
                            "origin: %s\n"
                            "destination: %s\n"
                            "schedule_departure_date: %s\n"
                            "schedule_arrival_date: %s\n"
                            "passengers: %u\n"
                            "delay: %d\n",
                        airline, plane_model, origin, destination,
                        sdeparture, sarrival, passengers, delay);

                    else
                    snprintf(*result, MAX_RESULT,
                            "%s;%s;%s;%s;%s;%s;%u;%d\n",
                        airline, plane_model, origin, destination,
                        sdeparture, sarrival, passengers, delay);

    free(airline);
    free(plane_model);
    free(origin);
    free(destination);
    free(sdeparture);
    free(sarrival);
    free(rdeparture);
}


char * query1(Almanac * box, char * string, short F){
    char * result = malloc(sizeof(char) * MAX_RESULT);

    if(strstr(string,"Book")!=NULL){
        void * entity = almanac_get_reservation(box,string);

        if(entity!=NULL){
            query1_reservation(entity,&result,F);
            return result;
        }
    }
    
    if(!user_verifier(string))
    if(almanac_get_user_node(box,string)!=NULL){

        void * entity = almanac_get_user(box,string);

            char * text = get_userID(entity);
            if(!strcmp(text,"RodrigGonçalves260"))
            print_user(entity);

        if(get_userASTATUS(entity)==1){
            
            query1_user(box,string,entity,&result,F);
            return result;
        }
    }
    
    else{
        void * entity = almanac_get_flight(box,string);
            
            if(entity!=NULL){
                query1_flight(entity,&result,F);
                return result;        
            }

    }

    free(result);
    return NULL;
}