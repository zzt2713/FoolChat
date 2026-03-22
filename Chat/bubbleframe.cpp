#include "bubbleframe.h"
#include <QPainter>
#include <QPainterPath>

BubbleFrame::BubbleFrame(ChatRole role, QWidget *parent)
    : QFrame(parent)
    , m_role(role)
    , m_margin(8) // 上下边距
{
    m_pHLayout = new QHBoxLayout();

    // 【修改】：把 14 改小为 8 或 10
    const int TEXT_PADDING_H = 10;

    if(m_role == ChatRole::Self)
    {
        // 自己的消息，稍微缩减一点【右边】的边距 (TEXT_PADDING_H - 2)
        m_pHLayout->setContentsMargins(
            TEXT_PADDING_H,
            m_margin,
            TEXT_PADDING_H - 2, // 让右边窄一点
            m_margin
            );
    }
    else
    {
        // 对方的消息，稍微缩减一点【左边】的边距
        m_pHLayout->setContentsMargins(
            TEXT_PADDING_H - 2,
            m_margin,
            TEXT_PADDING_H,
            m_margin
            );
    }

    this->setLayout(m_pHLayout);
}

void BubbleFrame::setMargin(int margin)
{
    m_margin = margin;
}

void BubbleFrame::setWidget(QWidget *w)
{
    if(m_pHLayout->count() > 0)
        return ;
    else{
        m_pHLayout->addWidget(w);
    }
}

void BubbleFrame::paintEvent(QPaintEvent *e)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setPen(Qt::NoPen);

    QPainterPath path;
    // 背景占满整个可用区域
    QRectF bk_rect = QRectF(0, 0, this->width(), this->height());
    qreal radius = 13.0;

    if(m_role == ChatRole::Other)
    {
        painter.setBrush(QColor("#FFFFFF"));
    }
    else
    {
        painter.setBrush(QColor("#D9EAFA"));
    }

    path.addRoundedRect(bk_rect, radius, radius);
    painter.drawPath(path);

    QFrame::paintEvent(e);
}
