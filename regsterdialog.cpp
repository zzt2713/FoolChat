#include "regsterdialog.h"
#include "ui_regsterdialog.h"
#include "httpmgr.h"
#include <QRegularExpression>
#include <QLineEdit>
#include "dbmanager.h"
#include "floatingtip.h"
#include "msgtip.h"

RegsterDialog::RegsterDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::RegsterDialog),_countdown(10)
{
    ui->setupUi(this);
    ui->errTip->setProperty("state","normal");
    ui->sure_btn->setDefault(true);
    ui->sure_btn->setAutoDefault(true);
    ui->varEdit->setCodeLength(4);
    ui->varEdit->setInputMode(ElaCaptcha::AlphaNumeric);

    repolish(ui->errTip);
    connect(HttpMgr::GetInstance().get(),&HttpMgr::sig_reg_mod_finish,
            this,&RegsterDialog::slot_reg_mod_finish);
    initHttpHandlers();
    SetPasswdEye();
    ui->getCode->setEnabled(false);
    ui->errTip->clear();
    connect(ui->userEdit,&QLineEdit::editingFinished,this,[this](){
        checkUserValid();
    });

    connect(ui->emailEdit, &QLineEdit::editingFinished, this, [this](){
        bool isValid = checkEmailValid();
        ui->getCode->setEnabled(isValid);
    });

    connect(ui->passEdit, &QLineEdit::editingFinished, this, [this](){
        checkPassValid();
    });

    connect(ui->passEdit_2, &QLineEdit::editingFinished, this, [this](){
        checkConfirmValid();
    });

    connect(ui->varEdit, &ElaCaptcha::codeCompleted, this, [this](const QString& code){
        checkVarifyValid();
    });

    _countdown_timer = new QTimer(this);
    connect(_countdown_timer, &QTimer::timeout, [this](){
        if(_countdown==0){
            _countdown_timer->stop();
            emit sigSwitchLogin();
            return;
        }
        _countdown--;
        auto str = QString("注册成功，%1s后返回登录").arg(_countdown);
        ui->tip_lb->setText(str);
    });

}

void RegsterDialog::AddTipErr(TipErr te, QString tips)
{
    _tip_errs[te] = tips;
    showTip(tips, false);
}

void RegsterDialog::DelTipErr(TipErr te)
{
    _tip_errs.remove(te);
    // if(_tip_errs.empty()){
    //     ui->errTip->clear();
    //     return;
    // }

    // showTip(_tip_errs.first(), false);
}

void RegsterDialog::ChangeTipPage()
{
    _countdown_timer->stop();
    ui->msg->setText(ui->userEdit->text());
    ui->msg2->setText(ui->passEdit->text());

    ui->stackedWidget->setCurrentWidget(ui->page_2);
    _countdown_timer->start(1000);
}

bool RegsterDialog::checkUserValid()
{
    if(ui->userEdit->text() == ""){
        AddTipErr(TipErr::TIP_USER_ERR, tr("用户名不能为空"));
        return false;
    }
    auto db = DBManager::GetInstance();

    if (db->isUsernameExist(ui->userEdit->text())) {
        AddTipErr(TipErr::TIP_USER_EXIST, db->getLastError());
        return false;
    }
    DelTipErr(TipErr::TIP_USER_EXIST);
    DelTipErr(TipErr::TIP_USER_ERR);
    return true;
}

bool RegsterDialog::checkEmailValid()
{
    auto email = ui->emailEdit->text();
    QRegularExpression regex(R"(^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,}$)");
    bool match = regex.match(email).hasMatch();
    if(!match){
        AddTipErr(TipErr::TIP_EMAIL_ERR, tr("邮箱地址不正确"));
        return false;
    }
    auto db = DBManager::GetInstance();

    if (db->isEmailExist(ui->emailEdit->text())) {
        AddTipErr(TipErr::TIP_EMAIL_EXIST, db->getLastError());
        return false;
    }

    DelTipErr(TipErr::TIP_EMAIL_EXIST);
    DelTipErr(TipErr::TIP_EMAIL_ERR);
    return true;
}

