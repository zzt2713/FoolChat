#ifndef CHATWID_H
#define CHATWID_H

#include <QWidget>
#include "ElaEmojiPicker.h"

namespace Ui {
class ChatWid;
}

class ChatWid : public QWidget
{
    Q_OBJECT

public:
    explicit ChatWid(QWidget *parent = nullptr);
    ~ChatWid();

private:
    Ui::ChatWid *ui;
    ElaEmojiPicker * emo_pic{nullptr};

protected:
    void paintEvent(QPaintEvent *event);
private slots:
    void on_send_btn_clicked();
    void on_emo_btn_clicked();
};

#endif // CHATWID_H
