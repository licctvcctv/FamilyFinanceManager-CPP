#include "ReportGenerator.h"
#include "DisplayHelper.h"
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <map>

ReportGenerator::ReportGenerator(FinanceManager& mgr) : manager(mgr) {}

std::string ReportGenerator::extractMonth(const std::string& date) {
    return date.length() >= 7 ? date.substr(0, 7) : "";
}

double ReportGenerator::calculateTotalFromRecords(const std::vector<IncomeRecord>& records) const {
    double total = 0.0;
    for (const auto& r : records) total += r.getAmount();
    return total;
}

double ReportGenerator::calculateTotalFromRecords(const std::vector<ExpenseRecord>& records) const {
    double total = 0.0;
    for (const auto& r : records) total += r.getAmount();
    return total;
}

void ReportGenerator::printAllIncomeRecords() {
    DisplayHelper::printSubHeader("所有收入记录");
    auto records = manager.getAllIncome();
    if (records.empty()) { DisplayHelper::printInfo("暂无收入记录"); return; }
    
    std::vector<std::string> headers = {"ID", "日期", "金额", "分类", "来源", "描述"};
    std::vector<int> widths = {6, 12, 14, 10, 12, 20};
    DisplayHelper::printTableHeader(headers, widths);
    
    double total = 0.0;
    for (const auto& r : records) {
        std::vector<std::string> row = {std::to_string(r.getId()), r.getDate(), DisplayHelper::formatAmount(r.getAmount()), r.getCategory(), r.getSource(), r.getDescription()};
        DisplayHelper::printTableRow(row, widths);
        total += r.getAmount();
    }
    std::cout << "└"; for (size_t i = 0; i < widths.size(); ++i) { std::cout << std::string(widths[i], '─'); if (i < widths.size() - 1) std::cout << "┴"; } std::cout << "┘" << std::endl;
    std::cout << std::endl << "共 " << records.size() << " 条记录，总计: " << DisplayHelper::formatAmount(total) << std::endl;
}

void ReportGenerator::printIncomeByMonth() {
    DisplayHelper::printSubHeader("收入月度统计");
    auto records = manager.getAllIncome();
    if (records.empty()) { DisplayHelper::printInfo("暂无收入记录"); return; }
    
    std::map<std::string, double> monthlyTotals;
    for (const auto& r : records) monthlyTotals[extractMonth(r.getDate())] += r.getAmount();
    
    std::vector<std::string> headers = {"月份", "收入金额"};
    std::vector<int> widths = {12, 20};
    DisplayHelper::printTableHeader(headers, widths);
    
    double total = 0.0;
    for (const auto& p : monthlyTotals) {
        DisplayHelper::printTableRow({p.first, DisplayHelper::formatAmount(p.second)}, widths);
        total += p.second;
    }
    DisplayHelper::printTableSeparator(widths);
    DisplayHelper::printTableRow({"总计", DisplayHelper::formatAmount(total)}, widths);
    std::cout << "└"; for (size_t i = 0; i < widths.size(); ++i) { std::cout << std::string(widths[i], '─'); if (i < widths.size() - 1) std::cout << "┴"; } std::cout << "┘" << std::endl;
}

void ReportGenerator::printIncomeByCategory() {
    DisplayHelper::printSubHeader("收入分类统计");
    auto summaries = calculateIncomeCategorySummary();
    if (summaries.empty()) { DisplayHelper::printInfo("暂无收入记录"); return; }
    
    std::vector<std::string> headers = {"分类", "金额", "占比"};
    std::vector<int> widths = {12, 18, 10};
    DisplayHelper::printTableHeader(headers, widths);
    
    double total = 0.0;
    for (const auto& s : summaries) {
        DisplayHelper::printTableRow({s.category, DisplayHelper::formatAmount(s.total), DisplayHelper::formatPercentage(s.percentage)}, widths);
        total += s.total;
    }
    DisplayHelper::printTableSeparator(widths);
    DisplayHelper::printTableRow({"总计", DisplayHelper::formatAmount(total), "100.0%"}, widths);
    std::cout << "└"; for (size_t i = 0; i < widths.size(); ++i) { std::cout << std::string(widths[i], '─'); if (i < widths.size() - 1) std::cout << "┴"; } std::cout << "┘" << std::endl;
}

