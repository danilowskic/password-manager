//
// Created by Czarek on 15.06.2022.
//

#ifndef PASSWORD_MANAGER_CATEGORY_H
#define PASSWORD_MANAGER_CATEGORY_H


#include <string>
#include <fstream>

class Category {
    std::string category;
public:
    Category();
    Category(std::string category);
    static bool alreadyPresent(std::string pred);
    void deleteCategory();
    std::string getCategory();
};


#endif //PASSWORD_MANAGER_CATEGORY_H
