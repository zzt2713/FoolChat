#ifndef C_WINDOW_H
#define C_WINDOW_H
/******************************************************************************
*
* @file       c_window.h
* @brief      聊天界面 Function
*
* @author     Fool
* @date       2026/03/08
* @history
*****************************************************************************/
#include "Setting_Page/f_setting.h"
#include "ElaWindow.h"
#include "ElaSuggestBox.h"
#include "chatpage.h"
#include "Contact_Page/contactpage.h"
#include "Notice_Page/noticepage.h"
#include "Music_Page/musicpage.h"
#include "chatuseritem.h"
#include "Chat_Page/chatdialog.h"
#include "Dynamic_Page/dynamic_page.h"
#include "Contact_Page/contactdialog.h"
#include "Editor_Page/editor_page.h"

class C_Window:public ElaWindow
{
    Q_OBJECT
public:
    explicit C_Window(QWidget* parent = nullptr);
    ~C_Window();

private:
    void initStatus();  // 状态栏
    void initToolBar(); // 工具栏
    void initWindow();  // 初始化窗口
    void initContent(); // 初始化界面内容
    void initClose();  // 关闭窗口
    void initGropMember();    //群成员显示
    void initGropAnnouncement(); // 群公告显示
    void initNav(); // 左侧导航

    template <typename T>
    void setMsgNum(T t,int n);

    F_Setting* _settingPage{nullptr};
    QString _settingKey;
    ElaText* _statusText{nullptr};
    ChatDialog* _chatDialog{nullptr};
    ChatPage* _chatPage{nullptr};
    ContactPage* _contactPage{nullptr};
    NoticePage* _noticePage{nullptr};
    MusicPage* _musicPage{nullptr};
    Dynamic_Page* _dynamicPage{nullptr};
    QMap<QString, QString> _pageTitleMap;
    ContactDialog* _contactDialog{nullptr};
    EditorPage * _editorPage{nullptr};

private slots:
    void Slot_Set_Msg_Num(QWidget* p,int n);

Q_SIGNALS:
    Q_SIGNAL void themeButtonClicked();

};

#endif // C_WINDOW_H
