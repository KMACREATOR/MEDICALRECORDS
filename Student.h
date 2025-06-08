#ifndef STUDENT_H
#define STUDENT_H

#include "json.hpp" // Убедись, что путь к json.hpp правильный

#include <string>

using json = nlohmann::json;

class Student
{
protected:
    std::string surname;
    std::string initials;
    int birth_year;
    std::string phone;
    int enrollment_year;
    std::string institute;
    std::string department;

public:
    // Конструктор
    Student(const std::string& surname, const std::string& initials, int birth_year, const std::string& phone,
            int enrollment_year, const std::string& institute, const std::string& department);

    // Виртуальный деструктор (для наследования)
    virtual ~Student() = default;

    // Вывод информации о студенте
    virtual void print() const;

    // Сериализация в JSON
    virtual void to_json(json& j) const;

    // Дружественная функция для десериализации
    friend void from_json(const json& j, Student& s);
};

#endif // STUDENT_H