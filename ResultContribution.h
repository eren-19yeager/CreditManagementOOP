#ifndef RESULTCONTRIBUTION_H
#define RESULTCONTRIBUTION_H

class ResultContribution {
public:
    float creditGpa;   // ci * gpi
    float credits;

    ResultContribution(float cg=0, float c=0);

    // operator overloading
    ResultContribution operator+(const ResultContribution& other);
};

#endif