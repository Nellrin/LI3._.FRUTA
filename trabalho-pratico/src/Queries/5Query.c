#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "../../include/Catalogs/Catalog.h"
#include "../../include/Output.h"

#include "../../include/DataStructures/BTree.h"
#include "../../include/DataStructures/Flights.h"
#include "../../include/Queries/4Query.h"



static void str_flights(FILE * file,void * flight,char ** arguments,int * n, char F){
    // id;schedule_departure_date;destination;airline;plane_model


    char * id = get_flightID(flight);
    char * sdeparture = get_flightSDEPARTURE(flight);
    char * destination = get_flightDESTINATION(flight);
    char * airline = get_flightAIRLINE(flight);
    char * plane_model = get_flightMODEL(flight);
    
    char * result = malloc(sizeof(char) * 1000); 
    result[0]='\0';

    if(strcmp(sdeparture,arguments[2])>=0 && strcmp(sdeparture,arguments[3])<=0){

            


        if(F){
                    if(!(*n))
                    snprintf(result,1000,
                                "--- %d ---\n"
                                "id: %s\n"
                                "schedule_departure_date: %s\n"
                                "destination: %s\n"
                                "airline: %s\n"
                                "plane_model: %s\n",
                                (*n)+1,id,sdeparture,destination,airline,plane_model);

                    else
                    snprintf(result,1000,
                                "\n--- %d ---\n"
                                "id: %s\n"
                                "schedule_departure_date: %s\n"
                                "destination: %s\n"
                                "airline: %s\n"
                                "plane_model: %s\n",
                                (*n)+1,id,sdeparture,destination,airline,plane_model);
            }

        else
        snprintf(result,1000,"%s;%s;%s;%s;%s\n",id,sdeparture,destination,airline,plane_model);


        (*n)++;

    }

    write_line(file,result);

    free(result);
    free(id);
    free(sdeparture);
    free(destination);
    free(airline);
    free(plane_model);
}

static void query5_getter(FILE * file,Almanac * box, char ** arguments, char F){

    void * airport_flights = almanac_get_airport_flights(box,arguments[1]);

    int nf = 0;
    get_every_node2(file,airport_flights,arguments,&nf,F,str_flights);
    
}


char * query5(FILE * file, Almanac * box, char ** arguments, short F){

    if(almanac_get_airport(box,arguments[1])!=NULL)
    query5_getter(file,box,arguments,F);

    return NULL;
}