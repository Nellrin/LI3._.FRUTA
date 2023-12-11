#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

#include "../include/Utilities.h"

///////////////////////////////////////////////////////////////
static int string_to_tm(char * format, char *date) {
    int year = 0, month = 0, day = 0, hours = 0, minutes = 0, seconds = 0;
    if (sscanf(date, format, &year, &month, &day, &hours, &minutes, &seconds) != (!strcmp(format,"%d/%d/%d")?3:6)){}

    return seconds + 60*(minutes+60*(hours+24*(day+31*(month + 12 * year))));
}
///////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////
int string_to_time(char *format, char *date1, char *date2) {

    int x1 = string_to_tm(format, date2), x2 = string_to_tm(format, date1);
    int diff;

    (!strcmp(format,"%d/%d/%d"))?(diff=(x1 - x2)/(24*60*60)):(diff = (x1 - x2));


    return diff;
}
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
///////////////////////////////////////////////////////////////
int date_validation(const char *date_string, int has_time) {
    if(has_time)
    return validate_hours(date_string);

    return validate_days(date_string);
}

int email_validation(char * string){
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

int country_code_validation(char * string){
    if(strlen(string)==2)
    return (isalpha(string[0])&&isalpha(string[1]));

    return 0;
}

int account_status_validation(char * string){
    char * copy = strdup(string);
    for(int i = 0; i < strlen(string); i++)
        copy[i] = toupper(copy[i]);
     
    if((!strcmp(copy,"ACTIVE"))||(!strcmp(copy,"INACTIVE"))){
        free(copy);
        return 1;
    }

    free(copy);
    return 0;
}

int total_seats_validation(char * total_seats, int amount){
    int x = atoi(total_seats);

    return (x>=amount);
}

int airport_validation(char * string){
    if(strlen(string) == 3){
        for(int i = 0; i < strlen(string); i++)
            if(!isalpha(string[i]))
            return 0;

        return 1;
    }
    return 0;
}

int general_number_validation(int li,char * string,int ls){
    double x = strtod(string,NULL);

    return((double)(int)x == x && x>=li && x<=ls); 

}

int includes_breafast_validation(char * string){
    
    char * x = strdup(string);

    if(!isdigit(x));

    for(int i = 0; i < strlen(x);i++)
    x[i] = tolower(x[i]);

    if ((!strcmp(x,""))||(!strcmp(x,"t"))||(!strcmp(x,"true"))||(!strcmp(x,"1"))||(!strcmp(x,"f"))||(!strcmp(x,"false"))||(!strcmp(x,"0"))){
        free(x);
        return 1;
    }

    free(x);
    return 0;
}

int rating_validation(char * string){
    if((!strcmp(string,"")))
    return 1;


    return (general_number_validation(1,string,5));
}

int general_string_validation(char * string){
    char * copy = strdup(string);
    int x = strlen(copy);
    free(copy);

    return(x>0);
}
///////////////////////////////////////////////////////////////
Utilities create_utilities(){
    Utilities f;

    f.time_diff = string_to_time;
    f.validations.account_status = account_status_validation;
    f.validations.airport = airport_validation;
    f.validations.breakfast = includes_breafast_validation;
    f.validations.country_code = country_code_validation;
    f.validations.date = date_validation;
    f.validations.email = email_validation;
    f.validations.number = general_number_validation;
    f.validations.rating = rating_validation;
    f.validations.string = general_string_validation;
    f.validations.total_seats = total_seats_validation;

    return f;
}

///////////////////////////////////////////////////////////////
void initialize_utilities(){
    Util = create_utilities();
}