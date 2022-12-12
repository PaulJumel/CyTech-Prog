#ifndef STRUCT_H
#define STRUCT_H

typedef struct // le struct logement
{
    double log_nb;
    double accomadates;
    double bedrooms;
    double bathrooms;
    double beds;
    double price;
    double minimum_nights;
    double maximum_nights;
    double number_of_reviews;
    double distance; // la distance avce le logement x
} Logement;


#endif