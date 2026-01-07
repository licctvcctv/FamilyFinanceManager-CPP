#include "MenuSystem.h"
#include "InputHelper.h"
#include "DisplayHelper.h"
#include <iostream>

MenuSystem::MenuSystem(FinanceManager& mgr) : manager(mgr), reporter(mgr), running(true) {}

void MenuSystem::displayMainMenu() {
    DisplayHelper::printHeader("家庭财务小管家");
    std::cout << "  1. 收入管理" << std::endl;
    std::cout << "  2. 支出管理" << std::endl;
    std::cout << "  3. 统计报表" << std::endl;
    std::cout << "  0. 退出系统" << std::endl << std::endl;
}

void MenuSystem::displayIncomeMenu() {
    DisplayHelper::printHeader("收入管理");
    std::cout << "  1. 添加收入记录" << std::endl;
    std::cout << "  2. 查询收入记录" << std::endl;
    std::cout << "  3. 修改收入记录" << std::endl;
    std::cout << "  4. 删除收入记录" << std::endl;
    std::cout << "  5. 打印收入报表" << std::endl;
    std::cout << "  0. 返回主菜单" << std::endl << std::endl;
}

void MenuSystem::displayExpenseMenu() {
    DisplayHelper::printHeader("支出管理");
    std::cout << "  1. 添加支出记录" << std::endl;
    std::cout << "  2. 查询支出记录" << std::endl;
    std::cout << "  3. 修改支出记录" << std::endl;
    std::cout << "  4. 删除支出记录" << std::endl;
    std::cout << "  5. 打印支出报表" << std::endl;
    std::cout << "  0. 返回主菜单" << std::endl << std::endl;
}

void MenuSystem::displayStatisticsMenu() {
    DisplayHelper::printHeader("统计报表");
    std::cout << "  1. 月度收支汇总" << std::endl;
    std::cout << "  2. 分类统计" << std::endl;
    std::cout << "  3. 财务总览" << std::endl;
    std::cout << "  0. 返回主菜单" << std::endl << std::endl;
}

void MenuSystem::run() {
    while (running) {
        DisplayHelper::clearScreen();
        displayMainMenu();
        int choice = InputHelper::getMenuChoice(0, 3);
        switch (choice) {
            case 1: handleIncomeMenu(); break;
            case 2: handleExpenseMenu(); break;
            case 3: handleStatisticsMenu(); break;
            case 0:
                if (InputHelper::getConfirmation("确定要退出系统吗？")) {
                    manager.saveAll();
                    DisplayHelper::printSuccess("数据已保存，感谢使用！");
                    running = false;
                }
                break;
        }
    }
}

void MenuSystem::handleIncomeMenu() {
    bool inSubmenu = true;
    while (inSubmenu) {
        DisplayHelper::clearScreen();
        displayIncomeMenu();
        int choice = InputHelper::getMenuChoice(0, 5);
        switch (choice) {
            case 1: addIncomeRecord(); break;
            case 2: queryIncomeRecords(); break;
            case 3: modifyIncomeRecord(); break;
            case 4: deleteIncomeRecord(); break;
            case 5: printIncomeRecords(); break;
            case 0: inSubmenu = false; break;
        }
    }
}

void MenuSystem::handleExpenseMenu() {
    bool inSubmenu = true;
    while (inSubmenu) {
        DisplayHelper::clearScreen();
        displayExpenseMenu();
        int choice = InputHelper::getMenuChoice(0, 5);
        switch (choice) {
            case 1: addExpenseRecord(); break;
            case 2: queryExpenseRecords(); break;
            case 3: modifyExpenseRecord(); break;
            case 4: deleteExpenseRecord(); break;
            case 5: printExpenseRecords(); break;
            case 0: inSubmenu = false; break;
        }
    }
}

void MenuSystem::handleStatisticsMenu() {
    bool inSubmenu = true;
    while (inSubmenu) {
        DisplayHelper::clearScreen();
        displayStatisticsMenu();
        int choice = InputHelper::getMenuChoice(0, 3);
        switch (choice) {
            case 1: reporter.printMonthlySummary(); InputHelper::pauseScreen(); break;
            case 2: reporter.printCategoryBreakdown(); InputHelper::pauseScreen(); break;
            case 3: reporter.printOverallSummary(); InputHelper::pauseScreen(); break;
            case 0: inSubmenu = false; break;
        }
    }
}

