# Day 09: 国际化 (i18n)

## 学习目标
- [x] 理解 Qt 国际化(i18n)的概念和工作流程
- [x] 掌握 `tr()` 函数的使用方法
- [x] 学习使用 `lupdate` 和 `lrelease` 工具
- [x] 掌握 QTranslator 翻译器的加载和使用
- [x] 实现运行时语言切换功能
- [x] 了解 .ts 和 .qm 文件的区别

## 实践任务
1. [x] 创建带有 `tr()` 标记的示例程序
2. [x] 使用 `lupdate` 提取翻译字符串生成 .ts 文件
3. [x] 编辑 .ts 文件添加中文翻译
4. [x] 使用 `lrelease` 编译 .ts 生成 .qm 文件
5. [x] 实现 QTranslator 加载和语言切换功能
6. [x] 实现界面文字的动态更新

## 关键概念

### 1. 国际化流程

```
┌─────────────────────────────────────────────────────────────┐
│                     Qt 国际化工作流程                        │
├─────────────────────────────────────────────────────────────┤
│                                                             │
│  1. 源代码中所有可翻译文本使用 tr() 包裹                      │
│     ↓                                                       │
│  2. 运行 lupdate 提取字符串，生成 .ts 文件(XML格式)          │
│     ↓                                                       │
│  3. 使用 Qt Linguist 或直接编辑 .ts 文件添加翻译             │
│     ↓                                                       │
│  4. 运行 lrelease 编译 .ts 生成 .qm 文件(二进制格式)         │
│     ↓                                                       │
│  5. 程序中使用 QTranslator 加载 .qm 文件                     │
│     ↓                                                       │
│  6. 用户界面显示翻译后的文字                                  │
│                                                             │
└─────────────────────────────────────────────────────────────┘
```

### 2. tr() 函数

`tr()` 是 `QObject` 的成员函数，用于标记需要翻译的字符串：

```cpp
// 基本用法
label->setText(tr("Hello World"));

// 带参数的翻译
label->setText(tr("Welcome, %1!").arg(username));

// 带复数形式的翻译
tr("%1 file(s)", "", count).arg(count);
```

**为什么用 tr() 而不是普通字符串？**
- `tr()` 会将字符串标记为"可翻译"
- `lupdate` 工具会扫描所有 `tr()` 调用并提取字符串
- 支持参数替换、复数形式等高级功能

### 3. 翻译文件格式

| 格式 | 扩展名 | 说明 | 用途 |
|------|--------|------|------|
| Translation Source | .ts | XML 格式，人类可读 | 编辑翻译 |
| Translation Binary | .qm | 二进制格式，机器高效 | 程序加载 |

### 4. lupdate 和 lrelease 工具

**lupdate** - 提取源代码中的可翻译字符串
```bash
# 从 .pro 文件提取
lupdate day09_i18n.pro

# 扫描结果
Updating 'translations/day09_i18n_zh_CN.ts'...
    Found 18 source text(s) (18 new and 0 already existing)
```

**lrelease** - 编译 .ts 文件为 .qm 文件
```bash
# 编译所有翻译
lrelease day09_i18n.pro

# 编译结果
Updating 'translations/day09_i18n_zh_CN.qm'...
    Generated 19 translation(s) (19 finished and 0 unfinished)
```

### 5. QTranslator 使用

```cpp
// 1. 创建翻译器
QTranslator translator;

// 2. 加载翻译文件
if (translator.load("translations/day09_i18n_zh_CN.qm")) {
    // 3. 安装到应用程序
    qApp->installTranslator(&translator);
}

// 4. 卸载翻译器
qApp->removeTranslator(&translator);
```

### 6. 动态切换语言

```cpp
void onLanguageChanged(QString langCode) {
    // 1. 移除旧翻译器
    qApp->removeTranslator(m_translator);
    
    // 2. 加载新翻译文件
    m_translator->load(QString("translations/day09_i18n_%1.qm").arg(langCode));
    
    // 3. 安装新翻译器
    qApp->installTranslator(m_translator);
    
    // 4. 刷新界面文字
    updateTexts();
}
```

**注意**：切换语言后需要手动调用函数刷新所有界面文字！

### 7. .pro 文件配置

```pro
# 翻译文件配置
TRANSLATIONS += translations/day09_i18n_zh_CN.ts \
                translations/day09_i18n_en.ts

# 让 qmake 自动生成翻译相关的构建目标
translate.target = translate
translate.commands = lupdate $$PWD/day09_i18n.pro && lrelease $$PWD/day09_i18n.pro
QMAKE_EXTRA_TARGETS += translate
```

### 8. .ts 文件结构

```xml
<?xml version="1.0" encoding="utf-8"?>
<!DOCTYPE TS>
<TS version="2.1" language="zh_CN">
<context>
    <name>ClassName</name>  <!-- 类名 -->
    <message>
        <location filename="main.cpp" line="10"/>  <!-- 源代码位置 -->
        <source>Hello</source>  <!-- 原文 -->
        <translation>你好</translation>  <!-- 译文 -->
    </message>
</context>
</TS>
```

## 关键代码

