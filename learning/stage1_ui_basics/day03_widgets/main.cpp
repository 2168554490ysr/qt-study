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
    

    // 显示窗口
    window.show();

    qDebug() << "Day03程序已启动";
    return app.exec();
}