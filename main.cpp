#include "mainwindow.h"
#include "ElaApplication.h"
#include "global.h"
#include <QSqlDatabase>
#include "tcpmgr.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // ELA初始化
    eApp->init();

    // 加载QSS样式
    QFile qss(":/style/stylesheet.qss");
    if(qss.open(QFile::ReadOnly)){
        QString style = QLatin1StringView(qss.readAll());
        a.setStyleSheet(style);
        qss.close();
    }else{
        LOG_ERROR("Err is main qss.open(QFile::ReadOnly).");
    }

    // 加载配置文件
    QString fileName = "config.ini";
    QString app_path = QCoreApplication::applicationDirPath();
    QString config_path = QDir::toNativeSeparators(app_path + QDir::separator() + fileName);

    QSettings settings(config_path,QSettings::IniFormat);
    QString gate_host = settings.value("GateServer/host").toString();
    QString gate_port = settings.value("GateServer/port").toString();
    gate_url_prefix = "http://" + gate_host + ":" + gate_port;

    MainWindow w;
    emit TcpMgr::GetInstance()->sig_switch_chatdlg();
    // w.show();
    return a.exec();
}
