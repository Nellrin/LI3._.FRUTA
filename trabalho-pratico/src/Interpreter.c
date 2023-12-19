#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/Catalogs/Catalog.h"
#include "../include/Queries/1Query.h"
#include "../include/Output.h"
///////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////
static void filter_querys(Almanac * box, char * line, int number){

    char * title = malloc(sizeof(char) * 200);
    snprintf(title, 200, "Resultados/command%d_output.txt", number);
    FILE * file = create_file(title,"w");

    char * answear;
    char * token = strsep(&line, " ");

        if (token != NULL) {

            char * type = strdup(token);
            token = strsep(&line, " ");

                switch (atoi(type)){
                    case 1:
                        
                        answear = query1(box,token,(strchr(type,'F')!=NULL));
                        
                        if(answear!=NULL){
                            write_line(file,answear);
                            free(answear);
                        }

                        break;
                    
                    case 2:
                        /* code */
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
                        /* code */
                        break;
                    
                    case 10:
                        /* code */
                        break;

                    default:
                        break;
            }

        
        free(type);
        free(title);
        fclose(file);
        }
}
///////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////
void read_query_file(Almanac * box, char * path){

    FILE * file = create_file(path,"r");

    char *line = NULL;
    size_t len = 0;
    
    
    for(int i = 1;getline(&line, &len, file) != -1;i++) {
        line[strlen(line)-1] = '\0';


        printf("%s\n",line);

        filter_querys(box,line,i);
    }

    free(line);
    fclose(file);
}
///////////////////////////////////////////////////////////////