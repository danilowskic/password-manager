#include <sstream>
#include <iostream>
#include "Password.h"
#include "Category.h"

Password::Password(std::string accessPass)
{
    accessPassword = accessPass;
}

Password::Password(std::string accessPass, std::string name1, std::string password1, Category category1)
{
    name = name1;
    password = password1;
    category = category1;
    website = "";
    login = "";
    accessPassword = accessPass;
}

Password::Password(std::string accessPass, std::string name1, std::string password1, Category category1, std::string website1, std::string login1)
{
    name = name1;
    password = password1;
    category = category1;
    website = website1;
    login = login1;
    accessPassword = accessPass;
}

/**
 * @param filename
 * @param name1
 * @return hasla o ustalonej nazwie
 */
std::vector<Password> Password::find(std::string filename, std::string name1)
{
    std::vector<Password> passwords;
    std::fstream file;
    file.open(filename, std::ios::in);

    if (file.is_open())
    {
        std::string line, e;
        while (std::getline(file, line))
        {
            std::stringstream sstream(line);

            std::string name2, password1, website1 = "", login1 = "";
            Category category1 = Category();

            bool condition = false;
            int counter = 1;
            while (std::getline(sstream, e, ';'))
            {
                if (counter == 1)
                {
                    if (name1 == e)
                        condition = true;

                    name2 = e;
                }

                if (counter == 2)
                    password1 = e;

                if (counter == 3)
                    category1 = Category(e);

                if (counter == 4)
                    website1 = e;

                if (counter == 5)
                    login1 = e;

                counter++;
            }

            if (condition)
            {
                if (website1 == "" && login1 == "")
                    passwords.push_back(Password(accessPassword, name2, password1, category1));
                else
                    passwords.push_back(Password(accessPassword, name2, password1, category1, website1, login1));
            }
        }
    }
    else
        std::cerr << "Nie udalo sie otworzyc pliku!" << std::endl;

    file.close();
    return passwords;
}

/**
 * @param filename
 * @return wektor posortowanych haseł według kategorii
 */
std::vector<Password> Password::sort(std::string filename)
{
    std::vector<Password> passwords;
    std::fstream file;
    file.open(filename, std::ios::in);

    if (file.is_open())
    {
        std::string line, e;
        while (std::getline(file, line))
        {
            std::stringstream sstream(line);

            std::string name1, password1, website1 = "", login1 = "";
            Category category1 = Category();

            int counter = 1;
            while (std::getline(sstream, e, ';'))
            {
                if (counter == 1)
                    name1 = e;

                if (counter == 2)
                    password1 = e;

                if (counter == 3)
                    category1 = Category(e);

                if (counter == 4)
                    website1 = e;

                if (counter == 5)
                    login1 = e;

                counter++;
            }

            if (website1 == "" && login1 == "")
            passwords.push_back(Password(accessPassword, name1, password1, category1));
            else
            passwords.push_back(Password(accessPassword, name1, password1, category1, website1, login1));
        }
    }
    else
        std::cerr << "Nie udalo sie otworzyc pliku!" << std::endl;

    file.close();

    bool isSorted = false;
    while (!isSorted) {
        bool sortedRound = true;
        for (size_t i = 1; i < passwords.size(); i++)
        {
            if (passwords.at(i - 1).getCategory() > passwords.at(i).getCategory())
            {
                std::swap(passwords.at(i-1), passwords.at(i));
                sortedRound = false;
            }
        }

        if (sortedRound)
            isSorted = true;
    }

    return passwords;
}

/**
 *
 * @param filename Nazwa pliku gdzie znajduje sie haslo
 * @param password Haslo w odszyfrowanej postaci
 * Funkcja łączy w sobie dwa pozostałe funckje dt bezpieczeństwa: czy haslo bylo już użyte i czy jest dość skomplikowane
 */
