QT       += core gui network sql multimedia multimediawidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

CONFIG += resources_big
RESOURCES += src.qrc
# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Chat/About_Page/c_about.cpp \
    Chat/Chat_Comp/ClickedOnceLabel.cpp \
    Chat/Chat_Comp/adduseritem.cpp \
    Chat/Chat_Comp/applyfriend.cpp \
    Chat/Chat_Comp/applyfrienditem.cpp \
    Chat/Chat_Comp/applyfriendlist.cpp \
    Chat/Chat_Comp/applyfriendpage.cpp \
    Chat/Chat_Comp/contactuserlist.cpp \
    Chat/Chat_Comp/conuseritem.cpp \
    Chat/Chat_Comp/findsuccessdlg.cpp \
    Chat/Chat_Comp/frienddlabel.cpp \
    Chat/Chat_Comp/grouptipitem.cpp \
    Chat/Chat_Comp/searchlist.cpp \
    Chat/Chat_Comp/userdata.cpp \
    Chat/Chat_Page/chatdialog.cpp \
    Chat/Contact_Page/contactdialog.cpp \
    Chat/Contact_Page/contactpage.cpp \
    Chat/Dynamic_Page/dynamic_page.cpp \
    Chat/Editor_Page/editor_page.cpp \
    Chat/Music_Page/musicpage.cpp \
    Chat/Notice_Page/msg_notice.cpp \
    Chat/Notice_Page/noticeitem.cpp \
    Chat/Notice_Page/noticepage.cpp \
    Chat/Setting_Page/f_setting.cpp \
    Chat/bubbleframe.cpp \
    Chat/c_searchedit.cpp \
    Chat/c_window.cpp \
    Chat/chatpage.cpp \
    Chat/chattext.cpp \
    Chat/chatuseritem.cpp \
    Chat/chatuserlist.cpp \
    Chat/chatview.cpp \
    Chat/chatwid.cpp \
    Chat/clikedbtn.cpp \
    Chat/listitembase.cpp \
    Chat/loadingdlg.cpp \
    Chat/messagetextedit.cpp \
    Chat/page_base.cpp \
    Chat/picturebubble.cpp \
    Chat/status_label.cpp \
    Chat/chatitembase.cpp \
    Chat/textbubble.cpp \
    Logger.cpp \
    clickedlabel.cpp \
    dbmanager.cpp \
    floatingtip.cpp \
    global.cpp \
    httpmgr.cpp \
    login.cpp \
    main.cpp \
    mainwindow.cpp \
    msgtip.cpp \
    ranimg.cpp \
    regsterdialog.cpp \
    resetdialog.cpp \
    tcpmgr.cpp \
    timerbtn.cpp \
    usermgr.cpp

HEADERS += \
    Chat/About_Page/c_about.h \
    Chat/Chat_Comp/ClickedOnceLabel.h \
    Chat/Chat_Comp/adduseritem.h \
    Chat/Chat_Comp/applyfriend.h \
    Chat/Chat_Comp/applyfrienditem.h \
    Chat/Chat_Comp/applyfriendlist.h \
    Chat/Chat_Comp/applyfriendpage.h \
    Chat/Chat_Comp/contactuserlist.h \
    Chat/Chat_Comp/conuseritem.h \
    Chat/Chat_Comp/findsuccessdlg.h \
    Chat/Chat_Comp/frienddlabel.h \
    Chat/Chat_Comp/grouptipitem.h \
    Chat/Chat_Comp/searchlist.h \
    Chat/Chat_Comp/userdata.h \
    Chat/Chat_Page/chatdialog.h \
    Chat/Contact_Page/contactdialog.h \
    Chat/Contact_Page/contactpage.h \
    Chat/Dynamic_Page/dynamic_page.h \
    Chat/Editor_Page/editor_page.h \
    Chat/Music_Page/musicpage.h \
    Chat/Notice_Page/msg_notice.h \
    Chat/Notice_Page/noticeitem.h \
    Chat/Notice_Page/noticepage.h \
    Chat/Setting_Page/f_setting.h \
    Chat/bubbleframe.h \
    Chat/c_searchedit.h \
    Chat/c_window.h \
    Chat/chatpage.h \
    Chat/chattext.h \
    Chat/chatuseritem.h \
    Chat/chatuserlist.h \
    Chat/chatview.h \
    Chat/chatwid.h \
    Chat/clikedbtn.h \
    Chat/listitembase.h \
    Chat/loadingdlg.h \
    Chat/messagetextedit.h \
    Chat/page_base.h \
    Chat/picturebubble.h \
    Chat/status_label.h \
    Chat/chatitembase.h \
    Chat/textbubble.h \
    F_singleton.h \
    Logger.h \
    clickedlabel.h \
    dbmanager.h \
    floatingtip.h \
    global.h \
    httpmgr.h \
    login.h \
    mainwindow.h \
    msgtip.h \
    ranimg.h \
    regsterdialog.h \
    resetdialog.h \
    tcpmgr.h \
    timerbtn.h \
    usermgr.h

