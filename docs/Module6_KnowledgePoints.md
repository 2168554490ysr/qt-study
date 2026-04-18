# 模块6: 通用UI组件库 (UI Components) - 知识点详细拆分

**版本**: v1.0  
**日期**: 2026-04-18  
**阶段**: 第一阶段学习 - 基础能力构建

---

## 一、模块概述

### 1.1 业务边界
- 提供可复用的自定义控件
- 实现统一的主题系统（明暗主题切换）
- 封装通用对话框和工具类
- 为其他5个模块提供UI基础设施

### 1.2 学习目标
完成本模块学习后，应能：
- 独立创建Qt窗口应用程序
- 理解Qt的核心机制（信号槽、事件循环）
- 掌握常用控件的使用
- 实现自定义控件
- 应用QSS样式美化界面
- 实现界面国际化

---

## 二、知识点详细拆分

### 知识点1: Qt项目基础结构

#### 1.1 核心概念
| 概念 | 说明 | 重要性 |
|------|------|--------|
| QApplication | 应用程序入口，管理全局资源 | ⭐⭐⭐ |
| main.cpp结构 | Qt程序的标准入口写法 | ⭐⭐⭐ |
| .pro项目文件 | qmake构建配置 | ⭐⭐⭐ |
| 元对象系统(MOC) | Qt的反射机制基础 | ⭐⭐⭐ |
| QObject基类 | 所有Qt对象的根基 | ⭐⭐⭐ |

#### 1.2 必须掌握的内容
- QApplication的创建和exec()事件循环
- 理解MOC编译过程（signals/slots宏展开）
- 项目文件(.pro)的基本配置：QT += widgets
- 头文件中Q_OBJECT宏的作用

#### 1.3 实践任务
- [ ] 创建一个最简单的Qt窗口程序
- [ ] 理解编译过程中的moc_xxx.cpp文件
- [ ] 修改.pro文件添加模块

---

### 知识点2: 信号与槽机制(Signals & Slots)

#### 2.1 核心概念
| 概念 | 说明 | 重要性 |
|------|------|--------|
| signals关键字 | 声明信号 | ⭐⭐⭐ |
| slots关键字 | 声明槽函数 | ⭐⭐⭐ |
| connect函数 | 连接信号与槽 | ⭐⭐⭐ |
| emit关键字 | 发射信号 | ⭐⭐⭐ |
| 连接类型 | Direct/Queued/Blocking | ⭐⭐⭐ |

#### 2.2 connect的5种写法
```cpp
// 1. Qt4语法（字符串方式，已不推荐）
connect(sender, SIGNAL(signal()), receiver, SLOT(slot()));

// 2. Qt5新语法（函数指针，编译期检查，推荐）
connect(sender, &Sender::signal, receiver, &Receiver::slot);

// 3. 连接Lambda表达式
connect(sender, &Sender::signal, [=]() { /* 处理逻辑 */ });

// 4. 连接重载函数（需要显式转换）
connect(combo, QOverload<int>::of(&QComboBox::currentIndexChanged), ...);

// 5. 指定连接类型（跨线程必需）
connect(sender, &Sender::signal, receiver, &Receiver::slot, Qt::QueuedConnection);
```

#### 2.3 必须掌握的内容
- 新旧语法的区别和优劣
- Lambda表达式在槽中的使用
- 跨线程连接必须使用Qt::QueuedConnection
- 断开连接：disconnect函数
- 信号可以连接信号（信号转发）

#### 2.4 常见错误
- 信号槽参数不匹配
- 忘记在头文件中写Q_OBJECT宏
- 跨线程使用DirectConnection导致崩溃

#### 2.5 实践任务
- [ ] 实现按钮点击改变标签文字
- [ ] 实现自定义信号和槽
- [ ] 实现信号连接信号
- [ ] 使用Lambda表达式处理信号

---

### 知识点3: 常用控件(Widgets)