void ReportGenerator::printAllExpenseRecords() {
    DisplayHelper::printSubHeader("所有支出记录");
    auto records = manager.getAllExpense();
    if (records.empty()) { DisplayHelper::printInfo("暂无支出记录"); return; }
    
    std::vector<std::string> headers = {"ID", "日期", "金额", "分类", "支付对象", "描述"};
    std::vector<int> widths = {6, 12, 14, 10, 12, 20};
    DisplayHelper::printTableHeader(headers, widths);
    
    double total = 0.0;
    for (const auto& r : records) {
        std::vector<std::string> row = {std::to_string(r.getId()), r.getDate(), DisplayHelper::formatAmount(r.getAmount()), r.getCategory(), r.getPayee(), r.getDescription()};
        DisplayHelper::printTableRow(row, widths);
        total += r.getAmount();
    }
    std::cout << "└"; for (size_t i = 0; i < widths.size(); ++i) { std::cout << std::string(widths[i], '─'); if (i < widths.size() - 1) std::cout << "┴"; } std::cout << "┘" << std::endl;
    std::cout << std::endl << "共 " << records.size() << " 条记录，总计: " << DisplayHelper::formatAmount(total) << std::endl;
}

void ReportGenerator::printExpenseByMonth() {
    DisplayHelper::printSubHeader("支出月度统计");
    auto records = manager.getAllExpense();
    if (records.empty()) { DisplayHelper::printInfo("暂无支出记录"); return; }
    
    std::map<std::string, double> monthlyTotals;
    for (const auto& r : records) monthlyTotals[extractMonth(r.getDate())] += r.getAmount();
    
    std::vector<std::string> headers = {"月份", "支出金额"};
    std::vector<int> widths = {12, 20};
    DisplayHelper::printTableHeader(headers, widths);
    
    double total = 0.0;
    for (const auto& p : monthlyTotals) {
        DisplayHelper::printTableRow({p.first, DisplayHelper::formatAmount(p.second)}, widths);
        total += p.second;
    }
    DisplayHelper::printTableSeparator(widths);
    DisplayHelper::printTableRow({"总计", DisplayHelper::formatAmount(total)}, widths);
    std::cout << "└"; for (size_t i = 0; i < widths.size(); ++i) { std::cout << std::string(widths[i], '─'); if (i < widths.size() - 1) std::cout << "┴"; } std::cout << "┘" << std::endl;
}

void ReportGenerator::printExpenseByCategory() {
    DisplayHelper::printSubHeader("支出分类统计");
    auto summaries = calculateExpenseCategorySummary();
    if (summaries.empty()) { DisplayHelper::printInfo("暂无支出记录"); return; }
    
    std::vector<std::string> headers = {"分类", "金额", "占比"};
    std::vector<int> widths = {12, 18, 10};
    DisplayHelper::printTableHeader(headers, widths);
    
    double total = 0.0;
    for (const auto& s : summaries) {
        DisplayHelper::printTableRow({s.category, DisplayHelper::formatAmount(s.total), DisplayHelper::formatPercentage(s.percentage)}, widths);
        total += s.total;
    }
    DisplayHelper::printTableSeparator(widths);
    DisplayHelper::printTableRow({"总计", DisplayHelper::formatAmount(total), "100.0%"}, widths);
    std::cout << "└"; for (size_t i = 0; i < widths.size(); ++i) { std::cout << std::string(widths[i], '─'); if (i < widths.size() - 1) std::cout << "┴"; } std::cout << "┘" << std::endl;
}

void ReportGenerator::printMonthlySummary() {
    DisplayHelper::printSubHeader("月度收支汇总");
    auto summaries = calculateMonthlySummary();
    if (summaries.empty()) { DisplayHelper::printInfo("暂无财务记录"); return; }
    
    std::vector<std::string> headers = {"月份", "收入", "支出", "结余"};
    std::vector<int> widths = {10, 16, 16, 16};
    DisplayHelper::printTableHeader(headers, widths);
    
    double totalIncome = 0.0, totalExpense = 0.0;
    for (const auto& s : summaries) {
        DisplayHelper::printTableRow({s.month, DisplayHelper::formatAmount(s.totalIncome), DisplayHelper::formatAmount(s.totalExpense), DisplayHelper::formatAmount(s.netBalance)}, widths);
        totalIncome += s.totalIncome; totalExpense += s.totalExpense;
    }
    DisplayHelper::printTableSeparator(widths);
    DisplayHelper::printTableRow({"总计", DisplayHelper::formatAmount(totalIncome), DisplayHelper::formatAmount(totalExpense), DisplayHelper::formatAmount(totalIncome - totalExpense)}, widths);
    std::cout << "└"; for (size_t i = 0; i < widths.size(); ++i) { std::cout << std::string(widths[i], '─'); if (i < widths.size() - 1) std::cout << "┴"; } std::cout << "┘" << std::endl;
}

