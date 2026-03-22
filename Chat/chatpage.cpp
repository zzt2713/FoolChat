#include "chatpage.h"
#include "ElaText.h"
#include "ElaInteractiveCard.h"
#include "ElaPushButton.h"
#include "ElaScrollArea.h"
#include "ElaPlainTextEdit.h"
#include "ElaMenu.h"
#include "ElaIcon.h"
#include "ElaTheme.h"
#include "QHBoxLayout"
#include "QVBoxLayout"
#include "QSplitter"
#include "ranimg.h"
#include <QColor>
#include <QScrollBar>
#include <QStandardItemModel>
#include "chatuseritem.h"
#include <QRandomGenerator>
#include "chatuserlist.h"
#include "LoadingDlg.h"

ChatPage::ChatPage(QWidget *parent) : Page_Base(parent),_b_loading(false)
{
    setTitleVisible(false);
    setWindowTitle("聊天");

    // 主布局
    _mainSplitter = new QSplitter(Qt::Horizontal);
    _mainSplitter->setChildrenCollapsible(false);
    _mainSplitter->setHandleWidth(1);

    // 左侧：联系人列表
    initLeft();
    // 右侧：聊天窗口
    initRight();

    _mainSplitter->addWidget(_leftPanel);
    _mainSplitter->addWidget(_rightPanel);
    _mainSplitter->setStretchFactor(0, 0);
    _mainSplitter->setStretchFactor(1, 1);

    addCentralWidget(_mainSplitter);

    connect(eTheme, &ElaTheme::themeModeChanged, this, &ChatPage::updateTheme);
    updateTheme(eTheme->getThemeMode());
}

void ChatPage::updateTheme(ElaThemeType::ThemeMode themeMode)
{
    QString fixedBg;
    QString borderColor;

    if (themeMode == ElaThemeType::Light) {
        fixedBg = "rgba(247, 247, 247, 255)";
        borderColor = "rgba(224, 224, 224, 255)";
    } else {
        fixedBg = "rgba(40, 40, 40, 255)";
        borderColor = "rgba(60, 60, 60, 255)";
    }

    _leftPanel->setStyleSheet("background-color: transparent;");

    if (_chatUserList) {
        _chatUserList->setStyleSheet("background-color: transparent; border: none;");
    }

    for (QWidget* _sessionPage : _chatSessions) {
        _sessionPage->setStyleSheet("background-color: transparent;");
    }
}
void ChatPage::slot_loading_chat_user()
{
    if(_b_loading){
        return;
    }
    _b_loading = true;
    LoadingDlg *load = new LoadingDlg(this);
    load->setModal(true);
    load->show();
    loadMoreUserMsg(10);
    load->deleteLater();
    _b_loading = false;
}

void ChatPage::onSendClicked()
{
    // 1. 获取发送按钮的信号发送者
    ElaToolButton* sendBtn = qobject_cast<ElaToolButton*>(sender());
    if (!sendBtn) {
        qDebug() << "无法获取发送按钮";
        return;
    }

    // 2. 直接从按钮属性获取当前会话页面
    QVariant sessionVariant = sendBtn->property("sessionPage");
    QWidget* currentSession = nullptr;
    if (sessionVariant.isValid() && sessionVariant.canConvert<QWidget*>()) {
        currentSession = sessionVariant.value<QWidget*>();
    }

    if (!currentSession) {
        qDebug() << "无法获取当前会话页面";
        return;
    }

    qDebug() << "成功获取会话页面:" << currentSession;

    // 3. 获取文本输入框
    QVariant textVariant = currentSession->property("textInput");
    ElaPlainTextEdit* textInput = nullptr;
    if (textVariant.isValid() && textVariant.canConvert<ElaPlainTextEdit*>()) {
        textInput = textVariant.value<ElaPlainTextEdit*>();
    }

    if (!textInput) {
        qDebug() << "无法获取文本输入框";
        return;
    }

    // 4. 获取输入的文本并去除首尾空格
    QString text = textInput->toPlainText().trimmed();

    // 5. 检查是否为空消息
    if (text.isEmpty()) {
        qDebug() << "不能发送空消息";
        return;
    }

    // 6. 获取消息布局
    QVariant layoutVariant = currentSession->property("msgLayout");
    QVBoxLayout* msgLayout = nullptr;
    if (layoutVariant.isValid() && layoutVariant.canConvert<QVBoxLayout*>()) {
        msgLayout = layoutVariant.value<QVBoxLayout*>();
    }

    if (!msgLayout) {
        qDebug() << "无法获取消息布局";
        return;
    }

    // 7. 获取滚动区域
    QVariant scrollVariant = currentSession->property("msgScrollArea");
    ElaScrollArea* scrollArea = nullptr;
    if (scrollVariant.isValid() && scrollVariant.canConvert<ElaScrollArea*>()) {
        scrollArea = scrollVariant.value<ElaScrollArea*>();
    }

    // 8. 清空输入框
    textInput->clear();

    // 9. 添加我的消息到列表
    addMyMessage(msgLayout, text);

    // 10. 滚动到底部
    if (scrollArea) {
        QScrollBar* vScrollBar = scrollArea->verticalScrollBar();
        if (vScrollBar) {
            vScrollBar->setValue(vScrollBar->maximum());
        }
    }

    // 11. 让输入框重新获得焦点
    textInput->setFocus();

    // 12. 打印调试信息
    qDebug() << "消息已发送:" << text;
}

