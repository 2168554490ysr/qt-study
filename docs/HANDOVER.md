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
- ✅ Git已初始化并配置完成

### 2.4 Git版本管理
**【重要】每一次代码更改都必须使用Git进行版本管理**

- 仓库位置：`LinuxDeviceManager/`（根目录）
- 远程仓库：`https://github.com/2168554490ysr/qt-study.git`
- 代理配置：`http://127.0.0.1:7897`
- **提交频率：每一次代码更改都要提交**
  - 每完成一个功能点提交一次
  - 每修复一个bug提交一次
  - 每完成一个学习日任务提交一次
- 提交规范：见第5章Git使用规范
- **核心原则：频繁提交，小步快跑**

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
# 6. 【重要】第一次Git提交 - 创建项目
git add learning/stage1_ui_basics/day02_signals_slots/
git commit -m "day02: 创建信号与槽学习项目"
git push

# 7. 后续每完成一个功能点都要提交
# 例如：完成信号连接功能
git add .
git commit -m "day02: 实现按钮点击信号连接"
git push

# 例如：完成Lambda表达式
git add .
git commit -m "day02: 添加Lambda表达式示例"
git push

# 8. 更新 PROGRESS.md 标记新学习日
git add learning/PROGRESS.md
git commit -m "docs: 更新Day02学习进度"
git push
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

### 5.2 Git提交流程（每次代码更改都执行）

**【必须】每一次代码更改都要执行以下步骤：**

```bash
# 1. 查看当前修改
git status

# 2. 查看具体修改内容（确认无误）
git diff

# 3. 添加修改的文件
git add <具体文件>       # 推荐：添加特定文件
git add .                # 或者：添加所有修改

# 4. 提交（使用规范格式）
git commit -m "day01: 完成Hello Qt学习，理解QApplication和项目结构"

# 5. 推送到远程仓库
git push

# 6. 查看提交历史确认成功
git log --oneline -5
```

### 5.3 何时需要提交

| 场景 | 提交示例 | 说明 |
|------|----------|------|
| 完成一个功能点 | `day02: 实现按钮点击信号连接` | 每完成一个小功能 |
| 修复一个bug | `fix: 修复Day03按钮不响应问题` | 修复后立即提交 |
| 重构代码 | `refactor: 优化Day05代码结构` | 重构后提交 |
| 更新文档 | `docs: 更新Day02学习笔记` | 文档更新也要提交 |
| 完成学习日 | `day02: 完成信号与槽学习` | 学习日结束时 |

**核心原则：频繁提交，小步快跑**
- 每15-30分钟的工作就应该有一次提交
- 不要积累大量修改后再提交
- 提交应该是原子性的（一个提交只做一件事）

### 5.4 提交信息规范

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

### 5.5 分支策略

```
main (主分支)
  └── 所有学习代码直接提交到main分支
  
【注意】本项目为个人学习，不使用复杂分支策略
所有代码直接提交到main分支即可
```

### 5.6 Git使用检查清单

**每一次代码更改后都要检查：**
- [ ] 代码可以编译通过
- [ ] 已执行 `git add` 添加修改的文件
- [ ] 已执行 `git commit` 提交（信息符合规范）
- [ ] 已执行 `git push` 推送到远程
- [ ] 已更新 `PROGRESS.md` 进度（如需要）

**提交频率检查：**
- [ ] 是否每完成一个功能点就提交？
- [ ] 是否每15-30分钟就有提交？
- [ ] 提交是否是原子性的（一个提交只做一件事）？

### 5.7 常用Git命令速查

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
# 验证编译通过后