#### 3.1 基础控件
| 控件类 | 用途 | 常用方法 | 常用信号 |
|--------|------|----------|----------|
| QWidget | 所有控件的基类 | show(), hide(), setEnabled() | 无 |
| QLabel | 显示文本/图片 | setText(), setPixmap() | 无 |
| QPushButton | 按钮 | setText(), setIcon() | clicked() |
| QLineEdit | 单行输入 | text(), setText(), clear() | textChanged(), returnPressed() |
| QTextEdit | 多行文本编辑 | toPlainText(), setPlainText() | textChanged() |
| QComboBox | 下拉选择 | addItem(), currentText() | currentIndexChanged() |
| QListWidget | 列表 | addItem(), currentItem() | itemClicked() |
| QCheckBox | 复选框 | isChecked(), setChecked() | stateChanged() |
| QRadioButton | 单选框 | isChecked() | toggled() |
| QSlider | 滑块 | value(), setValue() | valueChanged() |
| QProgressBar | 进度条 | setValue(), setRange() | 无 |

#### 3.2 容器控件
| 控件类 | 用途 | 关键方法 |
|--------|------|----------|
| QGroupBox | 分组框 | setTitle() |
| QTabWidget | 标签页 | addTab(), setCurrentIndex() |
| QStackedWidget | 堆叠窗口 | setCurrentIndex() |
| QSplitter | 分割器 | addWidget() |
| QScrollArea | 滚动区域 | setWidget() |

#### 3.3 对话框控件
| 控件类 | 用途 | 使用方式 |
|--------|------|----------|
| QMessageBox | 消息框 | QMessageBox::information(), warning(), critical() |
| QFileDialog | 文件对话框 | QFileDialog::getOpenFileName() |
| QInputDialog | 输入对话框 | QInputDialog::getText() |
| QProgressDialog | 进度对话框 | 构造函数创建 |

#### 3.4 必须掌握的内容
- 控件的父子关系（内存自动管理）
- 控件的enabled/disable状态
- 控件的sizePolicy（尺寸策略）
- 控件的minimumSize/maximumSize

#### 3.5 实践任务
- [ ] 创建一个包含各种控件的测试窗口
- [ ] 实现控件间的联动（如滑块控制进度条）
- [ ] 使用各种对话框
- [ ] 实现控件的显示/隐藏控制

---

### 知识点4: 布局管理(Layout)

#### 4.1 布局类
| 布局类 | 用途 | 特点 |
|--------|------|------|
| QHBoxLayout | 水平布局 | 控件从左到右排列 |
| QVBoxLayout | 垂直布局 | 控件从上到下排列 |
| QGridLayout | 网格布局 | 行列排列，可跨行列 |
| QFormLayout | 表单布局 | 标签-字段成对排列 |
| QStackedLayout | 堆叠布局 | 只显示一个控件 |

#### 4.2 布局技巧
| 技巧 | 说明 | 使用场景 |
|------|------|----------|
| addStretch() | 添加弹性空间 | 将控件推到一侧 |
| addSpacing() | 添加固定间距 | 控件间留空隙 |
| setMargin() | 设置边距 | 布局边缘留白 |
| setSpacing() | 设置控件间距 | 控件间距离 |
| setAlignment() | 设置对齐方式 | 控件居中/靠左/靠右 |

#### 4.3 布局嵌套
```
QVBoxLayout (主布局)
├── QHBoxLayout (顶部工具栏)
│   ├── 按钮1
│   ├── 按钮2
│   └── addStretch() (推到左边)
├── QSplitter (中部区域)
│   ├── QTreeWidget (左侧)
│   └── QTextEdit (右侧)
└── QHBoxLayout (底部状态栏)
```

#### 4.4 必须掌握的内容
- 布局可以嵌套
- 布局的addWidget()和addLayout()
- 布局的优先级和拉伸因子
- 使用Qt Designer设计布局

#### 4.5 实践任务
- [ ] 实现常见的三栏布局（左中右）
- [ ] 实现工具栏+内容区+状态栏布局
- [ ] 使用Qt Designer设计界面并加载
- [ ] 实现可调整比例的分割布局

---

### 知识点5: 主窗口(QMainWindow)

#### 5.1 核心组件
| 组件 | 说明 | 设置方法 |
|------|------|----------|
| 菜单栏(MenuBar) | 顶部菜单 | menuBar()->addMenu() |
| 工具栏(ToolBar) | 快捷按钮 | addToolBar() |
| 状态栏(StatusBar) | 底部状态 | statusBar()->showMessage() |
| 中心部件(CentralWidget) | 主内容区 | setCentralWidget() |
| 停靠窗口(DockWidget) | 可浮动窗口 | addDockWidget() |

