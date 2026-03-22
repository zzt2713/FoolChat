#include "musicpage.h"

#include <QPixmap>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QStandardItemModel>
#include <QHeaderView>
#include "musicpage.h"
#include <QFileDialog>
#include <QFileInfo>
#include <QDir>
#include <QDebug>
#include <QMediaPlayer>
#include <QUrl>
// Ela组件
#include "ElaPromotionView.h"
#include "ElaPromotionCard.h"
#include "ElaTableView.h"
#include "ElaText.h"
#include "ElaSlider.h"
#include "ElaIconButton.h"
#include "ElaCheckBox.h"  // 添加到头部

MusicPage::MusicPage(QWidget *parent) : Page_Base(parent)
{
    setupUI();
    initDatabase();
    initPlayer(); // 初始化播放器
    loadSongsFromDatabase();
}

// 新增：初始化播放器
void MusicPage::initPlayer()
{
    m_player = new QMediaPlayer(this);
    m_audioOutput = new QAudioOutput(this);
    m_player->setAudioOutput(m_audioOutput);
    m_audioOutput->setVolume(0.5); // 默认音量 50%

    // 连接信号
    connect(m_player, &QMediaPlayer::positionChanged, this, &MusicPage::updatePosition);
    connect(m_player, &QMediaPlayer::durationChanged, this, &MusicPage::updateDuration);

    // 自动播放下一首
    connect(m_player, &QMediaPlayer::mediaStatusChanged, this, [this](QMediaPlayer::MediaStatus status){
        if(status == QMediaPlayer::EndOfMedia){
            playNext();
        }
    });
}

MusicPage::~MusicPage()
{
}

void MusicPage::setupUI()
{
    setWindowTitle("音乐盒");
    QWidget* content = new QWidget();
    content->setWindowTitle("音乐盒");

    QVBoxLayout* mainLayout = new QVBoxLayout(content);
    mainLayout->setContentsMargins(20, 20, 20, 20);
    mainLayout->setSpacing(15);

    // ========== 1. 轮播图 ==========
    ElaPromotionView* _promotionView = new ElaPromotionView(this);
    _promotionView->setFixedHeight(330);

    ElaPromotionCard* exampleCard1 = new ElaPromotionCard(this);
    exampleCard1->setCardPixmap(QPixmap(":/images/banner_1.jpg"));

    ElaPromotionCard* exampleCard2 = new ElaPromotionCard(this);
    exampleCard2->setCardPixmap(QPixmap(":/images/banner_2.jpg"));

    ElaPromotionCard* exampleCard3 = new ElaPromotionCard(this);
    exampleCard3->setCardPixmap(QPixmap(":/images/banner_3.jpg"));

    ElaPromotionCard* exampleCard4 = new ElaPromotionCard(this);
    exampleCard4->setCardPixmap(QPixmap(":/images/banner_4.jpg"));

    _promotionView->appendPromotionCard(exampleCard1);
    _promotionView->appendPromotionCard(exampleCard2);
    _promotionView->appendPromotionCard(exampleCard3);
    _promotionView->appendPromotionCard(exampleCard4);
    _promotionView->setIsAutoScroll(true);

    mainLayout->addWidget(_promotionView);

    setupSongList(mainLayout);

    setupPlayerBar(mainLayout);

    // 添加到基础页面中心
    addCentralWidget(content);
}

void MusicPage::setupSongList(QVBoxLayout* mainLayout)
{
    m_pSongTable = new ElaTableView(this);

    m_pTableModel = new QStandardItemModel(this);
    m_pTableModel->setHorizontalHeaderLabels(QStringList() << "选择" << "歌曲名称" << "歌手" << "专辑" << "时长");
    m_pSongTable->setModel(m_pTableModel);

    m_pSongTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    m_pSongTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    m_pSongTable->setAlternatingRowColors(true);
    m_pSongTable->verticalHeader()->setVisible(false);
    m_pSongTable->setShowGrid(false);

    m_pSongTable->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Fixed);
    m_pSongTable->setColumnWidth(0, 60);
    m_pSongTable->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);
    m_pSongTable->horizontalHeader()->setSectionResizeMode(2, QHeaderView::Interactive);
    m_pSongTable->horizontalHeader()->setSectionResizeMode(3, QHeaderView::Stretch);
    m_pSongTable->horizontalHeader()->setSectionResizeMode(4, QHeaderView::Fixed);
    m_pSongTable->setColumnWidth(4, 80);

    connect(m_pSongTable, &ElaTableView::doubleClicked, this, [this](const QModelIndex &index){
        playMusic(index.row());
    });

    mainLayout->addWidget(m_pSongTable, 1);

    // 按钮区域保持不变
    QWidget* buttonWidget = new QWidget(this);
    QHBoxLayout* btnLayout = new QHBoxLayout(buttonWidget);
    btnLayout->setContentsMargins(0, 10, 0, 10);
    btnLayout->setSpacing(15);

    ElaPushButton* btnAdd = new ElaPushButton("添加音乐", this);
    btnAdd->setFixedSize(120, 35);
    connect(btnAdd, &ElaPushButton::clicked, this, &MusicPage::onAddSong);

    ElaPushButton* btnDelete = new ElaPushButton("删除选中", this);
    btnDelete->setFixedSize(120, 35);
    connect(btnDelete, &ElaPushButton::clicked, this, &MusicPage::onDeleteSong);

    btnLayout->addWidget(btnAdd);
    btnLayout->addWidget(btnDelete);
    btnLayout->addStretch();

    mainLayout->addWidget(buttonWidget);
}

