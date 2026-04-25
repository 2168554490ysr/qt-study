QT       += core gui widgets

TARGET = day10_resources
TEMPLATE = app

CONFIG += c++11

SOURCES += main.cpp

# 资源文件配置
RESOURCES += resources.qrc

# 默认构建规则
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