# 【必须】Git提交
git add learning/${STAGE}/${DAY}_${TOPIC}/
git commit -m "${DAY}: 创建${TOPIC}学习项目"
git push
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
- [x] 初始化Git仓库并配置代理
- [x] 完成第一次Git提交并推送到远程仓库
- [x] 更新交接文档，强调每一次代码更改都要Git提交
- [x] 完成Day01学习：讲解代码并更新README
- [x] 完成Day02学习：创建信号与槽项目
- [x] 解答学习者问题并更新Day02 README的Q&A部分
- [x] 完成Day03学习：创建常用控件项目，实现用户注册表单
- [x] 修复Lambda连接编译错误
- [x] 更新Day03 README的Q&A部分（10个问题）
- [x] 安装Qt5开发环境（版本5.12.8）
- [x] 验证Git远程仓库配置
- [x] 创建Day04项目：布局管理（Layout）
- [x] 创建day04_layout.pro项目文件
- [x] 创建main.cpp示例代码（6种布局示例）
- [x] 创建README.md学习文档（含Q&A）
- [x] 验证Day04代码编译通过
- [x] 更新PROGRESS.md进度文档
- [x] 更新HANDOVER.md交接文档
- [x] **完成Day04学习**：理解QHBoxLayout、QVBoxLayout、QGridLayout
- [x] **掌握布局嵌套和拉伸因子setColumnStretch/setRowStretch**
- [x] **更新Day04 README的Q&A部分（新增Q8、Q9关于行拉伸）**
- [x] **标记Day04为已完成状态**
- [x] **创建Day05项目：主窗口(MainWindow)**
- [x] **创建day05_mainwindow.pro项目文件**
- [x] **创建main.cpp示例代码（菜单栏、工具栏、状态栏、中心部件）**
- [x] **创建README.md学习文档（含Q&A）**
- [x] **验证Day05代码编译通过**
- [x] **更新PROGRESS.md进度文档（Day05标记为进行中）**
- [x] **更新HANDOVER.md交接文档"

### 7.2 学习者状态
- ✅ Day01已完成：理解QApplication、窗口创建、按钮添加
- ✅ Day02已完成：理解信号与槽、Lambda表达式、布局管理
- ✅ Day03已完成：掌握常用控件、QFormLayout、字体设置、进度条更新
- ✅ Day04已完成：掌握QHBoxLayout、QVBoxLayout、QGridLayout、布局嵌套、拉伸因子
- 📝 Day05已创建：主窗口项目已创建并验证编译，等待学习
- Qt5开发环境已安装（版本5.12.8）
- Git远程仓库已配置并可用

### 7.3 下一步任务
1. ~~创建Day04项目~~ ✅ 已完成
2. ~~学习Day04代码~~ ✅ 已完成
3. ~~理解布局嵌套和拉伸因子~~ ✅ 已完成
4. ~~更新README Q&A~~ ✅ 已完成
5. ~~创建Day05项目~~ ✅ 已完成
6. **学习Day05代码：主窗口(MainWindow)**
   - 理解QMainWindow结构
   - 学习菜单栏(QMenuBar)和QAction
   - 学习工具栏(QToolBar)
   - 学习状态栏(QStatusBar)
   - 理解中心部件(Central Widget)
   - 掌握动作的快捷键设置和复用

---

## 九、更新记录

| 日期 | 更新人 | 更新内容 |
|------|--------|----------|
| 2026-04-18 | AI Assistant | 初始创建，完成项目架构和Day01准备，初始化Git仓库 |
| 2026-04-18 | AI Assistant | 完成Day01和Day02学习，更新README的Q&A部分 |
| 2026-04-18 | AI Assistant | 完成Day03学习，修复编译错误，更新文档 |
| 2026-04-19 | AI Assistant | 安装Qt5开发环境，创建Day04布局管理项目，更新进度文档 |
| 2026-04-19 | AI Assistant | 完成Day04学习，创建Day05主窗口项目，更新所有进度文档 |

---

**【重要】每次对话结束时必须执行：**
1. 更新本文件的"本次对话记录"章节
2. 更新`learning/PROGRESS.md`中的进度表格
3. 确保所有新创建的代码都已验证可编译
4. **【必须】执行Git提交（每一次代码更改）**
   - `git add .`
   - `git commit -m "dayXX: 完成XXX功能"`
   - `git push`
5. **更新交接文档并提交**
   - `git add docs/HANDOVER.md`
   - `git commit -m "docs: 更新交接文档"`
   - `git push`
