#ifndef PETROV_ITEM_H
#define PETROV_ITEM_H

#include "petrov_header.h"
#include <iostream>
#include <string>

using namespace std;

class item {
public:
    string name = "";
    double weight = 0.0;
    double width = 0.0;
    double height = 0.0;
    int price = 0;
    bool stock = 0;

    virtual ~item() = default;

    template <class Archive>
    void serialize(Archive &ar, const unsigned int version) {
        ar & name;
        ar & weight;
        ar & width;
        ar & height;
        ar & price;
        ar & stock;
    }
};

#endif // PETROV_ITEM_H
