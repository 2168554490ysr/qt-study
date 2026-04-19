/******************************************************************************
 * Day 04: 布局管理(Layout)
 * 
 * 学习目标：
 * - 掌握 QHBoxLayout 水平布局
 * - 掌握 QVBoxLayout 垂直布局
 * - 掌握 QGridLayout 网格布局
 * - 理解布局嵌套（组合多种布局）
 * - 掌握拉伸因子(stretch)控制比例
 * - 了解布局边距和间距设置
 ******************************************************************************/

#include <QApplication>
#include <QWidget>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>
#include <QGroupBox>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QWidget window;
    window.setWindowTitle("Day 04: 布局管理(Layout)");
    window.resize(600, 500);

    // ========================================
    // 1. 水平布局示例 (QHBoxLayout)
    // ========================================
    QGroupBox *hBoxGroup = new QGroupBox("1. 水平布局 (QHBoxLayout)");
    QHBoxLayout *hLayout = new QHBoxLayout();
    
    QPushButton *btn1 = new QPushButton("按钮1");
    QPushButton *btn2 = new QPushButton("按钮2");
    QPushButton *btn3 = new QPushButton("按钮3");
    
    hLayout->addWidget(btn1);
    hLayout->addWidget(btn2);
    hLayout->addWidget(btn3);
    
    hBoxGroup->setLayout(hLayout);

    // ========================================
    // 2. 垂直布局示例 (QVBoxLayout)
    // ========================================
    QGroupBox *vBoxGroup = new QGroupBox("2. 垂直布局 (QVBoxLayout)");
    QVBoxLayout *vLayout = new QVBoxLayout();
    
    QPushButton *btnA = new QPushButton("按钮A");
    QPushButton *btnB = new QPushButton("按钮B");
    QPushButton *btnC = new QPushButton("按钮C");
    
    vLayout->addWidget(btnA);
    vLayout->addWidget(btnB);
    vLayout->addWidget(btnC);
    
    vBoxGroup->setLayout(vLayout);

    // ========================================
    // 3. 网格布局示例 (QGridLayout)
    // ========================================
    QGroupBox *gridGroup = new QGroupBox("3. 网格布局 (QGridLayout)");
    QGridLayout *gridLayout = new QGridLayout();
    
    // 创建标签和输入框
    QLabel *nameLabel = new QLabel("姓名:");
    QLabel *ageLabel = new QLabel("年龄:");
    QLabel *emailLabel = new QLabel("邮箱:");
    
    QLineEdit *nameEdit = new QLineEdit();
    QLineEdit *ageEdit = new QLineEdit();
    QLineEdit *emailEdit = new QLineEdit();
    
    // 添加到网格：行, 列, 行跨度, 列跨度
    gridLayout->addWidget(nameLabel, 0, 0);   // 第0行，第0列
    gridLayout->addWidget(nameEdit, 0, 1);    // 第0行，第1列
    gridLayout->addWidget(ageLabel, 1, 0);    // 第1行，第0列
    gridLayout->addWidget(ageEdit, 1, 1);     // 第1行，第1列
    gridLayout->addWidget(emailLabel, 2, 0);  // 第2行，第0列
    gridLayout->addWidget(emailEdit, 2, 1);   // 第2行，第1列
    
    // 设置列拉伸因子（第1列占更多空间）
    gridLayout->setColumnStretch(0, 1);//第0列占1份空间
    gridLayout->setColumnStretch(1, 3);//第1列占3份空间
    
    gridGroup->setLayout(gridLayout);

    // ========================================
    // 4. 布局嵌套示例（水平+垂直组合）
    // ========================================
    QGroupBox *nestedGroup = new QGroupBox("4. 布局嵌套（水平+垂直组合）");
    
    // 外层垂直布局
    QVBoxLayout *outerLayout = new QVBoxLayout();
    
    // 内层水平布局1
    QHBoxLayout *innerLayout1 = new QHBoxLayout();
    innerLayout1->addWidget(new QPushButton("左"));
    innerLayout1->addWidget(new QPushButton("中"));
    innerLayout1->addWidget(new QPushButton("右"));
    
    // 内层水平布局2
    QHBoxLayout *innerLayout2 = new QHBoxLayout();
    innerLayout2->addWidget(new QPushButton("确认"));
    innerLayout2->addWidget(new QPushButton("取消"));
    innerLayout2->addStretch();  // 添加弹性空间，将按钮推到左边
    
    // 将内层布局添加到外层
    outerLayout->addLayout(innerLayout1);
    outerLayout->addLayout(innerLayout2);
    
    nestedGroup->setLayout(outerLayout);

    // ========================================
    // 5. 拉伸因子示例
    // ========================================
    QGroupBox *stretchGroup = new QGroupBox("5. 拉伸因子 (Stretch Factor)");
    QHBoxLayout *stretchLayout = new QHBoxLayout();
    
    QPushButton *smallBtn = new QPushButton("小(1)");
    QPushButton *mediumBtn = new QPushButton("中(2)");
    QPushButton *largeBtn = new QPushButton("大(3)");
    
    // 添加控件时指定拉伸因子
    stretchLayout->addWidget(smallBtn, 1);   // 占1份
    stretchLayout->addWidget(mediumBtn, 2);  // 占2份
    stretchLayout->addWidget(largeBtn, 3);   // 占3份
    
    stretchGroup->setLayout(stretchLayout);

    // ========================================
    // 6. 边距和间距设置示例
    // ========================================
    QGroupBox *spacingGroup = new QGroupBox("6. 边距和间距设置");
    QVBoxLayout *spacingLayout = new QVBoxLayout();
    
    // 设置边距：左, 上, 右, 下
    spacingLayout->setContentsMargins(20, 20, 20, 20);
    // 设置控件间距
    spacingLayout->setSpacing(15);
    
    spacingLayout->addWidget(new QPushButton("按钮1（间距15像素）"));
    spacingLayout->addWidget(new QPushButton("按钮2（间距15像素）"));
    spacingLayout->addWidget(new QLabel("边距：上下左右各20像素"));
    
    spacingGroup->setLayout(spacingLayout);

    // ========================================
    // 主布局：将所有组垂直排列
    // ========================================
    QVBoxLayout *mainLayout = new QVBoxLayout();
    mainLayout->addWidget(hBoxGroup);
    mainLayout->addWidget(vBoxGroup);
    mainLayout->addWidget(gridGroup);
    mainLayout->addWidget(nestedGroup);
    mainLayout->addWidget(stretchGroup);
    mainLayout->addWidget(spacingGroup);
    
    // 设置主窗口布局
    window.setLayout(mainLayout);

    // 连接信号槽（示例）
    QObject::connect(btn1, &QPushButton::clicked, []() {
        qDebug() << "水平布局：按钮1被点击";
    });

    window.show();
    qDebug() << "Day04 布局管理示例已启动";
    qDebug() << "OK";
    return app.exec();
}
