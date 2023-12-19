#ifndef RESERVATIONS_H
#define RESERVATIONS_H

////////////////////////////////////////////////////////
typedef struct reservation Reservation;
////////////////////////////////////////////////////////


////////////////////////////////////////////////////////
void print_reservation(Reservation * a);
////////////////////////////////////////////////////////


////////////////////////////////////////////////////////
Reservation * set_reservation(char * id,char * id_hotel, char * user_id, char * hotel_name, char * hotel_stars, char * begin_date, char * end_date, char * includes_breakfast, char * rating, char * ppn, char * city_tax);
////////////////////////////////////////////////////////


////////////////////////////////////////////////////////
char * get_reservationID(Reservation * a);
char * get_reservationHOTELID(Reservation * a);
char * get_reservationUSERID(Reservation * a);
char * get_reservationHOTELNAME(Reservation * a);
char * get_reservationSTARS(Reservation * a);
char * get_reservationBEGIN(Reservation * a);
char * get_reservationEND(Reservation * a);
char * get_reservationBREAKFAST(Reservation * a);
char * get_reservationRATING(Reservation * a);
char * get_reservationPPN(Reservation * a);
char * get_reservationTAX(Reservation * a);
////////////////////////////////////////////////////////


////////////////////////////////////////////////////////
float total_got_from_reservation(const void * info);
int compare_reservation(const char *id, const void *info);
int compare_reservation_date(const void *a, const void *b);
////////////////////////////////////////////////////////


////////////////////////////////////////////////////////
void free_reservation(void *reservation);
////////////////////////////////////////////////////////

#endif