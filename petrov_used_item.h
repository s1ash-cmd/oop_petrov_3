#ifndef PETROV_USED_ITEM_H
#define PETROV_USED_ITEM_H

#include "petrov_header.h"
#include "petrov_item.h"
#include <string>

using namespace std;

class used_item : public item {
public:
    int age = 0;
    double condition = 0.0;
    string description = "";

    template <class Archive>
    void serialize(Archive &ar, const unsigned int version) {
        ar & boost::serialization::base_object<item>(*this);
        ar & age;
        ar & condition;
        ar & description;
    }
};

#endif // PETROV_USED_ITEM_H
