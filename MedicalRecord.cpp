#include "MedicalRecord.h"

#include "Student.h"
#include "Time.h"

#include <iostream>

// Use the json alias to avoid writing nlohmann::json every time
using json = nlohmann::json;

// Constructor: initialize base classes via initialization lists
MedicalRecord::MedicalRecord(const std::string& surname, const std::string& initials, int birth_year,
                             const std::string& phone, int enrollment_year, const std::string& institute,
                             const std::string& department, const std::string& visit_datetime,
                             const std::string& diagnosis, const std::string& recommendations,
                             const std::string& doctor_surname, const std::string& doctor_initials)
    : Student(surname, initials, birth_year, phone, enrollment_year, institute, department)
    , visit_datetime(visit_datetime)
    , diagnosis(diagnosis)
    , recommendations(recommendations)
    , doctor_surname(doctor_surname)
    , doctor_initials(doctor_initials)
{
}

void MedicalRecord::print() const
{
    Student::print();
    std::cout << "Дата обращения: " << visit_datetime << "\n"
              << "Диагноз: " << diagnosis << "\n"
              << "Рекомендации: " << recommendations << "\n"
              << "Врач: " << doctor_surname << " " << doctor_initials << "\n"
              << "----------------------------\n";
}

void MedicalRecord::to_json(json& j) const
{
    Student::to_json(j);
    j["visit_datetime"] = visit_datetime;
    j["diagnosis"] = diagnosis;
    j["recommendations"] = recommendations;
    j["doctor_surname"] = doctor_surname;
    j["doctor_initials"] = doctor_initials;
}

// Deserialize object from JSON
void from_json(const json& j, MedicalRecord& r)
{
    // Call deserialization for base classes
    from_json(j, static_cast<Student&>(r));
    from_json(j, static_cast<Time&>(r));

    // Load specific fields
    j.at("diagnosis").get_to(r.diagnosis);
    j.at("recommendations").get_to(r.recommendations);
    j.at("doctor_surname").get_to(r.doctor_surname);
    j.at("doctor_initials").get_to(r.doctor_initials);
}