# Day 05: 主窗口(MainWindow)

## 学习目标
- [ ] 掌握 QMainWindow 主窗口结构
- [ ] 掌握菜单栏(QMenuBar)的创建和使用
- [ ] 掌握工具栏(QToolBar)的创建和使用
- [ ] 掌握状态栏(QStatusBar)的创建和使用
- [ ] 理解中心部件(Central Widget)的概念
- [ ] 学习动作(QAction)的复用

## 实践任务
1. [ ] 创建 QMainWindow 主窗口
2. [ ] 创建菜单栏，包含文件、编辑、帮助菜单
3. [ ] 创建工具栏，添加常用按钮
4. [ ] 创建状态栏，显示状态信息
5. [ ] 创建中心部件(QTextEdit作为编辑器)
6. [ ] 实现动作的快捷键和信号槽连接

---

## 关键概念

### 1. QMainWindow 结构
```
┌─────────────────────────────────────┐
│  菜单栏 (MenuBar)                    │
├─────────────────────────────────────┤
│  工具栏 (ToolBar)                    │
├─────────────────────────────────────┤
│                                     │
│  中心部件 (Central Widget)           │
│  ┌─────────────────────────────┐   │
│  │                             │   │
│  │     主要内容显示区域         │   │
│  │                             │   │
│  └─────────────────────────────┘   │
│                                     │
├─────────────────────────────────────┤
│  状态栏 (StatusBar)    就绪 │
└─────────────────────────────────────┘
```

### 2. 菜单栏 (QMenuBar)
```cpp
// 获取主窗口的菜单栏
QMenuBar *menuBar = mainWindow.menuBar();

// 添加菜单
QMenu *fileMenu = menuBar->addMenu("文件(&F)");  // &F 表示 Alt+F 快捷键

// 添加动作
QAction *newAction = fileMenu->addAction("新建(&N)");
newAction->setShortcut(QKeySequence::New);  // Ctrl+N

// 添加分隔线
fileMenu->addSeparator();
```

### 3. 工具栏 (QToolBar)
```cpp
// 创建工具栏
QToolBar *toolBar = mainWindow.addToolBar("主工具栏");

// 添加动作（复用菜单中的动作）
toolBar->addAction(newAction);
toolBar->addAction(saveAction);

// 添加分隔线
toolBar->addSeparator();

// 添加自定义控件
toolBar->addWidget(new QPushButton("自定义按钮"));
```

### 4. 状态栏 (QStatusBar)
```cpp
// 获取主窗口的状态栏
QStatusBar *statusBar = mainWindow.statusBar();

// 显示临时消息（左侧，指定时间后消失）
statusBar->showMessage("就绪", 5000);  // 5秒后消失

// 添加永久显示的标签（右侧）
QLabel *label = new QLabel("就绪");
statusBar->addPermanentWidget(label);
```

### 5. 中心部件 (Central Widget)
```cpp
// 创建中心部件（可以是任何QWidget或其子类）
QWidget *centralWidget = new QWidget();
QVBoxLayout *layout = new QVBoxLayout();
layout->addWidget(new QTextEdit());
centralWidget->setLayout(layout);

// 设置到主窗口
mainWindow.setCentralWidget(centralWidget);
```

### 6. 动作 (QAction)
```cpp
// 创建动作
QAction *action = new QAction("新建", this);
action->setShortcut(QKeySequence::New);  // 设置快捷键
action->setStatusTip("创建新文件");       // 状态栏提示

// 连接信号槽
connect(action, &QAction::triggered, this, &MyClass::onNewFile);
```

### 7. 快捷键设置
```cpp
// 标准快捷键
action->setShortcut(QKeySequence::New);      // Ctrl+N
action->setShortcut(QKeySequence::Open);     // Ctrl+O
action->setShortcut(QKeySequence::Save);     // Ctrl+S
action->setShortcut(QKeySequence::Copy);     // Ctrl+C
action->setShortcut(QKeySequence::Paste);    // Ctrl+V
action->setShortcut(QKeySequence::Quit);     // Ctrl+Q

// 自定义快捷键
action->setShortcut(QKeySequence("Ctrl+Shift+X"));
```

---

## 代码逐行解说

### 创建主窗口
```cpp
QMainWindow mainWindow;
mainWindow.setWindowTitle("Day 05: 主窗口示例");
mainWindow.resize(800, 600);
```
主窗口是应用程序的主界面容器。

### 创建中心部件
```cpp
QWidget *centralWidget = new QWidget();
mainWindow.setCentralWidget(centralWidget);
```
中心部件是主窗口的核心区域，占据大部分空间。

### 动作复用
```cpp
// 同一个动作可以同时添加到菜单和工具栏
fileMenu->addAction(newAction);      // 添加到菜单
toolBar->addAction(newAction);       // 添加到工具栏
```
这是Qt的设计优势：动作与显示分离。

---

## Q&A 常见问题

### Q1: QMainWindow 和 QWidget 有什么区别？
**A:** 
- `QWidget`：基础窗口类，没有菜单栏、工具栏、状态栏的概念
- `QMainWindow`：专门的主窗口类，内置了菜单栏、工具栏、状态栏、中心部件的结构

### Q2: 为什么动作(QAction)可以同时在菜单和工具栏使用？
**A:** 这是Qt的设计模式。QAction是抽象的"动作"，包含了图标、文字、快捷键、回调函数。菜单和工具栏只是展示方式不同，同一个动作可以在多处复用。

### Q3: 菜单中的 `&F` 是什么意思？
**A:** `&` 表示 Alt 快捷键。`文件(&F)` 表示按 Alt+F 可以打开文件菜单。

### Q4: 如何禁用某个菜单项？
**A:** 
```cpp
action->setEnabled(false);  // 禁用
action->setEnabled(true);   // 启用
```

### Q5: 工具栏可以拖动吗？
**A:** 默认可以。用户可以拖动工具栏到窗口的顶部、底部、左侧或右侧。可以通过 `setMovable(false)` 禁用拖动。

### Q6: 如何在状态栏显示永久信息？
**A:** 使用 `addPermanentWidget()` 添加控件，这个信息会一直显示，不会被临时消息覆盖。

### Q7: 中心部件可以是什么类型？
**A:** 任何 QWidget 或其子类都可以：
- QTextEdit（文本编辑器）
- QTableWidget（表格）
- QGraphicsView（图形视图）
- 自定义的 QWidget

---

## 运行截图

（待学习者运行后补充）

---

## 学习心得

（学习者填写）
