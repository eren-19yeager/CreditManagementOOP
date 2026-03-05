#include "ResultContribution.h"

ResultContribution::ResultContribution(float cg, float c) {
    creditGpa = cg;
    credits = c;
}

ResultContribution ResultContribution::operator+(const ResultContribution& other) {
    return ResultContribution(
        creditGpa + other.creditGpa,
        credits + other.credits
    );
}