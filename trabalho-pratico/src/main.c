#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "../include/Catalogs/Catalog.h"
#include "../include/Tools/Validations.h"
#include "../include/IO/Parser.h"
#include "../include/IO/Interpreter.h"
#include "../include/IO/Interactive/Interactive.h"


static void setting_up(char ** path){

    Almanac * u = NULL;

        u = set_up_almanac(path[1]);

    parser(path[1],"users",u,valid_user);
    parser(path[1],"reservations",u,valid_reservation);
    
        almanac_count_passengers(u,path[1]);

    parser(path[1],"flights",u,valid_flight);
    parser(path[1],"passengers",u,valid_passenger);
    
    

        almanac_sort_flight_delays(u);


    read_query_file(u,path[2],0);


        free_almanac(u);
}


int main(int argc, char *argv[]){

    switch (argc){
        case 1:
            interactive_mode();
            setting_up(argv);
            break;


        case 3:
            setting_up(argv);
            break;

        default:
            printf("Número de argumentos inválidos\n");
            break;
    }


    return 0;
}