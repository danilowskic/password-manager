#include <iostream>
#include "Password.h"
#include "Category.h."

struct Options
{
    std::vector<Password> passwords;
    std::fstream passwordFile;
    std::string accessPassword;
    std::string filename;

    void showOptions()
    {
        std::cout << "1. Wyszukaj hasla" << std::endl;
        std::cout << "2. Posortuj hasla" << std::endl;
        std::cout << "3. Dodaj haslo" << std::endl;
        std::cout << "4. Edytuj haslo" << std::endl;
        std::cout << "5. Usun haslo" << std::endl;
        std::cout << "6. Dodaj kategorie" << std::endl;
        std::cout << "7. Usun kategorie" << std::endl;
        std::cout << "8. KONIEC" << std::endl << std::endl;
        std::cout << "WYBOR:";
    }

    void choice()
    {
        int option = 0;

        while (option != 8)
        {
            showOptions();

            std::cin >> option;

            switch (option) {
                case 1:
                    findPasswords();
                    break;
                case 2:
                    sortPasswords();
                    break;
                case 3:
                    addPassword();
                    break;
                case 4:
                    editPassword();
                    break;
                case 5:
                    deletePassword();
                    break;
                case 6:
                    addCategory();
                    break;
                case 7:
                    deleteCategory();
                    break;
                case 8:
                    exit(0);
                default:
                    std::cerr << "Nie ma takiej opcji!" << std::endl;
            }
        }
    }

    void findPasswords()
    {
        std::string name;
        std::cout << "Podaj nazwe szukanego hasla:";
        std::cin >> name;
        Password p = Password(accessPassword);

        passwords = p.find(filename, name);
        printPasswords();
    }

    void sortPasswords()
    {
        Password p = Password(accessPassword);
        passwords = p.sort(filename);
        printPasswords();
    }

    void addPassword()
    {
        std::string name;
        std::string password1;
        std::string category;
        std::string website = "";
        std::string login = "";

        std::cout << "Nazwa*:";
        std::cin >> name;

        std::cout << "Haslo*:";
        std::cin >> password1;

        std::cout << "Kategoria*:";
        std::cin >> category;

        char decision;
        std::cout << "Czy chcesz dodac \"strona WWW\" i \"login\"? [t/n]:";
        std::cin >> decision;

        if (decision == 't')
        {
            std::cout << "Strona:" << std::endl;
            std::cin >> website;

            std::cout << "Login:";
            std::cin >> login;
        }

        if (website == "" && login == "")
        {
            Password password = Password(accessPassword, name, password1, Category(category));
            password.saveToFile(filename);
        }
        else
        {
            Password password = Password(accessPassword, name, password1, Category(category), website, login);
            password.saveToFile(filename);
        }
    }

    void editPassword()
    {
        std::string name;
        std::cout << "Podaj nazwe hasla do edycji:";
        std::cin >> name;
        std::cout << "Przed kontynuacja: UPEWNIJ SIE CZY WPROWADZONE HASLO DOSTEPU DO APLIKACJI JEST PRAWIDLOWE!" << std::endl << "Haslo:" << Password(accessPassword).getAccessPassword() << std::endl;

        std::string name1, password1, category, website = "", login = "";

        std::cout << "Nazwa*:";
        std::cin >> name1;

        std::cout << "Haslo*:";
        std::cin >> password1;

        std::cout << "Kategoria*:";
        std::cin >> category;

        std::cout << "Strona:";
        std::cin >> website;

        std::cout << "Login:";
        std::cin >> login;

        std::vector<std::string> passwordToChange;
        passwordToChange.push_back(name);

        Password p = Password(accessPassword);
        p.deletePasswords(filename, passwordToChange);

        if (website == "" && login == "")
            Password(accessPassword, name1, password1, Category(category)).saveToFile(filename);
        else
            Password(accessPassword, name1, password1, Category(category), website, login).saveToFile(filename);
    }

    void deletePassword()
    {
        size_t howMany;
        std::cout << "Ile hasel chcesz usunac:";
        std::cin >> howMany;
        std::vector<std::string> passwordsToDelete;

        for (int i = 0; i < howMany; i++)
        {
            std::string name;
            std::cout << "Podaj nazwe [" << std::to_string(i + 1)  << "]:";
            std::cin >> name;
            passwordsToDelete.push_back(name);
        }

        if (howMany > 1)
        {
            std::cout << "Zostanie usunietych wiele hasel. Czy chcesz kontynuowac? [t/n]";
            char decision;
            std::cin >> decision;

            if (decision == 't')
            {
                Password p = Password(accessPassword);
                p.deletePasswords(filename, passwordsToDelete);
            }
            else
                std::cout << "Wstrzymano usuwanie wskazanych hasel" << std::endl;
        }
        else
        {
            Password p = Password(accessPassword);
            p.deletePasswords(filename, passwordsToDelete);
        }
    }

    void addCategory()
    {
        std::string name;
        std::cout << "Nazwa*:";
        std::cin >> name;

        Category category = Category(name);

        std::cout << "Kategoria " << name << " zostala dodana" << std::endl;
    }

    void deleteCategory()
    {
        std::string name;
        std::cout << "Podaj nazwe kategorii do usuniecia:";
        std::cin >> name;

        Category(name).deleteCategory();
        Password p = Password(accessPassword);
        p.deletePasswordsByCategory(filename, name);

        std::cout << "Kategoria " << name << " zostala usunieta" << std::endl;
    }

    void printPasswords()
    {
        for (size_t i = 0; i < passwords.size(); i++)
            std::cout << passwords.at(i).toString() << std::endl;
    }
};