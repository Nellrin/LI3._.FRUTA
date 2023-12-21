#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/Catalogs/Catalog.h"
#include "../include/Queries/1Query.h"
#include "../include/Queries/2Query.h"
#include "../include/Queries/9Query.h"
#include "../include/Output.h"
#include "../include/Interpreter.h"
///////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////
static void filter_querys(Almanac * box, char * line, int number){

                                char * title = malloc(sizeof(char) * 200);
                                snprintf(title, 200, "Resultados/command%d_output.txt", number);
                                FILE * file = create_file(title,"w");


                                char * answear = NULL;
                                char * token = NULL;
                                char ** arguments = malloc(sizeof(char *) * 20);

                                for(int i = 0; i < 20; i++)
                                arguments[i] = NULL;
                                
                                int n_arguments;



                                                                for (n_arguments = 0; (token = strsep(&line, " ")) != NULL; n_arguments++) {
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

                                                                            for(int i = 0; i < strlen(argumento) - 1; i++)
                                                                            argumento[i] = argumento[i+1];
                                                                            argumento[strlen(argumento)-2] = '\0';
                                                                        }


                                                                    arguments[n_arguments] = strdup(argumento);
                                                                    free(argumento);
                                                                }


        if (n_arguments>0) {


                switch (atoi(arguments[0])){
                    case 1:
                        answear = query1(box,arguments[1],(strchr(arguments[0],'F')!=NULL));
                        break;
                    
                    case 2:
                        answear = query2(box,arguments,n_arguments,(strchr(arguments[0],'F')!=NULL));
                        break;
                    
                    case 3:
                        /* code */
                        break;
                    
                    case 4:
                        /* code */
                        break;
                    
                    case 5:
                        /* code */
                        break;
                    
                    case 6:
                        /* code */
                        break;
                    
                    case 7:
                        /* code */
                        break;
                    
                    case 8:
                        /* code */
                        break;
                    
                    case 9:
                        answear = query9(box,arguments[1],(strchr(arguments[0],'F')!=NULL));
                        break;
                    
                    case 10:
                        /* code */
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

        free(token);
        free(title);
        fclose(file);
}
///////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////
void read_query_file(Almanac * box, char * path){

    FILE * file = create_file(path,"r");

    char *line = NULL;
    size_t len = 0;
    
    
    for(int i = 1;getline(&line, &len, file) != -1;i++) {
        line[strlen(line)-1] = '\0';


        // printf("%s\n",line);

        filter_querys(box,line,i);
    }

    free(line);
    fclose(file);
}
///////////////////////////////////////////////////////////////