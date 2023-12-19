#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// #include <malloc.h>

#include "../include/DataStructures/Users.h"
#include "../include/Catalogs/Catalog.h"
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

int main(int argc, char *argv[]) {

        Almanac * u = init_almanac();

    char * passengers = malloc(sizeof(char) * 256);
    strcpy(passengers,argv[1]);
    strcat(passengers,"/passengers.csv");

    printf("\n\n%s\n\n",passengers);



    switch (argc){
    case 3:

        parser(argv[1],"users",u,valid_user);
        parser(argv[1],"reservations",u,valid_reservation);
        almanac_add_passengers(u,passengers);
        parser(argv[1],"flights",u,valid_flight);
        free(passengers);
        parser(argv[1],"passengers",u,valid_passenger);
        // User * user = almanac_get_user(u,"AlícSá-Mendes");
        // print_user(user);

        // nulls(u," ");
        break;

    case 1:
        /* code */
        break;
    
    default:
        printf("Número de argumentos inválidos\n");
        break;
    }

    // User * a = set_user("124nlgkds","Jeremy","Jeremy","Jeremy","Jeremy","Jeremy","Jeremy");
    // User * b = set_user("124nlgkdt","Julia","Jeremy","Jeremy","Jeremy","Jeremy","Jeremy");
    // User * c1 = set_user("124nlgkdr","Robert","Jeremy","Jeremy","Jeremy","Jeremy","Jeremy");
    // User * a2 = set_user("124nlgkds","Jeremy","Jeremy","Jeremy","Jeremy","Jeremy","Jeremy");
    // User * b3 = set_user("124nlgkdt","Julia","Jeremy","Jeremy","Jeremy","Jeremy","Jeremy");
    // User * c4 = set_user("124nlgkdr","Robert","Jeremy","Jeremy","Jeremy","Jeremy","Jeremy");
    // User * a5 = set_user("124nlgkds","Jeremy","Jeremy","Jeremy","Jeremy","Jeremy","Jeremy");
    // User * b6 = set_user("124nlgkdt","Julia","Jeremy","Jeremy","Jeremy","Jeremy","Jeremy");
    // User * c7 = set_user("124nlgkdr","Robert","Jeremy","Jeremy","Jeremy","Jeremy","Jeremy");
    // User * a8 = set_user("124nlgkds","Jeremy","Jeremy","Jeremy","Jeremy","Jeremy","Jeremy");
    // User * b9 = set_user("124nlgkdt","Julia","Jeremy","Jeremy","Jeremy","Jeremy","Jeremy");
    // User * c0 = set_user("124nlgkdr","Robert","Jeremy","Jeremy","Jeremy","Jeremy","Jeremy");
    // almanac_add_user(u,"124nlgkds",(void *)a);
    // almanac_add_user(u,"124nlgkds",(void *)b);
    // almanac_add_user(u,"124nlgkds",(void *)c1);
    // almanac_add_user(u,"124nlgkds",(void *)a2);
    // almanac_add_user(u,"124nlgkds",(void *)b3);
    // almanac_add_user(u,"124nlgkds",(void *)c4);
    // almanac_add_user(u,"124nlgkds",(void *)a5);
    // almanac_add_user(u,"124nlgkds",(void *)b6);
    // almanac_add_user(u,"124nlgkds",(void *)c7);
    // almanac_add_user(u,"124nlgkds",(void *)a8);
    // almanac_add_user(u,"124nlgkds",(void *)b9);
    // almanac_add_user(u,"124nlgkds",(void *)c0);
    // almanac_add_user(u,"124nlgkds",(void *)b);
    // almanac_add_user(u,"124nlgkds",(void *)b);
    // almanac_add_user(u,"124nlgkds",(void *)b);
    // almanac_add_user(u,"124nlgkds",(void *)b);
    // almanac_add_user(u,"124nlgkds",(void *)b);
    // almanac_add_user(u,"124nlgkds",(void *)b);
    // almanac_add_user(u,"124nlgkds",(void *)b);
    // almanac_add_user(u,"124nlgkds",(void *)b);
    // almanac_add_user(u,"124nlgkds",(void *)b);
    // almanac_add_user(u,"124nlgkds",(void *)b);
    // almanac_add_user(u,"124nlgkds",(void *)b);
    // almanac_add_user(u,"124nlgkds",(void *)b);
    // almanac_add_user(u,"124nlgkds",(void *)b);
    // almanac_add_user(u,"124nlgkds",(void *)b);
    // almanac_add_user(u,"124nlgkds",(void *)b);
    // almanac_add_user(u,"124nlgkds",(void *)b);
    // almanac_add_user(u,"124nlgkds",(void *)b);
    // almanac_add_user(u,"124nlgkds",(void *)b);
    // almanac_add_user(u,"124nlgkds",(void *)b);
    // almanac_add_user(u,"124nlgkds",(void *)b);
    // almanac_add_user(u,"124nlgkds",(void *)b);
    // almanac_add_user(u,"124nlgkds",(void *)b);
    // almanac_add_user(u,"124nlgkds",(void *)b);
    // User * z = (User *)almanac_get_user(u,"124nlgkdt");
    // User * y = (User *)almanac_get_user(u,"124nlgkds");
    // User * x = (User *)almanac_get_user(u,"124nlgkdr");
    // print_user(x);
    // print_user(y);
    // print_user(z);
    
    
    
// printf("\n\n\n_______________");

// malloc_stats();
// printf("_______________");
//     free_almanac(u);
// printf("\n\n\n_______________");
// malloc_stats();
// printf("_______________\n");

    // struct mallinfo info = mallinfo();
    // printf("Heap memory statistics:\n");
    // printf("Total non-mmapped bytes (arena): %d\n", info.arena);
    // printf("Number of free chunks (ordblks): %d\n", info.ordblks);
    // printf("Number of fastbin blocks (smblks): %d\n", info.smblks);
    // printf("Maximum total allocated space (hblks): %d\n", info.hblks);
    // printf("Space in mmapped regions (hblkhd): %d\n", info.hblkhd);
    // printf("Maximum total allocated space (usmblks): %d\n", info.usmblks);


    return 0;
}