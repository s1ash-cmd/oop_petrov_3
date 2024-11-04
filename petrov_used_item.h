#ifndef PETROV_USED_ITEM_H
#define PETROV_USED_ITEM_H

#include "petrov_header.h"
#include "petrov_item.h"
#include <string>

using namespace std;

class used_item : public item {
protected:
    int age = 0;
    double condition = 0.0;
    string description = "";

public:
    virtual void output(ostringstream &oss) const override {
        item::output(oss);
        oss << "Возраст: " << age << "\n"
            << "Состояние: " << condition << "\n"
            << "Описание: " << description << "\n";
    }

    template <class Archive>
    void serialize(Archive &ar, const unsigned int version) {
        ar & boost::serialization::base_object<item>(*this);
        ar & age;
        ar & condition;
        ar & description;
    }
};

#endif // PETROV_USED_ITEM_H
