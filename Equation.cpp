#include "Equation.h"
#include <cmath>

Roots::Roots() : count(0), x1(0), x2(0) {}

Roots::Roots(double root) : count(1), x1(root), x2(0) {}

Roots::Roots(double r1, double r2) : count(2) {
    if (r1 < r2) {
        x1 = r1;
        x2 = r2;
    }
    else {
        x1 = r2;
        x2 = r1;
    }
}

QuadraticEquation::QuadraticEquation(double a_, double b_, double c_)
    : a(a_), b(b_), c(c_) {
}

Roots QuadraticEquation::solve() const {
    const double EPS = 1e-9;

    if (std::fabs(a) < EPS) {
        if (std::fabs(b) < EPS) {
            return Roots();
        }
        else {
            return Roots(-c / b);
        }
    }

    double discriminant = b * b - 4 * a * c;

    if (discriminant < -EPS) {
        return Roots();
    }
    else if (std::fabs(discriminant) < EPS) {
        double x = -b / (2 * a);
        return Roots(x);
    }
    else {
        double sqrtD = std::sqrt(discriminant);
        double x1 = (-b - sqrtD) / (2 * a);
        double x2 = (-b + sqrtD) / (2 * a);
        return Roots(x1, x2);
    }
}

bool QuadraticEquation::checkAnswer(const Roots& answer) const {
    const double EPS = 1e-6;

    Roots correct = solve();

    if (correct.count != answer.count) {
        return false;
    }

    if (correct.count == 0) {
        return true;
    }
    else if (correct.count == 1) {
        return std::fabs(correct.x1 - answer.x1) < EPS;
    }
    else {
        bool match1 = std::fabs(correct.x1 - answer.x1) < EPS &&
            std::fabs(correct.x2 - answer.x2) < EPS;
        bool match2 = std::fabs(correct.x1 - answer.x2) < EPS &&
            std::fabs(correct.x2 - answer.x1) < EPS;
        return match1 || match2;
    }
}