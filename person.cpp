#include "Person.h"

Person::Person(string i, string n, string pass) {
    id = i;
    name = n;
    password = pass;
}

string Person::getId() { return id; }
string Person::getName() { return name; }

bool Person::checkPassword(string p) {
    return p == password;
}

void Person::display() {
    // base implementation: just show generic info
    cout << "Person : " << id << " " << name << endl;
}
