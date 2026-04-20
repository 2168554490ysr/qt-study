# Day 06: 自定义控件 (Custom Widget)

## 学习目标
- [x] 学习继承 QWidget 创建自定义控件
- [x] 理解自定义信号的定义和使用
- [x] 理解自定义槽的定义和使用
- [x] 掌握控件的组合（在一个控件中包含其他控件）
- [x] 学习重写 paintEvent 绘制自定义外观
- [x] 学习重写鼠标/键盘事件
- [x] 理解 Q_OBJECT 宏的作用

---

## 实践任务
1. [x] 创建自定义控件类 CounterWidget
2. [x] 定义自定义信号（valueChanged、maximumReached、minimumReached）
3. [x] 定义自定义槽（increment、decrement、reset）
4. [x] 组合 QLabel、QPushButton、QSlider 创建复合控件
5. [x] 重写 paintEvent 绘制背景和进度条
6. [x] 重写 mousePressEvent 实现点击增加功能
7. [x] 在主程序中使用自定义控件

---

## 关键概念

### 1. 继承 QWidget 创建自定义控件

```cpp
class CounterWidget : public QWidget
{
    Q_OBJECT  // 必须添加，用于支持信号槽

public:
    explicit CounterWidget(QWidget *parent = nullptr);
    ...
};
```

### 2. 自定义信号

```cpp
signals:
    void valueChanged(int newValue);  // 值改变信号
    void maximumReached();             // 达到最大值
    void minimumReached();             // 达到最小值
```

### 3. 自定义槽

```cpp
public slots:
    void increment();   // 增加
    void decrement();   // 减少
    void reset();       // 重置
```

### 4. 发出信号

```cpp
void CounterWidget::setValue(int value)
{
    if (m_value != value) {
        m_value = value;
        emit valueChanged(m_value);  // 发出信号
    }
}
```

### 5. 重写 paintEvent

```cpp
void CounterWidget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)
    
    QPainter painter(this);
    
    // 绘制背景
    painter.fillRect(rect(), QColor(240, 240, 240));
    
    // 绘制边框
    painter.setPen(QPen(Qt::darkGray, 2));
    painter.drawRect(rect().adjusted(1, 1, -1, -1));
}
```

### 6. 控件组合

```cpp
// 在自定义控件中包含其他控件
QLabel *m_valueLabel;
QPushButton *m_incButton;
QSlider *m_slider;

void CounterWidget::setupUI()
{
    m_valueLabel = new QLabel("0", this);
    m_incButton = new QPushButton("+", this);
    m_slider = new QSlider(Qt::Horizontal, this);
    
    // 布局
    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->addWidget(m_decButton);
    layout->addWidget(m_valueLabel);
    layout->addWidget(m_incButton);
}
```

---

## 代码结构

```
day06_customwidget/
├── day06_customwidget.pro    # 项目文件
├── counterwidget.h           # 自定义控件头文件
├── counterwidget.cpp         # 自定义控件实现
└── main.cpp                  # 主程序
```

---

## Q&A 常见问题

### Q1: Q_OBJECT 宏是做什么的？
**A:** Q_OBJECT 宏必须添加在类定义中，它启用了 Qt 的元对象系统（Meta-Object System），提供以下功能：
- 信号和槽机制
- 运行时类型信息
- 动态属性系统

如果没有这个宏，信号槽将无法使用。

### Q2: 自定义信号和槽有什么命名规范？
**A:** 
- 信号：通常使用动词的过去式或表示状态变化，如 `valueChanged()`, `clicked()`, `textChanged()`
- 槽：通常使用动词，表示动作，如 `increment()`, `decrement()`, `reset()`

### Q3: emit 关键字是必须的吗？
**A:** emit 是一个空宏，实际上可以省略，但建议保留以提高代码可读性：
```cpp
emit valueChanged(m_value);  // 推荐
valueChanged(m_value);        // 效果相同，但不直观
```

