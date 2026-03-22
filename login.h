#ifndef LOGIN_H
#define LOGIN_H

#include "global.h"
#include <QMovie>
/******************************************************************************
*
* @file       login.h
* @brief      登录界面
*
* @author     Fool
* @date       2026/02/03
* @history
*****************************************************************************/
namespace Ui {
class login;
}

class login : public QDialog
{
    Q_OBJECT

public:
    explicit login(QWidget *parent = nullptr);
    ~login();
    void Clear();
private:
    Ui::login *ui;
    QMap<ReqId,std::function<void(const QJsonObject&)>> _handlers;
    QMap<TipErr, QString> _tip_errs;

    void SetPasswdEye();
    void initHead(QString path);
    void ininHttpHandlers();

    void showTip(QString str, bool b_ok);
    void AddTipErr(TipErr te, QString tips);
    void DelTipErr(TipErr te);

    bool enableBtn(bool enabled);
    bool checkPassValid();
    bool checkUserValid();
    bool checkUserIsexist();

    int _uid;
    QString _token;
    QMovie *m_loadingMovie;

    QTimer *m_btnTimer;
    int m_dotCount;

public slots:
    void slot_forget_pwd();

private slots:
    void on_loginBtn_clicked();
    void slot_login_mod_finish(ReqId id,QString res,ErrorCodes err);
    void slot_login_failed(int);
    void slot_tcp_con_failed(bool bsuccess);

signals:
    void switchRegister();
    void switchReset();
    void sig_connect_tcp(ServerInfo);

};

#endif // LOGIN_H