void MusicPage::onAddSong()
{
    QStringList fileNames = QFileDialog::getOpenFileNames(this, "选择音乐", QDir::homePath(), "音频文件 (*.mp3 *.flac *.wav *.m4a)");
    if (fileNames.isEmpty()) return;

    QSqlDatabase db = QSqlDatabase::database();
    if (!db.isOpen()) return;

    QSqlQuery query;
    db.transaction();

    for (const QString &filePath : fileNames) {
        QFileInfo fileInfo(filePath);
        QString title = fileInfo.baseName();
        QString artist = "未知歌手";
        QString album = "本地音乐";
        QString duration = "--:--";

        query.prepare("INSERT INTO songs (file_path, title, artist, album, duration) VALUES (:path, :title, :artist, :album, :duration)");
        query.bindValue(":path", filePath);
        query.bindValue(":title", title);
        query.bindValue(":artist", artist);
        query.bindValue(":album", album);
        query.bindValue(":duration", duration);

        if (query.exec()) {
            int newId = query.lastInsertId().toInt();
            addRowToTable(newId, title, artist, album, duration, filePath);
        }
    }
    db.commit();
}

void MusicPage::playMusic(int row)
{
    if (row < 0 || row >= m_pTableModel->rowCount()) return;

    // 1. 获取路径 (从第0列的 UserRole+1 取出)
    QString filePath = m_pTableModel->item(row, 0)->data(Qt::UserRole + 1).toString();

    // 2. 获取显示信息
    QString title = m_pTableModel->item(row, 1)->text();
    QString artist = m_pTableModel->item(row, 2)->text();

    // 3. 设置播放源并播放
    m_player->setSource(QUrl::fromLocalFile(filePath));
    m_player->play();

    // 4. 更新界面状态
    m_currentRow = row;
    m_pCurrentSongLabel->setText("正在播放：" + title);
    m_pCurrentArtistLabel->setText("歌手：" + artist);
    m_pPlayBtn->setAwesome(ElaIconType::Pause); // 切换图标为暂停
    m_pPlayBtn->update();
}

void MusicPage::togglePlayState()
{
    if (m_player->playbackState() == QMediaPlayer::PlayingState) {
        m_player->pause();
        m_pPlayBtn->setAwesome(ElaIconType::Play);
        m_pPlayBtn->update();
    } else {
        if (m_player->source().isEmpty() && m_pTableModel->rowCount() > 0) {
            playMusic(0);
        } else {
            m_player->play();
            m_pPlayBtn->setAwesome(ElaIconType::Pause);
            m_pPlayBtn->update();
        }
    }
}

void MusicPage::playNext()
{
    int nextRow = m_currentRow + 1;
    if (nextRow >= m_pTableModel->rowCount()) nextRow = 0; // 循环播放
    playMusic(nextRow);
}

void MusicPage::playPrev()
{
    int prevRow = m_currentRow - 1;
    if (prevRow < 0) prevRow = m_pTableModel->rowCount() - 1; // 循环播放
    playMusic(prevRow);
}

void MusicPage::updateDuration(qint64 duration)
{
    // 设置进度条最大值 (duration 是毫秒)
    m_pProgressSlider->setRange(0, duration);
    // 这里也可以更新界面上的总时长文字
}

void MusicPage::updatePosition(qint64 position)
{
    if (!m_pProgressSlider->isSliderDown()) {
        m_pProgressSlider->setValue(position);
    }
}

// 辅助：格式化时间
QString MusicPage::formatTime(qint64 ms)
{
    int seconds = (ms / 1000) % 60;
    int minutes = (ms / 60000) % 60;
    return QString("%1:%2").arg(minutes, 2, 10, QChar('0')).arg(seconds, 2, 10, QChar('0'));
}

