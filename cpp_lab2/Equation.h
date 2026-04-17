#ifndef EQUATION_H
#define EQUATION_H

const double EPS = 1e-9;

struct Roots {
    int count;
    double x1, x2;
    Roots();
    Roots(double root);
    Roots(double r1, double r2);
};

class QuadraticEquation {
private:
    double a, b, c;
public:
    QuadraticEquation(double a_, double b_, double c_);
    Roots solve() const;
    bool checkAnswer(const Roots& answer) const;
};

#endif