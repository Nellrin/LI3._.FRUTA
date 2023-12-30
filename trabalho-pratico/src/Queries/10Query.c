#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "../../include/Catalogs/Catalog.h"
#include "../../include/IO/Output.h"
#include "../../include/Tools/Utilities.h"

#include "../../include/DataStructures/BTree.h"
#include "../../include/DataStructures/Reservations.h"
#include "../../include/Queries/10Query.h"

static void q10_str(FILE * file, int n_arguments, int amount, int * year, int * user,int * fli, int * res,int * pas,int * uni_pas, short F){
    
    char * result = malloc(sizeof(char) * 1000); 
    result[0] = '\0';

    if(F){
        char * date = NULL;
        switch (n_arguments){
            case 0:
                date = strdup("year");
                break;

            case 1:
                date = strdup("month");
                break;

            case 2:
                date = strdup("day");
                break;
            
            default:
                break;
        }

        for(int i = 0; i < amount; i++){


                if(i == 0)
                snprintf(result,1000,
                            "--- %d ---\n"
                            "%s: %d\n"
                            "users: %d\n"
                            "flights: %d\n"
                            "passengers: %d\n"
                            "unique_passengers: %d\n"
                            "reservations: %d\n",
                            i+1,date,year[i],user[i],fli[i],pas[i],uni_pas[i],res[i]);

                else
                snprintf(result,1000,
                            "\n--- %d ---\n"
                            "%s: %d\n"
                            "users: %d\n"
                            "flights: %d\n"
                            "passengers: %d\n"
                            "unique_passengers: %d\n"
                            "reservations: %d\n",
                            i+1,date,year[i],user[i],fli[i],pas[i],uni_pas[i],res[i]);
    
    
                write_line(file,result);
                
                
                }

                free(date);
        }

    else
        for(int i = 0; i < amount; i++){
            snprintf(result,1000,"%d;%d;%d;%d;%d;%d\n",year[i],user[i],fli[i],pas[i],uni_pas[i],res[i]);
            write_line(file,result);
        }


    free(year);
    free(user);
    free(fli);
    free(pas);
    free(uni_pas);
    free(res);
    free(result);
}


char * query10(FILE * file, Almanac * box, char ** arguments,int n_arguments, short F){


    int amount = 0;
    int * year = NULL;
    int * user = NULL;
    int * fli = NULL;
    int * res = NULL;
    int * pas = NULL;
    int * uni_pas = NULL;

    almanac_get_dates(box,arguments,(n_arguments-1),&amount,&year,&user,&fli,&res,&pas,&uni_pas);

        for(int i = 0; i < amount; i++)
        for(int j = i+1; j < amount; j++){
            if(year[i]>year[j]){
                swap_ints(&year[i],&year[j]);
                swap_ints(&user[i],&user[j]);
                swap_ints(&fli[i],&fli[j]);
                swap_ints(&res[i],&res[j]);
                swap_ints(&pas[i],&pas[j]);
                swap_ints(&uni_pas[i],&uni_pas[j]);
            }

        }


    if(amount>0)
    q10_str(file,(n_arguments-1),amount,year,user,fli,res,pas,uni_pas,F);

    return NULL;
}