void MusicPage::onDeleteSong()
{
    // 从后往前遍历
    for (int row = m_pTableModel->rowCount() - 1; row >= 0; --row) {
        QModelIndex index = m_pTableModel->index(row, 0);
        QWidget* container = m_pSongTable->indexWidget(index);
        ElaCheckBox* checkBox = container ? container->findChild<ElaCheckBox*>() : nullptr;

        if (checkBox && checkBox->isChecked()) {
            // 1. 获取隐藏的数据库 ID
            int dbId = m_pTableModel->item(row, 0)->data(Qt::UserRole).toInt();

            // 2. 从数据库删除
            QSqlQuery query;
            query.prepare("DELETE FROM songs WHERE id = :id");
            query.bindValue(":id", dbId);
            query.exec();

            // 3. 从 UI 删除
            m_pTableModel->removeRow(row);
        }
    }
}

void MusicPage::setupPlayerBar(QVBoxLayout* mainLayout)
{
    // 底部容器
    QWidget* playerBar = new QWidget(this);
    playerBar->setFixedHeight(90);
    playerBar->setStyleSheet("background-color: rgba(240, 240, 240, 0.8); border-radius: 10px;");

    QHBoxLayout* hLayout = new QHBoxLayout(playerBar);
    hLayout->setContentsMargins(20, 10, 20, 10);
    hLayout->setSpacing(15);

    // --- 左侧：播放的音乐信息（去掉封面） ---
    QWidget* infoWidget = new QWidget(this);
    QVBoxLayout* infoLayout = new QVBoxLayout(infoWidget);
    infoLayout->setContentsMargins(0, 5, 0, 5);
    infoLayout->setSpacing(4);

    m_pCurrentSongLabel = new ElaText("正在播放：示例歌曲 1", this);
    m_pCurrentSongLabel->setTextPixelSize(14);
    m_pCurrentSongLabel->setStyleSheet("font-weight: bold; color: #333;");

    m_pCurrentArtistLabel = new ElaText("歌手：未知歌手", this);
    m_pCurrentArtistLabel->setTextPixelSize(12);
    m_pCurrentArtistLabel->setStyleSheet("color: #666;");

    infoLayout->addWidget(m_pCurrentSongLabel);
    infoLayout->addWidget(m_pCurrentArtistLabel);
    infoWidget->setMaximumWidth(300);

    // --- 中间：进度条 ---
    m_pProgressSlider = new ElaSlider(Qt::Horizontal, this);
    m_pProgressSlider->setRange(0, 100);
    m_pProgressSlider->setValue(35);

    // --- 右侧：播放按钮 ---
    QWidget* controlsWidget = new QWidget(this);
    QHBoxLayout* ctrlLayout = new QHBoxLayout(controlsWidget);
    ctrlLayout->setContentsMargins(0, 0, 0, 0);
    ctrlLayout->setSpacing(20);

    ElaIconButton* btnPrev = new ElaIconButton(ElaIconType::ChevronLeft, 16, this);
    btnPrev->setFixedSize(40, 40);
    connect(btnPrev, &ElaIconButton::clicked, this, &MusicPage::playPrev);

    m_pPlayBtn = new ElaIconButton(ElaIconType::Play, 20, this);
    m_pPlayBtn->setFixedSize(50, 50);
    m_pPlayBtn->setBorderRadius(25);
    m_pPlayBtn->setStyleSheet("background-color: #ff6b6b;");
    connect(m_pPlayBtn, &ElaIconButton::clicked, this, &MusicPage::togglePlayState);

    ElaIconButton* btnNext = new ElaIconButton(ElaIconType::ChevronRight, 16, this);
    btnNext->setFixedSize(40, 40);
    connect(btnNext, &ElaIconButton::clicked, this, &MusicPage::playNext);

    // 1. 音量图标按钮
    ElaIconButton* btnVolume = new ElaIconButton(ElaIconType::VolumeHigh, 14, this);
    btnVolume->setFixedSize(30, 30);

    // 2. 【新增】音量滑块
    m_pVolumeSlider = new ElaSlider(Qt::Horizontal, this);
    m_pVolumeSlider->setRange(0, 100);     // 范围 0-100
    m_pVolumeSlider->setFixedWidth(80);    // 固定宽度，短一点，不要太长
    m_pVolumeSlider->setValue(50);         // 默认音量 50

    // 3. 【逻辑】滑块拖动 -> 改变音量
    connect(m_pVolumeSlider, &ElaSlider::valueChanged, this, [this, btnVolume](int value){
        // 转换：0-100 -> 0.0-1.0
        qreal floatVol = value / 100.0;
        m_audioOutput->setVolume(floatVol);

        // 交互优化：根据音量大小改变图标
        if (value == 0) {
            btnVolume->setAwesome(ElaIconType::VolumeXmark); // 静音图标
        } else if (value < 50) {
            btnVolume->setAwesome(ElaIconType::VolumeLow);   // 低音量图标
        } else {
            btnVolume->setAwesome(ElaIconType::VolumeHigh);  // 高音量图标
        }
    });

    // 4. 【逻辑】点击图标 -> 静音/恢复 (并同步滑块)
    connect(btnVolume, &ElaIconButton::clicked, this, [this, btnVolume](){
        if (m_pVolumeSlider->value() > 0) {
            // 当前有声音 -> 设为静音 (滑块归零)
            m_pVolumeSlider->setValue(0);
        } else {
            // 当前是静音 -> 恢复到 50 (或者你可以用变量存一下之前的音量)
            m_pVolumeSlider->setValue(50);
        }
        // 注意：setValue 会触发上面的 valueChanged 信号，
        // 所以不需要在这里再写 m_audioOutput->setVolume
    });

    // 5. 添加到布局
    ctrlLayout->addWidget(btnPrev);
    ctrlLayout->addWidget(m_pPlayBtn);
    ctrlLayout->addWidget(btnNext);

    ctrlLayout->addSpacing(20); // 稍微隔开一点

    // 把音量图标和滑块加进去
    ctrlLayout->addWidget(btnVolume);
    ctrlLayout->addWidget(m_pVolumeSlider);
    connect(m_pProgressSlider, &ElaSlider::sliderReleased, this, [this](){
        m_player->setPosition(m_pProgressSlider->value());
    });

    connect(m_pProgressSlider, &ElaSlider::sliderMoved, this, [this](int position){
        m_player->setPosition(position);
    });

    hLayout->addWidget(infoWidget, 1);
    hLayout->addWidget(m_pProgressSlider, 1);
    hLayout->addWidget(controlsWidget, 0);

    mainLayout->addWidget(playerBar);
}

