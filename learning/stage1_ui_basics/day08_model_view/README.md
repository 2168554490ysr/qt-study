# Day 08: Model/View 基础

## 学习目标
- [x] 理解 Model/View 架构概念（数据与视图分离）
- [x] 掌握 QStringListModel 和 QListView 的使用
- [x] 掌握 QStandardItemModel 和 QTreeView 的使用
- [x] 学习自定义模型（继承 QAbstractTableModel）
- [x] 掌握 QTableView 的使用
- [x] 理解 Model 的编辑功能和角色系统

## 实践任务
1. [x] 创建 QStringListModel + QListView 示例
2. [x] 创建 QStandardItemModel + QTreeView 示例
3. [x] 实现自定义 DeviceTableModel 继承 QAbstractTableModel
4. [x] 实现数据的增删改查功能
5. [x] 理解并应用 Model 的角色系统（DisplayRole, BackgroundRole 等）

## 关键概念

### 1. Model/View 架构
Model/View 是 Qt 中用于数据和视图分离的架构模式：
- **Model（模型）**：负责数据的存储和管理
- **View（视图）**：负责数据的显示
- **Delegate（委托）**：负责数据的编辑和渲染（可选）

这种分离的好处：
- 一个 Model 可以对应多个 View
- 数据改变时，所有关联的 View 自动更新
- 代码更清晰，职责更明确

### 2. 常用 Model 类

| Model 类 | 用途 | 适用 View |
|---------|------|----------|
| QStringListModel | 存储字符串列表 | QListView |
| QStandardItemModel | 通用的标准模型，支持树形 | QListView, QTableView, QTreeView |
| QAbstractTableModel | 抽象表格模型基类 | QTableView |
| QAbstractListModel | 抽象列表模型基类 | QListView |
| QAbstractItemModel | 抽象项模型基类（最底层） | 所有 View |

### 3. 常用 View 类

| View 类 | 显示方式 |
|---------|---------|
| QListView | 列表形式（一行一个项目） |
| QTableView | 表格形式（行列结构） |
| QTreeView | 树形结构（可展开折叠） |

### 4. Model 角色（Role）

Role 用于指定数据的用途：

| Role | 值 | 说明 |
|------|-----|------|
| Qt::DisplayRole | 0 | 显示的文字 |
| Qt::DecorationRole | 1 | 装饰（如图标） |
| Qt::EditRole | 2 | 编辑时的数据 |
| Qt::ToolTipRole | 3 | 工具提示 |
| Qt::StatusTipRole | 4 | 状态栏提示 |
| Qt::WhatsThisRole | 5 | What's This 帮助 |
| Qt::FontRole | 6 | 字体 |
| Qt::TextAlignmentRole | 7 | 文字对齐 |
| Qt::BackgroundRole | 8 | 背景色 |
| Qt::ForegroundRole | 9 | 前景色（文字颜色） |
| Qt::CheckStateRole | 10 | 复选框状态 |

### 5. 自定义 Model 必须实现的虚函数

```cpp
// 返回行数
int rowCount(const QModelIndex& parent) const;

// 返回列数（表格模型需要）
int columnCount(const QModelIndex& parent) const;

// 返回指定索引的数据
QVariant data(const QModelIndex& index, int role) const;

// 返回表头数据
QVariant headerData(int section, Qt::Orientation orientation, int role) const;
```

### 6. 数据修改通知

当数据改变时，需要通知 View 更新：

```cpp
// 数据改变时发射信号
emit dataChanged(topLeft, bottomRight, roles);

// 插入行前调用
beginInsertRows(parent, first, last);
// ... 实际插入数据 ...
endInsertRows();

// 删除行前调用
beginRemoveRows(parent, first, last);
// ... 实际删除数据 ...
endRemoveRows();
```

## 关键代码

### 自定义表格模型
```cpp
class DeviceTableModel : public QAbstractTableModel {
    Q_OBJECT
    
public:
    explicit DeviceTableModel(QObject* parent = nullptr) 
        : QAbstractTableModel(parent) {}
    
    // 返回行数
    int rowCount(const QModelIndex& parent) const override {
        Q_UNUSED(parent)
        return m_devices.size();
    }
    
    // 返回列数
    int columnCount(const QModelIndex& parent) const override {
        Q_UNUSED(parent)
        return 4;
    }
    
    // 返回数据
    QVariant data(const QModelIndex& index, int role) const override {
        if (!index.isValid()) return QVariant();
        
        const DeviceInfo& device = m_devices[index.row()];
        
        if (role == Qt::DisplayRole) {
            switch (index.column()) {
                case 0: return device.name;
                case 1: return device.ip;
                // ...
            }
        }
        
        if (role == Qt::BackgroundRole) {
            // 根据状态返回不同背景色
            if (device.status == "在线") {
                return QColor(200, 255, 200);
            }
        }
        
        return QVariant();
    }
};
```

