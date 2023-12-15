#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// #include <glib.h>
#include "../include/Catalogs/Catalog.h"
#include "../include/Catalogs/Catalog_Functions.h"
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

Catalog_Functions Catalog;

int main(int argc, char *argv[]) {



Almanac * u = new_almanac();

    switch (argc){
    case 3:
        parser(argv[1],"users",u,parser_users);

        break;

    case 1:
        /* code */
        break;
    
    default:
        printf("Número de argumentos inválidos\n");
        break;
    }

    

    destroy_almanac(u);


    return 0;
}