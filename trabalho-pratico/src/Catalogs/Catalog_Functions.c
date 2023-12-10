#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../../include/Catalogs/Catalog_Functions.h"
#include "../../include/Catalogs/Catalog.h"

////////////////////////////////////////////////////////

////////////////////////////////////////////////////////


static User_Catalog create_user_catalog_f(){
    User_Catalog f;

        f.add.flight = almanac_add_flight_to_user;
        f.add.reservation = almanac_add_reservation_of_user;

        f.remove_flight = almanac_remove_flight_of_users;
        f.prefix_sort = user_prefix_sort;
        f.insert = almanac_insert_user;
            
        f.get.prefix = almanac_prefix_getter;
        f.get.user = almanac_user_getter;

    return f;
}

static Flight_Catalog create_flight_catalog_f(){
    Flight_Catalog f;

        f.add_passenger = almanac_add_passenger;
        f.airport_sort = almanac_airport_sort;
        f.complement = almanac_complement_flight;
        f.get.airport = almanac_Almanac_airport_getter;
        f.get.flight = almanac_Almanac_flight_getter;
        f.get.passengers = almanac_Almanac_passengers_getter;
        f.insert = almanac_insert_flight;
        f.remove_flight = almanac_remove_flight_catalog;

    return f;
}

Catalog_Functions create_catalog_functions(){
    Catalog_Functions f;
        
        f.destroy = destroy_almanac;
        f.new_catalog = new_almanac;
        f.user = create_user_catalog_f();
        f.flight = create_flight_catalog_f();

    return f;
}

void initialize_catalog_functions(){
    Catalog = create_catalog_functions();
}