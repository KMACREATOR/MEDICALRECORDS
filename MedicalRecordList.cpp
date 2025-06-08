#include "MedicalRecordList.h"

#include "json.hpp"

#include <algorithm>
#include <fstream>
#include <iostream>

using json = nlohmann::json;

void MedicalRecordList::addRecord(const MedicalRecord& record) { records.push_back(record); }

void MedicalRecordList::printAll() const
{
    for(const auto& record : records) {
        record.print();
    }
}

void MedicalRecordList::sortByDate() { std::sort(records.begin(), records.end()); }

void MedicalRecordList::saveToFile(const std::string& filename) const
{
    json data = json::array();
    for(const auto& record : records) {
        json j;
        record.to_json(j);
        data.push_back(j);
    }

    std::ofstream file(filename);
    if(file.is_open()) {
        file << data.dump(4); // Formatted output
        file.close();
        std::cout << "Data successfully saved to file: " << filename << "\n";
    } else {
        std::cerr << "Failed to open file for writing: " << filename << "\n";
    }
}

void MedicalRecordList::loadFromFile(const std::string& filename)
{
    std::ifstream file(filename);
    if(!file.is_open()) {
        std::cerr << "Failed to open file: " << filename << "\n";
        return;
    }

    json data;
    try {
        file >> data;
    } catch(const std::exception& e) {
        std::cerr << "JSON reading error: " << e.what() << "\n";
        return;
    }

    records.clear();
    for(const auto& j : data) {
        MedicalRecord record(j.value("surname", ""), "", 0, "", 0, "", "", "", "", "", "", "", "");
        from_json(j, record);
        records.push_back(record);
    }

    std::cout << "Data successfully loaded from file: " << filename << "\n";
}