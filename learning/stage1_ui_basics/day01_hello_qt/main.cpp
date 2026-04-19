/******************************************************************************
 * Day 01: Hello Qt - 第一个Qt程序
 * 
 * 学习目标：
 * - 理解Qt项目的基本结构
 * - 掌握QApplication的作用
 * - 学会创建最简单的Qt窗口程序
 ******************************************************************************/

#include <QApplication>
#include <QWidget>
#include <QPushButton>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QWidget window;
    window.setWindowTitle("Hello Qt - 我的第一个Qt程序");
    window.resize(800, 600);

    QPushButton *button = new QPushButton("点击我", &window);
    button->setGeometry(350, 250, 100, 40);  // 设置按钮位置和大小

    window.show();
    qDebug() << "程序已启动，窗口已显示";

    return app.exec();
}
