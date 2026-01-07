#ifndef DISPLAY_HELPER_H
#define DISPLAY_HELPER_H

#include <string>
#include <vector>

/**
 * @brief 显示辅助类，提供格式化输出功能
 */
class DisplayHelper {
public:
    // 屏幕控制
    static void clearScreen();
    
    // 标题和分隔线
    static void printHeader(const std::string& title);
    static void printSubHeader(const std::string& title);
    static void printSeparator(int width = 60, char ch = '-');
    static void printDoubleSeparator(int width = 60);
    
    // 表格输出
    static void printTableHeader(const std::vector<std::string>& headers,
                                  const std::vector<int>& widths);
    static void printTableRow(const std::vector<std::string>& values,
                               const std::vector<int>& widths);
    static void printTableSeparator(const std::vector<int>& widths);
    
    // 消息输出
    static void printMessage(const std::string& message, bool isError = false);
    static void printSuccess(const std::string& message);
    static void printWarning(const std::string& message);
    static void printInfo(const std::string& message);
    
    // 格式化
    static std::string formatAmount(double amount);
    static std::string formatDate(const std::string& date);
    static std::string formatPercentage(double percentage);
    static std::string padRight(const std::string& str, int width);
    static std::string padLeft(const std::string& str, int width);
    static std::string center(const std::string& str, int width);
    
    // 颜色支持（Windows控制台）
    static void setColor(int color);
    static void resetColor();
    
    // 常用颜色常量
    static const int COLOR_DEFAULT = 7;
    static const int COLOR_RED = 12;
    static const int COLOR_GREEN = 10;
    static const int COLOR_YELLOW = 14;
    static const int COLOR_BLUE = 9;
    static const int COLOR_CYAN = 11;
};

#endif // DISPLAY_HELPER_H
