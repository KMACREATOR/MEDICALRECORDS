#include "MedicalRecordList.h"

#include <cstdlib>
#include <iostream>
#include <windows.h>

#include <string>
#include <stdexcept>
#include <sstream>
#include <iomanip>

#include <sodium.h>
#include <fstream>


//шифрование первый приоритет
// 
//TODO: добавить проверку того, не загружен ли уже файл
//TODO: добавить шифрование
//TODO: обернуть тестами
//TODO: добавить шифрование, отладку проверить
//TODO: добавить обработку исключение
//исключения в неправильных датах, например.
//т.е. ожидаемый формат добавить в try,
//все неправильное - в catch
//может быть написать отдельную функцию парсинга дат
//с уже зашитыми исключениями?
// 
// Function to display the menu
void showMenu()
{
    std::cout << "\n===== Menu =====\n";
    std::cout << "1. Add Record\n";
    std::cout << "2. Show All Records\n";
    std::cout << "3. Sort by Visit Date\n";
    std::cout << "4. Save Database to File\n";
    std::cout << "5. Load Database from File\n";
    std::cout << "6. Find by date\n";
    std::cout << "7. Find by date-range\n";
    std::cout << "8. Count exemped students in a data-range\n";
    std::cout << "9. Save and encrypt\n";
    std::cout << "10. Load and decrypt\n";
    std::cout << "0. Exit\n";
    std::cout << "Choose an action: ";
}


int main()
{
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);
    setlocale(LC_ALL, "Russian");
    if(sodium_init() < 0) {
        std::cerr << "Ошибка инициализации libsodium!" << std::endl;
        return 1;
    }





    MedicalRecordList list;
    int choice;

    do {
        showMenu();
        std::cin >> choice;
        std::cin.ignore(); // Clear input buffer after numeric input

        switch(choice) {
        case 1: {
            std::string surname, initials, phone, group, institute, department;
            std::string visit_datetime, diagnosis, recommendations, doctor_surname, doctor_initials;
            int birth_year = 0, enrollment_year = 0;

            std::cout << "Student Surname: ";
            std::getline(std::cin, surname);

            std::cout << "Student Initials: ";
            std::getline(std::cin, initials);

            //обработка исключений неправильных дат
            std::cout << "Birth Year: ";
            std::cin >> birth_year;
            std::cin.ignore();

            //может быть обработку исключений неправильных номеров?
            std::cout << "Phone: ";
            std::getline(std::cin, phone);

            std::cout << "Enrollment Year: ";
            std::cin >> enrollment_year;
            std::cin.ignore();

            std::cout << "Group: ";
            std::getline(std::cin, group);

            std::cout << "Institute (abbreviation): ";
            std::getline(std::cin, institute);

            std::cout << "Department (abbreviation): ";
            std::getline(std::cin, department);

            //обработка неправильных дат
            std::cout << "Visit Date and Time (format YYYY-MM-DD HH:MM): ";
            std::getline(std::cin, visit_datetime);

            std::cout << "Diagnosis: ";
            std::getline(std::cin, diagnosis);

            std::cout << "Doctor's Recommendations: ";
            std::getline(std::cin, recommendations);

            std::cout << "Doctor Surname: ";
            std::getline(std::cin, doctor_surname);

            std::cout << "Doctor Initials: ";
            std::getline(std::cin, doctor_initials);

            // Create a new record
            MedicalRecord record(surname, initials, birth_year, phone, enrollment_year, institute, department,
                                 visit_datetime, diagnosis, recommendations, doctor_surname, doctor_initials);

            list.addRecord(record);
            std::cout << "Record successfully added!\n";
            break;
        }

        case 2:
            std::cout << "\n=== All Records ===\n";
            list.printAll();
            break;

        case 3:
            list.sortByDate();
            std::cout << "The list has been sorted by date.\n";
            break;

        case 4: {
            std::string filename;
            std::cout << "Enter the file name to save: ";
            std::getline(std::cin, filename);
            list.saveToFile(filename);
            break;
        }

        case 5: {
            std::string filename;
            std::cout << "Enter the file name to load: ";
            std::getline(std::cin, filename);
            list.loadFromFile(filename);
            break;
        }

        case 6: {
            std::string date;
            std::cout << "Enter date for searching (YYYY-MM-DD): ";
            std::getline(std::cin, date);

                

            std::vector<MedicalRecord> found = list.findByDate(date);
            std::cout << "\n=== Found records ===\n";
            if(found.empty()) {
                std::cout << "No records found.\n";
            } else {
                for(const auto& r : found) {
                    r.print();
                }
            }
            break;
        }
        case 7: {
            std::string start_date, end_date;

            std::cout << "Enter early date (YYYY-MM-DD): ";
            std::getline(std::cin, start_date);

            std::cout << "Enter latter date (YYYY-MM-DD): ";
            std::getline(std::cin, end_date);

            std::vector<MedicalRecord> found = list.findByDateRange(start_date, end_date);

            std::cout << "\n=== Found records ===\n";
            if(found.empty()) {
                std::cout << "No records found.\n";
            } else {
                for(const auto& r : found) {
                    r.print();
                }
            }
            break;
        }
        case 8: {
            std::string start_date, end_date;
            
            std::cout << "Enter early date (YYYY-MM-DD): ";
            std::getline(std::cin, start_date);

            std::cout << "Entry later date (YYYY-MM-DD): ";
            std::getline(std::cin, end_date);

            int total = list.countStudentsWithRest(start_date, end_date);
            std::cout << "Amount of students, who received exempt from classes from " << start_date << " to " << end_date << ": "
                      << total << "\n";
            break;
        }
        case 9: {
            std::string filename;
            std::string password;

            std::cout << "Введите имя файла для сохранения: ";
            std::getline(std::cin, filename);

            std::cout << "Введите пароль для шифрования: ";
            std::getline(std::cin, password);

            list.saveToFileEncrypted(filename, password);
            break;
        }

        case 10: {
            std::string filename;
            std::string password;

            std::cout << "Введите имя файла для загрузки: ";
            std::getline(std::cin, filename);

            std::cout << "Введите пароль для расшифровки: ";
            std::getline(std::cin, password);

            list.loadFromFileEncrypted(filename, password);
            break;
        }
        case 0:
            std::cout << "Exiting program.\n";
            break;

        default:
            std::cout << "Invalid choice. Please try again.\n";
            break;
        }

    } while(choice != 0);

    return 0;
}