bool RegsterDialog::checkPassValid()
{
    auto pwd = ui->passEdit->text();
    if(pwd.length() < 6 || pwd.length()>15){
        //提示长度不准确
        AddTipErr(TipErr::TIP_PWD_ERR, tr("密码长度应为6~15"));
        return false;
    }

    // 检测是否包含非法字符
    QRegularExpression regExp("^[a-zA-Z0-9!@#$%^&*]{6,15}$");
    bool match = regExp.match(pwd).hasMatch();
    if(!match){
        AddTipErr(TipErr::TIP_PWD_ERR, tr("不能包含非法字符"));
        return false;;
    }

    DelTipErr(TipErr::TIP_PWD_ERR);
    return true;
}

bool RegsterDialog::checkVarifyValid()
{
    auto pass = ui->varEdit->getCode();
    if(pass.isEmpty()){
        AddTipErr(TipErr::TIP_VARIFY_ERR, tr("验证码不能为空"));
        return false;
    }

    DelTipErr(TipErr::TIP_VARIFY_ERR);
    return true;
}

void RegsterDialog::Clear()
{
    ui->userEdit->setText("");
    ui->emailEdit->setText("");
    ui->passEdit->setText("");
    ui->varEdit->clear();
    ui->passEdit_2->setText("");
}

bool RegsterDialog::checkConfirmValid()
{
    QString password = ui->passEdit->text();
    QString confirm = ui->passEdit_2->text();

    if (confirm.isEmpty()) {
        AddTipErr(TipErr::TIP_CONFIRM_ERR, tr("请再次输入密码"));
        return false;
    }

    if (password.isEmpty()) {
        AddTipErr(TipErr::TIP_CONFIRM_ERR, tr("请先输入密码"));
        return false;
    }

    if (password != confirm) {
        AddTipErr(TipErr::TIP_CONFIRM_ERR, tr("两次输入的密码不一致"));
        return false;
    }

    DelTipErr(TipErr::TIP_CONFIRM_ERR);
    return true;
}

RegsterDialog::~RegsterDialog()
{
    delete ui;
}

void RegsterDialog::SetPasswdEye()
{
    auto setupPasswordEye = [this](QLineEdit* edit) {
        QAction *eyeAction = edit->addAction(
            QIcon(":/icons/eye-close.png"),
            QLineEdit::TrailingPosition
            );

        edit->setEchoMode(QLineEdit::Password);
        eyeAction->setVisible(false);
        QObject::connect(edit, &QLineEdit::textChanged, [eyeAction](const QString &text) {
            eyeAction->setVisible(!text.isEmpty());
        });
        QObject::connect(eyeAction, &QAction::triggered, [edit, eyeAction]() {
            bool isPassword = (edit->echoMode() == QLineEdit::Password);
            if (isPassword) {
                edit->setEchoMode(QLineEdit::Normal);
                eyeAction->setIcon(QIcon(":/icons/eye-open.png"));
            } else {
                edit->setEchoMode(QLineEdit::Password);
                eyeAction->setIcon(QIcon(":/icons/eye-close.png"));
            }
        });
    };

    setupPasswordEye(ui->passEdit);
    setupPasswordEye(ui->passEdit_2);
}

void RegsterDialog::showTip(QString str, bool b_ok)
{
    ADDMSG(ElaMessageBarType::TopLeft,str,this,b_ok);
    // ShowTip(this,str,b_ok);
    // if(!b_ok){
    //     ERR(ElaMessageBarType::TopLeft,str,this);
    //     return;
    // }
    // SUCCESS(ElaMessageBarType::TopLeft,str,this);
    // if(b_ok){
    //     ui->errTip->setProperty("state","normal");
    // }else{
    //     ui->errTip->setProperty("state","err");
    // }

    // ui->errTip->setText(str);
    // repolish(ui->errTip);
}