void MenuSystem::addIncomeRecord() {
    DisplayHelper::clearScreen();
    DisplayHelper::printSubHeader("添加收入记录");
    std::string date = InputHelper::getDate("请输入日期");
    double amount = InputHelper::getAmount("请输入金额: ");
    std::string category = InputHelper::getCategory("请选择分类", InputHelper::getIncomeCategories());
    std::string source = InputHelper::getString("请输入来源: ");
    std::string description = InputHelper::getString("请输入描述 (可选): ", false);
    
    int id = manager.getNextIncomeId();
    IncomeRecord record(id, date, amount, category, source, description);
    std::cout << std::endl << "即将添加以下记录：" << std::endl;
    record.display();
    
    if (InputHelper::getConfirmation("确认添加？")) {
        if (manager.addIncome(record)) DisplayHelper::printSuccess("收入记录添加成功！");
        else DisplayHelper::printMessage("添加失败，请重试。", true);
    } else DisplayHelper::printInfo("已取消添加。");
    InputHelper::pauseScreen();
}

void MenuSystem::queryIncomeRecords() {
    DisplayHelper::clearScreen();
    DisplayHelper::printSubHeader("查询收入记录");
    std::cout << "  1. 查询所有记录" << std::endl;
    std::cout << "  2. 按日期范围查询" << std::endl;
    std::cout << "  3. 按分类查询" << std::endl;
    std::cout << "  0. 返回" << std::endl << std::endl;
    
    int choice = InputHelper::getMenuChoice(0, 3);
    std::vector<IncomeRecord> results;
    
    switch (choice) {
        case 1: results = manager.getAllIncome(); break;
        case 2: {
            std::string startDate = InputHelper::getDate("请输入开始日期");
            std::string endDate = InputHelper::getDate("请输入结束日期");
            if (startDate > endDate) { DisplayHelper::printMessage("开始日期不能晚于结束日期！", true); InputHelper::pauseScreen(); return; }
            results = manager.queryIncomeByDateRange(startDate, endDate);
            break;
        }
        case 3: results = manager.queryIncomeByCategory(InputHelper::getCategory("请选择分类", InputHelper::getIncomeCategories())); break;
        case 0: return;
    }
    displayIncomeList(results);
    InputHelper::pauseScreen();
}

void MenuSystem::modifyIncomeRecord() {
    DisplayHelper::clearScreen();
    DisplayHelper::printSubHeader("修改收入记录");
    auto records = manager.getAllIncome();
    if (records.empty()) { DisplayHelper::printInfo("暂无收入记录可修改。"); InputHelper::pauseScreen(); return; }
    displayIncomeList(records);
    
    int id = InputHelper::getRecordId("请输入要修改的记录ID: ");
    IncomeRecord* record = manager.getIncomeById(id);
    if (!record) { DisplayHelper::printMessage("未找到该记录！", true); InputHelper::pauseScreen(); return; }
    
    std::cout << std::endl << "当前记录信息：" << std::endl;
    record->display();
    std::cout << std::endl << "请输入新值（直接回车保持原值）：" << std::endl;
    
    std::string newDate = InputHelper::getString("新日期 [" + record->getDate() + "]: ", false);
    std::string amountStr = InputHelper::getString("新金额 [" + std::to_string(record->getAmount()) + "]: ", false);
    std::string newCategory = InputHelper::getString("新分类 [" + record->getCategory() + "]: ", false);
    std::string newSource = InputHelper::getString("新来源 [" + record->getSource() + "]: ", false);
    std::string newDesc = InputHelper::getString("新描述 [" + record->getDescription() + "]: ", false);
    
    IncomeRecord newData;
    newData.setDate(newDate);
    if (!amountStr.empty() && InputHelper::isNumeric(amountStr)) newData.setAmount(std::stod(amountStr));
    newData.setCategory(newCategory);
    newData.setSource(newSource);
    newData.setDescription(newDesc);
    
    if (InputHelper::getConfirmation("确认修改？")) {
        if (manager.modifyIncome(id, newData)) DisplayHelper::printSuccess("记录修改成功！");
        else DisplayHelper::printMessage("修改失败，请重试。", true);
    } else DisplayHelper::printInfo("已取消修改。");
    InputHelper::pauseScreen();
}

void MenuSystem::deleteIncomeRecord() {
    DisplayHelper::clearScreen();
    DisplayHelper::printSubHeader("删除收入记录");
    auto records = manager.getAllIncome();
    if (records.empty()) { DisplayHelper::printInfo("暂无收入记录可删除。"); InputHelper::pauseScreen(); return; }
    displayIncomeList(records);
    
    int id = InputHelper::getRecordId("请输入要删除的记录ID: ");
    const IncomeRecord* record = manager.getIncomeById(id);
    if (!record) { DisplayHelper::printMessage("未找到该记录！", true); InputHelper::pauseScreen(); return; }
    
    std::cout << std::endl << "即将删除以下记录：" << std::endl;
    record->display();
    
    if (InputHelper::getConfirmation("确认删除？此操作不可恢复！")) {
        if (manager.deleteIncome(id)) DisplayHelper::printSuccess("记录删除成功！");
        else DisplayHelper::printMessage("删除失败，请重试。", true);
    } else DisplayHelper::printInfo("已取消删除。");
    InputHelper::pauseScreen();
}

