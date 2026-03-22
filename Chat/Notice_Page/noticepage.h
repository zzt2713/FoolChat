#ifndef NOTICEPAGE_H
#define NOTICEPAGE_H
/******************************************************************************
*
* @file       noticepage.h
* @brief      通知页 Function
*
* @author     Fool
* @date       2026/03/03
* @history
*****************************************************************************/
#include "../page_base.h"
#include "msg_notice.h"
class NoticePage:public Page_Base
{
    Q_OBJECT
public:
    Q_INVOKABLE explicit NoticePage(QWidget* parent = nullptr);
    ~NoticePage();
    void loadData();

signals:
    void sig_num_msg(QWidget*,int);
};
#endif // NOTICEPAGE_H
