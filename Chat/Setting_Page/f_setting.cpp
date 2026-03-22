#include "f_setting.h"
#include "ElaApplication.h"
#include "ElaComboBox.h"
#include "ElaLog.h"
#include "ElaRadioButton.h"
#include "ElaScrollPageArea.h"
#include "ElaText.h"
#include "ElaTheme.h"
#include "ElaToggleSwitch.h"
#include "ElaWindow.h"
#include <QButtonGroup>
#include <QHBoxLayout>
#include "ElaPushButton.h"
#include <QThread>
#include "ElaToolButton.h"
#include <QSettings>

F_Setting::F_Setting(QWidget *parent):ElaScrollPage(parent)
{
    ElaWindow* window = dynamic_cast<ElaWindow*>(parent);

    QPixmap lightImg = IMG("pc");
    QThread::msleep(50);
    QPixmap darkImg = IMG("pc");

    window->setWindowPixmap(ElaThemeType::Light, lightImg);
    window->setWindowPixmap(ElaThemeType::Dark, darkImg);
    setWindowTitle("设置");

    ElaText* themeText = new ElaText("主题设置", this);
    themeText->setWordWrap(false);
    themeText->setTextPixelSize(18);
    // 强制重新设置颜色
    eTheme->setThemeColor(ElaThemeType::Dark, ElaThemeType::BasicText, QColor(255, 255, 255));
    _themeComboBox = new ElaComboBox(this);
    _themeComboBox->addItem("日间模式");
    _themeComboBox->addItem("夜间模式");

    ElaScrollPageArea* themeSwitchArea = new ElaScrollPageArea(this);
    QHBoxLayout* themeSwitchLayout = new QHBoxLayout(themeSwitchArea);
    ElaText* themeSwitchText = new ElaText("主题切换", this);
    themeSwitchText->setWordWrap(false);
    themeSwitchText->setTextPixelSize(15);
    themeSwitchLayout->addWidget(themeSwitchText);
    themeSwitchLayout->addStretch();
    themeSwitchLayout->addWidget(_themeComboBox);
    connect(_themeComboBox, QOverload<int>::of(&ElaComboBox::currentIndexChanged), this, [=](int index) {
        if (index == 0)
        {
            eTheme->setThemeMode(ElaThemeType::Light);
        }
        else
        {
            eTheme->setThemeMode(ElaThemeType::Dark);
        }
    });
    connect(eTheme, &ElaTheme::themeModeChanged, _themeComboBox, [=]() {
        if (eTheme->getThemeMode() == ElaThemeType::Dark) {
            _themeComboBox->setStyleSheet("QComboBox { color: white; } QComboBox QAbstractItemView { color: white; background-color: #1E1E1E; }");
        } else {
            _themeComboBox->setStyleSheet("QComboBox { color: black; } QComboBox QAbstractItemView { color: black; }");
        }
        _themeComboBox->update();


        if (eTheme->getThemeMode() == ElaThemeType::Dark) {
            _otherComboBox->setStyleSheet("QComboBox { color: white; } QComboBox QAbstractItemView { color: white; background-color: #1E1E1E; }");
        } else {
            _otherComboBox->setStyleSheet("QComboBox { color: black; } QComboBox QAbstractItemView { color: black; }");
        }
        _otherComboBox->update();

    });

    ElaText* windowPaintText = new ElaText("主窗口绘制设置", this);
    windowPaintText->setWordWrap(false);
    windowPaintText->setTextPixelSize(15);

    _windowNormalButton = new ElaRadioButton("默认", this);
    _windowNormalButton->setChecked(true);
    _windowPixmapButton = new ElaRadioButton("随机二次元主题图", this);
    ElaPushButton* refreshButton = new ElaPushButton("刷新随机图片", this);
    refreshButton->setFixedHeight(38);
    refreshButton->setText("刷新图片");
    refreshButton->setFixedWidth(100);

    connect(eTheme, &ElaTheme::themeModeChanged, this, [=](ElaThemeType::ThemeMode themeMode) {
        // 同步下拉框状态
        _themeComboBox->blockSignals(true);
        if (themeMode == ElaThemeType::Light)
        {
            _themeComboBox->setCurrentIndex(0);
        }
        else
        {
            _themeComboBox->setCurrentIndex(1);
        }
        _themeComboBox->blockSignals(false);

        QTimer::singleShot(700, this, [=]() {
            if (themeMode == ElaThemeType::Light)
            {
                QPixmap darkImg = IMG("pc");
                window->setWindowPixmap(ElaThemeType::Dark, darkImg);
            }
            else
            {
                QPixmap lightImg = IMG("pc");
                window->setWindowPixmap(ElaThemeType::Light, lightImg);
            }
            window->update();
        });
    });

    connect(refreshButton, &ElaToolButton::clicked, this, [=]() {
        QPixmap lightImg = IMG("pc");
        QThread::msleep(50);
        QPixmap darkImg = IMG("pc");

        window->setWindowPixmap(ElaThemeType::Light, lightImg);
        window->setWindowPixmap(ElaThemeType::Dark, darkImg);
        window->update();

    });

    QButtonGroup* windowPaintButtonGroup = new QButtonGroup(this);
    windowPaintButtonGroup->addButton(_windowNormalButton, 0);
    windowPaintButtonGroup->addButton(_windowPixmapButton, 1);
    windowPaintButtonGroup->addButton(refreshButton, 2);

    connect(windowPaintButtonGroup, QOverload<QAbstractButton*, bool>::of(&QButtonGroup::buttonToggled), this, [=](QAbstractButton* button, bool isToggled) {
        if (isToggled)
        {
            window->setWindowPaintMode((ElaWindowType::PaintMode)windowPaintButtonGroup->id(button));
        }

    });
    connect(window, &ElaWindow::pWindowPaintModeChanged, this, [=]() {
        auto button = windowPaintButtonGroup->button(window->getWindowPaintMode());
        ElaRadioButton* elaRadioButton = dynamic_cast<ElaRadioButton*>(button);
        if (elaRadioButton)
        {
            elaRadioButton->setChecked(true);
        }

    });

    ElaScrollPageArea* windowPaintModeArea = new ElaScrollPageArea(this);
    QHBoxLayout* windowPaintModeLayout = new QHBoxLayout(windowPaintModeArea);
    windowPaintModeLayout->addWidget(windowPaintText);
    windowPaintModeLayout->addStretch();
    windowPaintModeLayout->addWidget(_windowNormalButton);
    windowPaintModeLayout->addWidget(_windowPixmapButton);
    windowPaintModeLayout->addWidget(refreshButton);

    // ==================== 导航栏模式选择 ====================
    ElaText* navigationText = new ElaText("导航栏设置", this);
    navigationText->setWordWrap(false);
    navigationText->setTextPixelSize(18);

    _minimumButton = new ElaRadioButton("隐藏", this);
    _compactButton = new ElaRadioButton("紧凑", this);
    _maximumButton = new ElaRadioButton("最大化", this);
    _autoButton = new ElaRadioButton("自动", this);
    _autoButton->setChecked(true);

    ElaScrollPageArea* displayModeArea = new ElaScrollPageArea(this);
    QHBoxLayout* displayModeLayout = new QHBoxLayout(displayModeArea);
    ElaText* displayModeText = new ElaText("导航栏模式选择", this);
    displayModeText->setWordWrap(false);
    displayModeText->setTextPixelSize(15);
    displayModeLayout->addWidget(displayModeText);
    displayModeLayout->addStretch();
    displayModeLayout->addWidget(_minimumButton);
    displayModeLayout->addWidget(_compactButton);
    displayModeLayout->addWidget(_maximumButton);
    displayModeLayout->addWidget(_autoButton);

    QButtonGroup* navigationGroup = new QButtonGroup(this);
    navigationGroup->addButton(_autoButton, 0);
    navigationGroup->addButton(_minimumButton, 1);
    navigationGroup->addButton(_compactButton, 2);
    navigationGroup->addButton(_maximumButton, 3);

    connect(navigationGroup, QOverload<QAbstractButton*, bool>::of(&QButtonGroup::buttonToggled), this, [=](QAbstractButton* button, bool isToggled) {
        if (isToggled) {
            window->setNavigationBarDisplayMode((ElaNavigationType::NavigationDisplayMode)navigationGroup->id(button));
        }
    });

    _noneButton = new ElaRadioButton("无特效", this);
    _popupButton = new ElaRadioButton("弹出", this);
    _popupButton->setChecked(true);
    _scaleButton = new ElaRadioButton("缩放", this);
    _flipButton = new ElaRadioButton("翻转", this);
    _blurButton = new ElaRadioButton("模糊", this);

    ElaScrollPageArea* stackSwitchModeArea = new ElaScrollPageArea(this);
    QHBoxLayout* stackSwitchModeLayout = new QHBoxLayout(stackSwitchModeArea);
    ElaText* stackSwitchModeText = new ElaText("界面切换效果选择", this);
    stackSwitchModeText->setWordWrap(false);
    stackSwitchModeText->setTextPixelSize(15);
    stackSwitchModeLayout->addWidget(stackSwitchModeText);
    stackSwitchModeLayout->addStretch();
    stackSwitchModeLayout->addWidget(_noneButton);
    stackSwitchModeLayout->addWidget(_popupButton);
    stackSwitchModeLayout->addWidget(_scaleButton);
    stackSwitchModeLayout->addWidget(_flipButton);
    stackSwitchModeLayout->addWidget(_blurButton);

    QButtonGroup* stackSwitchGroup = new QButtonGroup(this);
    stackSwitchGroup->addButton(_noneButton, 0);
    stackSwitchGroup->addButton(_popupButton, 1);
    stackSwitchGroup->addButton(_scaleButton, 2);
    stackSwitchGroup->addButton(_flipButton, 3);
    stackSwitchGroup->addButton(_blurButton, 4);

    connect(stackSwitchGroup, QOverload<QAbstractButton*, bool>::of(&QButtonGroup::buttonToggled), this, [=](QAbstractButton* button, bool isToggled) {
        if (isToggled) {
            window->setStackSwitchMode((ElaWindowType::StackSwitchMode)stackSwitchGroup->id(button));
        }

    });

    ElaText* functionText = new ElaText("功能设置", this);
    functionText->setWordWrap(false);
    functionText->setTextPixelSize(18);


    // 用户卡片开关
    _userCardSwitchButton = new ElaToggleSwitch(this);
    ElaScrollPageArea* userCardSwitchArea = new ElaScrollPageArea(this);
    QHBoxLayout* userCardSwitchLayout = new QHBoxLayout(userCardSwitchArea);
    ElaText* userCardSwitchText = new ElaText("隐藏用户卡片", this);
    userCardSwitchText->setWordWrap(false);
    userCardSwitchText->setTextPixelSize(15);
    userCardSwitchLayout->addWidget(userCardSwitchText);
    userCardSwitchLayout->addStretch();
    userCardSwitchLayout->addWidget(_userCardSwitchButton);
    // TODO: 实现用户卡片隐藏逻辑
    connect(_userCardSwitchButton, &ElaToggleSwitch::toggled, this, [=](bool checked) {
        window->setUserInfoCardVisible(!checked);

    });

    ElaText* micaSwitchText = new ElaText("窗口效果", this);
    micaSwitchText->setWordWrap(false);
    micaSwitchText->setTextPixelSize(15);
    _normalButton = new ElaRadioButton("普通", this);
    _elaMicaButton = new ElaRadioButton("新云母", this);
#ifdef Q_OS_WIN
    _micaButton = new ElaRadioButton("云母", this);
    _micaAltButton = new ElaRadioButton("云母-替代", this);
    _acrylicButton = new ElaRadioButton("亚克力", this);
    _dwmBlurnormalButton = new ElaRadioButton("DWM模糊", this);
#endif
    _normalButton->setChecked(true);
    QButtonGroup* displayButtonGroup = new QButtonGroup(this);
    displayButtonGroup->addButton(_normalButton, 0);
    displayButtonGroup->addButton(_elaMicaButton, 1);
#ifdef Q_OS_WIN
    displayButtonGroup->addButton(_micaButton, 2);
    displayButtonGroup->addButton(_micaAltButton, 3);
    displayButtonGroup->addButton(_acrylicButton, 4);
    displayButtonGroup->addButton(_dwmBlurnormalButton, 5);
#endif
    connect(displayButtonGroup, QOverload<QAbstractButton*, bool>::of(&QButtonGroup::buttonToggled), this, [=](QAbstractButton* button, bool isToggled) {
        if (isToggled)
        {
            eApp->setWindowDisplayMode((ElaApplicationType::WindowDisplayMode)displayButtonGroup->id(button));
        }
    });
    connect(eApp, &ElaApplication::pWindowDisplayModeChanged, this, [=]() {
        auto button = displayButtonGroup->button(eApp->getWindowDisplayMode());
        ElaRadioButton* elaRadioButton = dynamic_cast<ElaRadioButton*>(button);
        if (elaRadioButton)
        {
            elaRadioButton->setChecked(true);
        }
    });
    ElaScrollPageArea* micaSwitchArea = new ElaScrollPageArea(this);
    QHBoxLayout* micaSwitchLayout = new QHBoxLayout(micaSwitchArea);
    micaSwitchLayout->addWidget(micaSwitchText);
    micaSwitchLayout->addStretch();
    micaSwitchLayout->addWidget(_normalButton);
    micaSwitchLayout->addWidget(_elaMicaButton);
#ifdef Q_OS_WIN
    micaSwitchLayout->addWidget(_micaButton);
    micaSwitchLayout->addWidget(_micaAltButton);
    micaSwitchLayout->addWidget(_acrylicButton);
    micaSwitchLayout->addWidget(_dwmBlurnormalButton);
#endif


    // ==================== 其他设置 ====================
    ElaText* otherText = new ElaText("其他设置", this);
    otherText->setWordWrap(false);
    otherText->setTextPixelSize(18);

    _otherComboBox = new ElaComboBox(this);
    _otherComboBox->addItem("拒绝任何人添加好友");
    _otherComboBox->addItem("发送验证信息添加");
    _otherComboBox->addItem("允许任何人添加好友");

    ElaScrollPageArea* otherArea = new ElaScrollPageArea(this);
    QHBoxLayout* otherLayout = new QHBoxLayout(otherArea);
    ElaText* otherComboBoxText = new ElaText("加好友设置", this);
    otherComboBoxText->setWordWrap(false);
    otherComboBoxText->setTextPixelSize(15);
    otherLayout->addWidget(otherComboBoxText);
    otherLayout->addStretch();
    otherLayout->addWidget(_otherComboBox);
    connect(_otherComboBox, QOverload<int>::of(&ElaComboBox::currentIndexChanged), this, [=](int index) {
        qDebug() << "选择了选项：" << index;
    });

    // 创建中心容器
    QWidget* centralWidget = new QWidget(this);
    centralWidget->setWindowTitle("Setting");

    // 垂直布局
    QVBoxLayout* centerLayout = new QVBoxLayout(centralWidget);

    centerLayout->addSpacing(30);
    centerLayout->addWidget(themeText);
    centerLayout->addSpacing(10);
    centerLayout->addWidget(themeSwitchArea);
    centerLayout->addSpacing(15);
    centerLayout->addWidget(micaSwitchArea);
    centerLayout->addSpacing(10);
    centerLayout->addWidget(windowPaintText);
    centerLayout->addSpacing(10);
    centerLayout->addWidget(windowPaintModeArea);
    centerLayout->addSpacing(15);
    centerLayout->addWidget(navigationText);
    centerLayout->addSpacing(10);
    centerLayout->addWidget(displayModeArea);
    centerLayout->addSpacing(15);
    centerLayout->addWidget(stackSwitchModeArea);
    centerLayout->addSpacing(15);
    centerLayout->addWidget(functionText);
    centerLayout->addSpacing(10);
    centerLayout->addWidget(userCardSwitchArea);
    centerLayout->addSpacing(15);
    centerLayout->addWidget(otherText);
    centerLayout->addSpacing(10);
    centerLayout->addWidget(otherArea);
    centerLayout->addStretch();

    addCentralWidget(centralWidget, true, true, 0);

}

F_Setting::~F_Setting()
{

}


