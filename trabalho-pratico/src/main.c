#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/Catalogs/Catalog.h"
#include "../include/Utilities.h"
#include "../include/Parser.h"
#include "../include/Interpreter.h"


int main(int argc, char *argv[]) {
    
    Almanac * u = NULL;

    switch (argc){


    case 1:
            /* iterativo */
        break;


    case 3:

            set_up_almanac(&u,argv[1]);


            parser(argv[1],"users",u,valid_user);
            parser(argv[1],"reservations",u,valid_reservation);
            
            almanac_count_passengers(u,argv[1]);

            parser(argv[1],"flights",u,valid_flight);
            parser(argv[1],"passengers",u,valid_passenger);
            
            

                almanac_sort_flight_delays(u);


            read_query_file(u,argv[2]);

        break;

    case 4:
        /* testes */
        break;

    default:
        printf("Número de argumentos inválidos\n");
        break;
    }

        
        free_almanac(u);


    return 0;
}