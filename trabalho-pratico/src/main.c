#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/Catalogs/Catalog.h"
#include "../include/Utilities.h"
#include "../include/IO/Parser.h"
#include "../include/IO/Interpreter.h"
#include "../include/IO/Interactive/Interactive.h"


static void setting_up(char * path,char * input,short test){

    Almanac * u = NULL;

    switch (test){
    case 1:
            u = set_up_almanac(path);

        parser(path,"users",u,valid_user);
        parser(path,"reservations",u,valid_reservation);
        
            almanac_count_passengers(u,path);

        parser(path,"flights",u,valid_flight);
        parser(path,"passengers",u,valid_passenger);
        
        

            almanac_sort_flight_delays(u);


        read_query_file(u,input);


            free_almanac(u);
            
        break;
    
    default:
            u = set_up_almanac(path);

        parser(path,"users",u,valid_user);
        parser(path,"reservations",u,valid_reservation);
        
            almanac_count_passengers(u,path);

        parser(path,"flights",u,valid_flight);
        parser(path,"passengers",u,valid_passenger);
        
        

            almanac_sort_flight_delays(u);


        read_query_file(u,input);


            free_almanac(u);

        break;
    }
}


int main(int argc, char *argv[]){


    switch (argc){
        case 1:
                interactive_mode();
            break;


        case 3:
            setting_up(argv[1],argv[2],0);
            break;

        case 4:
            setting_up(argv[1],argv[2],1);
            break;

        default:
            printf("Número de argumentos inválidos\n");
            break;
    }

    return 0;
}