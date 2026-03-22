#ifndef MSG_NOTICE_H
#define MSG_NOTICE_H

#include <QListWidget>

namespace Ui {
class Msg_Notice;
}

class Msg_Notice : public QListWidget
{
    Q_OBJECT

public:
    explicit Msg_Notice(QWidget *parent = nullptr);
    ~Msg_Notice();

protected:
    bool eventFilter(QObject *watched, QEvent *event) override;

private:
    Ui::Msg_Notice *ui;

    void addNoticeMsg();

private slots:
    void onNoticeItemClosed(QString s);

signals:
    void sig_loading_Notice_Msg();
};

#endif // MSG_NOTICE_H
