#include "Record.h"

// 默认构造函数
Record::Record() : id(0), date(""), amount(0.0), category(""), description("") {
}

// 带参数构造函数
Record::Record(int id, const std::string& date, double amount,
               const std::string& category, const std::string& description)
    : id(id), date(date), amount(amount), category(category), description(description) {
}

// Getters
int Record::getId() const {
    return id;
}

std::string Record::getDate() const {
    return date;
}

double Record::getAmount() const {
    return amount;
}

std::string Record::getCategory() const {
    return category;
}

std::string Record::getDescription() const {
    return description;
}

// Setters
void Record::setId(int id) {
    this->id = id;
}

void Record::setDate(const std::string& date) {
    this->date = date;
}

void Record::setAmount(double amount) {
    this->amount = amount;
}

void Record::setCategory(const std::string& category) {
    this->category = category;
}

void Record::setDescription(const std::string& description) {
    this->description = description;
}
