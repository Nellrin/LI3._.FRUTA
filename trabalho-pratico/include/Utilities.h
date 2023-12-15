#ifndef UTILITIES_H
#define UTILITIES_H


///////////////////////////////////////////////////////////////
int string_to_time(char *format, char *date1, char *date2);
///////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////
int validate_hours(const char *date_string);
int validate_days(const char *date_string);

int email_validation(char * string);
int country_code_validation(char * string);
int account_status_validation(char * string);
int total_seats_validation(char * total_seats, int amount);
int airport_validation(char * string);
int general_number_validation(int li,char * string,int ls);
int includes_breafast_validation(char * string);
int rating_validation(char * string);
int general_string_validation(char * string);
///////////////////////////////////////////////////////////////


#endif