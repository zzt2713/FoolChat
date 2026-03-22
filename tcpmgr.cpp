#include "tcpmgr.h"
#include <QAbstractSocket>
#include <QJsonDocument>
#include <QByteArray>
#include "usermgr.h"
TcpMgr::~TcpMgr()
{

}

TcpMgr::TcpMgr():_host(""),_port(0),_b_recv_pending(false),_message_id(0),_message_len(0) {
    QObject::connect(&_socket,&QTcpSocket::connected,[&](){
        // 成功建立连接
        emit sig_con_success(true);
    });
    QObject::connect(&_socket, &QTcpSocket::readyRead, [&]() {
        _buffer.append(_socket.readAll());
        QDataStream stream(&_buffer, QIODevice::ReadOnly);
        stream.setVersion(QDataStream::Qt_6_0);
        forever {
            if(!_b_recv_pending){
                if (_buffer.size() < static_cast<int>(sizeof(quint16) * 2)) {
                    return;
                }
                stream >> _message_id >> _message_len;
                _buffer = _buffer.mid(sizeof(quint16) * 2);
                qDebug() << "Message ID:" << _message_id << ", Length:" << _message_len;
            }
            if(_buffer.size() < _message_len){
                _b_recv_pending = true;
                return;
            }
            _b_recv_pending = false;
            // 读取消息体
            QByteArray messageBody = _buffer.mid(0, _message_len);
            qDebug() << "receive body msg is " << messageBody ;
            _buffer = _buffer.mid(_message_len);
            handleMsg(ReqId(_message_id),_message_len, messageBody);
        }
    });
    QObject::connect(&_socket, &QTcpSocket::errorOccurred,
        [&](QAbstractSocket::SocketError socketError) {
        Q_UNUSED(socketError);
        qDebug() << "Error:" << _socket.errorString();
    });
    QObject::connect(&_socket,&QTcpSocket::disconnected,[&](){
        qDebug() << "Disconnected from server" << Qt::endl;
    });
    QObject::connect(this,&TcpMgr::sig_send_data,this,&TcpMgr::slot_send_data);
    initHandlers();
}

void TcpMgr::initHandlers()
{
    _handlers.insert(ID_CHAT_LOGIN_RSP,[this](ReqId id, int len, QByteArray data){
        Q_UNUSED(len);
        qDebug()<< "handle id is "<< id ;
        QJsonDocument jsonDoc = QJsonDocument::fromJson(data);
        if(jsonDoc.isNull()){
            return;
        }

        QJsonObject jsonObj = jsonDoc.object();
        if(!jsonObj.contains("error")){
            int err = ErrorCodes::ERR_JSON;
            emit sig_login_failed(err);
            return ;
        }

        int err = jsonObj["error"].toInt();
        if(err != ErrorCodes::SUCCESS){
            emit sig_login_failed(err);
            return ;
        }

        UserMgr::GetInstance()->SetUid(jsonObj["uid"].toInt());
        UserMgr::GetInstance()->SetName(jsonObj["name"].toString());
        UserMgr::GetInstance()->SetToken(jsonObj["token"].toString());

        emit sig_switch_chatdlg();
    });

    _handlers.insert(ID_SEARCH_USER_RSP,[this](ReqId id, int len, QByteArray data){
        Q_UNUSED(len);
        qDebug()<< "handle id is "<< id ;
        QJsonDocument jsonDoc = QJsonDocument::fromJson(data);
        if(jsonDoc.isNull()){
            return;
        }

        QJsonObject jsonObj = jsonDoc.object();
        if(!jsonObj.contains("error")){
            int err = ErrorCodes::ERR_JSON;
            emit sig_login_failed(err);
            return ;
        }

        int err = jsonObj["error"].toInt();
        if(err != ErrorCodes::SUCCESS){
            emit sig_login_failed(err);
            return ;
        }

        auto search_info = std::make_shared<SearchInfo>(jsonObj["uid"].toInt(),
            jsonObj["name"].toString(),jsonObj["nick"].toString(),
            jsonObj["desc"].toString(),jsonObj["sex"].toInt(),jsonObj["icon"].toString()
        );
        emit sig_user_search(search_info);
    });

    _handlers.insert(ID_ADD_FRIEND_RSP,[this](ReqId id, int len, QByteArray data){
        Q_UNUSED(len);
        qDebug()<< "handle id is "<< id ;
        QJsonDocument jsonDoc = QJsonDocument::fromJson(data);
        if(jsonDoc.isNull()){
            return;
        }

        QJsonObject jsonObj = jsonDoc.object();
        if(!jsonObj.contains("error")){
            int err = ErrorCodes::ERR_JSON;
            emit sig_login_failed(err);
            return ;
        }

        int err = jsonObj["error"].toInt();
        if(err != ErrorCodes::SUCCESS){
            emit sig_login_failed(err);
            return ;
        }

        // 请求发送成功...
    });

}

void TcpMgr::handleMsg(ReqId id, int len, QByteArray data)
{
    auto iter = _handlers.find(id);
    if(iter == _handlers.end()){
        return;
    }

    iter.value()(id,len,data);
}

void TcpMgr::slot_tcp_connect(ServerInfo si)
{
    _host = si.Host;
    _port = static_cast<uint16_t>(si.Port.toUInt());
    _socket.connectToHost(si.Host,_port);

}

void TcpMgr::slot_send_data(ReqId reqId, QByteArray dataBytes)
{
    uint16_t id = reqId;

    // 计算长度（使用网络字节序转换）
    quint16 len = static_cast<quint16>(dataBytes.length());

    // 创建一个QByteArray用于存储要发送的所有数据
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);

    // 设置数据流使用网络字节序
    out.setByteOrder(QDataStream::BigEndian);

    // 写入ID和长度
    out << id << len;

    // 添加字符串数据
    block.append(dataBytes);

    // 发送数据
    _socket.write(block);
    qDebug() << "tcp mgr send byte data is " << block ;

}
