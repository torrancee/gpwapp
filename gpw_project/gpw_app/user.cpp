#include "user.h"

User::User(QString name_):
    name(name_){}

QString User::getName()
{
    return name;
}
