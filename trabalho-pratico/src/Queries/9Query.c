#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <locale.h>

#include "../../include/Catalogs/Catalog.h"
#include "../../include/IO/Output.h"
#include "../../include/Tools/Utilities.h"

#include "../../include/DataStructures/Users.h"
#include "../../include/DataStructures/BTree.h"
#include "../../include/DataStructures/Trie.h"
#include "../../include/DataStructures/Flights.h"
#include "../../include/DataStructures/Reservations.h"
#include "../../include/Queries/9Query.h"


static void line_user(Almanac * u, FILE * file, char * argument,char ** names, char ** ids, int n, char F){
    char * line = malloc(sizeof(char) * 1000); 
    int count = 1;

    if(F){
        for(int i = 0; i < n; i++)
            if(strncmp(argument,names[i],strlen(argument))==0){
            if(get_userASTATUS(almanac_get_user(u,ids[i]))==1){
                if(count==1){
                snprintf(line,1000,
                                "--- %d ---\n"
                                "id: %s\n"
                                "name: %s\n",
                                count,ids[i],names[i]);
                        }

                else{
                    snprintf(line,1000,
                                    "\n--- %d ---\n"
                                    "id: %s\n"
                                    "name: %s\n",
                                    count,ids[i],names[i]);                    
                        }
            
                write_line(file,line);
                count++;
            }
            
            free(ids[i]);
            free(names[i]);
        }

    }
    else
    for(int i = 0; i < n; i++)
        if(!strncmp(argument,names[i],strlen(argument))){
        
        if(get_userASTATUS(almanac_get_user(u,ids[i]))==1){
            snprintf(line,1000,"%s;%s\n",ids[i],names[i]);
            write_line(file,line);
        }
        
        free(ids[i]);
        free(names[i]);
    }


                

    free(ids);
    free(names);

    free(line);


}


void query9(FILE * file,Almanac * box, char * argument,  short F){

        void * users = almanac_get_prefix(box);

        char ** names = NULL;
        char ** ids = NULL;
        int count = 0;


        lookup_prefix(users,&ids,&names,argument,&count);
        // printf("SAFE\n\n");
        line_user(box,file,argument,names,ids,count,F);

}