### 设置 View 的 Model
```cpp
// 创建 Model
m_deviceModel = new DeviceTableModel(this);

// 创建 View
m_tableView = new QTableView(this);

// 关联 Model
m_tableView->setModel(m_deviceModel);

// 设置选择行为
m_tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
m_tableView->setAlternatingRowColors(true);
```

### 操作 Model 数据
```cpp
// 添加数据
void addDevice(const DeviceInfo& device) {
    beginInsertRows(QModelIndex(), m_devices.size(), m_devices.size());
    m_devices.append(device);
    endInsertRows();
}

// 删除数据
void removeDevice(int row) {
    beginRemoveRows(QModelIndex(), row, row);
    m_devices.removeAt(row);
    endRemoveRows();
}
```

## 遇到的问题

### Q1: 编译报错 "incomplete type 'QTime' used in nested name specifier"
**原因**: 使用了 `QTime::currentTime()` 但没有包含头文件
**解决**: 添加 `#include <QTime>`

### Q2: 如何实现可编辑的 Model？
**解决**: 需要实现 `flags()` 和 `setData()` 函数：
```cpp
Qt::ItemFlags flags(const QModelIndex& index) const override {
    return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable;
}

bool setData(const QModelIndex& index, const QVariant& value, int role) override {
    if (index.isValid() && role == Qt::EditRole) {
        // 修改数据
        emit dataChanged(index, index, {role});
        return true;
    }
    return false;
}
```

### Q3: 如何设置交替行颜色？
**解决**: `m_tableView->setAlternatingRowColors(true);`

### Q4: 如何让表格列自动拉伸填充？
**解决**: 
```cpp
m_tableView->horizontalHeader()->setStretchLastSection(true);
m_tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
```

### Q5: 如何在 Model 中根据数据设置不同颜色？
**解决**: 在 `data()` 函数中处理 `Qt::BackgroundRole`：
```cpp
if (role == Qt::BackgroundRole) {
    if (device.status == "在线") {
        return QColor(200, 255, 200); // 浅绿色
    } else {
        return QColor(255, 200, 200); // 浅红色
    }
}
```

### Q6: 树形 Model 如何添加子节点？
**解决**: 使用 `QStandardItem::appendRow()`：
```cpp
QStandardItem* parent = new QStandardItem("父节点");
QStandardItem* child = new QStandardItem("子节点");
parent->appendRow(child);
model->appendRow(parent);
```

### Q7: QModelIndex 是什么？
**回答**: QModelIndex 是 Model/View 架构中用于定位数据的索引类：
- `row()`: 返回行号
- `column()`: 返回列号
- `isValid()`: 检查索引是否有效
- `parent()`: 返回父节点索引（树形结构用）

### Q8: 如何获取当前选中的行？
**解决**: 
```cpp
QModelIndex index = m_tableView->currentIndex();
if (index.isValid()) {
    int row = index.row();
    // 使用 row 操作数据
}
```

### Q9: beginInsertRows 和 endInsertRows 的作用？
**回答**: 这两个函数用于通知 View 即将插入/删除行，View 会相应更新显示：
- `beginInsertRows(parent, first, last)`: 在插入行前调用
- `endInsertRows()`: 在插入行后调用
- 如果不调用，View 不会知道数据已改变，显示不会更新

### Q10: 为什么自定义 Model 要加 Q_OBJECT 宏？
**回答**: 
- Q_OBJECT 宏启用 Qt 的元对象系统
- 让类可以使用信号槽机制
- 让 moc（元对象编译器）处理这个类
- 自定义 Model 通常需要发射 dataChanged 等信号

## 学习心得

1. **Model/View 分离思想很重要**：这种架构让数据和显示解耦，代码更清晰，维护更容易。

2. **角色系统很灵活**：通过不同的 Role，可以为同一个数据项提供多种表现形式（文字、颜色、对齐方式等）。

3. **Qt 提供了丰富的预定义 Model**：对于简单场景，可以直接使用 QStringListModel、QStandardItemModel，不需要自己实现。

4. **自定义 Model 并不复杂**：只需要实现几个关键的虚函数，就能创建功能完整的 Model。

5. **数据变更通知机制**：`beginInsertRows`/`endInsertRows` 等函数让 View 能正确响应数据变化，这是 Model/View 架构的关键。

## 运行截图

（请在此处添加程序运行截图）

## 参考资料
- [Qt Model/View Programming](https://doc.qt.io/qt-5/model-view-programming.html)
- [Qt Model/View Tutorial](https://doc.qt.io/qt-5/modelview.html)
