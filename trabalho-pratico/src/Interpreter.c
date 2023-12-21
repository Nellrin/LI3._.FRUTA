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
                                char ** arguments = malloc(sizeof(char *) * 6);
                                int n_arguments;



                                                                for (n_arguments = 0; (token = strsep(&line, " ")) != NULL; n_arguments++) {
                                                                    arguments[n_arguments] = strdup(token);

                                                                    if(token[0] == '"'){
                                                                            token = strsep(&line, " ");
                                                                            if (token != NULL) {
                                                                                strcat(arguments[n_arguments], " ");
                                                                                strcat(arguments[n_arguments], token);
                                                                            
                                                                            while(token[strlen(token)-1 ] != '"') {
                                                                                token = strsep(&line, " ");
                                                                                if (token != NULL) {
                                                                                    strcat(arguments[n_arguments], " ");
                                                                                    strcat(arguments[n_arguments], token);
                                                                                }
                                                                            }
                                                                        }


                                                                        for(int i = 0; i < strlen(arguments[n_arguments]) - 1; i++)
                                                                        arguments[n_arguments][i] = arguments[n_arguments][i+1];
                                                                        arguments[n_arguments][strlen(arguments[n_arguments])-2] = '\0';
                                                                    }
                                                                }


                printf("\n\n");
                        for(int i = 0; i < n_arguments; i++)
                        printf("%s\n",arguments[i]);


        if (n_arguments>0) {

                switch (atoi(arguments[0])){
                    case 1:
                        
                        answear = query1(box,arguments[1],(strchr(arguments[0],'F')!=NULL));
                        if(answear!=NULL){
                            write_line(file,answear);
                            free(answear);
                        }

                        break;
                    
                    case 2:
                    
                        answear = query2(box,arguments,n_arguments,(strchr(arguments[0],'F')!=NULL));
                        if(answear!=NULL){
                            write_line(file,answear);
                            free(answear);
                        }

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
                        // answear = query9(box,arguments[1],(strchr(arguments[0],'F')!=NULL));
                        // if(answear!=NULL){
                        //     write_line(file,answear);
                        //     free(answear);
                        // }
                        break;
                    
                    case 10:
                        /* code */
                        break;

                    default:
                        break;
            }

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