#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../../include/DataStructures/Calendar.h"
#include "../../include/DataStructures/FHash.h"
#include "../../include/Catalogs/Calendar_Catalog.h"

////////////////////////////////////////////////////////
struct c_almanac{
    short amount_years;
    char ** id_years;
    FHash * years;
};

struct g_date{
    char * general_date_id;
    Date_Counter * general_date;


    short amount_of_general_dates_inside;
    char ** ids_of_general_dates_inside;
    FHash * general_dates_inside;
};

////////////////////////////////////////////////////////


////////////////////////////////////////////////////////
static int compare_general_date(const char * id, const void * info){
    const General_Date * node = (const General_Date *)info;

    return (strcmp(id, node->general_date_id)==0);
}
static General_Date * init_general_date(char * id, int amount){
    General_Date * a = malloc(sizeof(General_Date));

    a->general_date_id = strdup(id);

    a->general_date = create_date();



    a->amount_of_general_dates_inside = 0;
    a->ids_of_general_dates_inside = NULL;



    if(amount != 0)
    a->general_dates_inside = fhash_init(amount);

    else
    a->general_dates_inside = NULL;

    return a;
}
static void free_nodes(void * info){
    General_Date * a = (General_Date *)info;

    if(a != NULL){

        free(a->general_date_id);
        free_date(a->general_date);

            for(int i = 0; i < a->amount_of_general_dates_inside; i++)
                free(a->ids_of_general_dates_inside[i]);

            free(a->ids_of_general_dates_inside);

        if(a->general_dates_inside!=NULL)
        free_fhash(a->general_dates_inside,free_nodes);


        free(a);

    }
}
////////////////////////////////////////////////////////


////////////////////////////////////////////////////////
Calendar_Almanac * init_calendar_almanac(){
    Calendar_Almanac * a = malloc(sizeof(Calendar_Almanac));

    a->amount_years = 0;
    a->id_years = NULL;
    a->years = fhash_init(10);

    return a;
}
void free_calendar_almanac(Calendar_Almanac * a){

    for(int i = 0; i < a->amount_years; i++)
    free(a->id_years[i]);

    free(a->id_years);

    free_fhash(a->years,free_nodes);

    free(a);
}
////////////////////////////////////////////////////////


