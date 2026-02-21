#ifndef PERSON_H
#define PERSON_H

#include <iostream>
using namespace std;

class Person {
protected:
    string id;
    string name;
    string password;
    static int count;  

public:
    Person(string i = "", string n = "", string pass = "");
    virtual ~Person(); 

    string getId();
    string getName();
    bool checkPassword(string p);

    virtual void display() = 0;

    static int getCount() { return count; }
};

#endif
