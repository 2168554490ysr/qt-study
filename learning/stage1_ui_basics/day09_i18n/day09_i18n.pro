QT += core gui widgets

CONFIG += c++11

TARGET = day09_i18n
TEMPLATE = app

SOURCES += main.cpp

# 翻译文件配置
TRANSLATIONS += translations/day09_i18n_zh_CN.ts \
                translations/day09_i18n_en.ts

# 让 qmake 自动生成翻译相关的构建目标
translate.target = translate
translate.commands = lupdate $$PWD/day09_i18n.pro && lrelease $$PWD/day09_i18n.pro
QMAKE_EXTRA_TARGETS += translate
