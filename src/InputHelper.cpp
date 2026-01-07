#include "InputHelper.h"
#include <iostream>
#include <sstream>
#include <algorithm>
#include <cctype>
#include <ctime>
#include <limits>
#include <iomanip>

int InputHelper::getMenuChoice(int min, int max) {
    int choice;
    while (true) {
        std::cout << "请选择 [" << min << "-" << max << "]: ";
        std::string input;
        std::getline(std::cin, input);
        input = trim(input);
        
        if (input.empty()) {
            std::cout << "输入不能为空，请重新输入。" << std::endl;
            continue;
        }
        
        if (!isNumeric(input)) {
            std::cout << "请输入有效的数字。" << std::endl;
            continue;
        }
        
        try {
            choice = std::stoi(input);
            if (choice >= min && choice <= max) {
                return choice;
            }
            std::cout << "选项超出范围，请输入 " << min << " 到 " << max << " 之间的数字。" << std::endl;
        } catch (...) {
            std::cout << "输入无效，请重新输入。" << std::endl;
        }
    }
}

double InputHelper::getAmount(const std::string& prompt) {
    double amount;
    while (true) {
        std::cout << prompt;
        std::string input;
        std::getline(std::cin, input);
        input = trim(input);
        
        if (input.empty()) {
            std::cout << "金额不能为空，请重新输入。" << std::endl;
            continue;
        }
        
        try {
            amount = std::stod(input);
            if (isValidAmount(amount)) {
                return amount;
            }
            std::cout << "金额必须大于0，请重新输入。" << std::endl;
        } catch (...) {
            std::cout << "输入无效，请重新输入。" << std::endl;
        }
    }
}

std::string InputHelper::getDate(const std::string& prompt) {
    while (true) {
        std::cout << prompt << " (格式: YYYY-MM-DD，直接回车使用今天): ";
        std::string input;
        std::getline(std::cin, input);
        input = trim(input);
        
        if (input.empty()) {
            return getCurrentDate();
        }
        
        if (isValidDate(input)) {
            return input;
        }
        std::cout << "日期格式错误，请使用 YYYY-MM-DD 格式。" << std::endl;
    }
}

std::string InputHelper::getString(const std::string& prompt, bool required) {
    while (true) {
        std::cout << prompt;
        std::string input;
        std::getline(std::cin, input);
        input = trim(input);
        
        if (input.empty() && required) {
            std::cout << "此字段为必填项，不能为空。" << std::endl;
            continue;
        }
        
        if (input.length() > 200) {
            input = input.substr(0, 200);
        }
        
        return input;
    }
}

bool InputHelper::getConfirmation(const std::string& prompt) {
    while (true) {
        std::cout << prompt << " (Y/N): ";
        std::string input;
        std::getline(std::cin, input);
        input = trim(input);
        
        if (input.empty()) continue;
        
        char c = std::toupper(input[0]);
        if (c == 'Y') return true;
        if (c == 'N') return false;
        
        std::cout << "请输入 Y 或 N。" << std::endl;
    }
}

int InputHelper::getRecordId(const std::string& prompt) {
    while (true) {
        std::cout << prompt;
        std::string input;
        std::getline(std::cin, input);
        input = trim(input);
        
        if (input.empty()) {
            std::cout << "ID不能为空。" << std::endl;
            continue;
        }
        
        try {
            int id = std::stoi(input);
            if (id > 0) return id;
            std::cout << "ID必须大于0。" << std::endl;
        } catch (...) {
            std::cout << "请输入有效的数字ID。" << std::endl;
        }
    }
}

std::string InputHelper::getCategory(const std::string& prompt, const std::vector<std::string>& categories) {
    std::cout << prompt << std::endl << "可选分类：" << std::endl;
    
    for (size_t i = 0; i < categories.size(); ++i) {
        std::cout << "  " << (i + 1) << ". " << categories[i] << std::endl;
    }
    std::cout << "  " << (categories.size() + 1) << ". 自定义分类" << std::endl;
    
    int choice = getMenuChoice(1, static_cast<int>(categories.size() + 1));
    
    if (choice <= static_cast<int>(categories.size())) {
        return categories[choice - 1];
    }
    
    return getString("请输入自定义分类: ");
}

bool InputHelper::isValidDate(const std::string& date) {
    if (date.length() != 10) return false;
    if (date[4] != '-' || date[7] != '-') return false;
    
    for (int i = 0; i < 10; ++i) {
        if (i == 4 || i == 7) continue;
        if (!std::isdigit(date[i])) return false;
    }
    
    try {
        int year = std::stoi(date.substr(0, 4));
        int month = std::stoi(date.substr(5, 2));
        int day = std::stoi(date.substr(8, 2));
        
        if (year < 1900 || year > 2100) return false;
        if (month < 1 || month > 12) return false;
        
        int maxDays = getDaysInMonth(year, month);
        if (day < 1 || day > maxDays) return false;
        
        return true;
    } catch (...) {
        return false;
    }
}

bool InputHelper::isValidAmount(double amount) {
    return amount > 0;
}

bool InputHelper::isNumeric(const std::string& str) {
    if (str.empty()) return false;
    
    size_t start = 0;
    if (str[0] == '-' || str[0] == '+') {
        if (str.length() == 1) return false;
        start = 1;
    }
    
    bool hasDecimal = false;
    for (size_t i = start; i < str.length(); ++i) {
        if (str[i] == '.') {
            if (hasDecimal) return false;
            hasDecimal = true;
        } else if (!std::isdigit(str[i])) {
            return false;
        }
    }
    
    return true;
}

bool InputHelper::isValidDateRange(const std::string& startDate, const std::string& endDate) {
    return isValidDate(startDate) && isValidDate(endDate) && startDate <= endDate;
}

std::string InputHelper::trim(const std::string& str) {
    size_t start = str.find_first_not_of(" \t\n\r\f\v");
    if (start == std::string::npos) return "";
    size_t end = str.find_last_not_of(" \t\n\r\f\v");
    return str.substr(start, end - start + 1);
}

void InputHelper::clearInputBuffer() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void InputHelper::pauseScreen() {
    std::cout << std::endl << "按回车键继续...";
    std::cin.get();
}

std::string InputHelper::getCurrentDate() {
    time_t now = time(nullptr);
    tm* ltm = localtime(&now);
    
    std::ostringstream oss;
    oss << std::setfill('0')
        << (1900 + ltm->tm_year) << "-"
        << std::setw(2) << (1 + ltm->tm_mon) << "-"
        << std::setw(2) << ltm->tm_mday;
    
    return oss.str();
}

std::vector<std::string> InputHelper::getIncomeCategories() {
    return {"工资", "奖金", "投资收益", "兼职收入", "礼金", "其他"};
}

std::vector<std::string> InputHelper::getExpenseCategories() {
    return {"餐饮", "住房", "交通", "购物", "娱乐", "医疗", "教育", "水电费", "通讯费", "其他"};
}

bool InputHelper::isLeapYear(int year) {
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

int InputHelper::getDaysInMonth(int year, int month) {
    static const int daysInMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (month == 2 && isLeapYear(year)) return 29;
    return daysInMonth[month - 1];
}
