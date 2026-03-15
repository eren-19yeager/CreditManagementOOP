#include "person.h"
#include <bits/stdc++.h>
using namespace std;

int Person::count = 0;

Person::Person(string i, string n, string pass)
    : id(i), name(n), password(pass) {
    count++;
}

Person::~Person() {
    count--;
}

string Person::getId()       const { return id; }
string Person::getName()     const { return name; }
string Person::getPassword() const { return password; }

void Person::setPassword(const string& p) { password = p; }

bool Person::checkPassword(string p) const { return p == password; }