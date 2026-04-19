# Day 03: 常用控件 (Common Widgets)

## 学习目标
- [ ] 掌握常用控件的基本用法
- [ ] 理解控件的信号与槽
- [ ] 学会使用水平布局和表单布局
- [ ] 实现用户注册表单

## 实践任务
1. [ ] 创建Day03项目
2. [ ] 学习QLineEdit的多种模式
3. [ ] 学习QCheckBox和QRadioButton
4. [ ] 学习QComboBox下拉框
5. [ ] 学习QSlider和QProgressBar
6. [ ] 学习QTextEdit多行文本
7. [ ] 学习QFormLayout表单布局
8. [ ] 实现完整的用户注册表单

---

## 控件速查表

| 控件类 | 用途 | 常用方法 | 常用信号 |
|--------|------|----------|----------|
| `QLineEdit` | 单行输入 | `text()`, `setText()`, `clear()`, `setPlaceholderText()`, `setEchoMode()` | `textChanged()`, `returnPressed()` |
| `QCheckBox` | 复选框 | `isChecked()`, `setChecked()` | `stateChanged()` |
| `QRadioButton` | 单选按钮 | `isChecked()`, `setChecked()` | `toggled()` |
| `QComboBox` | 下拉框 | `addItem()`, `currentText()`, `currentIndex()`, `setCurrentIndex()` | `currentIndexChanged()` |
| `QSlider` | 滑动条 | `setRange()`, `setValue()`, `value()` | `valueChanged()` |
| `QProgressBar` | 进度条 | `setRange()`, `setValue()` | - |
| `QTextEdit` | 多行文本 | `toPlainText()`, `setPlainText()`, `clear()` | `textChanged()` |
| `QGroupBox` | 分组框 | `setTitle()`, `setLayout()` | - |

---

## 布局管理

### 三种常用布局

| 布局类 | 排列方式 | 适用场景 |
|--------|----------|----------|
| `QVBoxLayout` | 垂直排列 | 纵向排列控件 |
| `QHBoxLayout` | 水平排列 | 横向排列控件 |
| `QFormLayout` | 表单样式（标签+输入） | 登录/注册表单 |

### 布局嵌套
```
QVBoxLayout (主布局)
    ├── QLabel (标题)
    ├── QFormLayout (表单)
    │       ├── 用户名: QLineEdit
    │       └── 密码: QLineEdit
    ├── QGroupBox (性别)
    │       └── QHBoxLayout
    │               ├── QRadioButton (男)
    │               └── QRadioButton (女)
    └── QHBoxLayout (按钮)
            ├── QPushButton (提交)
            └── QPushButton (重置)
```

---

## 代码逐行解说

### 1. 表单布局 (QFormLayout)
```cpp
QFormLayout *formLayout = new QFormLayout();

QLineEdit *usernameEdit = new QLineEdit();
usernameEdit->setPlaceholderText("请输入用户名");
formLayout->addRow("用户名:", usernameEdit);
```
**效果**：自动对齐标签和输入框
```
用户名: [__________]
密码:   [__________]
```

---

### 2. 密码输入模式
```cpp
QLineEdit *passwordEdit = new QLineEdit();
passwordEdit->setEchoMode(QLineEdit::Password);  // 显示为***
```

**EchoMode模式**：
| 模式 | 效果 |
|------|------|
| `Normal` | 正常显示（默认） |
| `Password` | 显示为*号 |
| `PasswordEchoOnEdit` | 输入时显示，离开后显示* |
| `NoEcho` | 完全不显示 |

---

### 3. 单选按钮分组 (QButtonGroup)
```cpp
QRadioButton *maleRadio = new QRadioButton("男");
QRadioButton *femaleRadio = new QRadioButton("女");
maleRadio->setChecked(true);  // 默认选中
```

**特点**：
- 同一父窗口的单选按钮自动互斥
- `setChecked(true)` 设置默认选中
- `isChecked()` 判断是否选中

---

### 4. 复选框 (QCheckBox)
```cpp
QCheckBox *swimCheck = new QCheckBox("游泳");
if (swimCheck->isChecked()) {
    // 选中了游泳
}
```

**特点**：
- 可以多选
- `isChecked()` 返回bool
- `stateChanged` 信号在状态改变时触发

---

### 5. 下拉框 (QComboBox)
```cpp
QComboBox *cityCombo = new QComboBox();
cityCombo->addItem("北京");
cityCombo->addItem("上海");
cityCombo->setCurrentIndex(1);  // 默认选中第2项（上海）

QString city = cityCombo->currentText();  // 获取选中的文字
```

