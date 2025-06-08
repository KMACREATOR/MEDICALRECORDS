#ifndef MEDICALRECORDLIST_H
#define MEDICALRECORDLIST_H

#include "MedicalRecord.h"
#include <vector>
#include <string>

class MedicalRecordList {
private:
    std::vector<MedicalRecord> records;

public:
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