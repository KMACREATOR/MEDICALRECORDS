#ifndef TIME_H
#define TIME_H

#include "json.hpp"
#include <string>

using json = nlohmann::json;

class Time
{
protected:
    std::string datetime;

public:
    // Конструктор
    explicit Time(const std::string& datetime);

    // Виртуальный деструктор для наследования
    virtual ~Time() = default;

    // Геттер
    const std::string& getDateTime() const;

    // Операторы сравнения
    bool operator==(const Time& other) const;
    bool operator!=(const Time& other) const;
    bool operator<(const Time& other) const;
    bool operator>(const Time& other) const;
    bool operator<=(const Time& other) const;
    bool operator>=(const Time& other) const;

    // Сериализация в JSON
    virtual void to_json(json& j) const;

    // Десериализация из JSON
    friend void from_json(const json& j, Time& t);
};

#endif // TIME_H