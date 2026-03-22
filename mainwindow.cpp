#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QLabel>
#include "tcpmgr.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow),b_clear(0)
{
    ui->setupUi(this);
    setWindowFlags(Qt::Window | Qt::WindowMinimizeButtonHint | Qt::WindowCloseButtonHint | Qt::WindowStaysOnTopHint);
    // setWindowButtonFlags(
    //     ElaAppBarType::StayTopButtonHint |
    //     ElaAppBarType::ThemeChangeButtonHint |
    //     ElaAppBarType::MinimizeButtonHint |
    //     ElaAppBarType::CloseButtonHint
    // );
    setWindowTitle("Fool Chat");

    _mainStack = new QStackedWidget(this);
    setCentralWidget(_mainStack);

    _login_dlg = new login(this);
    _reg_dlg = new RegsterDialog(this);
    _res_dlg = new ResetDialog(this);

    _mainStack->addWidget(_login_dlg);
    _mainStack->addWidget(_reg_dlg);
    _mainStack->addWidget(_res_dlg);

    connect(_login_dlg, &login::switchRegister, this, &MainWindow::SlotSwitchReg);
    connect(_login_dlg, &login::switchReset, this, &MainWindow::SlotSwitchReset);
    connect(_reg_dlg, &RegsterDialog::sigSwitchLogin, this, &MainWindow::SlotSwitchLogin);
    connect(_res_dlg, &ResetDialog::switchLogin, this, &MainWindow::SlotSwitchLogin);
    connect(TcpMgr::GetInstance().get(), &TcpMgr::sig_switch_chatdlg, this, &MainWindow::SlotSwitchChat);

    _mainStack->setCurrentWidget(_login_dlg);
}

MainWindow::~MainWindow()
{
    if (_chat_dlg) {
        delete _chat_dlg;
        _chat_dlg = nullptr;
    }
    delete ui;
}

void MainWindow::SlotSwitchReg()
{
    setWindowTitle("注册账号");
    _mainStack->setCurrentWidget(_reg_dlg);
    if(b_clear>2){
        _reg_dlg->Clear();
    }

    ++ b_clear;
}

void MainWindow::SlotSwitchLogin()
{
    setWindowTitle("FoolChat");
    _mainStack->setCurrentWidget(_login_dlg);
    if(b_clear>2){
        _login_dlg->Clear();
    }
    ++ b_clear;
}

void MainWindow::SlotSwitchReset()
{
    setWindowTitle("找回密码");
    _mainStack->setCurrentWidget(_res_dlg);
    if(b_clear>2){
        _res_dlg->Clear();
    }

    ++ b_clear;
}

void MainWindow::SlotSwitchChat()
{
    // 创建聊天窗口
    if (_chat_dlg) {
        delete _chat_dlg;
    }
    _chat_dlg = new C_Window();

    // 设置聊天窗口属性
    _chat_dlg->setWindowFlags(Qt::Window);
    _chat_dlg->setWindowTitle("Fool Chat");
    _chat_dlg->show();

    // 隐藏主登录窗口
    this->hide();

    // // 释放登录相关的资源，节省内存
    // if(_login_dlg) { delete _login_dlg; _login_dlg = nullptr; }
    // if(_reg_dlg)   { delete _reg_dlg;   _reg_dlg = nullptr; }
    // if(_res_dlg)   { delete _res_dlg;   _res_dlg = nullptr; }
}
