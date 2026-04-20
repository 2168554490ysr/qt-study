#include <QApplication>
#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QGroupBox>
#include <QDebug>
#include "counterwidget.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    
    // 主窗口
    QWidget window;
    window.setWindowTitle("Day 06: 自定义控件示例");
    window.resize(500, 600);
    
    QVBoxLayout *mainLayout = new QVBoxLayout(&window);
    
    // ========================================
    // 1. 标题
    // ========================================
    QLabel *titleLabel = new QLabel("<h1>Day 06: 自定义控件(CounterWidget)</h1>");
    titleLabel->setAlignment(Qt::AlignCenter);
    mainLayout->addWidget(titleLabel);
    
    // ========================================
    // 2. 使用自定义控件
    // ========================================
    QGroupBox *widgetGroup = new QGroupBox("计数器控件（自定义）");
    QVBoxLayout *widgetLayout = new QVBoxLayout(widgetGroup);
    
    // 创建自定义控件实例
    CounterWidget *counter = new CounterWidget();
    counter->setRange(0, 20);  // 设置范围 0-20
    widgetLayout->addWidget(counter, 0, Qt::AlignCenter);
    
    mainLayout->addWidget(widgetGroup);
    
    // ========================================
    // 3. 外部控制按钮
    // ========================================
    QGroupBox *controlGroup = new QGroupBox("外部控制");
    QHBoxLayout *controlLayout = new QHBoxLayout(controlGroup);
    
    QPushButton *add5Btn = new QPushButton("+5");
    QPushButton *sub5Btn = new QPushButton("-5");
    QPushButton *set10Btn = new QPushButton("设为10");
    
    controlLayout->addWidget(add5Btn);
    controlLayout->addWidget(sub5Btn);
    controlLayout->addWidget(set10Btn);
    
    mainLayout->addWidget(controlGroup);
    
    // ========================================
    // 4. 状态显示
    // ========================================
    QGroupBox *statusGroup = new QGroupBox("状态监控");
    QVBoxLayout *statusLayout = new QVBoxLayout(statusGroup);
    
    QLabel *valueLabel = new QLabel("当前值: 0");
    QLabel *eventLabel = new QLabel("事件: 等待操作...");
    valueLabel->setStyleSheet("font-size: 16px;");
    eventLabel->setStyleSheet("font-size: 14px; color: blue;");
    
    statusLayout->addWidget(valueLabel);
    statusLayout->addWidget(eventLabel);
    
    mainLayout->addWidget(statusGroup);
    
    // ========================================
    // 5. 信号槽连接 - 连接自定义信号
    // ========================================
    
    // 值改变信号
    QObject::connect(counter, &CounterWidget::valueChanged, 
        [&](int newValue) {
            valueLabel->setText(QString("当前值: %1").arg(newValue));
            eventLabel->setText(QString("事件: 值改变为 %1").arg(newValue));
            qDebug() << "收到 valueChanged 信号，新值:" << newValue;
        });
    
    // 达到最大值信号
    QObject::connect(counter, &CounterWidget::maximumReached, 
        [&]() {
            eventLabel->setText("事件: ⚠️ 已达到最大值！");
            eventLabel->setStyleSheet("font-size: 14px; color: red; font-weight: bold;");
            qDebug() << "收到 maximumReached 信号";
        });
    
    // 达到最小值信号
    QObject::connect(counter, &CounterWidget::minimumReached, 
        [&]() {
            eventLabel->setText("事件: ✅ 已达到最小值！");
            eventLabel->setStyleSheet("font-size: 14px; color: green; font-weight: bold;");
            qDebug() << "收到 minimumReached 信号";
        });
    
    // 外部控制按钮
    QObject::connect(add5Btn, &QPushButton::clicked, [&]() {
        counter->setValue(counter->value() + 5);
    });
    
    QObject::connect(sub5Btn, &QPushButton::clicked, [&]() {
        counter->setValue(counter->value() - 5);
    });
    
    QObject::connect(set10Btn, &QPushButton::clicked, [&]() {
        counter->setValue(10);
    });
    
    // ========================================
    // 6. 说明文本
    // ========================================
    QLabel *infoLabel = new QLabel(
        "<p><b>自定义控件功能：</b></p>"
        "<ul>"
        "<li>点击 +/- 按钮调整数值</li>"
        "<li>拖动滑块调整数值</li>"
        "<li>点击控件区域也会增加</li>"
        "<li>达到最大值/最小值时会发出信号</li>"
        "<li>背景颜色会根据状态变化</li>"
        "</ul>"
    );
    infoLabel->setWordWrap(true);
    mainLayout->addWidget(infoLabel);
    
    mainLayout->addStretch();
    
    window.show();
    qDebug() << "Day06 自定义控件示例已启动";
    
    return app.exec();
}
