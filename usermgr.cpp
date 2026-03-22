#include "usermgr.h"

UserMgr::~UserMgr()
{

}

void UserMgr::SetUid(int uid)
{
    _uid = uid;
}

void UserMgr::SetToken(QString token)
{
    _token = token;
}

void UserMgr::SetName(QString name)
{
    _name = name;
}

int UserMgr::GetUid()
{
    return _uid;
}

QString UserMgr::GetName()
{
    return _name;
}

std::vector<std::shared_ptr<ApplyInfo> > UserMgr::GetApplyList()
{
    return _apply_list;
}

UserMgr::UserMgr()
{

}
