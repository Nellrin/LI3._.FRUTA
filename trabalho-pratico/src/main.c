#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/Catalogs/Catalog.h"
#include "../include/Utilities.h"
#include "../include/Parser.h"
#include "../include/Interpreter.h"


int main(int argc, char *argv[]) {

        Almanac * u = init_almanac();

    char * passengers = malloc(sizeof(char) * 256);
    snprintf(passengers, 256, "%s/passengers.csv",argv[1]);

    switch (argc){
    case 3:

        parser(argv[1],"users",u,valid_user);
        parser(argv[1],"reservations",u,valid_reservation);
        
        almanac_count_passengers(u,passengers);

        parser(argv[1],"flights",u,valid_flight);
        parser(argv[1],"passengers",u,valid_passenger);
        

        read_query_file(u,argv[2]);

        break;

    case 1:
        /* code */
        break;
    
    default:
        printf("Número de argumentos inválidos\n");
        break;
    }


    free(passengers);
    free_almanac(u);

    return 0;
}