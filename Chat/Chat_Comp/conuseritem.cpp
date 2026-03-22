#include "conuseritem.h"
#include "ui_conuseritem.h"
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

ConUserItem::ConUserItem(QWidget *parent)
    : ListItemBase(parent)
    , ui(new Ui::ConUserItem)
{
    ui->setupUi(this);
}

ConUserItem::~ConUserItem()
{
    delete ui;
}

QSize ConUserItem::sizeHint() const
{
    return QSize(250,70);
}

void ConUserItem::SetInfo(std::shared_ptr<AuthInfo> auth_info)
{
    _info = std::make_shared<UserInfo>(auth_info);
    QPixmap pixmap(_info->_icon);
    qreal dpr = this->devicePixelRatioF();

    ui->icon_lb->setPixmap(getRoundPixmap(pixmap, ui->icon_lb->size(), dpr));
    ui->icon_lb->setScaledContents(false);
    ui->user_name_lb->setText(_info->_name);
}

void ConUserItem::SetInfo(std::shared_ptr<AuthRsp> auth_info)
{
    _info = std::make_shared<UserInfo>(auth_info);

    QPixmap pixmap(_info->_icon);

    qreal dpr = this->devicePixelRatioF();

    ui->icon_lb->setPixmap(getRoundPixmap(pixmap, ui->icon_lb->size(), dpr));
    ui->icon_lb->setScaledContents(false);
    ui->user_name_lb->setText(_info->_name);
}

void ConUserItem::SetInfo(int uid, QString name, QString icon)
{
    _info = std::make_shared<UserInfo>(uid,name,icon);

    QPixmap pixmap(_info->_icon);

    qreal dpr = this->devicePixelRatioF();

    ui->icon_lb->setPixmap(getRoundPixmap(pixmap, ui->icon_lb->size(), dpr));
    ui->icon_lb->setScaledContents(false);
    ui->user_name_lb->setText(_info->_name);
}

void ConUserItem::ShowRedPoint(bool show)
{
    if(show){
        ui->red_lb->show();
    }else{
        ui->red_lb->hide();
    }
}

void ConUserItem::addNewFriend()
{
    _info = std::make_shared<UserInfo>(0,"新的朋友","");
    ui->icon_lb->setElaIcon(ElaIconType::UserPlus);

    ui->user_name_lb->setText(_info->_name);
}
