#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// #include <glib.h>
#include "../include/DataStructures/Functions.h"
#include "../include/Catalogs/User_Catalog.h"
#include "../include/Utilities.h"
#include "../include/Parser.h"

// #include "../include/DataStructures/SLists.h"
// #include "../include/DataStructures/Airport.h"
// #include "../include/DataStructures/Users.h"
// #include "../include/DataStructures/Reservations.h"
// #include "../include/DataStructures/Flights.h"
// #include "../include/DataStructures/Counting_Calendar.h"
// #include "../include/DataStructures/Hotel.h"

#define CURRENT_DATE "2023/10/01"

#define token_user 0
#define token_reservation 1
#define token_passenger 2
#define token_flight 3
#define token_unique_passenger 4
#define token_not_unique_passenger 5

Functions Data;
Utilities Util;

void test_user(){
    // Functions Data = create_functions();
    User * a = Data.user.set("124969824","Frank Sinatra", "1932/12/11", "F", "PT", "active","1932/12/11");
    
    Data.user.add.flight(a,"4567","2023/12/10");
    Data.user.add.flight(a,"1234","2023/12/10");
    Data.user.add.flight(a,"2000","2023/12/10");
    Data.user.add.flight(a,"2323","2021/12/10");
    Data.user.add.flight(a,"9999","2020/12/10");

    
    Data.user.add.reservation(a,"AAAA","2018/12/10",10.200);
    Data.user.add.reservation(a,"VVVV","2012/12/10",100.200);
    Data.user.add.reservation(a,"BBBB","2011/12/10",299.200);
    
    Data.user.sort(a);

    SList * flight = Data.user.get.flights(a);

    char ** l1 = Data.slist.get.listA(flight);
    char ** l2 = Data.slist.get.listB(flight);
    int n1 = Data.slist.get.amount(flight);
    Data.slist.free(flight);

    SList * reservation = Data.user.get.reservations(a);

    char ** l3 = Data.slist.get.listA(reservation);
    char ** l4 = Data.slist.get.listB(reservation);
    int n2 = Data.slist.get.amount(reservation);
    Data.slist.free(reservation);

    for(int i = 0; i < n1; i++){
        printf("[%s][%s]\n",l1[i],l2[i]);
        free(l1[i]);
        free(l2[i]);
    }

    free(l1);
    free(l2);



    for(int i = 0; i < n2; i++){
        printf("[%s][%s]\n",l3[i],l4[i]);
        free(l3[i]);
        free(l4[i]);
    }

    free(l3);
    free(l4);

    Data.user.print(a);

    
    Data.user.free(a);
} 
void test_user_catalog(){
    // Functions Data = create_functions();
    User * a = Data.user.set("124969824","Frank Sinatra", "1932/12/11", "F", "PT", "active","1932/12/11");
    User * b = Data.user.set("1234","BRANK BINATRA", "1932/12/11", "F", "PT", "active","1932/12/11");
    User * c = Data.user.set("4","crank cinacra", "1932/12/11", "F", "PT", "active","1932/12/11");
    
    Data.user.add.flight(a,"4567","2023/12/10");
    Data.user.add.flight(a,"1234","2023/12/10");
    Data.user.add.flight(a,"2000","2023/12/10");
    Data.user.add.flight(a,"2323","2021/12/10");
    Data.user.add.flight(a,"9999","2020/12/10");

    
    Data.user.add.reservation(a,"AAAA","2018/12/10",10.200);
    Data.user.add.reservation(a,"VVVV","2012/12/10",100.200);
    Data.user.add.reservation(a,"BBBB","2011/12/10",299.200);
    
    Data.user.sort(a);

    Almanac_Users * u = new_user_almanac();

    insert_user(u,a);
    almanac_users_remove_flight(u,"124969824","4567");
    almanac_users_remove_flight(u,"124969824","2000");
    almanac_users_remove_flight(u,"124969824","2000");
    almanac_users_remove_flight(u,"124969824","1234");
    almanac_users_remove_flight(u,"124969824","2323");
    almanac_users_remove_flight(u,"124969824","2000");
    almanac_users_remove_flight(u,"124969824","2000");
    almanac_users_remove_flight(u,"124969824","1234");
    
    
    insert_user(u,b);
    insert_user(u,c);

    prefix_sort(u);


    almanac_users_add_flight(u,"1234","HOY","");
    almanac_users_add_flight(u,"124969824","HOY","");
    almanac_users_add_flight(u,"124969824","HOY","2020/12/10");
    User * p = almanac_users_user_getter(u,"124969824");

    Data.user.print(p);
    Data.user.free(p);



    User * r = almanac_users_user_getter(u,"1234");
    User * e = almanac_users_user_getter(u,"4");

    Data.user.print(r);
    Data.user.free(r);
    Data.user.free(e);

    destroy_user_almanac(u);
} 
void test_reservation(){
    
    Reservation * a = Data.reservation.set("12345","HTL1001","MAR123","Hotel do sol", "3.2", "2021/10/31","2021/11/14", "True","3.25", "2","3");

    Data.reservation.print(a);

    char * aa = Data.reservation.get.end(a);
    char * b = Data.reservation.get.id(a);
    char * c = Data.reservation.get.breakfast(a);
    char * d = Data.reservation.get.hotel_stars(a);

    printf("\n\n%s %s %s %s\n",aa,b,c,d);

    free(aa);
    free(b);
    free(c);
    free(d);

    Data.reservation.free(a);
} 
void test_flight(){
    
    Flight * a = Data.flight.new("000919");
    SList * p = Data.slist.set();

    Data.flight.set(a,"Moist Airlines","Dope","Florida","Anywhere","2023/11/12 12:30:00","2023/11/12 12:45:00","2023/11/12 14:30:00");


    Data.flight.add_passenger(a);
    Data.flight.add_passenger(a);
    Data.flight.add_passenger(a);
    Data.flight.add_passenger(a);
    Data.flight.add_passenger(a);
    Data.flight.add_passenger(a);

    Data.flight.print(a);

    char * b = Data.flight.get.airline(a);
    int c = Data.flight.get.delay(a);
    char * d = Data.flight.get.destination(a);
    char * e = Data.flight.get.id(a);
    char * f = Data.flight.get.origin(a);
    int g = Data.flight.get.passengers(a);
    char * h = Data.flight.get.plane_model(a);
    char * i = Data.flight.get.schedule_arrival(a);
    char * j = Data.flight.get.schedule_departure(a);

    printf("\n\n%s\n%d\n%s\n%s\n%s\n%s\n%s\n%s\n",b,c,d,e,f,h,i,j);

    free(b);
    free(d);
    free(e);
    free(f);
    free(h);
    free(i);
    free(j);
    Data.slist.free(p);

    Data.flight.free(a);
} 
void test_Hotel(){

    Reservation * b = Data.reservation.set("12345","HTL1001","MAR123","Hotel do sol", "3.2", "2021/10/31","2021/11/14", "True","3.25", "2","3");
    Reservation * c = Data.reservation.set("goig","HTL1001","MAR123","Hotel do sol", "3.2", "2021/10/31","2021/11/14", "True","3.25", "2","3");
    Reservation * d = Data.reservation.set("nnn ","HTL1001","MAR123","Hotel do sol", "3.2", "2021/10/31","2021/11/14", "True","3.25", "2","3");
    Hotel * a = Data.hotel.set("3","2.425",b);

    Data.hotel.add_reservation(a,c);
    Data.hotel.add_reservation(a,d);

    Data.hotel.print(a);



    char * id = Data.hotel.get.id(a);
    double rating = Data.hotel.get.rating(a);
    double ppn = Data.hotel.get.ppn(a);
    double revenue = Data.hotel.get.revenue(a,"2021/10/31","2021/11/14");
    
    printf("\n%s %.3f %.3f %.3f\n",id,rating,ppn,revenue);
    
    
    SList * list = Data.hotel.get.reservation(a);

    int n = Data.slist.get.amount(list);

    char ** lista = Data.slist.get.listA(list);
    char ** listb = Data.slist.get.listB(list);
    
    for(int i = 0; i<n;i++){
        printf("%s",lista[i]);
        printf("%s\n",listb[i]);

        free(lista[i]);
        free(listb[i]);
    }
    
    free(lista);
    free(listb);

    Data.slist.free(list);


    Data.reservation.free(b);
    Data.reservation.free(c);
    Data.reservation.free(d);
    Data.hotel.free(a);
    free(id);
} 
void test_airport(){

    // SList * p = Data.slist.set();
    Flight * f = Data.flight.new("000919");
    Data.flight.set(f,"Moist Airlines","Dope","Florida","Anywhere","2023/11/12 12:30:00","2023/11/12 12:45:00","2023/11/12 14:30:00");

    User * u = Data.user.set("124969824","Frank Sinatra", "1932/12/11", "F", "PT", "active","1932/12/11");

    Data.flight.add_passenger(f);
    Data.flight.add_passenger(f);
    
    Airport * a = Data.airport.set(f);
    
    Data.airport.add_flight(a,f);
    Data.airport.print(a);
    Data.user.free(u);
    Data.airport.free(a);
    Data.flight.free(f);
    // Data.slist.free(p);
} 

int main(int argc, char *argv[]) {
    initialize_functions();
    initialize_utilities();


    // test_flight();
    // test_user();
    // test_reservation();
    // test_Hotel();
    // test_airport();
    // test_user_catalog();

Almanac_Users * u = new_user_almanac();

    switch (argc){
    case 3:
        parser(argv[1],"users",u,parser_users);
        // parser(argv[1],"passengers",box,count_passengers);
        // parser(argv[1],"flights",box,parser_flight);
        break;

    case 1:
        /* code */
        break;
    
    default:
        printf("Número de argumentos inválidos\n");
        break;
    }

destroy_user_almanac(u);


    return 0;
}