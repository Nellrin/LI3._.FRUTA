#ifndef RESERVATIONS_H
#define RESERVATIONS_H

////////////////////////////////////////////////////////
typedef struct reservation Reservation;
////////////////////////////////////////////////////////

////////////////////////////////////////////////////////
void print_reservation(Reservation * a);
////////////////////////////////////////////////////////

////////////////////////////////////////////////////////
Reservation * reservation_setter(char * id,char * id_hotel, char * user_id, char * hotel_name, char * hotel_stars, char * begin_date, char * end_date, char * includes_breakfast, char * rating, char * ppn, char * city_tax);
////////////////////////////////////////////////////////

////////////////////////////////////////////////////////
Reservation * reservation_copy(Reservation * a);
char * reservation_id_getter(Reservation * a);
char * reservation_id_hotel_getter(Reservation * a);
char * reservation_user_id_getter(Reservation * a);
char * reservation_id_name_getter(Reservation * a);
char * reservation_hotel_name_getter(Reservation * a);
char * reservation_hotel_stars_getter(Reservation * a);
char * reservation_begin_date_getter(Reservation * a);
char * reservation_end_date_getter(Reservation * a);
char * reservation_include_breakfast_getter(Reservation * a);
char * reservation_rating_getter(Reservation * a);
int reservation_nights_getter(Reservation * a);
double reservation_total_price_getter(Reservation * a);
////////////////////////////////////////////////////////

////////////////////////////////////////////////////////
void free_reservation(Reservation *a);
////////////////////////////////////////////////////////

#endif