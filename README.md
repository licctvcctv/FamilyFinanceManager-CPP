# 家庭财务小管家

一个基于命令行的 C++ 家庭财务管理系统，用于管理家庭收入和支出记录。

## 功能特性

### 收入管理
- 添加收入记录（日期、金额、分类、来源、描述）
- 查询收入记录（按日期范围、按分类、全部）
- 修改收入记录
- 删除收入记录
- 打印收入报表（全部、按月、按分类）

### 支出管理
- 添加支出记录（日期、金额、分类、支付对象、描述）
- 查询支出记录（按日期范围、按分类、全部）
- 修改支出记录
- 删除支出记录
- 打印支出报表（全部、按月、按分类）

### 统计报表
- 月度收支汇总
- 分类统计（收入/支出占比）
- 财务总览（总收入、总支出、净余额、月均值）

### 数据持久化
- 自动保存到 CSV 文件
- 程序启动时自动加载数据
- 支持中文字符

## 编译运行

### Visual Studio 2022
1. 双击 `FamilyFinanceManager.sln` 打开解决方案
2. 选择 Debug 或 Release 配置
3. 按 F5 编译并运行

### CMake
```bash
mkdir build
cd build
cmake ..
cmake --build .
./bin/FamilyFinanceManager
```

## 项目结构

```
FamilyFinanceManager/
├── include/                 # 头文件
│   ├── Record.h            # 记录基类
│   ├── IncomeRecord.h      # 收入记录类
│   ├── ExpenseRecord.h     # 支出记录类
│   ├── InputHelper.h       # 输入辅助类
│   ├── DisplayHelper.h     # 显示辅助类
│   ├── RecordStorage.h     # 数据存储类
│   ├── FinanceManager.h    # 财务管理类
│   ├── ReportGenerator.h   # 报表生成类
│   └── MenuSystem.h        # 菜单系统类
├── src/                     # 源文件
│   ├── main.cpp            # 主程序入口
│   └── ...
├── data/                    # 数据文件目录
│   ├── income.csv          # 收入数据
│   └── expense.csv         # 支出数据
├── tests/                   # 测试文件
│   └── test_main.cpp       # 单元测试和属性测试
├── FamilyFinanceManager.sln     # VS2022 解决方案
├── FamilyFinanceManager.vcxproj # VS2022 项目文件
├── CMakeLists.txt          # CMake 配置
└── README.md               # 说明文档
```

## 预定义分类

### 收入分类
- 工资、奖金、投资收益、兼职收入、礼金、其他

### 支出分类
- 餐饮、住房、交通、购物、娱乐、医疗、教育、水电费、通讯费、其他

## 技术栈

- 语言：C++14
- 开发环境：Visual Studio 2022
- 数据存储：CSV 文本文件
- 界面：命令行界面 (CLI)

## 代码统计

- 总代码行数：3800+ 行
- 头文件：9 个
- 源文件：10 个
- 测试用例：20 个（单元测试 + 属性测试）

## 作者

高级语言程序设计课程大作业

## 许可证

MIT License
