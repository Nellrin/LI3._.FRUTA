#include "../../include/DataStructures/Reservations.h"
#include "../../include/Utilities.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>


////////////////////////////////////////////////////////
typedef struct reservation {
    char *id;
    char *id_hotel;
    char *user_id;
    char *hotel_name;
    
    char *hotel_stars;
    
    char *begin_date;
    char *end_date;
    char *includes_breakfast;
    
    char * rating;

    int nights;
    
    double total_price;
} Reservation;
////////////////////////////////////////////////////////
void print_reservation(Reservation * a){
    printf("\n----------------------------------------------------\n");
    printf("[ID BOOKING]: %s\n",a->id);
    printf("[ID HOTEL]: %s\n",a->id_hotel);
    printf("[ID USER]: %s\n",a->user_id);
    printf("[HOTEL NAME]: %s\n",a->hotel_name);
    printf("[HOTEL STARS]: %s\n",a->hotel_stars);
    printf("[BEGIN DATE]: %s\n",a->begin_date);
    printf("[END DATE]: %s\n",a->end_date);
    printf("[BREAKFAST]: %s\n",a->includes_breakfast);
    printf("[RATING]: %s\n",a->rating);
    printf("[NIGHTS]: %d\n",a->nights);
    printf("[TOTAL COST]: %3f\n",a->total_price);
    printf("----------------------------------------------------\n");

}
////////////////////////////////////////////////////////
Reservation * reservation_setter(char * id,char * id_hotel, char * user_id, char * hotel_name, char * hotel_stars, char * begin_date, char * end_date, char * includes_breakfast, char * rating, char * ppn, char * city_tax){
    Reservation * a = malloc(sizeof(Reservation));
    initialize_utilities();
    
    if (a == NULL)
        return NULL;

    a->id = strdup(id);
    a->id_hotel = strdup(id_hotel);
    a->user_id = strdup(user_id);
    a->hotel_name = strdup(hotel_name);
    a->hotel_stars = strdup(hotel_stars);
    a->begin_date = strdup(begin_date);
    a->end_date = strdup(end_date);
    a->includes_breakfast = strdup(includes_breakfast);
    a->rating = strdup(rating);

    a->nights = Util.time_diff("%d/%d/%d",begin_date,end_date);

    a->total_price = strtod(ppn, NULL) * a->nights + (((strtod(ppn, NULL) * a->nights)/100) * strtod(city_tax, NULL));

    return a;
}
////////////////////////////////////////////////////////
char * reservation_id_getter(Reservation * a){
    char * id = strdup(a->id);

    return id;
}
Reservation * reservation_copy(Reservation * a){
    Reservation * b = reservation_setter(a->id,a->id_hotel,a->user_id,a->hotel_name,a->hotel_stars,a->begin_date,a->end_date,a->includes_breakfast,a->rating,"1","1");
    b->total_price = a->total_price;
    return b;
}
char * reservation_id_hotel_getter(Reservation * a){
    char * id_hotel = strdup(a->id_hotel);

    return id_hotel;
}
char * reservation_user_id_getter(Reservation * a){
    char * user_id = strdup(a->user_id);

    return user_id;
}
char * reservation_hotel_name_getter(Reservation * a){
    char * hotel_name = strdup(a->hotel_name);

    return hotel_name;
}
char * reservation_hotel_stars_getter(Reservation * a){
    char * hotel_stars = strdup(a->hotel_stars);

    return hotel_stars;
}
char * reservation_begin_date_getter(Reservation * a){
    char * begin_date = strdup(a->begin_date);

    return begin_date;
}
char * reservation_end_date_getter(Reservation * a){
    char * end_date = strdup(a->end_date);

    return end_date;
}
char * reservation_include_breakfast_getter(Reservation * a){
    char * includes_breakfast = strdup(a->includes_breakfast);

    return includes_breakfast;
}
char * reservation_rating_getter(Reservation * a){
    char * rating = strdup(a->rating);

    return rating;
}
int reservation_nights_getter(Reservation * a){
    int nights = a->nights;

    return nights;
}
double reservation_total_price_getter(Reservation * a){
    double total_price = a->total_price;

    return total_price;
}
////////////////////////////////////////////////////////
void free_reservation(Reservation *a) {
    if(a!=NULL){

        free(a->id);
        free(a->id_hotel);
        free(a->user_id);
        
        free(a->hotel_name);
        free(a->hotel_stars);
        
        free(a->begin_date);
        free(a->end_date);
        
        free(a->includes_breakfast);
        free(a->rating);
        
        free(a);
    }
}
////////////////////////////////////////////////////////