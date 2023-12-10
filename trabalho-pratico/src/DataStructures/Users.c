#include "../../include/DataStructures/Users.h"
#include "../../include/DataStructures/SLists.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

////////////////////////////////////////////////////////
struct user {
    char *id;
    char *name;
    char *birth_date;
    char *sex;
    char *country_code;
    char *account_status;
    char *account_creation;

    double total_spent;

    SList * flights_went;
    SList * reservations_done;
};
////////////////////////////////////////////////////////
void print_user(User * a){
    printf("\n----------------------------------------------------\n");
    printf("[ID]: %s\n",a->id);
    printf("[NAME]: %s\n",a->name);
    printf("[BIRTH DATE]: %s\n",a->birth_date);
    printf("[SEX]: %s\n",a->sex);
    printf("[COUNTRY CODE]: %s\n",a->country_code);
    printf("[ACCOUNT STATUS]: %s\n",a->account_status);
    printf("\n[TOTAL SPENT]: %.3f\n",a->total_spent);

    int amount1 = slists_amount_getter(a->flights_went);
    char ** list1A = slists_listA_getter(a->flights_went);
    char ** list1B = slists_listB_getter(a->flights_went);

    printf("\n[TOTAL FLIGHTS WENT]: %d\n",amount1);
    
    for(int i = 0; i < amount1; i++){
        printf("[%s] [%s]\n",list1A[i],list1B[i]);
        free(list1A[i]);
        free(list1B[i]);
    }

        free(list1A);
        free(list1B);

    int amount2 = slists_amount_getter(a->reservations_done);
    char ** list2A = slists_listA_getter(a->reservations_done);
    char ** list2B = slists_listB_getter(a->reservations_done);

    printf("\n[TOTAL RESERVATIONS DONE]: %d\n",amount2);
    
    for(int i = 0; i < amount2; i++){
        printf("[%s] [%s]\n",list2A[i],list2B[i]);
        free(list2A[i]);
        free(list2B[i]);
    }

    free(list2A);
    free(list2B);

    printf("----------------------------------------------------\n");
}
////////////////////////////////////////////////////////
User * user_setter(char * id,char * name, char * birth_date, char * sex, char * country_code, char * account_status, char * account_creation){
    User * a = malloc(sizeof(User));
    
    if (a == NULL)
        return NULL;

    a->id = strdup(id);
    a->name = strdup(name);
    a->birth_date = strdup(birth_date);
    a->sex = strdup(sex);
    a->country_code = strdup(country_code);
    a->account_status = strdup(account_status);
    a->account_creation = strdup(account_creation);

    a->total_spent = 0;

    a->flights_went = slist_setter();
    a->reservations_done = slist_setter();

    return a;
}
////////////////////////////////////////////////////////
char * user_id_getter(User * a){
    if(a==NULL)
    return NULL;
    
    char * id = strdup(a->id);

    return id;
}
char * user_name_getter(User * a){
    char * name = strdup(a->name);

    return name;
}
char * user_birth_date_getter(User * a){
    char * birth_date = strdup(a->birth_date);

    return birth_date;
}
char * user_sex_getter(User * a){
    char * sex = strdup(a->sex);

    return sex;
}
char * user_country_code_getter(User * a){
    char * country_code = strdup(a->country_code);

    return country_code;
}
char * user_account_status_getter(User * a){
    char * account_status = strdup(a->account_status);

    return account_status;
}
char * user_account_creation_getter(User * a){
    char * account_creation = strdup(a->account_creation);

    return account_creation;
}

double user_total_spent_getter(User * a){
    double total_spent = a->total_spent;

    return total_spent;
}
SList * user_flight_getter(User * a){
    SList * x = slist_setter();
    
    slist_copy(x,a->flights_went);
    return x;
}
SList * user_reservation_getter(User * a){
    SList * x = slist_setter();
    
    slist_copy(x,a->reservations_done);
    return x;
}

User * user_copy(User * a){
    User * res = malloc(sizeof(User));

    res->id = strdup(a->id);
    res->name = strdup(a->name);
    res->birth_date = strdup(a->birth_date);
    res->sex = strdup(a->sex);
    res->country_code = strdup(a->country_code);
    res->account_status = strdup(a->account_status);
    res->account_creation = strdup(a->account_creation);
    res->total_spent = a->total_spent;

    res->flights_went = slist_setter();
    res->reservations_done = slist_setter();

    slist_copy(res->flights_went,a->flights_went);
    slist_copy(res->reservations_done,a->reservations_done);

    return res;
}
////////////////////////////////////////////////////////
void free_user(User *a) {
    if (a != NULL) {
        free(a->id);
        free(a->name);
        free(a->birth_date);
        free(a->sex);
        free(a->country_code);
        free(a->account_status);
        free(a->account_creation);

        free_slists(a->flights_went);
        free_slists(a->reservations_done);

        free(a);
    }
}
////////////////////////////////////////////////////////
void user_add_flight(User * a, char * id, char * date){

    if (a == NULL)
        return;
    int amount = slists_amount_getter(a->flights_went);
    
    if(!strcmp("",date))
    insert_slistB(a->flights_went,id);

    else
    insert_slistA(a->flights_went,date,id);
    
}
void user_add_reservation(User * a, char * id, char * date, float amount_spent){
    if (a == NULL)
        return;

        insert_slistB(a->reservations_done,id);
        insert_slistA(a->reservations_done,date,id);

    a->total_spent+=amount_spent;
}
void sort_user_slists(User * a){
    slist_sort(a->reservations_done);
    slist_sort(a->flights_went);
}
void remove_flight(User *a, char * str) {    
    remove_element(a->flights_went,str);
}
////////////////////////////////////////////////////////