void RegsterDialog::on_getCode_clicked()
{
    auto email = ui->emailEdit->text();

    QRegularExpression reg(R"(^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,}$)");
    bool m = reg.match(email).hasMatch();

    if(m){
        // 禁用验证码获取，防止重复点击
        ui->getCode->setEnabled(false);
        ui->getCode->setText("发送中...");

        QJsonObject obj;
        obj["email"] = email;
        HttpMgr::GetInstance()->PostHttpReq(QUrl(gate_url_prefix+"/get_varifycode"),
                                            obj, ReqId::ID_GET_VARIFY_CODE, Modules::REGISTERMOD);
    }else{
        // 理论上不会走到这里，因为按钮已被禁用
        showTip("邮箱地址不正确", false);
    }
}
void RegsterDialog::slot_reg_mod_finish(ReqId id, QString res, ErrorCodes err)
{
    // 先检查是否是获取验证码的请求
    if (id == ReqId::ID_GET_VARIFY_CODE) {
        // 如果网络请求失败
        if (err != ErrorCodes::SUCCESS) {
            // 恢复按钮状态
            ui->getCode->setEnabled(true);
            ui->getCode->setText("获取验证码");
            showTip("网络请求失败！", false);
            return;
        }

        // 解析JSON
        QJsonDocument jsondc = QJsonDocument::fromJson(res.toUtf8());
        if(jsondc.isNull() || !jsondc.isObject()){
            // JSON解析失败，恢复按钮状态
            ui->getCode->setEnabled(true);
            ui->getCode->setText("获取验证码");
            showTip("json解析失败", false);
            return;
        }

        // 调用对应的处理器
        _handlers[id](jsondc.object());
        return;
    }

    // 处理其他请求类型的网络错误
    if(err != ErrorCodes::SUCCESS){
        showTip("网络请求失败！", false);
        return;
    }

    // 解析其他请求的JSON
    QJsonDocument jsondc = QJsonDocument::fromJson(res.toUtf8());
    if(jsondc.isNull() || !jsondc.isObject()){
        showTip("json解析失败", false);
        return;
    }

    // 调用对应的处理器
    _handlers[id](jsondc.object());
}


void RegsterDialog::initHttpHandlers()
{
    // 获取验证码回包逻辑
    _handlers.insert(ReqId::ID_GET_VARIFY_CODE,[this](const QJsonObject& jsonObj){
        int error = jsonObj["error"].toInt();
        if(error != ErrorCodes::SUCCESS){
            showTip("参数错误！",false);
            return ;
        }

        auto email = jsonObj["email"].toString();
        showTip("验证码已发送至邮箱，请注意查收！",true);
        qDebug() << "email is " << email << Qt::endl;
    });

    _handlers.insert(ReqId::ID_REG_USER, [this](QJsonObject jsonObj){
        int error = jsonObj["error"].toInt();
        if(error != ErrorCodes::SUCCESS){
            showTip(tr("用户或邮箱已存在！"),false);
            return;
        }
        auto email = jsonObj["email"].toString();
        showTip(tr("用户注册成功！"), true);
        ChangeTipPage();
    });
}

void RegsterDialog::on_sure_btn_clicked()
{
    if(ui->userEdit->text() == ""){
        showTip(tr("用户名不能为空"), false);
        return;
    }

    if(ui->emailEdit->text() == ""){
        showTip(tr("邮箱不能为空"), false);
        return;
    }

    if(ui->passEdit->text() == ""){
        showTip(tr("密码不能为空"), false);
        return;
    }

    if(ui->passEdit_2->text() == ""){
        showTip(tr("确认密码不能为空"), false);
        return;
    }

    if(ui->passEdit_2->text() != ui->passEdit->text()){
        showTip(tr("密码和确认密码不匹配"), false);
        return;
    }

    if(ui->varEdit->getCode() == ""){
        showTip(tr("验证码不能为空"), false);
        return;
    }
    QJsonObject json_obj;
    json_obj["user"] = ui->userEdit->text();
    json_obj["email"] = ui->emailEdit->text();
    json_obj["passwd"] = hashString(ui->passEdit->text());
    json_obj["confirm"] = hashString(ui->passEdit_2->text());
    json_obj["varifycode"] = ui->varEdit->getCode();
    HttpMgr::GetInstance()->PostHttpReq(QUrl(gate_url_prefix+"/user_register"),
                                        json_obj, ReqId::ID_REG_USER,Modules::REGISTERMOD);
}


void RegsterDialog::on_returnBtn_clicked()
{
    _countdown_timer->stop();
    emit sigSwitchLogin();
}


void RegsterDialog::on_cencel_btn_clicked()
{
    _countdown_timer->stop();
    emit sigSwitchLogin();
}

