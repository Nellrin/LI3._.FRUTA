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
    char *sex;
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
        printf("[SEX]: %s\n",a->sex);
        printf("[COUNTRY CODE]: %s\n",a->country_code);
        printf("[ACCOUNT STATUS]: %d\n",a->account_status);
        printf("[PASSPORT]: %s\n",a->passport);

        printf("----------------------------------------------------\n");
    }
}
////////////////////////////////////////////////////////


////////////////////////////////////////////////////////
User * set_user(char * id,char * name, char * birth_date, char * sex, char * country_code, short account_status, char * account_creation, char * passport){
    User * a = malloc(sizeof(User));
    
    if (a == NULL)
        return NULL;

    a->id = strdup(id);
    a->name = strdup(name);
    a->birth_date = strdup(birth_date);
    a->sex = strdup(sex);
    a->country_code = strdup(country_code);
    a->account_status = (account_status);
    a->account_creation = strdup(account_creation);
    a->passport = strdup(passport);

    return a;
}
////////////////////////////////////////////////////////


////////////////////////////////////////////////////////
char * get_userID(User * a){
    if(a==NULL)
    return NULL;
    
    char * id = strdup(a->id);

    return id;
}
char * get_userNAME(User * a){
    char * name = strdup(a->name);

    return name;
}
char * get_userBDAY(User * a){
    char * birth_date = strdup(a->birth_date);

    return birth_date;
}
char * get_userSEX(User * a){
    char * sex = strdup(a->sex);

    return sex;
}
char * get_userCOUNTRY(User * a){
    char * country_code = strdup(a->country_code);

    return country_code;
}
short get_userASTATUS(User * a){
    return a->account_status;
}
char * get_userACREATION(User * a){
    char * account_creation = strdup(a->account_creation);

    return account_creation;
}
char * get_userPASSPORT(User * a){
    char * passport = strdup(a->passport);

    return passport;
}
////////////////////////////////////////////////////////


////////////////////////////////////////////////////////
int compare_user(const char *id, const void *info) {
    const User *user = (const User *)info;
    return (strcmp(id, user->id) == 0);
}


static void removeSpacesAndHyphens(char *str) {
    if (str == NULL) {
        return;
    }

    // Iterate through the string and remove spaces and hyphens
    char *src = str;
    char *dst = str;

    while (*src) {
        if (*src != ' ' && *src != '-') {
            *dst = *src;
            dst++;
        }

        src++;
    }

    *dst = '\0'; // Null-terminate the modified string
}

static int compare_prefix(char* a, char* b) {

    setlocale(LC_COLLATE, "en_US.UTF-8"); //Configura a localização

    int result = strcoll(a, b);

    return result;
}

int compare_user_prefix(const void *a, const void *b) {
    User *userA = (User *)a;
    User *userB = (User *)b;

    char * nameA = get_userNAME(userA);
    char * nameB = get_userNAME(userB);

    removeSpacesAndHyphens(nameA);
    removeSpacesAndHyphens(nameB);


    int res = compare_prefix(nameA, nameB);
    free(nameA);free(nameB);
    
    if(!res)
        return compare_prefix(userA->id,userB->id);

    return (res);
}
////////////////////////////////////////////////////////


////////////////////////////////////////////////////////
void free_user(void * user) {
    if (user != NULL) {

        User *a = (User *)user;

        free(a->id);
        free(a->name);
        free(a->birth_date);
        free(a->sex);
        free(a->country_code);
        free(a->account_creation);
        free(a->passport);

        free(a);
    }
}
////////////////////////////////////////////////////////