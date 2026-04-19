/******************************************************************************
 * Day 03: 常用控件 (Common Widgets)
 *
 * 学习目标：
 * - 掌握常用控件的基本用法
 * - 理解控件的信号与槽
 * - 学会使用水平布局和表单布局
 * - 实现用户注册表单
 ******************************************************************************/

#include <QApplication>
#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QCheckBox>
#include <QRadioButton>
#include <QButtonGroup>
#include <QComboBox>
#include <QSlider>
#include <QProgressBar>
#include <QTextEdit>
#include <QDebug>
#include <QGroupBox>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    // 创建主窗口
    QWidget window;
    window.setWindowTitle("Day03: 用户注册表单");
    window.resize(450, 500);

    // 主布局：垂直布局
    QVBoxLayout *mainLayout = new QVBoxLayout(&window);

    // ==================== 标题 ====================
    QLabel *titleLabel = new QLabel("用户注册");
    QFont titleFont = titleLabel->font();
    titleFont.setPointSize(16);
    titleFont.setBold(true);
    titleLabel->setFont(titleFont);
    titleLabel->setAlignment(Qt::AlignCenter);
    mainLayout->addWidget(titleLabel);

    // ==================== 表单区域 ====================
    QFormLayout *formLayout = new QFormLayout();

    // 用户名
    QLineEdit *usernameEdit = new QLineEdit();
    usernameEdit->setPlaceholderText("请输入用户名");
    formLayout->addRow("用户名:", usernameEdit);

    // 密码
    QLineEdit *passwordEdit = new QLineEdit();
    passwordEdit->setPlaceholderText("请输入密码");
    passwordEdit->setEchoMode(QLineEdit::Password);  // 密码模式
    formLayout->addRow("密码:", passwordEdit);

    // 确认密码
    QLineEdit *confirmEdit = new QLineEdit();
    confirmEdit->setPlaceholderText("请再次输入密码");
    confirmEdit->setEchoMode(QLineEdit::Password);
    formLayout->addRow("确认密码:", confirmEdit);

    mainLayout->addLayout(formLayout);

    // ==================== 性别选择 ====================
    QGroupBox *genderGroup = new QGroupBox("性别");
    QHBoxLayout *genderLayout = new QHBoxLayout();

    QRadioButton *maleRadio = new QRadioButton("男");
    QRadioButton *femaleRadio = new QRadioButton("女");
    maleRadio->setChecked(true);  // 默认选中男
