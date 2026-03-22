#include "contactpage.h"
#include "ElaText.h"
#include "ElaInteractiveCard.h"
#include "../c_searchedit.h"

ContactPage::ContactPage(QWidget *parent):Page_Base(parent)
{
    QWidget* content = new QWidget();
    content->setWindowTitle("通讯录");
    QVBoxLayout* layout = new QVBoxLayout(content);
    layout->setContentsMargins(30, 30, 30, 30);
    layout->setSpacing(15);


    layout->addStretch();

    // 添加到页面
    addCentralWidget(content);
}

ContactPage::~ContactPage()
{

}
