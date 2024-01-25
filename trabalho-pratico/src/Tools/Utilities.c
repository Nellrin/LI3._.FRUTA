#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include <time.h>
#include <locale.h>


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
int compare_strings(char* str1, char* str2, char* id1, char* id2) {

    int name_compare = strcoll(str1, str2);
    if (name_compare == 0) {
        return strcoll(id1, id2);
    }
    return name_compare;
}

static int partition(char*** arr, char*** ids, int low, int high, int (*f)(char*,char*,char*,char*)) {
    char* pivot = (*arr)[high];
    char* pivotId = (*ids)[high];
    int i = low - 1;

    for (int j = low; j <= high - 1; j++) {
        if (f((*arr)[j], pivot, (*ids)[j], pivotId) < 0) {
            i++;
            swap_strings(&(*arr)[i], &(*arr)[j]);
            swap_strings(&(*ids)[i], &(*ids)[j]);
        }
    }

    swap_strings(&(*arr)[i + 1], &(*arr)[high]);
    swap_strings(&(*ids)[i + 1], &(*ids)[high]);
    return i + 1;
}

static void quick_sort(char*** arr, char*** ids, int low, int high, int (*f)(char*,char*,char*,char*)) {
    if (low < high) {
        int partition_index = partition(arr, ids, low, high,f);

        quick_sort(arr, ids, low, partition_index - 1, f);
        quick_sort(arr, ids, partition_index + 1, high, f);
    }
}

void sort_strings(char*** arr, char*** ids, int count, int (*f)(char*,char*,char*,char*)) {
    setlocale(LC_COLLATE, "en_US.UTF-8"); 
    quick_sort(arr, ids, 0, count - 1, f);
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

    for(i = 0; (token = strsep(&copy, "\\")) &&  i < 256;i++)
        list[i] = strdup(token);


    (*amount) = i;
    
    free(copy_origin);

    return list;
}
int count_lines(const char *str){
    FILE * file = fopen(str,"r");
    
    if(file == NULL) return 0;

    int count = 0;
    char * line = malloc(sizeof(char) * 256);
    
    while(fgets(line, 256, file) != NULL)
    count ++;

    fclose(file);
    free(line);

    return count;
}
int count_chars(const char *str, char c) {
    int count = 0;

    while (*str) {
            if (*str == c)
            count++;
        str++;
    }

    return count;
}
///////////////////////////////////////////////////////////////