`
    genderLayout->addWidget(maleRadio);
    genderLayout->addWidget(femaleRadio);
    genderLayout->addStretch();  // 弹性空间
    genderGroup->setLayout(genderLayout);
    mainLayout->addWidget(genderGroup);

    // ==================== 爱好选择 ====================
    QGroupBox *hobbyGroup = new QGroupBox("爱好（可多选）");
    QHBoxLayout *hobbyLayout = new QHBoxLayout();

    QCheckBox *swimCheck = new QCheckBox("游泳");
    QCheckBox *musicCheck = new QCheckBox("音乐");
    QCheckBox *readCheck = new QCheckBox("阅读");
    QCheckBox *sportCheck = new QCheckBox("运动");

    hobbyLayout->addWidget(swimCheck);
    hobbyLayout->addWidget(musicCheck);
    hobbyLayout->addWidget(readCheck);
    hobbyLayout->addWidget(sportCheck);
    hobbyLayout->addStretch();
    hobbyGroup->setLayout(hobbyLayout);
    mainLayout->addWidget(hobbyGroup);

    // ==================== 城市选择 ====================
    QHBoxLayout *cityLayout = new QHBoxLayout();
    QLabel *cityLabel = new QLabel("城市:");
    QComboBox *cityCombo = new QComboBox();
    cityCombo->addItem("北京");
    cityCombo->addItem("上海");
    cityCombo->addItem("广州");
    cityCombo->addItem("深圳");
    cityCombo->addItem("杭州");
    cityCombo->setCurrentIndex(1);  // 默认选择上海

    cityLayout->addWidget(cityCombo);
    cityLayout->addWidget(cityLabel);
    cityLayout->addStretch();
    mainLayout->addLayout(cityLayout);

    // ==================== 年龄滑动条 ====================
    QHBoxLayout *ageLayout = new QHBoxLayout();
    QLabel *ageLabel = new QLabel("年龄:");
    QSlider *ageSlider = new QSlider(Qt::Horizontal);
    ageSlider->setRange(18, 60);  // 年龄范围18-60
    ageSlider->setValue(25);      // 默认值25
    QLabel *ageValueLabel = new QLabel("25");

    ageLayout->addWidget(ageLabel);
    ageLayout->addWidget(ageSlider);
    ageLayout->addWidget(ageValueLabel);
    mainLayout->addLayout(ageLayout);

    // ==================== 自我介绍 ====================
    QLabel *introLabel = new QLabel("自我介绍:");
    mainLayout->addWidget(introLabel);

    QTextEdit *introEdit = new QTextEdit();
    introEdit->setPlaceholderText("请简单介绍你自己...");
    introEdit->setMaximumHeight(80);
    mainLayout->addWidget(introEdit);

    // ==================== 进度条 ====================
    QLabel *progressLabel = new QLabel("填写进度:");
    mainLayout->addWidget(progressLabel);

    QProgressBar *progressBar = new QProgressBar();
    progressBar->setRange(0, 100);
    progressBar->setValue(0);
    mainLayout->addWidget(progressBar);

    // ==================== 按钮区域 ====================
    QHBoxLayout *buttonLayout = new QHBoxLayout();
    QPushButton *submitBtn = new QPushButton("提交");
    QPushButton *resetBtn = new QPushButton("重置");
    QPushButton *closeBtn = new QPushButton("关闭");

    buttonLayout->addWidget(submitBtn);
    buttonLayout->addWidget(resetBtn);
    buttonLayout->addWidget(closeBtn);
    mainLayout->addLayout(buttonLayout);

    // ==================== 状态标签 ====================
    QLabel *statusLabel = new QLabel("请填写注册信息");
    statusLabel->setAlignment(Qt::AlignCenter);
    mainLayout->addWidget(statusLabel);

    // ==================== 信号与槽连接 ====================

    // 【示例1】滑动条改变时更新年龄显示
    QObject::connect(ageSlider, &QSlider::valueChanged, [&](int value) {
        ageValueLabel->setText(QString::number(value));
    });

    // 【示例2】计算填写进度
    auto updateProgress = [&]() {
        int progress = 0;
        if (!usernameEdit->text().isEmpty()) progress += 20;
        if (!passwordEdit->text().isEmpty()) progress += 20;
        if (!confirmEdit->text().isEmpty()) progress += 20;
        if (!introEdit->toPlainText().isEmpty()) progress += 20;
        if (swimCheck->isChecked() || musicCheck->isChecked() ||
            readCheck->isChecked() || sportCheck->isChecked()) progress += 20;

        progressBar->setValue(progress);
    };

    // 连接多个控件的信号到同一个槽
    QObject::connect(usernameEdit, &QLineEdit::textChanged, updateProgress);
    QObject::connect(passwordEdit, &QLineEdit::textChanged, updateProgress);
    QObject::connect(confirmEdit, &QLineEdit::textChanged, updateProgress);
    QObject::connect(introEdit, &QTextEdit::textChanged, updateProgress);
    QObject::connect(swimCheck, &QCheckBox::stateChanged, updateProgress);
    QObject::connect(musicCheck, &QCheckBox::stateChanged, updateProgress);
    QObject::connect(readCheck, &QCheckBox::stateChanged, updateProgress);
    QObject::connect(sportCheck, &QCheckBox::stateChanged, updateProgress);

    // 【示例3】提交按钮
    QObject::connect(submitBtn, &QPushButton::clicked, [&]() {
        // 验证输入
        if (usernameEdit->text().isEmpty()) {
            statusLabel->setText("错误：用户名不能为空！");
            return;
        }
        if (passwordEdit->text().isEmpty()) {
            statusLabel->setText("错误：密码不能为空！");
            return;
        }
        if (passwordEdit->text() != confirmEdit->text()) {
            statusLabel->setText("错误：两次输入的密码不一致！");
            return;
        }

        // 收集信息
        QString gender = maleRadio->isChecked() ? "男" : "女";
        QString city = cityCombo->currentText();
        int age = ageSlider->value();

        QString hobbies;
        if (swimCheck->isChecked()) hobbies += "游泳 ";
        if (musicCheck->isChecked()) hobbies += "音乐 ";
        if (readCheck->isChecked()) hobbies += "阅读 ";
        if (sportCheck->isChecked()) hobbies += "运动 ";

        // 输出注册信息
        qDebug() << "===== 注册信息 =====";
        qDebug() << "用户名:" << usernameEdit->text();
        qDebug() << "性别:" << gender;
        qDebug() << "城市:" << city;
        qDebug() << "年龄:" << age;
        qDebug() << "爱好:" << hobbies;
        qDebug() << "自我介绍:" << introEdit->toPlainText();

        statusLabel->setText("注册成功！信息已输出到控制台");
    });

    // 【示例4】重置按钮
    QObject::connect(resetBtn, &QPushButton::clicked, [&]() {
        usernameEdit->clear();
        passwordEdit->clear();
        confirmEdit->clear();
        introEdit->clear();
        maleRadio->setChecked(true);
        swimCheck->setChecked(false);
        musicCheck->setChecked(false);
        readCheck->setChecked(false);
        sportCheck->setChecked(false);
        cityCombo->setCurrentIndex(1);
        ageSlider->setValue(25);
        statusLabel->setText("已重置，请重新填写");
    });

    // 【示例5】关闭按钮
    QObject::connect(closeBtn, &QPushButton::clicked, &window, &QWidget::close);

    // 显示窗口
    window.show();

    qDebug() << "Day03程序已启动 - 用户注册表单";

    return app.exec();
}
