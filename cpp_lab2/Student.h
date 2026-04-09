#ifndef STUDENT_H
#define STUDENT_H

#include <string>
#include "Equation.h"

class Student {
protected:
    std::string name;
    int countSolved;
public:
    Student(const std::string& n);
    virtual ~Student() {}
    std::string getName() const;
    int getCountSolved() const;
    void addSolved();
    virtual Roots solveTask(const QuadraticEquation& eq) = 0;
};

class StudentBad : public Student {
public:
    StudentBad(const std::string& n);
    Roots solveTask(const QuadraticEquation& eq) override;
};

class StudentGood : public Student {
public:
    StudentGood(const std::string& n);
    Roots solveTask(const QuadraticEquation& eq) override;
};

class StudentAvg : public Student {
private:
    double correctProbability;
public:
    StudentAvg(const std::string& n, double prob);
    Roots solveTask(const QuadraticEquation& eq) override;
};

#endif