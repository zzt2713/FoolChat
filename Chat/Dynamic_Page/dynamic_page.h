#ifndef DYNAMIC_PAGE_H
#define DYNAMIC_PAGE_H

#include <QWidget>

namespace Ui {
class Dynamic_Page;
}

class Dynamic_Page : public QWidget
{
    Q_OBJECT

public:
    Q_INVOKABLE explicit Dynamic_Page(QWidget *parent = nullptr);
    ~Dynamic_Page();


private:
    Ui::Dynamic_Page *ui;
};

#endif // DYNAMIC_PAGE_H
