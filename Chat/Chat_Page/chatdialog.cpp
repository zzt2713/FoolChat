#include "chatdialog.h"
#include "ui_chatdialog.h"
#include <QRandomGenerator>
#include "../chatuseritem.h"
#include "../loadingdlg.h"
#include <QMouseEvent>

ChatDialog::ChatDialog(QWidget *parent) :
    QWidget(parent),ui(new Ui::ChatDialog),_b_loading(false),
    _mode(ChatUIMode::ChatMode),_state(ChatUIMode::ChatMode)
{
    ui->setupUi(this);
    setWindowTitle("聊天");
    ui->search_edit->setFocusPolicy(Qt::ClickFocus);
    ui->add_btn->setIsTransparent(false);
    ui->add_btn->setElaIcon(ElaIconType::UserPlus);
    ui->add_btn->setToolTip("添加联系人");
    ui->search_list->SetSearchEdit(ui->search_edit);
    addAiChat();
    addChatUserList();

    ShowSearch(false);
    connect(ui->search_edit, &C_SearchEdit::textChanged, [=](const QString& text) {
        if (text.isEmpty()) {
            ShowSearch(false);
        }
    });
    connect(ui->chat_user_list, &ChatUserList::sig_loading_chat_user, this, &ChatDialog::slot_loading_chat_user);
    connect(ui->search_edit,&C_SearchEdit::textChanged,this,&ChatDialog::slot_text_change);


    this->installEventFilter(this);
    qApp->installEventFilter(this);
}

ChatDialog::~ChatDialog()
{
    delete ui;
}

void ChatDialog::ShowSearch(bool bsearch)
{
    if(bsearch){
        ui->chat_user_list->hide();
        ui->con_user_list->hide();
        ui->search_list->show();
        _mode = ChatUIMode::SearchMode;
    }else if(_state == ChatUIMode::ChatMode){
        ui->chat_user_list->show();
        ui->con_user_list->hide();
        ui->search_list->hide();
        _mode = ChatUIMode::ChatMode;
    }else if(_state == ChatUIMode::ContactMode){
        ui->chat_user_list->hide();
        ui->search_list->hide();
        ui->con_user_list->show();
        _mode = ChatUIMode::ContactMode;
    }
}

bool ChatDialog::eventFilter(QObject *watched, QEvent *event)
{
    if(event->type() == QEvent::MouseButtonPress){
        QMouseEvent* mouseEvent = static_cast<QMouseEvent*>(event);
        handleGlobalMousePress(mouseEvent);

    }
    return QWidget::eventFilter(watched,event);
}

void ChatDialog::addChatUserList()
{
    for(int i = 0; i < 10; i++){
        int randomValue = QRandomGenerator::global()->bounded(100);
        int str_i = randomValue%str.size();
        int head_i = randomValue%head.size();
        int name_i = randomValue%name.size();

        auto *chat_user_wid = new ChatUseritem(ui->chat_user_list);
        chat_user_wid->SetInfo(name[name_i], head[head_i], str[str_i]);
        QListWidgetItem *item = new QListWidgetItem;
        //qDebug()<<"chat_user_wid sizeHint is " << chat_user_wid->sizeHint();
        item->setSizeHint(chat_user_wid->sizeHint());
        item->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable);

        ui->chat_user_list->addItem(item);
        ui->chat_user_list->setItemWidget(item, chat_user_wid);
    }
}

void ChatDialog::addAiChat()
{
    auto *chat_user_wid = new ChatUseritem(ui->chat_user_list);
    chat_user_wid->SetInfo("AI聊天机器人",":/icons/image.png" , "你好");
    QListWidgetItem *item = new QListWidgetItem;
    item->setSizeHint(chat_user_wid->sizeHint());
    item->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable);
    chat_user_wid->setStyleSheet(  "ChatUseritem {"
                                 "   background-color: rgba(160, 160, 160, 0.1);"
                                 "}");
    ui->chat_user_list->addItem(item);
    ui->chat_user_list->setItemWidget(item, chat_user_wid);
}

void ChatDialog::handleGlobalMousePress(QMouseEvent* event)
{
    if (_mode != ChatUIMode::SearchMode) {
        return;
    }

    QWidget* clickedWidget = QApplication::widgetAt(event->globalPos());

    // 如果点击的是当前对话框内的元素，不处理
    if (this->isAncestorOf(clickedWidget)) {
        // 检查是否是搜索相关的元素
        bool isSearchRelated = false;

        if (ui->search_edit->isAncestorOf(clickedWidget) ||
            clickedWidget == ui->search_edit) {
            isSearchRelated = true;
        }

        if (ui->search_list->isAncestorOf(clickedWidget) ||
            clickedWidget == ui->search_list) {
            isSearchRelated = true;
        }

        // 如果不是搜索相关元素，则关闭搜索
        if (!isSearchRelated) {
            ui->search_edit->clear();
            ShowSearch(false);
        }
    }
    // 如果点击的是对话框外的元素，关闭搜索
    else {
        ui->search_edit->clear();
        ShowSearch(false);
    }
}

void ChatDialog::slot_loading_chat_user()
{
    if(_b_loading){
        return;
    }
    _b_loading = true;
    LoadingDlg *load = new LoadingDlg(this);
    load->setModal(true);
    load->show();
    addChatUserList();
    load->deleteLater();
    _b_loading = false;
}

void ChatDialog::slot_text_change(const QString &str)
{
    if(!str.isEmpty()){
        ShowSearch(true);
    }
}

