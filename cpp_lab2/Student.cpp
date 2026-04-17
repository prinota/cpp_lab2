#include "Student.h"
#include <cstdlib>
#include <ctime>

Student::Student(const std::string& n) : name(n), countSolved(0) {}

std::string Student::getName() const {
    return name;
}

int Student::getCountSolved() const {
    return countSolved;
}

void Student::addSolved() {
    countSolved++;
}

StudentBad::StudentBad(const std::string& n) : Student(n) {}

Roots StudentBad::solveTask(const QuadraticEquation& eq) {
    return Roots(0.0);
}

StudentGood::StudentGood(const std::string& n) : Student(n) {}

Roots StudentGood::solveTask(const QuadraticEquation& eq) {
    return eq.solve();
}

StudentAvg::StudentAvg(const std::string& n, double prob)
    : Student(n), correctProbability(prob) {
    static bool seeded = false;
    if (!seeded) {
        std::srand(std::time(nullptr));
        seeded = true;
    }
}

Roots StudentAvg::solveTask(const QuadraticEquation& eq) {
    static bool initialized = false;
    if (!initialized) {
        srand(time(0));
        initialized = true;
    }

    double chance = static_cast<double>(std::rand()) / RAND_MAX;

    if (chance < correctProbability) {
        return eq.solve();
    }
    else {
        // генерация неправильного ответа
        int errorType = std::rand() % 3;
        Roots correct = eq.solve();

        if (errorType == 0) {
            // один корень 0
            return Roots(0.0);
        }
        else if (errorType == 1 && correct.count > 0) {
            // меняем знак первого корня
            if (correct.count == 1) {
                return Roots(-correct.x1);
            }
            else {
                return Roots(-correct.x1, correct.x2);
            }
        }
        else {
            // случайные числа
            double r1 = (std::rand() % 200 - 100) / 10.0;
            double r2 = (std::rand() % 200 - 100) / 10.0;
            return Roots(r1, r2);
        }
    }
}