#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>


#include "../include/Utilities.h"
#include "../include/Catalogs/Catalog.h"
// #include "../include/DataStructures/Users.h"

///////////////////////////////////////////////////////////////
static int string_to_tm(char * format, char *date) {
    int year = 0, month = 0, day = 0, hours = 0, minutes = 0, seconds = 0;

    if(!strcmp(format,"%d/%d/%d")){
        if (sscanf(date, format, &year, &month, &day) != 3){}
        return (year * 365) + (month * 30) + day;
    }

    if (sscanf(date, format, &year, &month, &day, &hours, &minutes, &seconds) != (!strcmp(format,"%d/%d/%d")?3:6)){}
    return seconds + 60*(minutes+60*(hours+24*(day+31*(month + 12 * year))));
}
///////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////
int string_to_time(char *format, char *date1, char *date2) {

    int x1 = string_to_tm(format, date2), x2 = string_to_tm(format, date1);
    int diff = (x1 - x2);

    // (!strcmp(format,"%d/%d/%d"))?(diff=(x1 - x2)/(366 * 60)):(diff = (x1 - x2));


    return diff;
}
void swap_strings(char ** s1, char ** s2){
    char *temp = *s1;
    *s1 = *s2;
    *s2 = temp;
}
///////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////
static int validate_hours(const char *date_string){
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

static int validate_days(const char *date_string){
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
    char * copy = strdup(string);
    for(int i = 0; i < strlen(string); i++)
        copy[i] = toupper(copy[i]);
     
    if(!strcmp(copy,"ACTIVE")){
        free(copy);
        return 1;
    }

    if(!strcmp(copy,"INACTIVE")){
        free(copy);
        return 2;
    }

    free(copy);
    return 0;
}

static int total_seats_validation(char * total_seats, int amount){
    int x = atoi(total_seats);

    return (x>=amount);
}

static int airport_validation(char * string){
    if(strlen(string) == 3){
        for(int i = 0; i < strlen(string); i++)
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

static int includes_breafast_validation(char * string){
    
    for(int i = 0; i < strlen(string);i++)
    string[i] = tolower(string[i]);

    if ((!strcmp(string,"t"))||(!strcmp(string,"true"))||(!strcmp(string,"1"))){
        return 1;
    }

    if ((!strcmp(string,"f"))||(!strcmp(string,"false"))||(!strcmp(string,"0"))||(!strcmp(string,""))){
        return -1;
    }

    return 0;
}

static int rating_validation(char * string){
    if((!strcmp(string,"")))
    return 1;


    return (general_number_validation(1,string,5));
}

static int general_string_validation(char * string){
    char * copy = strdup(string);
    int x = strlen(copy);
    free(copy);

    return(x>0);
}
///////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////
int valid_passenger(Almanac * a, const char * string){
    
    char * copy = strdup(string);
    char * copy_origin = copy;
    int res = 0;
    char ** list = malloc(sizeof(char *)*2);
    char *token = NULL;
    
    for(int i = 0;token = strsep(&copy, ";");i++)
    list[i] = strdup(token);


    //muito incompleta

    if(general_string_validation(list[0])&&general_string_validation(list[1]))
    if(almanac_get_user_node(a,list[1])!=NULL)
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

    
    for(int i = 0;token = strsep(&copy, ";");i++)
    list[i] = strdup(token);
    
    if(general_string_validation(list[0])
    && general_string_validation(list[1])
    && general_string_validation(list[2])
    && general_string_validation(list[3]) && atoi(list[3]) >= almanac_get_seats(a,atoi(list[0])-1)
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


            // id;airline;plane_model;total_seats;origin;destination;schedule_departure_date;schedule_arrival_date;real_departure_date;real_arrival_date;pilot;copilot;notes

            // char *id, char *airline, char *plane_model, char *origin, char *destination, char *schedule_departure_date, char *real_departure_date, char *schedule_arrival_date, char *passengers
        }


        // schedule_departure_date;schedule_arrival_date;real_departure_date;real_arrival_date

        // schedule_departure_date;real_departure_date;schedule_arrival_date;real_arrival_date


    for(int i = 0; i < 13; i++)
    free(list[i]);

    free(list);
    free(copy_origin);
    free(token);


    return res;
}
int valid_user(Almanac * a, const char * string){
// char * id, *name, *birth_date, *sex, *country_code, *account_status, *account_creation;
// char * email, *phone, *passport, *address, *payment_method;
    char * copy = strdup(string);
    char * copy_origin = copy;
    int res = 0;
    char ** list = malloc(sizeof(char *)*12);
    char *token = NULL;
    
    for(int i = 0;token = strsep(&copy, ";");i++)
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
        almanac_add_user(a,list[0],list[1],list[4],list[5],list[7],account_status_validation(list[11]),list[9],list[6]);
        res ++;
    }

    // id;name;email;phone_number;birth_date;sex;passport;country_code;address;account_creation;pay_method;account_status
    // char *id, char *name, char *birth_date, char *sex, char *country_code, char *account_status, char *account_creation

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
    
    for(int i = 0;token = strsep(&copy, ";");i++)
    list[i] = strdup(token);

    // char * bekfast
    

    
    if(general_string_validation(list[0])
    && general_string_validation(list[1]))
        if(almanac_get_user_node(a,list[1]) != NULL)
        if(general_string_validation(list[2])
        && general_string_validation(list[3])
        && general_string_validation(list[4]) && general_number_validation(1,list[4],5)
        && general_string_validation(list[5]) && general_number_validation(0,list[5],1000)
        && general_string_validation(list[6])
        && general_string_validation(list[7]) && validate_days(list[7])
        && general_string_validation(list[8]) && validate_days(list[8])  && ((strcmp(list[8],list[7]))>0)
        && general_string_validation(list[9]) && general_number_validation(0,list[9],1000000)
        && includes_breafast_validation(list[10]) != 0
        && general_string_validation(list[11]) && rating_validation(list[12])){
            almanac_add_reservation(a,list[0],list[2],list[1],list[3],list[4],list[7],list[8],includes_breafast_validation(list[10]),list[12],list[9],list[5]);
            res++;
            }

            // id;user_id;hotel_id;hotel_name;hotel_stars;city_tax;address;begin_date;end_date;price_per_night;includes_breakfast;room_details;rating;comment
            // char *id, char *id_hotel, char *user_id, char *hotel_name, char *hotel_stars, char *begin_date, char *end_date, char *includes_breakfast, char *rating, char *ppn, char *city_tax

    for(int i = 0; i < 14; i++)
    free(list[i]);


    free(list);
    free(copy_origin);
    free(token);

    return res;
}
///////////////////////////////////////////////////////////////