#include <iostream>
#include <locale>
#include "FinanceManager.h"
#include "MenuSystem.h"
#include "DisplayHelper.h"

#ifdef _WIN32
#include <windows.h>
#endif

void initConsole() {
#ifdef _WIN32
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD dwMode = 0;
    GetConsoleMode(hOut, &dwMode);
    dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    SetConsoleMode(hOut, dwMode);
#endif
    std::locale::global(std::locale(""));
}

void showWelcome() {
    DisplayHelper::clearScreen();
    std::cout << std::endl;
    std::cout << "  ╔════════════════════════════════════════════════════════╗" << std::endl;
    std::cout << "  ║                                                        ║" << std::endl;
    std::cout << "  ║            欢迎使用 家庭财务小管家 v1.0                 ║" << std::endl;
    std::cout << "  ║                                                        ║" << std::endl;
    std::cout << "  ║        轻松管理家庭收支，让财务一目了然！              ║" << std::endl;
    std::cout << "  ║                                                        ║" << std::endl;
    std::cout << "  ╚════════════════════════════════════════════════════════╝" << std::endl;
    std::cout << std::endl;
    std::cout << "  正在加载数据..." << std::endl;
}

int main() {
    initConsole();
    showWelcome();
    
    FinanceManager manager;
    
    if (!manager.initialize()) {
        DisplayHelper::printMessage("警告：数据加载失败，将使用空数据开始。", true);
    } else {
        DisplayHelper::printSuccess("数据加载完成！");
        std::cout << "  - 收入记录: " << manager.getIncomeCount() << " 条" << std::endl;
        std::cout << "  - 支出记录: " << manager.getExpenseCount() << " 条" << std::endl;
    }
    
    std::cout << std::endl << "  按回车键进入系统...";
    std::cin.get();
    
    MenuSystem menu(manager);
    menu.run();
    
    return 0;
}
