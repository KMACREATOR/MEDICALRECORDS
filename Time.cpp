#include "Time.h"
#include "json.hpp"

// Конструктор
Time::Time(const std::string& datetime)
    : datetime(datetime)
{
}

// Геттер даты/времени
const std::string& Time::getDateTime() const { return datetime; }

// Оператор ==
bool Time::operator==(const Time& other) const { return datetime == other.datetime; }

// Оператор !=
bool Time::operator!=(const Time& other) const { return !(*this == other); }

// Оператор <
bool Time::operator<(const Time& other) const { return datetime < other.datetime; }

// Оператор >
bool Time::operator>(const Time& other) const { return datetime > other.datetime; }

// Оператор <=
bool Time::operator<=(const Time& other) const { return !(*this > other); }

// Оператор >=
bool Time::operator>=(const Time& other) const { return !(*this < other); }

// Сериализация в JSON
void Time::to_json(json& j) const { j["visit_datetime"] = datetime; }

// Десериализация из JSON
void from_json(const json& j, Time& t) { j.at("visit_datetime").get_to(t.datetime); }