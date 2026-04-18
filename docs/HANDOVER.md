# Linux Device Manager - 项目交接文档

**创建日期**: 2026-04-18  
**当前阶段**: 第一阶段 - 基础能力构建  
**当前模块**: 模块6 - 通用UI组件库 (UI Components)  
**学习者**: 具备C++基础，无Qt经验

---

## 一、项目背景

### 1.1 项目概述
面向Linux嵌入式设备的管理平台，采用Qt5/C++开发，目标用户为嵌入式Linux开发工程师、系统测试工程师。

### 1.2 项目架构（6大模块）
1. **模块1**: 设备连接管理器 (SSH连接)
2. **模块2**: 系统监控面板 (性能监控)
3. **模块3**: 文件传输工具 (SFTP)
4. **模块4**: 远程终端 (SSH终端)
5. **模块5**: 自动化测试平台 (测试框架)
6. **模块6**: 通用UI组件库 (基础设施) ← **当前学习阶段**

---

## 二、已完成工作

### 2.1 项目文档
| 文档 | 路径 | 说明 |
|------|------|------|
| 项目拆分文档 | `docs/ProjectBreakdown.md` | 6大模块详细拆分及知识点 |
| 模块6知识点 | `docs/Module6_KnowledgePoints.md` | 第一阶段10个知识点详细拆分 |
| 代码组织规范 | `docs/CodeOrganization.md` | 学习代码存放规范 |
| 交接文档 | `docs/HANDOVER.md` | 本文件 |

### 2.2 目录结构
```
LinuxDeviceManager/
├── docs/                           # 文档目录
│   ├── ProjectBreakdown.md
│   ├── Module6_KnowledgePoints.md
│   ├── CodeOrganization.md
│   └── HANDOVER.md                 # 【必须每次更新】
│
├── learning/                       # 学习代码目录
│   ├── PROGRESS.md                 # 学习进度跟踪【必须每次更新】
│   ├── common/                     # 公共代码库
│   │   ├── widgets/                # 可复用控件
│   │   ├── styles/                 # 公共样式
│   │   └── utils/                  # 工具类
│   └── stage1_ui_basics/           # 第一阶段：UI基础
│       └── day01_hello_qt/         # 第1天：Hello Qt（已创建）
│           ├── README.md
│           ├── day01_hello_qt.pro
│           └── main.cpp            # 【已验证可编译】
│
└── src/                            # 最终项目源码（待创建）
```

### 2.3 环境状态
- Qt5已安装（版本5.15.3）
- qmake可用
- Day01示例代码已创建并验证可编译
- Git已配置（待初始化仓库）

### 2.4 Git版本管理
**【重要】每次学习都必须使用Git进行版本管理**

- 仓库位置：`LinuxDeviceManager/`（根目录）
- 提交频率：每个学习日至少提交1次
- 提交规范：见第5章Git使用规范

---

## 三、当前进度

### 3.1 学习阶段
**第一阶段：基础能力构建（预计2-3周）**
- 模块：模块6 - 通用UI组件库
- 状态：Day01已创建，等待开始教学
- 下一个任务：讲解Day01代码，带领学习者理解并运行

### 3.2 模块6知识点（10个）
| 序号 | 知识点 | 状态 | 目录名 |
|------|--------|------|--------|
| 1 | Qt项目基础结构 | ⬜ | day01_hello_qt（已创建） |
| 2 | 信号与槽机制 | ⬜ | day02_signals_slots |
| 3 | 常用控件 | ⬜ | day03_widgets |
| 4 | 布局管理 | ⬜ | day04_layout |
| 5 | 主窗口 | ⬜ | day05_mainwindow |
| 6 | 自定义控件 | ⬜ | day06_custom_widget |
| 7 | QSS样式表 | ⬜ | day07_qss |
| 8 | Model/View基础 | ⬜ | day08_model_view |
| 9 | 国际化 | ⬜ | day09_i18n |
| 10 | 资源系统 | ⬜ | day10_resources |
| 项目 | UI组件库 | ⬜ | project/ |

**查看详细进度**: `learning/PROGRESS.md`

---

## 四、AI操作指令

### 4.1 每次对话开始时的标准流程

```
1. 【必须】读取 HANDOVER.md 了解当前状态
2. 【必须】读取 learning/PROGRESS.md 了解学习进度
3. 【可选】读取当前学习日的 README.md 了解当天目标
4. 根据学习者需求进行教学或开发
5. 【必须】对话结束时更新 HANDOVER.md 和 PROGRESS.md
```

### 4.2 创建新的学习日标准流程

当需要创建新的学习日（如Day02）时：

```bash
# 1. 创建目录
mkdir -p learning/stage1_ui_basics/day02_signals_slots

# 2. 创建项目文件 day02_signals_slots.pro
QT += core gui widgets
CONFIG += c++11
TARGET = day02_signals_slots
TEMPLATE = app
SOURCES += main.cpp

# 3. 创建 README.md（使用模板）
# 4. 创建 main.cpp（包含当天知识点的示例代码）
# 5. 验证编译：qmake && make
# 6. 更新 PROGRESS.md 标记新学习日
# 7. 【重要】Git提交
git add learning/stage1_ui_basics/day02_signals_slots/
git commit -m "day02: 创建信号与槽学习项目"
```

### 4.3 README.md 模板

```markdown
# Day XX: 主题

## 学习目标
- [ ] 目标1
- [ ] 目标2

## 实践任务
1. [ ] 任务1
2. [ ] 任务2

## 关键概念
### 概念1
说明...

## 关键代码
\`\`\`cpp
// 代码示例
\`\`\`

## 遇到的问题
- 

## 学习心得

## 运行截图
```

