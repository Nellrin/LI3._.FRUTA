////////////////////////////////////////////////////////
#include "../../include/DataStructures/Functions.h"
#include "../../include/DataStructures/SLists.h"
#include "../../include/DataStructures/Airport.h"
#include "../../include/DataStructures/Users.h"
#include "../../include/DataStructures/Reservations.h"
#include "../../include/DataStructures/Flights.h"
#include "../../include/DataStructures/Hotel.h"
////////////////////////////////////////////////////////

////////////////////////////////////////////////////////
static User_Functions create_user_functions(){
    User_Functions user;
    
    user.set = user_setter;

        user.get.id = user_id_getter;
        user.get.name = user_name_getter;
        user.get.birth_date = user_birth_date_getter;
        user.get.sex = user_sex_getter;
        user.get.country_code = user_country_code_getter;
        user.get.account_status = user_account_status_getter;
        user.get.account_creation = user_account_creation_getter;
        
        user.get.total_spent = user_total_spent_getter;
        
        user.get.flights = user_flight_getter;
        user.get.reservations = user_reservation_getter;
        user.get.user = user_copy;

    user.free = free_user;
    user.sort = sort_user_slists;
    user.remove_flight = remove_flight;
    user.print = print_user;

        user.add.flight = user_add_flight;
        user.add.reservation = user_add_reservation;

    return user;
}
////////////////////////////////////////////////////////

////////////////////////////////////////////////////////
static Flight_Functions create_flight_functions(){
    Flight_Functions flight;
    
    flight.set = flight_setter;

        flight.get.id = flight_id_getter;
        flight.get.airline = flight_airline_getter;
        flight.get.plane_model = flight_plane_model_getter;
        flight.get.origin = flight_origin_getter;
        flight.get.destination = flight_destination_getter;
        flight.get.schedule_departure = flight_schedule_departure_date_getter;
        flight.get.schedule_arrival = flight_schedule_arrival_date_getter;
        flight.get.passengers = flight_passengers_getter;
        flight.get.delay = flight_delay_date_getter;
        
        flight.free = free_flight;

        flight.print = print_flight;

        flight.add_passenger = add_passenger;

    flight.new = new_flight;

    return flight;
}
////////////////////////////////////////////////////////

////////////////////////////////////////////////////////
static Reservation_Functions create_reservation_functions(){
    Reservation_Functions reservation;

    
    reservation.set = reservation_setter;
    reservation.copy = reservation_copy;
    reservation.free = free_reservation;
    reservation.print = print_reservation;
    
    reservation.get.id = reservation_id_getter;
    reservation.get.begin = reservation_begin_date_getter;
    reservation.get.breakfast = reservation_include_breakfast_getter;
    reservation.get.end = reservation_end_date_getter;
    reservation.get.hotel_id = reservation_id_hotel_getter;
    reservation.get.hotel_name = reservation_hotel_name_getter;
    reservation.get.hotel_stars = reservation_hotel_stars_getter;
    reservation.get.nights = reservation_nights_getter;
    reservation.get.rating = reservation_rating_getter;
    reservation.get.total_spent = reservation_total_price_getter;
    reservation.get.user = reservation_user_id_getter;

    return reservation;
}
////////////////////////////////////////////////////////

////////////////////////////////////////////////////////
static Hotel_Functions create_hotel_functions(){
    Hotel_Functions hotel;

    
    hotel.set = hotel_setter;
    hotel.sort = sort_hotels_slists;
    hotel.free = free_hotel;
    hotel.print = print_hotel;
    hotel.add_reservation = hotel_add_reservation;
    
    hotel.get.id = hotel_id_getter;
    hotel.get.ppn = hotel_ppn_getter;
    hotel.get.rating = hotel_ratings_getter;
    hotel.get.reservation = hotel_reservation_getter;
    hotel.get.dates = hotel_dates_getter;
    hotel.get.revenue = hotel_revenue_getter;

    return hotel;
}
////////////////////////////////////////////////////////

////////////////////////////////////////////////////////
static Airport_Functions create_airport_functions(){
    Airport_Functions airport;
    
    airport.set = new_airport;
    airport.free = free_airport;
    airport.print = print_airport;
    airport.add_flight = add_flight;
    
    airport.get.dates = airport_dates_getter;
    airport.get.flights = airport_flights_getter;
    airport.get.flights_amount = airport_flights_amount_getter;
    airport.get.flights_dates = airport_dates_flights_getter;
    airport.get.id = airport_id_getter;
    airport.get.median = airport_median_getter;
    airport.get.passengers_year = airport_passenger_year_getter;
    airport.sort = sort_airport_slists;

    return airport;
}
////////////////////////////////////////////////////////

////////////////////////////////////////////////////////
static Slist_Functions create_slist_functions(){
    Slist_Functions sl;

    
    sl.set = slist_setter;
    sl.free = free_slists;
    sl.print = print_slist;
    sl.copy = slist_copy;
    sl.insert.A = insert_slistA;
    sl.insert.B = insert_slistB;
    sl.insert.F = insert_slistF;
    sl.sort = slist_sort;
    sl.remove_element = remove_element;
    
    sl.get.amount = slists_amount_getter;
    sl.get.listA = slists_listA_getter;
    sl.get.listB = slists_listB_getter;

    return sl;
}
////////////////////////////////////////////////////////

////////////////////////////////////////////////////////
Functions create_functions(){
    Functions f;
        
        f.user = create_user_functions();
        f.flight = create_flight_functions();
        f.reservation = create_reservation_functions();
        f.hotel = create_hotel_functions();
        f.airport = create_airport_functions();
        f.slist = create_slist_functions();

    return f;
}
////////////////////////////////////////////////////////

////////////////////////////////////////////////////////
void initialize_functions(){
    Data = create_functions();
}
////////////////////////////////////////////////////////