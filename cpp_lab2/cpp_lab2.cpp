#include <iostream>
#include <fstream>
#include <string>
#include <clocale>
#include "Teacher.h"
#include "Student.h"

int main() {
    setlocale(LC_ALL, "Russian");

    // чтение уравнений из файла
    std::ifstream file("input.txt");
    if (!file.is_open()) {
        std::cout << "Ошибка открытия файла input.txt\n";
        return 1;
    }

    QuadraticEquation** equations = new QuadraticEquation * [100];
    int eqCount = 0;

    double a, b, c;
    while (file >> a >> b >> c && eqCount < 100) {
        equations[eqCount++] = new QuadraticEquation(a, b, c);
    }
    file.close();

    if (eqCount == 0) {
        std::cout << "Файл пуст или не содержит уравнений\n";
        return 1;
    }

    // вывод загруженных уравнений
    std::cout << "=== ЗАГРУЖЕНО УРАВНЕНИЙ: " << eqCount << " ===\n";
    for (int i = 0; i < eqCount; i++) {
        Roots r = equations[i]->solve();
        std::cout << i + 1 << ") корни: ";
        if (r.count == 0) std::cout << "нет";
        else if (r.count == 1) std::cout << r.x1;
        else std::cout << r.x1 << " и " << r.x2;
        std::cout << "\n";
    }

    // создание студентов
    const int STUDENT_COUNT = 5;
    Student** students = new Student * [STUDENT_COUNT];
    students[0] = new StudentGood("Иванов");
    students[1] = new StudentGood("Петрова");
    students[2] = new StudentAvg("Сидоров", 0.7);
    students[3] = new StudentAvg("Козлова", 0.4);
    students[4] = new StudentBad("Смирнов");

    std::cout << "\n=== СТУДЕНТЫ ===\n";
    std::cout << "Иванов, Петрова - всегда правильно\n";
    std::cout << "Сидоров - правильно с вероятностью 70%\n";
    std::cout << "Козлова - правильно с вероятностью 40%\n";
    std::cout << "Смирнов - всегда 0\n";

    Teacher teacher;

    // симуляция семестра
    std::cout << "\n=== ХОД РЕШЕНИЯ ===\n";
    for (int i = 0; i < eqCount; i++) {
        std::cout << "\n--- Уравнение " << i + 1 << " ---\n";
        Roots correct = equations[i]->solve();
        std::cout << "Правильный ответ: ";
        if (correct.count == 0) std::cout << "нет корней";
        else if (correct.count == 1) std::cout << correct.x1;
        else std::cout << correct.x1 << " и " << correct.x2;
        std::cout << "\n";

        for (int j = 0; j < STUDENT_COUNT; j++) {
            Roots answer = students[j]->solveTask(*equations[i]);

            std::cout << students[j]->getName() << ": ";
            if (answer.count == 0) std::cout << "нет корней";
            else if (answer.count == 1) std::cout << answer.x1;
            else std::cout << answer.x1 << " и " << answer.x2;

            bool isCorrect = equations[i]->checkAnswer(answer);
            std::cout << " [" << (isCorrect ? "ВЕРНО" : "НЕВЕРНО") << "]\n";

            teacher.receiveLetter(*equations[i], answer, students[j]);
        }
    }

    // зачётная неделя
    std::cout << "\n=== ПРОВЕРКА ПРЕПОДАВАТЕЛЕМ ===\n";
    teacher.checkAllWorks();

    // результаты по студентам
    std::cout << "\n=== ИТОГИ ПО СТУДЕНТАМ ===\n";
    for (int i = 0; i < STUDENT_COUNT; i++) {
        std::cout << students[i]->getName() << ": решено "
            << students[i]->getCountSolved() << " из " << eqCount << "\n";
    }

    // таблица успеваемости
    std::cout << "\n=== ТАБЛИЦА УСПЕВАЕМОСТИ ===\n";
    teacher.publishResults();

    // очистка памяти
    for (int i = 0; i < eqCount; i++) delete equations[i];
    delete[] equations;
    for (int i = 0; i < STUDENT_COUNT; i++) delete students[i];
    delete[] students;

    return 0;
}