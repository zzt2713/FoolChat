#include "c_window.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLineEdit>
#include "ElaDef.h"
#include "ElaContentDialog.h"
#include "ElaText.h"
#include "c_window.h"
#include "chattext.h"
#include "ElaStatusBar.h"
#include "../global.h"
#include "../msgtip.h"
#include "About_Page/c_about.h"

C_Window::C_Window(QWidget *parent):ElaWindow(parent)
{
    initWindow();
    initContent();
    initClose();
    initGropAnnouncement();
    initGropMember();
    initNav();
    initStatus();
    initToolBar();
    ADDMSG(ElaMessageBarType::Top,"聊天界面初始化成功",this,1,3000);
}

C_Window::~C_Window()
{

}

void C_Window::initStatus()
{
    //状态栏
    ElaStatusBar* statusBar = new ElaStatusBar(this);
    _statusText = STAUTUS();
    // _statusText->setTextPixelSize(14);
    statusBar->addWidget(_statusText);
    // _statusText->setMaximumWidth(800);
    SET_STATUS(QString("欢迎回来,%1! ").arg(NAME));
    this->setStatusBar(statusBar);
    // 设置新状态 _statusText->setText("sadasd");
}

void C_Window::initToolBar()
{

}

void C_Window::initWindow()
{
    // setNavigationBarDisplayMode(ElaNavigationType::Compact);
    setIsAllowPageOpenInNewWindow(true);
    setUserInfoCardPixmap(QPixmap(":/icons/image.png"));  //卡片头像
    setUserInfoCardTitle(QString("%1").arg(NAME));   //卡片昵称
    setUserInfoCardSubTitle(QString("%1").arg(EMAIL));   //卡片邮箱
    setWindowTitle("Fool Chat");
    setFixedSize(1200, 680);    //窗口大小
    setNavigationBarWidth(225); //导航栏宽度
    setWindowIcon(QIcon(":/icons/image.png"));    //窗口icon
}

void C_Window::initContent()
{

}

void C_Window::initClose()
{
    ElaContentDialog* closeConfirmDialog = new ElaContentDialog(this);
    closeConfirmDialog->resize(500, 250);
    closeConfirmDialog->setStyleSheet(
        "ElaContentDialog {"
        "   background: transparent;"
        "   border-radius: 12px;"
        "}"
    );
    closeConfirmDialog->setLeftButtonText("取消");
    closeConfirmDialog->setMiddleButtonText("最小化");
    closeConfirmDialog->setRightButtonText("关闭");

    QWidget* customWidget = new QWidget(closeConfirmDialog);
    QVBoxLayout* layout = new QVBoxLayout(customWidget);
    layout->setContentsMargins(20, 30, 20, 10);

    ElaText* title = new ElaText("关闭窗口", closeConfirmDialog);
    title->setTextPixelSize(36);
    title->setTextStyle(ElaTextType::Title);

    ElaText* subTitle = new ElaText("确定要关闭窗口吗", closeConfirmDialog);
    subTitle->setTextStyle(ElaTextType::Body);

    layout->addWidget(title);
    layout->addSpacing(15);
    layout->addWidget(subTitle);
    layout->addStretch();

    closeConfirmDialog->setCentralWidget(customWidget);

    connect(closeConfirmDialog, &ElaContentDialog::rightButtonClicked, this, &C_Window::closeWindow);
    connect(closeConfirmDialog, &ElaContentDialog::middleButtonClicked, this, [=]() {
        closeConfirmDialog->close();
        showMinimized();
    });
    connect(this, &C_Window::closeButtonClicked, this, [=]() {
        closeConfirmDialog->exec();
    });

    // 禁用默认关闭
    setIsDefaultClosed(false);
}

void C_Window::initGropMember()
{

}

void C_Window::initGropAnnouncement()
{

}

void C_Window::initNav()
{
    QString chatKey,starKey,aboutKey;
    _chatPage = new ChatPage(this);
    _chatDialog = new ChatDialog(this);
    _contactPage = new ContactPage(this);
    _contactDialog = new ContactDialog(this);
    _noticePage = new NoticePage(this);
    _musicPage = new MusicPage(this);
    _dynamicPage = new Dynamic_Page(this);
    _editorPage = new EditorPage(this);


    addExpanderNode("聊天通讯", chatKey, ElaIconType::MessageDots);
    addPageNode("消息", _chatDialog, chatKey, ElaIconType::Comments);
    addPageNode("通讯录", _contactDialog, chatKey, ElaIconType::FileUser);
    addPageNode("通知", _noticePage, chatKey, ElaIconType::Bell);

    addPageNode("消息测试", _chatPage, chatKey, ElaIconType::Comments);
    addPageNode("通讯录测试", _contactPage, chatKey, ElaIconType::FileUser);

    addExpanderNode("社交动态", starKey, ElaIconType::CalendarStar);
    addPageNode("代码编辑器", _editorPage, starKey,ElaIconType::Code);
    addPageNode("音乐盒", _musicPage, starKey, ElaIconType::Music);
    addPageNode("动态", _dynamicPage, starKey, ElaIconType::Star);

    addFooterNode("关于", nullptr,aboutKey, 0, ElaIconType::User);
    C_About* aboutPage = new C_About();

    aboutPage->hide();
    connect(this, &ElaWindow::navigationNodeClicked, this, [=](ElaNavigationType::NavigationNodeType nodeType, QString nodeKey) {
        if (aboutKey == nodeKey)
        {
            aboutPage->moveToCenter();
            aboutPage->show();
        }
    });

    QString settingKey;
    _settingPage = new F_Setting(this);
    addFooterNode("设置", _settingPage, settingKey, 0, ElaIconType::Gear);

    // 展开导航
    expandNavigationNode(chatKey);
    expandNavigationNode(starKey);

    // 设置消息数
    setMsgNum(_chatPage,25);

    connect(_noticePage,&NoticePage::sig_num_msg,this,&C_Window::Slot_Set_Msg_Num);

    // 测试信号链接
    _noticePage->loadData();
}

void C_Window::Slot_Set_Msg_Num(QWidget *p, int n)
{
    setMsgNum(p,n);
}

template<typename T>
void C_Window::setMsgNum(T t, int n)
{
    QString key = t->property("ElaPageKey").toString();
    setNodeKeyPoints(key,n);
}
