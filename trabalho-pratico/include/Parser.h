#ifndef PARSER_H
#define PARSER_H

typedef struct flight Flight;
typedef struct almanac_users Almanac_Users;


int parser_users(const char * string, Almanac_Users * box);
// int parser_flight(const char * string, Almanac * box);
// int parser_passengers(const char * string, Almanac * box);
// int count_passengers(const char * string, Almanac * box);
void parser(char * path,char * type,Almanac_Users * box, int (*f)(const char *, Almanac_Users *));

#endif