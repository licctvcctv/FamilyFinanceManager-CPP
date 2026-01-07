#include "RecordStorage.h"
#include <fstream>
#include <sstream>

#ifdef _WIN32
#include <direct.h>
#define MKDIR(dir) _mkdir(dir)
#else
#include <sys/stat.h>
#define MKDIR(dir) mkdir(dir, 0755)
#endif

RecordStorage::RecordStorage(const std::string& incomeFile, const std::string& expenseFile)
    : incomeFilePath(incomeFile), expenseFilePath(expenseFile), nextIncomeId(1), nextExpenseId(1) {
    ensureDataDirectory();
}

bool RecordStorage::ensureDataDirectory() const {
    size_t pos = incomeFilePath.find_last_of("/\\");
    if (pos != std::string::npos) {
        std::string dir = incomeFilePath.substr(0, pos);
        MKDIR(dir.c_str());
    }
    return true;
}

std::string RecordStorage::escapeCSV(const std::string& field) const {
    bool needsQuotes = false;
    std::string result;
    for (char c : field) {
        if (c == '"') { result += "\"\""; needsQuotes = true; }
        else if (c == ',' || c == '\n' || c == '\r') { result += c; needsQuotes = true; }
        else { result += c; }
    }
    return needsQuotes ? "\"" + result + "\"" : result;
}

std::string RecordStorage::unescapeCSV(const std::string& field) const {
    if (field.empty()) return field;
    std::string result = field;
    if (result.length() >= 2 && result.front() == '"' && result.back() == '"') {
        result = result.substr(1, result.length() - 2);
    }
    std::string unescaped;
    for (size_t i = 0; i < result.length(); ++i) {
        if (result[i] == '"' && i + 1 < result.length() && result[i + 1] == '"') {
            unescaped += '"'; ++i;
        } else { unescaped += result[i]; }
    }
    return unescaped;
}

std::vector<std::string> RecordStorage::splitCSV(const std::string& line) const {
    std::vector<std::string> fields;
    std::string field;
    bool inQuotes = false;
    for (size_t i = 0; i < line.length(); ++i) {
        char c = line[i];
        if (c == '"') {
            if (inQuotes && i + 1 < line.length() && line[i + 1] == '"') { field += '"'; ++i; }
            else { inQuotes = !inQuotes; field += c; }
        } else if (c == ',' && !inQuotes) { fields.push_back(field); field.clear(); }
        else { field += c; }
    }
    fields.push_back(field);
    return fields;
}

std::vector<IncomeRecord> RecordStorage::loadIncomeRecords() {
    std::vector<IncomeRecord> records;
    std::ifstream file(incomeFilePath);
    if (!file.is_open()) return records;
    
    std::string line;
    bool isFirstLine = true;
    int maxId = 0;
    
    while (std::getline(file, line)) {
        if (line.empty()) continue;
        if (isFirstLine) { isFirstLine = false; if (line.find("id,") == 0) continue; }
        IncomeRecord record;
        if (record.fromCSV(line)) {
            records.push_back(record);
            if (record.getId() > maxId) maxId = record.getId();
        }
    }
    file.close();
    nextIncomeId = maxId + 1;
    return records;
}

bool RecordStorage::saveIncomeRecords(const std::vector<IncomeRecord>& records) {
    ensureDataDirectory();
    std::ofstream file(incomeFilePath);
    if (!file.is_open()) return false;
    file << "id,date,amount,category,source,description" << std::endl;
    for (const auto& record : records) { file << record.toCSV() << std::endl; }
    file.close();
    return true;
}

int RecordStorage::getNextIncomeId() { return nextIncomeId++; }

std::vector<ExpenseRecord> RecordStorage::loadExpenseRecords() {
    std::vector<ExpenseRecord> records;
    std::ifstream file(expenseFilePath);
    if (!file.is_open()) return records;
    
    std::string line;
    bool isFirstLine = true;
    int maxId = 0;
    
    while (std::getline(file, line)) {
        if (line.empty()) continue;
        if (isFirstLine) { isFirstLine = false; if (line.find("id,") == 0) continue; }
        ExpenseRecord record;
        if (record.fromCSV(line)) {
            records.push_back(record);
            if (record.getId() > maxId) maxId = record.getId();
        }
    }
    file.close();
    nextExpenseId = maxId + 1;
    return records;
}

bool RecordStorage::saveExpenseRecords(const std::vector<ExpenseRecord>& records) {
    ensureDataDirectory();
    std::ofstream file(expenseFilePath);
    if (!file.is_open()) return false;
    file << "id,date,amount,category,payee,description" << std::endl;
    for (const auto& record : records) { file << record.toCSV() << std::endl; }
    file.close();
    return true;
}

int RecordStorage::getNextExpenseId() { return nextExpenseId++; }
std::string RecordStorage::getIncomeFilePath() const { return incomeFilePath; }
std::string RecordStorage::getExpenseFilePath() const { return expenseFilePath; }
