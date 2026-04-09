#ifndef TEACHER_H
#define TEACHER_H

#include "Equation.h"
#include "Student.h"

// Письмо и очередь писем
struct Letter {
    QuadraticEquation eq;
    Roots answer;
    Student* sender;
    Letter* next;
    Letter(const QuadraticEquation& e, const Roots& a, Student* s);
};

class LetterQueue {
private:
    Letter* head;
    Letter* tail;
public:
    LetterQueue();
    ~LetterQueue();
    void push(const QuadraticEquation& eq, const Roots& ans, Student* sender);
    Letter* pop();
    bool empty() const;
};

// Журнал успеваемости
struct GradeRecord {
    std::string name;
    int solved;
};

class Gradebook {
private:
    static const int MAX_STUDENTS = 100;
    GradeRecord records[MAX_STUDENTS];
    int size;
    int findStudent(const std::string& name) const;
public:
    Gradebook();
    void addSolved(const std::string& name);
    void print() const;
};

// Преподаватель
class Teacher {
private:
    LetterQueue inbox;
    Gradebook gradebook;
public:
    void receiveLetter(const QuadraticEquation& eq, const Roots& ans, Student* sender);
    void checkAllWorks();
    void publishResults() const;
};

#endif