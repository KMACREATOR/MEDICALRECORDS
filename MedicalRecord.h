#ifndef MEDICALRECORD_H
#define MEDICALRECORD_H

#include "Student.h"
#include "Time.h"

class MedicalRecord : public Student
{
private:
    std::string visit_datetime;
    std::string diagnosis;
    std::string recommendations;
    std::string doctor_surname;
    std::string doctor_initials;

public:
    MedicalRecord(const std::string& surname, const std::string& initials, int birth_year, const std::string& phone,
                  int enrollment_year, const std::string& institute, const std::string& department,
                  const std::string& visit_datetime, const std::string& diagnosis, const std::string& recommendations,
                  const std::string& doctor_surname, const std::string& doctor_initials);
    MedicalRecord()
        : MedicalRecord("", "", 0, "", 0, "", "", "", "", "", "", "")
    {
    }

    void print() const override;
    void to_json(json& j) const override;
    const std::string& getVisitDate() const;   
    friend void from_json(const json& j, MedicalRecord& r);
    bool operator<(const MedicalRecord& other) const;
    const std::string& getRecommendations() const;
};

#endif // MEDICALRECORD_H