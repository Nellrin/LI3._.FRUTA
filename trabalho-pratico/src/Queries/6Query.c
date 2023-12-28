#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "../../include/Catalogs/Catalog.h"
#include "../../include/IO/Output.h"
#include "../../include/Utilities.h"

#include "../../include/Queries/6Query.h"



static void str_q6(FILE * file,int * passengers,char ** names,int n, char F){

    char * result = malloc(sizeof(char) * 1000); 
    result[0]='\0';



        if(F){
                for(int i = 0; i < n; i++){

                    if(!i)
                    snprintf(result,1000,
                                "--- %d ---\n"
                                "name: %s\n"
                                "passengers: %d\n",
                                i+1,names[i],passengers[i]);

                    else
                    snprintf(result,1000,
                                "\n--- %d ---\n"
                                "name: %s\n"
                                "passengers: %d\n",
                                i+1,names[i],passengers[i]);



                                                                write_line(file,result);

                    result[0] = '\0';
                }
            }

        else{
                
            for(int i = 0; i < n; i++){
                snprintf(result,1000,"%s;%d\n",names[i],passengers[i]);
                        write_line(file,result);
                    result[0] = '\0';

                }
            }


    free(result);

    
}


char * query6(FILE * file, Almanac * box, char ** arguments, short F){

    char ** list_names = NULL;
    int * passengers = NULL;
    int amount = 0, x = 0;

    almanac_get_airport_year(box,arguments[1],&list_names,&passengers,&amount);

            if(atoi(arguments[2])<amount)
            x = atoi(arguments[2]);

            else
            x = amount;

    if(amount > 0){str_q6(file,passengers,list_names,x,F);}



    for(int i = 0; i < amount; i++){free(list_names[i]);}

    free(list_names);
    free(passengers);


    return NULL;
}