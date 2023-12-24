#include "../../include/DataStructures/Reservations.h"
#include "../../include/Utilities.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
////////////////////////////////////////////////////////


////////////////////////////////////////////////////////
struct reservation {
    char *id;
    char *id_hotel;
    char *user_id;
    char *hotel_name;
    
    char *hotel_stars;
    
    char *begin_date;
    char *end_date;
    char *includes_breakfast;
    
    char * city_tax;
    char * ppn;

    char * rating;
};
////////////////////////////////////////////////////////


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
    printf("----------------------------------------------------\n");

}
////////////////////////////////////////////////////////


////////////////////////////////////////////////////////
Reservation * set_reservation(char * id,char * id_hotel, char * user_id, char * hotel_name, char * hotel_stars, char * begin_date, char * end_date, char * includes_breakfast, char * rating, char * ppn, char * city_tax){
    Reservation * a = malloc(sizeof(Reservation));
    
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
    a->city_tax = strdup(city_tax);
    a->ppn = strdup(ppn);
    a->rating = strdup(rating);

    return a;
}
////////////////////////////////////////////////////////


////////////////////////////////////////////////////////
char * get_reservationID(Reservation * a){
    char * id = strdup(a->id);

    return id;
}
char * get_reservationHOTELID(Reservation * a){
    char * id_hotel = strdup(a->id_hotel);

    return id_hotel;
}
char * get_reservationUSERID(Reservation * a){
    char * user_id = strdup(a->user_id);

    return user_id;
}
char * get_reservationHOTELNAME(Reservation * a){
    char * hotel_name = strdup(a->hotel_name);

    return hotel_name;
}
char * get_reservationSTARS(Reservation * a){
    char * hotel_stars = strdup(a->hotel_stars);

    return hotel_stars;
}
char * get_reservationBEGIN(Reservation * a){
    char * begin_date = strdup(a->begin_date);

    return begin_date;
}
char * get_reservationEND(Reservation * a){
    char * end_date = strdup(a->end_date);

    return end_date;
}
char * get_reservationBREAKFAST(Reservation * a){
    char * includes_breakfast = strdup(a->includes_breakfast);

    return includes_breakfast;
}
char * get_reservationPPN(Reservation * a){
    char * ppn = strdup(a->ppn);

    return ppn;
}
char * get_reservationTAX(Reservation * a){
    char * tax = strdup(a->city_tax);

    return tax;
}
char * get_reservationRATING(Reservation * a){
    char * rating = strdup(a->rating);

    return rating;
}
////////////////////////////////////////////////////////


////////////////////////////////////////////////////////
double total_got_from_reservation(const void * info){
    Reservation * a = (Reservation *) info;
    double ppn = strtod(a->ppn,NULL);
    double tax = strtod(a->city_tax,NULL);
    int nights = string_to_time("%d/%d/%d",a->begin_date,a->end_date);

    return (ppn * nights + ((ppn*nights)/100)*tax);
}
////////////////////////////////////////////////////////


////////////////////////////////////////////////////////
int compare_reservation(const char *id, const void *info){
    const Reservation *reservation = (const Reservation *)info;
    return (strcmp(id, reservation->id) == 0);
}
int compare_reservation_date(const void *a, const void *b) {
    const Reservation *reservationA = (const Reservation *)a;
    const Reservation *reservationB = (const Reservation *)b;
    
    return strcmp(reservationA->begin_date, reservationB->begin_date);
}
////////////////////////////////////////////////////////


////////////////////////////////////////////////////////
void free_reservation(void *reservation){

    if(reservation!=NULL){

        Reservation *a = (Reservation *)reservation;


        free(a->id);
        free(a->id_hotel);
        free(a->user_id);
        
        free(a->hotel_name);
        free(a->hotel_stars);
        
        free(a->begin_date);
        free(a->end_date);
        
        free(a->includes_breakfast);
        free(a->rating);

        free(a->ppn);
        free(a->city_tax);
        
        free(a);
    }
}
////////////////////////////////////////////////////////