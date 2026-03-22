#include "applyfrienditem.h"
#include "ui_applyfrienditem.h"
#include <QPainter>
#include <QPainterPath>

static QPixmap getRoundPixmap(const QPixmap &src, QSize size, qreal dpr)
{
    if (src.isNull() || size.isEmpty()) return src;

    // 取宽高中较小的值作为正圆的直径 (逻辑大小)
    int diameter = qMin(size.width(), size.height());
    if (diameter <= 0) return src;

    // 计算物理分辨率大小 (用来保证高分屏下绝对清晰)
    QSize logicalSize(diameter, diameter);
    QSize physicalSize = logicalSize * dpr;

    // 1. 将原图等比例拉伸/缩小到【物理大小】
    QPixmap scaledSrc = src.scaled(physicalSize, Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation);
    scaledSrc.setDevicePixelRatio(dpr); // 告诉Qt这是一张高清图

    // 2. 准备完全透明的【高清画布】
    QPixmap roundPixmap(physicalSize);
    roundPixmap.fill(Qt::transparent);
    roundPixmap.setDevicePixelRatio(dpr);

    // 3. 开始抗锯齿绘制
    QPainter painter(&roundPixmap);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setRenderHint(QPainter::SmoothPixmapTransform, true);

    // 4. 定义圆形裁剪路径 (因为画布设了dpr，这里的坐标用【逻辑大小】即可)
    QPainterPath path;
    path.addEllipse(0, 0, diameter, diameter);
    painter.setClipPath(path);

    // 5. 完美居中绘制 (防止长方形图片裁剪偏向左上角)
    qreal x = (diameter - scaledSrc.width() / dpr) / 2.0;
    qreal y = (diameter - scaledSrc.height() / dpr) / 2.0;
    painter.drawPixmap(QPointF(x, y), scaledSrc);

    return roundPixmap;
}

ApplyFriendItem::ApplyFriendItem(QWidget *parent)
    : ListItemBase(parent)
    , ui(new Ui::ApplyFriendItem),_added(false)
{
    ui->setupUi(this);
    SetItemType(ListItemType::APPLY_FRIEND_ITEM);
    ui->addBtn->hide();
    connect(ui->addBtn, &ClikedBtn::clicked,  [this](){
        emit this->sig_auth_friend(_apply_info);
    });
}

ApplyFriendItem::~ApplyFriendItem()
{
    delete ui;
}

QSize ApplyFriendItem::sizeHint() const
{
    return QSize(250, 80); // 返回自定义的尺寸
}

void ApplyFriendItem::SetInfo(std::shared_ptr<ApplyInfo> apply_info)
{
    _apply_info = apply_info;
    // 加载图片
    QPixmap pixmap(_apply_info->_icon);

    qreal dpr = this->devicePixelRatioF();
    ui->icon_lb->setPixmap(getRoundPixmap(pixmap, ui->icon_lb->size(), dpr));
    ui->user_name_lb->setText(_apply_info->_name);
    ui->user_chat_lb->setText(_apply_info->_desc);
}

void ApplyFriendItem::ShowAddBtn(bool bshow)
{
    if (bshow) {
        ui->addBtn->show();
        ui->already_add_lb->hide();
        _added = false;
    }
    else {
        ui->addBtn->hide();
        ui->already_add_lb->show();
        _added = true;
    }
}

int ApplyFriendItem::GetUid() {
    return _apply_info->_uid;
}
