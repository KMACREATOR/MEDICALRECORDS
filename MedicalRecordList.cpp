#include "MedicalRecordList.h"
#include <algorithm>
#include <fstream>
#include <iostream>
#include "json.hpp"
#include "sodium.h"

using json = nlohmann::json;

#include <iomanip>
#include <sodium.h>
#include <sstream>

// Вспомогательная функция: преобразует строку в hex
std::string to_hex(const std::string& input)
{
    std::stringstream hex_stream;
    hex_stream << std::hex << std::setfill('0');
    for(unsigned char c : input) {
        hex_stream << std::setw(2) << static_cast<int>(static_cast<unsigned char>(c));
    }
    return hex_stream.str();
}

// Обратно: hex -> строка
std::string from_hex(const std::string& hex)
{
    std::string result;
    for(size_t i = 0; i < hex.size(); i += 2) {
        std::string byte_str = hex.substr(i, 2);
        unsigned char byte = static_cast<unsigned char>(strtol(byte_str.c_str(), nullptr, 16));
        result.push_back(byte);
    }
    return result;
}



void derive_key_from_password(const std::string& password, unsigned char key[crypto_secretbox_KEYBYTES])
{
    static bool warned = false;

    // Простейший вариант для случаев, когда crypto_pwhash недоступен
    if(password.empty()) {
        sodium_memzero(key, crypto_secretbox_KEYBYTES);
        return;
    }

    // Хешируем пароль через SHA-256
    crypto_hash_sha256(key, (const unsigned char*)password.data(), password.length());

    // Дополняем ключ до нужной длины если требуется
    if(crypto_secretbox_KEYBYTES > crypto_hash_sha256_BYTES) {
        unsigned char tmp[crypto_hash_sha256_BYTES];
        memcpy(tmp, key, crypto_hash_sha256_BYTES);
        for(size_t i = crypto_hash_sha256_BYTES; i < crypto_secretbox_KEYBYTES; ++i) {
            key[i] = tmp[i % crypto_hash_sha256_BYTES];
        }
    }

    if(!warned) {
        std::cerr << "Warning: Using simplified key derivation. For better security use crypto_pwhash.\n";
        warned = true;
    }
}


void MedicalRecordList::addRecord(const MedicalRecord& record) {
    records.push_back(record);
}

void MedicalRecordList::printAll() const {
    for (const auto& record : records) {
        record.print();
    }
}


std::vector<MedicalRecord> MedicalRecordList::findByDateRange(const std::string& start_date,
                                                              const std::string& end_date) const
{
    std::vector<MedicalRecord> result;

    for(const auto& record : records) {
        std::string visit_date = record.getVisitDate();

        if(visit_date >= start_date && visit_date <= end_date) {
            result.push_back(record);
        }
    }

    return result;
}

void MedicalRecordList::sortByDate() {
    std::sort(records.begin(), records.end());
}

void MedicalRecordList::saveToFile(const std::string& filename) const {
    json data = json::array();
    for (const auto& record : records) {
        json j;
        record.to_json(j);
        data.push_back(j);
    }

    std::ofstream file(filename);
    if (file.is_open()) {
        file << data.dump(4);  // Formatted output
        file.close();
        std::cout << "Data successfully saved to file: " << filename << "\n";
    } else {
        std::cerr << "Failed to open file for writing: " << filename << "\n";
    }
}

void MedicalRecordList::loadFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Failed to open file: " << filename << "\n";
        return;
    }

    json data;
    try {
        file >> data;
    } catch (const std::exception& e) {
        std::cerr << "JSON reading error: " << e.what() << "\n";
        return;
    }

    records.clear();
    for(const auto& j : data) {
        MedicalRecord record("", "", 0, "", 0, "", "", "", "", "", "", "");
        from_json(j, record); // Заполняем данные из JSON
        records.push_back(record);
    }

    std::cout << "Data successfully loaded from file: " << filename << "\n";
}

std::vector<MedicalRecord> MedicalRecordList::findByDate(const std::string& date) const
{
    std::vector<MedicalRecord> result;

    for(const auto& record : records) {
        if(record.getVisitDate().find(date) == 0) {
            result.push_back(record);
        }
    }

    return result;
}

