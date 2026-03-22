#ifndef USERMGR_H
#define USERMGR_H
#include "F_singleton.h"
#include "chat/Chat_Comp/userdata.h"

class UserMgr : public QObject,public F_Singleton<UserMgr>,
                public std::enable_shared_from_this<UserMgr>
{
    Q_OBJECT
public:
    friend class F_Singleton<UserMgr>;
    ~UserMgr();
    void SetUid(int uid);
    void SetToken(QString token);
    void SetName(QString name);
    int GetUid();
    QString GetName();
    std::vector<std::shared_ptr<ApplyInfo>> GetApplyList();

private:
    int _uid;
    QString _name;
    QString _token;
    std::vector<std::shared_ptr<ApplyInfo>> _apply_list;
    UserMgr();
};

#endif // USERMGR_H