////////////////////////////////////////////////////////
void calendar_add(Calendar_Almanac *a, char * date, int amount,short type, void (*f)(void*,int)){


    char * copy = NULL;
    char * origin = NULL;
    char * token = NULL;

    char ** list = NULL;

    General_Date * x = NULL;
    General_Date * y = NULL;
    General_Date * z = NULL;



    switch (type){
    case 0:
        
                copy = strdup(date);
                origin = copy;
                token = NULL;

                list = malloc(sizeof(char *) * 3);

                for(int i = 0; i < 2; i++){
                    list[i] = NULL;
                    token = strsep(&copy, "/");
                    list[i] = strdup(token);
                }


                    list[2] = NULL;
                    token = strsep(&copy, " ");
                    list[2] = strdup(token);





                x = fhash_get(a->years,list[0],1,compare_general_date);

                if(x == NULL){
                    x = init_general_date(list[0],12);
                    fhash_add(a->years,list[0],x,1);
                    
                    char ** listA = (char **)realloc(a->id_years, sizeof(char *) * (a->amount_years + 1));
                    a->id_years = listA;

                    a->id_years[a->amount_years] = strdup(list[0]);
                    a->amount_years ++;

                }

                f(x->general_date,amount);


                    y = fhash_get(x->general_dates_inside,list[1],1,compare_general_date);

                    if(y == NULL){
                        y = init_general_date(list[1],31);
                        fhash_add(x->general_dates_inside,list[1],y,1);
                        
                        char ** listB = (char **)realloc(x->ids_of_general_dates_inside, sizeof(char *) * (x->amount_of_general_dates_inside + 1));
                        x->ids_of_general_dates_inside = listB;

                        x->ids_of_general_dates_inside[x->amount_of_general_dates_inside] = strdup(list[1]);
                        x->amount_of_general_dates_inside ++;

                    }

                    f(y->general_date,amount);

                        z = fhash_get(y->general_dates_inside,list[2],1,compare_general_date);

                        if(z == NULL){

                            z = init_general_date(list[2],0);
                            fhash_add(y->general_dates_inside,list[2],z,1);
                            
                            char ** listC = (char **)realloc(y->ids_of_general_dates_inside, sizeof(char *) * (y->amount_of_general_dates_inside + 1));
                            y->ids_of_general_dates_inside = listC;

                            y->ids_of_general_dates_inside[y->amount_of_general_dates_inside] = strdup(list[2]);
                            y->amount_of_general_dates_inside ++;

                        }

                        f(z->general_date,amount);



                free(origin);
                for(int i = 0; i < 3; i++)
                free(list[i]);

                free(list);

        break;

            case 1:
                date[10]='\0';
                copy = strdup(date);
                origin = copy;
                token = NULL;

                list = malloc(sizeof(char *) * 3);

                for(int i = 0; i < 2; i++){
                    list[i] = NULL;
                    token = strsep(&copy, "/");
                    list[i] = strdup(token);
                }


                    list[2] = NULL;
                    token = strsep(&copy, " ");
                    list[2] = strdup(token);





                x = fhash_get(a->years,list[0],1,compare_general_date);

                if(x == NULL){
                    x = init_general_date(list[0],12);
                    fhash_add(a->years,list[0],x,1);
                    
                    char ** listA = (char **)realloc(a->id_years, sizeof(char *) * (a->amount_years + 1));
                    a->id_years = listA;

                    a->id_years[a->amount_years] = strdup(list[0]);
                    a->amount_years ++;

                }

                    y = fhash_get(x->general_dates_inside,list[1],1,compare_general_date);

                    if(y == NULL){
                        y = init_general_date(list[1],31);
                        fhash_add(x->general_dates_inside,list[1],y,1);
                        
                        char ** listB = (char **)realloc(x->ids_of_general_dates_inside, sizeof(char *) * (x->amount_of_general_dates_inside + 1));
                        x->ids_of_general_dates_inside = listB;

                        x->ids_of_general_dates_inside[x->amount_of_general_dates_inside] = strdup(list[1]);
                        x->amount_of_general_dates_inside ++;

                    }

                        z = fhash_get(y->general_dates_inside,list[2],1,compare_general_date);

                        if(z == NULL){

                            z = init_general_date(list[2],0);
                            fhash_add(y->general_dates_inside,list[2],z,1);
                            
                            char ** listC = (char **)realloc(y->ids_of_general_dates_inside, sizeof(char *) * (y->amount_of_general_dates_inside + 1));
                            y->ids_of_general_dates_inside = listC;

                            y->ids_of_general_dates_inside[y->amount_of_general_dates_inside] = strdup(list[2]);
                            y->amount_of_general_dates_inside ++;

                        }

                        f(z->general_date,amount);



                free(origin);
                for(int i = 0; i < 3; i++)
                free(list[i]);

                free(list);

        break;
    
        case 2:
                date[7]='\0';
                copy = strdup(date);
                origin = copy;
                token = NULL;

                char ** list = malloc(sizeof(char *) * 2);

                for(int i = 0; i < 2; i++){
                    list[i] = NULL;
                    token = strsep(&copy, "/");
                    list[i] = strdup(token);
                }





                x = fhash_get(a->years,list[0],1,compare_general_date);

                if(x == NULL){
                    x = init_general_date(list[0],12);
                    fhash_add(a->years,list[0],x,1);
                    
                    char ** listA = (char **)realloc(a->id_years, sizeof(char *) * (a->amount_years + 1));
                    a->id_years = listA;

                    a->id_years[a->amount_years] = strdup(list[0]);
                    a->amount_years ++;

                }

                    y = fhash_get(x->general_dates_inside,list[1],1,compare_general_date);

                    if(y == NULL){
                        y = init_general_date(list[1],31);
                        fhash_add(x->general_dates_inside,list[1],y,1);
                        
                        char ** listB = (char **)realloc(x->ids_of_general_dates_inside, sizeof(char *) * (x->amount_of_general_dates_inside + 1));
                        x->ids_of_general_dates_inside = listB;

                        x->ids_of_general_dates_inside[x->amount_of_general_dates_inside] = strdup(list[1]);
                        x->amount_of_general_dates_inside ++;

                    }

                    f(y->general_date,amount);


                free(origin);
                for(int i = 0; i < 2; i++)
                free(list[i]);

                free(list);

        break;


                case 3:
        
                    date[4]='\0';
                    copy = strdup(date);

                    x = fhash_get(a->years,copy,1,compare_general_date);

                    if(x == NULL){
                        x = init_general_date(copy,12);
                        fhash_add(a->years,copy,x,1);
                        
                        char ** listA = (char **)realloc(a->id_years, sizeof(char *) * (a->amount_years + 1));
                        a->id_years = listA;

                        a->id_years[a->amount_years] = strdup(copy);
                        a->amount_years ++;

                    }

                    f(x->general_date,amount);

                    free(copy);


        break;


    default:
        break;
    }



}
void calendar_get(Calendar_Almanac *a,char ** arguments,int num_arguments,int * amount,int ** year, int ** user, int ** fli, int ** res,int ** pas, int ** uni_pas){

        int * years = NULL;
        int * passengers = NULL;
        int * unique_passengers = NULL;
        int * reservations = NULL;
        int * users = NULL;
        int * flights = NULL;


        General_Date * x = NULL;
        General_Date * y = NULL;
        General_Date * z = NULL;


    switch (num_arguments){
    case 0:

        *amount = a->amount_years;

        years = malloc(sizeof(int)*(*amount));
        passengers = malloc(sizeof(int)*(*amount));
        unique_passengers = malloc(sizeof(int)*(*amount));
        reservations = malloc(sizeof(int)*(*amount));
        users = malloc(sizeof(int)*(*amount));
        flights = malloc(sizeof(int)*(*amount));

        for(int i = 0; i < (*amount); i++){
            x = fhash_get(a->years,a->id_years[i],1,compare_general_date);
            
            years[i] = atoi(a->id_years[i]);
            
            passengers[i] = get_date_passengers(x->general_date);
            unique_passengers[i] = get_date_unique_passengers(x->general_date);
            reservations[i] = get_date_reservations(x->general_date);
            users[i] = get_date_users(x->general_date);
            flights[i] = get_date_flights(x->general_date);
        }


        break;

    case 1:
        
        x = fhash_get(a->years,arguments[1],1,compare_general_date);

        if(x == NULL)
        return;

            *amount = x->amount_of_general_dates_inside;

            years = malloc(sizeof(int)*(*amount));
            passengers = malloc(sizeof(int)*(*amount));
            unique_passengers = malloc(sizeof(int)*(*amount));
            reservations = malloc(sizeof(int)*(*amount));
            users = malloc(sizeof(int)*(*amount));
            flights = malloc(sizeof(int)*(*amount));

            for(int i = 0; i < (*amount); i++){
                
                y = fhash_get(x->general_dates_inside,x->ids_of_general_dates_inside[i],1,compare_general_date);
                
                years[i] = atoi(x->ids_of_general_dates_inside[i]);
                
                passengers[i] = get_date_passengers(y->general_date);
                unique_passengers[i] = get_date_unique_passengers(y->general_date);
                reservations[i] = get_date_reservations(y->general_date);
                users[i] = get_date_users(y->general_date);
                flights[i] = get_date_flights(y->general_date);
            }

        break;

    case 2:

    
        x = fhash_get(a->years,arguments[1],1,compare_general_date);

        if(x == NULL)
        return;

            y = fhash_get(x->general_dates_inside,arguments[2],1,compare_general_date);

            if(y == NULL)
            return;

                *amount = y->amount_of_general_dates_inside;

                years = malloc(sizeof(int)*(*amount));
                passengers = malloc(sizeof(int)*(*amount));
                unique_passengers = malloc(sizeof(int)*(*amount));
                reservations = malloc(sizeof(int)*(*amount));
                users = malloc(sizeof(int)*(*amount));
                flights = malloc(sizeof(int)*(*amount));

                for(int i = 0; i < (*amount); i++){
                    
                    z = fhash_get(y->general_dates_inside,y->ids_of_general_dates_inside[i],1,compare_general_date);
                    
                    years[i] = atoi(y->ids_of_general_dates_inside[i]);
                    
                    passengers[i] = get_date_passengers(z->general_date);
                    unique_passengers[i] = get_date_unique_passengers(z->general_date);
                    reservations[i] = get_date_reservations(z->general_date);
                    users[i] = get_date_users(z->general_date);
                    flights[i] = get_date_flights(z->general_date);
                }

        break;
    

    default:
            printf("Número de argumentos inválido");
        break;
    }


        *year = years;
        *pas = passengers;
        *uni_pas = unique_passengers;
        *res = reservations;
        *user = users;
        *fli = flights;

}
////////////////////////////////////////////////////////
