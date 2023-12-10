#ifndef UTILITIES_H
#define UTILITIES_H

////////////////////////////////////////////////////////
typedef struct v{
    int (*date)(const char*,int);
    int (*email)(char*);
    int (*country_code)(char*);
    int (*account_status)(char*);
    int (*total_seats)(char*,int);
    int (*airport)(char*);
    int (*number)(int,char*,int);
    int (*breakfast)(char*);
    int (*rating)(char*);
    int (*string)(char*);
}Validations;

typedef struct u{
    Validations validations;
    int (*time_diff)(char *, char *, char *);
}Utilities;
////////////////////////////////////////////////////////

////////////////////////////////////////////////////////
Utilities create_utilities();
////////////////////////////////////////////////////////

extern Utilities Util;

////////////////////////////////////////////////////////
void initialize_utilities();
////////////////////////////////////////////////////////


#endif