FORMS += \
    Chat/About_Page/c_about.ui \
    Chat/Chat_Comp/adduseritem.ui \
    Chat/Chat_Comp/applyfriend.ui \
    Chat/Chat_Comp/applyfrienditem.ui \
    Chat/Chat_Comp/applyfriendpage.ui \
    Chat/Chat_Comp/conuseritem.ui \
    Chat/Chat_Comp/findsuccessdlg.ui \
    Chat/Chat_Comp/frienddlabel.ui \
    Chat/Chat_Comp/grouptipitem.ui \
    Chat/Chat_Page/chatdialog.ui \
    Chat/Contact_Page/contactdialog.ui \
    Chat/Dynamic_Page/dynamic_page.ui \
    Chat/Notice_Page/msg_notice.ui \
    Chat/Notice_Page/noticeitem.ui \
    Chat/chatuseritem.ui \
    Chat/chatwid.ui \
    Chat/loadingdlg.ui \
    login.ui \
    mainwindow.ui \
    regsterdialog.ui \
    resetdialog.ui

DESTDIR = ./bin

RC_ICONS = logo/head.ico

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target


DISTFILES += \
    config.ini

# ElaWidgetTools 库配置
ELAWIDGETTOOLS_ROOT = D:/cppsoft/RabbitEla
INCLUDEPATH += $$ELAWIDGETTOOLS_ROOT/include
LIBS += -L$$ELAWIDGETTOOLS_ROOT/lib -lElaWidgetTools

CONFIG(debug, debug | release) {
    DLL_SRC = D:/cppsoft/RabbitEla/bin/ElaWidgetTools.dll
    DLL_SRC = $$replace(DLL_SRC, /, \\)
    DLL_DST = $$OUT_PWD/$$DESTDIR/ElaWidgetTools.dll
    DLL_DST = $$replace(DLL_DST, /, \\)
    QMAKE_POST_LINK += copy /Y \"$$DLL_SRC\" \"$$DLL_DST\" &

    TargetConfig = $${PWD}/config.ini
    TargetConfig = $$replace(TargetConfig, /, \\)
    OutputDir =  $${OUT_PWD}/$${DESTDIR}
    OutputDir = $$replace(OutputDir, /, \\)
    //执行copy命令
    QMAKE_POST_LINK += copy /Y \"$$TargetConfig\" \"$$OutputDir\" &

    # 首先，定义static文件夹的路径
    StaticDir = $${PWD}/static
    # 将路径中的"/"替换为"\"
    StaticDir = $$replace(StaticDir, /, \\)
    #message($${StaticDir})
    QMAKE_POST_LINK += xcopy /Y /E /I \"$$StaticDir\" \"$$OutputDir\\static\\\"

}else{
    #release
    message("release mode")

    DLL_SRC = D:/cppsoft/ElaWidgetTools/bin/ElaWidgetTools.dll
    DLL_SRC = $$replace(DLL_SRC, /, \\)
    DLL_DST = $$OUT_PWD/$$DESTDIR/ElaWidgetTools.dll
    DLL_DST = $$replace(DLL_DST, /, \\)
    QMAKE_POST_LINK += copy /Y \"$$DLL_SRC\" \"$$DLL_DST\" &

    TargetConfig = $${PWD}/config.ini
    #将输入目录中的"/"替换为"\"
    TargetConfig = $$replace(TargetConfig, /, \\)
    #将输出目录中的"/"替换为"\"
    OutputDir =  $${OUT_PWD}/$${DESTDIR}
    OutputDir = $$replace(OutputDir, /, \\)
    //执行copy命令
    QMAKE_POST_LINK += copy /Y \"$$TargetConfig\" \"$$OutputDir\"

    # 首先，定义static文件夹的路径
    StaticDir = $${PWD}/static
    # 将路径中的"/"替换为"\"
    StaticDir = $$replace(StaticDir, /, \\)
    #message($${StaticDir})
    # 使用xcopy命令拷贝文件夹，/E表示拷贝子目录及其内容，包括空目录。/I表示如果目标不存在则创建目录。/Y表示覆盖现有文件而不提示。
     QMAKE_POST_LINK += xcopy /Y /E /I \"$$StaticDir\" \"$$OutputDir\\static\\\"


}

win32-msvc*:QMAKE_CXXFLAGS += /wd"4819" /utf-8
