#include "counterwidget.h"
#include <QPushButton>
#include <QLabel>
#include <QSlider>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPainter>
#include <QMouseEvent>
#include <QDebug>

CounterWidget::CounterWidget(QWidget *parent)
    : QWidget(parent)
    , m_value(0)
    , m_minValue(0)
    , m_maxValue(100)
{
    setupUI();
    updateDisplay();
    
    // 设置固定大小
    setFixedSize(300, 150);
    
    qDebug() << "CounterWidget 创建完成，初始值:" << m_value;
}

CounterWidget::~CounterWidget()
{
    qDebug() << "CounterWidget 销毁";
}

int CounterWidget::value() const
{
    return m_value;
}

void CounterWidget::setValue(int value)
{
    // 限制在范围内
    if (value < m_minValue) {
        value = m_minValue;
    }
    if (value > m_maxValue) {
        value = m_maxValue;
    }
    
    if (m_value != value) {
        m_value = value;
        updateDisplay();
        emit valueChanged(m_value);  // 发出信号
        
        // 检查是否达到边界
        if (m_value == m_maxValue) {
            emit maximumReached();
        }
        if (m_value == m_minValue) {
            emit minimumReached();
        }
        
        // 触发重绘
        update();
    }
}

void CounterWidget::setRange(int min, int max)
{
    m_minValue = min;
    m_maxValue = max;
    
    // 更新滑块范围
    m_slider->setRange(min, max);
    
    // 确保当前值在范围内
    setValue(m_value);
}

void CounterWidget::increment()
{
    setValue(m_value + 1);
    qDebug() << "增加按钮点击，当前值:" << m_value;
}

void CounterWidget::decrement()
{
    setValue(m_value - 1);
    qDebug() << "减少按钮点击，当前值:" << m_value;
}

void CounterWidget::reset()
{
    setValue(0);
    qDebug() << "重置按钮点击";
}

void CounterWidget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)
    
    QPainter painter(this);
    
    // 绘制背景
    QColor bgColor = (m_value == m_maxValue) ? QColor(255, 200, 200) :  // 达到最大：红色
                     (m_value == m_minValue) ? QColor(200, 255, 200) :  // 达到最小：绿色
                                               QColor(240, 240, 240);    // 正常：灰色
    
    painter.fillRect(rect(), bgColor);
    
    // 绘制边框
    painter.setPen(QPen(Qt::darkGray, 2));
    painter.drawRect(rect().adjusted(1, 1, -1, -1));
    
    // 绘制进度条（底部）
    int progressWidth = (width() - 20) * (m_value - m_minValue) / (m_maxValue - m_minValue);
    painter.fillRect(10, height() - 15, progressWidth, 10, QColor(100, 150, 255));
}

void CounterWidget::mousePressEvent(QMouseEvent *event)
{
    Q_UNUSED(event)
    // 点击控件时增加
    increment();
}

void CounterWidget::setupUI()
{
    // 创建子控件
    m_valueLabel = new QLabel("0", this);
    m_valueLabel->setAlignment(Qt::AlignCenter);
    m_valueLabel->setStyleSheet("font-size: 32px; font-weight: bold; color: #333;");
    
    m_incButton = new QPushButton("+", this);
    m_incButton->setFixedSize(40, 40);
    m_incButton->setStyleSheet("font-size: 20px; font-weight: bold;");
    
    m_decButton = new QPushButton("-", this);
    m_decButton->setFixedSize(40, 40);
    m_decButton->setStyleSheet("font-size: 20px; font-weight: bold;");
    
    m_resetButton = new QPushButton("重置", this);
    m_resetButton->setFixedSize(60, 30);
    
    m_slider = new QSlider(Qt::Horizontal, this);
    m_slider->setRange(m_minValue, m_maxValue);
    
    // 布局
    QHBoxLayout *buttonLayout = new QHBoxLayout();
    buttonLayout->addWidget(m_decButton);
    buttonLayout->addWidget(m_valueLabel);
    buttonLayout->addWidget(m_incButton);
    
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addLayout(buttonLayout);
    mainLayout->addWidget(m_slider);
    mainLayout->addWidget(m_resetButton, 0, Qt::AlignCenter);
    
    // 连接信号槽
    connect(m_incButton, &QPushButton::clicked, this, &CounterWidget::increment);
    connect(m_decButton, &QPushButton::clicked, this, &CounterWidget::decrement);
    connect(m_resetButton, &QPushButton::clicked, this, &CounterWidget::reset);
    
    connect(m_slider, &QSlider::valueChanged, this, [this](int value) {
        setValue(value);
    });
}

void CounterWidget::updateDisplay()
{
    // 更新标签显示
    m_valueLabel->setText(QString::number(m_value));
    
    // 同步滑块
    m_slider->setValue(m_value);
    
    // 达到边界时改变标签颜色
    if (m_value == m_maxValue) {
        m_valueLabel->setStyleSheet("font-size: 32px; font-weight: bold; color: red;");
    } else if (m_value == m_minValue) {
        m_valueLabel->setStyleSheet("font-size: 32px; font-weight: bold; color: green;");
    } else {
        m_valueLabel->setStyleSheet("font-size: 32px; font-weight: bold; color: #333;");
    }
}