void MenuSystem::printIncomeRecords() {
    DisplayHelper::clearScreen();
    DisplayHelper::printSubHeader("打印收入报表");
    std::cout << "  1. 打印所有记录" << std::endl;
    std::cout << "  2. 按月份统计" << std::endl;
    std::cout << "  3. 按分类统计" << std::endl;
    std::cout << "  0. 返回" << std::endl << std::endl;
    
    int choice = InputHelper::getMenuChoice(0, 3);
    switch (choice) {
        case 1: reporter.printAllIncomeRecords(); break;
        case 2: reporter.printIncomeByMonth(); break;
        case 3: reporter.printIncomeByCategory(); break;
        case 0: return;
    }
    InputHelper::pauseScreen();
}

void MenuSystem::addExpenseRecord() {
    DisplayHelper::clearScreen();
    DisplayHelper::printSubHeader("添加支出记录");
    std::string date = InputHelper::getDate("请输入日期");
    double amount = InputHelper::getAmount("请输入金额: ");
    std::string category = InputHelper::getCategory("请选择分类", InputHelper::getExpenseCategories());
    std::string payee = InputHelper::getString("请输入支付对象: ");
    std::string description = InputHelper::getString("请输入描述 (可选): ", false);
    
    int id = manager.getNextExpenseId();
    ExpenseRecord record(id, date, amount, category, payee, description);
    std::cout << std::endl << "即将添加以下记录：" << std::endl;
    record.display();
    
    if (InputHelper::getConfirmation("确认添加？")) {
        if (manager.addExpense(record)) DisplayHelper::printSuccess("支出记录添加成功！");
        else DisplayHelper::printMessage("添加失败，请重试。", true);
    } else DisplayHelper::printInfo("已取消添加。");
    InputHelper::pauseScreen();
}

void MenuSystem::queryExpenseRecords() {
    DisplayHelper::clearScreen();
    DisplayHelper::printSubHeader("查询支出记录");
    std::cout << "  1. 查询所有记录" << std::endl;
    std::cout << "  2. 按日期范围查询" << std::endl;
    std::cout << "  3. 按分类查询" << std::endl;
    std::cout << "  0. 返回" << std::endl << std::endl;
    
    int choice = InputHelper::getMenuChoice(0, 3);
    std::vector<ExpenseRecord> results;
    
    switch (choice) {
        case 1: results = manager.getAllExpense(); break;
        case 2: {
            std::string startDate = InputHelper::getDate("请输入开始日期");
            std::string endDate = InputHelper::getDate("请输入结束日期");
            if (startDate > endDate) { DisplayHelper::printMessage("开始日期不能晚于结束日期！", true); InputHelper::pauseScreen(); return; }
            results = manager.queryExpenseByDateRange(startDate, endDate);
            break;
        }
        case 3: results = manager.queryExpenseByCategory(InputHelper::getCategory("请选择分类", InputHelper::getExpenseCategories())); break;
        case 0: return;
    }
    displayExpenseList(results);
    InputHelper::pauseScreen();
}

void MenuSystem::modifyExpenseRecord() {
    DisplayHelper::clearScreen();
    DisplayHelper::printSubHeader("修改支出记录");
    auto records = manager.getAllExpense();
    if (records.empty()) { DisplayHelper::printInfo("暂无支出记录可修改。"); InputHelper::pauseScreen(); return; }
    displayExpenseList(records);
    
    int id = InputHelper::getRecordId("请输入要修改的记录ID: ");
    ExpenseRecord* record = manager.getExpenseById(id);
    if (!record) { DisplayHelper::printMessage("未找到该记录！", true); InputHelper::pauseScreen(); return; }
    
    std::cout << std::endl << "当前记录信息：" << std::endl;
    record->display();
    std::cout << std::endl << "请输入新值（直接回车保持原值）：" << std::endl;
    
    std::string newDate = InputHelper::getString("新日期 [" + record->getDate() + "]: ", false);
    std::string amountStr = InputHelper::getString("新金额 [" + std::to_string(record->getAmount()) + "]: ", false);
    std::string newCategory = InputHelper::getString("新分类 [" + record->getCategory() + "]: ", false);
    std::string newPayee = InputHelper::getString("新支付对象 [" + record->getPayee() + "]: ", false);
    std::string newDesc = InputHelper::getString("新描述 [" + record->getDescription() + "]: ", false);
    
    ExpenseRecord newData;
    newData.setDate(newDate);
    if (!amountStr.empty() && InputHelper::isNumeric(amountStr)) newData.setAmount(std::stod(amountStr));
    newData.setCategory(newCategory);
    newData.setPayee(newPayee);
    newData.setDescription(newDesc);
    
    if (InputHelper::getConfirmation("确认修改？")) {
        if (manager.modifyExpense(id, newData)) DisplayHelper::printSuccess("记录修改成功！");
        else DisplayHelper::printMessage("修改失败，请重试。", true);
    } else DisplayHelper::printInfo("已取消修改。");
    InputHelper::pauseScreen();
}

