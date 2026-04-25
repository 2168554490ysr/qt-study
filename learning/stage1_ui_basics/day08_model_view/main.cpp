#include <QApplication>
#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QListView>
#include <QTableView>
#include <QTreeView>
#include <QStringListModel>
#include <QStandardItemModel>
#include <QAbstractTableModel>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QGroupBox>
#include <QHeaderView>
#include <QMessageBox>
#include <QTime>

// 自定义数据模型：设备信息模型
class DeviceInfo {
public:
    QString name;
    QString ip;
    QString status;
    int cpuUsage;
    
    DeviceInfo(const QString& n, const QString& i, const QString& s, int cpu)
        : name(n), ip(i), status(s), cpuUsage(cpu) {}
};

// 自定义TableModel：继承QAbstractTableModel
class DeviceTableModel : public QAbstractTableModel {
    Q_OBJECT
    
public:
    explicit DeviceTableModel(QObject* parent = nullptr) 
        : QAbstractTableModel(parent) {}
    
    // 添加设备
    void addDevice(const DeviceInfo& device) {
        beginInsertRows(QModelIndex(), m_devices.size(), m_devices.size());
        m_devices.append(device);
        endInsertRows();
    }
    
    // 删除设备
    void removeDevice(int row) {
        if (row < 0 || row >= m_devices.size()) return;
        beginRemoveRows(QModelIndex(), row, row);
        m_devices.removeAt(row);
        endRemoveRows();
    }
    
    // 获取设备
    DeviceInfo getDevice(int row) const {
        if (row >= 0 && row < m_devices.size()) {
            return m_devices[row];
        }
        return DeviceInfo("", "", "", 0);
    }
    
    // 必需实现的虚函数：返回行数
    int rowCount(const QModelIndex& parent = QModelIndex()) const override {
        Q_UNUSED(parent)
        return m_devices.size();
    }
    
    // 必需实现的虚函数：返回列数
    int columnCount(const QModelIndex& parent = QModelIndex()) const override {
        Q_UNUSED(parent)
        return 4; // 名称、IP、状态、CPU使用率
    }
    
    // 必需实现的虚函数：返回数据
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override {
        if (!index.isValid() || index.row() >= m_devices.size())
            return QVariant();
        
        const DeviceInfo& device = m_devices[index.row()];
        
        if (role == Qt::DisplayRole) {
            switch (index.column()) {
                case 0: return device.name;
                case 1: return device.ip;
                case 2: return device.status;
                case 3: return QString("%1%").arg(device.cpuUsage);
            }
        }
        
        // 设置文字对齐方式
        if (role == Qt::TextAlignmentRole) {
            return Qt::AlignCenter;
        }
        
        // 根据状态设置背景色
        if (role == Qt::BackgroundRole) {
            if (device.status == "在线") {
                return QColor(200, 255, 200); // 浅绿色
            } else if (device.status == "离线") {
                return QColor(255, 200, 200); // 浅红色
            }
        }
        
        return QVariant();
    }
    
    // 必需实现的虚函数：返回表头数据
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override {
        if (role == Qt::DisplayRole && orientation == Qt::Horizontal) {
            switch (section) {
                case 0: return "设备名称";
                case 1: return "IP地址";
                case 2: return "状态";
                case 3: return "CPU使用率";
            }
        }
        return QVariant();
    }
    
    // 实现编辑功能
    Qt::ItemFlags flags(const QModelIndex& index) const override {
        if (!index.isValid())
            return Qt::NoItemFlags;
        return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable;
    }
    
    // 设置数据（编辑功能）
    bool setData(const QModelIndex& index, const QVariant& value, int role = Qt::EditRole) override {
        if (index.isValid() && role == Qt::EditRole) {
            int row = index.row();
            switch (index.column()) {
                case 0: m_devices[row].name = value.toString(); break;
                case 1: m_devices[row].ip = value.toString(); break;
                case 2: m_devices[row].status = value.toString(); break;
                case 3: m_devices[row].cpuUsage = value.toInt(); break;
            }
            emit dataChanged(index, index, {role});
            return true;
        }
        return false;
    }

private:
    QList<DeviceInfo> m_devices;
};

