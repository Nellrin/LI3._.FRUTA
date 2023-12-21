#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>

#include "../include/Catalogs/Catalog.h"
#include "../include/DataStructures/Users.h"
#include "../include/Utilities.h"
#include "../include/Parser.h"
#include "../include/Interpreter.h"



void printMemoryInfo() {
    struct mallinfo info = mallinfo();
    printf("\n\nTotal allocated space: %u bytes\n", info.uordblks);
    printf("Total free space: %u bytes\n", info.fordblks);
}

int main(int argc, char *argv[]) {

        Almanac * u = init_almanac();

    char * passengers = malloc(sizeof(char) * 256);
    strcpy(passengers,argv[1]);
    strcat(passengers,"/passengers.csv");


    switch (argc){
    case 3:

        parser(argv[1],"users",u,valid_user);
        parser(argv[1],"reservations",u,valid_reservation);
        
        almanac_count_passengers(u,passengers);
        free(passengers);

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



    printMemoryInfo();
    free_almanac(u);
    printMemoryInfo();

    return 0;
}