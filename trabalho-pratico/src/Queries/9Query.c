#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "../../include/Catalogs/Catalog.h"
#include "../../include/Output.h"

#include "../../include/DataStructures/Users.h"
#include "../../include/DataStructures/BTree.h"
#include "../../include/DataStructures/Flights.h"
#include "../../include/DataStructures/Reservations.h"
#include "../../include/Queries/9Query.h"



static short checker(void * user, char * prefix){
    char * name = get_userNAME(user);
    
    short len = strlen(prefix);
    short result = !(strncmp(prefix,name,len));
    
    free(name);

    return result;

}

static void line_user(FILE * file,void * b, int * n, char F, char * prefix){
    User * a = (User *)b;
    char * name = get_userNAME(a);

    short len = strlen(prefix);
    if(!strncmp(prefix,name,len)&&get_userASTATUS(a)==1){
        char * id = get_userID(a);
        char * line = malloc(sizeof(char) * 1000); 


                if(F){
                    if((*n)==0)
                    snprintf(line,1000,
                                    "--- %d ---\n"
                                    "id: %s\n"
                                    "name: %s\n",
                                    (*n)+1,id,name);
                   
                   
                    else
                    snprintf(line,1000,
                                    "\n--- %d ---\n"
                                    "id: %s\n"
                                    "name: %s\n",
                                    (*n)+1,id,name);
                
                }

                else
                snprintf(line,1000,
                                "%s;%s\n",
                                id,name);


            write_line(file,line);

            
        (*n) ++;
        free(line);
        free(id);
    }
        free(name);
}


void query9(FILE * file,Almanac * box, char * argument,  short F){

        int nt = 0;

        void * users = almanac_get_prefix(box);

        get_prefix(file,users, argument,&nt,F, line_user,checker);
}