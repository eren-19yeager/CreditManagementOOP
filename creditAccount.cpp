#include "CreditAccount.h"
#include <bits/stdc++.h>
using namespace std;

CreditAccount::CreditAccount(int maxC, int minC)
    : currentCredits(0), maxCredits(maxC), minCredits(minC), overloadAllowed(false) {}

int  CreditAccount::getCurrentCredits() const { return currentCredits; }
int  CreditAccount::getMaxCredits()     const { return maxCredits; }
int  CreditAccount::getMinCredits()     const { return minCredits; }

bool CreditAccount::canAddCourse(int courseCredits) const {
    if (overloadAllowed) return true;
    return (currentCredits + courseCredits) <= maxCredits;
}

bool CreditAccount::canDropCourse(int courseCredits) const {
    return (currentCredits - courseCredits) >= minCredits;
}

void CreditAccount::addCredits(int courseCredits) {
    currentCredits += courseCredits;
}

void CreditAccount::dropCredits(int courseCredits) {
    currentCredits -= courseCredits;
    if (currentCredits < 0) currentCredits = 0;
}

bool CreditAccount::checkOverloadEligibility(double cgpa) {
    if (cgpa >= 3.75) {
        overloadAllowed = true;
        return true;
    }
    return false;
}

void CreditAccount::enableOverload()      { overloadAllowed = true; }
void CreditAccount::resetSemesterCredits(){ currentCredits = 0; overloadAllowed = false; }
