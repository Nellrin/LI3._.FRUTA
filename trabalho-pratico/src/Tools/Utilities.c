#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include <time.h>


#include "../../include/Tools/Utilities.h"
#include "../../include/Catalogs/Catalog.h"

///////////////////////////////////////////////////////////////
int string_to_time(char * format,char *date1, char *date2) {

    struct tm start = {0}, end = {0};

    if(strchr(format,':')){
        sscanf(date1,format,&start.tm_year,&start.tm_mon,&start.tm_mday,&start.tm_hour,&start.tm_min,&start.tm_sec);
        sscanf(date2,format,&end.tm_year,&end.tm_mon,&end.tm_mday,&end.tm_hour,&end.tm_min,&end.tm_sec);
    }
    else{
        sscanf(date1,format,&start.tm_year,&start.tm_mon,&start.tm_mday);
        sscanf(date2,format,&end.tm_year,&end.tm_mon,&end.tm_mday);
    }

    start.tm_year -= 1900;
    start.tm_mon -= 1;
    end.tm_year -= 1900;
    end.tm_mon -= 1;


    time_t quirky_start = mktime(&start);
    time_t quirky_end = mktime(&end);

    int int_seconds = quirky_end-quirky_start;

    if(strchr(format,':'))
    return int_seconds;

        int_seconds = 0;
        for (time_t current = quirky_start; current < quirky_end; current += 24 * 60 * 60)
        int_seconds++;


    return int_seconds;
}
void swap_pointers(void ** s1, void ** s2){
    void *temp = *s1;
    *s1 = *s2;
    *s2 = temp;
}
void swap_strings(char ** s1, char ** s2){
    char *temp = *s1;
    *s1 = *s2;
    *s2 = temp;
}
void swap_ints(int * a, int * b){
    int temp = *a;
    *a = *b;
    *b = temp;
}
///////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////
int median(int * array, int amount){
    if (amount % 2 == 0)
    return ((array[amount / 2 - 1] + array[amount / 2]) / 2.0);


    return array[amount / 2];
}
///////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////
char ** line_to_lines(char * line, int * amount){

    char * copy = strdup(line);
    char * copy_origin = copy;
    char * token = NULL;

    char ** list = malloc(sizeof(char *) * 256);

    for(int i = 0; i < 256; i++)
    list[i] = NULL;

    int i;

    for(i = 0; (token = strsep(&copy, ";")) &&  i < 256;i++)
        list[i] = strdup(token);


    (*amount) = i;
    
    free(copy_origin);

    return list;
}
///////////////////////////////////////////////////////////////