### 4.4 更新进度文件的标准

**更新 learning/PROGRESS.md**：
```markdown
| Day 01 | Hello Qt | ✅ 已完成 | 2026-04-18 | 已掌握QApplication |
```

**更新 docs/HANDOVER.md**：
- 修改"当前进度"章节
- 更新知识点状态表格
- 记录本次对话完成的工作

### 4.5 教学原则

1. **循序渐进**：必须按知识点顺序教学，不可跳过
2. **理论+实践**：每个知识点先讲解概念，再写代码验证
3. **小步快跑**：每个学习日控制在2-4小时工作量
4. **及时验证**：写完后立即编译运行，看到效果
5. **鼓励提问**：学习者不懂时要耐心解释，多举例子

### 4.6 代码规范检查清单

- [ ] 头文件包含Q_OBJECT宏
- [ ] 使用Qt命名规范（类名大驼峰，变量小驼峰）
- [ ] 信号槽使用新语法（函数指针方式）
- [ ] 代码注释使用中文
- [ ] 项目文件(.pro)配置正确
- [ ] 代码可以编译通过

---

## 五、常用命令速查

### 5.1 编译运行
```bash
# 进入学习日目录
cd learning/stage1_ui_basics/day01_hello_qt

# 编译
qmake
make

# 运行
./day01_hello_qt

# 清理
make clean
```

### 5.2 创建新学习日（脚本）
```bash
STAGE=stage1_ui_basics
DAY=day02
TOPIC=signals_slots

mkdir -p learning/${STAGE}/${DAY}_${TOPIC}
# 然后创建.pro, README.md, main.cpp
```

## 五、Git版本管理规范

### 5.1 Git初始化（首次使用）
```bash
# 进入项目根目录
cd /home/ysr/LinuxDeviceManager

# 初始化Git仓库
git init

# 配置用户信息（如未配置）
git config user.name "Learner"
git config user.email "learner@example.com"

# 创建.gitignore文件
cat > .gitignore << 'EOF'
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
# ... 每个学习日的可执行文件

# IDE
.vscode/
.idea/
*.swp
*.swo
*~

# 临时文件
*.tmp
*.log
EOF

# 添加所有文件并提交
git add .
git commit -m "init: 初始化项目，创建Day01学习代码"
```

### 5.2 每次学习的Git流程

**【必须】每个学习日结束时执行：**

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

### 5.3 提交信息规范

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

### 5.4 分支策略

```
main (主分支)
  └── 所有学习代码直接提交到main分支
  
【注意】本项目为个人学习，不使用复杂分支策略
所有代码直接提交到main分支即可
```

### 5.5 Git使用检查清单

每次学习结束时检查：
- [ ] 代码可以编译通过
- [ ] 已执行 `git add` 添加文件
- [ ] 已执行 `git commit` 提交
- [ ] 提交信息符合规范
- [ ] 已更新 `PROGRESS.md` 进度

### 5.6 常用Git命令速查

```bash
# 查看状态
git status

# 查看修改内容
git diff

# 添加文件
git add <文件路径>
git add .                    # 添加所有修改

# 提交
git commit -m "提交信息"

# 查看提交历史
git log --oneline -10        # 简洁显示最近10条
git log --graph --oneline    # 图形化显示

# 撤销操作
git checkout -- <文件>       # 撤销文件修改
git reset HEAD <文件>        # 取消暂存

# 查看某次提交的详情
git show <commit-id>
```

---

## 六、常用命令速查

### 6.1 编译运行
```bash
# 进入学习日目录
cd learning/stage1_ui_basics/day01_hello_qt

# 编译
qmake
make

# 运行
./day01_hello_qt

# 清理
make clean
```

### 6.2 创建新学习日（脚本）
```bash
STAGE=stage1_ui_basics
DAY=day02
TOPIC=signals_slots

mkdir -p learning/${STAGE}/${DAY}_${TOPIC}
# 然后创建.pro, README.md, main.cpp
# 最后别忘了：git add + git commit
```

---

## 七、关键文件索引

### 必读文档（每次对话前）
| 文件 | 用途 |
|------|------|
| `docs/HANDOVER.md` | 了解当前状态和任务 |
| `learning/PROGRESS.md` | 了解学习进度 |
| `docs/Module6_KnowledgePoints.md` | 查看知识点详细说明 |

### 参考文档
| 文件 | 用途 |
|------|------|
| `docs/ProjectBreakdown.md` | 了解项目整体架构 |
| `docs/CodeOrganization.md` | 代码组织规范 |

---

## 八、本次对话记录

### 7.1 本次完成的工作
- [x] 创建模块6知识点详细拆分文档
- [x] 创建代码组织规范文档
- [x] 创建学习代码目录结构
- [x] 创建Day01示例代码并验证编译
- [x] 创建学习进度跟踪文件
- [x] 完善交接文档，加入AI操作指令

### 7.2 学习者状态
- 尚未开始实际编码学习
- 等待开始Day01的教学

### 7.3 下一步任务
1. 向学习者介绍Day01的内容
2. 讲解QApplication和基本项目结构
3. 带领学习者运行第一个Qt程序
4. 完成Day01的学习任务

---

## 九、更新记录

| 日期 | 更新人 | 更新内容 |
|------|--------|----------|
| 2026-04-18 | AI Assistant | 初始创建，完成项目架构和Day01准备 |

---

**【重要】每次对话结束时必须执行：**
1. 更新本文件的"本次对话记录"章节
2. 更新`learning/PROGRESS.md`中的进度表格
3. 确保所有新创建的代码都已验证可编译
4. **执行Git提交（如完成学习日）**
   - `git add .`
   - `git commit -m "dayXX: 完成XXX学习"`
