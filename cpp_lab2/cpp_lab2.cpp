#include <iostream>
#include <fstream>
#include <string>
#include <clocale>
#include "Teacher.h"
#include "Student.h"
#include <vector>

int main() {
    setlocale(LC_ALL, "Russian");

    // чтение уравнений из файла
    std::ifstream file("input.txt");
    if (!file.is_open()) {
        std::cout << "Ошибка открытия файла input.txt\n";
        return 1;
    }

    std::vector<QuadraticEquation> equations;

    double a, b, c;
    while (file >> a >> b >> c) {
        equations.push_back(QuadraticEquation(a, b, c));
    }
    file.close();

    if (equations.empty()) {
        std::cout << "Файл пуст или не содержит уравнений\n";
        return 1;
    }

    // вывод загруженных уравнений
    std::cout << "=== ЗАГРУЖЕНО УРАВНЕНИЙ: " << equations.size() << " ===\n";
    for (int i = 0; i < equations.size(); i++) {
        Roots r = equations[i].solve();
        std::cout << i + 1 << ") корни: ";
        if (r.count == 0) std::cout << "нет";
        else if (r.count == 1) std::cout << r.x1;
        else std::cout << r.x1 << " и " << r.x2;
        std::cout << "\n";
    }

    // создание студентов
    std::vector<std::unique_ptr<Student>> students;
    students.push_back(std::make_unique<StudentGood>("Иванов"));
    students.push_back(std::make_unique<StudentGood>("Петрова"));
    students.push_back(std::make_unique<StudentAvg>("Сидоров", 0.7));
    students.push_back(std::make_unique<StudentAvg>("Козлова", 0.4));
    students.push_back(std::make_unique<StudentBad>("Смирнов"));

    std::cout << "\n=== СТУДЕНТЫ ===\n";
    std::cout << "Иванов, Петрова - всегда правильно\n";
    std::cout << "Сидоров - правильно с вероятностью 70%\n";
    std::cout << "Козлова - правильно с вероятностью 40%\n";
    std::cout << "Смирнов - всегда 0\n";

    Teacher teacher;

    // симуляция семестра
    std::cout << "\n=== ХОД РЕШЕНИЯ ===\n";
    for (int i = 0; i < equations.size(); i++) {
        std::cout << "\n--- Уравнение " << i + 1 << " ---\n";
        Roots correct = equations[i].solve();
        std::cout << "Правильный ответ: ";
        if (correct.count == 0) std::cout << "нет корней";
        else if (correct.count == 1) std::cout << correct.x1;
        else std::cout << correct.x1 << " и " << correct.x2;
        std::cout << "\n";

        for (int j = 0; j < students.size(); j++) {
            Roots answer = students[j]->solveTask(equations[i]);

            std::cout << students[j]->getName() << ": ";
            if (answer.count == 0) std::cout << "нет корней";
            else if (answer.count == 1) std::cout << answer.x1;
            else std::cout << answer.x1 << " и " << answer.x2;

            bool isCorrect = equations[i].checkAnswer(answer);
            std::cout << " [" << (isCorrect ? "ВЕРНО" : "НЕВЕРНО") << "]\n";

            teacher.receiveLetter(equations[i], answer, students[j].get());
        }
    }

    // зачётная неделя
    std::cout << "\n=== ПРОВЕРКА ПРЕПОДАВАТЕЛЕМ ===\n";
    teacher.checkAllWorks();

    // результаты по студентам
    std::cout << "\n=== ИТОГИ ПО СТУДЕНТАМ ===\n";
    for (int i = 0; i < students.size(); i++) {
        std::cout << students[i]->getName() << ": решено "
            << students[i]->getCountSolved() << " из " << equations.size() << "\n";
    }

    // таблица успеваемости
    std::cout << "\n=== ТАБЛИЦА УСПЕВАЕМОСТИ ===\n";
    teacher.publishResults();

    return 0;
}