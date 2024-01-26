#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <sys/resource.h>

#include "../../include/Tests/compare_files.h"

int compare_files(FILE * file, short n_file,char * resultado_obtido, char * output_esperado) {
    FILE *file_obtido = fopen(resultado_obtido, "r");
    FILE *file_esperado = fopen(output_esperado, "r");
    char * s = malloc(sizeof(char) * 1024);

    if(file_obtido == NULL) {
        printf("+──────────────────────────────────────────────\n");
        printf("|\033[1mFile %d\033[m\n|\n", n_file);
        printf("|Ficheiro %s inexistente\n", output_esperado);
        printf("+──────────────────────────────────────────────\n\n");
        
            snprintf(s,1024,"+──────────────────────────────────────────────\n"
                            "|File %d\n|\n"
                            "|Ficheiro %s inexistente\n"
                            "+──────────────────────────────────────────────\n\n",n_file,output_esperado);
            fputs(s,file);   
            free(s);
        return 0;
    }

    char * esperado = malloc(sizeof(char) * 1024);
    char * obtido = malloc(sizeof(char) * 1024);



    for(int line = 1;fgets(esperado, 1024, file_esperado) != NULL && fgets(obtido, 1024, file_obtido) != NULL; line++){
        esperado[strlen(esperado)-1] = '\0';
        obtido[strlen(obtido)-1] = '\0';

        if(strcmp(esperado, obtido) != 0) {
            printf("+──────────────────────────────────────────────\n");
            printf("|\033[1mFile %d\033[m\n|\n", n_file);
            printf("|Line %d\n",line);
            printf("|Output esperado: %s\n", esperado);
            printf("|Output obtido:   %s\n", obtido);
            printf("+──────────────────────────────────────────────\n\n");

            snprintf(s,1024,"+──────────────────────────────────────────────\n"
                            "|File %d\n|\n"
                            "|Line %d\n"
                            "|Output esperado: %s\n"
                            "|Output obtido:   %s\n"
                            "+──────────────────────────────────────────────\n\n",n_file,line,esperado,obtido);
            fputs(s,file);   

            fclose(file_obtido);
            fclose(file_esperado);
            free(esperado);
            free(s);
            free(obtido);
            return 0;
        }
    }

    if(fgets(esperado, sizeof(esperado), file_esperado) != NULL || fgets(obtido, sizeof(obtido), file_obtido) != NULL) {
        printf("+──────────────────────────────────────────────\n");
        printf("|\033[1mFile %d\033[m\n|\n", n_file);
        printf("|Ficheiros diferem na quantidade de linhas ...\n");
        printf("+──────────────────────────────────────────────\n\n");
        fclose(file_esperado);
        fclose(file_obtido);

            snprintf(s,1024,"+──────────────────────────────────────────────\n"
                            "|File %d\n|\n"
                            "|Ficheiros diferem na quantidade de linhas ...\n"
                            "+──────────────────────────────────────────────\n\n",n_file);
            fputs(s,file); 

        free(s);
        free(esperado);
        free(obtido);
        return 0;
    }

    fclose(file_obtido);
    fclose(file_esperado);
    free(esperado);
    free(obtido);
    free(s);
    return 1;
}

void compare_paths(char * path, char * inputs){
    FILE * queries_file = fopen(inputs,"r");

    int * correct_queries = malloc(sizeof(int) * 10);
    int * existing_queries = malloc(sizeof(int) * 10);

    for(int i = 0; i < 10; i++){
        correct_queries[i] = 0;
        existing_queries[i] = 0;
    }

    char *line = NULL;
    size_t len = 0;

    char * output_esperado = malloc(sizeof(char) * 1024);
    char * output_obtido = malloc(sizeof(char) * 1024);

    FILE * tests = fopen("Resultados/Tests/Check_Queries","w");
    for(int number_line = 1;getline(&line, &len, queries_file) != -1; number_line++){
        snprintf(output_esperado,1024,"%s/command%d_output.txt",path,number_line);
        snprintf(output_obtido,1024,"Resultados/command%d_output.txt",number_line);

        correct_queries[atoi(line)-1] += compare_files(tests,number_line,output_obtido,output_esperado);
        existing_queries[atoi(line)-1] ++;
    }
        
    char *s = malloc(sizeof(char) * 1024);

        printf("──────────────────────────────────────────────────\n");
        
            snprintf(s,1024,"+────────────────────────────────────────────────+\n");
            fputs(s,tests);   

        for(int i = 0; i < 10; i++){
            printf("    Query %2d:...............:(%3d/%3d)[%3d%%]\n",i+1,correct_queries[i],existing_queries[i],(100*correct_queries[i]/existing_queries[i]));

            snprintf(s,1024,"|    Query %2d:...............:(%3d/%3d)[%3d%%]    |\n",i+1,correct_queries[i],existing_queries[i],(100*correct_queries[i]/existing_queries[i]));
            fputs(s,tests);
        }
            snprintf(s,1024,"+────────────────────────────────────────────────+\n\n\n");
            fputs(s,tests);
        printf("──────────────────────────────────────────────────\n");


    free(output_esperado);
    free(output_obtido);
    free(line);
    free(s);
    free(existing_queries);
    free(correct_queries);
    fclose(queries_file);
    fclose(tests);
}