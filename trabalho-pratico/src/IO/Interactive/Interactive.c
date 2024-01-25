#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include "../../../include/Catalogs/Catalog.h"
#include "../../../include/IO/Output.h"
#include "../../../include/IO/Interpreter.h"
#include "../../../include/IO/Interactive/Interactive.h"
#include "../../../include/IO/Interactive/UI.h"
#include "../../../include/IO/Interactive/Add_Dataset.h"
#include "../../../include/IO/Interactive/Add_Input.h"
#include "../../../include/IO/Interactive/Start_Menu.h"
#include "../../../include/IO/Interactive/Check_Queries.h"
#include "../../../include/IO/Interactive/Instructions.h"
#include "../../../include/IO/Interactive/Query.h"
///////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////
void interactive_mode(Almanac * (*f)(char *)){
    
    clear_terminal();
    
    int amount_queries = 0, first_query_shown = 0, selected_query = 0;        
    Almanac * u = NULL;

    FILE * file = fopen("Resultados/input.txt","w");
    fclose(file);

        int option = 10;
        while (option!=0){
            switch (option){
                case 1:
                    option = execute_query(u,&amount_queries,&selected_query,&first_query_shown);
                    break;

                case 2:
                    option = check_query_menu(&amount_queries,&first_query_shown,&selected_query);
                    break;

                case 3:
                    option = add_input(u,&amount_queries);
                    break;
                
                case 4:
                    option = add_dataset(&u,f);
                    break;

                case 5:
                    option = instructions(&first_query_shown);
                    break;

                case 6:
                    option = show_query(selected_query,&first_query_shown);
                    break;
                
                case 10:
                    option = start_menu();
                    break;


                default:
                    continue;
                    break;
                }
    
            clear_terminal();
        }

        free_almanac(u);

}
///////////////////////////////////////////////////////////////