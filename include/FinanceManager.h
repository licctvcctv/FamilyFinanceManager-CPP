#ifndef FINANCE_MANAGER_H
#define FINANCE_MANAGER_H

#include <vector>
#include <string>
#include "IncomeRecord.h"
#include "ExpenseRecord.h"
#include "RecordStorage.h"

/**
 * @brief 财务管理类，提供业务逻辑功能
 */
class FinanceManager {
private:
    std::vector<IncomeRecord> incomeRecords;
    std::vector<ExpenseRecord> expenseRecords;
    RecordStorage storage;

    // 内部辅助方法
    IncomeRecord* findIncomeById(int id);
    ExpenseRecord* findExpenseById(int id);
    const IncomeRecord* findIncomeById(int id) const;
    const ExpenseRecord* findExpenseById(int id) const;

public:
    // 构造函数
    FinanceManager();
    FinanceManager(const std::string& incomeFile, const std::string& expenseFile);
    ~FinanceManager();

    // 初始化和保存
    bool initialize();
    bool saveAll();

    // 收入管理
    bool addIncome(const IncomeRecord& record);
    bool deleteIncome(int id);
    bool modifyIncome(int id, const IncomeRecord& newData);
    IncomeRecord* getIncomeById(int id);
    const IncomeRecord* getIncomeById(int id) const;
    
    // 收入查询
    std::vector<IncomeRecord> queryIncomeByDateRange(const std::string& startDate, 
                                                      const std::string& endDate) const;
    std::vector<IncomeRecord> queryIncomeByCategory(const std::string& category) const;
    std::vector<IncomeRecord> getAllIncome() const;
    int getIncomeCount() const;

    // 支出管理
    bool addExpense(const ExpenseRecord& record);
    bool deleteExpense(int id);
    bool modifyExpense(int id, const ExpenseRecord& newData);
    ExpenseRecord* getExpenseById(int id);
    const ExpenseRecord* getExpenseById(int id) const;
    
    // 支出查询
    std::vector<ExpenseRecord> queryExpenseByDateRange(const std::string& startDate,
                                                        const std::string& endDate) const;
    std::vector<ExpenseRecord> queryExpenseByCategory(const std::string& category) const;
    std::vector<ExpenseRecord> getAllExpense() const;
    int getExpenseCount() const;

    // 统计功能
    double getTotalIncome() const;
    double getTotalExpense() const;
    double getNetBalance() const;
    
    // ID生成
    int getNextIncomeId();
    int getNextExpenseId();
};

#endif // FINANCE_MANAGER_H
