#include <QApplication>
#include <QMainWindow>
#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QComboBox>
#include <QLineEdit>
#include <QGroupBox>
#include <QMessageBox>
#include <QStatusBar>
#include <QTranslator>
#include <QLocale>
#include <QDebug>
#include <QDir>

// 主窗口类
class I18nDemoWindow : public QMainWindow {
    Q_OBJECT
    
public:
    explicit I18nDemoWindow(QWidget* parent = nullptr) : QMainWindow(parent) {
        setupUI();
        updateTexts(); // 初始化界面文字
    }
    
    // 设置翻译器
    void setTranslator(QTranslator* translator) {
        m_translator = translator;
    }
    
private:
    void setupUI() {
        setWindowTitle("Qt Internationalization Demo");
        setMinimumSize(500, 400);
        
        // 中心部件
        QWidget* centralWidget = new QWidget(this);
        setCentralWidget(centralWidget);
        
        QVBoxLayout* mainLayout = new QVBoxLayout(centralWidget);
        
        // ===== 1. 语言选择区域 =====
        QGroupBox* langGroup = new QGroupBox(this);
        QHBoxLayout* langLayout = new QHBoxLayout(langGroup);
        
        m_langLabel = new QLabel(this);
        m_langCombo = new QComboBox(this);
        m_langCombo->addItem("English", "en");
        m_langCombo->addItem("中文", "zh_CN");
        
        langLayout->addWidget(m_langLabel);
        langLayout->addWidget(m_langCombo);
        langLayout->addStretch();
        
        connect(m_langCombo, QOverload<int>::of(&QComboBox::currentIndexChanged),
                this, &I18nDemoWindow::onLanguageChanged);
        
        // ===== 2. 用户登录表单区域 =====
        QGroupBox* formGroup = new QGroupBox(this);
        QVBoxLayout* formLayout = new QVBoxLayout(formGroup);
        
        // 用户名
        QHBoxLayout* userLayout = new QHBoxLayout();
        m_userLabel = new QLabel(this);
        m_userEdit = new QLineEdit(this);
        userLayout->addWidget(m_userLabel);
        userLayout->addWidget(m_userEdit);
        
        // 密码
        QHBoxLayout* pwdLayout = new QHBoxLayout();
        m_pwdLabel = new QLabel(this);
        m_pwdEdit = new QLineEdit(this);
        m_pwdEdit->setEchoMode(QLineEdit::Password);
        pwdLayout->addWidget(m_pwdLabel);
        pwdLayout->addWidget(m_pwdEdit);
        
        // 邮箱
        QHBoxLayout* emailLayout = new QHBoxLayout();
        m_emailLabel = new QLabel(this);
        m_emailEdit = new QLineEdit(this);
        emailLayout->addWidget(m_emailLabel);
        emailLayout->addWidget(m_emailEdit);
        
        formLayout->addLayout(userLayout);
        formLayout->addLayout(pwdLayout);
        formLayout->addLayout(emailLayout);
        
        // ===== 3. 按钮区域 =====
        QHBoxLayout* btnLayout = new QHBoxLayout();
        m_loginBtn = new QPushButton(this);
        m_clearBtn = new QPushButton(this);
        m_aboutBtn = new QPushButton(this);
        
        btnLayout->addWidget(m_loginBtn);
        btnLayout->addWidget(m_clearBtn);
        btnLayout->addWidget(m_aboutBtn);
        btnLayout->addStretch();
        
        connect(m_loginBtn, &QPushButton::clicked, this, &I18nDemoWindow::onLogin);
        connect(m_clearBtn, &QPushButton::clicked, this, &I18nDemoWindow::onClear);
        connect(m_aboutBtn, &QPushButton::clicked, this, &I18nDemoWindow::onAbout);
        
        // ===== 4. 说明标签 =====
        m_infoLabel = new QLabel(this);
        m_infoLabel->setWordWrap(true);
        m_infoLabel->setStyleSheet("color: #666; margin-top: 20px;");
        
        // 组装主布局
        mainLayout->addWidget(langGroup);
        mainLayout->addWidget(formGroup);
        mainLayout->addLayout(btnLayout);
        mainLayout->addWidget(m_infoLabel);
        mainLayout->addStretch();
    }
    
