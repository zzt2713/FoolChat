#include "login.h"
#include "ui_login.h"
#include <QPixmap>
#include <QPainter>
#include <QPainterPath>
#include "dbmanager.h"
#include "msgtip.h"
#include "httpmgr.h"
#include <QUrl>
#include "tcpmgr.h"
#include "floatingtip.h"
#include "ranimg.h"
#include "ElaLineEdit.h"

login::login(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::login)
{
    ui->setupUi(this);
    ui->forget_label->SetState("normal","hover","","selected","selected_hover","");

    // initHead(":/logo/logo.png");
    ininHttpHandlers();
    SetPasswdEye();

    ui->loginBtn->setDefault(true);
    ui->loginBtn->setAutoDefault(true);

    m_loadingMovie = new QMovie(":/icons/loadings.gif");
    m_loadingMovie->setScaledSize(QSize(200, 200));
    ui->lbl_loading_img->setMovie(m_loadingMovie);

    ui->stackedWidget->setCurrentIndex(0);

    m_dotCount = 0;
    m_btnTimer = new QTimer(this);
    connect(m_btnTimer, &QTimer::timeout, this, [this]() {
        m_dotCount = (m_dotCount + 1) % 4;
        QString text = "登录中";
        for (int i = 0; i < m_dotCount; ++i) {
            text += ".";
        }
        ui->loginBtn->setText(text);
    });

    connect(ui->forget_label, &ClickedLabel::clicked, this, &login::slot_forget_pwd);
    connect(ui->regBtn,&QPushButton::clicked,this,&login::switchRegister);
    // 回包信号连接
    connect(HttpMgr::GetInstance().get(),&HttpMgr::sig_login_mod_finish,this,&login::slot_login_mod_finish);
    // 连接tcp
    connect(this,&login::sig_connect_tcp,TcpMgr::GetInstance().get(),&TcpMgr::slot_tcp_connect);
    //连接tcp管理者发出的连接成功信号
    connect(TcpMgr::GetInstance().get(), &TcpMgr::sig_con_success, this, &login::slot_tcp_con_failed);
    //连接tcp管理者发出的登陆失败信号
    connect(TcpMgr::GetInstance().get(), &TcpMgr::sig_login_failed, this, &login::slot_login_failed);
}

login::~login()
{
    delete ui;
}

void login::SetPasswdEye()
{
    QAction *eyeAction = ui->passEdit->addAction(
        QIcon(":/icons/eye-close.png"),
        QLineEdit::TrailingPosition
        );

    ui->passEdit->setEchoMode(QLineEdit::Password);
    eyeAction->setVisible(false);

    connect(ui->passEdit, &QLineEdit::textChanged, [=](const QString &text) {
        eyeAction->setVisible(!text.isEmpty());
    });

    connect(eyeAction, &QAction::triggered, [=]() {
        bool isPassword = (ui->passEdit->echoMode() == QLineEdit::Password);

        if (isPassword) {
            ui->passEdit->setEchoMode(QLineEdit::Normal);
            eyeAction->setIcon(QIcon(":/icons/eye-open.png")); // 换成睁眼图标
        } else {
            ui->passEdit->setEchoMode(QLineEdit::Password);
            eyeAction->setIcon(QIcon(":/icons/eye-close.png")); // 换成闭眼图标
        }
    });
}

void login::initHead(QString path)
{
    QPixmap originalPixmap(path);
    originalPixmap = originalPixmap.scaled(ui->head_label->size(),
                                           Qt::KeepAspectRatio, Qt::SmoothTransformation);

    QPixmap roundedPixmap(originalPixmap.size());
    roundedPixmap.fill(Qt::transparent);

    QPainter painter(&roundedPixmap);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setRenderHint(QPainter::SmoothPixmapTransform);

    // 设置图片圆角
    QPainterPath paths;
    paths.addRoundedRect(0, 0, originalPixmap.width(), originalPixmap.height(), 10, 10);
    painter.setClipPath(paths);
    painter.drawPixmap(0, 0, originalPixmap);

    ui->head_label->setPixmap(roundedPixmap);
}

void login::ininHttpHandlers()
{
    _handlers.insert(ReqId::ID_LOGIN_USER, [this](QJsonObject jsonObj){
        int error = jsonObj["error"].toInt();
        if(error != ErrorCodes::SUCCESS){
            showTip(tr("用户名或密码错误！"),false);
            enableBtn(true);
            return;
        }

        // 获取登录信息
        NAME = jsonObj["user"].toString();
        EMAIL = jsonObj["email"].toString();

        //发送信号通知 tcpMgr发送长链接
        ServerInfo si;
        si.Uid = jsonObj["uid"].toInt();
        si.Host = jsonObj["host"].toString();
        si.Port = jsonObj["port"].toString();
        si.Token = jsonObj["token"].toString();
        qDebug() << "=== StatusServer Returned ===";
        qDebug() << "Host:" << si.Host;
        qDebug() << "Port:" << si.Port;
        qDebug() << "UID:" << si.Uid;
        _uid = si.Uid;
        _token = si.Token;

        emit sig_connect_tcp(si);
    });
}

void login::slot_forget_pwd()
{
    emit switchReset();
}