// 添加我的消息
void ChatPage::addMyMessage(QVBoxLayout* msgLayout, const QString& text)
{
    const int MAX_MSG_WIDTH = 450;

    // 创建我的消息widget
    QWidget* sendWidget = new QWidget();
    QHBoxLayout* sendLayout = new QHBoxLayout(sendWidget);
    sendLayout->setContentsMargins(0, 0, 0, 0);

    // 气泡卡片
    ElaInteractiveCard* bubbleCard = new ElaInteractiveCard();
    bubbleCard->setBorderRadius(12);
    bubbleCard->setStyleSheet(
        "ElaInteractiveCard {"
        "   background-color: #95EC69;"
        "   padding: 8px 12px;"
        "}"
        );

    QVBoxLayout* bubbleLayout = new QVBoxLayout(bubbleCard);
    bubbleLayout->setContentsMargins(12, 8, 12, 8);

    // 消息文本
    ElaText* sendText = new ElaText(text);
    sendText->setTextPixelSize(14);
    sendText->setTextStyle(ElaTextType::Body);
    sendText->setWordWrap(true);
    sendText->setMaximumWidth(MAX_MSG_WIDTH);
    sendText->setTextInteractionFlags(Qt::TextSelectableByMouse);
    sendText->setStyleSheet("background-color: transparent; border: none;");

    bubbleLayout->addWidget(sendText);

    // 我的头像
    ElaInteractiveCard* sendAvatar = new ElaInteractiveCard();
    sendAvatar->setFixedSize(36, 36);
    sendAvatar->setCardPixmapSize(36, 36);
    sendAvatar->setBorderRadius(18);
    // 设置头像图片，可以使用默认头像
    // sendAvatar->setCardPixmap(QPixmap(":/logo/logo.png"));

    sendLayout->addStretch();
    sendLayout->addWidget(bubbleCard);
    sendLayout->addSpacing(8);
    sendLayout->addWidget(sendAvatar);

    // 插入到消息布局中（在stretch之前）
    msgLayout->insertWidget(msgLayout->count() - 1, sendWidget);
}

ChatPage::~ChatPage(){

}