// 主窗口类
class ModelViewDemo : public QWidget {
    Q_OBJECT
    
public:
    explicit ModelViewDemo(QWidget* parent = nullptr) : QWidget(parent) {
        setupUI();
        initData();
    }
    
private:
    void setupUI() {
        setWindowTitle("Day08: Model/View 基础");
        setMinimumSize(900, 700);
        
        QVBoxLayout* mainLayout = new QVBoxLayout(this);
        
        // ========== 1. QStringListModel + QListView ==========
        QGroupBox* listGroup = new QGroupBox("1. QStringListModel + QListView (简单字符串列表)");
        QVBoxLayout* listLayout = new QVBoxLayout(listGroup);
        
        m_listView = new QListView(this);
        m_stringListModel = new QStringListModel(this);
        m_listView->setModel(m_stringListModel);
        m_listView->setEditTriggers(QAbstractItemView::DoubleClicked | QAbstractItemView::EditKeyPressed);
        
        QHBoxLayout* listBtnLayout = new QHBoxLayout();
        QPushButton* addBtn = new QPushButton("添加项目", this);
        QPushButton* delBtn = new QPushButton("删除选中", this);
        QPushButton* showBtn = new QPushButton("显示选中", this);
        
        listBtnLayout->addWidget(addBtn);
        listBtnLayout->addWidget(delBtn);
        listBtnLayout->addWidget(showBtn);
        listBtnLayout->addStretch();
        
        listLayout->addWidget(m_listView);
        listLayout->addLayout(listBtnLayout);
        
        connect(addBtn, &QPushButton::clicked, this, &ModelViewDemo::onAddListItem);
        connect(delBtn, &QPushButton::clicked, this, &ModelViewDemo::onDeleteListItem);
        connect(showBtn, &QPushButton::clicked, this, &ModelViewDemo::onShowSelectedListItem);
        
        // ========== 2. QStandardItemModel + QTreeView ==========
        QGroupBox* treeGroup = new QGroupBox("2. QStandardItemModel + QTreeView (树形结构)");
        QVBoxLayout* treeLayout = new QVBoxLayout(treeGroup);
        
        m_treeView = new QTreeView(this);
        m_standardModel = new QStandardItemModel(this);
        m_treeView->setModel(m_standardModel);
        m_treeView->setAlternatingRowColors(true); // 交替行颜色
        m_treeView->setSelectionBehavior(QAbstractItemView::SelectRows);
        
        treeLayout->addWidget(m_treeView);
        
        // ========== 3. 自定义模型 + QTableView ==========
        QGroupBox* tableGroup = new QGroupBox("3. 自定义DeviceTableModel + QTableView (表格视图)");
        QVBoxLayout* tableLayout = new QVBoxLayout(tableGroup);
        
        m_tableView = new QTableView(this);
        m_deviceModel = new DeviceTableModel(this);
        m_tableView->setModel(m_deviceModel);
        m_tableView->setAlternatingRowColors(true);
        m_tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
        m_tableView->setSelectionMode(QAbstractItemView::SingleSelection);
        m_tableView->horizontalHeader()->setStretchLastSection(true);
        m_tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
        
        // 添加/删除设备按钮
        QHBoxLayout* tableBtnLayout = new QHBoxLayout();
        m_nameEdit = new QLineEdit(this);
        m_nameEdit->setPlaceholderText("设备名称");
        m_ipEdit = new QLineEdit(this);
        m_ipEdit->setPlaceholderText("IP地址");
        
        QPushButton* addDeviceBtn = new QPushButton("添加设备", this);
        QPushButton* delDeviceBtn = new QPushButton("删除选中设备", this);
        QPushButton* refreshBtn = new QPushButton("刷新数据", this);
        
        tableBtnLayout->addWidget(new QLabel("名称:", this));
        tableBtnLayout->addWidget(m_nameEdit);
        tableBtnLayout->addWidget(new QLabel("IP:", this));
        tableBtnLayout->addWidget(m_ipEdit);
        tableBtnLayout->addWidget(addDeviceBtn);
        tableBtnLayout->addWidget(delDeviceBtn);
        tableBtnLayout->addWidget(refreshBtn);
        tableBtnLayout->addStretch();
        
        tableLayout->addWidget(m_tableView);
        tableLayout->addLayout(tableBtnLayout);
        
        connect(addDeviceBtn, &QPushButton::clicked, this, &ModelViewDemo::onAddDevice);
        connect(delDeviceBtn, &QPushButton::clicked, this, &ModelViewDemo::onDeleteDevice);
        connect(refreshBtn, &QPushButton::clicked, this, &ModelViewDemo::onRefreshData);
        
        // 组装主布局
        mainLayout->addWidget(listGroup, 1);
        mainLayout->addWidget(treeGroup, 1);
        mainLayout->addWidget(tableGroup, 2);
        
        // 说明标签
        QLabel* infoLabel = new QLabel(
            "💡 Model/View架构说明: Model负责数据存储，View负责数据显示，实现数据与视图分离"
        );
        infoLabel->setStyleSheet("color: #666; font-size: 12px;");
        mainLayout->addWidget(infoLabel);
    }
    
