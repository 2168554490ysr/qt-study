# Day 07: QSS样式表

## 学习目标
- [x] 理解QSS基本语法（类似CSS）
- [x] 掌握控件样式设置（颜色、字体、边框）
- [x] 学习伪状态样式（hover、pressed、disabled）
- [x] 实现主题切换功能
- [x] 学习渐变效果和复杂样式

## 实践任务
1. [x] 创建QSS样式表示例项目
2. [x] 实现三种主题切换（浅色、深色、蓝色）
3. [x] 演示各种控件的QSS样式
4. [x] 学习伪状态选择器的使用

## 关键概念

### 1. QSS是什么？
QSS (Qt Style Sheets) 是Qt的样式表机制，类似于Web开发中的CSS，用于控制Qt应用程序的外观。

### 2. QSS基本语法
```css
/* 选择器 { 属性: 值; } */
QPushButton {
    background-color: #2196f3;
    color: white;
    border-radius: 6px;
}
```

### 3. 选择器类型
| 选择器 | 示例 | 说明 |
|--------|------|------|
| 类型选择器 | `QPushButton` | 选择所有QPushButton |
| ID选择器 | `QPushButton#primaryButton` | 选择特定对象名的按钮 |
| 类选择器 | `.QWidget` | 选择QWidget及其子类 |
| 后代选择器 | `QDialog QPushButton` | 选择QDialog中的按钮 |
| 子选择器 | `QDialog > QPushButton` | 选择QDialog的直接子按钮 |

### 4. 常用属性
```css
/* 颜色和背景 */
background-color: #2196f3;        /* 背景色 */
color: white;                      /* 文字颜色 */
border: 2px solid #ddd;           /* 边框 */
border-radius: 6px;               /* 圆角 */

/* 尺寸和间距 */
padding: 10px;                    /* 内边距 */
margin: 5px;                      /* 外边距 */
min-width: 100px;                 /* 最小宽度 */
min-height: 30px;                 /* 最小高度 */

/* 字体 */
font-family: "Microsoft YaHei";   /* 字体 */
font-size: 14px;                  /* 字号 */
font-weight: bold;                /* 粗细 */

/* 渐变背景 */
background: qlineargradient(x1:0, y1:0, x2:1, y2:0,
    stop:0 #3f51b5, stop:1 #9c27b0);
```

### 5. 伪状态（Pseudo-States）
```css
/* 鼠标悬停 */
QPushButton:hover {
    background-color: #1976d2;
}

/* 鼠标按下 */
QPushButton:pressed {
    background-color: #0d47a1;
}

/* 禁用状态 */
QPushButton:disabled {
    background-color: #bdbdbd;
    color: #757575;
}

/* 获得焦点 */
QLineEdit:focus {
    border-color: #2196f3;
}

/* 选中状态 */
QCheckBox:checked {
    color: #2196f3;
}
```

### 6. 子控件（Sub-Controls）
```css
/* 下拉框的箭头 */
QComboBox::drop-down {
    border: none;
    width: 30px;
}

QComboBox::down-arrow {
    image: url(:/icons/arrow.png);
}

/* 滑动条的滑块 */
QSlider::handle:horizontal {
    background: #2196f3;
    width: 20px;
    height: 20px;
    border-radius: 10px;
}

/* 进度条的进度块 */
QProgressBar::chunk {
    background-color: #4caf50;
    border-radius: 4px;
}

/* 分组框的标题 */
QGroupBox::title {
    subcontrol-origin: margin;
    left: 10px;
    padding: 0 5px;
}
```

### 7. 渐变效果
```css
/* 线性渐变 */
background: qlineargradient(x1:0, y1:0, x2:1, y2:0,
    stop:0 #3f51b5, stop:1 #9c27b0);

/* 径向渐变 */
background: qradialgradient(cx:0.5, cy:0.5, radius:0.5,
    stop:0 #3f51b5, stop:1 #9c27b0);
```

### 8. 在代码中应用QSS
```cpp
// 方式1: 应用到整个应用程序
qApp->setStyleSheet("QPushButton { background-color: blue; }");

// 方式2: 应用到特定控件
button->setStyleSheet("background-color: blue; color: white;");

// 方式3: 从文件加载
QFile file(":/styles/style.qss");
file.open(QFile::ReadOnly);
QString styleSheet = QLatin1String(file.readAll());
qApp->setStyleSheet(styleSheet);
```

## 关键代码

### 主题切换实现
```cpp
void applyLightTheme() {
    QString qss = R"(
        QMainWindow {
            background-color: #f5f5f5;
        }
        QPushButton {
            background-color: #2196f3;
            color: white;
            border-radius: 6px;
        }
        QPushButton:hover {
            background-color: #1976d2;
        }
        // ... 更多样式
    )";
    qApp->setStyleSheet(qss);
}
```

