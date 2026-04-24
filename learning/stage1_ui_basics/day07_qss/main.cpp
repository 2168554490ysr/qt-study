#include <QApplication>
#include <QMainWindow>
#include <QStatusBar>
#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QComboBox>
#include <QSlider>
#include <QProgressBar>
#include <QGroupBox>
#include <QTextEdit>
#include <QMessageBox>
#include <QDebug>

// Day07: QSS样式表学习
// 演示QSS基本语法、控件样式、伪状态、主题切换

class QssDemoWindow : public QMainWindow {
    Q_OBJECT

public:
    QssDemoWindow(QWidget *parent = nullptr) : QMainWindow(parent) {
        setWindowTitle("Day07: QSS样式表学习");
        setMinimumSize(700, 600);
        
        // 创建中心部件
        QWidget *centralWidget = new QWidget(this);
        setCentralWidget(centralWidget);
        
        QVBoxLayout *mainLayout = new QVBoxLayout(centralWidget);
        mainLayout->setSpacing(15);
        mainLayout->setContentsMargins(20, 20, 20, 20);
        
        // ========== 1. 主题切换区域 ==========
        QGroupBox *themeGroup = new QGroupBox("主题切换", this);
        QHBoxLayout *themeLayout = new QHBoxLayout(themeGroup);
        
        QPushButton *lightBtn = new QPushButton("☀️ 浅色主题", this);
        QPushButton *darkBtn = new QPushButton("🌙 深色主题", this);
        QPushButton *blueBtn = new QPushButton("🔵 蓝色主题", this);
        
        themeLayout->addWidget(lightBtn);
        themeLayout->addWidget(darkBtn);
        themeLayout->addWidget(blueBtn);
        themeLayout->addStretch();
        
        mainLayout->addWidget(themeGroup);
        
        // ========== 2. 基本控件样式展示 ==========
        QGroupBox *widgetsGroup = new QGroupBox("控件样式展示", this);
        QVBoxLayout *widgetsLayout = new QVBoxLayout(widgetsGroup);
        
        // 标签
        QLabel *label = new QLabel("这是一个带样式的QLabel", this);
        label->setObjectName("demoLabel");
        label->setAlignment(Qt::AlignCenter);
        widgetsLayout->addWidget(label);
        
        // 输入框
        QLineEdit *lineEdit = new QLineEdit(this);
        lineEdit->setPlaceholderText("请输入内容...");
        lineEdit->setObjectName("demoLineEdit");
        widgetsLayout->addWidget(lineEdit);
        
        // 下拉框
        QComboBox *comboBox = new QComboBox(this);
        comboBox->addItems({"选项一", "选项二", "选项三", "选项四"});
        comboBox->setObjectName("demoComboBox");
        widgetsLayout->addWidget(comboBox);
        
        // 滑动条
        QSlider *slider = new QSlider(Qt::Horizontal, this);
        slider->setRange(0, 100);
        slider->setValue(50);
        slider->setObjectName("demoSlider");
        widgetsLayout->addWidget(slider);
        
        // 进度条
        QProgressBar *progressBar = new QProgressBar(this);
        progressBar->setRange(0, 100);
        progressBar->setValue(65);
        progressBar->setObjectName("demoProgressBar");
        progressBar->setFormat("进度: %p%");
        widgetsLayout->addWidget(progressBar);
        
        // 连接滑动条和进度条
        connect(slider, &QSlider::valueChanged, progressBar, &QProgressBar::setValue);
        
        mainLayout->addWidget(widgetsGroup);
        
        // ========== 3. 按钮样式展示 ==========
        QGroupBox *buttonGroup = new QGroupBox("按钮样式展示（包含伪状态）", this);
        QHBoxLayout *buttonLayout = new QHBoxLayout(buttonGroup);
        
        QPushButton *primaryBtn = new QPushButton("主要按钮", this);
        primaryBtn->setObjectName("primaryButton");
        
        QPushButton *successBtn = new QPushButton("成功按钮", this);
        successBtn->setObjectName("successButton");
        
        QPushButton *dangerBtn = new QPushButton("危险按钮", this);
        dangerBtn->setObjectName("dangerButton");
        
        QPushButton *disabledBtn = new QPushButton("禁用按钮", this);
        disabledBtn->setObjectName("disabledButton");
        disabledBtn->setEnabled(false);
        
        buttonLayout->addWidget(primaryBtn);
        buttonLayout->addWidget(successBtn);
        buttonLayout->addWidget(dangerBtn);
        buttonLayout->addWidget(disabledBtn);
        
        mainLayout->addWidget(buttonGroup);
        
        // ========== 4. 文本编辑区 ==========
        QGroupBox *textGroup = new QGroupBox("文本编辑区", this);
        QVBoxLayout *textLayout = new QVBoxLayout(textGroup);
        
        QTextEdit *textEdit = new QTextEdit(this);
        textEdit->setObjectName("demoTextEdit");
        textEdit->setPlaceholderText("在这里输入多行文本...");
        textEdit->setText("QSS (Qt Style Sheets) 是一种强大的样式机制，\n"
                         "类似于Web开发中的CSS。\n\n"
                         "它可以让你：\n"
                         "1. 统一设置控件外观\n"
                         "2. 实现主题切换功能\n"
                         "3. 定义控件在不同状态下的样式");
        textLayout->addWidget(textEdit);
        
        mainLayout->addWidget(textGroup);
        
        // ========== 5. 状态栏 ==========
        statusBar()->showMessage("就绪 - 点击主题按钮切换样式");
        
        // ========== 信号连接 ==========
        connect(lightBtn, &QPushButton::clicked, this, [this]() {
            applyLightTheme();
            statusBar()->showMessage("已切换到浅色主题", 3000);
        });
        
        connect(darkBtn, &QPushButton::clicked, this, [this]() {
            applyDarkTheme();
            statusBar()->showMessage("已切换到深色主题", 3000);
        });
        
        connect(blueBtn, &QPushButton::clicked, this, [this]() {
            applyBlueTheme();
            statusBar()->showMessage("已切换到蓝色主题", 3000);
        });
        
        connect(primaryBtn, &QPushButton::clicked, this, []() {
            QMessageBox::information(nullptr, "提示", "你点击了主要按钮！");
        });
        
        connect(successBtn, &QPushButton::clicked, this, []() {
            QMessageBox::information(nullptr, "提示", "你点击了成功按钮！");
        });
        
        connect(dangerBtn, &QPushButton::clicked, this, []() {
            QMessageBox::warning(nullptr, "警告", "你点击了危险按钮！");
        });
        
        // 默认应用浅色主题
        applyLightTheme();
    }

private:
    // 应用浅色主题
    void applyLightTheme() {
        QString qss = R"(
            /* ==================== 全局样式 ==================== */
            QWidget {
                font-family: "Microsoft YaHei", "SimHei", sans-serif;
                font-size: 14px;
            }
            
            /* ==================== 主窗口 ==================== */
            QMainWindow {
                background-color: #f5f5f5;
            }
            
            /* ==================== 分组框 ==================== */
            QGroupBox {
                background-color: #ffffff;
                border: 2px solid #e0e0e0;
                border-radius: 8px;
                margin-top: 12px;
                padding-top: 10px;
                font-weight: bold;
                color: #333333;
            }
            
            QGroupBox::title {
                subcontrol-origin: margin;
                left: 10px;
                padding: 0 5px;
            }
            
            /* ==================== 标签 ==================== */
            QLabel#demoLabel {
                background-color: #e3f2fd;
                color: #1976d2;
                padding: 15px;
                border-radius: 6px;
                font-size: 16px;
                font-weight: bold;
            }
            