void Password::checkSecure(std::string filename, std::string password)
{
    if (isSecure(password))
        std::cout << "Haslo jest bezpieczne" << std::endl;
    else
        std::cout << "Haslo nie jest bezpieczne, rozwaz jego zmiane" << std::endl;

    if (isUsed(filename, password))
        std::cout << "Haslo zostalo juz wczesniej uzyte" << std::endl;
    else
        std::cout << "Haslo nie zostalo jeszcze uzyte" << std::endl;
}

/**
 *
 * @param password1
 * @return Zwraca true jeśli hasło jest dość skomplikowane, false w przeciwnym
 */
bool Password::isSecure(std::string password1) {
    // Minimalna dlugosc 8
    if (password1.length() < 8)
        return false;

    // Zlozonosc
    int counterComplication = 0;
    for (size_t i = 1; i < password1.length(); i++)
    {
        if (password1.at(i) - password1.at(i - 1) > 1)
            counterComplication++;
    }

    if (counterComplication > 6)
        return true;

    return false;
}

/**
 *
 * @param filename
 * @param password
 * @return true jeśli hasło zostało już kiedyś użyte i zapisane do podanego pliku
 */
bool Password::isUsed(std::string filename, std::string password)
{
    std::fstream file;
    file.open(filename, std::ios::in);

    if (file.is_open())
    {
        std::string line, e;
        while (std::getline(file, line))
        {
            std::stringstream sstream(line);
            while (std::getline(sstream, e, ';'))
            {
                if (password == e)
                    return true;
            }
        }
    }

    return false;
}

/**
 * @return Wygenerowany string reprezentujący hasło zgodnie z predyspozycjami wybranymi przez użytkownika
 */
std::string Password::generatePassword()
{
    srand(time(NULL));
    size_t length;
    char letters;
    char special;

    std::cout << "Ile znakow ma posiadac? ";
    std::cin >> length;

    std::cout << "Ma posiadac male i duze litery? [t/n] ";
    std::cin >> letters;

    std::cout << "Ma posiadac znaki specjalne? [t/n] ";
    std::cin >> special;

    std::string generate = "";

    for (size_t i = 0; i < length; i++)
    {
        char character;
        if (letters == 't')
        {
            int letterType = rand() % 2;

            if (letterType == 0)
                character = 'A' + rand() % 26;
            else
                character = 'a' + rand() % 26;

            generate = generate + character;
        }

        if (special == 't')
        {
            char specials[] = {'!', '@', '#', '$', '%', '^', '&', '*', '(', ')', '-', '_', '+', '='};
            int index = rand() % 13;

            generate = generate + specials[index];
        }

        if (letters != 't' && special != 't')
        {
            int charType = rand() % 3;
            char specials[] = {'!', '@', '#', '$', '%', '^', '&', '*', '(', ')', '-', '_', '+', '='};

            if (charType == 0)
            {
                character = 'A' + rand() % 26;
                generate = generate + character;
            }
            if (charType == 1)
            {
                character = 'a' + rand() % 26;
                generate = generate + character;
            }
            if (charType == 2)
            {
                int index = rand() % 13;

                generate = generate + specials[index];
            }
        }
    }

    generate.resize(length);
    return generate;
}

/**
 * @return zaszyfrowane haslo wprowadzone przez użytkownika
 * Szyfrowane jest wg nowatorskiego algorytmu przy użyciu hasla dostępu (haslo dostępu do aplikacji wprowadzone przy pierwszym tworzeniu nowego pliku
 * i dodania pierwszego hasla jest dla danego pliku prawidlowym i jedynym sensownym kluczem do prawidlowego zaszyfrowania i odszyfrowania hasel w danym pliku)
 */
std::string Password::encrypt()
{
    std::string encrypted = "";

    int x = 0;
    for (size_t i = 0; i < accessPassword.length(); i++)
        x += accessPassword.at(i);
    x /= accessPassword.length();

    for (size_t i = 0; i < password.length(); i++)
    {
        char character = password.at(i) + x;
        encrypted = encrypted + character;
    }

    return encrypted;
}

