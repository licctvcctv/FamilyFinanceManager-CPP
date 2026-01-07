#include "DisplayHelper.h"
#include <iostream>
#include <sstream>
#include <iomanip>
#include <cstdlib>

#ifdef _WIN32
#include <windows.h>
#endif

void DisplayHelper::clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void DisplayHelper::printHeader(const std::string& title) {
    std::cout << std::endl;
    printDoubleSeparator(60);
    std::cout << "║" << center(title, 58) << "║" << std::endl;
    printDoubleSeparator(60);
    std::cout << std::endl;
}

void DisplayHelper::printSubHeader(const std::string& title) {
    std::cout << std::endl;
    printSeparator(50, '-');
    std::cout << "  " << title << std::endl;
    printSeparator(50, '-');
}

void DisplayHelper::printSeparator(int width, char ch) {
    std::cout << std::string(width, ch) << std::endl;
}

void DisplayHelper::printDoubleSeparator(int width) {
    std::cout << "╔" << std::string(width - 2, '═') << "╗" << std::endl;
}

void DisplayHelper::printTableHeader(const std::vector<std::string>& headers, const std::vector<int>& widths) {
    std::cout << "┌";
    for (size_t i = 0; i < widths.size(); ++i) {
        std::cout << std::string(widths[i], '─');
        if (i < widths.size() - 1) std::cout << "┬";
    }
    std::cout << "┐" << std::endl;
    
    std::cout << "│";
    for (size_t i = 0; i < headers.size() && i < widths.size(); ++i) {
        std::cout << center(headers[i], widths[i]) << "│";
    }
    std::cout << std::endl;
    
    std::cout << "├";
    for (size_t i = 0; i < widths.size(); ++i) {
        std::cout << std::string(widths[i], '─');
        if (i < widths.size() - 1) std::cout << "┼";
    }
    std::cout << "┤" << std::endl;
}

void DisplayHelper::printTableRow(const std::vector<std::string>& values, const std::vector<int>& widths) {
    std::cout << "│";
    for (size_t i = 0; i < values.size() && i < widths.size(); ++i) {
        std::string val = values[i];
        if (static_cast<int>(val.length()) > widths[i] - 2) {
            val = val.substr(0, widths[i] - 4) + "..";
        }
        std::cout << " " << padRight(val, widths[i] - 2) << " │";
    }
    std::cout << std::endl;
}

void DisplayHelper::printTableSeparator(const std::vector<int>& widths) {
    std::cout << "├";
    for (size_t i = 0; i < widths.size(); ++i) {
        std::cout << std::string(widths[i], '─');
        if (i < widths.size() - 1) std::cout << "┼";
    }
    std::cout << "┤" << std::endl;
}

void DisplayHelper::printMessage(const std::string& message, bool isError) {
    if (isError) {
        setColor(COLOR_RED);
        std::cout << "[错误] " << message << std::endl;
    } else {
        std::cout << message << std::endl;
    }
    resetColor();
}

void DisplayHelper::printSuccess(const std::string& message) {
    setColor(COLOR_GREEN);
    std::cout << "[成功] " << message << std::endl;
    resetColor();
}

void DisplayHelper::printWarning(const std::string& message) {
    setColor(COLOR_YELLOW);
    std::cout << "[警告] " << message << std::endl;
    resetColor();
}

void DisplayHelper::printInfo(const std::string& message) {
    setColor(COLOR_CYAN);
    std::cout << "[信息] " << message << std::endl;
    resetColor();
}

std::string DisplayHelper::formatAmount(double amount) {
    std::ostringstream oss;
    oss << std::fixed << std::setprecision(2) << amount;
    return "¥" + oss.str();
}

std::string DisplayHelper::formatDate(const std::string& date) {
    if (date.length() != 10) return date;
    return date.substr(0, 4) + "年" + date.substr(5, 2) + "月" + date.substr(8, 2) + "日";
}

std::string DisplayHelper::formatPercentage(double percentage) {
    std::ostringstream oss;
    oss << std::fixed << std::setprecision(1) << percentage << "%";
    return oss.str();
}

std::string DisplayHelper::padRight(const std::string& str, int width) {
    if (static_cast<int>(str.length()) >= width) return str.substr(0, width);
    return str + std::string(width - str.length(), ' ');
}

std::string DisplayHelper::padLeft(const std::string& str, int width) {
    if (static_cast<int>(str.length()) >= width) return str.substr(0, width);
    return std::string(width - str.length(), ' ') + str;
}

std::string DisplayHelper::center(const std::string& str, int width) {
    if (static_cast<int>(str.length()) >= width) return str.substr(0, width);
    int padding = width - static_cast<int>(str.length());
    int leftPad = padding / 2;
    int rightPad = padding - leftPad;
    return std::string(leftPad, ' ') + str + std::string(rightPad, ' ');
}

void DisplayHelper::setColor(int color) {
#ifdef _WIN32
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
#else
    switch (color) {
        case COLOR_RED:    std::cout << "\033[31m"; break;
        case COLOR_GREEN:  std::cout << "\033[32m"; break;
        case COLOR_YELLOW: std::cout << "\033[33m"; break;
        case COLOR_BLUE:   std::cout << "\033[34m"; break;
        case COLOR_CYAN:   std::cout << "\033[36m"; break;
        default:           std::cout << "\033[0m";  break;
    }
#endif
}

void DisplayHelper::resetColor() {
#ifdef _WIN32
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, COLOR_DEFAULT);
#else
    std::cout << "\033[0m";
#endif
}
