# Linux Device Manager - 学习代码组织规范

**版本**: v1.0  
**日期**: 2026-04-18

---

## 一、代码存放总览

```
LinuxDeviceManager/
├── docs/                           # 文档目录
│   ├── ProjectBreakdown.md         # 项目整体拆分
│   ├── Module6_KnowledgePoints.md  # 模块6知识点
│   ├── HANDOVER.md                 # 交接文档
│   └── CodeOrganization.md         # 本文件
│
├── learning/                       # 学习代码目录（按阶段组织）
│   ├── stage1_ui_basics/           # 第一阶段：UI基础
│   │   ├── day01_hello_qt/         # 第1天：第一个Qt程序
│   │   ├── day02_signals_slots/    # 第2天：信号与槽
│   │   ├── day03_widgets/          # 第3天：常用控件
│   │   ├── day04_layout/           # 第4天：布局管理
│   │   ├── day05_mainwindow/       # 第5天：主窗口
│   │   ├── day06_custom_widget/    # 第6天：自定义控件
│   │   ├── day07_qss/              # 第7天：QSS样式
│   │   ├── day08_model_view/       # 第8天：Model/View
│   │   ├── day09_i18n/             # 第9天：国际化
│   │   ├── day10_resources/        # 第10天：资源系统
│   │   └── project/                # 阶段项目：UI组件库
│   │       ├── ThemeManager/       # 主题管理器
│       ├── StatusIndicator/        # 状态指示器
│       ├── CollapsiblePanel/       # 折叠面板
│       └── ...
│   │
│   ├── stage2_ssh_connection/      # 第二阶段：SSH连接
│   ├── stage3_system_monitor/      # 第三阶段：系统监控
│   ├── stage4_file_transfer/       # 第四阶段：文件传输
│   ├── stage5_terminal/            # 第五阶段：远程终端
│   └── stage6_test_platform/       # 第六阶段：测试平台
│
├── src/                            # 最终项目源码（各阶段完成后整合）
│   ├── core/                       # 核心模块
│   ├── ui/                         # UI模块
│   ├── models/                     # 数据模型
│   └── utils/                      # 工具类
│
├── tests/                          # 测试代码
├── scripts/                        # 脚本工具
└── third_party/                    # 第三方库

```

---

## 二、每日学习代码结构

### 2.1 单天学习目录结构

每个学习日的代码按以下结构组织：

```
day01_hello_qt/                     # 目录命名：dayXX_主题
├── README.md                       # 当天学习总结
├── day01_hello_qt.pro              # 项目文件
├── main.cpp                        # 入口文件
├── mainwindow.cpp                  # 窗口实现
├── mainwindow.h                    # 窗口头文件
└── mainwindow.ui                   # UI文件（如使用Designer）
```

### 2.2 README.md 模板

每个学习目录必须包含README.md，记录：

```markdown
# Day 01: Hello Qt

## 学习目标
- 理解Qt项目结构
- 掌握QApplication的使用
- 了解MOC机制

## 实践内容
1. 创建第一个Qt窗口程序
2. 修改窗口标题和大小
3. 添加一个按钮

## 关键代码
```cpp
// main.cpp
QApplication app(argc, argv);
QWidget window;
window.setWindowTitle("Hello Qt");
window.show();
return app.exec();
```

## 遇到的问题
- 问题1：xxx → 解决方法：xxx

## 学习心得
今天学会了xxx...

## 运行截图
（可选）
```

---

## 三、代码命名规范

### 3.1 目录命名
| 类型 | 命名规范 | 示例 |
|------|----------|------|
| 学习阶段 | stageX_英文名 | stage1_ui_basics |
| 学习日期 | dayXX_主题 | day01_hello_qt |
| 练习项目 | exercise_XX_描述 | exercise_01_button_click |
| 阶段项目 | project/ | project/ |

