#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <sys/resource.h>

#include "../../include/Catalogs/Catalog.h"
#include "../../include/Tools/Validations.h"
#include "../../include/IO/Parser.h"
#include "../../include/IO/Interpreter.h"
#include "../../include/Tests/compare_files.h"

static void setting_up(char ** path){

    Almanac * u = NULL;


            struct rusage antes,depois;

            struct timespec start, end;
            double t;
            int amount;

            clock_gettime(CLOCK_REALTIME, &start);
                getrusage(RUSAGE_SELF, &antes);

                                    u = set_up_almanac(path[1]);

                getrusage(RUSAGE_SELF, &depois);
            clock_gettime(CLOCK_REALTIME, &end);


            t = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;
            printf("\033[1m[Set up do Almanac]\033[m (%.3fs)\n", t);
                printf("Memória gasta na \033[1m[Criação do Almanac]\033[m: %.3f MB\n\n", (double) (depois.ru_maxrss-antes.ru_maxrss)/1000);


            clock_gettime(CLOCK_REALTIME, &start);
                getrusage(RUSAGE_SELF, &antes);

                    amount = parser(path[1],"users",u,valid_user);
                getrusage(RUSAGE_SELF, &depois);
            clock_gettime(CLOCK_REALTIME, &end);

            t = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;
            printf("\033[1m[Parse de %d Users]\033[m (%.3fs)\n",amount, t);
                printf("Memória gasta no \033[1m[Parsing dos Users]\033[m: %.3f MB\n\n", (double) (depois.ru_maxrss-antes.ru_maxrss)/1000);


            clock_gettime(CLOCK_REALTIME, &start);
                getrusage(RUSAGE_SELF, &antes);

                    amount = parser(path[1],"reservations",u,valid_reservation);
            
                getrusage(RUSAGE_SELF, &depois);
            clock_gettime(CLOCK_REALTIME, &end);
            t = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;
            printf("\033[1m[Parse de %d Reservas]\033[m (%.3fs)\n",amount, t);
                printf("Memória gasta no \033[1m[Parsing das Reservas]\033[m: %.3f MB\n\n", (double) (depois.ru_maxrss-antes.ru_maxrss)/1000);
                

            clock_gettime(CLOCK_REALTIME, &start);
                getrusage(RUSAGE_SELF, &antes);

                    almanac_count_passengers(u,path[1]);
                    amount = parser(path[1],"flights",u,valid_flight);

                getrusage(RUSAGE_SELF, &depois);
            clock_gettime(CLOCK_REALTIME, &end);

            t = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;
            printf("\033[1m[Parse de %d Voos]\033[m (%.3fs)\n",amount, t);
                printf("Memória gasta no \033[1m[Parsing dos Voos]\033[m: %.3f MB\n\n", (double) (depois.ru_maxrss-antes.ru_maxrss)/1000);


            clock_gettime(CLOCK_REALTIME, &start);
                getrusage(RUSAGE_SELF, &antes);

                    amount = parser(path[1],"passengers",u,valid_passenger);

                getrusage(RUSAGE_SELF, &depois);
            clock_gettime(CLOCK_REALTIME, &end);

            t = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;
            printf("\033[1m[Parse de %d Passageiros]\033[m (%.3fs)\n",amount, t);
                printf("Memória gasta no \033[1m[Parsing dos Passageiros]\033[m: %.3f MB\n\n", (double) (depois.ru_maxrss-antes.ru_maxrss)/1000);
                                            

            clock_gettime(CLOCK_REALTIME, &start);
                getrusage(RUSAGE_SELF, &antes);

                    almanac_sort_flight_delays(u);

                getrusage(RUSAGE_SELF, &depois);
            clock_gettime(CLOCK_REALTIME, &end);

            t = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;
            printf("\n\033[1m[Sort do Almanac]\033[m (%.3fs)\n", t);
                printf("Memória gasta no \033[1m[Sorting do Almanac]\033[m: %.3f MB\n\n+──────────────────────────────────────────────────────\n", (double)(depois.ru_maxrss-antes.ru_maxrss));


            clock_gettime(CLOCK_REALTIME, &start);
                getrusage(RUSAGE_SELF, &antes);

                    read_query_file(u,path[2],1);

                getrusage(RUSAGE_SELF, &depois);
            clock_gettime(CLOCK_REALTIME, &end);
            t = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;
            printf("+──────────────────────────────────────────────────────\n\033[1m[Execução Geral das Queries]\033[m (%.3fs)\n", t);
                printf("Memória gasta na \033[1m[Execução Geral das Queries]\033[m: %.3f MB\n\n", (double) (depois.ru_maxrss-antes.ru_maxrss)/1000);


            clock_gettime(CLOCK_REALTIME, &start);
                getrusage(RUSAGE_SELF, &antes);

                    free_almanac(u);

            clock_gettime(CLOCK_REALTIME, &end);
            t = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;
            printf("\n\033[1m[Free Almanac]\033[m (%.3fs)\n", t);
                printf("\033[1m[Memória libertada ao dar Free ao Almanac]\033[m: %.3f MB\n\n", (double) (antes.ru_maxrss)/1000);





        compare_paths(path[3],path[2]);
}


int main(int argc, char *argv[]){

    if(argc==4){

        struct timespec start, end;
        double t;

        clock_gettime(CLOCK_REALTIME, &start);
            setting_up(argv);
        clock_gettime(CLOCK_REALTIME, &end);

        t = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;
        printf("\n\n\033[1m[Total Time needed]\033[m (%.3fs)\n", t);
    }

    return 0;
}