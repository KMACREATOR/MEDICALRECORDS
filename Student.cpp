#include "Student.h"

#include <iostream>

// Используем псевдоним json, чтобы упростить код
using json = nlohmann::json;

Student::Student(const std::string& surname, const std::string& initials, int birth_year, const std::string& phone,
                 int enrollment_year, const std::string& institute, const std::string& department)
    : surname(surname)
    , initials(initials)
    , birth_year(birth_year)
    , phone(phone)
    , enrollment_year(enrollment_year)
    , institute(institute)
    , department(department)
{
}

void Student::print() const
{
    std::cout << "Surname: " << surname << "\n"
              << "Initials: " << initials << "\n"
              << "Birthdate: " << birth_year << "\n"
              << "Telephone number: " << phone << "\n"
              << "Enrollment year: " << enrollment_year << "\n"
              << "Institute: " << institute << "\n"
              << "Department: " << department << "\n";
}

void Student::to_json(json& j) const
{
    j["surname"] = surname;
    j["initials"] = initials;
    j["birth_year"] = birth_year;
    j["phone"] = phone;
    j["enrollment_year"] = enrollment_year;
    j["institute"] = institute;
    j["department"] = department;
}

void from_json(const json& j, Student& s)
{
    j.at("surname").get_to(s.surname);
    j.at("initials").get_to(s.initials);
    j.at("birth_year").get_to(s.birth_year);
    j.at("phone").get_to(s.phone);
    j.at("enrollment_year").get_to(s.enrollment_year);
    j.at("institute").get_to(s.institute);
    j.at("department").get_to(s.department);
}