            /* ==================== 输入框 ==================== */
            QLineEdit#demoLineEdit {
                background-color: #ffffff;
                border: 2px solid #ddd;
                border-radius: 6px;
                padding: 10px;
                color: #333;
            }
            
            QLineEdit#demoLineEdit:focus {
                border-color: #2196f3;
                background-color: #f0f8ff;
            }
            
            QLineEdit#demoLineEdit:hover {
                border-color: #64b5f6;
            }
            
            /* ==================== 下拉框 ==================== */
            QComboBox#demoComboBox {
                background-color: #ffffff;
                border: 2px solid #ddd;
                border-radius: 6px;
                padding: 8px;
                min-width: 120px;
            }
            
            QComboBox#demoComboBox:hover {
                border-color: #64b5f6;
            }
            
            QComboBox#demoComboBox::drop-down {
                border: none;
                width: 30px;
            }
            
            QComboBox#demoComboBox::down-arrow {
                image: none;
                border-left: 5px solid transparent;
                border-right: 5px solid transparent;
                border-top: 8px solid #666;
                margin-right: 10px;
            }
            
            QComboBox#demoComboBox QAbstractItemView {
                background-color: #ffffff;
                border: 1px solid #ddd;
                selection-background-color: #2196f3;
                selection-color: white;
            }
            
            /* ==================== 滑动条 ==================== */
            QSlider#demoSlider::groove:horizontal {
                height: 8px;
                background: #e0e0e0;
                border-radius: 4px;
            }
            
            QSlider#demoSlider::handle:horizontal {
                background: #2196f3;
                width: 20px;
                height: 20px;
                margin: -6px 0;
                border-radius: 10px;
            }
            
            QSlider#demoSlider::handle:horizontal:hover {
                background: #1976d2;
            }
            
            QSlider#demoSlider::sub-page:horizontal {
                background: #2196f3;
                border-radius: 4px;
            }
            
            /* ==================== 进度条 ==================== */
            QProgressBar#demoProgressBar {
                border: 2px solid #e0e0e0;
                border-radius: 6px;
                text-align: center;
                height: 25px;
            }
            
            QProgressBar#demoProgressBar::chunk {
                background-color: #4caf50;
                border-radius: 4px;
            }
            
            /* ==================== 按钮 - 主要 ==================== */
            QPushButton#primaryButton {
                background-color: #2196f3;
                color: white;
                border: none;
                border-radius: 6px;
                padding: 10px 20px;
                font-weight: bold;
                min-width: 100px;
            }
            
            QPushButton#primaryButton:hover {
                background-color: #1976d2;
            }
            
            QPushButton#primaryButton:pressed {
                background-color: #0d47a1;
            }
            
            /* ==================== 按钮 - 成功 ==================== */
            QPushButton#successButton {
                background-color: #4caf50;
                color: white;
                border: none;
                border-radius: 6px;
                padding: 10px 20px;
                font-weight: bold;
                min-width: 100px;
            }
            
            QPushButton#successButton:hover {
                background-color: #388e3c;
            }
            
            QPushButton#successButton:pressed {
                background-color: #1b5e20;
            }
            
            /* ==================== 按钮 - 危险 ==================== */
            QPushButton#dangerButton {
                background-color: #f44336;
                color: white;
                border: none;
                border-radius: 6px;
                padding: 10px 20px;
                font-weight: bold;
                min-width: 100px;
            }
            
            QPushButton#dangerButton:hover {
                background-color: #d32f2f;
            }
            
            QPushButton#dangerButton:pressed {
                background-color: #b71c1c;
            }
            
            /* ==================== 按钮 - 禁用 ==================== */
            QPushButton#disabledButton {
                background-color: #bdbdbd;
                color: #757575;
                border: none;
                border-radius: 6px;
                padding: 10px 20px;
                font-weight: bold;
                min-width: 100px;
            }
            
            /* ==================== 主题切换按钮 ==================== */
            QPushButton {
                background-color: #ffffff;
                border: 2px solid #ddd;
                border-radius: 6px;
                padding: 8px 16px;
            }
            
            QPushButton:hover {
                background-color: #f5f5f5;
                border-color: #2196f3;
            }
            
            /* ==================== 文本编辑区 ==================== */
            QTextEdit#demoTextEdit {
                background-color: #ffffff;
                border: 2px solid #ddd;
                border-radius: 6px;
                padding: 10px;
                color: #333;
                line-height: 1.5;
            }
            
            QTextEdit#demoTextEdit:focus {
                border-color: #2196f3;
            }
            
            /* ==================== 状态栏 ==================== */
            QStatusBar {
                background-color: #fafafa;
                color: #666;
                border-top: 1px solid #e0e0e0;
            }
        )";
        
        qApp->setStyleSheet(qss);
    }
    
    // 应用深色主题
    void applyDarkTheme() {
        QString qss = R"(
            /* ==================== 全局样式 ==================== */
            QWidget {
                font-family: "Microsoft YaHei", "SimHei", sans-serif;
                font-size: 14px;
            }
            
            /* ==================== 主窗口 ==================== */
            QMainWindow {
                background-color: #263238;
            }
            
            /* ==================== 分组框 ==================== */
            QGroupBox {
                background-color: #37474f;
                border: 2px solid #455a64;
                border-radius: 8px;
                margin-top: 12px;
                padding-top: 10px;
                font-weight: bold;
                color: #eceff1;
            }
            
            QGroupBox::title {
                subcontrol-origin: margin;
                left: 10px;
                padding: 0 5px;
            }
            
            /* ==================== 标签 ==================== */
            QLabel#demoLabel {
                background-color: #1565c0;
                color: #ffffff;
                padding: 15px;
                border-radius: 6px;
                font-size: 16px;
                font-weight: bold;
            }
            
            /* ==================== 输入框 ==================== */
            QLineEdit#demoLineEdit {
                background-color: #455a64;
                border: 2px solid #546e7a;
                border-radius: 6px;
                padding: 10px;
                color: #eceff1;
            }
            
            QLineEdit#demoLineEdit:focus {
                border-color: #64b5f6;
                background-color: #37474f;
            }
            
            QLineEdit#demoLineEdit:hover {
                border-color: #90caf9;
            }
            
            /* ==================== 下拉框 ==================== */
            QComboBox#demoComboBox {
                background-color: #455a64;
                border: 2px solid #546e7a;
                border-radius: 6px;
                padding: 8px;
                min-width: 120px;
                color: #eceff1;
            }
            
            QComboBox#demoComboBox:hover {
                border-color: #90caf9;
            }
            
            QComboBox#demoComboBox::drop-down {
                border: none;
                width: 30px;
            }
            
            QComboBox#demoComboBox::down-arrow {
                image: none;
                border-left: 5px solid transparent;
                border-right: 5px solid transparent;
                border-top: 8px solid #b0bec5;
                margin-right: 10px;
            }
            
            QComboBox#demoComboBox QAbstractItemView {
                background-color: #455a64;
                border: 1px solid #546e7a;
                selection-background-color: #2196f3;
                selection-color: white;
            }
            
            /* ==================== 滑动条 ==================== */
            QSlider#demoSlider::groove:horizontal {
                height: 8px;
                background: #546e7a;
                border-radius: 4px;
            }
            
            QSlider#demoSlider::handle:horizontal {
                background: #64b5f6;
                width: 20px;
                height: 20px;
                margin: -6px 0;
                border-radius: 10px;
            }
            
            QSlider#demoSlider::handle:horizontal:hover {
                background: #90caf9;
            }
            
            QSlider#demoSlider::sub-page:horizontal {
                background: #64b5f6;
                border-radius: 4px;
            }
            
            /* ==================== 进度条 ==================== */
            QProgressBar#demoProgressBar {
                border: 2px solid #546e7a;
                border-radius: 6px;
                text-align: center;
                height: 25px;
                color: #eceff1;
            }
            
            QProgressBar#demoProgressBar::chunk {
                background-color: #66bb6a;
                border-radius: 4px;
            }
            
            /* ==================== 按钮 - 主要 ==================== */
            QPushButton#primaryButton {
                background-color: #2196f3;
                color: white;
                border: none;
                border-radius: 6px;
                padding: 10px 20px;
                font-weight: bold;
                min-width: 100px;
            }
            
            QPushButton#primaryButton:hover {
                background-color: #42a5f5;
            }
            
            QPushButton#primaryButton:pressed {
                background-color: #1565c0;
            }
            
            /* ==================== 按钮 - 成功 ==================== */
            QPushButton#successButton {
                background-color: #4caf50;
                color: white;
                border: none;
                border-radius: 6px;
                padding: 10px 20px;
                font-weight: bold;
                min-width: 100px;
            }
            
            QPushButton#successButton:hover {
                background-color: #66bb6a;
            }
            
            QPushButton#successButton:pressed {
                background-color: #2e7d32;
            }
            
            /* ==================== 按钮 - 危险 ==================== */
            QPushButton#dangerButton {
                background-color: #f44336;
                color: white;
                border: none;
                border-radius: 6px;
                padding: 10px 20px;
                font-weight: bold;
                min-width: 100px;
            }
            
            QPushButton#dangerButton:hover {
                background-color: #ef5350;
            }
            
            QPushButton#dangerButton:pressed {
                background-color: #c62828;
            }
            
            /* ==================== 按钮 - 禁用 ==================== */
            QPushButton#disabledButton {
                background-color: #546e7a;
                color: #90a4ae;
                border: none;
                border-radius: 6px;
                padding: 10px 20px;
                font-weight: bold;
                min-width: 100px;
            }
            
            /* ==================== 主题切换按钮 ==================== */
            QPushButton {
                background-color: #455a64;
                border: 2px solid #546e7a;
                border-radius: 6px;
                padding: 8px 16px;
                color: #eceff1;
            }
            
            QPushButton:hover {
                background-color: #546e7a;
                border-color: #64b5f6;
            }
            
            /* ==================== 文本编辑区 ==================== */
            QTextEdit#demoTextEdit {
                background-color: #455a64;
                border: 2px solid #546e7a;
                border-radius: 6px;
                padding: 10px;
                color: #eceff1;
                line-height: 1.5;
            }
            
            QTextEdit#demoTextEdit:focus {
                border-color: #64b5f6;
            }
            
            /* ==================== 状态栏 ==================== */
            QStatusBar {
                background-color: #37474f;
                color: #b0bec5;
                border-top: 1px solid #455a64;
            }
        )";
        
        qApp->setStyleSheet(qss);
    }
    
    // 应用蓝色主题
    void applyBlueTheme() {
        QString qss = R"(
            /* ==================== 全局样式 ==================== */
            QWidget {
                font-family: "Microsoft YaHei", "SimHei", sans-serif;
                font-size: 14px;
            }
            
            /* ==================== 主窗口 ==================== */
            QMainWindow {
                background-color: #e8eaf6;
            }
            
            /* ==================== 分组框 ==================== */
            QGroupBox {
                background-color: #ffffff;
                border: 2px solid #c5cae9;
                border-radius: 8px;
                margin-top: 12px;
                padding-top: 10px;
                font-weight: bold;
                color: #3f51b5;
            }
            
            QGroupBox::title {
                subcontrol-origin: margin;
                left: 10px;
                padding: 0 5px;
            }
            
            /* ==================== 标签 ==================== */
            QLabel#demoLabel {
                background: qlineargradient(x1:0, y1:0, x2:1, y2:0, 
                    stop:0 #3f51b5, stop:1 #9c27b0);
                color: #ffffff;
                padding: 15px;
                border-radius: 6px;
                font-size: 16px;
                font-weight: bold;
            }
            
            /* ==================== 输入框 ==================== */
            QLineEdit#demoLineEdit {
                background-color: #ffffff;
                border: 2px solid #c5cae9;
                border-radius: 6px;
                padding: 10px;
                color: #3f51b5;
            }
            
            QLineEdit#demoLineEdit:focus {
                border-color: #3f51b5;
                background-color: #e8eaf6;
            }
            
            QLineEdit#demoLineEdit:hover {
                border-color: #7986cb;
            }
            
            /* ==================== 下拉框 ==================== */
            QComboBox#demoComboBox {
                background-color: #ffffff;
                border: 2px solid #c5cae9;
                border-radius: 6px;
                padding: 8px;
                min-width: 120px;
                color: #3f51b5;
            }
            
            QComboBox#demoComboBox:hover {
                border-color: #7986cb;
            }
            
            QComboBox#demoComboBox::drop-down {
                border: none;
                width: 30px;
            }
            
            QComboBox#demoComboBox::down-arrow {
                image: none;
                border-left: 5px solid transparent;
                border-right: 5px solid transparent;
                border-top: 8px solid #3f51b5;
                margin-right: 10px;
            }
            
            QComboBox#demoComboBox QAbstractItemView {
                background-color: #ffffff;
                border: 1px solid #c5cae9;
                selection-background-color: #3f51b5;
                selection-color: white;
            }
            
            /* ==================== 滑动条 ==================== */
            QSlider#demoSlider::groove:horizontal {
                height: 8px;
                background: #c5cae9;
                border-radius: 4px;
            }
            
            QSlider#demoSlider::handle:horizontal {
                background: qradialgradient(cx:0.5, cy:0.5, radius:0.5,
                    stop:0 #3f51b5, stop:1 #9c27b0);
                width: 20px;
                height: 20px;
                margin: -6px 0;
                border-radius: 10px;
                border: 2px solid #ffffff;
            }
            
            QSlider#demoSlider::handle:horizontal:hover {
                background: qradialgradient(cx:0.5, cy:0.5, radius:0.5,
                    stop:0 #5c6bc0, stop:1 #ab47bc);
            }
            
            QSlider#demoSlider::sub-page:horizontal {
                background: qlineargradient(x1:0, y1:0, x2:1, y2:0,
                    stop:0 #3f51b5, stop:1 #9c27b0);
                border-radius: 4px;
            }
            
            /* ==================== 进度条 ==================== */
            QProgressBar#demoProgressBar {
                border: 2px solid #c5cae9;
                border-radius: 6px;
                text-align: center;
                height: 25px;
                color: #3f51b5;
            }
            
            QProgressBar#demoProgressBar::chunk {
                background-color: #9c27b0;
                border-radius: 4px;
            }
            
            /* ==================== 按钮 - 主要 ==================== */
            QPushButton#primaryButton {
                background: qlineargradient(x1:0, y1:0, x2:0, y2:1,
                    stop:0 #3f51b5, stop:1 #303f9f);
                color: white;
                border: none;
                border-radius: 6px;
                padding: 10px 20px;
                font-weight: bold;
                min-width: 100px;
            }
            
            QPushButton#primaryButton:hover {
                background: qlineargradient(x1:0, y1:0, x2:0, y2:1,
                    stop:0 #5c6bc0, stop:1 #3949ab);
            }
            
            QPushButton#primaryButton:pressed {
                background: qlineargradient(x1:0, y1:0, x2:0, y2:1,
                    stop:0 #283593, stop:1 #1a237e);
            }
            
            /* ==================== 按钮 - 成功 ==================== */
            QPushButton#successButton {
                background: qlineargradient(x1:0, y1:0, x2:0, y2:1,
                    stop:0 #9c27b0, stop:1 #7b1fa2);
                color: white;
                border: none;
                border-radius: 6px;
                padding: 10px 20px;
                font-weight: bold;
                min-width: 100px;
            }
            
            QPushButton#successButton:hover {
                background: qlineargradient(x1:0, y1:0, x2:0, y2:1,
                    stop:0 #ab47bc, stop:1 #8e24aa);
            }
            
            QPushButton#successButton:pressed {
                background: qlineargradient(x1:0, y1:0, x2:0, y2:1,
                    stop:0 #7b1fa2, stop:1 #4a148c);
            }
            
            /* ==================== 按钮 - 危险 ==================== */
            QPushButton#dangerButton {
                background: qlineargradient(x1:0, y1:0, x2:0, y2:1,
                    stop:0 #e91e63, stop:1 #c2185b);
                color: white;
                border: none;
                border-radius: 6px;
                padding: 10px 20px;
                font-weight: bold;
                min-width: 100px;
            }
            
            QPushButton#dangerButton:hover {
                background: qlineargradient(x1:0, y1:0, x2:0, y2:1,
                    stop:0 #f06292, stop:1 #d81b60);
            }
            
            QPushButton#dangerButton:pressed {
                background: qlineargradient(x1:0, y1:0, x2:0, y2:1,
                    stop:0 #c2185b, stop:1 #880e4f);
            }
            
            /* ==================== 按钮 - 禁用 ==================== */
            QPushButton#disabledButton {
                background-color: #e8eaf6;
                color: #9fa8da;
                border: 2px solid #c5cae9;
                border-radius: 6px;
                padding: 10px 20px;
                font-weight: bold;
                min-width: 100px;
            }
            
            /* ==================== 主题切换按钮 ==================== */
            QPushButton {
                background-color: #ffffff;
                border: 2px solid #c5cae9;
                border-radius: 6px;
                padding: 8px 16px;
                color: #3f51b5;
            }
            
            QPushButton:hover {
                background-color: #e8eaf6;
                border-color: #3f51b5;
            }
            
            /* ==================== 文本编辑区 ==================== */
            QTextEdit#demoTextEdit {
                background-color: #ffffff;
                border: 2px solid #c5cae9;
                border-radius: 6px;
                padding: 10px;
                color: #3f51b5;
                line-height: 1.5;
            }
            
            QTextEdit#demoTextEdit:focus {
                border-color: #3f51b5;
            }
            
            /* ==================== 状态栏 ==================== */
            QStatusBar {
                background-color: #3f51b5;
                color: #ffffff;
                border-top: 1px solid #c5cae9;
            }
        )";
        
        qApp->setStyleSheet(qss);
    }
};

#include "main.moc"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    
    QssDemoWindow window;
    window.show();
    
    return app.exec();
}
