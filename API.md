# ElaWidgetTools API 文档

> 本文档由 `scripts/generate_docs.py` 自动生成，请勿手动编辑。
>
> 共 **113** 个公开组件

·



<!-- 
功能说明：本文档是ElaWidgetTools库的完整API参考。
该库提供了113个公开组件，用于构建现代化的Qt应用程序。
包括窗口管理、导航、对话框、表单、卡片、图表等多种UI组件。
-->

## 目录

### 1. 核心应用组件
应用程序全局配置、主题管理、窗口基类

- [ElaApplication](#elaapplication) - 应用程序主类
- [ElaTheme](#elatheme) - 主题管理
- [ElaWindow](#elawindow) - 主窗口基类
- [ElaWidget](#elawidget) - 基础小部件

### 2. 窗口与导航
窗口管理、应用栏、导航栏、路由及相关容器

- [ElaAppBar](#elaappbar) - 应用栏
- [ElaNavigationBar](#elanavigationbar) - 导航栏
- [ElaNavigationRouter](#elanavigationrouter) - 导航路由器
- [ElaBreadcrumbBar](#elabreadcrumbbar) - 面包屑导航栏
- [ElaCommandBar](#elacommandbar) - 命令栏
- [ElaDockWidget](#eladockwidget) - 停靠小部件
- [ElaDrawerArea](#eladrawerarea) - 抽屉区域
- [ElaFlowLayout](#elaflowlayout) - 流式布局
- [ElaMenuBar](#elamenubar) - 菜单栏
- [ElaMenu](#elamenu) - 菜单
- [ElaSheetPanel](#elasheetpanel) - 工作表面板
- [ElaStatusBar](#elastatusbar) - 状态栏
- [ElaTabBar](#elatabbar) - 标签栏
- [ElaTabWidget](#elatabwidget) - 标签小部件
- [ElaToolBar](#elatoolbar) - 工具栏
- [ElaPivot](#elapivot) - 枢纽视图

### 3. 卡片与容器
各类卡片、分组、展开器及容器组件

- [ElaAcrylicUrlCard](#elaacrylicurlcard) - 亚克力网址卡
- [ElaImageCard](#elaimagecard) - 图片卡
- [ElaInteractiveCard](#elainteractivecard) - 交互卡
- [ElaPopularCard](#elapopularcard) - 热门卡
- [ElaPromotionCard](#elapromotioncard) - 推广卡
- [ElaPromotionView](#elapromotionview) - 推广视图
- [ElaReminderCard](#elaremindercard) - 提醒卡
- [ElaStatCard](#elastatcard) - 统计卡
- [ElaGroupBox](#elagroupbox) - 组合框
- [ElaExpander](#elaexpander) - 展开器
- [ElaScrollArea](#elascrollarea) - 滚动区域
- [ElaScrollPage](#elascrollpage) - 滚动页面
- [ElaScrollPageArea](#elascrollpagearea) - 滚动页面区域
- [ElaDivider](#eladivider) - 分隔符
- [ElaSplitter](#elasplitter) - 分隔窗格

### 4. 输入与选择
文本输入、数值输入、选择、复选框等交互组件

- [ElaLineEdit](#elalineedit) - 单行文本编辑框
- [ElaPasswordBox](#elapasswordbox) - 密码框
- [ElaPlainTextEdit](#elaplaintextedit) - 纯文本编辑框
- [ElaCodeEditor](#elacodeeditor) - 代码编辑器
- [ElaSuggestBox](#elasuggestbox) - 建议框
- [ElaComboBox](#elacombobox) - 组合框
- [ElaMultiSelectComboBox](#elamultiselectcombobox) - 多选组合框
- [ElaCheckBox](#elacheckbox) - 复选框
- [ElaRadioButton](#elaradiobutton) - 单选按钮
- [ElaToggleSwitch](#elatoggleswitch) - 开关
- [ElaToggleButton](#elatogglebutton) - 切换按钮
- [ElaNumberBox](#elanumberbox) - 数字框
- [ElaDoubleSpinBox](#eladoublespinbox) - 双精度数字框
- [ElaSpinBox](#elaspinbox) - 数字调整框
- [ElaSlider](#elaslider) - 滑块
- [ElaRoller](#elaroller) - 滚轴
- [ElaRollerPicker](#elarollerpicker) - 滚轴选择器
- [ElaEmojiPicker](#elaemojipicker) - 表情选择器
- [ElaColorDialog](#elacolordialog) - 颜色对话框
- [ElaInputDialog](#elainputdialog) - 输入对话框
- [ElaCaptcha](#elacaptcha) - 验证码
- [ElaTransfer](#elatransfer) - 穿梭框

### 5. 数据展示
表格、列表、树形、日历、图表等数据展示组件

- [ElaTableView](#elatableview) - 表格视图
- [ElaTableWidget](#elatablewidget) - 表格小部件
- [ElaListView](#elalistview) - 列表视图
- [ElaVirtualList](#elavirtuallist) - 虚拟列表
- [ElaTreeView](#elatreeview) - 树形视图
- [ElaCalendar](#elacalendar) - 日历
- [ElaCalendarPicker](#elacalendarpicker) - 日期选择器
- [ElaTimeline](#elatimeline) - 时间线
- [ElaLCDNumber](#elalcdnumber) - LCD数字显示
- [ElaText](#elatext) - 文本显示
- [ElaLog](#elalog) - 日志查看
- [ElaMarkdownViewer](#elamarkdownviewer) - Markdown查看器
- [ElaPersonPicture](#elapersonpicture) - 头像图片
- [ElaPagination](#elapagination) - 分页
- [ElaSelectorBar](#elaselectorbar) - 选择栏
- [ElaRatingControl](#elaratingcontrol) - 评分控件
- [ElaQRCode](#elaqrcode) - 二维码

### 6. 反馈与提示
对话框、提示消息、通知、气泡提示等反馈组件

- [ElaDialog](#eladialog) - 通用对话框
- [ElaContentDialog](#elacontentdialog) - 内容对话框
- [ElaMessageDialog](#elamessagedialog) - 消息对话框
- [ElaMessageBar](#elamessagebar) - 消息栏
- [ElaMessageButton](#elamessagebutton) - 消息按钮
- [ElaSnackbar](#elasnackbar) - 快餐栏
- [ElaToast](#elatoast) - 吐司提示
- [ElaNotificationCenter](#elanotificationcenter) - 通知中心
- [ElaTeachingTip](#elateachingtip) - 教学提示
- [ElaToolTip](#elatooltip) - 工具提示
- [ElaPopconfirm](#elapopconfirm) - 弹出确认
- [ElaFlyout](#elaflyout) - 飞出菜单
- [ElaInfoBadge](#elainfobadge) - 信息徽章
- [ElaTag](#elatag) - 标签

### 7. 按钮与动画
各类按钮、进度条、动画、骨架屏等

- [ElaPushButton](#elapushbutton) - 普通按钮
- [ElaIconButton](#elaiconbutton) - 图标按钮
- [ElaToolButton](#elatoolbutton) - 工具按钮
- [ElaDropDownButton](#eladropdownbutton) - 下拉按钮
- [ElaSplitButton](#elasplitbutton) - 分割按钮
- [ElaFloatButton](#elafloatbutton) - 浮动按钮
- [ElaCountdown](#elacountdown) - 倒计时
- [ElaProgressBar](#elaprogressbar) - 进度条
- [ElaProgressRing](#elaprogressring) - 进度圆环
- [ElaSteps](#elasteps) - 步骤条
- [ElaSkeleton](#elaskeleton) - 骨架屏
- [ElaWatermark](#elawatermark) - 水印
- [ElaWizard](#elawizard) - 向导
- [ElaSpotlight](#elaspotlight) - 聚焦灯

### 8. 高级组件
图形场景、路由、事件系统、系统集成等高级功能

- [ElaGraphicsScene](#elagraphicsscene) - 图形场景
- [ElaGraphicsView](#elagraphicsview) - 图形视图
- [ElaGraphicsItem](#elagraphicsitem) - 图形项目
- [ElaGraphicsLineItem](#elagraphicslineitem) - 图形直线项目
- [ElaRouter](#elarouter) - 路由器
- [ElaEvent](#elaevent) - 事件系统
- [ElaKeyBinder](#elakeybinder) - 快捷键绑定
- [ElaScreenCaptureManager](#elascreencapturemanager) - 屏幕截图管理器
- [ElaDxgiManager](#eladxgimanager) - DXGI管理器
- [ElaSplashScreen](#elasplashscreen) - 启动屏幕
- [ElaScrollBar](#elascrollbar) - 滚动条

---

<!-- ============================================================================
第1部分：核心应用程序和主题管理
功能：管理应用程序全局设置、主题切换、窗口显示模式等
包含：ElaApplication(应用程序), ElaTheme(主题管理)
============================================================================ -->

## ElaApplication

**继承**: `QObject` | **头文件**: `ElaApplication.h`

ElaApplication 是 ElaWidgetTools 库的核心应用程序类，负责管理全局应用程序设置、窗口显示模式和 Mica 效果等功能。

### 属性

| 类型 | 名称 | 读写 | 功能描述 |
|------|------|------|----------|
| `ElaApplicationType::WindowDisplayMode` | `WindowDisplayMode` | get/set | 设置应用程序的窗口显示模式，如最大化、最小化或全屏 |
| `QString` | `ElaMicaImagePath` | get/set | 设置 Mica 效果使用的背景图像路径，用于窗口透明效果 |

### 方法

- `void init()` - 初始化应用程序，设置必要的全局配置和资源
- `void syncWindowDisplayMode(QWidget* widget, bool isSync = true)` - 将指定窗口的显示模式与应用程序设置同步
- `static bool containsCursorToItem(QWidget* item)` - 静态方法，检查鼠标光标是否位于指定 QWidget 项目内，用于交互检测

---

## ElaTheme

**继承**: `QObject` | **头文件**: `ElaTheme.h`

ElaTheme 类负责管理应用程序的主题设置，包括主题模式切换、颜色配置和阴影效果绘制。

### 方法

- `void setThemeMode(ElaThemeType::ThemeMode themeMode)` - 设置应用程序的主题模式，如亮色或暗色主题
- `ElaThemeType::ThemeMode getThemeMode()` - 获取当前主题模式
- `void drawEffectShadow(QPainter* painter, QRect widgetRect, int shadowBorderWidth, int borderRadius)` - 使用指定的画家在指定矩形区域绘制阴影效果
- `void setThemeColor(ElaThemeType::ThemeMode themeMode, ElaThemeType::ThemeColor themeColor, QColor newColor)` - 为指定主题模式设置特定主题颜色的值
- `const QColor& getThemeColor(ElaThemeType::ThemeMode themeMode, ElaThemeType::ThemeColor themeColor)` - 获取指定主题模式下特定主题颜色的值

### 信号

- `themeModeChanged(ElaThemeType::ThemeMode themeMode)` - 当主题模式改变时发出信号

---

<!-- ============================================================================
第2部分：窗口管理和导航系统
功能：管理应用窗口、导航栏、页面路由等核心窗口功能
包含：ElaWindow(主窗口), ElaWidget(基础窗口), ElaAppBar(应用栏), 
      ElaNavigationBar(导航栏), ElaNavigationRouter(路由器)
============================================================================ -->

## ElaWindow

**继承**: `QMainWindow` | **头文件**: `ElaWindow.h`

ElaWindow 是 ElaWidgetTools 的主窗口类，继承自 QMainWindow，提供导航栏、应用栏、用户卡片等高级窗口功能，支持页面导航和多窗口管理。

### 属性

| 类型 | 名称 | 读写 | 功能描述 |
|------|:-----|------|----------|
| `bool` | `IsStayTop` | get/set | 设置窗口是否始终置顶 |
| `bool` | `IsFixedSize` | get/set | 设置窗口大小是否固定 |
| `bool` | `IsDefaultClosed` | get/set | 设置窗口是否默认关闭 |
| `int` | `AppBarHeight` | get/set | 设置应用栏的高度 |
| `int` | `ThemeChangeTime` | get/set | 设置主题切换的动画时间 |
| `bool` | `IsCentralStackedWidgetTransparent` | get/set | 设置中央堆叠窗口是否透明 |
| `bool` | `IsAllowPageOpenInNewWindow` | get/set | 设置是否允许页面在新窗口中打开 |
| `bool` | `IsNavigationBarEnable` | get/set | 设置导航栏是否启用 |
| `int` | `NavigationBarWidth` | get/set | 设置导航栏的宽度 |

### 方法

- `void moveToCenter()` - 将窗口移动到屏幕中心
- `void setCustomWidget(ElaAppBarType::CustomArea customArea, QWidget* customWidget, QObject* hitTestObject = nullptr, const QString& hitTestFunctionName = "")` - 在应用栏的指定区域设置自定义窗口部件
- `QWidget* getCustomWidget(ElaAppBarType::CustomArea customArea)` - 获取应用栏指定区域的自定义窗口部件
- `void setCentralCustomWidget(QWidget* customWidget)` - 设置中央自定义窗口部件
- `QWidget* getCentralCustomWidget()` - 获取中央自定义窗口部件
- `void setCustomMenu(QMenu* customMenu)` - 设置自定义菜单
- `QMenu* getCustomMenu()` - 获取自定义菜单
- `void setUserInfoCardVisible(bool isVisible)` - 设置用户信息卡片是否可见
- `void setUserInfoCardPixmap(QPixmap pix)` - 设置用户信息卡片的头像图片
- `void setUserInfoCardTitle(QString title)` - 设置用户信息卡片的标题
- `void setUserInfoCardSubTitle(QString subTitle)` - 设置用户信息卡片的副标题
- `ElaNavigationType::NodeResult addExpanderNode(const QString& expanderTitle, QString& expanderKey, ElaIconType::IconName awesome = ElaIconType::None)` - 添加展开器节点到导航栏
- `ElaNavigationType::NodeResult addExpanderNode(const QString& expanderTitle, QString& expanderKey, const QString& targetExpanderKey, ElaIconType::IconName awesome = ElaIconType::None)` - 在指定展开器下添加子展开器节点
- `ElaNavigationType::NodeResult addPageNode(const QString& pageTitle, QWidget* page, ElaIconType::IconName awesome = ElaIconType::None)` - 添加页面节点到导航栏
- `ElaNavigationType::NodeResult addPageNode(const QString& pageTitle, QWidget* page, int keyPoints, ElaIconType::IconName awesome = ElaIconType::None)` - 添加带关键点数的页面节点
- `ElaNavigationType::NodeResult addPageNode(const QString& pageTitle, QWidget* page, const QString& targetExpanderKey, ElaIconType::IconName awesome = ElaIconType::None)` - 在指定展开器下添加页面节点
- `ElaNavigationType::NodeResult addPageNode(const QString& pageTitle, QWidget* page, const QString& targetExpanderKey, int keyPoints, ElaIconType::IconName awesome = ElaIconType::None)` - 在指定展开器下添加带关键点数的页面节点
- `ElaNavigationType::NodeResult addFooterNode(const QString& footerTitle, QString& footerKey, int keyPoints = 0, ElaIconType::IconName awesome = ElaIconType::None)` - 添加页脚节点到导航栏
- `ElaNavigationType::NodeResult addFooterNode(const QString& footerTitle, QWidget* page, QString& footerKey, int keyPoints = 0, ElaIconType::IconName awesome = ElaIconType::None)` - 添加带页面的页脚节点
- `ElaNavigationType::NodeResult addCategoryNode(const QString& categoryTitle, QString& categoryKey)` - 添加分类节点到导航栏
- `ElaNavigationType::NodeResult addCategoryNode(const QString& categoryTitle, QString& categoryKey, const QString& targetExpanderKey)` - 在指定展开器下添加分类节点
- `void addCentralWidget(QWidget* centralWidget)` - 添加中央窗口部件到堆叠布局
- `QWidget* getCentralWidget(int index)` - 获取指定索引的中央窗口部件
- `bool getNavigationNodeIsExpanded(QString expanderKey)` - 检查指定导航节点是否展开
- `void expandNavigationNode(QString expanderKey)` - 展开指定导航节点
- `void collapseNavigationNode(QString expanderKey)` - 折叠指定导航节点
- `void removeNavigationNode(QString nodeKey)` - 移除指定导航节点
- `int getPageOpenInNewWindowCount(QString nodeKey)` - 获取指定节点在新窗口中打开的页面数量
- `void backtrackNavigationNode(QString nodeKey)` - 回溯到指定导航节点
- `void setNodeKeyPoints(QString nodeKey, int keyPoints)` - 设置节点的關鍵点数
- `int getNodeKeyPoints(QString nodeKey)` - 获取节点的關鍵点数
- `void setNavigationNodeTitle(QString nodeKey, QString nodeTitle)` - 设置导航节点的标题
- `QString getNavigationNodeTitle(QString nodeKey)` - 获取导航节点的标题
- `void navigation(QString pageKey)` - 导航到指定页面
- `int getCurrentNavigationIndex()` - 获取当前导航索引
- `QString getCurrentNavigationPageKey()` - 获取当前导航页面键
- `void setWindowButtonFlag(ElaAppBarType::ButtonType buttonFlag, bool isEnable = true)` - 设置窗口按钮标志
- `void setWindowButtonFlags(ElaAppBarType::ButtonFlags buttonFlags)` - 设置窗口按钮标志集合
- `ElaAppBarType::ButtonFlags getWindowButtonFlags()` - 获取窗口按钮标志
- `void setWindowMoviePath(ElaThemeType::ThemeMode themeMode, const QString& moviePath)` - 设置窗口电影路径
- `QString getWindowMoviePath(ElaThemeType::ThemeMode themeMode)` - 获取窗口电影路径
- `void setWindowPixmap(ElaThemeType::ThemeMode themeMode, const QPixmap& pixmap)` - 设置窗口图片
- `QPixmap getWindowPixmap(ElaThemeType::ThemeMode themeMode)` - 获取窗口图片
- `void setWindowMovieRate(qreal rate)` - 设置窗口电影播放速率
- `qreal getWindowMovieRate()` - 获取窗口电影播放速率
- `void closeWindow()` - 关闭窗口

### 信号

- `userInfoCardClicked()` - 用户信息卡片被点击时发出
- `closeButtonClicked()` - 关闭按钮被点击时发出
- `navigationNodeClicked(ElaNavigationType::NavigationNodeType nodeType, QString nodeKey)` - 导航节点被点击时发出
- `customWidgetChanged()` - 自定义窗口部件改变时发出
- `centralCustomWidgetChanged()` - 中央自定义窗口部件改变时发出
- `customMenuChanged()` - 自定义菜单改变时发出
- `pageOpenInNewWindow(QString nodeKey)` - 页面在新窗口中打开时发出

---

## ElaWidget

**继承**: `QWidget` | **头文件**: `ElaWidget.h`

ElaWidget 是 ElaWidgetTools 的基础窗口部件类，继承自 QWidget，提供基本的窗口属性设置和按钮管理功能。

### 属性

| 类型 | 名称 | 读写 | 功能描述 |
|------|------|------|----------|
| `bool` | `IsStayTop` | get/set | 设置窗口部件是否始终置顶 |
| `bool` | `IsFixedSize` | get/set | 设置窗口部件大小是否固定 |
| `bool` | `IsDefaultClosed` | get/set | 设置窗口部件是否默认关闭 |
| `int` | `AppBarHeight` | get/set | 设置应用栏的高度 |

### 方法

- `void moveToCenter()` - 将窗口部件移动到屏幕中心
- `void setWindowButtonFlag(ElaAppBarType::ButtonType buttonFlag, bool isEnable = true)` - 设置窗口按钮标志
- `void setWindowButtonFlags(ElaAppBarType::ButtonFlags buttonFlags)` - 设置窗口按钮标志集合
- `ElaAppBarType::ButtonFlags getWindowButtonFlags()` - 获取窗口按钮标志

### 信号

- `routeBackButtonClicked()` - 路由返回按钮被点击时发出
- `navigationButtonClicked()` - 导航按钮被点击时发出
- `themeChangeButtonClicked()` - 主题切换按钮被点击时发出
- `closeButtonClicked()` - 关闭按钮被点击时发出

---

## ElaAppBar

**继承**: `QWidget` | **头文件**: `ElaAppBar.h`

ElaAppBar 是应用程序栏组件，提供自定义窗口部件、菜单和按钮管理功能，支持路由导航和窗口控制。

### 属性

| 类型 | 名称 | 读写 | 功能描述 |
|------|------|------|----------|
| `bool` | `IsStayTop` | get/set | 设置应用栏是否始终置顶 |
| `bool` | `IsFixedSize` | get/set | 设置应用栏大小是否固定 |
| `bool` | `IsDefaultClosed` | get/set | 设置应用栏是否默认关闭 |
| `bool` | `IsOnlyAllowMinAndClose` | get/set | 设置是否只允许最小化和关闭按钮 |
| `int` | `AppBarHeight` | get/set | 设置应用栏的高度 |

### 方法

- `void setCustomWidget(ElaAppBarType::CustomArea customArea, QWidget* customWidget, QObject* hitTestObject = nullptr, const QString& hitTestFunctionName = "")` - 在指定区域设置自定义窗口部件
- `QWidget* getCustomWidget(ElaAppBarType::CustomArea customArea)` - 获取指定区域的自定义窗口部件
- `void setCustomMenu(QMenu* customMenu)` - 设置自定义菜单
- `QMenu* getCustomMenu()` - 获取自定义菜单
- `void setWindowButtonFlag(ElaAppBarType::ButtonType buttonFlag, bool isEnable = true)` - 设置窗口按钮标志
- `void setWindowButtonFlags(ElaAppBarType::ButtonFlags buttonFlags)` - 设置窗口按钮标志集合
- `ElaAppBarType::ButtonFlags getWindowButtonFlags()` - 获取窗口按钮标志
- `void setRouteBackButtonEnable(bool isEnable)` - 设置路由返回按钮是否启用
- `void setRouteForwardButtonEnable(bool isEnable)` - 设置路由前进按钮是否启用
- `void closeWindow()` - 关闭窗口
- `int takeOverNativeEvent(const QByteArray& eventType, void* message, qintptr* result)` - 接管原生事件处理
- `int takeOverNativeEvent(const QByteArray& eventType, void* message, long* result)` - 接管原生事件处理（另一种签名）

### 信号

- `routeBackButtonClicked()` - 路由返回按钮被点击时发出
- `routeForwardButtonClicked()` - 路由前进按钮被点击时发出
- `navigationButtonClicked()` - 导航按钮被点击时发出
- `themeChangeButtonClicked()` - 主题切换按钮被点击时发出
- `closeButtonClicked()` - 关闭按钮被点击时发出
- `customWidgetChanged()` - 自定义窗口部件改变时发出
- `customMenuChanged()` - 自定义菜单改变时发出

---

## ElaNavigationBar

**继承**: `QWidget` | **头文件**: `ElaNavigationBar.h`

ElaNavigationBar 是导航栏组件，提供用户卡片、导航节点管理和显示模式切换功能，支持展开器、页面、页脚和分类节点的添加和管理。

### 属性

| 类型 | 名称 | 读写 | 功能描述 |
|------|------|------|----------|
| `bool` | `IsTransparent` | get/set | 设置导航栏是否透明 |
| `bool` | `IsAllowPageOpenInNewWindow` | get/set | 设置是否允许页面在新窗口中打开 |
| `int` | `NavigationBarWidth` | get/set | 设置导航栏的宽度 |

### 方法

- `void setUserInfoCardVisible(bool isVisible)` - 设置用户信息卡片是否可见
- `void setUserInfoCardPixmap(QPixmap pix)` - 设置用户信息卡片的头像图片
- `void setUserInfoCardTitle(QString title)` - 设置用户信息卡片的标题
- `void setUserInfoCardSubTitle(QString subTitle)` - 设置用户信息卡片的副标题
- `ElaNavigationType::NodeResult addExpanderNode(const QString& expanderTitle, QString& expanderKey, ElaIconType::IconName awesome = ElaIconType::None)` - 添加展开器节点
- `ElaNavigationType::NodeResult addExpanderNode(const QString& expanderTitle, QString& expanderKey, const QString& targetExpanderKey, ElaIconType::IconName awesome = ElaIconType::None)` - 在指定展开器下添加子展开器节点
- `ElaNavigationType::NodeResult addPageNode(const QString& pageTitle, QWidget* page, ElaIconType::IconName awesome = ElaIconType::None)` - 添加页面节点
- `ElaNavigationType::NodeResult addPageNode(const QString& pageTitle, QWidget* page, int keyPoints, ElaIconType::IconName awesome = ElaIconType::None)` - 添加带关键点数的页面节点
- `ElaNavigationType::NodeResult addPageNode(const QString& pageTitle, QWidget* page, const QString& targetExpanderKey, ElaIconType::IconName awesome = ElaIconType::None)` - 在指定展开器下添加页面节点
- `ElaNavigationType::NodeResult addPageNode(const QString& pageTitle, QWidget* page, const QString& targetExpanderKey, int keyPoints, ElaIconType::IconName awesome = ElaIconType::None)` - 在指定展开器下添加带关键点数的页面节点
- `ElaNavigationType::NodeResult addFooterNode(const QString& footerTitle, QString& footerKey, int keyPoints = 0, ElaIconType::IconName awesome = ElaIconType::None)` - 添加页脚节点
- `ElaNavigationType::NodeResult addFooterNode(const QString& footerTitle, QWidget* page, QString& footerKey, int keyPoints = 0, ElaIconType::IconName awesome = ElaIconType::None)` - 添加带页面的页脚节点
- `ElaNavigationType::NodeResult addCategoryNode(const QString& categoryTitle, QString& categoryKey)` - 添加分类节点
- `ElaNavigationType::NodeResult addCategoryNode(const QString& categoryTitle, QString& categoryKey, const QString& targetExpanderKey)` - 在指定展开器下添加分类节点
- `bool getNodeIsExpanded(QString expanderKey)` - 检查指定节点是否展开
- `void expandNode(QString expanderKey)` - 展开指定节点
- `void collapseNode(QString expanderKey)` - 折叠指定节点
- `void removeNode(QString nodeKey)` - 移除指定节点
- `void setNodeKeyPoints(QString nodeKey, int keyPoints)` - 设置节点的關鍵点数
- `int getNodeKeyPoints(QString nodeKey)` - 获取节点的關鍵点数
- `void setNodeTitle(QString nodeKey, QString nodeTitle)` - 设置节点的标题
- `QString getNodeTitle(QString nodeKey)` - 获取节点的标题
- `void navigation(QString pageKey, bool isLogClicked = true, bool isRouteBack = false)` - 执行导航到指定页面
- `void setDisplayMode(ElaNavigationType::NavigationDisplayMode displayMode, bool isAnimation = true)` - 设置导航栏的显示模式
- `ElaNavigationType::NavigationDisplayMode getDisplayMode()` - 获取导航栏的显示模式
- `int getPageOpenInNewWindowCount(QString nodeKey)` - 获取指定节点在新窗口中打开的页面数量

### 信号

- `pageOpenInNewWindow(QString nodeKey)` - 页面在新窗口中打开时发出
- `userInfoCardClicked()` - 用户信息卡片被点击时发出
- `navigationNodeClicked(ElaNavigationType::NavigationNodeType nodeType, QString nodeKey, bool isRouteBack)` - 导航节点被点击时发出
- `navigationNodeAdded(ElaNavigationType::NavigationNodeType nodeType, QString nodeKey, QWidget* page)` - 导航节点被添加时发出
- `navigationNodeRemoved(ElaNavigationType::NavigationNodeType nodeType, QString nodeKey)` - 导航节点被移除时发出

---

## ElaNavigationRouter

**继承**: `QObject` | **头文件**: `ElaNavigationRouter.h`

ElaNavigationRouter 是导航路由器类，管理应用程序的导航历史和路由状态，支持前进、后退和路由数据传递。

### 属性

| 类型 | 名称 | 读写 | 功能描述 |
|------|------|------|----------|
| `int` | `MaxRouteCount` | get/set | 设置最大路由历史记录数量 |

### 方法

- `ElaNavigationRouterType::NavigationRouteType navigationRoute(QObject* routeObject, QString routeFunctionName, const QVariantMap& routeData = {}, Qt::ConnectionType connectionType = Qt::AutoConnection)` - 执行导航路由，调用指定对象的函数并传递数据
- `void clearNavigationRoute()` - 清除导航路由历史
- `void navigationRouteBack()` - 导航到上一个路由
- `void navigationRouteForward()` - 导航到下一个路由
- `ElaNavigationRouterType::NavigationRouteType navigationRoute(QObject* context, QObject* routeObject, QString routeFunctionName, const QVariantMap& routeData = {}, Qt::ConnectionType connectionType = Qt::AutoConnection)` - 在指定上下文中执行导航路由
- `void clearNavigationRoute(QObject* context)` - 清除指定上下文的导航路由历史
- `void navigationRouteBack(QObject* context)` - 在指定上下文中导航到上一个路由
- `void navigationRouteForward(QObject* context)` - 在指定上下文中导航到下一个路由

### 信号

- `navigationRouterStateChanged(ElaNavigationRouterType::RouteMode routeMode)` - 导航路由器状态改变时发出
- `windowRouterStateChanged(QObject* context, ElaNavigationRouterType::RouteMode routeMode)` - 窗口路由器状态改变时发出

---

<!-- ============================================================================
第3部分：卡片和展示组件
功能：提供各种卡片样式和内容展示组件，用于展示信息、链接等
包含：ElaAcrylicUrlCard(亚克力URL卡片), ElaImageCard(图片卡片), 
      ElaInteractiveCard(交互卡片), ElaPopularCard(热门卡片),
      ElaPromotionCard(促销卡片), ElaReminderCard(提醒卡片),
      ElaStatCard(统计卡片)
============================================================================ -->

## ElaAcrylicUrlCard

**继承**: `QPushButton` | **头文件**: `ElaAcrylicUrlCard.h`

ElaAcrylicUrlCard 是亚克力风格的 URL 卡片组件，继承自 QPushButton，提供带有图片、标题和副标题的卡片式按钮，支持 URL 链接。

### 属性

| 类型 | 名称 | 读写 | 功能描述 |
|------|------|------|----------|
| `int` | `BorderRadius` | get/set | 设置卡片的边框圆角半径 |
| `qreal` | `MainOpacity` | get/set | 设置主内容的透明度 |
| `qreal` | `NoiseOpacity` | get/set | 设置噪声效果的透明度 |
| `int` | `BrushAlpha` | get/set | 设置画笔的 alpha 值 |
| `QString` | `Title` | get/set | 设置卡片的标题文本 |
| `QString` | `SubTitle` | get/set | 设置卡片的副标题文本 |
| `int` | `TitlePixelSize` | get/set | 设置标题的像素大小 |
| `int` | `SubTitlePixelSize` | get/set | 设置副标题的像素大小 |
| `int` | `TitleSpacing` | get/set | 设置标题的间距 |
| `int` | `SubTitleSpacing` | get/set | 设置副标题的间距 |
| `QPixmap` | `CardPixmap` | get/set | 设置卡片的图片 |
| `QSize` | `CardPixmapSize` | get/set | 设置卡片图片的大小 |
| `int` | `CardPixmapBorderRadius` | get/set | 设置卡片图片的边框圆角半径 |
| `ElaCardPixType::PixMode` | `CardPixMode` | get/set | 设置卡片图片的显示模式 |
| `QString` | `Url` | get/set | 设置卡片关联的 URL |

### 方法

- `void setCardPixmapSize(int width, int height)` - 设置卡片图片的宽度和高度

---

<!-- ============================================================================
第4部分：菜单和导航栏组件
功能：提供菜单栏、菜单、面包屑导航、选择栏等导航和菜单功能
包含：ElaMenu(菜单), ElaMenuBar(菜单栏), ElaCommandBar(命令栏),
      ElaBreadcrumbBar(面包屑导航), ElaSelectorBar(选择栏),
      ElaDropDownButton(下拉按钮)
============================================================================ -->

## ElaBreadcrumbBar

**继承**: `QWidget` | **头文件**: `ElaBreadcrumbBar.h`

ElaBreadcrumbBar 是面包屑导航栏组件，用于显示导航路径，支持自动移除和点击事件。

### 属性

| 类型 | 名称 | 读写 | 功能描述 |
|------|------|------|----------|
| `int` | `TextPixelSize` | get/set | 设置文本的像素大小 |
| `bool` | `IsAutoRemove` | get/set | 设置是否自动移除面包屑 |

### 方法

- `void setBreadcrumbList(QStringList breadcrumbList)` - 设置面包屑列表
- `QStringList appendBreadcrumb(QString breadcrumb)` - 追加面包屑并返回列表
- `QStringList removeBreadcrumb(QString breadcrumb)` - 移除指定面包屑并返回列表
- `int getBreadcrumbListCount()` - 获取面包屑列表的数量
- `QStringList getBreadcrumbList()` - 获取面包屑列表

### 信号

- `breadcrumbClicked(QString breadcrumb, QStringList lastBreadcrumbList)` - 面包屑被点击时发出

---

<!-- ============================================================================
第5部分：日期、时间和计数组件
功能：提供日期选择、倒计时、数字显示等时间相关的组件
包含：ElaCalendar(日历), ElaCalendarPicker(日历选择器),
      ElaCountdown(倒计时), ElaLCDNumber(LCD数字显示),
      ElaRoller(滚轮), ElaRollerPicker(滚轮选择器)
============================================================================ -->

## ElaCalendar

**继承**: `QWidget` | **头文件**: `ElaCalendar.h`

ElaCalendar 是日历组件，提供日期选择功能，支持设置选定日期、最小和最大日期范围。

### 属性

| 类型 | 名称 | 读写 | 功能描述 |
|------|------|------|----------|
| `int` | `BorderRaiuds` | get/set | 设置日历的边框圆角半径 |
| `QDate` | `SelectedDate` | get/set | 设置选定的日期 |
| `QDate` | `MinimumDate` | get/set | 设置可选择的最小日期 |
| `QDate` | `MaximumDate` | get/set | 设置可选择的最大日期 |

### 信号

- `clicked(QDate date)` - 日期被点击时发出

---

## ElaCalendarPicker

**继承**: `QPushButton` | **头文件**: `ElaCalendarPicker.h`

ElaCalendarPicker 是日历选择器组件，继承自 QPushButton，提供弹出日历进行日期选择的按钮。

### 属性

| 类型 | 名称 | 读写 | 功能描述 |
|------|------|------|----------|
| `int` | `BorderRadius` | get/set | 设置按钮的边框圆角半径 |
| `QDate` | `SelectedDate` | get/set | 设置选定的日期 |

### 信号

- `selectedDateChanged(QDate date)` - 选定日期改变时发出

---

## ElaCaptcha

**继承**: `QWidget` | **头文件**: `ElaCaptcha.h`

ElaCaptcha 是验证码组件，提供数字或字母数字验证码的生成和输入验证功能。

### 属性

| 类型 | 名称 | 读写 | 功能描述 |
|------|------|------|----------|
| `int` | `CodeLength` | get/set | 设置验证码的长度 |
| `int` | `BorderRadius` | get/set | 设置组件的边框圆角半径 |
| `int` | `BoxSize` | get/set | 设置输入框的大小 |
| `int` | `BoxSpacing` | get/set | 设置输入框之间的间距 |

### 枚举

**InputMode**: `DigitOnly` - 仅数字输入, `AlphaNumeric` - 字母数字输入

### 方法

- `void setInputMode(InputMode mode)` - 设置输入模式
- `InputMode getInputMode()` - 获取输入模式
- `QString getCode()` - 获取生成的验证码
- `void clear()` - 清空输入

### 信号

- `codeCompleted(const QString& code)` - 验证码输入完成时发出
- `codeChanged(const QString& code)` - 验证码输入改变时发出

---

## ElaCheckBox

**继承**: `QCheckBox` | **头文件**: `ElaCheckBox.h`

ElaCheckBox 是复选框组件，继承自 QCheckBox，提供标准的复选框功能。

## ElaCodeEditor

**继承**: `QWidget` | **头文件**: `ElaCodeEditor.h`

ElaCodeEditor 是代码编辑器组件，提供代码编辑功能，支持多种编程语言的语法高亮。

### 属性

| 类型 | 名称 | 读写 | 功能描述 |
|------|------|------|----------|
| `QString` | `Code` | get/set | 设置编辑器的代码内容 |
| `bool` | `IsReadOnly` | get/set | 设置编辑器是否只读 |
| `int` | `TabSize` | get/set | 设置制表符的大小 |

### 枚举

**Language**: `CPP` - C++, `C` - C, `CSharp` - C#, `Python` - Python, `JavaScript` - JavaScript, `Lua` - Lua, `Rust` - Rust, `PHP` - PHP

### 方法

- `void setLanguage(Language lang)` - 设置编程语言
- `Language getLanguage()` - 获取编程语言

---

## ElaColorDialog

**继承**: `QDialog` | **头文件**: `ElaColorDialog.h`

ElaColorDialog 是颜色对话框组件，提供颜色选择功能，支持自定义颜色。

### 属性

| 类型 | 名称 | 读写 | 功能描述 |
|------|------|------|----------|
| `QColor` | `CurrentColor` | get/set | 设置当前选定的颜色 |

### 方法

- `QColor getCustomColor(int index)` - 获取指定索引的自定义颜色
- `QString getCurrentColorRGB()` - 获取当前颜色的 RGB 字符串

### 信号

- `colorSelected(const QColor& color)` - 颜色被选中时发出

---

## ElaComboBox

**继承**: `QComboBox` | **头文件**: `ElaComboBox.h`

ElaComboBox 是组合框组件，继承自 QComboBox，提供下拉选择功能。

### 属性

| 类型 | 名称 | 读写 | 功能描述 |
|------|------|------|----------|
| `int` | `BorderRadius` | get/set | 设置组合框的边框圆角半径 |

### 方法

- `void setEditable(bool editable)` - 设置组合框是否可编辑

---

## ElaCommandBar

**继承**: `QWidget` | **头文件**: `ElaCommandBar.h`

ElaCommandBar 是命令栏组件，提供命令项的添加和管理，支持图标和分隔符。

### 属性

| 类型 | 名称 | 读写 | 功能描述 |
|------|------|------|----------|
| `int` | `ButtonSize` | get/set | 设置按钮的大小 |

### 结构体

**CommandItem**
```cpp
  ElaIconType::IconName icon = ElaIconType::None;  // 图标
  QString text;  // 文本
  bool isSeparator = false;  // 是否为分隔符
```

### 方法

- `void addItem(const CommandItem& item)` - 添加命令项
- `void addSeparator()` - 添加分隔符
- `void clearItems()` - 清空所有项

### 信号

- `itemClicked(int index)` - 项被点击时发出

---

## ElaContentDialog

**继承**: `QDialog` | **头文件**: `ElaContentDialog.h`

ElaContentDialog 是内容对话框组件，提供中央窗口部件和按钮配置功能。

### 方法

- `void setCentralWidget(QWidget* centralWidget)` - 设置中央窗口部件
- `void setLeftButtonText(QString text)` - 设置左按钮文本
- `void setMiddleButtonText(QString text)` - 设置中按钮文本
- `void setRightButtonText(QString text)` - 设置右按钮文本
- `void setLeftButtonVisible(bool visible)` - 设置左按钮是否可见
- `void setMiddleButtonVisible(bool visible)` - 设置中按钮是否可见
- `void setRightButtonVisible(bool visible)` - 设置右按钮是否可见
- `void close()` - 关闭对话框

### 信号

- `leftButtonClicked()` - 左按钮被点击时发出
- `middleButtonClicked()` - 中按钮被点击时发出
- `rightButtonClicked()` - 右按钮被点击时发出

---

## ElaCountdown

**继承**: `QWidget` | **头文件**: `ElaCountdown.h`

ElaCountdown 是倒计时组件，提供目标日期时间的倒计时显示和控制功能。

### 属性

| 类型 | 名称 | 读写 | 功能描述 |
|------|------|------|----------|
| `int` | `BorderRadius` | get/set | 设置组件的边框圆角半径 |
| `bool` | `IsShowDays` | get/set | 设置是否显示天数 |
| `bool` | `IsShowHours` | get/set | 设置是否显示小时 |
| `bool` | `IsShowMinutes` | get/set | 设置是否显示分钟 |
| `bool` | `IsShowSeconds` | get/set | 设置是否显示秒数 |
| `int` | `DigitWidth` | get/set | 设置数字的宽度 |
| `int` | `DigitHeight` | get/set | 设置数字的高度 |
| `int` | `DigitSpacing` | get/set | 设置数字之间的间距 |
| `int` | `FontPixelSize` | get/set | 设置字体的像素大小 |

### 方法

- `void setTargetDateTime(const QDateTime& dateTime)` - 设置目标日期时间
- `QDateTime getTargetDateTime()` - 获取目标日期时间
- `void setRemainingSeconds(qint64 seconds)` - 设置剩余秒数
- `qint64 getRemainingSeconds()` - 获取剩余秒数
- `void start()` - 开始倒计时
- `void pause()` - 暂停倒计时
- `void resume()` - 恢复倒计时
- `void stop()` - 停止倒计时
- `bool isRunning()` - 检查是否正在运行

### 信号

- `timeout()` - 倒计时结束时发出
- `tick(qint64 remainingSeconds)` - 每秒更新剩余秒数时发出

---

## ElaDialog

**继承**: `QDialog` | **头文件**: `ElaDialog.h`

ElaDialog 是对话框组件，继承自 QDialog，提供基本的对话框功能和窗口属性设置。

### 属性

| 类型 | 名称 | 读写 | 功能描述 |
|------|------|------|----------|
| `bool` | `IsStayTop` | get/set | 设置对话框是否始终置顶 |
| `bool` | `IsFixedSize` | get/set | 设置对话框大小是否固定 |
| `bool` | `IsDefaultClosed` | get/set | 设置对话框是否默认关闭 |
| `int` | `AppBarHeight` | get/set | 设置应用栏的高度 |

### 方法

- `void moveToCenter()` - 将对话框移动到屏幕中心
- `void setWindowButtonFlag(ElaAppBarType::ButtonType buttonFlag, bool isEnable = true)` - 设置窗口按钮标志
- `void setWindowButtonFlags(ElaAppBarType::ButtonFlags buttonFlags)` - 设置窗口按钮标志集合
- `ElaAppBarType::ButtonFlags getWindowButtonFlags()` - 获取窗口按钮标志

### 信号

- `routeBackButtonClicked()` - 路由返回按钮被点击时发出
- `navigationButtonClicked()` - 导航按钮被点击时发出
- `themeChangeButtonClicked()` - 主题切换按钮被点击时发出
- `closeButtonClicked()` - 关闭按钮被点击时发出

---

## ElaDivider

**继承**: `QWidget` | **头文件**: `ElaDivider.h`

ElaDivider 是分隔符组件，提供水平或垂直分隔线，支持文本和内容位置设置。

### 属性

| 类型 | 名称 | 读写 | 功能描述 |
|------|------|------|----------|
| `Qt::Orientation` | `Orientation` | get/set | 设置分隔符的方向（水平或垂直） |
| `QString` | `Text` | get/set | 设置分隔符上的文本 |
| `int` | `ContentPosition` | get/set | 设置内容的相对位置 |

### 枚举

**ContentPositionType**: `Left` - 左侧, `Center` - 居中, `Right` - 右侧

---

## ElaDockWidget

**继承**: `QDockWidget` | **头文件**: `ElaDockWidget.h`

ElaDockWidget 是停靠窗口部件，继承自 QDockWidget，提供标准的停靠功能。

### 属性

| 类型 | 名称 | 读写 | 功能描述 |
|------|------|------|----------|
| `QString` | `Title` | get/set | 设置停靠窗口的标题 |
| `bool` | `IsFloating` | get/set | 设置窗口是否浮动 |
| `bool` | `IsClosable` | get/set | 设置窗口是否可关闭 |

### 方法

- `void setWidget(QWidget* widget)` - 设置停靠窗口的内容组件
- `QWidget* widget()` - 获取停靠窗口的内容组件

---

## ElaDoubleSpinBox

**继承**: `QDoubleSpinBox` | **头文件**: `ElaDoubleSpinBox.h`

ElaDoubleSpinBox 是双精度浮点数旋转框组件，继承自 QDoubleSpinBox，提供数值输入功能。

### 属性

| 类型 | 名称 | 读写 | 功能描述 |
|------|------|------|----------|
| `ElaSpinBoxType::ButtonMode` | `ButtonMode` | get/set | 设置增减按钮的显示模式 |
| `int` | `BorderRadius` | get/set | 设置输入框的边框圆角半径 |
| `int` | `Decimals` | get/set | 设置小数位数 |

### 枚举

**ButtonMode**:
- `Normal` - 标准模式，按钮在两侧
- `Compact` - 紧凑模式，按钮在右侧堆叠
- `Icon` - 图标模式，使用图标表示增减

---

<!-- ============================================================================
第6部分：输入和表单组件
功能：提供各种文本输入、密码框、数字输入等表单组件
包含：ElaLineEdit(行编辑框), ElaPasswordBox(密码框), ElaNumberBox(数字框),
      ElaSpinBox(整数旋转框), ElaDoubleSpinBox(浮点旋转框),
      ElaPlainTextEdit(纯文本编辑), ElaSuggestBox(建议框)
============================================================================ -->

## ElaDrawerArea

**继承**: `QWidget` | **头文件**: `ElaDrawerArea.h`

ElaDrawerArea 是抽屉区域组件，提供抽屉的添加、移除和展开/折叠功能。

### 属性

| 类型 | 名称 | 读写 | 功能描述 |
|------|------|------|----------|
| `int` | `BorderRadius` | get/set | 设置区域的边框圆角半径 |
| `int` | `HeaderHeight` | get/set | 设置头部的高度 |

### 方法

- `void setDrawerHeader(QWidget* widget)` - 设置抽屉头部
- `void addDrawer(QWidget* widget)` - 添加抽屉
- `void removeDrawer(QWidget* widget)` - 移除抽屉
- `void expand()` - 展开抽屉
- `void collapse()` - 折叠抽屉
- `bool getIsExpand()` - 获取是否展开

### 信号

- `expandStateChanged(bool isExpand)` - 展开状态改变时发出

---

## ElaDropDownButton

**继承**: `QWidget` | **头文件**: `ElaDropDownButton.h`

ElaDropDownButton 是下拉按钮组件，提供文本、图标和菜单设置功能。

### 属性

| 类型 | 名称 | 读写 | 功能描述 |
|------|------|------|----------|
| `int` | `BorderRadius` | get/set | 设置按钮的边框圆角半径 |
| `QString` | `Text` | get/set | 设置按钮的文本 |
| `ElaIconType::IconName` | `ElaIcon` | get/set | 设置按钮的图标 |

### 方法

- `void setMenu(ElaMenu* menu)` - 设置下拉菜单
- `ElaMenu* getMenu()` - 获取下拉菜单

---

## ElaDxgiManager

**继承**: `QObject` | **头文件**: `ElaDxgiManager.h`

ElaDxgiManager 是 DXGI 管理器类，提供屏幕捕获和设备管理功能。

### 属性

| 类型 | 名称 | 读写 | 功能描述 |
|------|------|------|----------|
| `int` | `BorderRadius` | get/set | 设置边框圆角半径 |

### 方法

- `QStringList getDxDeviceList()` - 获取 DX 设备列表
- `QStringList getOutputDeviceList()` - 获取输出设备列表
- `QImage grabScreenToImage()` - 抓取屏幕到图像
- `void startGrabScreen()` - 开始屏幕抓取
- `void stopGrabScreen()` - 停止屏幕抓取
- `bool getIsGrabScreen()` - 获取是否正在抓取
- `bool setDxDeviceID(int dxID)` - 设置 DX 设备 ID
- `int getDxDeviceID()` - 获取 DX 设备 ID
- `bool setOutputDeviceID(int deviceID)` - 设置输出设备 ID
- `int getOutputDeviceID()` - 获取输出设备 ID
- `void setGrabArea(int width, int height)` - 设置抓取区域大小
- `void setGrabArea(int x, int y, int width, int height)` - 设置抓取区域位置和大小
- `QRect getGrabArea()` - 获取抓取区域
- `void setGrabFrameRate(int frameRateValue)` - 设置抓取帧率
- `int getGrabFrameRate()` - 获取抓取帧率
- `void setTimeoutMsValue(int timeoutValue)` - 设置超时毫秒值
- `int getTimeoutMsValue()` - 获取超时毫秒值
- `explicit ElaDxgiScreen(QWidget* parent = nullptr)` - 构造函数
- `void setIsSyncGrabSize(bool isSyncGrabSize)` - 设置是否同步抓取大小
- `bool getIsSyncGrabSize()` - 获取是否同步抓取大小

### 信号

- `grabImageUpdate(QImage img)` - 抓取图像更新时发出

---

## ElaEmojiPicker

**继承**: `QWidget` | **头文件**: `ElaEmojiPicker.h`

ElaEmojiPicker 是表情选择器组件，提供丰富的表情符号选择功能。

### 属性

| 类型 | 名称 | 读写 | 功能描述 |
|------|------|------|----------|
| `int` | `EmojiSize` | get/set | 设置表情的大小 |
| `int` | `Columns` | get/set | 设置表情显示的列数 |
| `int` | `BorderRadius` | get/set | 设置选择器的边框圆角半径 |

### 方法

- `void popup(QWidget* anchor)` - 在指定窗口部件附近弹出表情选择器
- `void popup(const QPoint& pos)` - 在指定位置弹出表情选择器
- `void clearRecent()` - 清空最近使用的表情
- `QStringList getRecentEmojis()` - 获取最近使用的表情列表

### 信号

- `emojiSelected(const QString& emoji)` - 表情被选中时发出

---

## ElaEvent

**继承**: `QObject` | **头文件**: `ElaEventBus.h`

ElaEvent 是事件总线组件，提供事件的注册、发送和监听功能，用于实现应用程序内的事件驱动架构。

### 属性

| 类型 | 名称 | 读写 | 功能描述 |
|------|------|------|----------|
| `QString` | `EventName` | get/set | 设置事件名称，用于标识事件的唯一键 |
| `QString` | `FunctionName` | get/set | 设置处理事件的函数名称，当事件被触发时调用 |
| `Qt::ConnectionType` | `ConnectionType` | get/set | 设置事件连接类型，如Qt::AutoConnection或Qt::QueuedConnection |

### 方法

- `ElaEventBusType::EventBusReturnType registerAndInit()` - 注册并初始化事件监听器
- `ElaEventBusType::EventBusReturnType post(const QString& eventName, const QVariantMap& data = {})` - 发送事件，可传递附加数据
- `QStringList getRegisteredEventsName()` - 获取所有已注册的事件名称列表
- `bool hasEvent(const QString& eventName)` - 检查是否存在特定事件
- `void unregister(const QString& eventName)` - 取消注册指定事件的监听器

---

<!-- ============================================================================
第15部分：弹出层和浮动组件
功能：提供浮动按钮、弹出框、工具提示等弹出层组件
包含：ElaFlyout(飞出框), ElaFloatButton(浮动按钮),
      ElaToolTip(工具提示), ElaExpander(扩展器),
      ElaPopularCard(热门卡片视图)
============================================================================ -->

## ElaExpander

**继承**: `QWidget` | **头文件**: `ElaExpander.h`

ElaExpander 是扩展器组件，提供可展开和折叠的内容容器，用于节省空间的同时展示多个内容块。

### 属性

| 类型 | 名称 | 读写 | 功能描述 |
|------|------|------|----------|
| `int` | `BorderRadius` | get/set | 设置扩展器的边框圆角半径 |
| `QString` | `Title` | get/set | 设置扩展器的标题文本 |
| `QString` | `SubTitle` | get/set | 设置扩展器的副标题文本 |
| `ElaIconType::IconName` | `HeaderIcon` | get/set | 设置扩展器头部的图标 |
| `int` | `AnimationDuration` | get/set | 设置展开和折叠的动画时长（毫秒） |

### 枚举

**ExpandDirection**: 
- `Down` - 向下展开
- `Up` - 向上展开

### 方法

- `void setExpandDirection(ExpandDirection direction)` - 设置展开方向
- `ExpandDirection getExpandDirection()` - 获取当前展开方向
- `void setContentWidget(QWidget* widget)` - 设置扩展器的内容窗口部件
- `QWidget* getContentWidget()` - 获取扩展器的内容窗口部件
- `void setHeaderWidget(QWidget* widget)` - 设置扩展器的头部自定义窗口部件
- `void setIsExpanded(bool expanded)` - 设置是否展开状态
- `bool getIsExpanded()` - 获取当前是否展开

### 信号

- `expandStateChanged(bool expanded)` - 展开状态改变时发出

---

## ElaFloatButton

**继承**: `QWidget` | **头文件**: `ElaFloatButton.h`

ElaFloatButton 是浮动按钮组件，通常位于应用窗口的一个角落，提供快速访问主要功能的便捷入口。

### 属性

| 类型 | 名称 | 读写 | 功能描述 |
|------|------|------|----------|
| `int` | `ButtonSize` | get/set | 设置浮动按钮的大小（宽度和高度） |
| `int` | `Margin` | get/set | 设置浮动按钮与屏幕边界的间距 |

### 枚举

**Position**: 
- `BottomRight` - 屏幕右下角
- `BottomLeft` - 屏幕左下角
- `TopRight` - 屏幕右上角
- `TopLeft` - 屏幕左上角

### 方法

- `void setIcon(ElaIconType::IconName icon)` - 设置浮动按钮显示的图标
- `ElaIconType::IconName getIcon()` - 获取浮动按钮当前的图标
- `void setPosition(Position position)` - 设置浮动按钮在屏幕上的位置
- `Position getPosition()` - 获取浮动按钮当前的位置
- `void setMenu(ElaMenu* menu)` - 为浮动按钮设置右键菜单
- `ElaMenu* getMenu()` - 获取浮动按钮的菜单

### 信号

- `clicked()` - 浮动按钮被用户点击时发出

---

## ElaFlowLayout

**继承**: `QLayout` | **头文件**: `ElaFlowLayout.h`

ElaFlowLayout 是流式布局组件，自动排列窗口部件，当窗口变小时自动换行，提供自适应的弹性布局。

### 方法

- `int horizontalSpacing()` - 获取布局中组件之间的水平间距（像素）
- `int verticalSpacing()` - 获取布局中组件之间的垂直间距（像素）
- `void setIsAnimation(bool isAnimation)` - 设置组件进出时是否显示动画效果

---

## ElaFlyout

**继承**: `QWidget` | **头文件**: `ElaFlyout.h`

ElaFlyout 是飞出框组件，从屏幕边缘飞出的浮动面板，常用于展示额外信息、帮助文本或操作选项。

### 属性

| 类型 | 名称 | 读写 | 功能描述 |
|------|------|------|----------|
| `int` | `BorderRadius` | get/set | 设置飞出框的边框圆角半径 |
| `QString` | `Title` | get/set | 设置飞出框的标题文本 |
| `QString` | `Content` | get/set | 设置飞出框的内容文本 |
| `bool` | `IsLightDismiss` | get/set | 设置是否允许点击框外区域关闭飞出框 |

### 方法

- `void setContentWidget(QWidget* widget)` - 设置飞出框的自定义内容窗口部件，可完全替代默认内容
- `void showFlyout(QWidget* target)` - 在指定窗口部件附近显示飞出框
- `void closeFlyout()` - 关闭飞出框

### 信号

- `closed()` - 飞出框被关闭时发出（无论是用户点击还是代码关闭）

---

<!-- ============================================================================
第7部分：图形和场景组件
功能：提供图形场景、视图、项目等高级图形绘制功能
包含：ElaGraphicsScene(图形场景), ElaGraphicsView(图形视图),
      ElaGraphicsItem(图形项), ElaGraphicsLineItem(图形线项)
============================================================================ -->

## ElaGraphicsItem

**继承**: `QGraphicsObject` | **头文件**: `ElaGraphicsItem.h`

### 属性

| 类型 | 名称 | 读写 |
|------|------|------|
| `int` | `Width` | get/set |
| `int` | `Height` | get/set |
| `QImage` | `ItemImage` | get/set |
| `QImage` | `ItemSelectedImage` | get/set |
| `QString` | `ItemName` | get/set |
| `QVariantMap` | `DataRoutes` | get/set |
| `int` | `MaxLinkPortCount` | get/set |

### 方法

- `QString getItemUID()`
- `void setLinkPortState(bool isFullLink)`
- `void setLinkPortState(bool isLink, int portIndex)`
- `bool getLinkPortState(int portIndex)`
- `int getUsedLinkPortCount()`
- `int getUnusedLinkPortCount()`

---

## ElaGraphicsLineItem

**继承**: `QGraphicsPathItem` | **头文件**: `ElaGraphicsLineItem.h`

ElaGraphicsLineItem 是图形线条项类，用于在图形场景中绘制连接线条，支持起点、终点和端口连接的管理。

### 属性

| 类型 | 名称 | 读写 | 功能描述 |
|------|------|------|----------|
| `QPointF` | `StartPoint` | get/set | 设置线条的起点坐标 |
| `QPointF` | `EndPoint` | get/set | 设置线条的终点坐标 |
| `ElaGraphicsItem*` | `StartItem` | get/set | 设置线条连接的起始图形项 |
| `ElaGraphicsItem*` | `EndItem` | get/set | 设置线条连接的结束图形项 |
| `int` | `StartItemPort` | get/set | 设置起始项的端口索引 |
| `int` | `EndItemPort` | get/set | 设置结束项的端口索引 |

### 方法

- `bool isTargetLink(ElaGraphicsItem* item)` - 检查是否与指定项有连接
- `bool isTargetLink(ElaGraphicsItem* item1, ElaGraphicsItem* item2)` - 检查两个项之间是否有连接
- `bool isTargetLink(ElaGraphicsItem* item1, ElaGraphicsItem* item2, int port1, int port2)` - 检查两个项指定端口之间是否有连接

---

## ElaGraphicsScene

**继承**: `QGraphicsScene` | **头文件**: `ElaGraphicsScene.h`

ElaGraphicsScene 是图形场景类，管理图形项和线条的添加、移除和连接，支持序列化和反序列化。

### 属性

| 类型 | 名称 | 读写 | 功能描述 |
|------|------|------|----------|
| `bool` | `IsCheckLinkPort` | get/set | 设置是否检查链接端口 |
| `QString` | `SerializePath` | get/set | 设置序列化路径 |

### 方法

- `void addItem(ElaGraphicsItem* item)` - 添加图形项到场景
- `void removeItem(ElaGraphicsItem* item)` - 从场景移除图形项
- `void removeSelectedItems()` - 移除所有选中的项
- `void clear()` - 清空场景
- `void setSceneMode(ElaGraphicsSceneType::SceneMode mode)` - 设置场景模式
- `ElaGraphicsSceneType::SceneMode getSceneMode()` - 获取场景模式
- `void selectAllItems()` - 选择所有项
- `bool addItemLink(ElaGraphicsItem* item1, ElaGraphicsItem* item2, int port1 = 0, int port2 = 0)` - 添加两个项之间的链接
- `bool removeItemLink(ElaGraphicsItem* item1)` - 移除指定项的所有链接
- `bool removeItemLink(ElaGraphicsItem* item1, ElaGraphicsItem* item2, int port1 = 0, int port2 = 0)` - 移除两个项之间的指定链接
- `void serialize()` - 序列化场景
- `void deserialize()` - 反序列化场景

### 信号

- `showItemLink()` - 显示项链接时发出
- `mouseLeftClickedItem(ElaGraphicsItem* item)` - 鼠标左键点击项时发出
- `mouseRightClickedItem(ElaGraphicsItem* item)` - 鼠标右键点击项时发出
- `mouseDoubleClickedItem(ElaGraphicsItem* item)` - 鼠标双击项时发出

---

## ElaGraphicsView

**继承**: `QGraphicsView` | **头文件**: `ElaGraphicsView.h`

ElaGraphicsView 是图形视图类，用于显示和交互图形场景，支持缩放变换。

### 属性

| 类型 | 名称 | 读写 | 功能描述 |
|------|------|------|----------|
| `qreal` | `MaxTransform` | get/set | 设置最大缩放变换值 |
| `qreal` | `MinTransform` | get/set | 设置最小缩放变换值 |

---

## ElaGroupBox

**继承**: `QGroupBox` | **头文件**: `ElaGroupBox.h`

ElaGroupBox 是分组框组件，提供圆角边框设置。

### 属性

| 类型 | 名称 | 读写 | 功能描述 |
|------|------|------|----------|
| `int` | `BorderRadius` | get/set | 设置分组框的边框圆角半径 |

---

<!-- ============================================================================
第8部分：按钮组件
功能：提供各种类型的按钮，包括普通、图标、切换、确认等
包含：ElaPushButton(普通按钮), ElaIconButton(图标按钮),
      ElaToolButton(工具按钮), ElaToggleButton(切换按钮),
      ElaToggleSwitch(开关), ElaRadioButton(单选按钮),
      ElaSplitButton(分割按钮)
============================================================================ -->

## ElaIconButton

**继承**: `QPushButton` | **头文件**: `ElaIconButton.h`

ElaIconButton 是图标按钮组件，支持图标显示和颜色设置。

### 属性

| 类型 | 名称 | 读写 | 功能描述 |
|------|------|------|----------|
| `int` | `BorderRadius` | get/set | 设置按钮的边框圆角半径 |
| `qreal` | `Opacity` | get/set | 设置按钮的透明度 |
| `QColor` | `LightHoverColor` | get/set | 设置亮色主题下的悬停颜色 |
| `QColor` | `DarkHoverColor` | get/set | 设置暗色主题下的悬停颜色 |
| `QColor` | `LightIconColor` | get/set | 设置亮色主题下的图标颜色 |
| `QColor` | `DarkIconColor` | get/set | 设置暗色主题下的图标颜色 |
| `QColor` | `LightHoverIconColor` | get/set | 设置亮色主题下的悬停图标颜色 |
| `QColor` | `DarkHoverIconColor` | get/set | 设置暗色主题下的悬停图标颜色 |
| `bool` | `IsSelected` | get/set | 设置按钮是否被选中 |

### 方法

- `void setAwesome(ElaIconType::IconName awesome)` - 设置图标
- `ElaIconType::IconName getAwesome()` - 获取图标
- `void setPixmap(QPixmap pix)` - 设置图片

---

## ElaImageCard

**继承**: `QWidget` | **头文件**: `ElaImageCard.h`

ElaImageCard 是图片卡片组件，用于展示和显示图像内容，支持多种显示模式和圆角处理。

### 属性

| 类型 | 名称 | 读写 | 功能描述 |
|------|------|------|----------|
| `QImage` | `CardImage` | get/set | 设置卡片要显示的图像 |
| `int` | `BorderRadius` | get/set | 设置卡片的边框圆角半径 |
| `bool` | `IsPreserveAspectCrop` | get/set | 设置是否保持图像长宽比进行裁剪显示 |

---

## ElaInfoBadge

**继承**: `QWidget` | **头文件**: `ElaInfoBadge.h`

ElaInfoBadge 是信息徽章组件，用于在组件上显示通知、计数或状态指示器，支持多种显示模式和严重程度。

### 属性

| 类型 | 名称 | 读写 | 功能描述 |
|------|------|------|----------|
| `int` | `Value` | get/set | 设置徽章显示的数值（用于Value_模式） |
| `ElaIconType::IconName` | `ElaIcon` | get/set | 设置徽章显示的图标（用于Icon模式） |

### 枚举

**BadgeMode**: 
- `Dot` - 只显示小圆点
- `Value_` - 显示数值
- `Icon` - 显示图标

**Severity**: 
- `Attention` - 吸引注意（通常为红色）
- `Informational` - 信息提示（通常为蓝色）
- `Success` - 成功状态（通常为绿色）
- `Caution` - 警告（通常为黄色）
- `Critical` - 严重错误（通常为深红色）

### 方法

- `void setBadgeMode(BadgeMode mode)` - 设置徽章的显示模式
- `BadgeMode getBadgeMode()` - 获取当前徽章的显示模式
- `void setMaxValue(int maxValue)` - 设置数值显示的最大值（超过则显示"N+"）
- `int getMaxValue()` - 获取设置的最大值
- `void setSeverity(Severity severity)` - 设置徽章的严重程度（影响颜色）
- `Severity getSeverity()` - 获取当前严重程度
- `void attachTo(QWidget* target)` - 将徽章附加到指定窗口部件上

---

## ElaInputDialog

**继承**: `QDialog` | **头文件**: `ElaInputDialog.h`

ElaInputDialog 是输入对话框组件，提供多种输入类型（文本、整数、浮点数），用于获取用户输入。

### 属性

| 类型 | 名称 | 读写 | 功能描述 |
|------|------|------|----------|
| `QString` | `TitleText` | get/set | 设置对话框的标题文本 |
| `QString` | `SubTitleText` | get/set | 设置对话框的副标题文本 |
| `QString` | `LabelText` | get/set | 设置输入字段前的标签文本 |
| `QString` | `TextValue` | get/set | 设置或获取文本输入框的当前值 |
| `int` | `IntValue` | get/set | 设置或获取整数输入框的当前值 |
| `double` | `DoubleValue` | get/set | 设置或获取浮点数输入框的当前值 |
| `QString` | `OkButtonText` | get/set | 设置确定按钮的文本 |
| `QString` | `CancelButtonText` | get/set | 设置取消按钮的文本 |
| `QString` | `PlaceholderText` | get/set | 设置输入框的占位符提示文本 |
| `int` | `InputMinimumWidth` | get/set | 设置输入框的最小宽度 |
| `int` | `InputMaximumWidth` | get/set | 设置输入框的最大宽度 |

### 方法

- `void setTextEchoMode(QLineEdit::EchoMode mode)` - 设置文本显示模式（如密码模式） 
- `QLineEdit::EchoMode textEchoMode()` - 获取当前文本显示模式
- `void setIntRange(int minValue, int maxValue, int step = 1)` - 设置整数输入的范围和步长
- `void setDoubleRange(double minValue, double maxValue, int decimals = 2)` - 设置浮点数输入的范围和小数位数
- `void setMultiLine(bool multiLine)` - 设置是否为多行文本输入

### 信号

- `textValueChanged(QString text)` - 文本输入内容改变时发出
- `intValueChanged(int value)` - 整数输入值改变时发出
- `doubleValueChanged(double value)` - 浮点数输入值改变时发出

---

## ElaInteractiveCard

**继承**: `QPushButton` | **头文件**: `ElaInteractiveCard.h`

ElaInteractiveCard 是交互卡片组件，用于展示带有图片、标题、副标题的可交互卡片。

### 属性

| 类型 | 名称 | 读写 | 功能描述 |
|------|------|------|----------|
| `int` | `BorderRadius` | get/set | 设置卡片的边框圆角半径 |
| `QString` | `Title` | get/set | 设置卡片的标题文本 |
| `QString` | `SubTitle` | get/set | 设置卡片的副标题文本 |
| `int` | `TitlePixelSize` | get/set | 设置标题的像素大小 |
| `int` | `SubTitlePixelSize` | get/set | 设置副标题的像素大小 |
| `int` | `TitleSpacing` | get/set | 设置标题和副标题之间的间距 |
| `QPixmap` | `CardPixmap` | get/set | 设置卡片要显示的图片 |
| `QSize` | `CardPixmapSize` | get/set | 设置卡片图片的大小 |
| `int` | `CardPixmapBorderRadius` | get/set | 设置卡片图片的边框圆角半径 |
| `ElaCardPixType::PixMode` | `CardPixMode` | get/set | 设置卡片图片的显示模式 |

### 方法

- `void setCardPixmapSize(int width, int height)` - 设置卡片图片的宽度和高度

---

## ElaKeyBinder

**继承**: `QLabel` | **头文件**: `ElaKeyBinder.h`

ElaKeyBinder 是快捷键绑定组件，用于显示和绑定键盘快捷键。

### 属性

| 类型 | 名称 | 读写 | 功能描述 |
|------|------|------|----------|
| `int` | `BorderRadius` | get/set | 设置组件的边框圆角半径 |
| `QString` | `BinderKeyText` | get/set | 设置显示的快捷键文本 |
| `quint32` | `NativeVirtualBinderKey` | get/set | 设置本地虚拟快捷键代码 |

### 信号

- `binderKeyTextChanged(QString binderKeyText)` - 快捷键文本改变时发出
- `nativeVirtualBinderKeyChanged(quint32 binderKey)` - 快捷键代码改变时发出

---

## ElaLCDNumber

**继承**: `QLCDNumber` | **头文件**: `ElaLCDNumber.h`

ElaLCDNumber 是LCD数字显示组件，用于以LCD风格显示数字或时钟。

### 属性

| 类型 | 名称 | 读写 | 功能描述 |
|------|------|------|----------|
| `bool` | `IsUseAutoClock` | get/set | 设置是否自动显示系统时钟 |
| `QString` | `AutoClockFormat` | get/set | 设置自动时钟的时间格式（如"hh:mm:ss"） |
| `bool` | `IsTransparent` | get/set | 设置是否使用透明背景 |

---

## ElaLineEdit

**继承**: `QLineEdit` | **头文件**: `ElaLineEdit.h`

ElaLineEdit 是行编辑框组件，支持圆角样式和清空按钮。

### 属性

| 类型 | 名称 | 读写 | 功能描述 |
|------|------|------|----------|
| `int` | `BorderRadius` | get/set | 设置编辑框的边框圆角半径 |
| `bool` | `IsClearButtonEnable` | get/set | 设置是否显示清空文本的按钮 |

### 信号

- `focusIn(QString text)` - 编辑框获得焦点时发出，传递当前文本
- `focusOut(QString text)` - 编辑框失去焦点时发出，传递当前文本
- `wmFocusOut(QString text)` - Windows消息触发焦点丢失时发出

---

<!-- ============================================================================
第9部分：数据表格和列表组件
功能：提供表格、列表、树形、虚拟列表等数据展示组件
包含：ElaTableView(表格视图), ElaTableWidget(表格控件),
      ElaListView(列表视图), ElaTreeView(树形视图),
      ElaVirtualList(虚拟列表), ElaTransfer(数据转换)
============================================================================ -->

## ElaListView

**继承**: `QListView` | **头文件**: `ElaListView.h`

ElaListView 是列表视图组件，用于展示项目列表，支持自定义行高和透明背景。

### 属性

| 类型 | 名称 | 读写 | 功能描述 |
|------|------|------|----------|
| `int` | `ItemHeight` | get/set | 设置列表项目的统一高度 |
| `bool` | `IsTransparent` | get/set | 设置列表视图是否使用透明背景 |

---

## ElaLog

**继承**: `QObject` | **头文件**: `ElaLog.h`

ElaLog 是日志管理组件，用于记录应用程序的运行日志到文件。

### 属性

| 类型 | 名称 | 读写 | 功能描述 |
|------|------|------|----------|
| `QString` | `LogSavePath` | get/set | 设置日志文件保存的目录路径 |
| `QString` | `LogFileName` | get/set | 设置日志文件的名称 |
| `bool` | `IsLogFileNameWithTime` | get/set | 设置日志文件名是否包含时间戳 |

### 方法

- `void initMessageLog(bool isEnable)` - 初始化并启用或禁用消息日志记录

### 信号

- `logMessage(QString log)` - 当有新的日志消息时发出

---

## ElaMarkdownViewer

**继承**: `QWidget` | **头文件**: `ElaMarkdownViewer.h`

ElaMarkdownViewer 是Markdown查看器组件，用于显示和解析Markdown格式的文本。

### 属性

| 类型 | 名称 | 读写 | 功能描述 |
|------|------|------|----------|
| `QString` | `Markdown` | get/set | 设置要显示的Markdown文本内容 |
| `int` | `BorderRadius` | get/set | 设置查看器的边框圆角半径 |

---

## ElaMenu

**继承**: `QMenu` | **头文件**: `ElaMenu.h`

ElaMenu 是自定义菜单组件，提供更灵活的菜单项配置和图标支持。

### 方法

- `void setMenuItemHeight(int menuItemHeight)` - 设置菜单项的统一高度
- `int getMenuItemHeight()` - 获取菜单项的高度
- `QAction* addMenu(QMenu* menu)` - 添加子菜单
- `ElaMenu* addMenu(const QString& title)` - 建立新菜单并添加为子菜单，使用标题
- `ElaMenu* addMenu(const QIcon& icon, const QString& title)` - 添加带图标和标题的子菜单
- `ElaMenu* addMenu(ElaIconType::IconName icon, const QString& title)` - 添加带Ela图标和标题的子菜单
- `QAction* addElaIconAction(ElaIconType::IconName icon, const QString& text)` - 添加Ela图标动作项
- `QAction* addElaIconAction(ElaIconType::IconName icon, const QString& text, const QKeySequence& shortcut)` - 添加带快捷键的Ela图标动作项
- `bool isHasChildMenu()` - 检查是否有子菜单
- `bool isHasIcon()` - 检查菜单项是否包含图标

### 信号

- `menuShow()` - 菜单显示时发出

---

## ElaMenuBar

**继承**: `QMenuBar` | **头文件**: `ElaMenuBar.h`

ElaMenuBar 是自定义菜单栏组件，支持Ela图标和更丰富的菜单定制选项。

### 方法

- `QAction* addMenu(QMenu* menu)` - 添加菜单到菜单栏
- `ElaMenu* addMenu(const QString& title)` - 创建并添加带标题的菜单
- `ElaMenu* addMenu(const QIcon& icon, const QString& title)` - 创建并添加带图标和标题的菜单
- `ElaMenu* addMenu(ElaIconType::IconName, const QString& title)` - 创建并添加带Ela图标和标题的菜单
- `QAction* addElaIconAction(ElaIconType::IconName icon, const QString& text)` - 添加Ela图标动作
- `QAction* addElaIconAction(ElaIconType::IconName icon, const QString& text, const QKeySequence& shortcut)` - 添加带快捷键的Ela图标动作

---

<!-- ============================================================================
第10部分：对话框和消息提示组件
功能：提供各种对话框、消息提示、通知等用户交互反馈组件
包含：ElaMessageDialog(消息对话框), ElaInputDialog(输入对话框),
      ElaMessageBar(消息栏), ElaSnackbar(小提示), ElaToast(提示框),
      ElaPopconfirm(弹出确认), ElaNotificationCenter(通知中心),
      ElaTeachingTip(教学提示)
============================================================================ -->

## ElaMessageBar

**继承**: `QWidget` | **头文件**: `ElaMessageBar.h`

ElaMessageBar 是消息栏组件，用于在窗口顶部或指定位置显示通知消息。

### 方法

- `static void success(ElaMessageBarType::PositionPolicy policy, QString title, QString text, int displayMsec, QWidget* parent = nullptr)` - 显示成功消息
- `static void warning(ElaMessageBarType::PositionPolicy policy, QString title, QString text, int displayMsec, QWidget* parent = nullptr)` - 显示警告消息
- `static void information(ElaMessageBarType::PositionPolicy policy, QString title, QString text, int displayMsec, QWidget* parent = nullptr)` - 显示信息消息
- `static void error(ElaMessageBarType::PositionPolicy policy, QString title, QString text, int displayMsec, QWidget* parent = nullptr)` - 显示错误消息

---

## ElaMessageButton

**继承**: `QPushButton` | **头文件**: `ElaMessageButton.h`

ElaMessageButton 是消息按钮组件，点击时显示消息栏提示。

### 属性

| 类型 | 名称 | 读写 | 功能描述 |
|------|------|------|----------|
| `int` | `BorderRadius` | get/set | 设置按钮的边框圆角半径 |
| `QString` | `BarTitle` | get/set | 设置弹出消息栏的标题 |
| `QString` | `BarText` | get/set | 设置弹出消息栏的文本内容 |
| `int` | `DisplayMsec` | get/set | 设置消息栏显示的时长（毫秒） |
| `QWidget*` | `MessageTargetWidget` | get/set | 设置消息栏显示的目标窗口部件 |
| `ElaMessageBarType::MessageMode` | `MessageMode` | get/set | 设置消息栏的类型（成功、错误、警告等） |
| `ElaMessageBarType::PositionPolicy` | `PositionPolicy` | get/set | 设置消息栏的显示位置 |

---

## ElaMessageDialog

**继承**: `QWidget` | **头文件**: `ElaMessageDialog.h`

ElaMessageDialog 是消息对话框组件，用于显示确认、询问等消息。

### 属性

| 类型 | 名称 | 读写 | 功能描述 |
|------|------|------|----------|
| `int` | `BorderRadius` | get/set | 设置对话框的边框圆角半径 |
| `QString` | `Title` | get/set | 设置对话框的标题 |
| `QString` | `Content` | get/set | 设置对话框的内容文本 |
| `int` | `TitlePixelSize` | get/set | 设置标题的像素大小 |
| `int` | `ContentPixelSize` | get/set | 设置内容文本的像素大小 |

### 信号

- `confirmed()` - 用户确认时发出
- `cancelled()` - 用户取消时发出

---

## ElaMultiSelectComboBox

**继承**: `QComboBox` | **头文件**: `ElaMultiSelectComboBox.h`

ElaMultiSelectComboBox 是多选组合框组件，允许用户同时选择多个选项。

### 属性

| 类型 | 名称 | 读写 | 功能描述 |
|------|------|------|----------|
| `int` | `BorderRadius` | get/set | 设置组合框的边框圆角半径 |
| `bool` | `ShowCheckBox` | get/set | 设置是否显示复选框 |

### 方法

- `void setCurrentSelection(QString selection)` - 设置单个选项为已选中
- `void setCurrentSelection(QStringList selection)` - 设置多个选项为已选中
- `void setCurrentSelection(int index)` - 按索引设置已选中选项
- `void setCurrentSelection(QList<int> selectionIndex)` - 按索引列表设置多个已选中选项
- `QStringList getCurrentSelection()` - 获取所有已选中的选项文本列表

### 信号

- `itemSelectionChanged(QVector<bool> itemSelection)` - 项目选择状态改变时发出
- `currentTextListChanged(QStringList selectedTextList)` - 已选文本列表改变时发出

---

## ElaNotificationCenter

**继承**: `QWidget` | **头文件**: `ElaNotificationCenter.h`

ElaNotificationCenter 是通知中心组件，用于显示和管理应用通知。

### 属性

| 类型 | 名称 | 读写 | 功能描述 |
|------|------|------|----------|
| `int` | `BorderRadius` | get/set | 设置通知中心的边框圆角半径 |
| `int` | `PanelWidth` | get/set | 设置通知面板的宽度 |

### 结构体

**NotificationItem**
```cpp
  QString title;              // 通知标题
  QString content;            // 通知内容
  QString timestamp;          // 时间戳
  ElaIconType::IconName icon; // 通知图标
```

### 方法

- `void addNotification(const NotificationItem& item)` - 添加新通知
- `void clearAll()` - 清空所有通知
- `int getNotificationCount()` - 获取当前通知数量
- `void showPanel(QWidget* anchor)` - 在指定位置显示通知面板
- `void hidePanel()` - 隐藏通知面板
- `bool isPanelVisible()` - 检查通知面板是否可见

### 信号

- `notificationClicked(int index)` - 通知被点击时发出

---

## ElaNumberBox

**继承**: `QWidget` | **头文件**: `ElaNumberBox.h`

ElaNumberBox 是数字输入框组件，用于输入和调整数值。

### 属性

| 类型 | 名称 | 读写 | 功能描述 |
|------|------|------|----------|
| `int` | `BorderRadius` | get/set | 设置输入框的边框圆角半径 |
| `double` | `Value` | get/set | 设置或获取数值 |
| `double` | `Minimum` | get/set | 设置数值的最小值 |
| `double` | `Maximum` | get/set | 设置数值的最大值 |
| `double` | `Step` | get/set | 设置增减的步长 |
| `int` | `Decimals` | get/set | 设置小数位数 |
| `bool` | `IsWrapping` | get/set | 设置是否循环（最大值后返回最小值） |

### 方法

- `void stepUp()` - 数值增加一个步长
- `void stepDown()` - 数值减少一个步长

### 信号

- `valueChanged(double value)` - 数值改变时发出

---

## ElaPagination

**继承**: `QWidget` | **头文件**: `ElaPagination.h`

ElaPagination 是分页导航组件，用于显示分页按钮和跳转功能。

### 属性

| 类型 | 名称 | 读写 | 功能描述 |
|------|------|------|----------|
| `int` | `CurrentPage` | get/set | 设置或获取当前页码 |
| `int` | `TotalPages` | get/set | 设置总页数 |
| `int` | `ButtonSize` | get/set | 设置按钮的大小 |
| `int` | `PagerCount` | get/set | 设置显示的页码按钮数量 |
| `bool` | `JumperVisible` | get/set | 设置是否显示快速跳转输入框 |

### 信号

- `currentPageChanged(int page)` - 当前页码改变时发出

---

## ElaPasswordBox

**继承**: `QLineEdit` | **头文件**: `ElaPasswordBox.h`

ElaPasswordBox 是密码输入框组件，支持显示/隐藏密码的快速切换。

### 属性

| 类型 | 名称 | 读写 | 功能描述 |
|------|------|------|----------|
| `int` | `BorderRadius` | get/set | 设置输入框的边框圆角半径 |
| `bool` | `IsPasswordVisible` | get/set | 设置密码是否以明文显示 |

### 信号

- `focusIn(QString text)` - 输入框获得焦点时发出
- `focusOut(QString text)` - 输入框失去焦点时发出
- `wmFocusOut(QString text)` - Windows消息触发焦点丢失时发出

---

## ElaPersonPicture

**继承**: `QWidget` | **头文件**: `ElaPersonPicture.h`

ElaPersonPicture 是人物头像组件，用于显示用户头像和名称。

### 属性

| 类型 | 名称 | 读写 | 功能描述 |
|------|------|------|----------|
| `int` | `PictureSize` | get/set | 设置头像的大小 |
| `QString` | `DisplayName` | get/set | 设置要显示的用户名称 |
| `QPixmap` | `Picture` | get/set | 设置头像的图像pixmap |

---

## ElaPivot

**继承**: `QWidget` | **头文件**: `ElaPivot.h`

ElaPivot 是枢纽组件，用于在多个内容视图间快速切换。

### 属性

| 类型 | 名称 | 读写 | 功能描述 |
|------|------|------|----------|
| `int` | `TextPixelSize` | get/set | 设置枢纽项文本的像素大小 |
| `int` | `CurrentIndex` | get/set | 设置或获取当前选中的枢纽索引 |
| `int` | `PivotSpacing` | get/set | 设置枢纽项之间的间距 |
| `int` | `MarkWidth` | get/set | 设置枢纽下方标记线的宽度 |

### 方法

- `void appendPivot(QString pivotTitle)` - 添加新的枢纽项
- `void removePivot(QString pivotTitle)` - 移除指定的枢纽项

### 信号

- `pivotClicked(int index)` - 枢纽项被单击时发出
- `pivotDoubleClicked(int index)` - 枢纽项被双击时发出

---

## ElaPlainTextEdit

**继承**: `QPlainTextEdit` | **头文件**: `ElaPlainTextEdit.h`

ElaPlainTextEdit 是纯文本编辑器组件，用于编辑不带格式的纯文本内容。

### 属性

| 类型 | 名称 | 读写 | 功能描述 |
|------|------|------|----------|
| `int` | `BorderRadius` | get/set | 设置编辑器的边框圆角半径 |
| `bool` | `IsReadOnly` | get/set | 设置编辑器是否只读 |
| `QString` | `PlainText` | get/set | 设置或获取编辑器的文本内容 |

### 信号

- `textChanged()` - 文本内容改变时发出

---

## ElaPopconfirm

**继承**: `QWidget` | **头文件**: `ElaPopconfirm.h`

ElaPopconfirm 是弹出确认组件，在用户执行重要操作前显示确认对话框。

### 属性

| 类型 | 名称 | 读写 | 功能描述 |
|------|------|------|----------|
| `int` | `BorderRadius` | get/set | 设置确认框的边框圆角半径 |
| `QString` | `Title` | get/set | 设置确认框的标题 |
| `QString` | `Content` | get/set | 设置确认框的内容文本 |
| `QString` | `ConfirmButtonText` | get/set | 设置确认按钮的文本 |
| `QString` | `CancelButtonText` | get/set | 设置取消按钮的文本 |
| `ElaIconType::IconName` | `Icon` | get/set | 设置确认框的图标 |
| `bool` | `IsLightDismiss` | get/set | 设置是否允许点击框外关闭 |

### 方法

- `void showPopconfirm(QWidget* target)` - 在指定窗口部件附近显示确认框
- `void closePopconfirm()` - 关闭确认框

### 信号

- `confirmed()` - 用户点击确认按钮时发出
- `cancelled()` - 用户点击取消按钮时发出
- `closed()` - 确认框关闭时发出

---

## ElaPopularCard

**继承**: `QWidget` | **头文件**: `ElaPopularCard.h`

ElaPopularCard 是热门卡片组件，用于展示热门内容或推荐商品。

### 属性

| 类型 | 名称 | 读写 | 功能描述 |
|------|------|------|----------|
| `int` | `BorderRadius` | get/set | 设置卡片的边框圆角半径 |
| `QPixmap` | `CardPixmap` | get/set | 设置卡片的背景图片 |
| `QString` | `Title` | get/set | 设置卡片的标题 |
| `QString` | `SubTitle` | get/set | 设置卡片的副标题 |
| `QString` | `InteractiveTips` | get/set | 设置交互提示文本 |
| `QString` | `DetailedText` | get/set | 设置详细描述文本 |
| `QString` | `CardButtonText` | get/set | 设置卡片按钮的文本 |
| `QWidget*` | `CardFloatArea` | get/set | 设置浮动区域组件 |
| `QPixmap` | `CardFloatPixmap` | get/set | 设置浮动区域的图片 |
| `QSize` | `CardFloatPixmapSize` | get/set | 设置浮动图片的大小 |

### 方法

- `void setCardPixmapSize(int width, int height)` - 设置卡片图片的大小

### 信号

- `popularCardClicked()` - 卡片被点击时发出
- `popularCardButtonClicked()` - 卡片按钮被点击时发出

---

<!-- ============================================================================
第11部分：进度和动画组件
功能：提供进度条、进度环、骨架屏、加载动画等加载和进度展示组件
包含：ElaProgressBar(进度条), ElaProgressRing(进度环),
      ElaSkeleton(骨架屏), ElaSpotlight(聚光灯),
      ElaRatingControl(评分控件), ElaSlider(滑块)
============================================================================ -->

## ElaProgressBar

**继承**: `QProgressBar` | **头文件**: `ElaProgressBar.h`

ElaProgressBar 是进度条组件，用于显示操作的进度。

### 属性

| 类型 | 名称 | 读写 | 功能描述 |
|------|------|------|----------|
| `int` | `Minimum` | get/set | 设置最小值 |
| `int` | `Maximum` | get/set | 设置最大值 |
| `int` | `Value` | get/set | 设置当前值 |
| `int` | `BorderRadius` | get/set | 设置边框圆角半径 |

### 方法

- `void setMinimum(int minimum)` - 设置最小值
- `void setMaximum(int maximum)` - 设置最大值
- `void setValue(int value)` - 设置当前值
- `void reset()` - 重置进度条

---

## ElaProgressRing

**继承**: `QWidget` | **头文件**: `ElaProgressRing.h`

ElaProgressRing 是圆形进度条组件，用于显示圆形进度。

### 属性

| 类型 | 名称 | 读写 | 功能描述 |
|------|------|------|----------|
| `bool` | `IsBusying` | get/set | 设置是否显示忙碌动画 |
| `bool` | `IsTransparent` | get/set | 设置是否透明背景 |
| `bool` | `IsDisplayValue` | get/set | 设置是否显示数值 |
| `ElaProgressRingType::ValueDisplayMode` | `ValueDisplayMode` | get/set | 设置数值显示模式 |
| `int` | `BusyingWidth` | get/set | 设置忙碌动画的宽度 |
| `int` | `BusyingDurationTime` | get/set | 设置忙碌动画的持续时间 |
| `int` | `Minimum` | get/set | 设置最小值 |
| `int` | `Maximum` | get/set | 设置最大值 |
| `int` | `Value` | get/set | 设置当前值 |
| `int` | `ValuePixelSize` | get/set | 设置数值的像素大小 |

### 枚举

**ValueDisplayMode**:
- `None` - 不显示数值
- `Percent` - 显示百分比
- `Value` - 显示数值

### 方法

- `void setRange(int min, int max)`

### 信号

- `rangeChanged(int min, int max)`

---

## ElaPromotionCard

**继承**: `QWidget` | **头文件**: `ElaPromotionCard.h`

ElaPromotionCard 是促销卡片组件，用于展示促销、折扣等信息。

### 属性

| 类型 | 名称 | 读写 | 功能描述 |
|------|------|------|----------|
| `int` | `BorderRadius` | get/set | 设置卡片的边框圆角半径 |
| `QPixmap` | `CardPixmap` | get/set | 设置卡片的背景图 |
| `QString` | `CardTitle` | get/set | 设置卡片的标题 |
| `QString` | `PromotionTitle` | get/set | 设置促销标题 |
| `QString` | `Title` | get/set | 设置卡片主标题 |
| `QString` | `SubTitle` | get/set | 设置卡片副标题 |
| `QColor` | `CardTitleColor` | get/set | 设置卡片标题颜色 |
| `QColor` | `PromotionTitleColor` | get/set | 设置促销标题颜色 |
| `QColor` | `PromotionTitleBaseColor` | get/set | 设置促销标题背景颜色 |
| `QColor` | `TitleColor` | get/set | 设置主标题颜色 |
| `QColor` | `SubTitleColor` | get/set | 设置副标题颜色 |
| `int` | `CardTitlePixelSize` | get/set | 设置卡片标题的像素大小 |
| `int` | `PromotionTitlePixelSize` | get/set | 设置促销标题的像素大小 |
| `int` | `TitlePixelSize` | get/set | 设置主标题的像素大小 |
| `int` | `SubTitlePixelSize` | get/set | 设置副标题的像素大小 |
| `qreal` | `HorizontalCardPixmapRatio` | get/set | 设置水平方向图片比例 |
| `qreal` | `VerticalCardPixmapRatio` | get/set | 设置竖直方向图片比例 |

### 信号

- `promotionCardClicked()` - 促销卡片被点击时发出

---

## ElaPromotionView

**继承**: `QWidget` | **头文件**: `ElaPromotionView.h`

ElaPromotionView 是促销视图组件，用于显示可滚动的促销卡片列表。

### 属性

| 类型 | 名称 | 读写 | 功能描述 |
|------|------|------|----------|
| `int` | `CardExpandWidth` | get/set | 设置卡片展开时的宽度 |
| `int` | `CardCollapseWidth` | get/set | 设置卡片折叠时的宽度 |
| `int` | `CurrentIndex` | get/set | 设置或获取当前选中卡片的索引 |
| `bool` | `IsAutoScroll` | get/set | 设置是否自动滚动 |
| `int` | `AutoScrollInterval` | get/set | 设置自动滚动的时间间隔 |

### 方法

- `void appendPromotionCard(ElaPromotionCard* card)` - 添加促销卡片到视图

---

## ElaPushButton

**继承**: `QPushButton` | **头文件**: `ElaPushButton.h`

ElaPushButton 是推送按钮组件，具有自定义颜色和悬停效果。

### 属性

| 类型 | 名称 | 读写 | 功能描述 |
|------|------|------|----------|
| `int` | `BorderRadius` | get/set | 设置按钮的边框圆角半径 |
| `QColor` | `LightDefaultColor` | get/set | 设置亮色主题下的默认颜色 |
| `QColor` | `DarkDefaultColor` | get/set | 设置暗色主题下的默认颜色 |
| `QColor` | `LightHoverColor` | get/set | 设置亮色主题下的悬停颜色 |
| `QColor` | `DarkHoverColor` | get/set | 设置暗色主题下的悬停颜色 |
| `QColor` | `LightPressColor` | get/set | 设置亮色主题下的按压颜色 |
| `QColor` | `DarkPressColor` | get/set | 设置暗色主题下的按压颜色 |

### 方法

- `void setLightTextColor(QColor color)` - 设置亮色主题下的文字颜色
- `QColor getLightTextColor()` - 获取亮色主题下的文字颜色
- `void setDarkTextColor(QColor color)` - 设置暗色主题下的文字颜色
- `QColor getDarkTextColor()` - 获取暗色主题下的文字颜色
- `void setElaIcon(ElaIconType::IconName icon)` - 设置Ela图标
- `void setElaIcon(ElaIconType::IconName icon, int iconSize)` - 设置Ela图标及其大小
- `void setHoverEnabled(bool enabled)` - 设置是否启用悬停效果
- `bool isHoverEnabled()` - 检查是否启用悬停效果

---

<!-- ============================================================================
第14部分：特殊功能组件
功能：提供二维码、截图、屏幕捕获等特殊功能组件
包含：ElaQRCode(二维码), ElaDxgiManager(DXGI管理器),
      ElaScreenCaptureManager(屏幕捕获), ElaEmojiPicker(emoji选择器),
      ElaLog(日志), ElaKeyBinder(快捷键绑定)
============================================================================ -->

## ElaQRCode

**继承**: `QWidget` | **头文件**: `ElaQRCode.h`

ElaQRCode 是二维码生成组件，用于生成和显示二维码。

### 属性

| 类型 | 名称 | 读写 | 功能描述 |
|------|------|------|----------|
| `int` | `BorderRadius` | get/set | 设置组件的边框圆角半径 |
| `int` | `QuietZone` | get/set | 设置二维码的安全边距 |
| `QColor` | `ForegroundColor` | get/set | 设置二维码的前景色（黑色部分） |
| `QColor` | `BackgroundColor` | get/set | 设置二维码的背景色（白色部分） |

### 枚举

**ErrorCorrectionLevel**: 
- `Low` - 低纠错级别（约7%）
- `Medium` - 中等纠错级别（约15%）
- `Quartile` - 四分之一纠错级别（约25%）
- `High` - 高纠错级别（约30%）

### 方法

- `void setText(const QString& text)` - 设置要编码的文本内容
- `QString getText()` - 获取当前编码的文本
- `void setErrorCorrectionLevel(ErrorCorrectionLevel level)` - 设置纠错级别
- `ErrorCorrectionLevel getErrorCorrectionLevel()` - 获取当前纠错级别
- `QPixmap toPixmap(int size = 256)` - 生成指定大小的二维码图像

---

## ElaRadioButton

**继承**: `QRadioButton` | **头文件**: `ElaRadioButton.h`

ElaRadioButton 是单选按钮组件，用于单选一组互斥选项。

---

## ElaRatingControl

**继承**: `QWidget` | **头文件**: `ElaRatingControl.h`

ElaRatingControl 是评分控件，用于显示和收集用户星级评分。

### 属性

| 类型 | 名称 | 读写 | 功能描述 |
|------|------|------|----------|
| `int` | `MaxRating` | get/set | 设置最大评分值（通常为5） |
| `int` | `Rating` | get/set | 设置或获取当前评分 |
| `int` | `StarSize` | get/set | 设置星星的大小 |
| `int` | `Spacing` | get/set | 设置星星之间的间距 |
| `bool` | `IsReadOnly` | get/set | 设置是否为只读模式 |

### 信号

- `ratingChanged(int rating)` - 评分改变时发出

---

## ElaReminderCard

**继承**: `QPushButton` | **头文件**: `ElaReminderCard.h`

ElaReminderCard 是提醒卡片组件，用于显示提醒或备忘信息。

### 属性

| 类型 | 名称 | 读写 | 功能描述 |
|------|------|------|----------|
| `int` | `BorderRadius` | get/set | 设置卡片的边框圆角半径 |
| `QString` | `Title` | get/set | 设置卡片的标题 |
| `QString` | `SubTitle` | get/set | 设置卡片的副标题 |
| `int` | `TitlePixelSize` | get/set | 设置标题的像素大小 |
| `int` | `SubTitlePixelSize` | get/set | 设置副标题的像素大小 |
| `int` | `TitleSpacing` | get/set | 设置标题间的距离 |
| `QPixmap` | `CardPixmap` | get/set | 设置卡片的图片 |
| `QSize` | `CardPixmapSize` | get/set | 设置卡片图片的大小 |
| `int` | `CardPixmapBorderRadius` | get/set | 设置卡片图片的边框圆角 |
| `ElaCardPixType::PixMode` | `CardPixMode` | get/set | 设置卡片图片的显示模式 |

### 方法

- `void setCardPixmapSize(int width, int height)` - 设置卡片图片的宽度和高度

---

## ElaRoller

**继承**: `QWidget` | **头文件**: `ElaRoller.h`

ElaRoller 是滚轮选择器组件，用于选择列表中的项目。

### 属性

| 类型 | 名称 | 读写 | 功能描述 |
|------|------|------|----------|
| `int` | `BorderRadius` | get/set | 设置组件的边框圆角半径 |
| `QStringList` | `ItemList` | get/set | 设置滚轮的项目列表 |
| `int` | `ItemHeight` | get/set | 设置每个项目的高度 |
| `int` | `MaxVisibleItems` | get/set | 设置最多可见的项目数 |
| `int` | `CurrentIndex` | get/set | 设置或获取当前选中的索引 |
| `bool` | `IsContainer` | get/set | 设置是否为容器模式 |
| `bool` | `IsEnableLoop` | get/set | 设置是否启用循环滚动 |

### 方法

- `void setCurrentData(const QString& data)` - 按数据值设置当前选中项
- `QString getCurrentData()` - 获取当前选中项的数据

### 信号

- `currentDataChanged(const QString& data)` - 当前数据改变时发出

---

## ElaRollerPicker

**继承**: `QPushButton` | **头文件**: `ElaRollerPicker.h`

ElaRollerPicker 是滚轮选择器按钮，点击时弹出多个滚轮组成的选择器。

### 属性

| 类型 | 名称 | 读写 | 功能描述 |
|------|------|------|----------|
| `int` | `BorderRadius` | get/set | 设置按钮的边框圆角半径 |

### 方法

- `void addRoller(const QStringList& itemList, bool isEnableLoop = true)` - 添加新的滚轮及其项目列表
- `void removeRoller(int index)` - 移除指定索引的滚轮
- `void setRollerItemList(int index, const QStringList& itemList)` - 设置指定滚轮的项目列表
- `void setRollerWidth(int index, int width)` - 设置指定滚轮的宽度
- `void setCurrentData(int index, const QString& data)` - 设置指定滚轮的当前数据
- `void setCurrentData(const QStringList& dataList)` - 一次性设置所有滚轮的当前数据
- `QString getCurrentData(int index)` - 获取指定滚轮的当前数据
- `QStringList getCurrentData()` - 获取所有滚轮的当前数据
- `void setCurrentIndex(int rollerIndex, int index)` - 按索引设置指定滚轮的当前项
- `void setCurrentIndex(const QList<int>& indexList)` - 按索引列表设置所有滚轮的当前项
- `int getCurrentIndex(int rollerIndex)` - 获取指定滚轮的当前索引

### 信号

- `currentDataChanged(const QStringList& dataList)` - 当前数据改变时发出
- `currentDataSelectionChanged(const QStringList& dataList)` - 当前数据选择改变时发出

---

<!-- ============================================================================
第16部分：页面和路由组件
功能：提供页面管理、路由、标签页等页面切换和导航组件
包含：ElaScrollPage(滚动页面), ElaScrollPageArea(滚动页面区域),
      ElaPivot(枢纽), ElaTabBar(标签栏), ElaTabWidget(标签窗口),
      ElaRouter(路由器), ElaSteps(步骤条)
============================================================================ -->

## ElaRouter

**继承**: `QObject` | **头文件**: `ElaRouter.h`

### 方法

- `void bindWindow(ElaWindow* window)`
- `ElaWindow* getBoundWindow()`
- `ElaRouterType::NavigationResult addRoute(const ElaRouteConfig& config)`
- `ElaRouterType::NavigationResult addRoutes(const QVector<ElaRouteConfig>& configs)`
- `ElaRouterType::NavigationResult addDynamicRoute(const QString& parentPath, const ElaRouteConfig& config)`
- `ElaRouterType::NavigationResult removeRoute(const QString& path)`
- `bool hasRoute(const QString& path)`
- `QStringList getRoutePaths()`
- `QVariantMap getRouteMeta(const QString& path)`
- `ElaRouterType::NavigationResult push(const QString& path, const QVariantMap& params = {})`
- `ElaRouterType::NavigationResult replace(const QString& path, const QVariantMap& params = {})`
- `void back()`
- `void forward()`
- `QString getCurrentPath()`
- `QVariantMap getCurrentParams()`
- `int beforeEach(const ElaRouteGuard& guard)`
- `int afterEach(const ElaRouteAfterHook& hook)`
- `void removeBeforeGuard(int guardId)`
- `void removeAfterHook(int hookId)`
- `void setRouteBeforeEnter(const QString& path, const ElaRouteGuard& guard)`
- `void installRoutes()`
- `void resetRouter()`

### 信号

- `routeChanged(const QString& path, const QVariantMap& params)`
- `navigationBlocked(const QString& path)`
- `routeTableChanged()`

---

## ElaScreenCaptureManager

**继承**: `QObject` | **头文件**: `ElaScreenCaptureManager.h`

### 属性

| 类型 | 名称 | 读写 |
|------|------|------|
| `int` | `BorderRadius` | get/set |

### 方法

- `QStringList getDisplayList()`
- `QImage grabScreenToImage()`
- `void startGrabScreen()`
- `void stopGrabScreen()`
- `bool getIsGrabScreen()`
- `bool setDisplayID(int displayID)`
- `int getDisplayID()`
- `void setGrabArea(int width, int height)`
- `void setGrabArea(int x, int y, int width, int height)`
- `QRect getGrabArea()`
- `void setGrabFrameRate(int frameRateValue)`
- `int getGrabFrameRate()`
- `explicit ElaScreenCaptureScreen(QWidget* parent = nullptr)`
- `void setIsSyncGrabSize(bool isSyncGrabSize)`
- `bool getIsSyncGrabSize()`

### 信号

- `grabImageUpdate(QImage img)`

---

<!-- ============================================================================
第12部分：布局和容器组件
功能：提供流式布局、滚动区域、分割线、分组框等容器和布局组件
包含：ElaFlowLayout(流式布局), ElaScrollArea(滚动区域),
      ElaScrollBar(滚动条), ElaSplitter(分割线),
      ElaGroupBox(分组框), ElaDrawerArea(抽屉区域),
      ElaSheetPanel(底部面板)
============================================================================ -->

## ElaScrollArea

**继承**: `QScrollArea` | **头文件**: `ElaScrollArea.h`

### 方法

- `void setIsGrabGesture(bool isEnable, qreal mousePressEventDelay = 0.5)`
- `void setIsOverShoot(Qt::Orientation orientation, bool isEnable)`
- `bool getIsOverShoot(Qt::Orientation orientation)`
- `void setIsAnimation(Qt::Orientation orientation, bool isAnimation)`
- `bool getIsAnimation(Qt::Orientation orientation)`

---

## ElaScrollBar

**继承**: `QScrollBar` | **头文件**: `ElaScrollBar.h`

### 属性

| 类型 | 名称 | 读写 |
|------|------|------|
| `bool` | `IsAnimation` | get/set |
| `qreal` | `SpeedLimit` | get/set |

### 信号

- `rangeAnimationFinished()`

---

## ElaScrollPage

**继承**: `QWidget` | **头文件**: `ElaScrollPage.h`

### 属性

| 类型 | 名称 | 读写 |
|------|------|------|
| `QWidget*` | `CustomWidget` | get/set |

### 方法

- `void addCentralWidget(QWidget* centralWidget, bool isWidgetResizeable = true, bool isVerticalGrabGesture = true, qreal mousePressEventDelay = 0.5)`
- `void setPageTitle(const QString& title)`
- `void navigation(int widgetIndex, bool isLogRoute = true)`
- `void setPageTitleSpacing(int spacing)`
- `int getPageTitleSpacing()`
- `void setTitleVisible(bool isVisible)`

---

## ElaScrollPageArea

**继承**: `QWidget` | **头文件**: `ElaScrollPageArea.h`

### 属性

| 类型 | 名称 | 读写 |
|------|------|------|
| `int` | `BorderRadius` | get/set |

---

## ElaSelectorBar

**继承**: `QWidget` | **头文件**: `ElaSelectorBar.h`

ElaSelectorBar 是选择器栏组件，用于在多个选项之间进行选择，常用于标签页或选项切换。

### 属性

| 类型 | 名称 | 读写 | 功能描述 |
|------|------|------|----------|
| `int` | `CurrentIndex` | get/set | 设置或获取当前选中的索引 |
| `int` | `BorderRadius` | get/set | 设置选择器栏的边框圆角半径 |

### 方法

- `void addItem(const QString& text)` - 添加一个文本选项
- `void addItem(ElaIconType::IconName icon, const QString& text)` - 添加带图标的选项
- `void clearItems()` - 清空所有选项
- `int getItemCount()` - 获取选项总数

### 信号

- `currentIndexChanged(int index)` - 当前选中的索引改变时发出

---

## ElaSheetPanel

**继承**: `QWidget` | **头文件**: `ElaSheetPanel.h`

ElaSheetPanel 是底部面板组件，提供从屏幕底部滑出的模态面板，支持多个停驻位置。

### 属性

| 类型 | 名称 | 读写 | 功能描述 |
|------|------|------|----------|
| `int` | `BorderRadius` | get/set | 设置面板的边框圆角半径 |
| `ElaSheetPanelType::Direction` | `Direction` | get/set | 设置面板展开的方向 |
| `qreal` | `PeekRatio` | get/set | 设置窥视状态时显示的高度比例 |
| `qreal` | `HalfRatio` | get/set | 设置半展开状态的高度比例 |
| `qreal` | `FullRatio` | get/set | 设置全展开状态的高度比例 |
| `bool` | `DragHandleVisible` | get/set | 设置是否显示拖拽手柄 |
| `bool` | `CloseOnOverlayClick` | get/set | 设置点击半透明遮罩时是否关闭面板 |
| `qreal` | `OverlayOpacity` | get/set | 设置半透明遮罩的透明度 |

### 枚举

**DetentLevel**: 
- `Peek` - 窥视状态（显示部分内容）
- `Half` - 半展开状态
- `Full` - 全展开状态

### 方法

- `void setCentralWidget(QWidget* widget)` - 设置面板的中心内容组件
- `void open(ElaSheetPanelType::DetentLevel level = ElaSheetPanelType::Half)` - 打开面板并设置停驻位置
- `void close()` - 关闭面板
- `ElaSheetPanelType::DetentLevel currentDetent()` - 获取当前停驻位置
- `bool isOpened()` - 检查面板是否打开

### 信号

- `opened()` - 面板打开时发出
- `closed()` - 面板关闭时发出
- `detentChanged(ElaSheetPanelType::DetentLevel level)` - 停驻位置改变时发出

---

## ElaSkeleton

**继承**: `QWidget` | **头文件**: `ElaSkeleton.h`

ElaSkeleton 是骨架屏组件，用于在内容加载时显示占位符动画。

### 属性

| 类型 | 名称 | 读写 | 功能描述 |
|------|------|------|----------|
| `int` | `BorderRadius` | get/set | 设置占位符的边框圆角半径 |
| `bool` | `IsAnimated` | get/set | 设置是否启用加载动画 |

### 枚举

**SkeletonType**: 
- `Text` - 文本占位符
- `Circle` - 圆形占位符
- `Rectangle` - 矩形占位符

### 方法

- `void setSkeletonType(SkeletonType type)` - 设置占位符的类型
- `SkeletonType getSkeletonType()` - 获取当前占位符的类型

---

## ElaSlider

**继承**: `QSlider` | **头文件**: `ElaSlider.h`

ElaSlider 是滑块控件，用于选择一个范围内的数值。

### 属性

| 类型 | 名称 | 读写 | 功能描述 |
|------|------|------|----------|
| `int` | `BorderRadius` | get/set | 设置滑块的边框圆角半径 |
| `int` | `ThumbSize` | get/set | 设置滑块的大小 |
| `bool` | `IsEnableAnimation` | get/set | 设置是否启用动画效果 |

---

## ElaSnackbar

**继承**: `QWidget` | **头文件**: `ElaSnackbar.h`

ElaSnackbar 是消息条组件，用于显示简短的消息反馈，通常在屏幕下方显示。

### 属性

| 类型 | 名称 | 读写 | 功能描述 |
|------|------|------|----------|
| `int` | `BorderRadius` | get/set | 设置消息条的边框圆角半径 |
| `int` | `DisplayMsec` | get/set | 设置消息条自动关闭的时间（毫秒） |

### 枚举

**SnackbarType**: 
- `Success` - 成功消息
- `Info` - 信息消息
- `Warning` - 警告消息
- `Error` - 错误消息

### 方法

- `void dismiss()` - 手动关闭消息条
- `static void setMaxCount(int count)` - 设置同时显示的最多消息条数量
- `static int getMaxCount()` - 获取最多消息条数量
- `static ElaSnackbar* success(const QString& text, const QString& actionText = "", int displayMsec = 4000, QWidget* parent = nullptr)` - 显示成功消息
- `static ElaSnackbar* info(const QString& text, const QString& actionText = "", int displayMsec = 4000, QWidget* parent = nullptr)` - 显示信息消息
- `static ElaSnackbar* warning(const QString& text, const QString& actionText = "", int displayMsec = 4000, QWidget* parent = nullptr)` - 显示警告消息
- `static ElaSnackbar* error(const QString& text, const QString& actionText = "", int displayMsec = 4000, QWidget* parent = nullptr)` - 显示错误消息

### 信号

- `actionClicked()` - 用户点击操作按钮时发出
- `closed()` - 消息条关闭时发出

---

## ElaSpinBox

**继承**: `QSpinBox` | **头文件**: `ElaSpinBox.h`

ElaSpinBox 是数值输入框组件，用于输入和调整整数值。

### 属性

| 类型 | 名称 | 读写 | 功能描述 |
|------|------|------|----------|
| `ElaSpinBoxType::ButtonMode` | `ButtonMode` | get/set | 设置增减按钮的显示模式 |
| `int` | `BorderRadius` | get/set | 设置输入框的边框圆角半径 |

### 枚举

**ButtonMode**:
- `Normal` - 标准模式，按钮在两侧
- `Compact` - 紧凑模式，按钮在右侧堆叠
- `Icon` - 图标模式，使用图标表示增减

---

## ElaSplashScreen

**继承**: `QWidget` | **头文件**: `ElaSplashScreen.h`

ElaSplashScreen 是启动画面组件，用于在应用启动时显示进度和品牌信息。

### 属性

| 类型 | 名称 | 读写 | 功能描述 |
|------|------|------|----------|
| `int` | `BorderRadius` | get/set | 设置启动画面的边框圆角半径 |
| `int` | `Minimum` | get/set | 设置进度条的最小值 |
| `int` | `Maximum` | get/set | 设置进度条的最大值 |
| `int` | `Value` | get/set | 设置进度条的当前值 |
| `bool` | `IsShowProgressBar` | get/set | 设置是否显示进度条 |
| `bool` | `IsShowProgressRing` | get/set | 设置是否显示进度圆环 |
| `bool` | `IsClosable` | get/set | 设置用户是否可以手动关闭启动画面 |

### 方法

- `void setLogo(const QPixmap& logo)` - 设置启动画面的logo图像
- `void setTitle(const QString& title)` - 设置标题文本
- `void setSubTitle(const QString& subTitle)` - 设置副标题文本
- `void setStatusText(const QString& text)` - 设置状态描述文本
- `void show()` - 显示启动画面
- `void close()` - 关闭启动画面
- `void finish(QWidget* mainWindow)` - 完成启动画面并显示主窗口

### 信号

- `closed()` - 启动画面关闭时发出

---

## ElaSplitButton

**继承**: `QWidget` | **头文件**: `ElaSplitButton.h`

ElaSplitButton 是分割按钮组件，由主按钮和下拉菜单按钮组成，支持快速操作和选项菜单。

### 属性

| 类型 | 名称 | 读写 | 功能描述 |
|------|------|------|----------|
| `int` | `BorderRadius` | get/set | 设置按钮的边框圆角半径 |
| `QString` | `Text` | get/set | 设置主按钮的文本 |
| `ElaIconType::IconName` | `ElaIcon` | get/set | 设置按钮的图标 |

### 方法

- `void setMenu(ElaMenu* menu)` - 设置下拉菜单
- `ElaMenu* getMenu()` - 获取下拉菜单

### 信号

- `clicked()` - 主按钮被点击时发出

---

## ElaSplitter

**继承**: `QSplitter` | **头文件**: `ElaSplitter.h`

ElaSplitter 是分割线组件，用于分割和调整相邻窗口部件的大小。

### 属性

| 类型 | 名称 | 读写 | 功能描述 |
|------|------|------|----------|
| `int` | `HandleWidth` | get/set | 设置分割线句柄的宽度 |
| `int` | `GripLength` | get/set | 设置分割线句柄的长度 |

---

## ElaSpotlight

**继承**: `QWidget` | **头文件**: `ElaSpotlight.h`

ElaSpotlight 是聚焦提示组件，用于引导用户关注界面的特定区域，常用于新手教程。

### 属性

| 类型 | 名称 | 读写 | 功能描述 |
|------|------|------|----------|
| `int` | `BorderRadius` | get/set | 设置高亮区域的边框圆角半径 |
| `int` | `Padding` | get/set | 设置高亮区域到目标区域的间距 |
| `int` | `OverlayAlpha` | get/set | 设置遮罩层的透明度 |
| `bool` | `IsCircle` | get/set | 设置是否使用圆形高亮而非矩形 |
| `QString` | `Title` | get/set | 设置提示标题 |
| `QString` | `Content` | get/set | 设置提示内容 |

### 结构体

**SpotlightStep**: 聚焦步骤配置
- `QWidget* target` - 要高亮的目标组件
- `QString title` - 该步骤的标题
- `QString content` - 该步骤的说明文本

### 方法

- `void showSpotlight(QWidget* target, const QString& buttonText = "知道了")` - 显示单个高亮
- `void setSteps(const QList<SpotlightStep>& steps)` - 设置多步骤聚焦序列
- `void start()` - 开始聚焦流程
- `void next()` - 跳转到下一步
- `void previous()` - 返回上一步
- `void finish()` - 完成聚焦并关闭
- `int currentStep()` - 获取当前步骤号
- `int stepCount()` - 获取总步骤数

### 信号

- `stepChanged(int step)` - 步骤改变时发出
- `finished()` - 聚焦完成时发出

---

## ElaStatCard

**继承**: `QWidget` | **头文件**: `ElaStatCard.h`

ElaStatCard 是统计卡片组件，用于显示数据统计和指标信息。

### 属性

| 类型 | 名称 | 读写 | 功能描述 |
|------|------|------|----------|
| `QString` | `Title` | get/set | 设置卡片标题 |
| `QString` | `Value` | get/set | 设置统计数值 |
| `QString` | `Description` | get/set | 设置描述文本 |
| `int` | `BorderRadius` | get/set | 设置卡片的边框圆角半径 |
| `ElaIconType::IconName` | `CardIcon` | get/set | 设置卡片的图标 |
| `QString` | `Trend` | get/set | 设置趋势标签文本 |
| `ElaStatCardType::TrendType` | `TrendType` | get/set | 设置趋势类型 |

### 枚举

**TrendType**: 
- `None` - 无趋势
- `Up` - 上升趋势（显示绿色向上箭头）
- `Down` - 下降趋势（显示红色向下箭头）
- `Neutral` - 中性趋势（无箭头）

### 方法

- `void setTrend(TrendType trend)` - 设置趋势类型
- `TrendType getTrend()` - 获取趋势类型
- `void setTrendText(const QString& text)` - 设置趋势文本
- `QString getTrendText()` - 获取趋势文本

---

## ElaStatusBar

**继承**: `QStatusBar` | **头文件**: `ElaStatusBar.h`

ElaStatusBar 是状态栏组件，用于在窗口底部显示应用状态和信息。

### 属性

| 类型 | 名称 | 读写 | 功能描述 |
|------|------|------|----------|
| `int` | `BorderRadius` | get/set | 设置状态栏的边框圆角半径 |
| `bool` | `IsShowBorder` | get/set | 设置是否显示上边框 |

### 方法

- `void addPermanentWidget(QWidget* widget, int stretch = 0)` - 添加永久显示的组件
- `void addWidget(QWidget* widget, int stretch = 0)` - 添加状态消息组件
- `void showMessage(const QString& message, int timeout = 0)` - 显示状态消息
- `void clearMessage()` - 清除状态消息

---

## ElaSteps

**继承**: `QWidget` | **头文件**: `ElaSteps.h`

ElaSteps 是步骤指示器组件，用于显示流程的进度和步骤。

### 属性

| 类型 | 名称 | 读写 | 功能描述 |
|------|------|------|----------|
| `int` | `CurrentStep` | get/set | 设置或获取当前步骤 |
| `int` | `StepCount` | get/set | 设置或获取总步骤数 |
| `int` | `StepSpacing` | get/set | 设置步骤之间的间距 |
| `bool` | `IsVertical` | get/set | 设置是否为纵向显示 |

### 方法

- `void setStepTitles(const QStringList& titles)` - 设置所有步骤的标题
- `QStringList getStepTitles()` - 获取所有步骤的标题
- `void setStepDescription(int index, const QString& description)` - 为指定步骤设置描述
- `next()` - 跳转到下一步骤
- `previous()` - 返回上一步骤

### 信号

- `currentStepChanged(int step)` - 当前步骤改变时发出

---

## ElaSuggestBox

**继承**: `QWidget` | **头文件**: `ElaSuggestBox.h`

ElaSuggestBox 是建议输入框组件，输入时显示匹配的建议列表。

### 属性

| 类型 | 名称 | 读写 | 功能描述 |
|------|------|------|----------|
| `int` | `BorderRadius` | get/set | 设置输入框的边框圆角半径 |
| `Qt::CaseSensitivity` | `CaseSensitivity` | get/set | 设置建议匹配是否区分大小写 |
| `QString` | `PlaceholderText` | get/set | 设置占位符文本 |
| `int` | `MaxSuggestions` | get/set | 设置显示的最多建议数量 |

### 结构体

**SuggestData**: 建议数据容器
- `ElaIconType::IconName icon` - 建议的图标
- `QString suggestText` - 建议的文本
- `QVariantMap suggestData` - 建议的关联数据

### 方法

- `void setPlaceholderText(const QString& placeholderText)` - 设置占位符文本
- `QString addSuggestion(const QString& suggestText, const QVariantMap& suggestData = {})` - 添加文本建议
- `QString addSuggestion(ElaIconType::IconName icon, const QString& suggestText, const QVariantMap& suggestData = {})` - 添加带图标的建议
- `QString addSuggestion(const ElaSuggestBox::SuggestData& suggestData)` - 添加完整的建议数据
- `QStringList addSuggestion(const QList<ElaSuggestBox::SuggestData>& suggestDataList)` - 批量添加建议
- `void removeSuggestion(const QString& suggestKey)` - 按键移除建议
- `void removeSuggestion(int index)` - 按索引移除建议
- `void clearSuggestion()` - 清空所有建议

### 信号

- `suggestionClicked(const ElaSuggestBox::SuggestData& suggestData)` - 用户选择建议时发出

---

## ElaTabBar

**继承**: `QTabBar` | **头文件**: `ElaTabBar.h`

ElaTabBar 是标签栏组件，用于选择和管理多个标签页。

### 属性

| 类型 | 名称 | 读写 | 功能描述 |
|------|------|------|----------|
| `QSize` | `TabSize` | get/set | 设置标签页的大小 |
| `int` | `TabSpacing` | get/set | 设置标签页之间的间距 |
| `bool` | `IsDragDropEnabled` | get/set | 设置是否启用拖拽功能 |

### 信号

- `tabDragCreate(QMimeData* mimeData)` - 标签被拖出时发出
- `tabDragEnter(QMimeData* mimeData)` - 拖拽进入时发出
- `tabDragLeave(QMimeData* mimeData)` - 拖拽离开时发出
- `tabDragDrop(QMimeData* mimeData)` - 拖拽放下时发出

---

## ElaTabWidget

**继承**: `QTabWidget` | **头文件**: `ElaTabWidget.h`

ElaTabWidget 是标签组件，管理多个页面的显示和切换。

### 属性

| 类型 | 名称 | 读写 | 功能描述 |
|------|------|------|----------|
| `bool` | `IsTabTransparent` | get/set | 设置标签栏是否透明 |
| `bool` | `IsContainerAcceptDrops` | get/set | 设置是否接受拖拽放下 |
| `QSize` | `TabSize` | get/set | 设置标签页的大小 |
| `int` | `BorderRadius` | get/set | 设置组件的边框圆角半径 |

### 方法

- `void setTabPosition(TabPosition position)` - 设置标签栏的位置（顶部/底部/左侧/右侧）

---

## ElaTableView

**继承**: `QTableView` | **头文件**: `ElaTableView.h`

ElaTableView 是表格视图组件，用于显示模型数据的表格。

### 属性

| 类型 | 名称 | 读写 | 功能描述 |
|------|------|------|----------|
| `int` | `HeaderMargin` | get/set | 设置表头边距 |
| `bool` | `IsAlternatingRowColors` | get/set | 设置是否启用行交替颜色 |
| `int` | `RowHeight` | get/set | 设置行高 |

### 信号

- `tableViewShow()` - 表格显示时发出
- `tableViewHide()` - 表格隐藏时发出

---

## ElaTableWidget

**继承**: `QTableWidget` | **头文件**: `ElaTableWidget.h`

ElaTableWidget 是表格组件，提供便捷的基于项的表格编辑功能。

### 属性

| 类型 | 名称 | 读写 | 功能描述 |
|------|------|------|----------|
| `int` | `ItemHeight` | get/set | 设置表格行高 |
| `int` | `HeaderMargin` | get/set | 设置表头边距 |
| `bool` | `IsTransparent` | get/set | 设置表格背景是否透明 |
| `bool` | `IsAlternatingRowColors` | get/set | 设置是否启用行交替颜色 |

### 方法

- `void insertRows(int row, int count)` - 在指定行插入多行
- `void removeRows(int row, int count)` - 删除指定行
- `void insertColumns(int column, int count)` - 在指定列插入多列
- `void removeColumns(int column, int count)` - 删除指定列
- `void setItemText(int row, int column, const QString& text)` - 设置指定单元格的文本
- `QString getItemText(int row, int column)` - 获取指定单元格的文本
- `void setRowData(int row, const QStringList& data)` - 设置整行数据
- `QStringList getRowData(int row)` - 获取整行数据

### 信号

- `tableWidgetShow()` - 表格显示时发出
- `tableWidgetHide()` - 表格隐藏时发出

---

<!-- ============================================================================
第13部分：标签和信息显示组件
功能：提供标签、徽章、人物头像、文本、时间轴等信息展示组件
包含：ElaTag(标签), ElaInfoBadge(信息徽章), ElaPersonPicture(人物头像),
      ElaText(文本), ElaWatermark(水印), ElaTimeline(时间轴),
      ElaMarkdownViewer(Markdown查看器)
============================================================================ -->

## ElaTag

**继承**: `QWidget` | **头文件**: `ElaTag.h`

ElaTag 是标签组件，用于显示和管理标签，支持关闭和选择功能。

### 属性

| 类型 | 名称 | 读写 | 功能描述 |
|------|------|------|----------|
| `int` | `BorderRadius` | get/set | 设置标签的边框圆角半径 |
| `QString` | `TagText` | get/set | 设置标签文本 |
| `bool` | `IsClosable` | get/set | 设置是否显示关闭按钮 |
| `bool` | `IsCheckable` | get/set | 设置是否可以被选中 |
| `bool` | `IsChecked` | get/set | 设置是否被选中 |

### 枚举

**TagColor**: `Default`, `Primary`, `Success`, `Warning`, `Danger`

### 方法

- `void setTagColor(TagColor color)`
- `TagColor getTagColor()`

### 信号

- `closed()`
- `clicked()`
- `checkedChanged(bool checked)`

---

## ElaTeachingTip

**继承**: `QWidget` | **头文件**: `ElaTeachingTip.h`

ElaTeachingTip 是教学提示组件，用于引导用户了解应用功能，类似于教程气泡。

### 属性

| 类型 | 名称 | 读写 | 功能描述 |
|------|------|------|----------|
| `int` | `BorderRadius` | get/set | 设置提示框的边框圆角半径 |
| `QString` | `Title` | get/set | 设置提示标题 |
| `QString` | `SubTitle` | get/set | 设置提示副标题 |
| `QString` | `Content` | get/set | 设置提示内容 |
| `ElaIconType::IconName` | `TipIcon` | get/set | 设置提示图标 |
| `QPixmap` | `HeroImage` | get/set | 设置英雄图片 |
| `bool` | `IsLightDismiss` | get/set | 设置点击外部是否关闭提示 |

### 枚举

**TailPosition**: 尾部箭头位置
- `Auto` - 自动选择
- `Top` - 上方
- `Bottom` - 下方
- `Left` - 左方
- `Right` - 右方

### 方法

- `void setTailPosition(TailPosition position)` - 设置尾部箭头位置
- `TailPosition getTailPosition()` - 获取尾部箭头位置
- `void setTarget(QWidget* target)` - 设置指向的目标组件
- `QWidget* getTarget()` - 获取指向的目标组件
- `void setCloseButtonVisible(bool visible)` - 设置关闭按钮是否可见
- `void clearActions()` - 清除所有操作按钮
- `void showTip()` - 显示提示框
- `void closeTip()` - 关闭提示框

### 信号

- `closed()` - 提示框关闭时发出
- `closeButtonClicked()` - 用户点击关闭按钮时发出

---

## ElaText

**继承**: `QLabel` | **头文件**: `ElaText.h`

ElaText 是文本显示组件，提供多种文本风格和对齐方式。

### 属性

| 类型 | 名称 | 读写 | 功能描述 |
|------|------|------|----------|
| `bool` | `IsWrapAnywhere` | get/set | 设置文本是否在任何位置换行 |
| `int` | `TextPixelSize` | get/set | 设置文本像素大小 |
| `int` | `TextPointSize` | get/set | 设置文本点数大小 |
| `ElaTextType::TextStyle` | `TextStyle` | get/set | 设置文本风格（标题/正文/标签等） |
| `ElaIconType::IconName` | `ElaIcon` | get/set | 设置显示的图标 |
| `int` | `TextBoxHeight` | get/set | 设置文本框高度 |

### 枚举

**TextStyle**:
- `DisplayLarge` - 显示大标题
- `DisplayMedium` - 显示中标题
- `DisplaySmall` - 显示小标题
- `HeadlineLarge` - 大标题
- `HeadlineMedium` - 中标题
- `HeadlineSmall` - 小标题
- `TitleLarge` - 大副标题
- `TitleMedium` - 中副标题
- `TitleSmall` - 小副标题
- `BodyLarge` - 大正文
- `BodyMedium` - 中正文
- `BodySmall` - 小正文
- `LabelLarge` - 大标签
- `LabelMedium` - 中标签
- `LabelSmall` - 小标签

---

## ElaTimeline

**继承**: `QWidget` | **头文件**: `ElaTimeline.h`

ElaTimeline 是时间轴组件，用于显示事件序列或历史记录。

### 结构体

**TimelineItem**: 时间线项目
- `QString title` - 项目标题
- `QString content` - 项目内容描述
- `QString timestamp` - 时间戳
- `ElaIconType::IconName icon` - 项目图标

### 方法

- `void addItem(const TimelineItem& item)` - 添加一个时间线项目
- `void addItem(const QString& title, const QString& content, const QString& timestamp)` - 添加项目（简化版）
- `void clearItems()` - 清空所有项目
- `int getItemCount()` - 获取项目总数
- `void setOrientation(Qt::Orientation orientation)` - 设置时间线方向（竖直/水平）

### 信号

- `itemClicked(int index)` - 项目被点击时发出

---

## ElaToast

**继承**: `QWidget` | **头文件**: `ElaToast.h`

ElaToast 是提示框组件，用于显示临时的消息提示，自动消失。

### 属性

| 类型 | 名称 | 读写 | 功能描述 |
|------|------|------|----------|
| `int` | `BorderRadius` | get/set | 设置提示框的边框圆角半径 |
| `int` | `DisplayMsec` | get/set | 设置提示框自动关闭的时间（毫秒） |

### 枚举

**ToastType**: 
- `Success` - 成功提示
- `Info` - 信息提示
- `Warning` - 警告提示
- `Error` - 错误提示

### 方法

- `static void success(const QString& text, int displayMsec = 2000, QWidget* parent = nullptr)` - 显示成功提示
- `static void info(const QString& text, int displayMsec = 2000, QWidget* parent = nullptr)` - 显示信息提示
- `static void warning(const QString& text, int displayMsec = 2000, QWidget* parent = nullptr)` - 显示警告提示
- `static void error(const QString& text, int displayMsec = 2000, QWidget* parent = nullptr)` - 显示错误提示
- `void setDisplayPosition(Qt::Alignment alignment)` - 设置提示框显示的位置

### 信号

- `closed()` - 提示框关闭时发出

---

## ElaToggleButton

**继承**: `QWidget` | **头文件**: `ElaToggleButton.h`

ElaToggleButton 是切换按钮组件，可以被点击以在两个状态之间切换。

### 属性

| 类型 | 名称 | 读写 | 功能描述 |
|------|------|------|----------|
| `int` | `BorderRadius` | get/set | 设置按钮的边框圆角半径 |
| `QString` | `Text` | get/set | 设置按钮文本 |
| `bool` | `IsToggled` | get/set | 设置是否已切换状态 |

### 方法

- `void setIsToggled(bool isToggled)` - 设置切换状态
- `bool getIsToggled()` - 获取切换状态

### 信号

- `toggled(bool checked)` - 切换状态改变时发出

---

## ElaToggleSwitch

**继承**: `QWidget` | **头文件**: `ElaToggleSwitch.h`

ElaToggleSwitch 是切换开关组件，用于在两个状态之间快速切换。

### 属性

| 类型 | 名称 | 读写 | 功能描述 |
|------|------|------|----------|
| `bool` | `IsChecked` | get/set | 设置是否选中 |
| `int` | `ThumbSize` | get/set | 设置滑块大小 |
| `int` | `AnimationDuration` | get/set | 设置动画持续时间 |

### 方法

- `void setIsToggled(bool isToggled)` - 设置切换状态
- `bool getIsToggled()` - 获取切换状态
- `void toggle()` - 切换状态

### 信号

- `toggled(bool checked)` - 切换状态改变时发出

---

## ElaToolBar

**继承**: `QToolBar` | **头文件**: `ElaToolBar.h`

ElaToolBar 是工具栏组件，用于放置工具按钮和常用操作。

### 属性

| 类型 | 名称 | 读写 | 功能描述 |
|------|------|------|----------|
| `int` | `ToolBarSpacing` | get/set | 设置工具栏内项目的间距 |
| `int` | `BorderRadius` | get/set | 设置工具栏的边框圆角半径 |

### 方法

- `void setToolBarSpacing(int spacing)` - 设置工具栏间距
- `int getToolBarSpacing()` - 获取工具栏间距
- `QAction* addElaIconAction(ElaIconType::IconName icon, const QString& text)` - 添加图标操作
- `QAction* addElaIconAction(ElaIconType::IconName icon, const QString& text, const QKeySequence& shortcut)` - 添加带快捷键的图标操作

---

## ElaToolButton

**继承**: `QToolButton` | **头文件**: `ElaToolButton.h`

ElaToolButton 是工具按钮组件，用于工具栏中显示图标按钮。

### 属性

| 类型 | 名称 | 读写 | 功能描述 |
|------|------|------|----------|
| `ElaIconType::IconName` | `ElaIcon` | get/set | 设置按钮的图标 |
| `QString` | `ToolTip` | get/set | 设置工具提示文本 |
| `int` | `IconSize` | get/set | 设置图标大小 |

### 属性

| 类型 | 名称 | 读写 | 功能描述 |
|------|------|------|----------|
| `int` | `BorderRadius` | get/set | 设置按钮的边框圆角半径 |
| `bool` | `IsSelected` | get/set | 设置是否被选中 |
| `bool` | `IsTransparent` | get/set | 设置是否为透明背景 |

### 方法

- `void setIsTransparent(bool isTransparent)` - 设置是否透明
- `bool getIsTransparent()` - 获取透明状态
- `void setMenu(ElaMenu* menu)` - 设置关联菜单
- `void setElaIcon(ElaIconType::IconName icon)` - 设置图标
- `void setElaIcon(ElaIconType::IconName icon, int rotate)` - 设置带旋转角度的图标

---

## ElaToolTip

**继承**: `QWidget` | **头文件**: `ElaToolTip.h`

ElaToolTip 是工具提示组件，用于在悬停时显示说明文本或自定义内容。

### 属性

| 类型 | 名称 | 读写 | 功能描述 |
|------|------|------|----------|
| `int` | `BorderRadius` | get/set | 设置提示框的边框圆角半径 |
| `int` | `DisplayMsec` | get/set | 设置显示持续时间 |
| `int` | `ShowDelayMsec` | get/set | 设置显示延迟时间 |
| `int` | `HideDelayMsec` | get/set | 设置隐藏延迟时间 |
| `QString` | `ToolTip` | get/set | 设置提示文本 |
| `QWidget*` | `CustomWidget` | get/set | 设置自定义内容组件 |

### 方法

- `void updatePos()` - 更新提示框位置
- `void show()` - 显示提示
- `void hide()` - 隐藏提示

---

## ElaTransfer

**继承**: `QWidget` | **头文件**: `ElaTransfer.h`

ElaTransfer 是传输组件，用于在两个列表之间移动项目。

### 属性

| 类型 | 名称 | 读写 | 功能描述 |
|------|------|------|----------|
| `int` | `BorderRadius` | get/set | 设置组件的边框圆角半径 |
| `int` | `ItemHeight` | get/set | 设置列表项的高度 |
| `QString` | `SourceTitle` | get/set | 设置源列表的标题 |
| `QString` | `TargetTitle` | get/set | 设置目标列表的标题 |
| `bool` | `IsSearchVisible` | get/set | 设置是否显示搜索框 |

### 方法

- `void setSourceItems(const QStringList& items)` - 设置源列表项
- `void addSourceItem(const QString& text)` - 添加源项
- `void addSourceItems(const QStringList& items)` - 批量添加源项
- `QStringList getSourceItems()` - 获取源列表项
- `QStringList getTargetItems()` - 获取目标列表项
- `void moveToTarget()` - 移动选中项到目标列表
- `void moveToSource()` - 移动选中项到源列表
- `void moveAllToTarget()` - 移动所有项到目标列表
- `void moveAllToSource()` - 移动所有项到源列表

### 信号

- `transferChanged(const QStringList& sourceItems, const QStringList& targetItems)` - 传输内容改变时发出

---

## ElaTreeView

**继承**: `QTreeView` | **头文件**: `ElaTreeView.h`

ElaTreeView 是树形视图组件，用于显示层级结构的数据。

### 属性

| 类型 | 名称 | 读写 | 功能描述 |
|------|------|------|----------|
| `int` | `ItemHeight` | get/set | 设置树形项的高度 |
| `int` | `HeaderMargin` | get/set | 设置表头边距 |
| `bool` | `IsAlternatingRowColors` | get/set | 设置是否启用行交替颜色 |

### 方法

- `void setAllItemsExpanded(bool expanded)` - 展开或折叠所有项
- `void setItemHeightByVerticalScrollBar(int height)` - 根据垂直滚动条设置项高度

---

## ElaVirtualList

**继承**: `QListView` | **头文件**: `ElaVirtualList.h`

ElaVirtualList 是虚拟列表组件，用于高效显示大量数据，只渲染可见项。

### 属性

| 类型 | 名称 | 读写 | 功能描述 |
|------|------|------|----------|
| `int` | `ItemHeight` | get/set | 设置列表项的高度 |
| `bool` | `IsTransparent` | get/set | 设置列表背景是否透明 |
| `bool` | `IsAlternatingRowColors` | get/set | 设置是否启用行交替颜色 |

### 方法

- `void setItemCount(int count)` - 设置列表项总数
- `int getItemCount()` - 获取列表项总数
- `void scrollToItem(int index)` - 滚动到指定项

### 信号

- `itemRequestData(int startIndex, int endIndex)` - 需要数据时发出，提供可见范围

---

## ElaWatermark

**继承**: `QWidget` | **头文件**: `ElaWatermark.h`

ElaWatermark 是水印组件，用于在界面上显示文本水印或图像水印。

### 属性

| 类型 | 名称 | 读写 | 功能描述 |
|------|------|------|----------|
| `QString` | `Text` | get/set | 设置水印文本 |
| `int` | `FontPixelSize` | get/set | 设置水印字体像素大小 |
| `qreal` | `Opacity` | get/set | 设置水印透明度（0-1） |
| `qreal` | `Rotation` | get/set | 设置水印旋转角度 |
| `int` | `GapX` | get/set | 设置水印水平间距 |
| `int` | `GapY` | get/set | 设置水印竖直间距 |
| `QColor` | `TextColor` | get/set | 设置水印文本颜色 |
| `QImage` | `Image` | get/set | 设置水印图像 |
| `int` | `ImageWidth` | get/set | 设置水印图像宽度 |
| `int` | `ImageHeight` | get/set | 设置水印图像高度 |

---

## ElaWizard

**继承**: `QWidget` | **头文件**: `ElaWizard.h`

ElaWizard 是向导组件，提供多步向导功能，用于引导用户完成复杂的配置流程。

### 属性

| 类型 | 名称 | 读写 | 功能描述 |
|------|------|------|----------|
| `int` | `BorderRadius` | get/set | 设置向导的边框圆角半径 |
| `int` | `CurrentStep` | get/set | 设置或获取当前步骤 |
| `int` | `StepCount` | get/set | 设置或获取步骤总数 |
| `QString` | `Title` | get/set | 设置向导标题 |
| `QString` | `SubTitle` | get/set | 设置向导副标题 |

### 方法

- `void addStep(const QString& title, QWidget* page)` - 添加向导步骤
- `void insertStep(int index, const QString& title, QWidget* page)` - 在指定位置插入步骤
- `void removeStep(int index)` - 移除指定步骤
- `void next()` - 前进到下一步
- `void previous()` - 返回到上一步
- `void finish()` - 完成向导
- `int getStepCount()` - 获取步骤总数
- `QWidget* getCurrentPage()` - 获取当前页面
- `void setButtonText(const QString& nextText, const QString& backText, const QString& finishText)` - 设置按钮文本

### 信号

- `currentStepChanged(int step)` - 当前步骤改变时发出
- `finished()` - 向导完成时发出
- `cancelled()` - 向导被取消时发出

---

<!-- ============================================================================
文档说明：
本API文档完整列出了ElaWidgetTools库提供的113个公开组件的详细信息。
每个组件都包括以下内容：
- 继承关系：说明该组件继承自哪个Qt基类
- 头文件：包含该组件的头文件名称
- 功能描述：简明扼要说明该组件的用途和主要功能
- 属性：可读写的属性列表，包括类型、名称、访问权限和功能描述
- 方法：公开方法列表，包括参数和功能说明
- 枚举：如果有枚举类型，列出所有枚举值的说明
- 信号：Qt信号列表，用于事件处理和回调
- 结构体：如果有相关结构体，提供成员变量说明

使用建议：
1. 按照功能分类找到你需要的组件
2. 查看继承关系了解组件的基础功能
3. 阅读功能描述快速了解组件用途
4. 根据需要查看属性、方法和信号进行开发
5. 通过信号连接实现事件处理和用户交互

更新说明：
本文档由 `scripts/generate_docs.py` 脚本自动生成，确保内容与源代码同步。
如需修改，请更新源代码注释或脚本，不要直接编辑此文件。
============================================================================ -->
