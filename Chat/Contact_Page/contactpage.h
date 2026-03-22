#ifndef CONTACTPAGE_H
#define CONTACTPAGE_H
#include "../page_base.h"
/******************************************************************************
*
* @file       contactpage.h
* @brief      通讯录 Function
*
* @author     Fool
* @date       2026/03/03
* @history
*****************************************************************************/
class ContactPage:public Page_Base
{
    Q_OBJECT
public:
    Q_INVOKABLE explicit ContactPage(QWidget* parent = nullptr);
    ~ContactPage();

};
#endif // CONTACTPAGE_H
