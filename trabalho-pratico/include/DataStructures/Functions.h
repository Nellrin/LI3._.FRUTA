#ifndef FUNCTIONS_H
#define FUNCTIONS_H

////////////////////////////////////////////////////////
typedef struct user User;
typedef struct flight Flight;
typedef struct reservation Reservation;


typedef struct String_list SList;


typedef struct contador Count;
typedef struct calendario_contador CCalendar;

typedef struct hotel Hotel;

typedef struct airport Airport;
////////////////////////////////////////////////////////

////////////////////////////////////////////////////////
    typedef struct user_f_g{
        char * (*id)(User *);
        char * (*name)(User *);
        char * (*birth_date)(User *);
        char * (*sex)(User *);
        char * (*country_code)(User *);
        char * (*account_status)(User *);
        char * (*account_creation)(User *);
        
        double (*total_spent)(User *);
        
        SList * (*flights)(User *);
        SList * (*reservations)(User *);
        User * (*user)(User *);
    }User_Functions_Getters;


    typedef struct user_f_a{
        void (*flight)(User *, char *, char *);
        void (*reservation)(User *, char *, char *, float);
    }User_Functions_Adder;

    typedef struct user_f {
        User * (*set)(char * ,char * , char * , char * , char * , char * , char * );
        User_Functions_Getters get;
        User_Functions_Adder add;
        void (*remove_flight) (User *, char * id);
        void (*sort) (User *);
        void (*free) (User *);
        void (*print) (User *);
    }User_Functions;
////////////////////////////////////////////////////////

////////////////////////////////////////////////////////
    typedef struct flight_f_g{
        char * (*id)(Flight *);
        char * (*airline)(Flight *);
        char * (*plane_model)(Flight *);
        char * (*origin)(Flight *);
        char * (*destination)(Flight *);
        char * (*schedule_departure)(Flight *);
        char * (*schedule_arrival)(Flight *);
        
        int (*passengers)(Flight *);
        int (*delay)(Flight *);
    }Flight_Functions_Getters;

    typedef struct flight_f {
        Flight * (*new)(char *);
        void (*set)(Flight *,char *,char *, char *, char *, char *, char *,char *);
        Flight_Functions_Getters get;
        void (*add_passenger)(Flight *);
        void (*free) (Flight *);
        void (*print) (Flight *);
    }Flight_Functions;
////////////////////////////////////////////////////////

////////////////////////////////////////////////////////
    typedef struct reservation_f_g{
        char * (*id)(Reservation *);
        char * (*hotel_id)(Reservation *);
        char * (*user)(Reservation *);
        char * (*hotel_name)(Reservation *);
        char * (*hotel_stars)(Reservation *);
        char * (*begin)(Reservation *);
        char * (*end)(Reservation *);
        char * (*breakfast)(Reservation *);
        char * (*rating)(Reservation *);
        int (*nights)(Reservation *);
        double (*total_spent)(Reservation *);
        
    }Reservation_Functions_Getters;

    typedef struct reservation_f {
        Reservation * (*set)(char *,char *, char *, char *, char *, char *, char *, char *, char *, char *, char *);
        Reservation * (*copy)(Reservation *);
        Reservation_Functions_Getters get;
        void (*free) (Reservation *);
        void (*print) (Reservation *);
    }Reservation_Functions;
////////////////////////////////////////////////////////

////////////////////////////////////////////////////////
    typedef struct hotel_f_g{
        char * (*id)(Hotel *);
        double (*rating)(Hotel *);
        double (*ppn)(Hotel *);
        SList * (*reservation)(Hotel *);
        SList * (*dates)(Hotel *);
        double (*revenue)(Hotel *,char *,char *);        
    }Hotel_Functions_Getters;

    typedef struct hotel_f {
        Hotel * (*set)(char *,char *,Reservation *);
        Hotel_Functions_Getters get;
        void (*add_reservation) (Hotel *,Reservation *);
        void (*free) (Hotel *);
        void (*sort) (Hotel *);
        void (*print) (Hotel *);
    }Hotel_Functions;
////////////////////////////////////////////////////////

////////////////////////////////////////////////////////
    typedef struct airport_f_g{
        char * (*id)(Airport *);
        int (*median)(Airport *);
        int (*passengers_year)(Airport *,int);
        SList * (*flights_dates)(Airport *);
        int (*flights_amount)(Airport *);        
        char ** (*flights)(Airport *);        
        char ** (*dates)(Airport *);        
    }Airport_Functions_Getters;

    typedef struct airport_f {
        Airport * (*set)(Flight *);
        Airport_Functions_Getters get;
        void (*add_flight) (Airport *,Flight *);
        void (*free) (Airport *);
        void (*print) (Airport *);
        void (*sort) (Airport *);
    }Airport_Functions;
////////////////////////////////////////////////////////

////////////////////////////////////////////////////////
    typedef struct slist_f_g{
        int (*amount)(SList *);        
        char ** (*listA)(SList *);        
        char ** (*listB)(SList *);        
    }SList_Functions_Getters;

    typedef struct slist_f_i{
        void (*A)(SList *,char *, char *);        
        void (*B)(SList *, char *);        
        void (*F)(SList *, char *, char *);        
    }SList_Functions_Insert;

    typedef struct slist_f {
        SList * (*set)();
        void (*copy)(SList *,SList *);
        SList_Functions_Getters get;
        SList_Functions_Insert insert;
        void (*free) (SList *);
        void (*print) (SList *);
        void (*sort) (SList *);
        void (*remove_element) (SList *,char *);
    }Slist_Functions;
////////////////////////////////////////////////////////

////////////////////////////////////////////////////////
typedef struct f{
    User_Functions user;
    Reservation_Functions reservation;
    Flight_Functions flight;
    Slist_Functions slist;
    Hotel_Functions hotel;
    Airport_Functions airport;
}Functions;
////////////////////////////////////////////////////////

////////////////////////////////////////////////////////
Functions create_functions();
////////////////////////////////////////////////////////

extern Functions Data;

////////////////////////////////////////////////////////
void initialize_functions();
////////////////////////////////////////////////////////

#endif