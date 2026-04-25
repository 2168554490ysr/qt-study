#include <QApplication>
#include <QMainWindow>
#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QComboBox>
#include <QGroupBox>
#include <QTextEdit>
#include <QFile>
#include <QDebug>
#include <QIcon>
#include <QPixmap>
#include <QMessageBox>

// 资源系统演示窗口
class ResourceDemoWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit ResourceDemoWindow(QWidget* parent = nullptr) : QMainWindow(parent) {
        setupUI();
        loadDefaultStyle();
    }

private:
    void setupUI() {
        setWindowTitle("Qt Resource System Demo");
        setMinimumSize(600, 500);

        // 设置窗口图标（从资源文件加载）
        QIcon appIcon = QIcon(":/icons/resources/icons/app_icon.png");
        setWindowIcon(appIcon);

        // 中心部件
        QWidget* centralWidget = new QWidget(this);
        setCentralWidget(centralWidget);

        QVBoxLayout* mainLayout = new QVBoxLayout(centralWidget);

        // ===== 1. 主题切换区域 =====
        QGroupBox* themeGroup = new QGroupBox("Theme Settings", this);
        QHBoxLayout* themeLayout = new QHBoxLayout(themeGroup);

        QLabel* themeLabel = new QLabel("Select Theme:", this);
        m_themeCombo = new QComboBox(this);
        m_themeCombo->addItem("Light", ":/styles/resources/styles/light.qss");
        m_themeCombo->addItem("Dark", ":/styles/resources/styles/dark.qss");
        m_themeCombo->addItem("Blue", ":/styles/resources/styles/blue.qss");

        themeLayout->addWidget(themeLabel);
        themeLayout->addWidget(m_themeCombo);
        themeLayout->addStretch();

        connect(m_themeCombo, QOverload<int>::of(&QComboBox::currentIndexChanged),
                this, &ResourceDemoWindow::onThemeChanged);

        // ===== 2. 图标演示区域 =====
        QGroupBox* iconGroup = new QGroupBox("Icon Resources", this);
        QVBoxLayout* iconLayout = new QVBoxLayout(iconGroup);

        // 创建带图标的按钮
        QHBoxLayout* btnLayout = new QHBoxLayout();

        QPushButton* newBtn = new QPushButton("New File", this);
        newBtn->setIcon(QIcon(":/icons/resources/icons/new_file.png"));
        newBtn->setIconSize(QSize(24, 24));

        QPushButton* openBtn = new QPushButton("Open File", this);
        openBtn->setIcon(QIcon(":/icons/resources/icons/open_file.png"));
        openBtn->setIconSize(QSize(24, 24));

        QPushButton* saveBtn = new QPushButton("Save File", this);
        saveBtn->setIcon(QIcon(":/icons/resources/icons/save_file.png"));
        saveBtn->setIconSize(QSize(24, 24));

        QPushButton* settingsBtn = new QPushButton("Settings", this);
        settingsBtn->setIcon(QIcon(":/icons/resources/icons/settings.png"));
        settingsBtn->setIconSize(QSize(24, 24));

        btnLayout->addWidget(newBtn);
        btnLayout->addWidget(openBtn);
        btnLayout->addWidget(saveBtn);
        btnLayout->addWidget(settingsBtn);
        btnLayout->addStretch();

        iconLayout->addLayout(btnLayout);

        // 图标信息显示
        m_iconInfoLabel = new QLabel(this);
        m_iconInfoLabel->setWordWrap(true);
        iconLayout->addWidget(m_iconInfoLabel);

        updateIconInfo();

        // ===== 3. 样式表内容显示区域 =====
        QGroupBox* styleGroup = new QGroupBox("Current Stylesheet Content", this);
        QVBoxLayout* styleLayout = new QVBoxLayout(styleGroup);

        m_styleContentEdit = new QTextEdit(this);
        m_styleContentEdit->setReadOnly(true);
        m_styleContentEdit->setMaximumHeight(200);

        styleLayout->addWidget(m_styleContentEdit);

        // ===== 4. 资源信息显示区域 =====
        QGroupBox* infoGroup = new QGroupBox("Resource Information", this);
        QVBoxLayout* infoLayout = new QVBoxLayout(infoGroup);

        m_resourceInfoLabel = new QLabel(this);
        m_resourceInfoLabel->setWordWrap(true);
        m_resourceInfoLabel->setStyleSheet("color: #666;");

        infoLayout->addWidget(m_resourceInfoLabel);

        updateResourceInfo();

        // ===== 5. 操作按钮区域 =====
        QHBoxLayout* actionLayout = new QHBoxLayout();

        QPushButton* reloadStyleBtn = new QPushButton("Reload Stylesheet", this);
        QPushButton* checkResourceBtn = new QPushButton("Check Resources", this);
        QPushButton* aboutBtn = new QPushButton("About", this);
        aboutBtn->setIcon(QIcon(":/icons/resources/icons/help.png"));

        actionLayout->addWidget(reloadStyleBtn);
        actionLayout->addWidget(checkResourceBtn);
        actionLayout->addWidget(aboutBtn);
        actionLayout->addStretch();

        connect(reloadStyleBtn, &QPushButton::clicked, this, &ResourceDemoWindow::loadDefaultStyle);
        connect(checkResourceBtn, &QPushButton::clicked, this, &ResourceDemoWindow::checkResources);
        connect(aboutBtn, &QPushButton::clicked, this, &ResourceDemoWindow::showAbout);

        // 组装主布局
        mainLayout->addWidget(themeGroup);
        mainLayout->addWidget(iconGroup);
        mainLayout->addWidget(styleGroup);
        mainLayout->addWidget(infoGroup);
        mainLayout->addLayout(actionLayout);

        // 连接按钮信号
        connect(newBtn, &QPushButton::clicked, []() {
            QMessageBox::information(nullptr, "New File", "Creating new file...");
        });
        connect(openBtn, &QPushButton::clicked, []() {
            QMessageBox::information(nullptr, "Open File", "Opening file...");
        });
        connect(saveBtn, &QPushButton::clicked, []() {
            QMessageBox::information(nullptr, "Save File", "Saving file...");
        });
        connect(settingsBtn, &QPushButton::clicked, []() {
            QMessageBox::information(nullptr, "Settings", "Opening settings...");
        });
    }

    // 加载默认样式
    void loadDefaultStyle() {
        QString stylePath = m_themeCombo->currentData().toString();
        applyStylesheet(stylePath);
    }

    // 应用样式表
    void applyStylesheet(const QString& path) {
        // 从资源文件读取样式表
        QFile file(path);
        if (file.open(QFile::ReadOnly)) {
            QString styleSheet = QLatin1String(file.readAll());
            qApp->setStyleSheet(styleSheet);
            file.close();

            // 显示样式内容
            m_styleContentEdit->setText(styleSheet);

            qDebug() << "Applied stylesheet from:" << path;
        } else {
            qDebug() << "Failed to load stylesheet:" << path;
            m_styleContentEdit->setText("Failed to load stylesheet!");
        }
    }

    // 更新图标信息
    void updateIconInfo() {
        QString info = "<b>Available Icons:</b><br>"
                       "• :/icons/resources/icons/app_icon.png - Application icon<br>"
                       "• :/icons/resources/icons/new_file.png - New file icon<br>"
                       "• :/icons/resources/icons/open_file.png - Open file icon<br>"
                       "• :/icons/resources/icons/save_file.png - Save file icon<br>"
                       "• :/icons/resources/icons/settings.png - Settings icon<br>"
                       "• :/icons/resources/icons/exit.png - Exit icon<br>"
                       "• :/icons/resources/icons/help.png - Help icon";
        m_iconInfoLabel->setText(info);
    }

    // 更新资源信息
    void updateResourceInfo() {
        QString info = "<b>Resource System Benefits:</b><br>"
                       "1. All resources are compiled into the executable<br>"
                       "2. No external files needed at runtime<br>"
                       "3. Access via <code>qrc:/</code> or <code>:/</code> prefix<br>"
                       "4. Supports: icons, images, stylesheets, translations, data files<br><br>"
                       "<b>Usage:</b> <code>QIcon(\":/icons/resources/icons/app_icon.png\")</code>";
        m_resourceInfoLabel->setText(info);
    }