int MedicalRecordList::countStudentsWithRest(const std::string& start_date, const std::string& end_date) const
{
    int count = 0;

    for(const auto& record : records) {
        std::string visit_date = record.getVisitDate();
        std::string rec = record.getRecommendations();

        if(visit_date >= start_date && visit_date <= end_date && rec.find("rest") != std::string::npos) {
            ++count;
        }
    }

    return count;
}


std::string MedicalRecordList::encrypt(const std::string& data, const std::string& password)
{
    unsigned char key[crypto_secretbox_KEYBYTES];
    derive_key_from_password(password, key);

    // Генерируем случайный nonce
    unsigned char nonce[crypto_secretbox_NONCEBYTES];
    randombytes_buf(nonce, sizeof nonce);

    // Буфер для зашифрованных данных (+ MAC)
    std::vector<unsigned char> ciphertext(data.size() + crypto_secretbox_MACBYTES);

    // Шифруем
    if(crypto_secretbox_easy(ciphertext.data(), (const unsigned char*)data.data(), data.size(), nonce, key) != 0) {
        return ""; // Ошибка шифрования
    }

    // Объединяем nonce + зашифрованные данные
    std::string result;
    result.assign((char*)nonce, crypto_secretbox_NONCEBYTES);
    result.append((char*)ciphertext.data(), ciphertext.size());

    return result;
}

std::string MedicalRecordList::decrypt(const std::string& cipher, const std::string& password)
{
    if(cipher.size() <= crypto_secretbox_NONCEBYTES) {
        return ""; // Слишком короткие данные
    }

    unsigned char key[crypto_secretbox_KEYBYTES];
    derive_key_from_password(password, key);

    // Извлекаем nonce
    const unsigned char* nonce = (const unsigned char*)cipher.data();

    // Извлекаем зашифрованные данные (после nonce)
    const unsigned char* encrypted = (const unsigned char*)cipher.data() + crypto_secretbox_NONCEBYTES;
    size_t encrypted_len = cipher.size() - crypto_secretbox_NONCEBYTES;

    // Буфер для расшифровки
    std::vector<unsigned char> decrypted(encrypted_len - crypto_secretbox_MACBYTES);

    // Пытаемся расшифровать
    if(crypto_secretbox_open_easy(decrypted.data(), encrypted, encrypted_len, nonce, key) != 0) {
        return ""; // Ошибка (неверный пароль или повреждённые данные)
    }

    return std::string((char*)decrypted.data(), decrypted.size());
}


void MedicalRecordList::saveToFileEncrypted(const std::string& filename, const std::string& password)
{
    json data = json::array();
    for(const auto& record : records) {
        json j;
        record.to_json(j);
        data.push_back(j);
    }

    std::string cipher = encrypt(data.dump(), password);
    if(cipher.empty()) {
        std::cerr << "Ошибка шифрования!\n";
        return;
    }

    std::ofstream file(filename, std::ios::binary);
    if(!file.write(cipher.data(), cipher.size())) {
        std::cerr << "Ошибка записи в файл!\n";
    }
}

void MedicalRecordList::loadFromFileEncrypted(const std::string& filename, const std::string& password)
{
    std::ifstream file(filename, std::ios::binary | std::ios::ate);
    if(!file.is_open()) {
        std::cerr << "Не удалось открыть файл!\n";
        return;
    }

    std::string cipher;
    cipher.resize(file.tellg());
    file.seekg(0);
    file.read(&cipher[0], cipher.size());

    std::string plaintext = decrypt(cipher, password);
    if(plaintext.empty()) {
        std::cerr << "Ошибка расшифровки!\n";
        return;
    }

    try {
        records.clear();
        for(const auto& j : json::parse(plaintext)) {
            MedicalRecord r("", "", 0, "", 0, "", "", "", "", "", "", "");
            from_json(j, r);
            records.push_back(r);
        }
    } catch(...) {
        std::cerr << "Ошибка парсинга JSON!\n";
    }
}   

std::vector<MedicalRecord> MedicalRecordList::findByDateRangeAndDiagnosis(const std::string& start_date,
                                                                          const std::string& end_date,
                                                                          const std::string& diagnosis) const
{
    std::vector<MedicalRecord> result;

    for(const auto& record : records) {
        if(record.getVisitDate() >= start_date && record.getVisitDate() <= end_date &&
           record.getDiagnosis() == diagnosis) {
            result.push_back(record);
        }
    }

    return result;

}