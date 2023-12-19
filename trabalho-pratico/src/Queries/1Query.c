#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "../../include/Catalogs/Catalog.h"
#include "../../include/Utilities.h"

#include "../../include/DataStructures/Flights.h"
#include "../../include/DataStructures/Reservations.h"
#include "../../include/Queries/1Query.h"

#define MAX_RESULT 20000

//como n posso assumir que o user_id n começa por numeros ("123Andre"), uso isto para confirmar

static int user(const char * id){
    
    while (*id) {
        if (!isdigit(*id))
        return 0;
    
        id++;
    }

    return 1;
}

char * query1(Almanac * box, char * string, short F){
    char * result = malloc(sizeof(char) * MAX_RESULT);

    if(strstr(string,"Book")!=NULL){
        void * entity = almanac_get_reservation(box,string);
//(hotel_id;hotel_name;hotel_stars;begin_date;end_date;includes_breakfast;nights;total_price)
            if(entity!=NULL){

                    char * hotel_id = get_reservationHOTELID(entity);
                    char * hotel_name = get_reservationHOTELNAME(entity);
                    char * hotel_stars = get_reservationSTARS(entity);
                    char * begin_date = get_reservationBEGIN(entity);
                    char * end_date = get_reservationEND(entity);
                    char * includes_breakfast = get_reservationBREAKFAST(entity);

                    int nights = string_to_time("%d/%d/%d",begin_date,end_date);
                    char * char_ppn = get_reservationPPN(entity);
                    float ppn = strtod(char_ppn,NULL);
                    char * char_tax = get_reservationTAX(entity);
                    float tax = strtod(char_tax,NULL);
                    float total_price = total_pay(ppn,tax,nights);

                                    if(F)
                                    snprintf(result, MAX_RESULT ,
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
                                    snprintf(result, MAX_RESULT,
                                            "%s;%s;%s;%s;%s;%s;%d;%.3f\n",
                                        hotel_id, hotel_name, hotel_stars, begin_date,
                                        end_date, includes_breakfast, nights, total_price);

                    free(hotel_id);
                    free(hotel_name);
                    free(hotel_stars);
                    free(begin_date);
                    free(end_date);
                    free(includes_breakfast);
                    free(char_ppn);
                    free(char_tax);

                return result;      
            }
    }
    
    if(!user(string)){
        void * entity = almanac_get_user(box,string);
            
            if(entity!=NULL){

            }
    }
    
    else{
        void * entity = almanac_get_flight(box,string);
            
            if(entity!=NULL){

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
                                    snprintf(result, MAX_RESULT ,
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
                                    snprintf(result, MAX_RESULT,
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


                return result;        
            }

    }

    free(result);
    return NULL;
}