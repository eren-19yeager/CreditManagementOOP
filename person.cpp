#include "Person.h"

int Person::count = 0;
Person::Person(string i, string n, string pass) {
    id = i;
    name = n;
    password = pass;
    count++
}
Person:: ~Person() {
        count--;
}

string Person::getId() { return id; }
string Person::getName() { return name; }

bool Person::checkPassword(string p) {
    return p == password;
}