#### 5.2 必须掌握的内容
- QMainWindow的结构和组成部分
- QAction的使用（菜单项和工具按钮共用）
- 状态栏显示临时消息和永久部件
- 保存和恢复窗口状态

#### 5.3 实践任务
- [ ] 创建带菜单栏的主窗口
- [ ] 添加工具栏和状态栏
- [ ] 实现菜单项和工具按钮的联动
- [ ] 保存窗口大小和位置

---

### 知识点6: 自定义控件

#### 6.1 创建自定义控件的步骤
1. 继承合适的基类（QWidget或其子类）
2. 在头文件中声明Q_OBJECT宏
3. 定义属性（Q_PROPERTY）
4. 重写paintEvent()（需要时）
5. 定义信号和槽

#### 6.2 常用重写函数
| 函数 | 用途 | 触发时机 |
|------|------|----------|
| paintEvent() | 绘制控件 | 需要重绘时 |
| resizeEvent() | 尺寸变化 | 控件大小改变 |
| mousePressEvent() | 鼠标按下 | 鼠标左键按下 |
| mouseMoveEvent() | 鼠标移动 | 鼠标在控件上移动 |
| keyPressEvent() | 键盘按下 | 控件获得焦点时按键 |
| event() | 通用事件处理 | 所有事件 |

#### 6.3 Q_PROPERTY属性系统
```cpp
Q_PROPERTY(QString title READ title WRITE setTitle NOTIFY titleChanged)
```

#### 6.4 必须掌握的内容
- 何时需要自定义控件
- 控件的最小尺寸提示（sizeHint）
- 控件的事件处理
- 使用QPainter绘制自定义外观

#### 6.5 实践任务
- [ ] 创建一个带图标的按钮控件
- [ ] 创建一个进度指示器控件
- [ ] 创建一个可折叠的面板控件
- [ ] 实现自定义绘制的控件

---

### 知识点7: QSS样式表

#### 7.1 QSS基础语法
```css
/* 选择器 */
QPushButton { }           /* 类型选择器 */
#myButton { }             /* ID选择器 */
QPushButton:hover { }     /* 伪状态 */
QPushButton[class="primary"] { }  /* 属性选择器 */
```

#### 7.2 常用属性
| 属性 | 说明 | 示例 |
|------|------|------|
| background-color | 背景色 | #2d2d2d, rgb(255,0,0) |
| color | 文字颜色 | white, #cccccc |
| border | 边框 | 1px solid #555 |
| border-radius | 圆角 | 4px, 50% |
| padding | 内边距 | 5px 10px |
| margin | 外边距 | 5px |
| font-size | 字体大小 | 12px, 14pt |
| font-family | 字体 | "Microsoft YaHei" |

#### 7.3 控件特定样式
| 控件 | 特殊属性 |
|------|----------|
| QPushButton | ::pressed, ::checked |
| QSlider | ::groove, ::handle |
| QScrollBar | ::handle, ::add-line |
| QTabWidget | ::tab-bar, ::tab |
| QProgressBar | ::chunk |

#### 7.4 动态样式
使用属性控制样式切换：
```cpp
// C++代码
button->setProperty("type", "primary");

// QSS代码
QPushButton[type="primary"] {
    background-color: #0078d4;
}
```

#### 7.5 必须掌握的内容
- QSS与CSS的异同
- 选择器的优先级
- 动态切换主题的方法
- 使用qApp->setStyleSheet()设置全局样式

#### 7.6 实践任务
- [ ] 为按钮编写hover和pressed样式
- [ ] 实现暗色主题样式表
- [ ] 实现主题动态切换功能
- [ ] 为自定义控件编写QSS

---

### 知识点8: Model/View架构基础

#### 8.1 核心概念
| 概念 | 说明 | 对应类 |
|------|------|--------|
| Model | 数据模型 | QAbstractItemModel |
| View | 视图显示 | QListView, QTreeView, QTableView |
| Delegate | 委托（控制显示和编辑） | QAbstractItemDelegate |
| 角色(Role) | 数据类型标识 | Qt::DisplayRole, Qt::UserRole |

