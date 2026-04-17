#include "Teacher.h"
#include <iostream>

Letter::Letter(const QuadraticEquation& e, const Roots& a, Student* s)
    : eq(e), answer(a), sender(s), next(nullptr) {
}

LetterQueue::LetterQueue() : head(nullptr), tail(nullptr) {}

LetterQueue::~LetterQueue() {
    while (!empty()) {
        Letter* temp = pop();
        delete temp;
    }
}

void LetterQueue::push(const QuadraticEquation& eq, const Roots& ans, Student* sender) {
    Letter* newLetter = new Letter(eq, ans, sender);
    if (tail) {
        tail->next = newLetter;
        tail = newLetter;
    }
    else {
        head = tail = newLetter;
    }
}

Letter* LetterQueue::pop() {
    if (!head) return nullptr;
    Letter* temp = head;
    head = head->next;
    if (!head) tail = nullptr;
    return temp;
}

bool LetterQueue::empty() const {
    return head == nullptr;
}

Gradebook::Gradebook() : size(0) {}

int Gradebook::findStudent(const std::string& name) const {
    for (int i = 0; i < size; i++) {
        if (records[i].name == name) return i;
    }
    return -1;
}

void Gradebook::addSolved(const std::string& name) {
    int idx = findStudent(name);
    if (idx != -1) {
        records[idx].solved++;
    }
    else if (size < MAX_STUDENTS) {
        records[size].name = name;
        records[size].solved = 1;
        size++;
    }
}

void Gradebook::print() const {
    for (int i = 0; i < size; i++) {
        std::cout << records[i].name << ": " << records[i].solved << "\n";
    }
}

void Teacher::receiveLetter(const QuadraticEquation& eq, const Roots& ans, Student* sender) {
    inbox.push(eq, ans, sender);
}

void Teacher::checkAllWorks() {
    while (!inbox.empty()) {
        Letter* letter = inbox.pop();
        if (letter->eq.checkAnswer(letter->answer)) {
            letter->sender->addSolved();
            gradebook.addSolved(letter->sender->getName());
        }
        delete letter;
    }
}

void Teacher::publishResults() const {
    gradebook.print();
}