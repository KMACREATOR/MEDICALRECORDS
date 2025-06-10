#ifndef MEDICALRECORDLIST_H
#define MEDICALRECORDLIST_H

#include "MedicalRecord.h"
#include <vector>
#include <string>

class MedicalRecordList {
private:
    std::vector<MedicalRecord> records;
    static std::string encrypt(const std::string& data, const std::string& password);
    static std::string decrypt(const std::string& cipher, const std::string& password);

public:
    std::vector<MedicalRecord> findByDateRangeAndDiagnosis(const std::string& start_date, const std::string& end_date,
                                                           const std::string& diagnosis) const;
    void saveToFileEncrypted(const std::string& filename, const std::string& password);
    void loadFromFileEncrypted(const std::string& filename, const std::string& password);
    std::vector<MedicalRecord> findByDate(const std::string& date) const;
    std::vector<MedicalRecord> findByDateRange(const std::string& start_date, const std::string& end_date) const;
    int countStudentsWithRest(const std::string& start_date, const std::string& end_date) const;
    // Добавление записи
    void addRecord(const MedicalRecord& record);

    // Вывод всех записей
    void printAll() const;

    // Сортировка по дате обращения
    void sortByDate();

    // Сохранение в JSON
    void saveToFile(const std::string& filename) const;

    // Загрузка из JSON
    void loadFromFile(const std::string& filename);
};

#endif // MEDICALRECORDLIST_H