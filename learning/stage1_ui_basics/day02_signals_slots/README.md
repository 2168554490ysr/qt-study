# Day 02: 信号与槽机制 (Signals & Slots)

## 学习目标
- [ ] 理解信号与槽的概念和作用
- [ ] 掌握connect函数的5种连接方式
- [ ] 学会使用Lambda表达式
- [ ] 理解信号与槽的参数传递
- [ ] 实现一个信号连接多个槽

## 实践任务
1. [ ] 创建Day02项目
2. [ ] 理解信号与槽的基本概念
3. [ ] 使用Lambda表达式连接信号和槽
4. [ ] 实现点击按钮改变标签文字
5. [ ] 实现点击按钮清空输入框
6. [ ] 实现点击按钮关闭窗口
7. [ ] 实现一个信号连接多个槽

---

## 核心概念

### 什么是信号与槽？

**信号(Signal)**：某个事件发生时发出的通知
**槽(Slot)**：接收信号并执行的函数
**连接(Connect)**：将信号和槽关联起来

**类比**：
- 信号 = "有人按门铃了"
- 槽 = "去开门"
- 连接 = "把门铃和开门动作绑定"

---

## 5种连接方式

### 1. Qt4语法（不推荐）
```cpp
connect(sender, SIGNAL(signal()), receiver, SLOT(slot()));
```
缺点：编译期不检查，运行时才报错

### 2. Qt5语法（推荐）
```cpp
connect(sender, &Sender::signal, receiver, &Receiver::slot);
```
优点：编译期检查类型是否匹配

### 3. Lambda表达式（最灵活）⭐
```cpp
connect(sender, &Sender::signal, [=]() {
    // 直接写代码，无需定义槽函数
});
```

### 4. 连接信号到信号（转发）
```cpp
connect(sender, &Sender::signal1, forwarder, &Forwarder::signal2);
```

### 5. 连接内置信号到内置槽
```cpp
connect(button, &QPushButton::clicked, &window, &QWidget::close);
```

---

## 代码逐行解说

### 包含头文件
```cpp
#include <QApplication>
#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>    // 垂直布局
#include <QDebug>
#include <QLineEdit>      // 输入框
#include <QLabel>         // 标签
```

### 创建布局
```cpp
// 创建垂直布局
QVBoxLayout *layout = new QVBoxLayout(&window);
```
**QVBoxLayout**：垂直排列控件的布局管理器

### 创建控件
```cpp
QLabel *label = new QLabel("等待操作...", &window);
QLineEdit *lineEdit = new QLineEdit(&window);
QPushButton *btn1 = new QPushButton("改变标签文字", &window);
```

### 信号与槽连接详解

#### 【示例1】Lambda表达式 - 改变标签文字
```cpp
QObject::connect(btn1, &QPushButton::clicked, [&]() {
    QString text = lineEdit->text();
    if (text.isEmpty()) {
        label->setText("请输入内容！");
    } else {
        label->setText("你输入了: " + text);
    }
    qDebug() << "按钮1被点击，输入内容:" << text;
});
```

**解析**：
- `btn1`：发送者（按钮）
- `&QPushButton::clicked`：信号（点击事件）
- `[&]`：Lambda捕获列表，`&`表示捕获所有变量的引用
- `()`：参数列表，clicked()无参数
- `{}`：槽函数的实现代码

#### 【示例2】Lambda表达式 - 清空输入框
```cpp
QObject::connect(btn2, &QPushButton::clicked, [&]() {
    lineEdit->clear();
    label->setText("输入框已清空");
    qDebug() << "按钮2被点击，清空输入框";
});
```

#### 【示例3】内置信号连接内置槽 - 关闭窗口
```cpp
QObject::connect(btn3, &QPushButton::clicked, &window, &QWidget::close);
```

**解析**：
- 不需要Lambda，直接连接Qt提供的槽函数
- `&QWidget::close`：关闭窗口的槽函数

#### 【示例4】一个信号连接多个槽
```cpp
// 第一个槽：更新标签
QObject::connect(lineEdit, &QLineEdit::textChanged, [&](const QString &text) {
    label->setText("正在输入: " + text);
});

// 第二个槽：输出调试信息
QObject::connect(lineEdit, &QLineEdit::textChanged, [](const QString &text) {
    qDebug() << "文字改变:" << text;
});
```

**解析**：
- `textChanged(const QString &text)`：带参数的信号
- 两个槽都接收同一个信号
- 执行顺序：按连接顺序依次执行

---

## Lambda表达式详解

### 基本语法
```cpp
[捕获列表](参数列表) -> 返回类型 {
    函数体
}
```

### 捕获列表
| 写法 | 含义 |
|------|------|
| `[]` | 不捕获任何变量 |
| `[=]` | 按值捕获所有变量 |
| `[&]` | 按引用捕获所有变量 |
| `[this]` | 捕获当前对象指针 |
| `[=, &var]` | 按值捕获所有，但var按引用 |

**推荐**：在connect中使用 `[&]` 按引用捕获

---

## 编译运行

```bash
cd /home/ysr/LinuxDeviceManager/learning/stage1_ui_basics/day02_signals_slots
qmake
make
./day02_signals_slots
```

---

## 操作演示

1. **在输入框输入文字** → 标签实时显示"正在输入: xxx"
2. **点击"改变标签文字"** → 标签显示"你输入了: xxx"
3. **点击"清空输入框"** → 输入框清空，标签显示"输入框已清空"
4. **点击"关闭窗口"** → 窗口关闭，程序退出

---

## 扩展练习

1. **添加新按钮**：点击后改变窗口标题
   ```cpp
   QPushButton *btn4 = new QPushButton("改变标题", &window);
   connect(btn4, &QPushButton::clicked, [&]() {
       window.setWindowTitle("新标题");
   });
   ```

2. **添加计数器**：每点击一次按钮，计数+1
   ```cpp
   int count = 0;
   connect(btn, &QPushButton::clicked, [&]() {
       count++;
       label->setText(QString("点击次数: %1").arg(count));
   });
   ```

3. **连接输入框回车信号**：
   ```cpp
   connect(lineEdit, &QLineEdit::returnPressed, [&]() {
       qDebug() << "回车被按下";
   });
   ```

---

## 遇到的问题
-

## 学习心得

## 运行截图
（完成后贴图）
