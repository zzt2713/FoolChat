#ifndef CHATUSERITEM_H
#define CHATUSERITEM_H

#include <QWidget>
#include "listitembase.h"


namespace Ui {
class ChatUseritem;
}

class ChatUseritem : public ListItemBase
{
    Q_OBJECT

public:
    explicit ChatUseritem(QWidget *parent = nullptr);
    ~ChatUseritem();
    QSize sizeHint() const override;
    void SetInfo(QString name,QString head,QString msg);
    QString getName();
private:
    Ui::ChatUseritem *ui;
    QString _name;
    QString _head;
    QString _msg;
};
#endif // CHATUSERITEM_H

