#ifndef RECORD_STORAGE_H
#define RECORD_STORAGE_H

#include <string>
#include <vector>
#include "IncomeRecord.h"
#include "ExpenseRecord.h"

/**
 * @brief 数据存储类，负责文件读写和数据持久化
 */
class RecordStorage {
private:
    std::string incomeFilePath;
    std::string expenseFilePath;
    int nextIncomeId;
    int nextExpenseId;

    // CSV处理辅助函数
    std::string escapeCSV(const std::string& field) const;
    std::string unescapeCSV(const std::string& field) const;
    std::vector<std::string> splitCSV(const std::string& line) const;
    
    // 确保数据目录存在
    bool ensureDataDirectory() const;

public:
    // 构造函数
    RecordStorage(const std::string& incomeFile = "data/income.csv",
                  const std::string& expenseFile = "data/expense.csv");

    // 收入记录操作
    std::vector<IncomeRecord> loadIncomeRecords();
    bool saveIncomeRecords(const std::vector<IncomeRecord>& records);
    int getNextIncomeId();

    // 支出记录操作
    std::vector<ExpenseRecord> loadExpenseRecords();
    bool saveExpenseRecords(const std::vector<ExpenseRecord>& records);
    int getNextExpenseId();
    
    // 文件路径
    std::string getIncomeFilePath() const;
    std::string getExpenseFilePath() const;
};

#endif // RECORD_STORAGE_H
