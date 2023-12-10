#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "../include/Parser.h"
#include "../include/Utilities.h"
#include "../include/Output.h"
// #include "../include/Catalogs/Flight_Catalog.h"
// #include "../include/Catalogs/User_Catalog.h"
#include "../include/Catalogs/Catalog_Functions.h"
#include "../include/DataStructures/Functions.h"



int parser_users(const char * string, Almanac * box){
    initialize_catalog_functions();
    initialize_utilities();
// char * id, *name, *birth_date, *sex, *country_code, *account_status, *account_creation;
// char * email, *phone, *passport, *address, *payment_method;
    char * copy = strdup(string);
    char * copy_origin = copy;
    int res = 0;
    char ** list = malloc(sizeof(char *)*12);
    char *token = NULL;
    
    for(int i = 0;token = strsep(&copy, ";");i++)
    list[i] = strdup(token);
    
    if(Util.validations.string(list[0])
    && Util.validations.string(list[1])
    && Util.validations.string(list[2])
    && Util.validations.string(list[3])
    && Util.validations.string(list[4]) && Util.validations.date(list[4],0)
    && Util.validations.string(list[5])
    && Util.validations.string(list[6])
    && Util.validations.string(list[7]) && Util.validations.country_code(list[7])
    && Util.validations.string(list[8])
    && Util.validations.string(list[9]) && Util.validations.date(list[9],1) && ((strcmp(list[9],list[4]))>0)
    && Util.validations.string(list[10])
    && Util.validations.string(list[11]) && Util.validations.account_status(list[11])
    && Util.validations.email(list[2])){
        User * user = Data.user.set(list[0],list[1],list[4],list[5],list[7],list[11],list[9]);
        Catalog.user.insert(box,user);
        res ++;
    }

    for(int i = 0; i < 12; i++){
        // printf("%s/",list[i]);
        free(list[i]);
    }

    // printf("\n");
    free(list);
    free(copy_origin);
    free(token);

    return res;
}

int parser_flight(const char * string, Almanac * box){
    initialize_utilities();
    initialize_catalog_functions();

// real_departure_date real_arrival_date pilot copilot notes

    char * copy = strdup(string);
    char * copy_origin = copy;
    int res = 0;
    char ** list = malloc(sizeof(char *)*13);
    char *token = NULL;
    Flight * flight;
    
    for(int i = 0;token = strsep(&copy, ";");i++)
    list[i] = strdup(token);
    
    if(Util.validations.string(list[0])
    && Util.validations.string(list[1])
    && Util.validations.string(list[2])
    && Util.validations.string(list[3])){

        int amount = atoi(list[3]),seats = 0, id_num = atoi(list[0]);
        
        SList * x = Catalog.flight.get.passengers(box,id_num);
        
        seats = Data.slist.get.amount(x);

        Data.slist.free(x);
        printf("%s (available %d) < (%d true)\n",list[0], amount, seats);
    
        if(amount>=seats 
        && Util.validations.string(list[4]) && Util.validations.airport(list[4])
        && Util.validations.string(list[5]) && Util.validations.airport(list[5])  && (strcmp(list[4], list[5]) != 0)
        && Util.validations.string(list[6]) && Util.validations.date(list[6],1)
        && Util.validations.string(list[7]) && Util.validations.date(list[7],1) && strcmp(list[7],list[6])
        && Util.validations.string(list[8]) && Util.validations.date(list[8],1) && ((strcmp(list[8],list[6]))>=0)
        && Util.validations.string(list[9]) && Util.validations.date(list[9],1) && ((strcmp(list[9],list[7]))>=0)
        && Util.validations.string(list[10])
        && Util.validations.string(list[11])){
            res ++;
            flight = Data.flight.new(list[0]);
            Data.flight.set(flight,list[1],list[2],list[4],list[5],list[6],list[8],list[7]);
            Catalog.flight.insert(box,flight);
        }
    }

    for(int i = 0; i < 13; i++){
        // printf("%s/",list[i]);
        free(list[i]);
        }

    // printf("\n");
    free(list);
    free(copy_origin);
    free(token);


    return res;
}

// int parser_passengers(const char * string, Almanac * box){
//     initialize_utilities();
//     initialize_functions();

    
//     char * copy = strdup(string);
//     char * copy_origin = copy;
//     char ** list = malloc(sizeof(char *)*2);
//     char *token = NULL;
    
//     for(int i = 0;token = strsep(&copy, ";");i++)
//     list[i] = strdup(token);

    
//     if(Util.validations.string(list[0])&& Util.validations.string(list[1])){
//         User * user = find_user(box->users->users,list[1]);
//         if(user!=NULL){
//         Flight * flight = find_flight(box->flights,list[0]);
        
//         if(flight == NULL){
//             flight = Data.flight.new(list[0]);
//             add_catalog_flight(box,flight,list[0]);
//         }

//         else
//         Data.flight.add_passenger(flight);
//         }
//     }   


//     for(int i = 0; i < 2; i++)
//     free(list[i]);

//     free(list);
//     free(copy_origin);
//     free(token);

//     return 0;
// }

int count_passengers(const char * string, Almanac * box){
    initialize_utilities();
    initialize_functions();
    
    char * copy = strdup(string);
    char * copy_origin = copy;
    int res = 1;
    char ** list = malloc(sizeof(char *)*2);
    char *token = NULL;
    
    for(int i = 0;token = strsep(&copy, ";");i++)
    list[i] = strdup(token);

    
    if(Util.validations.string(list[0])&& Util.validations.string(list[1])){
        User * user = Catalog.user.get.user(box,list[1]);
        if(user!=NULL){
            Data.user.free(user);
            Catalog.flight.add_passenger(box,list[1],list[0]);
        }
    }

    for(int i = 0; i < 2; i++)
    free(list[i]);

    free(list);
    free(copy_origin);
    free(token);

    return res;
}

void parser(char * path,char * type,Almanac * box, int (*f)(const char *, Almanac *)){
    initialize_catalog_functions();


    char * name = malloc(sizeof(char)*200);

    int take_nl,amount = 0;

    snprintf(name, 200, "%s/%s.csv", path, type);
    FILE * file = create_file(name,"r");

    free(name);

    name = malloc(sizeof(char)*200);
    snprintf(name, 200, "Resultados/%s_errors.csv", type);
    FILE * errors = create_file(name,"a");


    char *head = NULL;
    size_t len = 0;
    if(getline(&head, &len, file));
    write_line(errors,head);
    
    int i = 0;
    while (getline(&head, &len, file) != -1) {
        char *line = strdup(head);
        take_nl = strlen(head)-1;
        head[take_nl] = '\0';

        if(f(head,box))
        amount++;

        else{
        // printf("%s",line);
        write_line(errors,line);
        }
        // printf("%s\n",head);
        free(line);

        i ++;
        // printf(" [%d] ",i);
    }

    printf("\n\n%d\n\n",amount);

    free(head);
    free(name);
    fclose(file);
    fclose(errors);
}