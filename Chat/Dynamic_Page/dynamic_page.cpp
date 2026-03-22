#include "dynamic_page.h"
#include "ui_dynamic_page.h"
#include "ElaFloatButton.h"
#include "ElaMenu.h"

Dynamic_Page::Dynamic_Page(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Dynamic_Page)
{
    ui->setupUi(this);
    setWindowTitle("动态");

    ElaMenu* menu = new ElaMenu(this);
    QAction* publishAction = menu->addAction("发布动态");
    ui->floatBtn->setMenu(menu);

    connect(publishAction, &QAction::triggered, this, [this]() {
        // 处理发布动态的逻辑
        // todo...
    });

    connect(ui->floatBtn, &ElaFloatButton::clicked, this, [this, menu]() {
        QPoint pos = ui->floatBtn->mapToGlobal(QPoint(-ui->floatBtn->width(), -ui->floatBtn->height()));
        menu->exec(pos);
    });
}

Dynamic_Page::~Dynamic_Page()
{
    delete ui;
}