void MenuSystem::deleteExpenseRecord() {
    DisplayHelper::clearScreen();
    DisplayHelper::printSubHeader("删除支出记录");
    auto records = manager.getAllExpense();
    if (records.empty()) { DisplayHelper::printInfo("暂无支出记录可删除。"); InputHelper::pauseScreen(); return; }
    displayExpenseList(records);
    
    int id = InputHelper::getRecordId("请输入要删除的记录ID: ");
    const ExpenseRecord* record = manager.getExpenseById(id);
    if (!record) { DisplayHelper::printMessage("未找到该记录！", true); InputHelper::pauseScreen(); return; }
    
    std::cout << std::endl << "即将删除以下记录：" << std::endl;
    record->display();
    
    if (InputHelper::getConfirmation("确认删除？此操作不可恢复！")) {
        if (manager.deleteExpense(id)) DisplayHelper::printSuccess("记录删除成功！");
        else DisplayHelper::printMessage("删除失败，请重试。", true);
    } else DisplayHelper::printInfo("已取消删除。");
    InputHelper::pauseScreen();
}

void MenuSystem::printExpenseRecords() {
    DisplayHelper::clearScreen();
    DisplayHelper::printSubHeader("打印支出报表");
    std::cout << "  1. 打印所有记录" << std::endl;
    std::cout << "  2. 按月份统计" << std::endl;
    std::cout << "  3. 按分类统计" << std::endl;
    std::cout << "  0. 返回" << std::endl << std::endl;
    
    int choice = InputHelper::getMenuChoice(0, 3);
    switch (choice) {
        case 1: reporter.printAllExpenseRecords(); break;
        case 2: reporter.printExpenseByMonth(); break;
        case 3: reporter.printExpenseByCategory(); break;
        case 0: return;
    }
    InputHelper::pauseScreen();
}

void MenuSystem::displayIncomeList(const std::vector<IncomeRecord>& records) {
    if (records.empty()) { DisplayHelper::printInfo("没有找到符合条件的记录。"); return; }
    std::vector<std::string> headers = {"ID", "日期", "金额", "分类", "来源"};
    std::vector<int> widths = {6, 12, 14, 10, 15};
    DisplayHelper::printTableHeader(headers, widths);
    double total = 0.0;
    for (const auto& r : records) {
        DisplayHelper::printTableRow({std::to_string(r.getId()), r.getDate(), DisplayHelper::formatAmount(r.getAmount()), r.getCategory(), r.getSource()}, widths);
        total += r.getAmount();
    }
    std::cout << "└"; for (size_t i = 0; i < widths.size(); ++i) { std::cout << std::string(widths[i], '─'); if (i < widths.size() - 1) std::cout << "┴"; } std::cout << "┘" << std::endl;
    std::cout << std::endl << "共 " << records.size() << " 条记录，总计: " << DisplayHelper::formatAmount(total) << std::endl;
}

void MenuSystem::displayExpenseList(const std::vector<ExpenseRecord>& records) {
    if (records.empty()) { DisplayHelper::printInfo("没有找到符合条件的记录。"); return; }
    std::vector<std::string> headers = {"ID", "日期", "金额", "分类", "支付对象"};
    std::vector<int> widths = {6, 12, 14, 10, 15};
    DisplayHelper::printTableHeader(headers, widths);
    double total = 0.0;
    for (const auto& r : records) {
        DisplayHelper::printTableRow({std::to_string(r.getId()), r.getDate(), DisplayHelper::formatAmount(r.getAmount()), r.getCategory(), r.getPayee()}, widths);
        total += r.getAmount();
    }
    std::cout << "└"; for (size_t i = 0; i < widths.size(); ++i) { std::cout << std::string(widths[i], '─'); if (i < widths.size() - 1) std::cout << "┴"; } std::cout << "┘" << std::endl;
    std::cout << std::endl << "共 " << records.size() << " 条记录，总计: " << DisplayHelper::formatAmount(total) << std::endl;
}
