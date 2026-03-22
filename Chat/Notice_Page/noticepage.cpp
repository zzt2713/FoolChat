#include "noticepage.h"
#include <QLabel>
#include <QListWidget>
#include <QListWidgetItem>
#include "../Chat_Comp/applyfriendpage.h""

NoticePage::NoticePage(QWidget *parent):Page_Base(parent)
{
    setWindowTitle("通知");
    QWidget* content = new QWidget();
    content->setWindowTitle("通知");
    QVBoxLayout* layout = new QVBoxLayout(content);
    layout->setContentsMargins(30, 30, 30, 30);
    layout->setSpacing(15);

    Msg_Notice* listWidget = new Msg_Notice();

    listWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    layout->addWidget(listWidget);

    addCentralWidget(content);
}

NoticePage::~NoticePage()
{

}

void NoticePage::loadData()
{
    emit sig_num_msg(this, 25);
}
