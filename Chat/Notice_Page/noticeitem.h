#ifndef NOTICEITEM_H
#define NOTICEITEM_H

#include <QWidget>
#include "../listitembase.h"
#include "../Chat_Comp/userdata.h"

namespace Ui {
class NoticeItem;
}

class NoticeItem : public ListItemBase
{
    Q_OBJECT

public:
    explicit NoticeItem(QWidget *parent = nullptr);
    ~NoticeItem();
    QSize sizeHint() const override ;
    void SetInfo(std::shared_ptr<NoticeInfo> auth_info);
    void SetInfo(int uid, QString name, QString msg, QString icon);
    std::shared_ptr<NoticeInfo> GetInfo();

private:
    Ui::NoticeItem *ui;
    std::shared_ptr<NoticeInfo> _info;

private slots:
    void slot_close(QString);
signals:
    void sig_close(QString);
};

#endif // NOTICEITEM_H
