#include "noticeitem.h"
#include "ui_noticeitem.h"
#include <QPainter>
#include <QPainterPath>

static QPixmap getRoundPixmap(const QPixmap &src, QSize size, qreal dpr)
{
    if (src.isNull() || size.isEmpty()) return src;

    int diameter = qMin(size.width(), size.height());
    if (diameter <= 0) return src;

    QSize logicalSize(diameter, diameter);
    QSize physicalSize = logicalSize * dpr;

    QPixmap scaledSrc = src.scaled(physicalSize, Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation);
    scaledSrc.setDevicePixelRatio(dpr);

    QPixmap roundPixmap(physicalSize);
    roundPixmap.fill(Qt::transparent);
    roundPixmap.setDevicePixelRatio(dpr);

    QPainter painter(&roundPixmap);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setRenderHint(QPainter::SmoothPixmapTransform, true);

    QPainterPath path;
    path.addEllipse(0, 0, diameter, diameter);
    painter.setClipPath(path);

    qreal x = (diameter - scaledSrc.width() / dpr) / 2.0;
    qreal y = (diameter - scaledSrc.height() / dpr) / 2.0;
    painter.drawPixmap(QPointF(x, y), scaledSrc);

    return roundPixmap;
}

NoticeItem::NoticeItem(QWidget *parent)
    : ListItemBase(parent)
    , ui(new Ui::NoticeItem)
{
    ui->setupUi(this);
    ui->close_lb->setElaIcon(ElaIconType::Xmark);
    ui->close_lb->setToolTip("删除通知");
    ui->go_notice->setElaIcon(ElaIconType::AnglesRight);
    ui->go_notice->setToolTip("前往查看");
    this->setFocusPolicy(Qt::NoFocus);
    this->SetItemType(ListItemType::NOTICE_MSG_ITEM);
    connect(ui->close_lb,&ClickedOnceLabel::clicked,this,&NoticeItem::slot_close);
}

NoticeItem::~NoticeItem()
{
    delete ui;
}

QSize NoticeItem::sizeHint() const
{
    return QSize(200,80);
}

void NoticeItem::SetInfo(std::shared_ptr<NoticeInfo> auth_info)
{
    _info = std::make_shared<NoticeInfo>(auth_info);

    QPixmap pixmap(_info->_icon);
    qreal dpr = this->devicePixelRatioF();
    ui->icon_lb->setPixmap(getRoundPixmap(pixmap,ui->icon_lb->size(),dpr));
    ui->icon_lb->setScaledContents(false);
    ui->user_name_lb->setText(_info->_name);
    ui->msg_lb->setText(_info->_msg);
}

void NoticeItem::SetInfo(int uid, QString name, QString msg, QString icon)
{
    _info = std::make_shared<NoticeInfo>(uid,name,msg,icon);
    QPixmap pixmap(_info->_icon);
    qreal dpr = this->devicePixelRatioF();
    ui->icon_lb->setPixmap(getRoundPixmap(pixmap,ui->icon_lb->size(),dpr));
    ui->icon_lb->setScaledContents(false);
    ui->user_name_lb->setText(_info->_name);
    ui->msg_lb->setText(_info->_msg);
}

std::shared_ptr<NoticeInfo> NoticeItem::GetInfo()
{
    return _info;
}

void NoticeItem::slot_close(QString s)
{
    sig_close(ui->user_name_lb->text());
}


