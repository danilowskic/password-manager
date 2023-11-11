#ifndef PASSWORD_MANAGER_PASSWORDMANAGER_H
#define PASSWORD_MANAGER_PASSWORDMANAGER_H

#include <string>
#include <fstream>

class PasswordManager {
    std::fstream timestampFile;
    std::string fileName;
    std::string aP;
public:
    PasswordManager();
    void timestamp();
    void readTimestamp();
    void updateTimestamp();
};


#endif //PASSWORD_MANAGER_PASSWORDMANAGER_H
