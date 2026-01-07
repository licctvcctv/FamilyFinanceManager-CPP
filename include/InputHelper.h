#ifndef INPUT_HELPER_H
#define INPUT_HELPER_H

#include <string>
#include <vector>

/**
 * @brief 输入辅助类，提供输入验证和获取功能
 */
class InputHelper {
public:
    // 获取用户输入
    static int getMenuChoice(int min, int max);
    static double getAmount(const std::string& prompt);
    static std::string getDate(const std::string& prompt);
    static std::string getString(const std::string& prompt, bool required = true);
    static bool getConfirmation(const std::string& prompt);
    static int getRecordId(const std::string& prompt);
    static std::string getCategory(const std::string& prompt, const std::vector<std::string>& categories);

    // 验证函数
    static bool isValidDate(const std::string& date);
    static bool isValidAmount(double amount);
    static bool isNumeric(const std::string& str);
    static bool isValidDateRange(const std::string& startDate, const std::string& endDate);

    // 工具函数
    static std::string trim(const std::string& str);
    static void clearInputBuffer();
    static void pauseScreen();
    static std::string getCurrentDate();

    // 预定义分类
    static std::vector<std::string> getIncomeCategories();
    static std::vector<std::string> getExpenseCategories();

private:
    // 日期验证辅助函数
    static bool isLeapYear(int year);
    static int getDaysInMonth(int year, int month);
};

#endif // INPUT_HELPER_H
