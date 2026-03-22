#include "chatdialog.h"
#include "ui_chatdialog.h"
#include <QRandomGenerator>
#include "chatuseritem.h"
#include "loadingdlg.h"

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

    addChatUserList();

    ShowSearch(false);
    connect(ui->search_edit, &C_SearchEdit::textChanged, [=](const QString& text) {
        if (text.isEmpty()) {
            ShowSearch(false);
        }
    });
    connect(ui->chat_user_list, &ChatUserList::sig_loading_chat_user, this, &ChatDialog::slot_loading_chat_user);
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
std::vector<QString>  str ={"hello world !",
                            "nice to meet u",
                            "New year，new life",
                            "You have to love yourself",
                            "My love is written in the wind ever since the whole world is you"};

std::vector<QString> head = {
    ":/res/head_1.jpg",
    ":/res/head_2.jpg",
    ":/res/head_3.jpg",
    ":/res/head_4.jpg",
    ":/res/head_5.jpg"
};

std::vector<QString> name = {
    "llfc",
    "zack",
    "golang",
    "cpp",
    "java",
    "nodejs",
    "python",
    "rust"
};

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