### 3.2 文件命名
| 类型 | 命名规范 | 示例 |
|------|----------|------|
| 项目文件 | 目录名.pro | day01_hello_qt.pro |
| 头文件 | 小写_分隔.h | main_window.h |
| 源文件 | 小写_分隔.cpp | main_window.cpp |
| UI文件 | 小写_分隔.ui | main_window.ui |
| 资源文件 | resources.qrc | resources.qrc |

### 3.3 类命名
| 类型 | 命名规范 | 示例 |
|------|----------|------|
| 窗口类 | 大驼峰 + Window/Widget | MainWindow, LoginWidget |
| 控件类 | 大驼峰 + 功能 | StatusIndicator, ThemeButton |
| 工具类 | 大驼峰 + Utils/Helper | StringUtils, JsonHelper |

---

## 四、Git版本控制规范

### 4.1 初始化Git仓库

```bash
# 在项目根目录初始化
cd /home/ysr/LinuxDeviceManager
git init

# 配置用户信息
git config user.name "Learner"
git config user.email "learner@example.com"

# 创建.gitignore文件（见4.4节）
```

### 4.2 提交规范

**【必须】每次学习日结束时提交：**

```bash
# 1. 查看当前状态
git status

# 2. 添加当天学习代码
git add learning/stage1_ui_basics/day01_hello_qt/

# 3. 提交（使用规范格式）
git commit -m "day01: 完成Hello Qt学习，理解QApplication和项目结构"

# 4. 查看提交历史
git log --oneline -5
```

### 4.3 提交信息格式

**格式**: `<type>: <subject>`

| Type | 含义 | 示例 |
|------|------|------|
| `dayXX` | 第XX天学习 | `day01: 完成Hello Qt学习` |
| `fix` | 修复问题 | `fix: 修复Day03按钮不响应问题` |
| `docs` | 文档更新 | `docs: 更新Day02学习笔记` |
| `refactor` | 重构 | `refactor: 优化Day05代码结构` |
| `project` | 阶段项目 | `project: 完成UI组件库主题管理器` |

**Subject规范**：
- 简短描述（不超过50字）
- 使用中文
- 说明做了什么，而非怎么做的

### 4.4 .gitignore模板

```gitignore
# Qt构建产物
*.o
*.obj
moc_*.cpp
moc_*.h
ui_*.h
qrc_*.cpp
Makefile
*.pro.user
*.pro.user.*

# 可执行文件（无后缀）
/day01_hello_qt
/day02_signals_slots
/day03_widgets
/day04_layout
/day05_mainwindow
/day06_custom_widget
/day07_qss
/day08_model_view
/day09_i18n
/day10_resources

# IDE
.vscode/
.idea/
*.swp
*.swo
*~

# 临时文件
*.tmp
*.log
```

### 4.5 分支策略

```
main (主分支)
  └── 所有学习代码直接提交到main分支
  
【注意】本项目为个人学习，不使用复杂分支策略
所有代码直接提交到main分支即可
```

### 4.6 Git使用检查清单

每次学习结束时检查：
- [ ] 代码可以编译通过
- [ ] 已执行 `git add` 添加文件
- [ ] 已执行 `git commit` 提交
- [ ] 提交信息符合规范
- [ ] 已更新 `PROGRESS.md` 进度

---

## 五、代码复用策略

### 5.1 从学习到项目的代码演进

```
学习阶段 (learning/)
    ↓ 提取、完善、封装
阶段项目 (learning/stageX/project/)
    ↓ 整合、优化
最终项目 (src/)
```

### 5.2 可复用组件管理

在`learning/common/`目录存放可复用代码：

```
learning/
├── common/                         # 公共代码库
│   ├── widgets/                    # 可复用控件
│   │   ├── StatusIndicator/        # 状态指示灯
│   │   ├── ThemeButton/            # 主题按钮
│   │   └── ...
│   ├── styles/                     # 公共样式
│   │   ├── dark_theme.qss
│   │   └── light_theme.qss
│   └── utils/                      # 工具类
│       ├── string_utils.h
│       └── ...
```

---

