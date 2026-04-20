#ifndef COUNTERWIDGET_H
#define COUNTERWIDGET_H

#include <QWidget>

class QPushButton;
class QLabel;
class QSlider;

/**
 * @brief 计数器自定义控件
 * 
 * 这是一个自定义控件示例，展示了：
 * - 继承 QWidget 创建自定义控件
 * - 定义自定义信号
 * - 定义自定义槽
 * - 组合多个基本控件
 * - 重写 paintEvent 自定义绘制
 */
class CounterWidget : public QWidget
{
    Q_OBJECT  // 必须添加，用于支持信号槽机制

public:
    explicit CounterWidget(QWidget *parent = nullptr);
    ~CounterWidget();

    // 获取当前值
    int value() const;
    
    // 设置值
    void setValue(int value);
    
    // 设置范围
    void setRange(int min, int max);

signals:
    // 自定义信号：值改变时发出
    void valueChanged(int newValue);
    
    // 自定义信号：达到最大值时发出
    void maximumReached();
    
    // 自定义信号：达到最小值时发出
    void minimumReached();

public slots:
    // 自定义槽：增加
    void increment();
    
    // 自定义槽：减少
    void decrement();
    
    // 自定义槽：重置
    void reset();

protected:
    // 重写绘制事件，自定义外观
    void paintEvent(QPaintEvent *event) override;
    
    // 重写鼠标按下事件
    void mousePressEvent(QMouseEvent *event) override;

private:
    void setupUI();      // 设置界面
    void updateDisplay(); // 更新显示

    // 成员变量
    int m_value;         // 当前值
    int m_minValue;      // 最小值
    int m_maxValue;      // 最大值
    
    // 子控件
    QLabel *m_valueLabel;       // 显示当前值
    QPushButton *m_incButton;   // 增加按钮
    QPushButton *m_decButton;   // 减少按钮
    QPushButton *m_resetButton; // 重置按钮
    QSlider *m_slider;          // 滑块
};

#endif // COUNTERWIDGET_H
