#ifndef CHATPAGE_H
#define CHATPAGE_H
#include "page_base.h"
#include "ElaScrollArea.h"
#include "QSplitter"
#include "ElaTheme.h"
#include "ElaLineEdit.h"
#include "ElaSuggestBox.h"
#include "c_searchedit.h"
#include "ElaToolButton.h"
#include "chatuserlist.h"
#include <QStackedWidget>

class ChatPage : public Page_Base
{
    Q_OBJECT
public:
    Q_INVOKABLE explicit ChatPage(QWidget* parent = nullptr);
    ~ChatPage();

private:
    void initLeft();
    void initRight();
    bool _b_loading;
    // 关键组件成员变量
    QSplitter* _mainSplitter{nullptr};

    // 左侧面板
    QWidget* _leftPanel{nullptr};
    ChatUserList* _chatUserList{nullptr};
    ElaScrollArea* _listScrollArea{nullptr};
    QWidget* _listContainer{nullptr};
    QVBoxLayout* _listLayout{nullptr};
    C_SearchEdit* _searchEdit{nullptr};
    ElaToolButton* _addContactBtn{nullptr};
    QString _dynamicSearchKey;
    void loadMoreUserMsg(int count);
    int _currentContactCount = 0;  // 当前联系人数量
    bool eventFilter(QObject *watched, QEvent *event) override;

    // 右侧面板
    QWidget* _rightPanel{nullptr};
    QWidget* _chatHeader{nullptr};
    ElaScrollArea* _msgScrollArea{nullptr};
    QWidget* _msgContainer{nullptr};
    QVBoxLayout* _msgLayout{nullptr};
    QWidget* _inputPanel{nullptr};
    QVBoxLayout* _rightLayout{nullptr};
    QStackedWidget* _chatStackWidget;
    QMap<QString, QWidget*> _chatSessions;
    QWidget* _sessionPage{nullptr};

    QWidget* createChatSessionPage(const QString& userId, const QString& userName);

    // 主题更新函数
    void updateTheme(ElaThemeType::ThemeMode themeMode);
    void addTestMessagesToSession(QVBoxLayout* msgLayout);
    void addMyMessage(QVBoxLayout* msgLayout, const QString& text);

private slots:
    void slot_loading_chat_user();

    void onSendClicked();
};

#endif // CHATPAGE_H