    void initData() {
        // 初始化列表数据
        QStringList provinces;
        provinces << "北京市" << "上海市" << "广东省" << "浙江省" << "江苏省";
        m_stringListModel->setStringList(provinces);
        
        // 初始化树形数据
        m_standardModel->setHorizontalHeaderLabels(QStringList() << "名称" << "描述");
        
        QStandardItem* root1 = new QStandardItem("设备组A");
        root1->setEditable(false);
        
        QStandardItem* child1 = new QStandardItem("服务器1");
        QStandardItem* desc1 = new QStandardItem("192.168.1.1");
        root1->appendRow(QList<QStandardItem*>() << child1 << desc1);
        
        QStandardItem* child2 = new QStandardItem("服务器2");
        QStandardItem* desc2 = new QStandardItem("192.168.1.2");
        root1->appendRow(QList<QStandardItem*>() << child2 << desc2);
        
        QStandardItem* root2 = new QStandardItem("设备组B");
        root2->setEditable(false);
        
        QStandardItem* child3 = new QStandardItem("交换机1");
        QStandardItem* desc3 = new QStandardItem("192.168.2.1");
        root2->appendRow(QList<QStandardItem*>() << child3 << desc3);
        
        m_standardModel->appendRow(root1);
        m_standardModel->appendRow(root2);
        
        m_treeView->expandAll(); // 展开所有节点
        
        // 初始化表格数据
        m_deviceModel->addDevice(DeviceInfo("Web服务器", "192.168.1.10", "在线", 45));
        m_deviceModel->addDevice(DeviceInfo("数据库服务器", "192.168.1.11", "在线", 78));
        m_deviceModel->addDevice(DeviceInfo("文件服务器", "192.168.1.12", "离线", 0));
        m_deviceModel->addDevice(DeviceInfo("缓存服务器", "192.168.1.13", "在线", 32));
    }
    
private slots:
    // 列表视图槽函数
    void onAddListItem() {
        int row = m_stringListModel->rowCount();
        m_stringListModel->insertRow(row);
        QModelIndex index = m_stringListModel->index(row);
        m_stringListModel->setData(index, QString("新项目 %1").arg(row + 1));
        m_listView->edit(index);
    }
    
    void onDeleteListItem() {
        QModelIndex index = m_listView->currentIndex();
        if (index.isValid()) {
            m_stringListModel->removeRow(index.row());
        }
    }
    
    void onShowSelectedListItem() {
        QModelIndex index = m_listView->currentIndex();
        if (index.isValid()) {
            QString text = m_stringListModel->data(index).toString();
            QMessageBox::information(this, "选中的项目", text);
        }
    }
    
    // 表格视图槽函数
    void onAddDevice() {
        QString name = m_nameEdit->text();
        QString ip = m_ipEdit->text();
        
        if (name.isEmpty() || ip.isEmpty()) {
            QMessageBox::warning(this, "警告", "请输入设备名称和IP地址");
            return;
        }
        
        // 随机生成状态和CPU使用率
        QString status = (qrand() % 2 == 0) ? "在线" : "离线";
        int cpu = (status == "在线") ? (qrand() % 100) : 0;
        
        m_deviceModel->addDevice(DeviceInfo(name, ip, status, cpu));
        
        m_nameEdit->clear();
        m_ipEdit->clear();
    }
    
    void onDeleteDevice() {
        QModelIndex index = m_tableView->currentIndex();
        if (index.isValid()) {
            m_deviceModel->removeDevice(index.row());
        }
    }
    
    void onRefreshData() {
        // 模拟数据刷新
        int rowCount = m_deviceModel->rowCount(QModelIndex());
        for (int i = 0; i < rowCount; ++i) {
            DeviceInfo device = m_deviceModel->getDevice(i);
            if (device.status == "在线") {
                device.cpuUsage = qrand() % 100;
            }
            // 通知视图数据已改变
            QModelIndex index = m_deviceModel->index(i, 3);
            m_deviceModel->setData(index, QString("%1%").arg(device.cpuUsage));
        }
    }

private:
    // 列表视图相关
    QListView* m_listView;
    QStringListModel* m_stringListModel;
    
    // 树形视图相关
    QTreeView* m_treeView;
    QStandardItemModel* m_standardModel;
    
    // 表格视图相关
    QTableView* m_tableView;
    DeviceTableModel* m_deviceModel;
    QLineEdit* m_nameEdit;
    QLineEdit* m_ipEdit;
};

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);
    
    qsrand(QTime::currentTime().msec()); // 初始化随机数种子
    
    ModelViewDemo demo;
    demo.show();
    
    return app.exec();
}

#include "main.moc"
