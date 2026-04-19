# Day 04: 布局管理(Layout)

## 学习目标
- [x] 掌握 QHBoxLayout 水平布局
- [x] 掌握 QVBoxLayout 垂直布局
- [x] 掌握 QGridLayout 网格布局
- [x] 理解布局嵌套（组合多种布局）
- [x] 掌握拉伸因子(stretch)控制控件比例
- [x] 了解布局边距和间距设置

## 实践任务
1. [x] 创建水平布局示例（3个按钮横向排列）
2. [x] 创建垂直布局示例（3个按钮纵向排列）
3. [x] 创建网格布局示例（表单布局：标签+输入框）
4. [x] 实现布局嵌套（水平布局内嵌垂直布局）
5. [x] 使用拉伸因子控制控件比例
6. [x] 设置布局边距和间距

---

## 关键概念

### 1. 水平布局 (QHBoxLayout)
控件从左到右水平排列。

```cpp
QHBoxLayout *layout = new QHBoxLayout();
layout->addWidget(widget1);
layout->addWidget(widget2);
layout->addWidget(widget3);
```

### 2. 垂直布局 (QVBoxLayout)
控件从上到下垂直排列。

```cpp
QVBoxLayout *layout = new QVBoxLayout();
layout->addWidget(widget1);
layout->addWidget(widget2);
```

### 3. 网格布局 (QGridLayout)
控件按行和列排列，像表格一样。

```cpp
QGridLayout *layout = new QGridLayout();
layout->addWidget(widget, row, column);      // 添加到指定行列
layout->addWidget(widget, row, column, rowSpan, colSpan);  // 跨越多行多列
```

### 4. 拉伸因子 (Stretch Factor)
控制控件在布局中占据的空间比例。

```cpp
// 方法1：添加时指定
layout->addWidget(widget, stretch);

// 方法2：单独设置
layout->setStretch(index, stretch);
layout->setRowStretch(row, stretch);      // 网格布局行拉伸
layout->setColumnStretch(col, stretch);   // 网格布局列拉伸
```

### 5. 布局嵌套
将一个布局添加到另一个布局中，实现复杂界面。

```cpp
QVBoxLayout *mainLayout = new QVBoxLayout();
QHBoxLayout *subLayout = new QHBoxLayout();

mainLayout->addLayout(subLayout);  // 嵌套子布局
```

### 6. 弹性空间 (Stretch)
使用 `addStretch()` 添加可伸缩的空白空间，将控件推到一侧。

```cpp
layout->addWidget(button1);
layout->addStretch();  // 弹性空间，将按钮推到左边
layout->addWidget(button2);
```

### 7. 边距和间距
```cpp
// 设置内容边距（左, 上, 右, 下）
layout->setContentsMargins(left, top, right, bottom);

// 设置控件间距
layout->setSpacing(pixels);
```

---

## 代码逐行解说

### 主窗口设置
```cpp
QWidget window;
window.setWindowTitle("Day 04: 布局管理(Layout)");
window.setLayout(mainLayout);  // 设置主布局
```

### 网格布局详解
```cpp
QGridLayout *grid = new QGridLayout();

// 参数说明：控件, 行号, 列号
grid->addWidget(nameLabel, 0, 0);   // 第0行第0列
grid->addWidget(nameEdit, 0, 1);    // 第0行第1列

// 设置列的拉伸比例
grid->setColumnStretch(0, 1);  // 第0列占1份
grid->setColumnStretch(1, 3);  // 第1列占3份
```

### 布局嵌套示例
```cpp
// 外层垂直布局
QVBoxLayout *outer = new QVBoxLayout();

// 内层水平布局
QHBoxLayout *inner = new QHBoxLayout();
inner->addWidget(new QPushButton("左"));
inner->addWidget(new QPushButton("右"));

// 将内层添加到外层
outer->addLayout(inner);
```

---

## Q&A 常见问题

### Q1: 什么时候用水平布局，什么时候用垂直布局？
**A:** 
- 按钮组横向排列 → QHBoxLayout
- 表单字段纵向排列 → QVBoxLayout
- 复杂界面通常需要两者嵌套使用

### Q2: 网格布局和普通布局有什么区别？
**A:** 网格布局更适合表单类界面，可以精确控制每个控件的位置（行列）。普通布局（水平/垂直）更简单，控件自动排列。

### Q3: 拉伸因子有什么作用？
**A:** 当窗口大小改变时，控制各个控件占据的空间比例。例如拉伸因子为1:2:3，则三个控件分别占据1/6、2/6、3/6的空间。

### Q4: addStretch() 是做什么的？
**A:** 添加一个可伸缩的空白区域，常用于将按钮推到窗口边缘。例如：按钮 + Stretch + 按钮，会将第一个按钮推到左边，第二个推到右边。

### Q5: 如何设置控件之间的间距？
**A:** 
```cpp
layout->setSpacing(10);  // 所有控件间距10像素
// 或
layout->setContentsMargins(10, 10, 10, 10);  // 边距
```

### Q6: 一个窗口可以有多个布局吗？
**A:** 一个窗口只能有一个主布局（通过 setLayout 设置），但可以通过布局嵌套实现复杂的界面结构。

### Q7: QGroupBox 是什么？
**A:** 带标题的框形容器，可以将相关控件分组显示，让界面更有组织性。

### Q8: 行拉伸的函数是什么？
**A:** 行拉伸使用 `setRowStretch()` 函数：
```cpp
gridLayout->setRowStretch(行号, 拉伸因子);
```
示例：
```cpp
// 第0行占1份，第1行占3份
gridLayout->setRowStretch(0, 1);
gridLayout->setRowStretch(1, 3);
```
当窗口**变高**时，第1行会获得更多垂直空间。

### Q9: setColumnStretch 和 setRowStretch 有什么区别？
**A:** 
| 函数 | 方向 | 作用 |
|------|------|------|
| `setColumnStretch(col, stretch)` | 水平方向 | 控制列宽比例 |
| `setRowStretch(row, stretch)` | 垂直方向 | 控制行高比例 |

---

## 运行截图

（待学习者运行后补充）

---

## 学习心得

（学习者填写）
