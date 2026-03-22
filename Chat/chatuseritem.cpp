#include "chatuseritem.h"
#include "ui_chatuseritem.h"
#include <QPixmap>
#include <QPainterPath>
#include <QPainter>

ChatUseritem::ChatUseritem(QWidget *parent)
    : ListItemBase(parent)
    , ui(new Ui::ChatUseritem)
{
    ui->setupUi(this);
    SetItemType(ListItemType::CHAT_USER_ITEM);

}

ChatUseritem::~ChatUseritem()
{
    delete ui;
}

QSize ChatUseritem::sizeHint() const
{
    return QSize(250,70);
}

void ChatUseritem::SetInfo(QString name, QString head, QString msg)
{
    _name = name;
    _head = head;
    _msg = msg;

    QPixmap pixmap;
    // 简化加载逻辑
    if (!pixmap.load(head)) {
        pixmap.load(":/default_avatar.png");
    }

    // 1. 获取目标大小 (优先使用真实大小，未初始化时给个保底大小，根据你的ui文件应为45)
    QSize iconSize = ui->icon_lb->size();
    if (iconSize.isEmpty() || iconSize.width() <= 0) {
        iconSize = QSize(45, 45);
    }

    // 2. 物理像素大小 (用于高分屏高清渲染)
    qreal dpr = this->devicePixelRatioF();
    QSize physicalSize = iconSize * dpr;

    // 3. 高质量等比例缩放原图
    QPixmap scaled = pixmap.scaled(physicalSize,
                                   Qt::KeepAspectRatioByExpanding,
                                   Qt::SmoothTransformation);

    // 4. 创建透明的圆形画布
    QPixmap roundPixmap(physicalSize);
    roundPixmap.fill(Qt::transparent);
    roundPixmap.setDevicePixelRatio(dpr); // 告诉画布这是高分屏素材

    // 5. 开始抗锯齿绘制
    QPainter painter(&roundPixmap);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setRenderHint(QPainter::SmoothPixmapTransform, true);

    // 切圆角
    QPainterPath path;
    path.addEllipse(0, 0, iconSize.width(), iconSize.height());
    painter.setClipPath(path);

    // 6. 【关键修复】居中画图
    scaled.setDevicePixelRatio(dpr); // 告诉 Painter 这张图也是高清的

    // 计算居中坐标 (因为画布已经设了 dpr，这里的坐标必须是逻辑坐标，绝不能再乘 dpr！)
    QPointF center((iconSize.width() - scaled.width() / dpr) / 2.0,
                   (iconSize.height() - scaled.height() / dpr) / 2.0);

    painter.drawPixmap(center, scaled);
    painter.end();

    // 7. 设置给 Label 并取消自动拉伸(因为尺寸已经完美贴合了)
    ui->icon_lb->setPixmap(roundPixmap);
    ui->icon_lb->setScaledContents(false);

    ui->user_name->setText(_name);
    ui->user_chat_lib->setText(_msg);
}

QString ChatUseritem::getName()
{
    return _name;
}
