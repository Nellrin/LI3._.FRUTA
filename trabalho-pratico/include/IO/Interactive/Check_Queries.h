#ifndef CHECK_QUERIES_H
#define CHECK_QUERIES_H

char ** draw_UI(char * path, int * amount, int terminal_window_size, int first_query_shown, int query);
int check_query_menu(int * amount_of_queries, int * first_query_shown, int * selected_query);

#endif