void ChatPage::initLeft()
{
    _leftPanel = new QWidget();
    _leftPanel->setFixedWidth(280);

    QVBoxLayout* leftLayout = new QVBoxLayout(_leftPanel);
    leftLayout->setContentsMargins(0, 0, 0, 0);
    leftLayout->setSpacing(0);

    // 搜索区域
    QWidget* topSearchWidget = new QWidget();
    topSearchWidget->setFixedHeight(60);

    QHBoxLayout* searchLayout = new QHBoxLayout(topSearchWidget);
    searchLayout->setContentsMargins(10, 10, 10, 10);

    _searchEdit = new C_SearchEdit(this);
    _searchEdit->setFixedHeight(36);
    _searchEdit->setPlaceholderText("搜索联系人...");
    searchLayout->addWidget(_searchEdit);

    ElaToolButton* addContactBtn = new ElaToolButton();
    addContactBtn->setFixedSize(36, 36);
    addContactBtn->setIsTransparent(false);
    addContactBtn->setElaIcon(ElaIconType::UserPlus);
    addContactBtn->setToolTip("添加联系人");
    searchLayout->addWidget(addContactBtn);
    leftLayout->addWidget(topSearchWidget);

    _chatUserList = new ChatUserList(this);

    connect(_chatUserList, &QListWidget::itemClicked, this, [this](QListWidgetItem* item) {
        if (!item) return;

        ChatUseritem* userWidget = qobject_cast<ChatUseritem*>(_chatUserList->itemWidget(item));
        if (userWidget) {
            qDebug() << "选中（未切换）:" << userWidget->getName();
        }
    });
    connect(_chatUserList, &QListWidget::itemDoubleClicked, this, [this](QListWidgetItem* item) {
        ChatUseritem* userWidget = qobject_cast<ChatUseritem*>(_chatUserList->itemWidget(item));
        if (!userWidget) {
            return;
        }
        QString userId = userWidget->getName();
        QString userName = userWidget->getName();

        if (!_chatSessions.contains(userId)) {
            QWidget* _sessionPage = createChatSessionPage(userId, userName);
            _chatSessions[userId] = _sessionPage;
            _chatStackWidget->addWidget(_sessionPage);
        }

        _chatStackWidget->setCurrentWidget(_chatSessions[userId]);
    });

    connect(_chatUserList, &ChatUserList::sig_loading_chat_user, this, [this]() {
        qDebug() << "加载更多联系人";
        slot_loading_chat_user();
    });

    leftLayout->addWidget(_chatUserList, 1);

    loadMoreUserMsg(10);
}

void ChatPage::initRight()
{
    _rightPanel = new QWidget();
    _rightLayout = new QVBoxLayout(_rightPanel);
    _rightLayout->setContentsMargins(0, 0, 0, 0);
    _rightLayout->setSpacing(0);

    _chatStackWidget = new QStackedWidget();
    _rightLayout->addWidget(_chatStackWidget);

    QWidget* welcomePage = new QWidget();
    QVBoxLayout* welcomeLayout = new QVBoxLayout(welcomePage);
    welcomeLayout->setAlignment(Qt::AlignCenter);

    ElaText* welcomeText = new ElaText("请选择一个联系人开始聊天");
    welcomeText->setAlignment(Qt::AlignCenter);
    welcomeText->setTextPixelSize(18);
    welcomeText->setTextStyle(ElaTextType::Body);

    welcomeLayout->addWidget(welcomeText);

    _chatStackWidget->addWidget(welcomePage);
    _chatStackWidget->setCurrentIndex(0);
}


std::vector<QString>  strs ={"hello world !",
                             "nice to meet u",
                             "New year，new life",
                             "You have to love yourself",
                             "My love is written in the wind ever since the whole world is you"};

std::vector<QString> heads = {
    ":/res/head_1.jpg",
    ":/res/head_2.jpg",
    ":/res/head_3.jpg",
    ":/res/head_4.jpg",
    ":/res/head_5.jpg"
};

std::vector<QString> names = {
    "llfc",
    "zack",
    "golang",
    "cpp",
    "java",
    "nodejs",
    "python",
    "rust"
};

void ChatPage::loadMoreUserMsg(int count)
{
    for(int i = 0; i < count; i++){
        int randomValue = QRandomGenerator::global()->bounded(100); // 生成0到99之间的随机整数
        int str_i = randomValue%strs.size();
        int head_i = randomValue%heads.size();
        int name_i = randomValue%names.size();

        auto *chat_user_wid = new ChatUseritem(_chatUserList);
        chat_user_wid->SetInfo(names[name_i], heads[head_i], strs[str_i]);
        QListWidgetItem *item = new QListWidgetItem;
        //qDebug()<<"chat_user_wid sizeHint is " << chat_user_wid->sizeHint();
        item->setSizeHint(chat_user_wid->sizeHint());
        item->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable);

        _chatUserList->addItem(item);
        _chatUserList->setItemWidget(item, chat_user_wid);
    }
}

