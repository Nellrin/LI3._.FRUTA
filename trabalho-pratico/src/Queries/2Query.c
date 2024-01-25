#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "../../include/Catalogs/Catalog.h"
#include "../../include/Tools/Utilities.h"

#include "../../include/DataStructures/Users.h"
#include "../../include/DataStructures/BTree.h"
#include "../../include/DataStructures/Flights.h"
#include "../../include/DataStructures/Reservations.h"
#include "../../include/Queries/2Query.h"
#include "../../include/Tools/Utilities.h"


static char * strcat_list(char ** list_id,char ** list_dates, short F, int n, short mixed){

    char * line = malloc(sizeof(char) * 200 * n);
    char * x = malloc(sizeof(char) * 20);
    line[0] = '\0';
    
    if(F){
            for (int i = 0; i < n; i++) {
                
                    sprintf(x, "%d", (i+1));
                    strcat(line, "--- ");
                    strcat(line, x);
                    strcat(line, " ---\n");
                
                strcat(line, "id: ");
                strcat(line, list_id[i]);
                strcat(line, "\ndate: ");
                strncat(line, list_dates[i],10);

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
            strncat(line,list_dates[i],10);

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

static int good_strcmp(char* str1, char* str2, char* id1, char* id2){

    int res = strcmp(str2,str1);

    if(!res)
    res = strcmp(id1,id2);

    return res;
}

static char * query2_getter(Almanac * box, char ** arguments,int n_arguments,char F){
    
    char * result = NULL;
    
    if(n_arguments == 3){
        char ** list = NULL;
        int n = 0;
                        if(!strcmp(arguments[2],"flights"))
                        list = almanac_get_user_flights(box,arguments[1],&n);
                            
                        if(!strcmp(arguments[2],"reservations"))
                        list = almanac_get_user_reservations(box,arguments[1],&n);
        
        
        char ** ids = malloc(sizeof(char *) * n);
        char ** dates = malloc(sizeof(char *) * n);

                        for(int i = 0; i < n*2; i+=2){
                            ids[i/2] = list[i];
                            dates[i/2] = list[i+1];
                        }

                        free(list);

        sort_strings(&dates,&ids,n,good_strcmp);
        result = strcat_list(ids,dates,F,n,0);


                        for(int i = 0; i < n; i++){
                            free(ids[i]);
                            free(dates[i]);
                        }

                        free(ids);
                        free(dates);

        return result;
    }

    if(n_arguments == 2){

        int nf = 0;
        int nr = 0;
        
        char **list_flights = almanac_get_user_flights(box,arguments[1],&nf);
        char **list_reservations = almanac_get_user_reservations(box,arguments[1],&nr);
            
            
            int nt = nf + nr;


            char **merge_id = malloc(sizeof(char *) * nt);
            char **merge_dates = malloc(sizeof(char *) * nt);

        for(int i = 0; i < nf * 2; i+=2){
            merge_id[i/2] = list_flights[i];
            merge_dates[i/2] = list_flights[i+1];
        }

        for(int i = 0; i < nr * 2; i+=2){
            merge_id[nf + i/2] = list_reservations[i];
            merge_dates[nf + i/2] = list_reservations[i+1];

        }

                sort_strings(&merge_dates,&merge_id,nt,good_strcmp);             

            result = strcat_list(merge_id,merge_dates,F,nt,1);
            
                                for(int i = 0; i < nt; i++){
                                    free(merge_id[i]);
                                    free(merge_dates[i]);
                                }
                                
                        free(list_flights);
                        free(list_reservations);
                        free(merge_id);
                        free(merge_dates);

            return result;
        }

    return NULL;
}


char * query2(Almanac * box, char ** arguments,  int n_arguments, short F){

    if(almanac_get_user(box,arguments[1])!=NULL)
    if(get_userASTATUS(almanac_get_user(box,arguments[1]))==1)
            return query2_getter(box,arguments,n_arguments,F);

    return NULL;
}