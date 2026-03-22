#ifndef CHATITEMBASE_H
#define CHATITEMBASE_H
#include <QWidget>
#include <QGridLayout>
#include "ElaText.h"
#include "global.h"

class BubbleFrame;

class ChatItemBase: public QWidget
{
    Q_OBJECT
public:
    explicit ChatItemBase(ChatRole role, QWidget *parent = nullptr);
    void setUserName(const QString &name);
    void setUserIcon(const QPixmap &icon);
    void setWidget(QWidget *w);

private:
    ChatRole _role;
    ElaText *_pNameLabel;
    QLabel *_pIconLabel;
    QWidget *_pBubble;
};

#endif // CHATITEMBASE_H
