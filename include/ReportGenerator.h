#ifndef REPORT_GENERATOR_H
#define REPORT_GENERATOR_H

#include <vector>
#include <string>
#include <map>
#include "FinanceManager.h"

/**
 * @brief 月度汇总结构
 */
struct MonthlySummary {
    std::string month;      // YYYY-MM
    double totalIncome;
    double totalExpense;
    double netBalance;
    
    MonthlySummary() : totalIncome(0), totalExpense(0), netBalance(0) {}
};

/**
 * @brief 分类汇总结构
 */
struct CategorySummary {
    std::string category;
    double total;
    double percentage;
    
    CategorySummary() : total(0), percentage(0) {}
};

/**
 * @brief 报表生成类，提供各种统计报表功能
 */
class ReportGenerator {
private:
    FinanceManager& manager;

public:
    // 构造函数
    explicit ReportGenerator(FinanceManager& mgr);

    // 收入报表
    void printAllIncomeRecords();
    void printIncomeByMonth();
    void printIncomeByCategory();

    // 支出报表
    void printAllExpenseRecords();
    void printExpenseByMonth();
    void printExpenseByCategory();

    // 综合统计
    void printMonthlySummary();
    void printCategoryBreakdown();
    void printOverallSummary();

    // 计算方法
    std::vector<MonthlySummary> calculateMonthlySummary() const;
    std::vector<CategorySummary> calculateIncomeCategorySummary() const;
    std::vector<CategorySummary> calculateExpenseCategorySummary() const;
    
    // 辅助方法
    static std::string extractMonth(const std::string& date);
    double calculateTotalFromRecords(const std::vector<IncomeRecord>& records) const;
    double calculateTotalFromRecords(const std::vector<ExpenseRecord>& records) const;
};

#endif // REPORT_GENERATOR_H
