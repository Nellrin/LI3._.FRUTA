#ifndef ADD_DATASET_H
#define ADD_DATASET_H

typedef struct almanac Almanac;

int add_dataset(Almanac ** u, Almanac * (*f)(char *));

#endif