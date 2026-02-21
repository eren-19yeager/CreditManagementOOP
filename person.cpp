#include "Person.h"

Person::Person(string i, string n) {
Person::Person(string i, string n, string pass) {
    id = i;
    name = n;
    password = p;
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


