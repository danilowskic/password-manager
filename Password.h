#ifndef PASSWORD_MANAGER_PASSWORD_H
#define PASSWORD_MANAGER_PASSWORD_H

#include <string>
#include <vector>
#include "Category.h"

class Password {
    std::string name;
    std::string password;
    Category category = Category();
    std::string website;
    std::string login;
    std::string accessPassword;
    void checkSecure(std::string filename, std::string password);
    bool isSecure(std::string password);
    bool isUsed(std::string filename, std::string password);
    std::string generatePassword();
    std::string encrypt();
    std::string decrypt(std::string password1);
public:
    Password(std::string accessPass);
    Password(std::string accessPass, std::string name, std::string password1, Category category1);
    Password(std::string accessPass, std::string name, std::string password1, Category category1, std::string website1, std::string login1);
    std::vector<Password> find(std::string filename, std::string name1);
    std::vector<Password> sort(std::string filename);
    void deletePasswords(std::string filename, std::vector<std::string> passwordsNames);
    void deletePasswordsByCategory(std::string filename, std::string categoryName);
    void saveToFile(std::string filename);
    std::string getAccessPassword();
    std::string getCategory();
    std::string toString();
};


#endif //PASSWORD_MANAGER_PASSWORD_H
