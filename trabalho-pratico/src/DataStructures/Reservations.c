#include "../../include/DataStructures/Reservations.h"
#include "../../include/Utilities.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
////////////////////////////////////////////////////////


////////////////////////////////////////////////////////
struct reservation {
    int id;
    char first_id_digit;

    short id_hotel;
    char *user_id;
    char *hotel_name;
    
    char *begin_date;
    char *end_date;
    
    char hotel_stars;
    short city_tax;
    short ppn;
    char rating;
    char includes_breakfast;
};
////////////////////////////////////////////////////////


////////////////////////////////////////////////////////
void print_reservation(Reservation * a){
    printf("\n----------------------------------------------------\n");
    printf("[ID BOOKING]: Book%d%d\n",a->first_id_digit,a->id);
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

    a->first_id_digit = (id[4]);
    a->id = atoi(id+5);
    a->id_hotel = (id_hotel);
    a->user_id = strdup(user_id);
    a->hotel_name = strdup(hotel_name);
    a->hotel_stars = (char) hotel_stars;
    a->begin_date = strdup(begin_date);
    a->end_date = strdup(end_date);
    a->includes_breakfast = (char)includes_breakfast;
    a->city_tax = city_tax;
    a->ppn = ppn;
    a->rating = (char) rating;

    return a;
}
////////////////////////////////////////////////////////


////////////////////////////////////////////////////////
char * get_reservationID(Reservation * a){
    char * id = malloc(sizeof(char)*20);
    snprintf(id,20,"Book%c%09d",a->first_id_digit,a->id);
    return id;
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
    short hotel_stars = (short)(a->hotel_stars);

    return hotel_stars;
}
char * get_reservationBEGIN(Reservation * a){
    return strdup(a->begin_date);
}
char * get_reservationEND(Reservation * a){
    return strdup(a->end_date);
}
short get_reservationBREAKFAST(Reservation * a){
    short includes_breakfast = (short)a->includes_breakfast;

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
    char * res_id = get_reservationID((Reservation *)info);
    int res = (strcmp(id, res_id) == 0);
    free(res_id);
    return res;
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


        free(a->user_id);
        
        free(a->hotel_name);
        
        free(a->begin_date);
        free(a->end_date);
        
        free(a);
    }
}
////////////////////////////////////////////////////////