/**
 * @param password1
 * @return odszyfrowane haslo wg nowatorskiego algorytmu szyfrowania
 * Do odszyfrowania hasla używane jest hasło dostępu do aplikacji (pierwsze haslo dostepu wprowadzone przy dodawaniu pierszego hasla do pliku
 * jest jedynym gwarantem prawdziwego odszyfrowanego hasla)
 */
std::string Password::decrypt(std::string password1)
{
    std::string encrypted = "";

    int x = 0;
    for (size_t i = 0; i < accessPassword.length(); i++)
        x += accessPassword.at(i);
    x /= accessPassword.length();

    for (size_t i = 0; i < password1.length(); i++)
    {
        char character = password1.at(i) - x;
        encrypted = encrypted + character;
    }

    return encrypted;
}

/**
 *
 * @param filename nazwa pliku, z którego usunięte będą hasla
 * @param passwordsNames wektor zawierający nazwy haseł do usunięcia
 * Usuwa z pliku hasla spelniajace warunek nazwy
 */
void Password::deletePasswords(std::string filename, std::vector<std::string> passwordsNames)
{
    std::fstream file;
    file.open(filename, std::ios::in);
    std::fstream tempFile;
    tempFile.open("temp.txt", std::ios::out);

    std::string line;
    if (file.is_open() && tempFile.is_open())
    {
        while (std::getline(file, line))
        {
            std::stringstream sstream(line);
            std::string e;

            int counter = 1;
            while (std::getline(sstream, e, ';'))
            {
                if (counter == 1)
                {
                    bool notDelete = true;
                    for (size_t i = 0; i < passwordsNames.size(); i++)
                    {
                        if (e == passwordsNames.at(i))
                            notDelete = false;
                    }

                    if (notDelete)
                        tempFile << line << std::endl;
                }

                counter++;
            }
        }
    }

    file.close();
    tempFile.close();
    const char* p = filename.c_str();
    remove(p);
    rename("temp.txt", p);
}

/**
 * @param filename
 * @param categoryName
 * Usuwa hasla z pliku przy usuwaniu danej kategorii, do której te hasła należą
 */
void Password::deletePasswordsByCategory(std::string filename, std::string categoryName)
{
    std::fstream file;
    file.open(filename, std::ios::in);
    std::fstream tempFile;
    tempFile.open("temp.txt", std::ios::out);

    std::string line;
    if (file.is_open() && tempFile.is_open())
    {
        while (std::getline(file, line))
        {
            std::stringstream sstream(line);
            std::string e;

            int counter = 1;
            while (std::getline(sstream, e, ';'))
            {
                if (counter == 3)
                {
                    if (e != categoryName)
                        tempFile << line << std::endl;
                }

                counter++;
            }
        }
    }

    file.close();
    tempFile.close();
    const char* p = filename.c_str();
    remove(p);
    rename("temp.txt", p);
}

/**
 * @param filename Nazwa pliku gdzie ma być zapisany rekord hasła
 */
void Password::saveToFile(std::string filename)
{
    checkSecure(filename, password);
    char decision;
    std::cout << "Czy chcialbys haslo wygenerowane automatycznie? [t/n] ";
    std::cin >> decision;

    if (decision == 't')
    {
        std::string generated = generatePassword();
        std::cout << "Wygenerowane haslo: " << generated << std::endl;
        char save;
        std::cout << "Czy chcesz je zachowac? [t/n] ";
        std::cin >> save;

        password = save == 't' ? generated : password;
    }

    std::fstream file;
    file.open(filename, std::ios::app);

    if (file.is_open())
    {
        file << this->name << ";" << this->encrypt() << ";" << this->category.getCategory();
        if (website != "" && login != "")
            file << ";" << website << ";" << login;

        file << std::endl;
    }
    else
        std::cerr << "Nie udalo sie otworzyc pliku!" << std::endl;

    file.close();
}

std::string Password::getCategory()
{
    return category.getCategory();
}

std::string Password::toString()
{
    std::string result = name + "\nOdszyfrowane: " + decrypt(password) + " kategoria:" + category.getCategory() + " " + website + " " + login;
    return result;
}

std::string Password::getAccessPassword()
{
    return accessPassword;
}