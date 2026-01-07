#ifndef INCOME_RECORD_H
#define INCOME_RECORD_H

#include "Record.h"

/**
 * @brief 收入记录类，继承自Record基类
 */
class IncomeRecord : public Record {
private:
    std::string source;  // 收入来源（如：工资、奖金、投资）

public:
    // 构造函数
    IncomeRecord();
    IncomeRecord(int id, const std::string& date, double amount,
                 const std::string& category, const std::string& source,
                 const std::string& description);

    // Getter/Setter
    std::string getSource() const;
    void setSource(const std::string& source);

    // 实现基类纯虚函数
    std::string toCSV() const override;
    bool fromCSV(const std::string& line) override;
    void display() const override;
    std::string getTypeName() const override;

    // 比较运算符（用于测试）
    bool operator==(const IncomeRecord& other) const;
};

#endif // INCOME_RECORD_H
