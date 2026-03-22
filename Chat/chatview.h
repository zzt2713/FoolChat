#ifndef CHATVIEW_H
#define CHATVIEW_H
#include <QWidget>
#include <QVBoxLayout>
#include "ElaScrollArea.h"

class ChatView:public QWidget
{
    Q_OBJECT
public:
    explicit ChatView(QWidget* parent = Q_NULLPTR);
    ~ChatView();
    void appendItem(QWidget* item);
    void prependItem(QWidget* item);
    void insertItem(QWidget* before,QWidget* item);
protected:
    bool eventFilter(QObject *o, QEvent *e) override;
    void paintEvent(QPaintEvent *event) override;
private slots:
    void onVScrollBarMoved(int min, int max);
private:
    void initStyleSheet();

    QVBoxLayout *m_pVl;
    ElaScrollArea *m_pScrollArea;
    bool isAppended;
};
#endif // CHATVIEW_H
