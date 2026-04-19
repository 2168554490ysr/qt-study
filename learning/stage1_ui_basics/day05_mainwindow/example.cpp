/******************************************************************************
 * Day 05: 主窗口(MainWindow)
 * 
 * 学习目标：
 * - 掌握 QMainWindow 主窗口结构
 * - 掌握菜单栏(QMenuBar)的创建和使用
 * - 掌握工具栏(QToolBar)的创建和使用
 * - 掌握状态栏(QStatusBar)的创建和使用
 * - 理解中心部件(Central Widget)的概念
 * - 学习动作(QAction)的复用
 ******************************************************************************/

#include <QApplication>
#include <QMainWindow>
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QToolBar>
#include <QStatusBar>
#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QTextEdit>
#include <QDebug>
#include <QMessageBox>
#include <QIcon>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    // ========================================
    // 1. 创建主窗口
    // ========================================
    QMainWindow mainWindow;
    mainWindow.setWindowTitle("Day 05: 主窗口(MainWindow)示例");
    mainWindow.resize(800, 600);

    // ========================================
    // 2. 创建中心部件(Central Widget)
    // ========================================
    QWidget *centralWidget = new QWidget();
    QVBoxLayout *centerLayout = new QVBoxLayout();
    
    // 添加一些内容到中心区域
    QLabel *titleLabel = new QLabel("<h2>欢迎使用主窗口示例</h2>");
    titleLabel->setAlignment(Qt::AlignCenter);
    
    QTextEdit *textEdit = new QTextEdit();
    textEdit->setPlaceholderText("这里显示内容...\n\n试试点击菜单和工具栏按钮！");
    
    centerLayout->addWidget(titleLabel);
    centerLayout->addWidget(textEdit);
    centralWidget->setLayout(centerLayout);
    
    // 设置中心部件
    mainWindow.setCentralWidget(centralWidget);

    // ========================================
    // 3. 创建菜单栏(MenuBar)
    // ========================================
    QMenuBar *menuBar = mainWindow.menuBar();
    
    // 3.1 文件菜单
    QMenu *fileMenu = menuBar->addMenu("文件(&F)");  // &F 表示 Alt+F 快捷键
    
    QAction *newAction = fileMenu->addAction("新建(&N)");
    newAction->setShortcut(QKeySequence::New);  // Ctrl+N
    
    QAction *openAction = fileMenu->addAction("打开(&O)...");
    openAction->setShortcut(QKeySequence::Open);  // Ctrl+O
    
    QAction *saveAction = fileMenu->addAction("保存(&S)");
    saveAction->setShortcut(QKeySequence::Save);  // Ctrl+S
    
    fileMenu->addSeparator();  // 分隔线
    
    QAction *exitAction = fileMenu->addAction("退出(&X)");
    exitAction->setShortcut(QKeySequence::Quit);  // Ctrl+Q
    
    // 3.2 编辑菜单
    QMenu *editMenu = menuBar->addMenu("编辑(&E)");
    
    QAction *cutAction = editMenu->addAction("剪切(&T)");
    cutAction->setShortcut(QKeySequence::Cut);  // Ctrl+X
    
    QAction *copyAction = editMenu->addAction("复制(&C)");
    copyAction->setShortcut(QKeySequence::Copy);  // Ctrl+C
    
    QAction *pasteAction = editMenu->addAction("粘贴(&P)");
    pasteAction->setShortcut(QKeySequence::Paste);  // Ctrl+V
    
    // 3.3 帮助菜单
    QMenu *helpMenu = menuBar->addMenu("帮助(&H)");
    QAction *aboutAction = helpMenu->addAction("关于(&A)...");

    // ========================================
    // 4. 创建工具栏(ToolBar)
    // ========================================
    QToolBar *toolBar = mainWindow.addToolBar("主工具栏");
    
    // 添加动作到工具栏（复用菜单中的动作）
    toolBar->addAction(newAction);
    toolBar->addAction(openAction);
    toolBar->addAction(saveAction);
    toolBar->addSeparator();
    toolBar->addAction(cutAction);
    toolBar->addAction(copyAction);
    toolBar->addAction(pasteAction);
    
    // 添加按钮到工具栏
    QPushButton *customBtn = new QPushButton("自定义按钮");
    toolBar->addWidget(customBtn);

    // ========================================
    // 5. 创建状态栏(StatusBar)
    // ========================================
    QStatusBar *statusBar = mainWindow.statusBar();
    
    // 添加永久显示的标签（右侧）
    QLabel *permanentLabel = new QLabel("就绪");
    statusBar->addPermanentWidget(permanentLabel);
    
    // 显示临时消息（左侧，5秒后消失）
    statusBar->showMessage("应用程序已启动", 5000);  // 5000毫秒 = 5秒

    // ========================================
    // 6. 连接信号槽
    // ========================================
    
    // 新建动作
    QObject::connect(newAction, &QAction::triggered, [&]() {
        textEdit->clear();
        textEdit->setText("新建文件...");
        statusBar->showMessage("新建文件", 3000);
        qDebug() << "新建文件";
    });
    
    // 打开动作
    QObject::connect(openAction, &QAction::triggered, [&]() {
        textEdit->setText("打开文件...");
        statusBar->showMessage("打开文件", 3000);
        qDebug() << "打开文件";
    });
    
    // 保存动作
    QObject::connect(saveAction, &QAction::triggered, [&]() {
        statusBar->showMessage("文件已保存", 3000);
        qDebug() << "保存文件:" << textEdit->toPlainText();
    });
    
    // 退出动作
    QObject::connect(exitAction, &QAction::triggered, &app, &QApplication::quit);
    
    // 剪切/复制/粘贴（使用QTextEdit自带功能）
    QObject::connect(cutAction, &QAction::triggered, textEdit, &QTextEdit::cut);
    QObject::connect(copyAction, &QAction::triggered, textEdit, &QTextEdit::copy);
    QObject::connect(pasteAction, &QAction::triggered, textEdit, &QTextEdit::paste);
    
    // 关于动作
    QObject::connect(aboutAction, &QAction::triggered, [&]() {
        QMessageBox::about(&mainWindow, "关于", 
            "<h2>Day 05: 主窗口示例</h2>"
            "<p>这是Qt学习项目的主窗口示例。</p>"
            "<p>学习目标：</p>"
            "<ul>"
            "<li>菜单栏(QMenuBar)</li>"
            "<li>工具栏(QToolBar)</li>"
            "<li>状态栏(QStatusBar)</li>"
            "<li>中心部件(Central Widget)</li>"
            "<li>动作(QAction)复用</li>"
            "</ul>");
    });
    
    // 自定义按钮
    QObject::connect(customBtn, &QPushButton::clicked, [&]() {
        textEdit->append("点击了自定义工具栏按钮！");
        statusBar->showMessage("自定义按钮被点击", 2000);
    });

    // 监听文本变化，更新状态栏
    QObject::connect(textEdit, &QTextEdit::textChanged, [&]() {
        int len = textEdit->toPlainText().length();
        permanentLabel->setText(QString("字符数: %1").arg(len));
    });

    // ========================================
    // 7. 显示主窗口
    // ========================================
    mainWindow.show();
    qDebug() << "Day05 主窗口示例已启动";
    qDebug() << "OK";
    return app.exec();
}