    // 更新所有界面文字（当语言切换时调用）
    void updateTexts() {
        // 窗口标题
        setWindowTitle(tr("Qt Internationalization Demo"));
        
        // 语言选择
        // 注意：语言名称通常保持原样，不翻译
        
        // 表单标签
        m_userLabel->setText(tr("Username:"));
        m_pwdLabel->setText(tr("Password:"));
        m_emailLabel->setText(tr("Email:"));
        
        // 按钮文字
        m_loginBtn->setText(tr("Login"));
        m_clearBtn->setText(tr("Clear"));
        m_aboutBtn->setText(tr("About"));
        
        // 输入框提示文字
        m_userEdit->setPlaceholderText(tr("Enter username"));
        m_pwdEdit->setPlaceholderText(tr("Enter password"));
        m_emailEdit->setPlaceholderText(tr("Enter email"));
        
        // 信息标签
        m_infoLabel->setText(tr("This demo shows how to use Qt's internationalization (i18n) system. "
                                "Select a language from the dropdown above to see the interface change. "
                                "All text is marked with tr() for translation."));
    }
    
private slots:
    // 语言切换
    void onLanguageChanged(int index) {
        QString langCode = m_langCombo->itemData(index).toString();
        
        if (m_translator) {
            // 移除旧翻译器
            qApp->removeTranslator(m_translator);
            
            // 加载新翻译文件
            QString qmFile = QString(":/translations/day09_i18n_%1.qm").arg(langCode);
            
            // 先尝试从资源文件加载，失败后从文件系统加载
            if (m_translator->load(qmFile)) {
                qDebug() << "Loaded translation from resources:" << qmFile;
            } else {
                // 从文件系统加载
                qmFile = QString("translations/day09_i18n_%1.qm").arg(langCode);
                if (m_translator->load(qmFile)) {
                    qDebug() << "Loaded translation from file:" << qmFile;
                } else {
                    qDebug() << "Failed to load translation:" << qmFile;
                    QMessageBox::warning(this, tr("Warning"), 
                        tr("Failed to load translation file for %1").arg(langCode));
                    return;
                }
            }
            
            // 安装新翻译器
            qApp->installTranslator(m_translator);
            
            // 刷新界面文字
            updateTexts();
            
            // 刷新所有子控件
            update();
        }
    }
    
    // 登录按钮
    void onLogin() {
        QString user = m_userEdit->text();
        
        if (user.isEmpty()) {
            QMessageBox::warning(this, tr("Warning"), 
                tr("Please enter a username!"));
            return;
        }
        
        QMessageBox::information(this, tr("Login Success"), 
            tr("Welcome, %1!").arg(user));
    }
    
    // 清空按钮
    void onClear() {
        m_userEdit->clear();
        m_pwdEdit->clear();
        m_emailEdit->clear();
        
        // 使用带数字的翻译
        QString msg = tr("Cleared %1 fields", "", 3).arg(3);
        statusBar()->showMessage(msg, 2000);
    }
    
    // 关于按钮
    void onAbout() {
        QMessageBox::about(this, tr("About"), 
            tr("<h2>Qt i18n Demo</h2>"
               "<p>Version 1.0</p>"
               "<p>This application demonstrates Qt's internationalization capabilities.</p>"));
    }
    
private:
    // 界面控件
    QLabel* m_langLabel;
    QComboBox* m_langCombo;
    
    QLabel* m_userLabel;
    QLabel* m_pwdLabel;
    QLabel* m_emailLabel;
    
    QLineEdit* m_userEdit;
    QLineEdit* m_pwdEdit;
    QLineEdit* m_emailEdit;
    
    QPushButton* m_loginBtn;
    QPushButton* m_clearBtn;
    QPushButton* m_aboutBtn;
    
    QLabel* m_infoLabel;
    
    QTranslator* m_translator = nullptr;
};

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);
    
    // 设置应用程序信息（用于查找翻译文件）
    app.setApplicationName("day09_i18n");
    app.setOrganizationName("qt-study");
    
    // 设置默认本地化
    QLocale locale = QLocale::system();
    qDebug() << "System locale:" << locale.name();
    
    // 创建并加载翻译器
    QTranslator translator;
    
    // 尝试加载系统语言的翻译
    QString qmFile = QString("translations/day09_i18n_%1.qm").arg(locale.name());
    if (translator.load(qmFile)) {
        qDebug() << "Loaded system translation:" << qmFile;
        app.installTranslator(&translator);
    } else {
        qDebug() << "Using default language (English)";
    }
    
    // 创建主窗口
    I18nDemoWindow window;
    window.setTranslator(&translator);
    window.show();
    
    return app.exec();
}

#include "main.moc"
