#include "chatwid.h"
#include "ui_chatwid.h"
#include <QStyleOption>
#include <QPainter>
#include "ranimg.h"
#include "global.h"
#include "ElaImageCard.h"
#include "textbubble.h"
#include "picturebubble.h"
#include "chatitembase.h"

ChatWid::ChatWid(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ChatWid)
{
    ui->setupUi(this);

    ui->emo_btn->setIsTransparent(true);
    ui->emo_btn->setElaIcon(ElaIconType::FaceSmile);
    ui->emo_btn->setToolTip("表情");

    ui->file_btn->setIsTransparent(true);
    ui->file_btn->setElaIcon(ElaIconType::File);
    ui->file_btn->setToolTip("文件");

    ui->video_btn->setIsTransparent(true);
    ui->video_btn->setElaIcon(ElaIconType::Video);
    ui->video_btn->setToolTip("视频通话");

    ui->phone_btn->setIsTransparent(true);
    ui->phone_btn->setElaIcon(ElaIconType::Phone);
    ui->phone_btn->setToolTip("语音通话");

    ui->more_btn->setIsTransparent(true);
    ui->more_btn->setElaIcon(ElaIconType::Ellipsis);
    ui->more_btn->setToolTip("更多");

    ui->status_lb->setStatus(true);

    ui->avatar_wid->setFixedSize(35,35);
    ui->avatar_wid->setBorderRadius(35 / 2);
    ui->avatar_wid->setCardImage(IMG_IMAGE("pp"));
    ui->avatar_wid->setIsPreserveAspectCrop(true);


    connect(ui->chatEdit, &MessageTextEdit::send, this, &ChatWid::on_send_btn_clicked);

}

ChatWid::~ChatWid()
{
    delete ui;
}

void ChatWid::paintEvent(QPaintEvent *event)
{
    QStyleOption opt;
    opt.initFrom(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

void ChatWid::on_send_btn_clicked()
{
    auto pTextEdit = ui->chatEdit;
    ChatRole role = ChatRole::Self;
    QString userName = QStringLiteral("Fool");
    QString userIcon = ":/logo/logo.png";

    const QVector<MsgInfo>& msgList = pTextEdit->getMsgList();
    for(int i=0; i<msgList.size(); ++i)
    {
        QString type = msgList[i].msgFlag;
        ChatItemBase *pChatItem = new ChatItemBase(role);
        pChatItem->setUserName(userName);
        pChatItem->setUserIcon(QPixmap(userIcon));
        QWidget *pBubble = nullptr;
        if(type == "text")
        {
            pBubble = new TextBubble(role, msgList[i].content);
        }
        else if(type == "image")
        {
            pBubble = new PictureBubble(QPixmap(msgList[i].content) , role);
        }
        else if(type == "file")
        {

        }
        if(pBubble != nullptr)
        {
            pChatItem->setWidget(pBubble);
            ui->chat_data_list->appendItem(pChatItem);
        }
    }
}

void ChatWid::on_emo_btn_clicked()
{
    if(!emo_pic){
        emo_pic = new ElaEmojiPicker(this);
        connect(emo_pic, &ElaEmojiPicker::emojiSelected,
            this, [this](const QString& emoji) {
            ui->chatEdit->insertPlainText(emoji);
        });
    }


    QPoint btnPos = ui->emo_btn->mapToGlobal(QPoint(0, 0));
    int btnHeight = ui->emo_btn->height();

    QPoint popupPos = btnPos + QPoint(0, -emo_pic->height());
    QRect screenGeometry = QApplication::primaryScreen()->availableGeometry();
    if (popupPos.y() < screenGeometry.top()) {
        popupPos = btnPos + QPoint(0, btnHeight);
    }

    emo_pic->popup(popupPos);

    QTimer* timer = new QTimer(this);

    connect(timer, &QTimer::timeout, this, [this, timer]() {
        if (!emo_pic || !emo_pic->isVisible()) {
            // 窗口已关闭，恢复按钮状态
            ui->emo_btn->setDown(false);
            ui->emo_btn->clearFocus();
            ui->emo_btn->update();
            ui->chatEdit->setFocus();
            timer->deleteLater();
        }
    });
    timer->start(100);
}

