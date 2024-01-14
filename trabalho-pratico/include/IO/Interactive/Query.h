#ifndef SINGULAR_QUERY_H
#define SINGULAR_QUERY_H

typedef struct almanac Almanac;

int execute_query(Almanac * u, int * amount_of_queries, int * selected_query, int * first_query_shown);
int show_query(int selected_query, int * first_query_shown);

#endif