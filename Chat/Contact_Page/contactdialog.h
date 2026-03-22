#ifndef CONTACTDIALOG_H
#define CONTACTDIALOG_H

#include <QWidget>
#include "../../global.h"
#include <QMouseEvent>

namespace Ui {
class ContactDialog;
}

class ContactDialog : public QWidget
{
    Q_OBJECT

public:
    Q_INVOKABLE explicit ContactDialog(QWidget *parent = nullptr);
    ~ContactDialog();

private:
    Ui::ContactDialog *ui;
    void ShowSearch(bool bsearch);

    ChatUIMode _mode;
    ChatUIMode _state;
    void handleGlobalMousePress(QMouseEvent *);

protected:
    bool eventFilter(QObject *watched, QEvent *event) override;
private slots:
    void slot_text_change(const QString &str);

signals:

};

#endif // CONTACTDIALOG_H
