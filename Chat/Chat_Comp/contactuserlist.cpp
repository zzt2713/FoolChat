#include "contactuserlist.h"
#include "tcpmgr.h"
#include "../../global.h"
#include "../listitembase.h"
#include <QRandomGenerator>
#include "conuseritem.h"
#include "grouptipitem.h"

ContactUserList::ContactUserList(QWidget *parent):QListWidget(parent)
{
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    // 安装事件过滤器
    this->viewport()->installEventFilter(this);

    //模拟从数据库或者后端传输过来的数据,进行列表加载
    addContactUserList();
    //连接点击的信号和槽
    connect(this, &QListWidget::itemClicked, this, &ContactUserList::slot_item_clicked);
    //    //链接对端同意认证后通知的信号
    //    connect(TcpMgr::GetInstance().get(), &TcpMgr::sig_add_auth_friend,this,
    //            &ContactUserList::slot_add_auth_firend);

    //    //链接自己点击同意认证后界面刷新
    //    connect(TcpMgr::GetInstance().get(), &TcpMgr::sig_auth_rsp,this,
    //            &ContactUserList::slot_auth_rsp);
}

void ContactUserList::ShowRedPoint(bool bshow)
{
    _add_friend_item->ShowRedPoint(bshow);
}

ContactUserList::~ContactUserList()
{

}

bool ContactUserList::eventFilter(QObject *watched, QEvent *event)
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
            // 滚动到底部，加载新的联系人
            qDebug()<<"load more contact user";
            //发送信号通知聊天界面加载更多聊天内容
            emit sig_loading_contact_user();
        }

        return true; // 停止事件传递
    }

    return QListWidget::eventFilter(watched, event);
}

void ContactUserList::addContactUserList()
{
    auto * groupTip = new GroupTipItem();
    groupTip->setAttribute(Qt::WA_StyledBackground, true);
    groupTip->setStyleSheet("background-color: #eaeaea; border: none;");

    QListWidgetItem *item = new QListWidgetItem;
    item->setSizeHint(groupTip->sizeHint());
    this->addItem(item);
    this->setItemWidget(item, groupTip);
    // 保持不可选中状态
    item->setFlags(item->flags() & ~Qt::ItemIsSelectable);

    // 添加新的朋友条目
    _add_friend_item = new ConUserItem();
    _add_friend_item->setObjectName("new_friend_item");
    _add_friend_item->addNewFriend();
    _add_friend_item->SetItemType(ListItemType::APPLY_FRIEND_ITEM);

    QListWidgetItem *add_item = new QListWidgetItem;
    add_item->setSizeHint(_add_friend_item->sizeHint());
    this->addItem(add_item);
    this->setItemWidget(add_item, _add_friend_item);

    auto * groupCon = new GroupTipItem();
    groupCon->SetGroupTip(tr("联系人"));

    groupCon->setAttribute(Qt::WA_StyledBackground, true);
    groupCon->setStyleSheet("background-color: #eaeaea; border: none;");

    _groupitem = new QListWidgetItem;
    _groupitem->setSizeHint(groupCon->sizeHint());
    this->addItem(_groupitem);
    this->setItemWidget(_groupitem, groupCon);
    // 保持不可选中状态
    _groupitem->setFlags(_groupitem->flags() & ~Qt::ItemIsSelectable);


    // 创建正常的联系人条目
    for(int i = 0; i < 13; i++){
        int randomValue = QRandomGenerator::global()->bounded(100);
        int str_i = randomValue % str.size();
        int head_i = randomValue % head.size();
        int name_i = randomValue % name.size();

        auto *con_user_wid = new ConUserItem();
        con_user_wid->SetInfo(0, name[name_i], head[head_i]);
        QListWidgetItem *item = new QListWidgetItem;
        item->setSizeHint(con_user_wid->sizeHint());
        this->addItem(item);
        this->setItemWidget(item, con_user_wid);
    }
}

void ContactUserList::slot_item_clicked(QListWidgetItem *item)
{
    QWidget* wid = this->itemWidget(item);
    if(!wid){
        return ;
    }

    ListItemBase* it = qobject_cast<ListItemBase*>(wid);
    if(!it){
        return ;
    }

    auto itemType = it->GetItemType();
    if(itemType == ListItemType::INVALID_ITEM
        || itemType == ListItemType::GROUP_TIP_ITEM){
        qDebug()<< "slot invalid item clicked ";
        return;
    }

    if(itemType == ListItemType::APPLY_FRIEND_ITEM){
        // 创建对话框，提示用户
        qDebug()<< "apply friend item clicked ";
        //跳转到好友申请界面
        emit sig_switch_apply_friend_page();
        return;
    }

    if(itemType == ListItemType::CONTACT_USER_ITEM){
        // 创建对话框，提示用户
        qDebug()<< "contact user item clicked ";
        //跳转到好友申请界面
        emit sig_switch_friend_info_page();
        return;
    }
}
