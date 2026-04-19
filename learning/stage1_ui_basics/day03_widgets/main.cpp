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
    window.setWindowTitle("Day03: 常用控件");
    window.resize(400, 300);
    
    // 创建垂直布局
    QVBoxLayout *mainLayout = new QVBoxLayout(&window);
    
    // ==================== 标题 ====================
    // 创建标签显示标题文字
    QLabel *titleLabel = new QLabel("用户注册");
    
    // 获取标签当前字体，并修改字体属性
    QFont titleFont = titleLabel->font();
    titleFont.setPointSize(16);   // 设置字号为16磅
    titleFont.setBold(true);       // 设置为粗体
    titleLabel->setFont(titleFont); // 将修改后的字体应用到标签
    
    // 设置文字居中对齐
    titleLabel->setAlignment(Qt::AlignCenter);
    
    // 将标题标签添加到主布局
    mainLayout->addWidget(titleLabel);
    // ==================== 表单区域 ====================
    // 创建表单布局
    QFormLayout *formLayout = new QFormLayout();
    
    // 用户名
    QLineEdit *usernameEdit = new QLineEdit();
    usernameEdit->setPlaceholderText("请输入用户名");
    formLayout->addRow("用户名:", usernameEdit);

    //密码
    QLineEdit *passwordEdit = new QLineEdit();
    passwordEdit->setPlaceholderText("请输入密码");
    formLayout->addRow("密码:", passwordEdit);

    //确认密码
    QLineEdit *confirmEdit = new QLineEdit();
    confirmEdit->setPlaceholderText("请确认密码");
    formLayout->addRow("确认密码:", confirmEdit);

    mainLayout->addLayout(formLayout);

// ==================== 性别选择 ====================
    QGroupBox *genderGroup = new QGroupBox("性别");
    QHBoxLayout *genderLayout = new QHBoxLayout(genderGroup);

    //创建单选按钮
    QRadioButton *maleRadio = new QRadioButton("男");
    QRadioButton *femaleRadio = new QRadioButton("女");
    maleRadio->setChecked(true);
    
    genderLayout->addWidget(maleRadio);
    genderLayout->addWidget(femaleRadio);
    genderLayout->addStretch();
    genderGroup->setLayout(genderLayout);

    mainLayout->addWidget(genderGroup);
// ==================== 爱好选择 ====================
    QGroupBox *hobbyGroup = new QGroupBox("爱好");
    QHBoxLayout *hobbyLayout = new QHBoxLayout(hobbyGroup);

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
    QLabel *cityLabel = new QLabel("城市");
    QHBoxLayout *cityLayout = new QHBoxLayout();
    
    QComboBox *cityCombo = new QComboBox();
    cityCombo->addItems({"北京", "上海", "广州", "深圳"});
    cityCombo->setCurrentIndex(1);
    cityLayout->addWidget(cityCombo);


    cityLayout ->addWidget(cityLabel); 
    mainLayout->addLayout(cityLayout);

// ==================== 年龄滑动条 ====================
    QHBoxLayout *ageLayout = new QHBoxLayout();
    
    QLabel *ageLabel = new QLabel("年龄");
    
    QSlider *ageSlider = new QSlider(Qt::Horizontal);
    ageSlider->setRange(18, 60);
    ageSlider->setValue(25);
    
    QLabel *ageValueLabel = new QLabel("25");

    ageLayout->addWidget(ageLabel);
    ageLayout->addWidget(ageSlider);
    ageLayout->addWidget(ageValueLabel);
    mainLayout->addLayout(ageLayout);
// ==================== 自我介绍 ====================
    QLabel *introductionLabel = new QLabel("自我介绍");

    QTextEdit *introductionEdit = new QTextEdit();
    introductionEdit->setPlaceholderText("请输入自我介绍");
    introductionEdit -> setMaximumHeight(80);

    mainLayout->addWidget(introductionLabel);
    mainLayout->addWidget(introductionEdit);

    // ==================== 进度条 ====================
    QLabel *progressLabel = new QLabel("填写进度");
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
    //更新年龄显示
    QObject::connect(ageSlider,&QSlider::valueChanged,[&](int value)
    {
        ageValueLabel->setText(QString::number(value));
    });

    //填写计算进度
    auto updateProgress = [&]()
    {
        int progress = 0;
        if(!usernameEdit -> text().isEmpty()) progress += 20;
        if(!passwordEdit -> text().isEmpty()) progress += 20;
        if(!confirmEdit -> text().isEmpty()) progress += 20;
        if(!introductionEdit -> toPlainText().isEmpty()) progress += 20;
        if(swimCheck -> isChecked() || musicCheck -> isChecked() || readCheck -> isChecked() || sportCheck -> isChecked()) progress += 20;
        progressBar->setValue(progress);
    };
    //连接信号与槽（注意：Lambda直接用名字，不加&）
    QObject::connect(usernameEdit, &QLineEdit::textChanged, updateProgress);
    QObject::connect(passwordEdit, &QLineEdit::textChanged, updateProgress);
    QObject::connect(confirmEdit, &QLineEdit::textChanged, updateProgress);
    QObject::connect(introductionEdit, &QTextEdit::textChanged, updateProgress);
    QObject::connect(swimCheck, &QCheckBox::stateChanged, updateProgress);
    QObject::connect(musicCheck, &QCheckBox::stateChanged, updateProgress);
    QObject::connect(readCheck, &QCheckBox::stateChanged, updatePro gress);
    QObject::connect(sportCheck, &QCheckBox::stateChanged, updateProgress);
    

    
    // 显示窗口
    window.show();

    qDebug() << "Day03程序已启动";
    return app.exec();
}