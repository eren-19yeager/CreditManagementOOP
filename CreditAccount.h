
#ifndef CREDITACCOUNT_H
#define CREDITACCOUNT_H

class CreditAccount {
private:
    int currentCredits;
    int maxCredits;
    int minCredits;
    bool overloadAllowed;

public:
    CreditAccount(int maxCredits = 18, int minCredits = 9);

    int getCurrentCredits() const;
    int getMaxCredits() const;
    int getMinCredits() const;

    bool canAddCourse(int courseCredits) const;
    bool canDropCourse(int courseCredits) const;

    void addCredits(int courseCredits);
    void dropCredits(int courseCredits);

    bool checkOverloadEligibility(double cgpa);
    void enableOverload();
    void resetSemesterCredits();
};

#endif