void ReportGenerator::printCategoryBreakdown() {
    DisplayHelper::printSubHeader("分类统计");
    std::cout << std::endl << "【收入分类】" << std::endl;
    printIncomeByCategory();
    std::cout << std::endl << "【支出分类】" << std::endl;
    printExpenseByCategory();
}

void ReportGenerator::printOverallSummary() {
    DisplayHelper::printSubHeader("财务总览");
    double totalIncome = manager.getTotalIncome();
    double totalExpense = manager.getTotalExpense();
    double netBalance = manager.getNetBalance();
    
    std::cout << std::endl;
    std::cout << "┌────────────────────────────────────────────┐" << std::endl;
    std::cout << "│              财务统计总览                  │" << std::endl;
    std::cout << "├────────────────────────────────────────────┤" << std::endl;
    std::cout << "│ 收入记录数:     " << std::setw(25) << std::left << manager.getIncomeCount() << "│" << std::endl;
    std::cout << "│ 支出记录数:     " << std::setw(25) << std::left << manager.getExpenseCount() << "│" << std::endl;
    std::cout << "├────────────────────────────────────────────┤" << std::endl;
    std::cout << "│ 总收入:         " << std::setw(25) << std::left << DisplayHelper::formatAmount(totalIncome) << "│" << std::endl;
    std::cout << "│ 总支出:         " << std::setw(25) << std::left << DisplayHelper::formatAmount(totalExpense) << "│" << std::endl;
    std::cout << "│ 净结余:         " << std::setw(25) << std::left << DisplayHelper::formatAmount(netBalance) << "│" << std::endl;
    std::cout << "└────────────────────────────────────────────┘" << std::endl;
    
    std::cout << std::endl;
    if (netBalance > 0) DisplayHelper::printSuccess("财务状况良好，收入大于支出！");
    else if (netBalance < 0) DisplayHelper::printWarning("注意：支出大于收入，建议控制开支。");
    else DisplayHelper::printInfo("收支平衡。");
}

std::vector<MonthlySummary> ReportGenerator::calculateMonthlySummary() const {
    std::map<std::string, MonthlySummary> monthlyData;
    for (const auto& r : manager.getAllIncome()) { auto m = extractMonth(r.getDate()); monthlyData[m].month = m; monthlyData[m].totalIncome += r.getAmount(); }
    for (const auto& r : manager.getAllExpense()) { auto m = extractMonth(r.getDate()); monthlyData[m].month = m; monthlyData[m].totalExpense += r.getAmount(); }
    
    std::vector<MonthlySummary> result;
    for (auto& p : monthlyData) { p.second.netBalance = p.second.totalIncome - p.second.totalExpense; result.push_back(p.second); }
    std::sort(result.begin(), result.end(), [](const MonthlySummary& a, const MonthlySummary& b) { return a.month < b.month; });
    return result;
}

std::vector<CategorySummary> ReportGenerator::calculateIncomeCategorySummary() const {
    std::map<std::string, double> categoryTotals;
    double grandTotal = 0.0;
    for (const auto& r : manager.getAllIncome()) { categoryTotals[r.getCategory()] += r.getAmount(); grandTotal += r.getAmount(); }
    
    std::vector<CategorySummary> result;
    for (const auto& p : categoryTotals) {
        CategorySummary s; s.category = p.first; s.total = p.second; s.percentage = grandTotal > 0 ? (p.second / grandTotal * 100.0) : 0.0;
        result.push_back(s);
    }
    std::sort(result.begin(), result.end(), [](const CategorySummary& a, const CategorySummary& b) { return a.total > b.total; });
    return result;
}

std::vector<CategorySummary> ReportGenerator::calculateExpenseCategorySummary() const {
    std::map<std::string, double> categoryTotals;
    double grandTotal = 0.0;
    for (const auto& r : manager.getAllExpense()) { categoryTotals[r.getCategory()] += r.getAmount(); grandTotal += r.getAmount(); }
    
    std::vector<CategorySummary> result;
    for (const auto& p : categoryTotals) {
        CategorySummary s; s.category = p.first; s.total = p.second; s.percentage = grandTotal > 0 ? (p.second / grandTotal * 100.0) : 0.0;
        result.push_back(s);
    }
    std::sort(result.begin(), result.end(), [](const CategorySummary& a, const CategorySummary& b) { return a.total > b.total; });
    return result;
}
