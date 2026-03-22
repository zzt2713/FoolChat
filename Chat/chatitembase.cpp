#include "chatitembase.h"

ChatItemBase::ChatItemBase(ChatRole role, QWidget *parent):QWidget(parent),_role(role)
{
    // 用户昵称
    _pNameLabel = new ElaText();
    _pNameLabel->setObjectName("chat_user_name");
    QFont font("Microsoft YaHei");
    font.setPointSize(9);
    _pNameLabel->setFont(font);
    _pNameLabel->setFixedHeight(20);

    // 用户头像
    _pIconLabel = new QLabel();
    _pIconLabel->setScaledContents(true);
    _pIconLabel->setFixedSize(42,42);

    _pBubble = new QWidget();

    QGridLayout *pGLayout = new QGridLayout();
    pGLayout->setVerticalSpacing(3);
    pGLayout->setHorizontalSpacing(3);
    pGLayout->setContentsMargins(3,3,3,3);

    QSpacerItem *pSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);
    if(_role == ChatRole::Self)
    {
        _pNameLabel->setContentsMargins(0,0,8,0);
        _pNameLabel->setAlignment(Qt::AlignRight);
        pGLayout->addWidget(_pNameLabel, 0,1, 1,1);
        pGLayout->addWidget(_pIconLabel, 0, 2, 2,1, Qt::AlignTop);
        pGLayout->addItem(pSpacer, 1, 0, 1, 1);
        pGLayout->addWidget(_pBubble, 1,1, 1,1);
        pGLayout->setColumnStretch(0, 2);
        pGLayout->setColumnStretch(1, 3);
    }else{
        _pNameLabel->setContentsMargins(8,0,0,0);
        _pNameLabel->setAlignment(Qt::AlignLeft);
        pGLayout->addWidget(_pIconLabel, 0, 0, 2,1, Qt::AlignTop);
        pGLayout->addWidget(_pNameLabel, 0,1, 1,1);
        pGLayout->addWidget(_pBubble, 1,1, 1,1);
        pGLayout->addItem(pSpacer, 2, 2, 1, 1);
        pGLayout->setColumnStretch(1, 3);
        pGLayout->setColumnStretch(2, 2);
    }
    this->setLayout(pGLayout);
}

void ChatItemBase::setUserName(const QString &name)
{
    _pNameLabel->setText(name);
}

void ChatItemBase::setUserIcon(const QPixmap &icon)
{
    _pIconLabel->setPixmap(icon);
}

void ChatItemBase::setWidget(QWidget *w)
{
    QGridLayout *pGLayout = (qobject_cast<QGridLayout *>)(this->layout());
    pGLayout->replaceWidget(_pBubble, w);
    delete _pBubble;
    _pBubble = w;
}