bool ChatPage::eventFilter(QObject *watched, QEvent *event)
{
    if (watched == _listScrollArea) {
        if (event->type() == QEvent::Enter) {
            _listScrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
        } else if (event->type() == QEvent::Leave) {
            _listScrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        }
    }
    return Page_Base::eventFilter(watched, event);
}

QWidget* ChatPage::createChatSessionPage(const QString& userId, const QString& userName)
{
    _sessionPage = new QWidget();
    QVBoxLayout* sessionLayout = new QVBoxLayout(_sessionPage);
    sessionLayout->setContentsMargins(0, 0, 0, 0);
    sessionLayout->setSpacing(0);

    // ========== 1. 聊天头部 ==========
    QWidget* chatHeader = new QWidget();
    chatHeader->setFixedHeight(60);
    chatHeader->setStyleSheet("background-color: transparent;");

    QHBoxLayout* headerLayout = new QHBoxLayout(chatHeader);
    headerLayout->setContentsMargins(15, 0, 15, 0);

    ElaInteractiveCard* peerAvatar = new ElaInteractiveCard();
    peerAvatar->setFixedSize(40, 40);
    peerAvatar->setCardPixmapSize(40, 40);
    peerAvatar->setBorderRadius(20);

    QWidget* peerInfo = new QWidget();
    QVBoxLayout* peerInfoLayout = new QVBoxLayout(peerInfo);
    peerInfoLayout->setContentsMargins(0, 0, 0, 0);
    peerInfoLayout->setSpacing(2);

    ElaText* peerName = new ElaText(userName);
    peerName->setTextStyle(ElaTextType::BodyStrong);
    peerName->setTextPixelSize(14);

    ElaText* peerStatus = new ElaText("在线");
    peerStatus->setTextPixelSize(11);
    peerStatus->setTextStyle(ElaTextType::Caption);
    peerStatus->setStyleSheet("color: #67C23A;");

    peerInfoLayout->addWidget(peerName);
    peerInfoLayout->addWidget(peerStatus);

    headerLayout->addWidget(peerAvatar);
    headerLayout->addSpacing(10);
    headerLayout->addWidget(peerInfo, 1);
    headerLayout->addStretch();

    ElaToolButton* videoBtn = new ElaToolButton();
    videoBtn->setFixedSize(32, 32);
    videoBtn->setIsTransparent(true);
    videoBtn->setElaIcon(ElaIconType::Video);
    videoBtn->setToolTip("视频通话");

    ElaToolButton* phoneBtn = new ElaToolButton();
    phoneBtn->setFixedSize(32, 32);
    phoneBtn->setIsTransparent(true);
    phoneBtn->setElaIcon(ElaIconType::Phone);
    phoneBtn->setToolTip("语音通话");

    ElaToolButton* moreBtn = new ElaToolButton();
    moreBtn->setFixedSize(32, 32);
    moreBtn->setIsTransparent(true);
    moreBtn->setElaIcon(ElaIconType::Ellipsis);
    moreBtn->setToolTip("更多");

    headerLayout->addWidget(videoBtn);
    headerLayout->addSpacing(5);
    headerLayout->addWidget(phoneBtn);
    headerLayout->addSpacing(5);
    headerLayout->addWidget(moreBtn);

    // ========== 2. 消息滚动区域 ==========
    ElaScrollArea* msgScrollArea = new ElaScrollArea();
    msgScrollArea->setWidgetResizable(true);
    msgScrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    msgScrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);

    QWidget* msgContainer = new QWidget();
    msgContainer->setStyleSheet("background-color: transparent;");

    QVBoxLayout* msgLayout = new QVBoxLayout(msgContainer);
    msgLayout->setContentsMargins(15, 15, 15, 15);
    msgLayout->setSpacing(15);
    msgLayout->addStretch();  // 重要：保持消息在底部

    // 添加时间标签
    ElaText* timeLabel = new ElaText("今天 14:30");
    timeLabel->setAlignment(Qt::AlignCenter);
    timeLabel->setTextPixelSize(11);
    timeLabel->setTextStyle(ElaTextType::Caption);
    msgLayout->insertWidget(msgLayout->count() - 1, timeLabel);

    msgScrollArea->setWidget(msgContainer);

    // ========== 3. 输入面板（整合原_inputPanel代码） ==========
    QWidget* inputPanel = new QWidget();
    inputPanel->setFixedHeight(200);

    QVBoxLayout* inputVLayout = new QVBoxLayout(inputPanel);
    inputVLayout->setContentsMargins(12, 8, 12, 12);
    inputVLayout->setSpacing(6);

    // 工具栏
    QHBoxLayout* toolBarLayout = new QHBoxLayout();
    toolBarLayout->setContentsMargins(0, -20, 0, 0);
    toolBarLayout->setSpacing(8);

    ElaToolButton* emojiBtn = new ElaToolButton();
    emojiBtn->setFixedSize(24, 24);
    emojiBtn->setIsTransparent(true);
    emojiBtn->setElaIcon(ElaIconType::FaceSmile);
    emojiBtn->setToolTip("表情");

    ElaToolButton* fileBtn = new ElaToolButton();
    fileBtn->setFixedSize(24, 24);
    fileBtn->setIsTransparent(true);
    fileBtn->setElaIcon(ElaIconType::File);
    fileBtn->setToolTip("文件");

    toolBarLayout->addWidget(emojiBtn);
    toolBarLayout->addWidget(fileBtn);
    toolBarLayout->addStretch();

    inputVLayout->addLayout(toolBarLayout);

    // 输入框
    ElaPlainTextEdit* textInput = new ElaPlainTextEdit();
    textInput->setPlaceholderText("输入消息...");
    textInput->setFixedHeight(110);
    textInput->setFrameShape(QFrame::NoFrame);
    inputVLayout->addWidget(textInput);
    inputVLayout->addStretch();

    // 接收、发送按钮行
    QHBoxLayout* btnLayout = new QHBoxLayout();
    btnLayout->setContentsMargins(0, 0, 0, 0);
    btnLayout->setSpacing(5);
    btnLayout->addStretch();

    ElaToolButton* receiveBtn = new ElaToolButton();
    receiveBtn->setFixedSize(100, 30);
    receiveBtn->setIsTransparent(true);
    receiveBtn->setText("接收");
    receiveBtn->setToolTip("接收");
    receiveBtn->setStyleSheet(
        "ElaToolButton {"
        "   background-color: #E0E0E0;"
        "   border-radius: 4px;"
        "   color: #666666;"
        "   padding: 0;"
        "   text-align: center;"
        "}"
        "ElaToolButton:hover {"
        "   background-color: #D0D0D0;"
        "}"
        );

    ElaToolButton* sendBtn = new ElaToolButton();
    sendBtn->setFixedSize(100, 30);
    sendBtn->setIsTransparent(false);
    sendBtn->setText("发送");
    sendBtn->setStyleSheet(
        "ElaToolButton {"
        "   background-color: #E0E0E0;"
        "   border-radius: 4px;"
        "   color: #666666;"
        "   padding: 0;"
        "   text-align: center;"
        "}"
        "ElaToolButton:hover {"
        "   background-color: #D0D0D0;"
        "}"
        );
    sendBtn->setToolTip("发送");

    btnLayout->addWidget(receiveBtn);
    btnLayout->addWidget(sendBtn);
    inputVLayout->addLayout(btnLayout);

    // ========== 4. 组装页面 ==========
    sessionLayout->addWidget(chatHeader);
    sessionLayout->addWidget(msgScrollArea, 1);
    sessionLayout->addWidget(inputPanel);

    _sessionPage->setProperty("msgLayout", QVariant::fromValue(msgLayout));
    _sessionPage->setProperty("msgScrollArea", QVariant::fromValue(msgScrollArea));
    _sessionPage->setProperty("userId", userId);

    _sessionPage->setProperty("textInput", QVariant::fromValue(textInput));
    _sessionPage->setProperty("sendBtn", QVariant::fromValue(sendBtn));
    _sessionPage->setProperty("receiveBtn", QVariant::fromValue(receiveBtn));

    // 在 createChatSessionPage 函数中，连接信号之前添加
    sendBtn->setProperty("sessionPage", QVariant::fromValue(_sessionPage));

    connect(sendBtn, &ElaToolButton::clicked, this, [this]() {
        this->onSendClicked();
    });

    addTestMessagesToSession(msgLayout);

    return _sessionPage;
}

