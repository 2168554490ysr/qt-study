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
    // 创建应用程序对象
    // 每个Qt程序必须有且只有一个QApplication对象
    // 它负责管理应用程序的全局资源和事件循环
    QApplication app(argc, argv);
    
    // 创建主窗口
    QWidget window;
    
    // 设置窗口标题
    window.setWindowTitle("Hello Qt - 我的第一个Qt程序");
    
    // 设置窗口大小 (宽度, 高度)
    window.resize(800, 600);
    
    // 创建一个按钮
    QPushButton *button = new QPushButton("点击我", &window);
    button->setGeometry(350, 250, 100, 40);  // 设置按钮位置和大小
    
    // 显示窗口
    window.show();
    
    // 输出调试信息
    qDebug() << "程序已启动，窗口已显示";
    
    // 进入事件循环，等待用户交互
    // exec()会一直运行，直到程序退出
    return app.exec();
}
