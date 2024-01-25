#include "../../include/DataStructures/Users.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <locale.h>

////////////////////////////////////////////////////////
struct user {
    char *id;
    char *name;
    char *birth_date;
    short sex;
    char *passport;
    char *country_code;
    char *account_creation;
    short account_status;
};
////////////////////////////////////////////////////////


////////////////////////////////////////////////////////
void print_user(User * a){
    if(a != NULL){
        printf("\n----------------------------------------------------\n");
        printf("[ID]: %s\n",a->id);
        printf("[NAME]: %s\n",a->name);
        printf("[BIRTH DATE]: %s\n",a->birth_date);
        printf("[SEX]: %d\n",a->sex);
        printf("[COUNTRY CODE]: %s\n",a->country_code);
        printf("[ACCOUNT STATUS]: %d\n",a->account_status);
        printf("[PASSPORT]: %s\n",a->passport);

        printf("----------------------------------------------------\n");
    }
}
////////////////////////////////////////////////////////


////////////////////////////////////////////////////////
User * set_user(char * id,char * name, char * birth_date, short sex, char * country_code, short account_status, char * account_creation, char * passport){
    User * a = malloc(sizeof(User));
    
    if (a == NULL)
        return NULL;

    a->id = strdup(id);
    a->name = strdup(name);
    a->birth_date = strdup(birth_date);
    a->sex = (sex);
    a->country_code = strdup(country_code);
    a->account_status = (account_status);
    a->account_creation = strdup(account_creation);
    a->passport = strdup(passport);

    return a;
}
////////////////////////////////////////////////////////


////////////////////////////////////////////////////////
const char * get_userID(User * a){
    return (a->id);
}
const char * get_userNAME(User * a){
    return (a->name);
}
char * get_userBDAY(User * a){
    return strdup(a->birth_date);
}
short get_userSEX(User * a){
    short sex = (a->sex);

    return sex;
}
char * get_userCOUNTRY(User * a){
    return strdup(a->country_code);
}
short get_userASTATUS(User * a){
    short status = a->account_status;
    return status;
}
char * get_userACREATION(User * a){
    return strdup(a->account_creation);
}
char * get_userPASSPORT(User * a){
    return strdup(a->passport);
}
////////////////////////////////////////////////////////


////////////////////////////////////////////////////////
int compare_user(const char *id, const void *info) {
    const User *user = (const User *)info;
    return (strcmp(id, user->id) == 0);
}

static void tira_aspas(char *str) {
    if (str == NULL) {
        return;
    }

    char *src = str;
    char *dst = str;

    while (*src) {
        if (*src != ' ' && *src != '-') {
            *dst = *src;
            dst++;
        }

        src++;
    }

    *dst = '\0';
}

static int compare_prefix(char* a, char* b) {

    setlocale(LC_COLLATE, "en_US.UTF-8"); 

    return strcoll(a, b);
}

int compare_user_prefix(const void *a, const void *b){
    char * nameA = strdup(get_userNAME((User *)a));
    char * nameB = strdup(get_userNAME((User *)b));

    tira_aspas(nameA);
    tira_aspas(nameB);


    int res = compare_prefix(nameA, nameB);
    free(nameA);free(nameB);
    
    if(!res){
        char * idA = strdup(get_userID((User *)a));
        char * idB = strdup(get_userID((User *)b));

        res = compare_prefix(idA,idB);
        free(idA);free(idB);
    }

    return res;
}
////////////////////////////////////////////////////////


////////////////////////////////////////////////////////
void free_user(void * user) {
    if (user != NULL) {

        User *a = (User *)user;

        free(a->id);
        free(a->name);
        free(a->birth_date);
        free(a->country_code);
        free(a->account_creation);
        free(a->passport);

        free(a);
    }
}
////////////////////////////////////////////////////////