void login::on_loginBtn_clicked()
{
    if(!checkUserValid()){
        return;
    }
    if(!checkPassValid()){
        return;
    }
    if(!checkUserIsexist()){
        return;
    }

    enableBtn(false);

    m_dotCount = 0;
    ui->loginBtn->setText("登录中");
    m_btnTimer->start(400);

    auto user = ui->userEdit->text();
    auto pwd = hashString(ui->passEdit->text());
    QJsonObject json_obj;
    json_obj["user"] = user;
    json_obj["passwd"] = pwd;
    HttpMgr::GetInstance()->PostHttpReq(QUrl(gate_url_prefix + "/user_login"),
                                        json_obj,ReqId::ID_LOGIN_USER,Modules::LOGINMOD);
}

void login::slot_login_mod_finish(ReqId id, QString res, ErrorCodes err)
{
    if(err != ErrorCodes::SUCCESS){
        showTip("网络请求错误！", false);
        enableBtn(true);
        return;
    }

    QJsonDocument jsonDoc = QJsonDocument::fromJson(res.toUtf8());

    if(jsonDoc.isNull() || !jsonDoc.isObject()){
        showTip("json解析错误", false);
        enableBtn(true);
        return;
    }

    _handlers[id](jsonDoc.object());
}
void login::slot_login_failed(int err)
{
    QString result = QString("登录失败，err is %1").arg(err);
    showTip(result,false);
    enableBtn(true);
    ui->stackedWidget->setCurrentWidget(ui->page_login); // 切回输入界面
    m_loadingMovie->stop();
}

void login::slot_tcp_con_failed(bool bsuccess)
{
    if(bsuccess){
        ADDMSG(ElaMessageBarType::TopLeft,"连接成功，正在跳转....",this,bsuccess,3000);
        ui->stackedWidget->setCurrentWidget(ui->page_loading);
        m_loadingMovie->start();

        // 延迟 2 秒发送登录请求，让动画至少播放 2 秒
        QTimer::singleShot(2000, [this, uid = _uid, token = _token]() {
            QJsonObject obj;
            obj["uid"] = uid;
            obj["token"] = token;
            QJsonDocument doc(obj);

            QByteArray jsonStr = doc.toJson(QJsonDocument::Indented);
            emit TcpMgr::GetInstance()->sig_send_data(ReqId::ID_CHAT_LOGIN,jsonStr);
        });
    }else{
        showTip("网络异常，无法连接到聊天服务器", false);
        enableBtn(true);

        ui->stackedWidget->setCurrentWidget(ui->page_login);
        m_loadingMovie->stop();
    }
}

void login::showTip(QString str, bool b_ok)
{
    ADDMSG(ElaMessageBarType::TopLeft,str,this,b_ok);
    // MSGTIP(ElaMessageBarType::TopLeft,str,this,b_ok);
    // ShowTip(this, str, b_ok);
    // if(!b_ok){
    //     ERR(ElaMessageBarType::TopLeft,str,this);
    //     return;
    // }
    // SUCCESS(ElaMessageBarType::TopLeft,str,this);

    /*
    if(b_ok){
        ui->errTip->setProperty("state","normal");
    }else{
        ui->errTip->setProperty("state","err");
    }
    ui->errTip->setText(str);
    repolish(ui->errTip);
    */
}

void login::AddTipErr(TipErr te, QString tips)
{
    _tip_errs[te] = tips;
    showTip(tips, false);
}

void login::DelTipErr(TipErr te)
{
    _tip_errs.remove(te);
    // if(_tip_errs.empty()){
    //     ui->errTip->clear();
    //     return;
    // }

    // showTip(_tip_errs.first(), false);
}

void login::Clear()
{
    ui->userEdit->setText("");
    ui->passEdit->setText("");
}

bool login::enableBtn(bool enabled)
{
    ui->loginBtn->setEnabled(enabled);
    ui->regBtn->setEnabled(enabled);

    if (enabled) {
        if (m_btnTimer && m_btnTimer->isActive()) {
            m_btnTimer->stop();
        }
        ui->loginBtn->setText("登 录"); // 恢复原来的文字
    }

    return true;
}

bool login::checkUserValid()
{
    if(ui->userEdit->text() == ""){
        AddTipErr(TipErr::TIP_USER_ERR, tr("用户名不能为空"));
        return false;
    }

    DelTipErr(TipErr::TIP_USER_ERR);
    return true;
}

bool login::checkUserIsexist()
{
    auto db = DBManager::GetInstance();
    if(!(db->isUsernameExist(ui->userEdit->text()))){
        AddTipErr(TipErr::TIP_USER_NOT_EXIST, tr("用户名不存在"));
        qDebug() << "用户名不存在";
        return false;
    }

    DelTipErr(TipErr::TIP_USER_NOT_EXIST);
    return true;
}

bool login::checkPassValid()
{
    auto pass = ui->passEdit->text();

    if(pass.length() < 6 || pass.length()>15){
        //提示长度不准确
        AddTipErr(TipErr::TIP_PWD_ERR, tr("密码长度应为6~15"));
        return false;
    }

    QRegularExpression regExp("^[a-zA-Z0-9!@#$%^&*.]{6,15}$");
    bool match = regExp.match(pass).hasMatch();
    if(!match){
        //提示字符非法
        AddTipErr(TipErr::TIP_PWD_ERR, tr("不能包含非法字符"));
        return false;;
    }

    DelTipErr(TipErr::TIP_PWD_ERR);
    return true;
}
