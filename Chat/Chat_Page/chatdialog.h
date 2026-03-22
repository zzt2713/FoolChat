#ifndef CHATDIALOG_H
#define CHATDIALOG_H
/******************************************************************************
*
* @file       chatdialog.h
* @brief      聊天页 Function
*
* @author     Fool
* @date       2026/03/08
* @history
*****************************************************************************/
#include <QWidget>
#include "../../global.h"

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
    void addAiChat();

private:
    Ui::ChatDialog *ui;
    bool _b_loading;
    ChatUIMode _mode;
    ChatUIMode _state;

    void handleGlobalMousePress(QMouseEvent *);
    void ShowSearch(bool bsearch);

protected:
    bool eventFilter(QObject *watched, QEvent *event) override;

private slots:
    void slot_loading_chat_user();
    void slot_text_change(const QString &str);
};



#endif // CHATDIALOG_H
