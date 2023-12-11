#include "../../include/DataStructures/Hotel.h"
#include "../../include/DataStructures/Reservations.h"
#include "../../include/DataStructures/SLists.h"
#include "../../include/Utilities.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

////////////////////////////////////////////////////////
typedef struct hotel {
    char * hotel_id;
    
    int amount_of_ratings;
    double sum_rating;
    
    double price_per_night;
    
    SList * reservation_list;
    SList * begin_end;

} Hotel;
////////////////////////////////////////////////////////
void print_hotel(Hotel * a){
    printf("\n----------------------------------------------------\n");
    printf("[AMOUNT OF RATINGS]: %d\n",a->amount_of_ratings);
    printf("[SUM RATING]: %.3f\n",a->sum_rating);
    printf("[PRICE PER NIGHT]: %.3f\n",a->price_per_night);
    int x = slists_amount_getter(a->reservation_list);
    printf("[AMOUNT OF RESERVATIONS]: %d\n",x);

    char ** list_ids = slists_listA_getter(a->reservation_list);
    char ** list_date = slists_listB_getter(a->reservation_list);
    int amount = slists_amount_getter(a->reservation_list);
    
    for(int i = 0; i<amount;i++){
        printf("[%s | %s]\n",list_ids[i],list_date[i]);
        free(list_ids[i]);
        free(list_date[i]);
    }

    free(list_ids);
    free(list_date);

    printf("----------------------------------------------------\n");

}
////////////////////////////////////////////////////////
Hotel * hotel_setter(char * price_per_night,char * rating, Reservation * reservation){
    Hotel * a = malloc(sizeof(Hotel));
    
    if (a == NULL)
        return NULL;

    
    if(!strcmp(rating,"")){
        a->amount_of_ratings = 0;
        a->sum_rating = 0;
    }

    else{
        a->amount_of_ratings = 1;
        a->sum_rating = strtod(rating,NULL);
    }

    a->hotel_id = reservation_id_hotel_getter(reservation);
    a->price_per_night = strtod(price_per_night,NULL);
    
    char * begin = reservation_begin_date_getter(reservation);
    char * end = reservation_end_date_getter(reservation);
    
    a->reservation_list = slist_setter();
    a->begin_end = slist_setter();
    
    hotel_add_reservation(a,reservation);

    free(begin);
    free(end);

    return a;
}
////////////////////////////////////////////////////////
char * hotel_id_getter(Hotel * a){
    char * id = strdup(a->hotel_id);

    return id;
}
double hotel_ratings_getter(Hotel * a){
    int amount = slists_amount_getter(a->reservation_list);
    double rating = a->sum_rating/amount;

    return rating;
}
double hotel_ppn_getter(Hotel * a){
    double ppn = a->price_per_night;

    return ppn;
}
SList * hotel_reservation_getter(Hotel * a){
    SList * list = slist_setter();
    slist_copy(list,a->reservation_list);

    return list;
}
SList * hotel_dates_getter(Hotel * a){
    SList * list = slist_setter();
    slist_copy(list,a->begin_end);

    return list;
}
double hotel_revenue_getter(Hotel * a,char * begin, char * end){

    initialize_utilities();

    double total = 0;

    int x,y,z,days;
    sscanf(begin,"%d/%d/%d",&x,&y,&z);
    days = Util.time_diff("%d/%d/%d",begin,end);

    // for(int i = 0; i<= days; i++){
    //     if(z > 31){y++;z=1;}
    //     if(y > 12){x++;y=1;z=1;}
    //     total += (a->schedule[2023-x][y-1][z-1]*a->price_per_night);
    //     z++;
    // }

    return total;
}
Hotel * hotel_copy(Hotel * a){
    Hotel * b = malloc(sizeof(Hotel));
    b->hotel_id = strdup(a->hotel_id);
    
    b->amount_of_ratings = a->amount_of_ratings;

    b->sum_rating = a->sum_rating;

    b->price_per_night = a->price_per_night;
    b->reservation_list = hotel_reservation_getter(a);
    b->begin_end = hotel_dates_getter(a);
    return b;
}
////////////////////////////////////////////////////////
static void insert_reservation(Hotel * a, char *begin, char *id){

    char * c = strdup(begin);
    char * b = strdup(id);
    
    insert_slistB(a->reservation_list, b);
    insert_slistA(a->reservation_list,c, b);

    free(c);
    free(b);
}
static void insert_begin_end(Hotel * a, char *begin,char * end){
    char * c = strdup(begin);
    char * b = strdup(end);

    insert_slistB(a->begin_end, b);
    insert_slistA(a->begin_end, c, b);


    free(c);
    free(b);
}
////////////////////////////////////////////////////////
void hotel_add_reservation(Hotel * a, Reservation * reservation){
    char * rating = reservation_rating_getter(reservation);
    char * begin = reservation_begin_date_getter(reservation);
    char * end = reservation_end_date_getter(reservation);
    char * id = reservation_id_getter(reservation);

    double x = strtod(rating,NULL);
    a->sum_rating += x;
    a->amount_of_ratings += ((x==0)?0:1);


    insert_begin_end(a,begin,end);
    insert_reservation(a,begin,id);

    free(id);
    free(rating);
    free(begin);
    free(end);
}
void sort_hotels_slists(Hotel * a){
    slist_sort(a->reservation_list);
    slist_sort(a->begin_end);
}
////////////////////////////////////////////////////////
void free_hotel(Hotel *a) {

        if(a!=NULL){
            free(a->hotel_id);
            free_slists(a->reservation_list);
            free_slists(a->begin_end);
            free(a);
        }
}
////////////////////////////////////////////////////////