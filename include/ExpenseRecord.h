#ifndef EXPENSE_RECORD_H
#define EXPENSE_RECORD_H

#include "Record.h"

/**
 * @brief 支出记录类，继承自Record基类
 */
class ExpenseRecord : public Record {
private:
    std::string payee;  // 支出对象（如：超市、餐厅、水电费）

public:
    // 构造函数
    ExpenseRecord();
    ExpenseRecord(int id, const std::string& date, double amount,
                  const std::string& category, const std::string& payee,
                  const std::string& description);

    // Getter/Setter
    std::string getPayee() const;
    void setPayee(const std::string& payee);

    // 实现基类纯虚函数
    std::string toCSV() const override;
    bool fromCSV(const std::string& line) override;
    void display() const override;
    std::string getTypeName() const override;

    // 比较运算符（用于测试）
    bool operator==(const ExpenseRecord& other) const;
};

#endif // EXPENSE_RECORD_H
