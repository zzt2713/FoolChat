#ifndef CHATDIALOG_H
#define CHATDIALOG_H

#include <QWidget>
#include "../global.h"

namespace Ui {
class ChatDialog;
}

class ChatDialog : public QWidget
{
    Q_OBJECT
public:
    Q_INVOKABLE explicit ChatDialog(QWidget* parent = nullptr);
    ~ChatDialog();
    void addChatUserList();

private:
    Ui::ChatDialog *ui;
    bool _b_loading;
    ChatUIMode _mode;
    ChatUIMode _state;
    void ShowSearch(bool bsearch);

private slots:
    void slot_loading_chat_user();
};



#endif // CHATDIALOG_H
