#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <sys/resource.h>

#include "../include/Catalogs/Catalog.h"
#include "../include/Utilities.h"
#include "../include/IO/Parser.h"
#include "../include/IO/Interpreter.h"
#include "../include/IO/Interactive/Interactive.h"


static void setting_up(char * path,char * input,short test){



    Almanac * u = NULL;

    switch (test){
    case 1:

        struct rusage antes,depois;

        struct timespec start, end;
        double t;
        int amount;

        clock_gettime(CLOCK_REALTIME, &start);
            getrusage(RUSAGE_SELF, &antes);

                                u = set_up_almanac(path);

            getrusage(RUSAGE_SELF, &depois);
        clock_gettime(CLOCK_REALTIME, &end);


        t = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;
        printf("\e[1m[Set up do Almanac]\e[m (%.3fs)\n", t);
            printf("Memória gasta na \e[1m[Criação do Almanac]\e[m: %.3f MB\n\n", (double) (depois.ru_maxrss-antes.ru_maxrss)/1000);


        clock_gettime(CLOCK_REALTIME, &start);
            getrusage(RUSAGE_SELF, &antes);

                amount = parser(path,"users",u,valid_user);
            getrusage(RUSAGE_SELF, &depois);
        clock_gettime(CLOCK_REALTIME, &end);

        t = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;
        printf("\e[1m[Parse de %d Users]\e[m (%.3fs)\n",amount, t);
            printf("Memória gasta no \e[1m[Parsing dos Users]\e[m: %.3f MB\n\n", (double) (depois.ru_maxrss-antes.ru_maxrss)/1000);


        clock_gettime(CLOCK_REALTIME, &start);
            getrusage(RUSAGE_SELF, &antes);

                amount = parser(path,"reservations",u,valid_reservation);
        
            getrusage(RUSAGE_SELF, &depois);
        clock_gettime(CLOCK_REALTIME, &end);
        t = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;
        printf("\e[1m[Parse de %d Reservas]\e[m (%.3fs)\n",amount, t);
            printf("Memória gasta no \e[1m[Parsing das Reservas]\e[m: %.3f MB\n\n", (double) (depois.ru_maxrss-antes.ru_maxrss)/1000);
            

        clock_gettime(CLOCK_REALTIME, &start);
            getrusage(RUSAGE_SELF, &antes);

                almanac_count_passengers(u,path);
                amount = parser(path,"flights",u,valid_flight);

            getrusage(RUSAGE_SELF, &depois);
        clock_gettime(CLOCK_REALTIME, &end);

        t = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;
        printf("\e[1m[Parse de %d Voos]\e[m (%.3fs)\n",amount, t);
            printf("Memória gasta no \e[1m[Parsing dos Voos]\e[m: %.3f MB\n\n", (double) (depois.ru_maxrss-antes.ru_maxrss)/1000);


        clock_gettime(CLOCK_REALTIME, &start);
            getrusage(RUSAGE_SELF, &antes);

                amount = parser(path,"passengers",u,valid_passenger);

            getrusage(RUSAGE_SELF, &depois);
        clock_gettime(CLOCK_REALTIME, &end);

        t = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;
        printf("\e[1m[Parse de %d Passageiros]\e[m (%.3fs)\n",amount, t);
            printf("Memória gasta no \e[1m[Parsing dos Passageiros]\e[m: %.3f MB\n\n", (double) (depois.ru_maxrss-antes.ru_maxrss)/1000);
                                        

        clock_gettime(CLOCK_REALTIME, &start);
            getrusage(RUSAGE_SELF, &antes);

                almanac_sort_flight_delays(u);

            getrusage(RUSAGE_SELF, &depois);
        clock_gettime(CLOCK_REALTIME, &end);

        t = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;
        printf("\n\e[1m[Sort do Almanac]\e[m (%.3fs)\n", t);
            printf("Memória gasta no \e[1m[Sorting do Almanac]\e[m: %.3f MB\n\n+──────────────────────────────────────────────────────\n", (double)(depois.ru_maxrss-antes.ru_maxrss));


        clock_gettime(CLOCK_REALTIME, &start);
            getrusage(RUSAGE_SELF, &antes);

                read_query_file(u,input,test);

            getrusage(RUSAGE_SELF, &depois);
        clock_gettime(CLOCK_REALTIME, &end);
        t = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;
        printf("+──────────────────────────────────────────────────────\n\e[1m[Execução Geral das Queries]\e[m (%.3fs)\n", t);
            // printf("Memória gasta na \e[1m[Execução Geral das Queries]\e[m: %.3f MB\n\n", (double) (depois.ru_maxrss-antes.ru_maxrss)/1000);


        clock_gettime(CLOCK_REALTIME, &start);
            getrusage(RUSAGE_SELF, &antes);

                free_almanac(u);

        clock_gettime(CLOCK_REALTIME, &end);
        t = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;
        printf("\n\e[1m[Free Almanac]\e[m (%.3fs)\n", t);
            printf("\e[1m[Memória libertada ao dar Free ao Almanac]\e[m: %.3f MB\n\n", (double) (antes.ru_maxrss)/1000);


            
        break;
    
    default:
            u = set_up_almanac(path);

        parser(path,"users",u,valid_user);
        parser(path,"reservations",u,valid_reservation);
        
            almanac_count_passengers(u,path);

        parser(path,"flights",u,valid_flight);
        parser(path,"passengers",u,valid_passenger);
        
        

            almanac_sort_flight_delays(u);


        read_query_file(u,input,0);


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