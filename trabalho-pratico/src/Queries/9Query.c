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
#include "../../include/Queries/9Query.h"



static void line_user(void * a, char *** list_id, char *** list_name, int * n, char * prefix){
    char * name = get_userNAME(a);

    if(!strncmp(prefix,name,strlen(prefix))&&get_userASTATUS(a)==1){
        (*list_id)[(*n)] = get_userID(a);

        // printf("%s\n",name);
        (*list_name)[(*n)] = get_userNAME(a);
            
        (*n) ++;
        
    }
        free(name);
}

static char * strcat_list_pre( char ** list_id,char ** list_dates, short F, int n){

    char * line = malloc(sizeof(char) * 200000);
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
                strcat(line, "\nname: ");
                strcat(line, list_dates[i]);


                strcat(line, "\n\n");
            }


            line[strlen(line)-1] = '\0';
    }


    else{
        for(int i = 0; i < n; i++){
            strcat(line,list_id[i]);
            strcat(line,";");
            strcat(line,list_dates[i]);
            strcat(line,"\n");
        }
    }

    free(x);
    return line;

}

static custom_compare(const char *str1, const char *str2){
       while (*str1 && *str2) {
        // Convert characters to lowercase for comparison
        unsigned int c1 = tolower((unsigned int)*str1);
        unsigned int c2 = tolower((unsigned int)*str2);

        // Compare characters
        if (c1 < c2) {
            return -1;
        } else if (c1 > c2) {
            return 1;
        }

        // Move to the next characters
        str1++;
        str2++;
    }

    // Strings are equal up to the shorter length
    if (*str1 == *str2) {
        return 0;
    } else if (*str1) {
        return 1; // str1 is longer
    } else {
        return -1; // str2 is longer
    }
}


static char * query9_getter(Almanac * box, char * argument ,char F){
    char * result = NULL;
    
    int nt = 1000;

    char **list_user_id = malloc(sizeof(char *) * nt);
    char **list_user_name = malloc(sizeof(char *) * nt);

    nt = 0;


        void * users = almanac_get_prefix(box);


        get_prefix(users, &list_user_id,&list_user_name, argument,&nt, line_user);

    for(int i = 0; i < nt; i++)
    for(int j = i; j < nt; j++){
        char * nameA = strdup(list_user_name[i]);
        char * nameB = strdup(list_user_name[j]);

        for(int k = 0; k < strlen(nameA); k++)
        if(nameA[k]=='-')
        nameA[k] = ' ';

        for(int k = 0; k < strlen(nameB); k++)
            if(nameB[k]=='-')
            nameB[k] = ' ';

        int res = custom_compare(nameA, nameB);
        free(nameA);free(nameB);
        
        if(!res)
        if(strcasecmp(list_user_id[i], list_user_id[j])>0){
            swap_strings(&list_user_id[i],&list_user_id[j]);
            swap_strings(&list_user_name[i],&list_user_name[j]);
        }
            

        if(res>0){
            swap_strings(&list_user_name[i],&list_user_name[j]);
            swap_strings(&list_user_id[i],&list_user_id[j]);
        }
    }

        result = strcat_list_pre(list_user_id,list_user_name,F,nt);

            // for(int i = 0; i < nt; i++){
            //     if(list_user_id[i]!=NULL)
            //     free(list_user_id[i]);
            //     free(list_user_name[i]);
            // }

            // free(list_user_id);
            // free(list_user_name);

            return result;
}


char * query9(Almanac * box, char * argument,  short F){

        return query9_getter(box,argument,F);

}