### 带伪状态的按钮样式
```css
QPushButton#primaryButton {
    background-color: #2196f3;
    color: white;
    border: none;
    border-radius: 6px;
    padding: 10px 20px;
}

QPushButton#primaryButton:hover {
    background-color: #1976d2;
}

QPushButton#primaryButton:pressed {
    background-color: #0d47a1;
}
```

## 运行截图

运行程序后可以看到：
1. 顶部有三个主题切换按钮（浅色/深色/蓝色）
2. 中间展示各种控件的样式效果
3. 按钮有hover和pressed状态的视觉反馈
4. 滑动条可以控制进度条的值
5. 文本编辑区显示QSS介绍

## 遇到的问题

### Q1: QSS和CSS有什么区别？
**A**: QSS语法与CSS非常相似，但有以下区别：
- QSS使用 `qlineargradient` 和 `qradialgradient` 代替CSS的 `linear-gradient`
- QSS支持子控件选择器（如 `QComboBox::drop-down`）
- QSS的属性名可能与CSS略有不同
- QSS不支持CSS3的一些高级特性（如动画、变换）

### Q2: 如何让QSS立即生效？
**A**: 调用 `qApp->setStyleSheet()` 后，样式会立即应用到所有控件。如果只想更新特定控件，可以使用 `widget->setStyleSheet()` 然后调用 `widget->update()`。

### Q3: 如何调试QSS？
**A**: 
1. 使用Qt Creator的样式表编辑器
2. 在代码中使用 `qDebug()` 输出样式字符串检查
3. 分步添加样式，观察效果
4. 使用 ` QWidget::setStyleSheet()` 单独测试控件

### Q4: 为什么我的QSS没有生效？
**A**: 常见原因：
1. 选择器写错（如ID选择器前面忘了 `#`）
2. 属性名拼写错误
3. 属性值格式不正确
4. 被其他样式覆盖（QSS有优先级规则）
5. 控件没有显示（如设置了 `display: none`）

### Q5: 如何实现动态主题切换？
**A**: 将不同主题的QSS字符串保存在函数或变量中，通过按钮点击事件调用 `qApp->setStyleSheet()` 切换。示例代码中实现了三种主题的切换。

### Q6: 子控件是什么？
**A**: 子控件是复杂控件的组成部分，如：
- `QComboBox::drop-down` - 下拉框的下拉按钮
- `QSlider::handle` - 滑动条的滑块
- `QProgressBar::chunk` - 进度条的进度块
- `QGroupBox::title` - 分组框的标题

### Q7: 如何设置控件的最小/最大尺寸？
**A**: 使用 `min-width`、`max-width`、`min-height`、`max-height` 属性：
```css
QPushButton {
    min-width: 100px;
    max-width: 200px;
    min-height: 30px;
}
```

### Q8: 如何让输入框获得焦点时改变边框颜色？
**A**: 使用 `:focus` 伪状态：
```css
QLineEdit {
    border: 2px solid #ddd;
}
QLineEdit:focus {
    border-color: #2196f3;
}
```

### Q9: 如何给分组框添加圆角和阴影效果？
**A**: 
```css
QGroupBox {
    background-color: #ffffff;
    border: 2px solid #e0e0e0;
    border-radius: 8px;
    margin-top: 12px;
}

QGroupBox::title {
    subcontrol-origin: margin;
    left: 10px;
    padding: 0 5px;
}
```
注意：Qt的QSS不支持CSS的 `box-shadow`，需要使用其他方式实现阴影。

### Q10: 如何自定义下拉框的选项样式？
**A**: 使用 `QComboBox QAbstractItemView` 选择器：
```css
QComboBox QAbstractItemView {
    background-color: #ffffff;
    border: 1px solid #ddd;
    selection-background-color: #2196f3;
    selection-color: white;
}
```

## 学习心得

1. **QSS让界面美化变得简单**：不需要重写paintEvent，只需要写样式表就能实现漂亮的界面

2. **主题切换很实用**：通过切换QSS字符串，可以快速实现日间/夜间模式切换

3. **伪状态增强交互感**：hover、pressed等伪状态让控件有更好的视觉反馈

4. **ID选择器精准控制**：使用 `setObjectName()` 配合ID选择器，可以精确控制特定控件的样式

5. **渐变效果提升质感**：线性渐变和径向渐变可以让界面更有层次感

6. **注意性能**：复杂的QSS可能会影响渲染性能，在大型应用中要注意优化

## 参考资料
- [Qt Style Sheets Reference](https://doc.qt.io/qt-5/stylesheet-reference.html)
- [Qt Style Sheets Examples](https://doc.qt.io/qt-5/stylesheet-examples.html)
