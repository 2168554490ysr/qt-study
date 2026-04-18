# Day 01: Hello Qt - 第一个Qt程序

## 学习目标
- [ ] 理解Qt项目的基本结构
- [ ] 掌握QApplication的作用
- [ ] 了解MOC（元对象编译器）机制
- [ ] 学会创建最简单的Qt窗口程序
- [ ] 理解.pro项目文件的配置

## 实践任务
1. [ ] 创建Qt项目文件(.pro)
2. [ ] 编写main.cpp入口文件
3. [ ] 编译并运行程序
4. [ ] 修改窗口标题和大小
5. [ ] 添加一个按钮到窗口

## 关键概念

### 1. QApplication
- 每个Qt程序必须有且只有一个QApplication对象
- 负责管理应用程序的全局资源
- `exec()`启动事件循环，等待用户交互

### 2. MOC机制
- Qt的元对象系统，提供信号槽、反射等功能
- 头文件中必须写`Q_OBJECT`宏
- 编译时会生成moc_xxx.cpp文件

### 3. .pro文件
- qmake的项目配置文件
- 指定模块依赖、源文件、头文件等

## 关键代码

```cpp
// main.cpp
#include <QApplication>
#include <QWidget>

int main(int argc, char *argv[])
{
    // 创建应用程序对象
    QApplication app(argc, argv);
    
    // 创建窗口
    QWidget window;
    window.setWindowTitle("Hello Qt");  // 设置窗口标题
    window.resize(800, 600);             // 设置窗口大小
    window.show();                       // 显示窗口
    
    // 进入事件循环
    return app.exec();
}
```

## 编译运行

```bash
# 方法1: 命令行编译
qmake day01_hello_qt.pro
make
./day01_hello_qt

# 方法2: Qt Creator
# 打开.pro文件，点击运行按钮
```

## 遇到的问题
- 

## 学习心得

## 运行截图
（完成后贴图）
