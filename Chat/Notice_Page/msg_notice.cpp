#include "msg_notice.h"
#include "ui_msg_notice.h"
#include "noticeitem.h"
#include <QScrollBar>
#include <QEvent>
#include <QWheelEvent>
#include <memory>

Msg_Notice::Msg_Notice(QWidget *parent)
    : QListWidget(parent)
    , ui(new Ui::Msg_Notice)
{
    ui->setupUi(this);
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    // 安装事件过滤器
    this->viewport()->installEventFilter(this);

    //模拟从数据库或者后端传输过来的数据,进行列表加载
    addNoticeMsg();
}

Msg_Notice::~Msg_Notice()
{
    delete ui;
}

bool Msg_Notice::eventFilter(QObject *watched, QEvent *event)
{
    if (watched == this->viewport()) {
        if (event->type() == QEvent::Enter) {
            // 鼠标悬浮，显示滚动条
            this->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        } else if (event->type() == QEvent::Leave) {
            // 鼠标离开，隐藏滚动条
            this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        }
    }

    // 检查事件是否是鼠标滚轮事件
    if (watched == this->viewport() && event->type() == QEvent::Wheel) {
        QWheelEvent *wheelEvent = static_cast<QWheelEvent*>(event);
        int numDegrees = wheelEvent->angleDelta().y() / 8;
        int numSteps = numDegrees / 15; // 计算滚动步数

        // 设置滚动幅度
        this->verticalScrollBar()->setValue(this->verticalScrollBar()->value() - numSteps);

        // 检查是否滚动到底部
        QScrollBar *scrollBar = this->verticalScrollBar();
        int maxScrollValue = scrollBar->maximum();
        int currentValue = scrollBar->value();
        //int pageSize = 10; // 每页加载的联系人数量

        if (maxScrollValue - currentValue <= 0) {
            emit sig_loading_Notice_Msg();
        }

        return true; // 停止事件传递
    }

    return QListWidget::eventFilter(watched, event);
}

void Msg_Notice::addNoticeMsg()
{
    this->clear();

    // 准备测试数据（名字和消息）
    QList<QPair<QString, QString>> testMessages = {
        {"系统通知", "欢迎使用本应用！点击查看最新功能更新。"},
        {"安全提醒", "为了账号安全，建议开启双重认证。"},
        {"张三", "请求添加您为好友"},
        {"李四", "请求添加您为好友"},
        {"王五", "请求添加您为好友"},
        {"赵六", "赞了你的动态"},
        {"钱七", "评论了你的动态：太棒了！"},
        {"孙八", "转发了你的动态"},
        {"版本更新", "v2.0.0 版本发布，新增多项功能"},
        {"活动通知", "双十一特惠活动火热进行中"}
    };

    // 头像范围 1-5
    int avatarCount = 5;

    for (int i = 0; i < testMessages.size(); i++) {
        int uid = 0;
        QString name = testMessages[i].first;
        QString msg = testMessages[i].second;
        // 随机选择头像 (1-5)
        int avatarIndex = (i % avatarCount) + 1;  // 循环使用1-5
        QString avatarPath = QString(":/res/head_%1.jpg").arg(avatarIndex);

        std::shared_ptr<NoticeInfo> notice = std::make_shared<NoticeInfo>(
            uid, name, msg, avatarPath
            );

        QListWidgetItem *item = new QListWidgetItem;
        NoticeItem *noticeItem = new NoticeItem;
        // 连接关闭信号
        connect(noticeItem, &NoticeItem::sig_close,
                this, &Msg_Notice::onNoticeItemClosed);
        noticeItem->SetInfo(notice);
        item->setSizeHint(noticeItem->sizeHint());
        this->addItem(item);
        this->setItemWidget(item, noticeItem);
    }
}

void Msg_Notice::onNoticeItemClosed(QString s)
{
    for (int i = 0; i < this->count(); i++) {
        QListWidgetItem *item = this->item(i);
        NoticeItem *noticeItem = qobject_cast<NoticeItem*>(this->itemWidget(item));

        if (noticeItem && noticeItem->GetInfo()->_name == s) {  // 需要添加GetUid()函数
            delete item;  // 删除item
            break;
        }
    }
}
