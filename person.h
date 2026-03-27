#ifndef PERSON_H
#define PERSON_H
#include <bits/stdc++.h>
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

    string getId()       const;
    string getName()     const;
    string getPassword() const;
    void   setPassword(const string& p);
    bool   checkPassword(string p) const;

    virtual void display() = 0;

    static int getCount() { return count; }
};

#endif