#### 8.2 内置Model类
| Model类 | 用途 |
|---------|------|
| QStringListModel | 字符串列表 |
| QStandardItemModel | 通用标准模型 |
| QFileSystemModel | 文件系统模型 |

#### 8.3 必须掌握的内容
- Model/View与直接操作控件的区别
- 使用QStandardItemModel快速实现列表
- 理解Role的概念
- View的选中模式（单选/多选）

#### 8.4 实践任务
- [ ] 使用QStringListModel显示列表
- [ ] 使用QStandardItemModel显示表格
- [ ] 实现列表项的增删改
- [ ] 获取选中的数据项

---

### 知识点9: 国际化(i18n)

#### 9.1 国际化步骤
1. 代码中使用tr()包裹所有显示文本
2. 使用lupdate生成.ts文件
3. 使用Qt Linguist翻译
4. 使用lrelease生成.qm文件
5. 程序加载对应.qm文件

#### 9.2 关键类
| 类 | 用途 |
|----|------|
| QTranslator | 翻译器 |
| QLocale | 区域设置 |
| tr() | 标记可翻译文本 |

#### 9.3 必须掌握的内容
- tr()的正确使用
- 处理复数形式
- 运行时切换语言

#### 9.4 实践任务
- [ ] 为界面添加tr()标记
- [ ] 生成翻译文件
- [ ] 实现语言切换功能

---

### 知识点10: 资源系统

#### 10.1 资源文件(.qrc)
```xml
<RCC>
    <qresource prefix="/icons">
        <file>connect.png</file>
        <file>disconnect.png</file>
    </qresource>
    <qresource prefix="/styles">
        <file>dark_theme.qss</file>
    </qresource>
</RCC>
```

#### 10.2 使用资源
```cpp
// 使用图标
QIcon icon(":/icons/connect.png");

// 加载样式表
QFile file(":/styles/dark_theme.qss");
file.open(QFile::ReadOnly);
qApp->setStyleSheet(file.readAll());
```

#### 10.3 实践任务
- [ ] 创建资源文件
- [ ] 添加图标和样式文件
- [ ] 在代码中使用资源

---

## 三、学习顺序建议

### 推荐学习路径
```
Week 1: 基础入门
├── Day 1-2: 知识点1 (Qt项目基础)
├── Day 3-4: 知识点2 (信号与槽)
├── Day 5-6: 知识点3 (常用控件)
└── Day 7: 知识点4 (布局管理)

Week 2: 进阶提升
├── Day 1-2: 知识点5 (主窗口)
├── Day 3-4: 知识点6 (自定义控件)
├── Day 5-6: 知识点7 (QSS样式表)
└── Day 7: 知识点8 (Model/View)

Week 3: 完善优化
├── Day 1-2: 知识点9 (国际化)
├── Day 3-4: 知识点10 (资源系统)
└── Day 5-7: 综合项目实战
```

---

## 四、模块6实战项目

### 项目目标
创建一个完整的UI组件库，包含：
1. **主题管理器** - 支持明暗主题切换
2. **自定义按钮** - 带图标、支持多种状态样式
3. **状态指示器** - 显示连接状态的LED指示灯
4. **折叠面板** - 可展开/收起的设置面板
5. **消息通知** - 右下角弹出通知
6. **加载动画** - 旋转的加载指示器

### 验收标准
- [ ] 所有控件都有完整的QSS样式
- [ ] 支持中英文切换
- [ ] 主题切换即时生效
- [ ] 控件可在Qt Designer中使用

---

## 五、参考资源

### 官方文档
- [Qt Widgets](https://doc.qt.io/qt-5/qtwidgets-index.html)
- [Signals & Slots](https://doc.qt.io/qt-5/signalsandslots.html)
- [Layout Management](https://doc.qt.io/qt-5/layout.html)
- [Style Sheets](https://doc.qt.io/qt-5/stylesheet.html)

### 推荐书籍
- 《Qt Creator快速入门》
- 《Qt5开发及实例》

### 在线教程
- Qt官方入门教程
- B站Qt视频教程

---

**文档变更记录**

| 版本 | 日期 | 修改人 | 修改内容 |
|------|------|--------|----------|
| v1.0 | 2026-04-18 | - | 初始版本 |
