/******************************************************************************
 * Day 02: 信号与槽机制 (Signals & Slots)
 *
 * 学习目标：
 * - 理解信号与槽的概念和作用
 * - 掌握connect函数的5种连接方式
 * - 学会使用Lambda表达式
 * - 理解信号与槽的参数传递
 ******************************************************************************/

#include <QApplication>
#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QDebug>
#include <QLineEdit>
#include <QLabel>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    // 创建主窗口
    QWidget window;
    window.setWindowTitle("Day02: 信号与槽机制");
    window.resize(400, 300);

    // 创建垂直布局
    QVBoxLayout *layout = new QVBoxLayout(&window);

    // 创建标签显示信息
    QLabel *label = new QLabel("等待操作...", &window);
    label->setAlignment(Qt::AlignCenter);
    layout->addWidget(label);

    // 创建输入框
    QLineEdit *lineEdit = new QLineEdit(&window);
    lineEdit->setPlaceholderText("在此输入文字...");
    layout->addWidget(lineEdit);

    // 创建按钮1：改变标签文字
    QPushButton *btn1 = new QPushButton("改变标签文字", &window);
    layout->addWidget(btn1);

    // 创建按钮2：清空输入框
    QPushButton *btn2 = new QPushButton("清空输入框", &window);
    layout->addWidget(btn2);

    // 创建按钮3：关闭窗口
    QPushButton *btn3 = new QPushButton("关闭窗口", &window);
    layout->addWidget(btn3);

    // ==================== 信号与槽连接 ====================

    // 【示例1】Lambda表达式连接 - 改变标签文字
    // 当按钮被点击时，标签显示输入框的内容
    QObject::connect(btn1, &QPushButton::clicked, [&]() {
        QString text = lineEdit->text();
        if (text.isEmpty()) {
            label->setText("请输入内容！");
        } else {
            label->setText("你输入了: " + text);
        }
        qDebug() << "按钮1被点击，输入内容:" << text;
    });

    // 【示例2】Lambda表达式连接 - 清空输入框
    QObject::connect(btn2, &QPushButton::clicked, [&]() {
        lineEdit->clear();
        label->setText("输入框已清空");
        qDebug() << "按钮2被点击，清空输入框";
    });

    // 【示例3】连接内置信号到内置槽 - 关闭窗口
    // clicked() 信号连接 QWidget::close() 槽
    QObject::connect(btn3, &QPushButton::clicked, &window, &QWidget::close);

    // 【示例4】一个信号连接多个槽
    // 输入框文字改变时，同时更新标签和输出调试信息
    QObject::connect(lineEdit, &QLineEdit::textChanged, [&](const QString &text) {
        label->setText("正在输入: " + text);
    });

    QObject::connect(lineEdit, &QLineEdit::textChanged, [](const QString &text) {
        qDebug() << "文字改变:" << text;
    });

    // 显示窗口
    window.show();

    qDebug() << "Day02程序已启动";

    return app.exec();
}