### tr() 函数使用示例
```cpp
// 简单翻译
setWindowTitle(tr("Qt Internationalization Demo"));

// 带参数的翻译
QMessageBox::information(this, tr("Login Success"), 
    tr("Welcome, %1!").arg(user));

// 占位符提示文字
m_userEdit->setPlaceholderText(tr("Enter username"));
```

### 翻译器加载
```cpp
// main.cpp
QTranslator translator;

// 根据系统语言加载
QLocale locale = QLocale::system();
QString qmFile = QString("translations/day09_i18n_%1.qm").arg(locale.name());

if (translator.load(qmFile)) {
    app.installTranslator(&translator);
}
```

### 界面刷新
```cpp
void updateTexts() {
    // 重新设置所有文字（会自动从翻译器获取对应语言的文本）
    setWindowTitle(tr("Qt Internationalization Demo"));
    m_userLabel->setText(tr("Username:"));
    m_pwdLabel->setText(tr("Password:"));
    m_loginBtn->setText(tr("Login"));
    // ... 其他所有控件
}
```

## 遇到的问题

### Q1: lupdate 提示 "no source code found"
**原因**: .pro 文件中没有 SOURCES 配置或配置错误
**解决**: 确保 .pro 文件中有 `SOURCES += main.cpp`

### Q2: 程序运行时翻译没有生效
**可能原因和解决**:
1. .qm 文件路径错误 → 检查路径是否正确
2. 忘记调用 `installTranslator()` → 确认已安装
3. 字符串没有用 `tr()` 包裹 → 检查源代码
4. .ts 文件中 `<translation>` 为空 → 确认已完成翻译

### Q3: 如何支持复数形式？
**解决**: 使用带参数的 `tr()`
```cpp
// %1 会被替换为 count 的值
tr("%1 file(s)", "", count).arg(count);

// 在 .ts 文件中可以配置不同复数形式的翻译
<translation>
    <numerusform>%1 个文件</numerusform>
</translation>
```

### Q4: 切换语言后界面没有更新？
**原因**: Qt 不会自动刷新界面
**解决**: 必须手动调用更新函数
```cpp
// 切换语言后
qApp->installTranslator(&translator);

// 手动刷新所有文字
updateTexts();  // 自定义函数，重新设置所有 tr() 文字
```

### Q5: lupdate 没有提取到某些字符串？
**原因**: 可能字符串在宏或特殊位置
**解决**: 
- 确保字符串在 `tr()` 中
- 对于非 QObject 类，使用 `QCoreApplication::translate("context", "text")`

### Q6: 如何同时支持多种语言？
**解决**: 在 .pro 文件中添加多个 TRANSLATIONS
```pro
TRANSLATIONS += translations/app_zh_CN.ts \
                translations/app_en.ts \
                translations/app_ja.ts \
                translations/app_ko.ts
```

### Q7: QLocale::name() 返回什么格式？
**回答**: `语言_国家` 格式，如：
- `zh_CN` - 简体中文
- `zh_TW` - 繁体中文
- `en_US` - 美式英语
- `ja_JP` - 日语
- `ko_KR` - 韩语

### Q8: 翻译文件应该放在哪里？
**建议**:
- 开发时: 放在 `translations/` 目录下
- 发布时: 
  - 可以打包到资源文件(.qrc)中
  - 或放在应用程序目录的 `translations/` 子目录

### Q9: 如何让翻译支持换行和HTML？
**解决**: 直接在 .ts 文件中使用 HTML
```xml
<source>&lt;h2&gt;About&lt;/h2&gt;&lt;p&gt;Version 1.0&lt;/p&gt;</source>
<translation>&lt;h2&gt;关于&lt;/h2&gt;&lt;p&gt;版本 1.0&lt;/p&gt;</translation>
```

### Q10: lupdate 和 lrelease 在哪里？
**回答**: 
- Linux: `/usr/lib/qt5/bin/lupdate` 和 `lrelease`
- 或已经添加到 PATH 中，可以直接使用
- 检查: `which lupdate`

## 学习心得

1. **国际化要尽早规划**: 从一开始就用 `tr()` 包裹所有用户可见的字符串，比后期改造容易得多。

2. **语言名称通常不翻译**: 语言选择下拉框中的语言名称（如 "English"、"中文"）通常保持原样，让用户能识别。

3. **翻译文件版本管理**: .ts 文件是 XML 格式，可以放入版本控制。.qm 文件是编译生成的，不需要版本控制。

4. **测试多种语言**: 不仅要测试中文，还要测试原文（英文），确保不会因为翻译破坏布局。

5. **注意文本长度**: 不同语言翻译后的长度差异很大，界面设计时要预留足够空间。

## 运行截图

（请在此处添加程序运行截图）

## 参考命令速查

```bash
# 提取翻译字符串
cd day09_i18n
lupdate day09_i18n.pro

# 编译翻译文件
lrelease day09_i18n.pro

# 编译并运行
qmake
make
./day09_i18n
```

## 参考资料
- [Qt Internationalization](https://doc.qt.io/qt-5/internationalization.html)
- [Writing Source Code for Translation](https://doc.qt.io/qt-5/i18n-source-translation.html)
- [Qt Linguist Manual](https://doc.qt.io/qt-5/linguist-manual.html)