void ChatPage::addTestMessagesToSession(QVBoxLayout* msgLayout)
{
    const int MAX_MSG_WIDTH = 450;

    for (int i = 0; i < 5; i++) {
        if (i % 2 == 0) {
            // 对方的消息
            QWidget* receiveWidget = new QWidget();
            QHBoxLayout* receiveLayout = new QHBoxLayout(receiveWidget);
            receiveLayout->setContentsMargins(0, 0, 0, 0);

            ElaInteractiveCard* receiveAvatar = new ElaInteractiveCard();
            receiveAvatar->setFixedSize(36, 36);
            receiveAvatar->setCardPixmapSize(36, 36);
            receiveAvatar->setBorderRadius(18);

            ElaInteractiveCard* bubbleCard = new ElaInteractiveCard();
            bubbleCard->setBorderRadius(12);
            bubbleCard->setStyleSheet(
                "ElaInteractiveCard {"
                "   background-color: #F0F0F0;"
                "   padding: 8px 12px;"
                "}"
                );

            QVBoxLayout* bubbleLayout = new QVBoxLayout(bubbleCard);
            bubbleLayout->setContentsMargins(12, 8, 12, 8);

            ElaText* receiveText = new ElaText(QString("消息 %1").arg(i + 1));
            receiveText->setTextPixelSize(14);
            receiveText->setTextStyle(ElaTextType::Body);
            receiveText->setWordWrap(true);
            receiveText->setMaximumWidth(MAX_MSG_WIDTH);
            receiveText->setTextInteractionFlags(Qt::TextSelectableByMouse);
            receiveText->setStyleSheet("background-color: transparent; border: none;");

            bubbleLayout->addWidget(receiveText);

            receiveLayout->addWidget(receiveAvatar);
            receiveLayout->addSpacing(8);
            receiveLayout->addWidget(bubbleCard);
            receiveLayout->addStretch();

            msgLayout->insertWidget(msgLayout->count() - 1, receiveWidget);
        } else {
            // 我的消息
            QWidget* sendWidget = new QWidget();
            QHBoxLayout* sendLayout = new QHBoxLayout(sendWidget);
            sendLayout->setContentsMargins(0, 0, 0, 0);

            ElaInteractiveCard* bubbleCard = new ElaInteractiveCard();
            bubbleCard->setBorderRadius(12);
            bubbleCard->setStyleSheet(
                "ElaInteractiveCard {"
                "   background-color: #95EC69;"
                "   padding: 8px 12px;"
                "}"
                );

            QVBoxLayout* bubbleLayout = new QVBoxLayout(bubbleCard);
            bubbleLayout->setContentsMargins(12, 8, 12, 8);

            ElaText* sendText = new ElaText(QString("回复 %1").arg(i + 1));
            sendText->setTextPixelSize(14);
            sendText->setTextStyle(ElaTextType::Body);
            sendText->setWordWrap(true);
            sendText->setMaximumWidth(MAX_MSG_WIDTH);
            sendText->setTextInteractionFlags(Qt::TextSelectableByMouse);
            sendText->setStyleSheet("background-color: transparent; border: none;");

            bubbleLayout->addWidget(sendText);

            ElaInteractiveCard* sendAvatar = new ElaInteractiveCard();
            sendAvatar->setFixedSize(36, 36);
            sendAvatar->setCardPixmapSize(36, 36);
            sendAvatar->setBorderRadius(18);

            sendLayout->addStretch();
            sendLayout->addWidget(bubbleCard);
            sendLayout->addSpacing(8);
            sendLayout->addWidget(sendAvatar);

            msgLayout->insertWidget(msgLayout->count() - 1, sendWidget);
        }
    }
}
