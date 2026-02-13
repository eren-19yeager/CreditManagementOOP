#ifndef PERSON_H
#define PERSON_H

#include <iostream>
using namespace std;

class Person {
protected:
    string id;
    string name;
    string password;
public:
    Person(string i = "", string n = "", string pass = "");

    string getId();
    string getName();
    bool checkPassword(string p);

    // allow derived classes to override for polymorphic display
    virtual void display();
};

#endif
