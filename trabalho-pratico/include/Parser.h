#ifndef PARSER_H
#define PARSER_H

typedef struct flight Flight;
typedef struct almanac Almanac;


int parser_users(const char * string, Almanac * box);
int parser_flight(const char * string, Almanac * box);
// int parser_passengers(const char * string, Almanac * box);
int count_passengers(const char * string, Almanac * box);
void parser(char * path,char * type,Almanac * box, int (*f)(const char *, Almanac *));

#endif