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
#include "../../include/Queries/2Query.h"




static void line_flight(void * a, char *** list_id, char *** list_dates, int * n){
    Flight * f = (Flight *) a;

    (*list_id)[(*n)] = get_flightID(f);
    (*list_dates)[(*n)] = get_flightSDEPARTURE(f);
    
    (*list_dates)[(*n)][10] = '\0';
    

    (*n) ++;

}
static void line_reservation(void * a, char *** list_id, char *** list_dates, int * n){
    Reservation * f = (Reservation *) a;

    (*list_id)[(*n)] = get_reservationID(f);
    (*list_dates)[(*n)] = get_reservationBEGIN(f);
        
    (*n) ++;
}

static char * strcat_list( char ** list_id,char ** list_dates, short F, int n, short mixed){

    char * line = malloc(sizeof(char) * 20000);
    char * x = malloc(sizeof(char) * 3);
    line[0] = '\0';
    
    if(F){
            for (int i = 0; i < n; i++) {
                
                    sprintf(x, "%d", i+1);
                    strcat(line, "--- ");
                    strcat(line, x);
                    strcat(line, " ---\n");
                
                strcat(line, "id: ");
                strcat(line, list_id[i]);
                strcat(line, "\ndate: ");
                strcat(line, list_dates[i]);

                    if(mixed){
                        if(strstr(list_id[i],"Book")!=NULL)
                        strcat(line, "\ntype: reservation");

                        else
                        strcat(line, "\ntype: flight");
                    }

                strcat(line, "\n\n");
            }


            line[strlen(line)-1] = '\0';
    }


    else{
        for(int i = 0; i < n; i++){
            strcat(line,list_id[i]);
            strcat(line,";");
            strcat(line,list_dates[i]);

            if(mixed){
                if(strstr(list_id[i],"Book")!=NULL)
                strcat(line, ";reservation");

                else
                strcat(line, ";flight");
            }
            strcat(line,"\n");
        }
    }

    free(x);
    return line;

}
static char * query2_getter(Almanac * box, char ** arguments,int n_arguments,char F){
    int nf = 0,nr = 0;
    char * result = NULL;
    
    almanac_get_user_reservations_flights(box,arguments[1],&nf,&nr);
    
    char **list_flights_id = malloc(sizeof(char *) * nf);
    char **list_flights_dates = malloc(sizeof(char *) * nf);
    char **list_reservations_id = malloc(sizeof(char *) * nr);
    char **list_reservations_dates = malloc(sizeof(char *) * nr);

    nf = 0;
    nr = 0;

    void * flights = almanac_get_user_flights(box,arguments[1]);
    void * reservations = almanac_get_user_reservations(box,arguments[1]);

    get_tlines(flights, &list_flights_id,&list_flights_dates, &nf, line_flight);
    get_tlines(reservations, &list_reservations_id,&list_reservations_dates, &nr, line_reservation);


                    if(n_arguments == 3){
                                    if(!strcmp(arguments[2],"flights")){
                                    result = strcat_list(list_flights_id,list_flights_dates,F,nf,0);

                                        for(int i = 0; i < nf; i++){
                                            free(list_flights_id[i]);
                                            free(list_flights_dates[i]);
                                        }

                                        for(int i = 0; i < nr; i++){
                                            free(list_reservations_id[i]);
                                            free(list_reservations_dates[i]);
                                        }

                                        free(list_flights_id);
                                        free(list_flights_dates);
                                        free(list_reservations_id);
                                        free(list_reservations_dates);

                                        return result;
                                    }

                                    else if(!strcmp(arguments[2],"reservations")){
                                        
                                    result = strcat_list(list_reservations_id,list_reservations_dates,F,nr,0);
                                    
                                        for(int i = 0; i < nf; i++){
                                            free(list_flights_id[i]);
                                            free(list_flights_dates[i]);
                                        }

                                        for(int i = 0; i < nr; i++){
                                            free(list_reservations_id[i]);
                                            free(list_reservations_dates[i]);
                                        }

                                        free(list_flights_id);
                                        free(list_flights_dates);
                                        free(list_reservations_id);
                                        free(list_reservations_dates);
                                    
                                        return result;
                                    }
                    }

            if(n_arguments == 2){
                    int nt = nf + nr;
                    char **merge_id = malloc(sizeof(char *) * nt);
                    char **merge_dates = malloc(sizeof(char *) * nt);

                    memcpy(merge_id, list_reservations_id, sizeof(char *) * nr);
                    memcpy(merge_id + nr, list_flights_id, sizeof(char *) * nf);

                    memcpy(merge_dates, list_reservations_dates, sizeof(char *) * nr);
                    memcpy(merge_dates + nr, list_flights_dates, sizeof(char *) * nf);

                        for (int i = 0; i < nt; i++)
                        for (int j = i + 1; j < nt; j++) {
                            if(
                                    (strcmp(merge_dates[i], merge_dates[j]) < 0)
                                    || 
                                    (
                                        (!strcmp(merge_dates[i], merge_dates[j]))
                                        
                                        && 

                                        (
                                            ((strstr(merge_id[i], "Book") != NULL) && (strstr(merge_id[j], "Book") == NULL)) 
                                            
                                            || 
                                            
                                            ((strstr(merge_id[i], "Book") != NULL) && (strstr(merge_id[j], "Book") != NULL) && (strcmp(merge_id[i], merge_id[j])>0))
                                        )
                                        
                                    )
                                ) {
                                swap_strings(&merge_dates[i], &merge_dates[j]);
                                swap_strings(&merge_id[i], &merge_id[j]);
                            }
                        }

                        // for (int i = 0; i < nt; i++)
                        // for (int j = i + 1; j < nt; j++)
                        //     if(!strcmp(merge_dates[i], merge_dates[j]))
                        //     if ((strstr(merge_id[i], "Book") != NULL && strstr(merge_id[j], "Book") == NULL) || strstr(merge_id[i], "Book") != NULL && strstr(merge_id[j], "Book") != NULL && (strcmp(merge_id[i], merge_id[j])>0))
                        //             swap_strings(&merge_id[i], &merge_id[j]);

                                // (strstr(merge_id[i], "Book") != NULL && strstr(merge_id[j], "Book") != NULL && (strcmp(merge_id[i], merge_id[j])>0))||
                                // (strstr(merge_id[i], "Book") == NULL && strstr(merge_id[j], "Book") == NULL && (strcmp(merge_id[i], merge_id[j])>0)))

                        // for (int i = 0; i < nt; i++)
                        // for (int j = i + 1; j < nt; j++)
                        //     if(!strcmp(merge_dates[i], merge_dates[j]))
                        //         if()
                        //             swap_strings(&merge_id[i], &merge_id[j]);


                            

                    result = strcat_list(merge_id,merge_dates,F,nt,1);
                    
                                        for(int i = 0; i < nf; i++){
                                            free(list_flights_id[i]);
                                            free(list_flights_dates[i]);
                                        }
                                        

                                        for(int i = 0; i < nr; i++){
                                            free(list_reservations_id[i]);
                                            free(list_reservations_dates[i]);
                                        }

                                        free(list_flights_id);
                                        free(list_flights_dates);
                                        free(list_reservations_id);
                                        free(list_reservations_dates);
                                        free(merge_id);
                                        free(merge_dates);

                    return result;
                }

    return NULL;
}


char * query2(Almanac * box, char ** arguments,  int n_arguments, short F){


    if(almanac_get_user_node(box,arguments[1])!=NULL)
    if(get_userASTATUS(almanac_get_user(box,arguments[1]))==1)
            return query2_getter(box,arguments,n_arguments,F);

    return NULL;
}