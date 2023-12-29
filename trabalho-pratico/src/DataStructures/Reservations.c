#include "../../include/DataStructures/Reservations.h"
#include "../../include/Utilities.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
////////////////////////////////////////////////////////


////////////////////////////////////////////////////////
struct reservation {
    char *id;
    short id_hotel;
    char *user_id;
    char *hotel_name;
    
    char *begin_date;
    char *end_date;
    
    short hotel_stars;
    short city_tax;
    short ppn;
    short rating;
    short includes_breakfast;
};
////////////////////////////////////////////////////////


////////////////////////////////////////////////////////
void print_reservation(Reservation * a){
    printf("\n----------------------------------------------------\n");
    printf("[ID BOOKING]: %s\n",a->id);
    printf("[ID HOTEL]: %d\n",a->id_hotel);
    printf("[ID USER]: %s\n",a->user_id);
    printf("[HOTEL NAME]: %s\n",a->hotel_name);
    printf("[HOTEL STARS]: %d\n",a->hotel_stars);
    printf("[BEGIN DATE]: %s\n",a->begin_date);
    printf("[END DATE]: %s\n",a->end_date);
    printf("[BREAKFAST]: %d\n",a->includes_breakfast);
    printf("[RATING]: %d\n",a->rating);
    printf("----------------------------------------------------\n");

}
////////////////////////////////////////////////////////


////////////////////////////////////////////////////////
Reservation * set_reservation(char * id,short id_hotel, char * user_id, char * hotel_name, short hotel_stars, char * begin_date, char * end_date, short includes_breakfast, short rating, short ppn, short city_tax){
    Reservation * a = malloc(sizeof(Reservation));
    
    if (a == NULL)
        return NULL;

    a->id = strdup(id);
    a->id_hotel = (id_hotel);
    a->user_id = strdup(user_id);
    a->hotel_name = strdup(hotel_name);
    a->hotel_stars = hotel_stars;
    a->begin_date = strdup(begin_date);
    a->end_date = strdup(end_date);
    a->includes_breakfast = includes_breakfast;
    a->city_tax = city_tax;
    a->ppn = ppn;
    a->rating = rating;

    return a;
}
////////////////////////////////////////////////////////


////////////////////////////////////////////////////////
char * get_reservationID(Reservation * a){
    return strdup(a->id);
}
short get_reservationHOTELID(Reservation * a){
    short id_hotel = (a->id_hotel);

    return id_hotel;
}
char * get_reservationUSERID(Reservation * a){
    return strdup(a->user_id);
}
char * get_reservationHOTELNAME(Reservation * a){
    return strdup(a->hotel_name);
}
short get_reservationSTARS(Reservation * a){
    short hotel_stars = (a->hotel_stars);

    return hotel_stars;
}
char * get_reservationBEGIN(Reservation * a){
    return strdup(a->begin_date);
}
char * get_reservationEND(Reservation * a){
    return strdup(a->end_date);
}
short get_reservationBREAKFAST(Reservation * a){
    short includes_breakfast = a->includes_breakfast;

    return includes_breakfast;
}
short get_reservationPPN(Reservation * a){
    short ppn = (a->ppn);

    return ppn;
}
short get_reservationTAX(Reservation * a){
    short tax = (a->city_tax);

    return tax;
}
double get_reservationRATING(void * a){
    double rating = (double)((Reservation *) a)->rating;

    return rating;
}
////////////////////////////////////////////////////////


////////////////////////////////////////////////////////
double total_got_from_reservation(void * info){
    Reservation * a = (Reservation *) info;
    double ppn = a->ppn;
    double tax = a->city_tax;
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
    
    return strcmp(reservationB->begin_date, reservationA->begin_date);
}
////////////////////////////////////////////////////////


////////////////////////////////////////////////////////
void free_reservation(void *reservation){

    if(reservation!=NULL){

        Reservation *a = (Reservation *)reservation;


        free(a->id);
        free(a->user_id);
        
        free(a->hotel_name);
        
        free(a->begin_date);
        free(a->end_date);
        
        free(a);
    }
}
////////////////////////////////////////////////////////