### Q4: 如何连接自定义信号槽？
**A:** 与 Qt 内置信号槽的连接方式相同：
```cpp
CounterWidget *counter = new CounterWidget();

// 连接自定义信号
connect(counter, &CounterWidget::valueChanged, 
    [&](int newValue) {
        qDebug() << "值改变:" << newValue;
    });

// 连接自定义槽
connect(button, &QPushButton::clicked, 
    counter, &CounterWidget::reset);
```

### Q5: 可以在自定义控件中包含其他控件吗？
**A:** 可以！这就是**控件组合**。CounterWidget 就组合了 QLabel、QPushButton 和 QSlider。

### Q6: paintEvent 什么时候被调用？
**A:** 以下情况会触发 paintEvent：
- 窗口首次显示
- 窗口大小改变
- 调用 update() 或 repaint()
- 窗口从被遮挡状态变为可见

### Q7: 如何强制重绘控件？
**A:** 
```cpp
update();     // 异步重绘，推荐
repaint();    // 立即重绘，可能阻塞
```

### Q8: 自定义控件可以设置样式表吗？
**A:** 可以！自定义控件完全支持 QSS 样式表：
```cpp
counter->setStyleSheet("background-color: yellow;");
```

### Q9: 如何发布自定义控件供其他人使用？
**A:** 
1. 创建独立的库项目（.pro 中使用 `TEMPLATE = lib`）
2. 导出头文件
3. 提供使用文档
4. 其他项目链接库文件即可使用

### Q10: 自定义控件的父控件参数有什么用？
**A:** 父控件参数用于：
- 内存管理：父控件销毁时自动销毁子控件
- 坐标系统：子控件的坐标是相对于父控件的
- 显示层次：子控件显示在父控件之上

```cpp
// 指定 this 为父控件
m_valueLabel = new QLabel("0", this);
```

### Q11: Makefile 是谁写的？
**A:** Makefile 不是手写的，而是 **qmake 自动生成的**！

构建流程：
```
.pro 项目文件 → qmake → Makefile → make → 可执行文件
```

你写的：`.pro` 文件（项目配置）  
qmake 生成：`Makefile`（编译规则）  
make 使用：`Makefile` 生成可执行文件

### Q12: `emit` 关键字是做什么的？
**A:** `emit` 是一个**空宏**，只是为了提高代码可读性，明确表示"这里发出信号"。

```cpp
// 这两行效果完全相同：
emit valueChanged(5);   // ✅ 推荐，明确表示发信号
valueChanged(5);        // 效果一样，但不直观
```

`emit` 的定义： `#define emit` （就是空的！）

### Q13: 如何使用自定义控件？
**A:** 和 Qt 内置控件用法**完全一样**！

```cpp
// 创建
CounterWidget *counter = new CounterWidget();

// 设置属性
counter->setRange(0, 20);
counter->setValue(10);

// 连接信号
connect(counter, &CounterWidget::valueChanged, callback);

// 添加到布局
layout->addWidget(counter);
```

### Q14: `new QVBoxLayout(widgetGroup)` 是什么意思？
**A:** 创建垂直布局并应用到 `widgetGroup` 控件。

等价写法：
```cpp
// 写法1（代码中的方式）
QVBoxLayout *layout = new QVBoxLayout(widgetGroup);

// 写法2（等价的）
QVBoxLayout *layout = new QVBoxLayout();
widgetGroup->setLayout(layout);
```

作用：让 `widgetGroup`（如 QGroupBox）使用这个布局管理内部子控件。

### Q15: 为什么要在控件内部 `connect`？
**A:** 这是**封装内部逻辑**，让控件自包含。

```cpp
// CounterWidget.cpp 内部连接
connect(m_incButton, &QPushButton::clicked, 
        this, &CounterWidget::increment);
```

好处：
- 外部使用者不需要知道内部按钮细节
- 控件开箱即用，无需额外配置
- 内部实现可以修改而不影响外部

---

## 运行截图

（待学习者运行后补充）

---

## 学习心得

（学习者填写）
