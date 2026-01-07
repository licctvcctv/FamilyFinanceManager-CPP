#ifndef RECORD_H
#define RECORD_H

#include <string>
#include <iostream>

/**
 * @brief 记录基类，定义收入和支出记录的公共属性和接口
 */
class Record {
protected:
    int id;                     // 记录唯一标识
    std::string date;           // 日期，格式: YYYY-MM-DD
    double amount;              // 金额
    std::string category;       // 分类
    std::string description;    // 描述

public:
    // 构造函数
    Record();
    Record(int id, const std::string& date, double amount,
           const std::string& category, const std::string& description);
    virtual ~Record() = default;

    // Getters
    int getId() const;
    std::string getDate() const;
    double getAmount() const;
    std::string getCategory() const;
    std::string getDescription() const;

    // Setters
    void setId(int id);
    void setDate(const std::string& date);
    void setAmount(double amount);
    void setCategory(const std::string& category);
    void setDescription(const std::string& description);

    // 纯虚函数 - 子类必须实现
    virtual std::string toCSV() const = 0;
    virtual bool fromCSV(const std::string& line) = 0;
    virtual void display() const = 0;
    virtual std::string getTypeName() const = 0;
};

#endif // RECORD_H
