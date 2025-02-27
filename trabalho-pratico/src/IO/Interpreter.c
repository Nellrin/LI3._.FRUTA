#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/resource.h>

#include "../../include/Catalogs/Catalog.h"
#include "../../include/Queries/1Query.h"
#include "../../include/Queries/2Query.h"
#include "../../include/Queries/3Query.h"
#include "../../include/Queries/4Query.h"
#include "../../include/Queries/5Query.h"
#include "../../include/Queries/6Query.h"
#include "../../include/Queries/7Query.h"
#include "../../include/Queries/8Query.h"
#include "../../include/Queries/9Query.h"
#include "../../include/Queries/10Query.h"
#include "../../include/IO/Output.h"
#include "../../include/IO/Interpreter.h"
///////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////
static char ** break_arguments(char * line, int * n_arguments){

    char * token = NULL;
    char ** arguments = malloc(sizeof(char *) * 20);

    for(int i = 0; i < 20; i++)
    arguments[i] = NULL;

    for ((*n_arguments) = 0; (token = strsep(&line, " ")) != NULL; (*n_arguments)++) {
        char * argumento = malloc(sizeof(char) * 1000);


        strcpy(argumento,token);

        if(token[0] == '"'){
                token = strsep(&line, " ");
                if (token != NULL) {
                    strcat(argumento, " ");
                    strcat(argumento, token);
                
                while(token[strlen(token)-1] != '"') {
                    token = strsep(&line, " ");
                    if (token != NULL) {
                        strcat(argumento, " ");
                        strcat(argumento, token);
                    }
                }
            }

                for(int i = 0; i < (int)strlen(argumento) - 1; i++)
                argumento[i] = argumento[i+1];
                argumento[strlen(argumento)-2] = '\0';
            }


        arguments[(*n_arguments)] = strdup(argumento);
        if(argumento != NULL)
        free(argumento);
    }

    if(token!=NULL)
    free(token);

    return arguments;
}
///////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////
void filter_querys(Almanac * box, char * line, int number){

    char * title = malloc(sizeof(char) * 200);
    snprintf(title, 200, "Resultados/command%d_output.txt", number);
    FILE * file = create_file(title,"w");


    char * answear = NULL;

    char ** arguments = NULL;
    int n_arguments = 0;
    arguments = break_arguments(line,&n_arguments);


    if (n_arguments>0) {
        switch (atoi(arguments[0])){
            case 1:
                answear = query1(box,arguments[1],(strchr(arguments[0],'F')!=NULL));
                break;
            
            case 2:
                answear = query2(box,arguments,n_arguments,(strchr(arguments[0],'F')!=NULL));
                break;
            
            case 3:
                answear = query3(box,arguments[1],(strchr(arguments[0],'F')!=NULL));
                break;
            
            case 4:
                fputs("",file);
                fclose(file);
                file = create_file(title,"a");

                answear = query4(file,box,arguments[1],(strchr(arguments[0],'F')!=NULL));
                break;
            
            case 5:
                fputs("",file);
                fclose(file);
                file = create_file(title,"a");

                answear = query5(file,box,arguments,(strchr(arguments[0],'F')!=NULL));
                break;
            
            case 6:
                fputs("",file);
                fclose(file);
                file = create_file(title,"a");

                answear = query6(file,box,arguments,(strchr(arguments[0],'F')!=NULL));
                break;
            
            case 7:
                fputs("",file);
                fclose(file);
                file = create_file(title,"a");

                answear = query7(file,box,arguments[1],(strchr(arguments[0],'F')!=NULL));
                break;
            
            case 8:
                answear = query8(box,arguments,(strchr(arguments[0],'F')!=NULL));
                break;
            
            case 9:
                fputs("",file);
                fclose(file);
                file = create_file(title,"a");
            
                query9(file,box,arguments[1],(strchr(arguments[0],'F')!=NULL));
                break;
            
            case 10:
                fputs("",file);
                fclose(file);
                file = create_file(title,"a");

                query10(file,box,arguments,n_arguments,(strchr(arguments[0],'F')!=NULL));
                break;

            default:
                break;
        }

    }



    if(answear!=NULL){
        write_line(file,answear);
        free(answear);
    }



    for(int i = 0;i<n_arguments;i++)
    if(arguments[i]!=NULL)
    free(arguments[i]);

    free(arguments);

        free(title);
        fclose(file);
}
///////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////
void read_query_file(Almanac * box, char * path,short test){

    // struct rusage antes,depois;
    struct timespec start, end;
    double t;


    char *line = NULL;
    size_t len = 0;
    char *s = NULL;
    double * times = NULL;
    int * amount = NULL; 

        FILE * file = create_file(path,"r");
        FILE * tests = fopen("Resultados/Tests/Performance_Queries","w");


    switch (test){
    case 1: 
        amount = malloc(sizeof(int) * 10);
        times = malloc(sizeof(double) * 10);
        
        for(int i = 0; i < 10; i++){
            times[i] = 0;
            amount[i] = 0;
        }

        s = malloc(sizeof(char) * 1024);
                snprintf(s,1024,"[Tempo de Execução das Queries]\n\n+─────────+──────────+──────────────\n");
                fputs(s,tests);

            for(int i = 1;getline(&line, &len, file) != -1;i++) {
                line[strlen(line)-1] = '\0';
                
                clock_gettime(CLOCK_REALTIME, &start);
                    // getrusage(RUSAGE_SELF, &antes);

                        filter_querys(box,line,i);

                    // getrusage(RUSAGE_SELF, &depois);
                clock_gettime(CLOCK_REALTIME, &end);

                t = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;
                times[atoi(line)-1] += t;
                amount[atoi(line)-1]++;
                printf("\033[1m|   [Line %4d: Query %2d]\033[m (%.6fs)\n",(int)i, atoi(line), t);

                snprintf(s,1024,"|Line %4d| Query %2d | %.6fs \n",(int)i, atoi(line), t);
                fputs(s,tests);
            }
            snprintf(s,1024,"+─────────+──────────+──────────────\n\n\n");
            fputs(s,tests);
                                              
                snprintf(s,1024,"+───────+───────────────────────\n| Query | Mean Time\n+───────+─────────────\n");
                fputs(s,tests);

                for(int i = 0; i < 10; i++){
                    snprintf(s,1024,"|  %2d   | %.6f \n",1+i, times[i]/amount[i]);
                    fputs(s,tests);
                }



            snprintf(s,1024,"+───────+─────────────\n");
            fputs(s,tests);

            if(line!=NULL)
            free(line);
            free(s);
            free(times);
            free(amount);
            fclose(file);
            fclose(tests);

        break;
    
    default:
            
            for(int i = 1;getline(&line, &len, file) != -1;i++) {
                line[strlen(line)-1] = '\0';
                
                filter_querys(box,line,i);
            }

            if(line!=NULL)
            free(line);
            fclose(file);
            fclose(tests);

        break;
    }


}
///////////////////////////////////////////////////////////////