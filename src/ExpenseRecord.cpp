#include "ExpenseRecord.h"
#include <sstream>
#include <iomanip>
#include <cmath>

// 默认构造函数
ExpenseRecord::ExpenseRecord() : Record(), payee("") {
}

// 带参数构造函数
ExpenseRecord::ExpenseRecord(int id, const std::string& date, double amount,
                             const std::string& category, const std::string& payee,
                             const std::string& description)
    : Record(id, date, amount, category, description), payee(payee) {
}

// Getter
std::string ExpenseRecord::getPayee() const {
    return payee;
}

// Setter
void ExpenseRecord::setPayee(const std::string& payee) {
    this->payee = payee;
}

// CSV字段转义辅助函数
static std::string escapeCSVField(const std::string& field) {
    bool needsQuotes = false;
    std::string result;
    
    for (char c : field) {
        if (c == '"') {
            result += "\"\"";
            needsQuotes = true;
        } else if (c == ',' || c == '\n' || c == '\r') {
            result += c;
            needsQuotes = true;
        } else {
            result += c;
        }
    }
    
    if (needsQuotes) {
        return "\"" + result + "\"";
    }
    return result;
}

// CSV字段反转义辅助函数
static std::string unescapeCSVField(const std::string& field) {
    if (field.empty()) return field;
    
    std::string result = field;
    
    // 去除首尾引号
    if (result.length() >= 2 && result.front() == '"' && result.back() == '"') {
        result = result.substr(1, result.length() - 2);
    }
    
    // 处理双引号转义
    std::string unescaped;
    for (size_t i = 0; i < result.length(); ++i) {
        if (result[i] == '"' && i + 1 < result.length() && result[i + 1] == '"') {
            unescaped += '"';
            ++i;
        } else {
            unescaped += result[i];
        }
    }
    
    return unescaped;
}

// 分割CSV行
static std::vector<std::string> splitCSVLine(const std::string& line) {
    std::vector<std::string> fields;
    std::string field;
    bool inQuotes = false;
    
    for (size_t i = 0; i < line.length(); ++i) {
        char c = line[i];
        
        if (c == '"') {
            if (inQuotes && i + 1 < line.length() && line[i + 1] == '"') {
                field += '"';
                ++i;
            } else {
                inQuotes = !inQuotes;
                field += c;
            }
        } else if (c == ',' && !inQuotes) {
            fields.push_back(field);
            field.clear();
        } else {
            field += c;
        }
    }
    fields.push_back(field);
    
    return fields;
}

// 序列化为CSV格式
std::string ExpenseRecord::toCSV() const {
    std::ostringstream oss;
    oss << id << ","
        << escapeCSVField(date) << ","
        << std::fixed << std::setprecision(2) << amount << ","
        << escapeCSVField(category) << ","
        << escapeCSVField(payee) << ","
        << escapeCSVField(description);
    return oss.str();
}

// 从CSV格式反序列化
bool ExpenseRecord::fromCSV(const std::string& line) {
    std::vector<std::string> fields = splitCSVLine(line);
    
    if (fields.size() < 6) {
        return false;
    }
    
    try {
        id = std::stoi(fields[0]);
        date = unescapeCSVField(fields[1]);
        amount = std::stod(fields[2]);
        category = unescapeCSVField(fields[3]);
        payee = unescapeCSVField(fields[4]);
        description = unescapeCSVField(fields[5]);
        return true;
    } catch (...) {
        return false;
    }
}

// 显示记录
void ExpenseRecord::display() const {
    std::cout << "┌────────────────────────────────────────┐" << std::endl;
    std::cout << "│           支出记录详情                 │" << std::endl;
    std::cout << "├────────────────────────────────────────┤" << std::endl;
    std::cout << "│ ID:       " << std::setw(28) << std::left << id << "│" << std::endl;
    std::cout << "│ 日期:     " << std::setw(28) << std::left << date << "│" << std::endl;
    std::cout << "│ 金额:     " << std::setw(28) << std::left 
              << std::fixed << std::setprecision(2) << amount << "│" << std::endl;
    std::cout << "│ 分类:     " << std::setw(28) << std::left << category << "│" << std::endl;
    std::cout << "│ 支付对象: " << std::setw(28) << std::left << payee << "│" << std::endl;
    std::cout << "│ 描述:     " << std::setw(28) << std::left << description << "│" << std::endl;
    std::cout << "└────────────────────────────────────────┘" << std::endl;
}

// 获取类型名称
std::string ExpenseRecord::getTypeName() const {
    return "支出";
}

// 比较运算符
bool ExpenseRecord::operator==(const ExpenseRecord& other) const {
    return id == other.id &&
           date == other.date &&
           std::abs(amount - other.amount) < 0.01 &&
           category == other.category &&
           payee == other.payee &&
           description == other.description;
}
