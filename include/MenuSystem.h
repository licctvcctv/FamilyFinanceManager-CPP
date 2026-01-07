#ifndef MENU_SYSTEM_H
#define MENU_SYSTEM_H

#include "FinanceManager.h"
#include "ReportGenerator.h"

/**
 * @brief 菜单系统类，提供用户交互界面
 */
class MenuSystem {
private:
    FinanceManager& manager;
    ReportGenerator reporter;
    bool running;

    // 子菜单处理
    void handleIncomeMenu();
    void handleExpenseMenu();
    void handleStatisticsMenu();

    // 收入操作
    void addIncomeRecord();
    void queryIncomeRecords();
    void deleteIncomeRecord();
    void modifyIncomeRecord();
    void printIncomeRecords();

    // 支出操作
    void addExpenseRecord();
    void queryExpenseRecords();
    void deleteExpenseRecord();
    void modifyExpenseRecord();
    void printExpenseRecords();

    // 显示记录列表
    void displayIncomeList(const std::vector<IncomeRecord>& records);
    void displayExpenseList(const std::vector<ExpenseRecord>& records);

public:
    // 构造函数
    explicit MenuSystem(FinanceManager& mgr);

    // 菜单显示
    void displayMainMenu();
    void displayIncomeMenu();
    void displayExpenseMenu();
    void displayStatisticsMenu();

    // 运行主循环
    void run();
};

#endif // MENU_SYSTEM_H
