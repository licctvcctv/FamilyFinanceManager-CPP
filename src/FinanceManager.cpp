#include "FinanceManager.h"
#include <algorithm>

FinanceManager::FinanceManager() : storage() {}
FinanceManager::FinanceManager(const std::string& incomeFile, const std::string& expenseFile) : storage(incomeFile, expenseFile) {}
FinanceManager::~FinanceManager() { saveAll(); }

bool FinanceManager::initialize() {
    incomeRecords = storage.loadIncomeRecords();
    expenseRecords = storage.loadExpenseRecords();
    return true;
}

bool FinanceManager::saveAll() {
    return storage.saveIncomeRecords(incomeRecords) && storage.saveExpenseRecords(expenseRecords);
}

IncomeRecord* FinanceManager::findIncomeById(int id) {
    for (auto& r : incomeRecords) if (r.getId() == id) return &r;
    return nullptr;
}

const IncomeRecord* FinanceManager::findIncomeById(int id) const {
    for (const auto& r : incomeRecords) if (r.getId() == id) return &r;
    return nullptr;
}

ExpenseRecord* FinanceManager::findExpenseById(int id) {
    for (auto& r : expenseRecords) if (r.getId() == id) return &r;
    return nullptr;
}

const ExpenseRecord* FinanceManager::findExpenseById(int id) const {
    for (const auto& r : expenseRecords) if (r.getId() == id) return &r;
    return nullptr;
}

bool FinanceManager::addIncome(const IncomeRecord& record) {
    incomeRecords.push_back(record);
    return saveAll();
}

bool FinanceManager::deleteIncome(int id) {
    auto it = std::find_if(incomeRecords.begin(), incomeRecords.end(), [id](const IncomeRecord& r) { return r.getId() == id; });
    if (it != incomeRecords.end()) { incomeRecords.erase(it); return saveAll(); }
    return false;
}

bool FinanceManager::modifyIncome(int id, const IncomeRecord& newData) {
    IncomeRecord* record = findIncomeById(id);
    if (!record) return false;
    if (!newData.getDate().empty()) record->setDate(newData.getDate());
    if (newData.getAmount() > 0) record->setAmount(newData.getAmount());
    if (!newData.getCategory().empty()) record->setCategory(newData.getCategory());
    if (!newData.getSource().empty()) record->setSource(newData.getSource());
    if (!newData.getDescription().empty()) record->setDescription(newData.getDescription());
    return saveAll();
}

IncomeRecord* FinanceManager::getIncomeById(int id) { return findIncomeById(id); }
const IncomeRecord* FinanceManager::getIncomeById(int id) const { return findIncomeById(id); }

std::vector<IncomeRecord> FinanceManager::queryIncomeByDateRange(const std::string& startDate, const std::string& endDate) const {
    std::vector<IncomeRecord> result;
    for (const auto& r : incomeRecords) {
        if (r.getDate() >= startDate && r.getDate() <= endDate) result.push_back(r);
    }
    std::sort(result.begin(), result.end(), [](const IncomeRecord& a, const IncomeRecord& b) { return a.getDate() < b.getDate(); });
    return result;
}

std::vector<IncomeRecord> FinanceManager::queryIncomeByCategory(const std::string& category) const {
    std::vector<IncomeRecord> result;
    for (const auto& r : incomeRecords) if (r.getCategory() == category) result.push_back(r);
    std::sort(result.begin(), result.end(), [](const IncomeRecord& a, const IncomeRecord& b) { return a.getDate() < b.getDate(); });
    return result;
}

std::vector<IncomeRecord> FinanceManager::getAllIncome() const {
    std::vector<IncomeRecord> result = incomeRecords;
    std::sort(result.begin(), result.end(), [](const IncomeRecord& a, const IncomeRecord& b) { return a.getDate() < b.getDate(); });
    return result;
}

int FinanceManager::getIncomeCount() const { return static_cast<int>(incomeRecords.size()); }

bool FinanceManager::addExpense(const ExpenseRecord& record) {
    expenseRecords.push_back(record);
    return saveAll();
}

bool FinanceManager::deleteExpense(int id) {
    auto it = std::find_if(expenseRecords.begin(), expenseRecords.end(), [id](const ExpenseRecord& r) { return r.getId() == id; });
    if (it != expenseRecords.end()) { expenseRecords.erase(it); return saveAll(); }
    return false;
}

bool FinanceManager::modifyExpense(int id, const ExpenseRecord& newData) {
    ExpenseRecord* record = findExpenseById(id);
    if (!record) return false;
    if (!newData.getDate().empty()) record->setDate(newData.getDate());
    if (newData.getAmount() > 0) record->setAmount(newData.getAmount());
    if (!newData.getCategory().empty()) record->setCategory(newData.getCategory());
    if (!newData.getPayee().empty()) record->setPayee(newData.getPayee());
    if (!newData.getDescription().empty()) record->setDescription(newData.getDescription());
    return saveAll();
}

ExpenseRecord* FinanceManager::getExpenseById(int id) { return findExpenseById(id); }
const ExpenseRecord* FinanceManager::getExpenseById(int id) const { return findExpenseById(id); }

std::vector<ExpenseRecord> FinanceManager::queryExpenseByDateRange(const std::string& startDate, const std::string& endDate) const {
    std::vector<ExpenseRecord> result;
    for (const auto& r : expenseRecords) {
        if (r.getDate() >= startDate && r.getDate() <= endDate) result.push_back(r);
    }
    std::sort(result.begin(), result.end(), [](const ExpenseRecord& a, const ExpenseRecord& b) { return a.getDate() < b.getDate(); });
    return result;
}

std::vector<ExpenseRecord> FinanceManager::queryExpenseByCategory(const std::string& category) const {
    std::vector<ExpenseRecord> result;
    for (const auto& r : expenseRecords) if (r.getCategory() == category) result.push_back(r);
    std::sort(result.begin(), result.end(), [](const ExpenseRecord& a, const ExpenseRecord& b) { return a.getDate() < b.getDate(); });
    return result;
}

std::vector<ExpenseRecord> FinanceManager::getAllExpense() const {
    std::vector<ExpenseRecord> result = expenseRecords;
    std::sort(result.begin(), result.end(), [](const ExpenseRecord& a, const ExpenseRecord& b) { return a.getDate() < b.getDate(); });
    return result;
}

int FinanceManager::getExpenseCount() const { return static_cast<int>(expenseRecords.size()); }

double FinanceManager::getTotalIncome() const {
    double total = 0.0;
    for (const auto& r : incomeRecords) total += r.getAmount();
    return total;
}

double FinanceManager::getTotalExpense() const {
    double total = 0.0;
    for (const auto& r : expenseRecords) total += r.getAmount();
    return total;
}

double FinanceManager::getNetBalance() const { return getTotalIncome() - getTotalExpense(); }
int FinanceManager::getNextIncomeId() { return storage.getNextIncomeId(); }
int FinanceManager::getNextExpenseId() { return storage.getNextExpenseId(); }
