#ifndef USER_H
#define USER_H

#include <string>

using std::string;

class User final
{
public:
    User() = delete;
    User(string);

private:
    string name;

};

#endif // USER_H
