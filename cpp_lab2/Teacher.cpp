#include "Teacher.h"
#include <iostream>

void LetterQueue::push(const QuadraticEquation& eq, const Roots& ans, Student* sender) {
    letters.push_back(Letter(eq, ans, sender)); 
}

Letter LetterQueue::pop() {
    Letter front = letters.front();
    letters.erase(letters.begin());
    return front;
}

bool LetterQueue::empty() const {
    return letters.empty();
}

Gradebook::Gradebook() {}

int Gradebook::findStudent(const std::string& name) const {
    for (size_t i = 0; i < records.size(); i++) {
        if (records[i].name == name) return i;
    }
    return -1;
}

void Gradebook::addSolved(const std::string& name) {
    int idx = findStudent(name);
    if (idx != -1) {
        records[idx].solved++;
    }
    else {
        GradeRecord newRecord;
        newRecord.name = name;
        newRecord.solved = 1;
        records.push_back(newRecord);
    }
}

void Gradebook::print() const {
    for (size_t i = 0; i < records.size(); i++) {
        std::cout << records[i].name << ": " << records[i].solved << "\n";
    }
}

void Teacher::receiveLetter(const QuadraticEquation& eq, const Roots& ans, Student* sender) {
    inbox.push(eq, ans, sender);
}

void Teacher::checkAllWorks() {
    while (!inbox.empty()) {
        Letter letter = inbox.pop();
        if (letter.eq.checkAnswer(letter.answer)) {
            gradebook.addSolved(letter.sender->getName());  
            letter.sender->addSolved();
        }
    }
}

void Teacher::publishResults() const {
    gradebook.print();
}