void MusicPage::addRowToTable(int id, QString title, QString artist, QString album, QString duration, QString filePath)
{
    QList<QStandardItem*> rowItems;

    QStandardItem* checkItem = new QStandardItem();
    checkItem->setData(id, Qt::UserRole);
    checkItem->setData(filePath, Qt::UserRole + 1);
    rowItems << checkItem;

    QStandardItem* songItem = new QStandardItem(title);
    songItem->setTextAlignment(Qt::AlignCenter);
    QStandardItem* artistItem = new QStandardItem(artist);
    artistItem->setTextAlignment(Qt::AlignCenter);
    QStandardItem* albumItem = new QStandardItem(album);
    albumItem->setTextAlignment(Qt::AlignCenter);
    QStandardItem* durationItem = new QStandardItem(duration);
    durationItem->setTextAlignment(Qt::AlignCenter);

    rowItems << songItem << artistItem << albumItem << durationItem;
    m_pTableModel->appendRow(rowItems);

    int newRow = m_pTableModel->rowCount() - 1;
    QWidget* checkBoxContainer = new QWidget(this);
    QHBoxLayout* checkBoxLayout = new QHBoxLayout(checkBoxContainer);
    checkBoxLayout->setContentsMargins(0, 0, 0, 0);
    checkBoxLayout->setAlignment(Qt::AlignCenter);
    ElaCheckBox* checkBox = new ElaCheckBox(this);
    checkBoxLayout->addWidget(checkBox);
    m_pSongTable->setIndexWidget(m_pTableModel->index(newRow, 0), checkBoxContainer);
}

void MusicPage::loadSongsFromDatabase()
{
    QSqlQuery query("SELECT id, title, artist, album, duration, file_path FROM songs");
    while (query.next()) {
        int id = query.value(0).toInt();
        QString title = query.value(1).toString();
        QString artist = query.value(2).toString();
        QString album = query.value(3).toString();
        QString duration = query.value(4).toString();
        QString path = query.value(5).toString(); // 读取路径

        addRowToTable(id, title, artist, album, duration, path);
    }
}


void MusicPage::initDatabase()
{
    // 检查是否已经存在连接，避免重复添加
    if (QSqlDatabase::contains("qt_sql_default_connection")) {
        return;
    }

    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("music_player.db"); // 数据库文件名

    if (!db.open()) {
        qDebug() << "无法打开数据库:" << db.lastError().text();
        return;
    }

    // 创建表：包含 ID, 路径, 标题, 歌手, 专辑, 时长
    QSqlQuery query;
    QString createTable = R"(
        CREATE TABLE IF NOT EXISTS songs (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            file_path TEXT NOT NULL,
            title TEXT,
            artist TEXT,
            album TEXT,
            duration TEXT
        )
    )";

    if (!query.exec(createTable)) {
        qDebug() << "创建表失败:" << query.lastError().text();
    }
}