private slots:
    // 主题切换
    void onThemeChanged(int index) {
        QString stylePath = m_themeCombo->itemData(index).toString();
        applyStylesheet(stylePath);

        qDebug() << "Theme changed to:" << m_themeCombo->currentText()
                 << "Path:" << stylePath;
    }

    // 检查资源
    void checkResources() {
        QStringList resources;
        resources << ":/icons/resources/icons/app_icon.png"
                  << ":/icons/resources/icons/new_file.png"
                  << ":/icons/resources/icons/open_file.png"
                  << ":/icons/resources/icons/save_file.png"
                  << ":/icons/resources/icons/settings.png"
                  << ":/icons/resources/icons/exit.png"
                  << ":/icons/resources/icons/help.png"
                  << ":/styles/resources/styles/light.qss"
                  << ":/styles/resources/styles/dark.qss"
                  << ":/styles/resources/styles/blue.qss";

        QString result = "<b>Resource Check Results:</b><br>";
        for (const QString& res : resources) {
            QFile file(res);
            bool exists = file.exists();
            result += QString("• %1: %2<br>").arg(res).arg(exists ? "✓ OK" : "✗ Not Found");
        }

        QMessageBox::information(this, "Resource Check", result);
    }

    // 关于对话框
    void showAbout() {
        QMessageBox::about(this, "About Resource System Demo",
            "<h2>Qt Resource System Demo</h2>"
            "<p>Version 1.0</p>"
            "<p>This demo shows how to use Qt's resource system (.qrc files) "
            "to embed icons, stylesheets, and other files into the executable.</p>"
            "<p><b>Key Concepts:</b></p>"
            "<ul>"
            "<li>.qrc resource collection files</li>"
            "<li>Accessing resources with :/ prefix</li>"
            "<li>Loading stylesheets from resources</li>"
            "<li>Using icons from resources</li>"
            "</ul>");
    }

private:
    QComboBox* m_themeCombo;
    QTextEdit* m_styleContentEdit;
    QLabel* m_iconInfoLabel;
    QLabel* m_resourceInfoLabel;
};

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);

    // 设置应用程序信息
    app.setApplicationName("day10_resources");
    app.setOrganizationName("qt-study");

    qDebug() << "Starting Resource System Demo...";
    qDebug() << "Resources are embedded in the executable via .qrc file";

    // 创建主窗口
    ResourceDemoWindow window;
    window.show();

    return app.exec();
}

#include "main.moc"
