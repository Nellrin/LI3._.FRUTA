#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "../include/Catalogs/Catalog.h"
#include "../include/Tools/Validations.h"
#include "../include/IO/Parser.h"
#include "../include/IO/Interpreter.h"
#include "../include/IO/Interactive/Interactive.h"


static Almanac * setting_up(char * path){

    Almanac * u = NULL;

        u = set_up_almanac(path);
        
    if(u != NULL){

        parser(path,"users",u,valid_user);
        parser(path,"reservations",u,valid_reservation);
        
            almanac_count_passengers(u,path);

        parser(path,"flights",u,valid_flight);
        parser(path,"passengers",u,valid_passenger);
        
            almanac_sort_flight_delays(u);
    }

    return u;

}


int main(int argc, char *argv[]){
    switch (argc){
        case 1:
            interactive_mode(setting_up);
            // setting_up(argv);
            break;


        case 3:
            Almanac * u = setting_up(argv[1]);

            if(u != NULL){
                read_query_file(u,argv[2],0);

                free_almanac(u);
            }
            break;

        default:
            printf("Número de argumentos inválidos\n");
            break;
    }


    return 0;
}