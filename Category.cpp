//
// Created by Czarek on 15.06.2022.
//

#include <iostream>
#include "Category.h"

Category::Category()
{
}

Category::Category(std::string category)
{
    this -> category = category;

    if (!alreadyPresent(category))
    {
        std::fstream categoriesFile;
        categoriesFile.open("cats.txt", std::ios::app);
        categoriesFile << category << std::endl;
        categoriesFile.close();
    }
}

/**
 * @param pred Nazwa kategorii
 * @return true jeśli taka kategoria jest już w pliku zawierający kategorie, false w przeciwnym wypadku
 */
bool Category::alreadyPresent(std::string pred)
{
    std::fstream categoriesFile;

    categoriesFile.open("cats.txt", std::ios::in);
    std::string line;
    if (categoriesFile.is_open())
    {
        while (std::getline(categoriesFile, line))
        {
            if (line == pred)
            {
                categoriesFile.close();
                return true;
            }
        }
    }

    categoriesFile.close();
    return false;
}

/**
 * Usuwa kategorię z pliku, której nazwa jest taka sama jak nazwa kategorii obieku klasy Category, na którego rzecz wywoływana jest metoda
 */
void Category::deleteCategory()
{
    std::fstream categoriesFile;
    std::fstream tempFile;
    tempFile.open("temp.txt", std::ios::out);
    categoriesFile.open("cats.txt", std::ios::in);
    std::string line;

    if (tempFile.is_open() && categoriesFile.is_open())
    {
        while (std::getline(categoriesFile, line))
        {
            if (line != category)
                tempFile << line << std::endl;
        }
    }

    tempFile.close();
    categoriesFile.close();
    std::string filename = "cats.txt";
    const char* p = filename.c_str();
    remove(p);
    rename("temp.txt", p);
}

std::string Category::getCategory()
{
    return category;
}