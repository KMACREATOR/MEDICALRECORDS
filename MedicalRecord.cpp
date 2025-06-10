#include "MedicalRecord.h"

#include "Student.h"
//#include "Time.h"

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
    std::cout << "Visit date: " << visit_datetime << "\n"
              << "Diagnosis: " << diagnosis << "\n"
              << "Recommendations: " << recommendations << "\n"
              << "Doctor: " << doctor_surname << " " << doctor_initials << "\n"
              << "----------------------------\n";
}

const std::string& MedicalRecord::getVisitDate() const { return visit_datetime; }

void MedicalRecord::to_json(json& j) const
{
    Student::to_json(j);
    j["visit_datetime"] = visit_datetime;
    j["diagnosis"] = diagnosis;
    j["recommendations"] = recommendations;
    j["doctor_surname"] = doctor_surname;
    j["doctor_initials"] = doctor_initials;
}

void from_json(const json& j, MedicalRecord& r)
{
    from_json(j, static_cast<Student&>(r));
    j.at("visit_datetime").get_to(r.visit_datetime);
    j.at("diagnosis").get_to(r.diagnosis);
    j.at("recommendations").get_to(r.recommendations);
    j.at("doctor_surname").get_to(r.doctor_surname);
    j.at("doctor_initials").get_to(r.doctor_initials);
}

const std::string& MedicalRecord::getRecommendations() const { return recommendations; }

bool MedicalRecord::operator<(const MedicalRecord& other) const { return visit_datetime < other.visit_datetime; }


const std::string& MedicalRecord::getDiagnosis() const { return diagnosis; }
