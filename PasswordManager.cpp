#include "PasswordManager.h"
#include "Options.cpp"
#include <iostream>
#include <ctime>

PasswordManager::PasswordManager()
{
    std::cout << "Podaj nazwe pliku hasel do odczytu: ";
    std::cin >> fileName;

    std::cout << "Podaj klucz szyfrujacy by poprawnie odczytac hasla: ";
    std::cin >> aP;

    timestamp();

    Options options;
    options.accessPassword = aP;
    options.filename = fileName;

    options.choice();
}

void PasswordManager::timestamp()
{
    timestampFile.open("log00.txt", std::ios::in);
    readTimestamp();
    timestampFile.open("log00.txt", std::ios::out);
    updateTimestamp();
}

void PasswordManager::readTimestamp()
{
    if (timestampFile.is_open())
    {
        std::cout << "Ostatnia proba odszyfrowania " << std::endl;

        std::string line;
        while (std::getline(timestampFile, line)) {
            // Odszyfrowanie nastepnych elementow pliku timestampa
            // znak '[' jest kluczem ktory odejmujemy by odszyfrowac zawartosc
            char x = line.at(0) - '[';
            std::cout << x;
        }

        std::cout << std::endl;
    }
    else
        std::cerr << "Nie udalo sie odczytac pliku";

    timestampFile.close();
}

void PasswordManager::updateTimestamp()
{
    // Czyszczenie zawartosci pliku
    timestampFile << "";
    timestampFile.close();

    // Tutaj nastepuje update pliku timestamp'a przy probie odszyfrowania hasel
    timestampFile.open("log00.txt", std::ios::app);

    std::time_t t = std::time(0);
    std::tm* now = std::localtime(&t);

    std::string year = std::to_string(now->tm_year + 1900);
    std::string month = std::to_string(now->tm_mon + 1);
    std::string day = std::to_string(now->tm_mday);
    std::string hour = std::to_string(now->tm_hour);
    std::string minutes = std::to_string(now->tm_min);
    std::string secs = std::to_string(now->tm_sec);

    std::string fullTimestamp = year + "-" + month + "-" + day + " " + hour + ":" + minutes + ":" + secs;

    if (timestampFile.is_open())
    {
        for (std::size_t i = 0; i < fullTimestamp.length(); i++)
        {
            char element = fullTimestamp.at(i) + '[';
            timestampFile << element << std::endl;
        }
    }
    else
        std::cerr << "Nie udalo sie odczytac pliku";

    timestampFile.close();
}