---

### 6. 滑动条与进度条联动
```cpp
QSlider *ageSlider = new QSlider(Qt::Horizontal);
ageSlider->setRange(18, 60);  // 范围
ageSlider->setValue(25);      // 当前值

QProgressBar *progressBar = new QProgressBar();
progressBar->setValue(0);

// 连接信号
connect(ageSlider, &QSlider::valueChanged, [&](int value) {
    ageValueLabel->setText(QString::number(value));
});
```

---

### 7. 多行文本 (QTextEdit)
```cpp
QTextEdit *introEdit = new QTextEdit();
introEdit->setPlaceholderText("请简单介绍你自己...");
introEdit->toPlainText();  // 获取文本
```

---

### 8. 一个槽函数连接多个信号
```cpp
auto updateProgress = [&]() {
    int progress = 0;
    if (!usernameEdit->text().isEmpty()) progress += 20;
    if (!passwordEdit->text().isEmpty()) progress += 20;
    // ...
    progressBar->setValue(progress);
};

// 多个控件连接同一个槽
connect(usernameEdit, &QLineEdit::textChanged, updateProgress);
connect(passwordEdit, &QLineEdit::textChanged, updateProgress);
connect(swimCheck, &QCheckBox::stateChanged, updateProgress);
```

---

## 编译运行

```bash
cd /home/ysr/LinuxDeviceManager/learning/stage1_ui_basics/day03_widgets
qmake
make
./day03_widgets
```

---

## 操作演示

1. **输入用户名和密码** → 进度条增加
2. **选择性别** → 单选按钮互斥
3. **选择爱好** → 可多选，进度条增加
4. **选择城市** → 下拉框选择
5. **拖动年龄滑块** → 数值实时显示
6. **填写自我介绍** → 多行文本，进度条增加
7. **点击提交** → 控制台输出注册信息
8. **点击重置** → 清空所有输入
9. **点击关闭** → 退出程序

---

## 扩展练习

1. **添加邮箱验证**：
   ```cpp
   if (!email.contains("@")) {
       statusLabel->setText("邮箱格式不正确！");
   }
   ```

2. **添加密码强度显示**：
   ```cpp
   connect(passwordEdit, &QLineEdit::textChanged, [&](const QString &text) {
       int strength = text.length() * 10;
       strengthBar->setValue(qMin(strength, 100));
   });
   ```

3. **添加确认对话框**：
   ```cpp
   QMessageBox::StandardButton reply;
   reply = QMessageBox::question(&window, "确认", "确定要提交吗？");
   if (reply == QMessageBox::Yes) {
       // 提交
   }
   ```

---

## 常见问题解答 (Q&A)

### Q1: QFormLayout和QVBoxLayout有什么区别？

**A**: 
- `QVBoxLayout`：简单垂直排列
- `QFormLayout`：两列布局，适合表单（标签+输入框自动对齐）

```cpp
// QFormLayout会自动对齐
用户名: [__________]
密码:   [__________]  ← 输入框左对齐

// QVBoxLayout需要手动控制
```

---

### Q2: 为什么单选按钮会自动互斥？

**A**: 同一父窗口的`QRadioButton`自动形成互斥组。

如果需要多组单选按钮，使用`QButtonGroup`：
```cpp
QButtonGroup *group1 = new QButtonGroup(&window);
group1->addButton(maleRadio);
group1->addButton(femaleRadio);
```

---

### Q3: `addStretch()` 是做什么的？

**A**: 添加弹性空间，将控件推到一边。

```cpp
QHBoxLayout *layout = new QHBoxLayout();
layout->addWidget(btn1);
layout->addStretch();  // 弹性空间
layout->addWidget(btn2);
// 效果：btn1在左，btn2在右
```

---

### Q4: 如何获取多行文本的内容？

**A**: 使用`toPlainText()`：
```cpp
QTextEdit *edit = new QTextEdit();
QString text = edit->toPlainText();  // 获取纯文本
```

注意：不是`text()`，QTextEdit使用`toPlainText()`。

---

### Q5: 进度条如何显示百分比？

**A**: 默认自动显示百分比。
```cpp
QProgressBar *bar = new QProgressBar();
bar->setValue(40);  // 自动显示 "40%"
```

可以设置格式：
```cpp
bar->setFormat("进度: %p%");  // %p表示百分比
```

---

## 遇到的问题
-

## 学习心得

## 运行截图
（完成后贴图）
