#ifndef USERDATA_H
#define USERDATA_H
#include <QString>

class SearchInfo
{
public:
    SearchInfo(int uid, QString name, QString nick, QString desc, int sex, QString icon);
    int _uid;
    QString _name;
    QString _nick;
    QString _desc;
    int _sex;
    QString _icon;

    ~SearchInfo();
};

class AddFriendApply {
public:
    AddFriendApply(int from_uid, QString name, QString desc);
    int _from_uid;
    QString _name;
    QString _desc;
};

struct ApplyInfo {
    ApplyInfo(int uid, QString name, QString desc,
              QString icon, QString nick, int sex, int status)
        :_uid(uid),_name(name),_desc(desc),
        _icon(icon),_nick(nick),_sex(sex),_status(status){}

    void SetIcon(QString head){
        _icon = head;
    }
    int _uid;
    QString _name;
    QString _desc;
    QString _icon;
    QString _nick;
    int _sex;
    int _status;
};

struct AuthInfo {
    AuthInfo(int uid, QString name,
             QString nick, QString icon, int sex):
        _uid(uid), _name(name), _nick(nick), _icon(icon),
        _sex(sex){}
    int _uid;
    QString _name;
    QString _nick;
    QString _icon;
    int _sex;
};

struct AuthRsp {
    AuthRsp(int peer_uid, QString peer_name,
            QString peer_nick, QString peer_icon, int peer_sex)
        :_uid(peer_uid),_name(peer_name),_nick(peer_nick),
        _icon(peer_icon),_sex(peer_sex)
    {}

    int _uid;
    QString _name;
    QString _nick;
    QString _icon;
    int _sex;
};

struct UserInfo {
    UserInfo(int uid, QString name, QString nick, QString icon, int sex, QString last_msg = ""):
        _uid(uid),_name(name),_nick(nick),_icon(icon),_sex(sex),_last_msg(last_msg){}

    UserInfo(std::shared_ptr<AuthInfo> auth):
        _uid(auth->_uid),_name(auth->_name),_nick(auth->_nick),
        _icon(auth->_icon),_sex(auth->_sex),_last_msg(""){}

    UserInfo(int uid, QString name, QString icon):
        _uid(uid), _name(name), _nick(name),_icon(icon),
        _sex(0),_last_msg(""){
    }

    UserInfo(std::shared_ptr<AuthRsp> auth):
        _uid(auth->_uid),_name(auth->_name),_nick(auth->_nick),
        _icon(auth->_icon),_sex(auth->_sex),_last_msg(""){}

    int _uid;
    QString _name;
    QString _nick;
    QString _icon;
    int _sex;
    QString _last_msg;

};

struct NoticeInfo {
    NoticeInfo(int uid, QString name,
             QString msg, QString icon):
        _uid(uid), _name(name), _msg(msg), _icon(icon){}
    NoticeInfo(std::shared_ptr<NoticeInfo> auth):
        _uid(auth->_uid),_name(auth->_name),_msg(auth->_msg),
        _icon(auth->_icon){}

    int _uid;
    QString _name;
    QString _msg;
    QString _icon;
};



#endif // USERDATA_H
