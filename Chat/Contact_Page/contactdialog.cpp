#include "contactdialog.h"
#include "ui_contactdialog.h"

ContactDialog::ContactDialog(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ContactDialog),_mode(ChatUIMode::ContactMode),_state(ChatUIMode::ContactMode)
{
    setWindowTitle("联系人");
    ui->setupUi(this);
    ShowSearch(false);
    ui->search_list->SetSearchEdit(ui->search_edit);
    connect(ui->search_edit, &C_SearchEdit::textChanged, [=](const QString& text) {
        if (text.isEmpty()) {
            ShowSearch(false);
        }
    });
    connect(ui->search_edit,&C_SearchEdit::textChanged,this,&ContactDialog::slot_text_change);

    this->installEventFilter(this);
    qApp->installEventFilter(this);
}

ContactDialog::~ContactDialog()
{
    delete ui;
}

void ContactDialog::ShowSearch(bool bsearch)
{
    if(bsearch){
        ui->con_user_list->hide();
        ui->search_list->show();
        _mode = ChatUIMode::SearchMode;
    }else if(_state == ChatUIMode::ChatMode){
        ui->con_user_list->hide();
        ui->search_list->hide();
        _mode = ChatUIMode::ChatMode;
    }else if(_state == ChatUIMode::ContactMode){
        ui->search_list->hide();
        ui->con_user_list->show();
        _mode = ChatUIMode::ContactMode;
    }
}

void ContactDialog::slot_text_change(const QString &str)
{
    if(!str.isEmpty()){
        ShowSearch(true);
    }
}

bool ContactDialog::eventFilter(QObject *watched, QEvent *event)
{
    if(event->type() == QEvent::MouseButtonPress){
        QMouseEvent* mouseEvent = static_cast<QMouseEvent*>(event);
        handleGlobalMousePress(mouseEvent);

    }
    return QWidget::eventFilter(watched,event);
}


void ContactDialog::handleGlobalMousePress(QMouseEvent* event)
{
    if (_mode != ChatUIMode::SearchMode) {
        return;
    }

    QWidget* clickedWidget = QApplication::widgetAt(event->globalPos());

    // 如果点击的是当前对话框内的元素，不处理
    if (this->isAncestorOf(clickedWidget)) {
        // 检查是否是搜索相关的元素
        bool isSearchRelated = false;

        if (ui->search_edit->isAncestorOf(clickedWidget) ||
            clickedWidget == ui->search_edit) {
            isSearchRelated = true;
        }

        if (ui->search_list->isAncestorOf(clickedWidget) ||
            clickedWidget == ui->search_list) {
            isSearchRelated = true;
        }

        // 如果不是搜索相关元素，则关闭搜索
        if (!isSearchRelated) {
            ui->search_edit->clear();
            ShowSearch(false);
        }
    }
    // 如果点击的是对话框外的元素，关闭搜索
    else {
        ui->search_edit->clear();
        ShowSearch(false);
    }
}
