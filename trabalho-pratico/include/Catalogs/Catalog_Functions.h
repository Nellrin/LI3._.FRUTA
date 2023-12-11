#ifndef CATALOG_FUNCTIONS_H
#define CATALOG_FUNCTIONS_H

////////////////////////////////////////////////////////
typedef struct String_list SList;
typedef struct user User;
typedef struct almanac Almanac;
typedef struct flight Flight;
typedef struct airport Airport;
typedef struct reservation Reservation;
typedef struct hotel Hotel;
typedef struct almanac_reservation Almanac_Reservation;
typedef struct almanac_flight Almanac_Flights;
typedef struct almanac_users Almanac_Users;
typedef struct almanac Almanac;
////////////////////////////////////////////////////////






////////////////////////////////////////////////////////
    typedef struct user_g{
        User * (*user)(Almanac *, char *);
        SList * (*prefix)(Almanac *);
    }User_Catalog_Getter;

    typedef struct user_a{
        void (*reservation)(Almanac *, char *, char *, char *, float);
        void (*flight)(Almanac *, char *, char *, char *);
    }User_Catalog_Add;

    typedef struct flight_c {
        void (*insert)(Almanac *,User *);
        void (*prefix_sort)(Almanac *);
        void (*remove_flight)(Almanac *, char *, char *);

        User_Catalog_Getter get;
        User_Catalog_Add add;
    }User_Catalog;


////////////////////////////////////////////////////////
    typedef struct flight_c_g{
        Airport * (*airport)(Almanac *, char *);
        Flight * (*flight)(Almanac *, char *,int);
        SList * (*passengers)(Almanac *, int);
    }Flight_Catalog_Getter;

    typedef struct flight_c_f {
        void (*add_passenger)(Almanac *,char *, char *);
        void (*insert)(Almanac *,Flight *);
        void (*complement)(Almanac *,Flight *);
        void (*airport_sort)(Almanac *);
        void (*remove_flight)(Almanac *, char *);

        Flight_Catalog_Getter get;
    }Flight_Catalog;
////////////////////////////////////////////////////////


////////////////////////////////////////////////////////
    typedef struct reservation_c_g{
        Hotel * (*hotel)(Almanac *, char *);
        Reservation * (*reservation)(Almanac *, char *);
    }Reservation_Catalog_Getter;

    typedef struct reservation_c_f {
        void (*insert)(Almanac *,Reservation *, char *, char *);
        void (*hotel_sort)(Almanac *);

        Reservation_Catalog_Getter get;
    }Reservation_Catalog;
////////////////////////////////////////////////////////


////////////////////////////////////////////////////////
    typedef struct c_f
    {
        Almanac * (*new_catalog)();
        void (*destroy)(Almanac *);

        Flight_Catalog flight;
        User_Catalog user;
        Reservation_Catalog reservation;
    }Catalog_Functions;
    
////////////////////////////////////////////////////////

////////////////////////////////////////////////////////
Catalog_Functions create_catalog_functions();
////////////////////////////////////////////////////////

extern Catalog_Functions Catalog;

////////////////////////////////////////////////////////
void initialize_catalog_functions();
////////////////////////////////////////////////////////

#endif