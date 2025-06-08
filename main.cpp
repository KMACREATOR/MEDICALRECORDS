#include "MedicalRecordList.h"

#include <cstdlib>
#include <iostream>
#include <windows.h>

// Function to display the menu
void showMenu()
{
    std::cout << "\n===== Menu =====\n";
    std::cout << "1. Add Record\n";
    std::cout << "2. Show All Records\n";
    std::cout << "3. Sort by Visit Date\n";
    std::cout << "4. Save Database to File\n";
    std::cout << "5. Load Database from File\n";
    std::cout << "0. Exit\n";
    std::cout << "Choose an action: ";
}

int main()
{
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);
    setlocale(LC_ALL, "Russian");
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

            std::cout << "Birth Year: ";
            std::cin >> birth_year;
            std::cin.ignore();

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
            MedicalRecord record(surname, initials, birth_year, phone, enrollment_year, group, institute, department,
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