## 六、学习进度跟踪

### 6.1 进度文件

创建`learning/PROGRESS.md`记录学习进度：

```markdown
# 学习进度跟踪

## 第一阶段：UI基础 (stage1_ui_basics)

| 天数 | 主题 | 状态 | 完成日期 | 备注 |
|------|------|------|----------|------|
| Day 01 | Hello Qt | ⬜ 未开始 | - | |
| Day 02 | 信号与槽 | ⬜ 未开始 | - | |
| Day 03 | 常用控件 | ⬜ 未开始 | - | |
| ... | ... | ... | ... | ... |
| 项目 | UI组件库 | ⬜ 未开始 | - | |

## 第二阶段：SSH连接 (stage2_ssh_connection)
...

## 总体进度
- [ ] 第一阶段：UI基础 (0/11)
- [ ] 第二阶段：SSH连接 (0/8)
- [ ] 第三阶段：系统监控 (0/8)
- [ ] 第四阶段：文件传输 (0/6)
- [ ] 第五阶段：远程终端 (0/7)
- [ ] 第六阶段：测试平台 (0/6)
```

---

## 七、快速创建学习项目的脚本

### 7.1 创建新学习日的脚本

```bash
#!/bin/bash
# create_learning_day.sh

STAGE=$1      # 阶段名，如 stage1_ui_basics
DAY=$2        # 天数，如 day01
TOPIC=$3      # 主题，如 hello_qt

DIR="learning/${STAGE}/${DAY}_${TOPIC}"
mkdir -p "$DIR"

# 创建项目文件
cat > "$DIR/${DAY}_${TOPIC}.pro" << EOF
QT += core gui widgets

CONFIG += c++11

TARGET = ${DAY}_${TOPIC}
TEMPLATE = app

SOURCES += main.cpp
EOF

# 创建main.cpp
cat > "$DIR/main.cpp" << 'EOF'
#include <QApplication>
#include <QWidget>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    
    QWidget window;
    window.setWindowTitle("${TOPIC}");
    window.resize(800, 600);
    window.show();
    
    return app.exec();
}
EOF

# 创建README.md
cat > "$DIR/README.md" << EOF
# ${DAY}: ${TOPIC}

## 学习目标
- 

## 实践内容
1. 
2. 
3. 

## 关键代码
\`\`\`cpp
// 在这里记录关键代码
\`\`\`

## 遇到的问题
- 

## 学习心得

EOF

echo "Created: $DIR"
```

使用方式：
```bash
./create_learning_day.sh stage1_ui_basics day01 hello_qt
```

---

## 八、示例：第一阶段完整目录

```
learning/
├── PROGRESS.md
├── common/
│   ├── widgets/
│   │   ├── StatusIndicator/
│   │   │   ├── status_indicator.h
│   │   │   ├── status_indicator.cpp
│   │   │   └── README.md
│   │   └── ThemeButton/
│   └── styles/
│       ├── dark_theme.qss
│       └── light_theme.qss
│
└── stage1_ui_basics/
    ├── day01_hello_qt/
    │   ├── README.md
    │   ├── day01_hello_qt.pro
    │   └── main.cpp
    │
    ├── day02_signals_slots/
    │   ├── README.md
    │   ├── day02_signals_slots.pro
    │   ├── main.cpp
    │   ├── mainwindow.cpp
    │   └── mainwindow.h
    │
    ├── day03_widgets/
    │   ├── README.md
    │   ├── day03_widgets.pro
    │   └── ...
    │
    ├── ...
    │
    └── project/
        ├── ThemeManager/
        │   ├── theme_manager.h
        │   ├── theme_manager.cpp
        │   └── README.md
        ├── StatusIndicator/
        ├── CollapsiblePanel/
        ├── project.pro
        └── main.cpp
```

---

**文档变更记录**

| 版本 | 日期 | 修改人 | 修改内容 |
|------|------|--------|----------|
| v1.0 | 2026-04-18 | - | 初始版本 |
