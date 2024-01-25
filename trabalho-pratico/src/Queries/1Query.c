#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "../../include/Catalogs/Catalog.h"
#include "../../include/Tools/Utilities.h"

#include "../../include/DataStructures/Users.h"
#include "../../include/DataStructures/BTree.h"
#include "../../include/DataStructures/Flights.h"
#include "../../include/DataStructures/Reservations.h"
#include "../../include/Queries/1Query.h"


#define MAX_RESULT 20000
//como n posso assumir que o user_id n começa por numeros ("123Andre"), uso isto para confirmar

static int user_verifier(const char * id){

    for(int i = 0; i < (int)strlen(id); i++)
        if(isalpha(id[i]))
        return 1;

    return 0;
}
static void query1_reservation(void * entity, char ** result,char F){

        char * hotel_name = get_reservationHOTELNAME(entity);
        char * begin_date = get_reservationBEGIN(entity);
        char * end_date = get_reservationEND(entity);
        char * includes_breakfast = NULL;

        if(get_reservationBREAKFAST(entity)==1)
        includes_breakfast = strdup("True");

        else
        includes_breakfast = strdup("False");

        int nights = string_to_time("%d/%d/%d",begin_date,end_date);
        double total_price = total_got_from_reservation(entity);

                        if(F)
                        snprintf(*result, MAX_RESULT ,
                                "--- 1 ---\n"
                                "hotel_id: HTL%d\n"
                                "hotel_name: %s\n"
                                "hotel_stars: %d\n"
                                "begin_date: %s\n"
                                "end_date: %s\n"
                                "includes_breakfast: %s\n"
                                "nights: %d\n"
                                "total_price: %.3f\n",
                            get_reservationHOTELID(entity), hotel_name, get_reservationSTARS(entity), begin_date,
                            end_date, includes_breakfast, nights, total_price);



                        else
                        snprintf(*result, MAX_RESULT,
                                "HTL%d;%s;%d;%s;%s;%s;%d;%.3f\n",
                            get_reservationHOTELID(entity), hotel_name, get_reservationSTARS(entity), begin_date,
                            end_date, includes_breakfast, nights, total_price);

        free(hotel_name);
        free(begin_date);
        free(end_date);
        free(includes_breakfast);
}
static void query1_user(Almanac * box, char * string, void * entity, char ** result,char F){
        char * name = strdup(get_userNAME(entity));
        char * sex = NULL;

        if(!get_userSEX(entity))
        sex = strdup("F");

        else
        sex = strdup("M");
        
        char * age = get_userBDAY(entity);
        char * country = get_userCOUNTRY(entity);
        char * passport = get_userPASSPORT(entity);
        int number_of_flights = 0;
        int number_of_reservations = 0;
        double total_spent = 0;

        char ** list = almanac_get_user_flights(box,string,&number_of_flights);
        for(int i = 0; i < number_of_flights * 2; i+=2){
            free(list[i]);
            free(list[i+1]);
        }
        free(list);

        list = almanac_get_user_reservations(box,string,&number_of_reservations);
        for(int i = 0; i < number_of_reservations * 2; i+=2){
            total_spent += total_got_from_reservation(almanac_get_reservation(box,list[i]));
            free(list[i]);
            free(list[i+1]);
        }

        free(list);
        
        int idade = (string_to_time("%d/%d/%d",age,CURRENT_DATE))/(365.25);

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
    char * sdeparture = strdup(get_flightSDEPARTURE(entity));
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
    
    if(user_verifier(string))
    if(almanac_get_user(box,string)!=NULL){

        void * entity = almanac_get_user(box,string);

            if(get_userASTATUS(entity)==1){
            
            query1_user(box,string,entity,&result,F);
            return result;
        }
    }
    
        void * entity = almanac_get_flight(box,string);
            
            if(entity!=NULL){
                query1_flight(entity,&result,F);
                return result;        
            }

    free(result);
    return NULL;
}