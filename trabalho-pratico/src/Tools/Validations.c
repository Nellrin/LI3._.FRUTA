#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include <time.h>

#include "../../include/Catalogs/Catalog.h"
#include "../../include/Tools/Validations.h"

///////////////////////////////////////////////////////////////
static int validate_hours(char *date_string){
    if (strlen(date_string) != 19)
    return 0;
    
    if(date_string[4] != '/' || date_string[7] != '/' || date_string[13] != ':' || date_string[16] != ':')
    return 0;

    int year, month, day, hour, minute, second;
    if (sscanf(date_string, "%d/%d/%d %d:%d:%d", &year, &month, &day, &hour, &minute, &second) != 6)
    return 0;

    if (month < 1 || month > 12 || day < 1 || day > 31 || hour < 0 || hour > 23 || minute < 0 || minute > 59 || second < 0 || second > 59)
    return 0;

    return 1;
}
static int validate_days(char *date_string){
    if (strlen(date_string) != 10)
    return 0;
    
    if(date_string[4] != '/' || date_string[7] != '/')
    return 0;

    int year, month, day;
    if (sscanf(date_string, "%d/%d/%d", &year, &month, &day) != 3)
    return 0;

    if (year < 1 || month < 1 || month > 12 || day < 1 || day > 31)
    return 0;

    return 1;
}
static int email_validation(char * string){
    const char *at_symbol = strchr(string, '@');
    const char *dot_symbol = at_symbol ? strchr(at_symbol, '.') : NULL;

    
    if (at_symbol && dot_symbol &&
        at_symbol > string && dot_symbol > at_symbol + 1 &&
        at_symbol < dot_symbol && dot_symbol < string + strlen(string) - 1) {
        
        if (at_symbol - string >= 1 && dot_symbol - (at_symbol + 1) >= 1 && strlen(dot_symbol + 1) >= 2) {
            return 1;
        }
    }

    return 0;
}
static int country_code_validation(char * string){
    if(strlen(string)==2)
    return (isalpha(string[0])&&isalpha(string[1]));

    return 0;
}
static int account_status_validation(char * string){
    return (strcasecmp(string,"ACTIVE") == 0) - (strcasecmp(string,"INACTIVE") == 0);
}
static int airport_validation(char * string){
    if(strlen(string) == 3){
        for(int i = 0; i < (int)strlen(string); i++)
            if(!isalpha(string[i]))
            return 0;

        return 1;
    }
    return 0;
}
static int general_number_validation(int li,char * string,int ls){
    double x = strtod(string,NULL);

    return((double)(int)x == x && x>=li && x<=ls); 

}
static short includes_breafast_validation(char * string){
    if((!strcasecmp(string,"t"))||(!strcasecmp(string,"true"))||(!strcmp(string,"1")))
        return 1;

    if((!strcasecmp(string,"f"))||(!strcasecmp(string,"false"))||(!strcmp(string,"0"))||(!strcmp(string,"")))
        return -1;

    return 0;
}
static short rating_validation(char * string){
    if((!strcmp(string,"")))
    return 0;


    if(general_number_validation(1,string,5))
    return (short)atoi(string);

    return -1;
}
static int general_string_validation(char * string){
    return(strlen(string)>0);
}
///////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////
int valid_passenger(Almanac * a, const char * string){
    
    char * copy = strdup(string);
    char * copy_origin = copy;
    int res = 0;
    char ** list = malloc(sizeof(char *)*2);
    char *token = NULL;
    
    
    for(int i = 0;(token = strsep(&copy, ";"));i++)
    list[i] = strdup(token);


    // if(almanac_get_valid_passenger(a))
    if(general_string_validation(list[0])&&general_string_validation(list[1]))
    if(almanac_get_user(a,list[1])!=NULL)
    if(almanac_get_flight(a,list[0])!=NULL){
        almanac_add_passengers(a,list[1],list[0]);
        res++;
    }
            

    for(int i = 0; i < 2; i++)
    free(list[i]);

    free(list);
    free(copy_origin);
    free(token);
    

    return res;
}
int valid_flight(Almanac * a, const char * string){

    char * copy = strdup(string);
    char * copy_origin = copy;
    char ** list = malloc(sizeof(char *)*13);
    char *token = NULL;
    int res = 0;

    
    for(int i = 0;(token = strsep(&copy, ";"));i++)
    list[i] = strdup(token);

    
    if(general_string_validation(list[0])
    && general_string_validation(list[1])
    && general_string_validation(list[2])
    && general_string_validation(list[3]) && (unsigned int)atoi(list[3]) >= almanac_get_seats(a,atoi(list[0])-1)
    && general_string_validation(list[4]) && airport_validation(list[4])
        && general_string_validation(list[5]) && airport_validation(list[5])  && (strcmp(list[4], list[5]) != 0)
        && general_string_validation(list[6]) && validate_hours(list[6])
        && general_string_validation(list[7]) && validate_hours(list[7]) && ((strcmp(list[6],list[7]))<0)
        && general_string_validation(list[8]) && validate_hours(list[8])
        && general_string_validation(list[9]) && validate_hours(list[9]) && ((strcmp(list[8],list[9]))<0)
        && general_string_validation(list[10])
        && general_string_validation(list[11])){
            almanac_add_flight(a,list[0],list[1],list[2],list[4],list[5],list[6],list[8],list[7],almanac_get_seats(a,atoi(list[0])-1));
            res ++;
        }


    for(int i = 0; i < 13; i++)
    free(list[i]);

    free(list);
    free(copy_origin);
    free(token);


    return res;
}
int valid_user(Almanac * a, const char * string){
    char * copy = strdup(string);
    char * copy_origin = copy;
    int res = 0;
    char ** list = malloc(sizeof(char *)*12);
    char *token = NULL;
    
    for(int i = 0;(token = strsep(&copy, ";"));i++)
    list[i] = strdup(token);
    
    if(general_string_validation(list[0])
    && general_string_validation(list[1])
    && general_string_validation(list[2])
    && general_string_validation(list[3])
    && general_string_validation(list[4]) && validate_days(list[4])
    && general_string_validation(list[5])
    && general_string_validation(list[6])
    && general_string_validation(list[7]) && country_code_validation(list[7])
    && general_string_validation(list[8])
    && general_string_validation(list[9]) && validate_hours(list[9]) && ((strcmp(list[9],list[4]))>0)
    && general_string_validation(list[10])
    && general_string_validation(list[11]) && account_status_validation(list[11])
    && email_validation(list[2])){
        almanac_add_user(a,list[0],list[1],list[4],strcmp(list[5],"F"),list[7],account_status_validation(list[11]),list[9],list[6]);
        res ++;
    }

    for(int i = 0; i < 12; i++)
    free(list[i]);
    

    free(list);
    free(copy_origin);
    free(token);

    return res;
}
int valid_reservation(Almanac * a, const char * string){
    char * copy = strdup(string);
    char * copy_origin = copy;
    int res = 0;
    char ** list = malloc(sizeof(char *)*14);
    char *token = NULL;
    for(int i = 0;(token = strsep(&copy, ";"));i++)
    list[i] = strdup(token);

    // char * bekfast
    

    
    if(general_string_validation(list[0])
    && general_string_validation(list[1]))
        if(almanac_get_user(a,list[1]) != NULL)
        if(general_string_validation(list[2])
        && general_string_validation(list[3])
        && general_string_validation(list[4]) && general_number_validation(1,list[4],5)
        && general_string_validation(list[5]) && general_number_validation(0,list[5],1000)
        && general_string_validation(list[6])
        && general_string_validation(list[7]) && validate_days(list[7])
        && general_string_validation(list[8]) && validate_days(list[8])  && ((strcmp(list[8],list[7]))>0)
        && general_string_validation(list[9]) && general_number_validation(0,list[9],1000000)
        && includes_breafast_validation(list[10]) != 0
        && general_string_validation(list[11]) && (rating_validation(list[12])!= -1)){
            almanac_add_reservation(a,list[0],atoi(list[2]+3),list[1],list[3],atoi(list[4]),list[7],list[8],includes_breafast_validation(list[10]),rating_validation(list[12]),atoi(list[9]),atoi(list[5]));
            res++;
        }

    for(int i = 0; i < 14; i++)
    free(list[i]);


    free(list);
    free(copy_origin);
    free(token);

    return res;
}
///////////////////////////////////////////////////////////////