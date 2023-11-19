#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

class Guide 
{
private:
    std::string companyName;
    std::string owner;
    int phoneNumber;
    std::string address;
    std::string activity;

public:
    Guide() = default;
    Guide(const std::string& companyName, const std::string& owner, int phoneNumber, const std::string& address, const std::string& activity)
        : companyName(companyName), owner(owner), phoneNumber(phoneNumber), address(address), activity(activity) {}

    void printGuide() const;
    void addCompany(const std::string& companyName, const std::string& owner, int phoneNumber, const std::string& address, const std::string& activity);
    void saveGuide();
    void loadGuide(const std::string& fileName);
    void searchCompanyName(const std::string& companyName);
    void searchOwner(const std::string& owner);
    void searchPhoneNumber(int phoneNumber);
    void searchActivity(const std::string& activity);
    void viewAllCompanies();
    void saveCurrentCompanyToFile();
};

int main() 
{
    setlocale(LC_ALL, "rus");
    Guide guide;

    int choice;
    do 
    {
        std::cout << "\nМеню:\n";
        std::cout << "1. Добавить компанию\n";
        std::cout << "2. Поиск по названию компании\n";
        std::cout << "3. Поиск по владельцу\n";
        std::cout << "4. Поиск по номеру телефона\n";
        std::cout << "5. Поиск по роду деятельности\n";
        std::cout << "6. Вывести все записи\n";
        std::cout << "7. Сохранить компанию в файл\n";
        std::cout << "0. Выйти из программы\n";
        std::cout << "Выберите операцию: ";
        std::cin >> choice;

        switch (choice) 
        {
        case 1: 
        {
            std::string name, owner, address, activity;
            int phoneNumber;
            std::cout << "Введите название компании: ";
            std::cin.ignore();
            std::getline(std::cin, name);
            std::cout << "Введите владельца: ";
            std::getline(std::cin, owner);
            std::cout << "Введите номер телефона: ";
            std::cin >> phoneNumber;
            std::cout << "Введите адрес: ";
            std::cin.ignore();
            std::getline(std::cin, address);
            std::cout << "Введите род деятельности: ";
            std::getline(std::cin, activity);

            guide.addCompany(name, owner, phoneNumber, address, activity);
            guide.saveGuide();
            break;
        }

        case 2: 
        {
            std::string name;
            std::cout << "Введите название компании для поиска: ";
            std::cin.ignore();
            std::getline(std::cin, name);
            guide.searchCompanyName(name);
            break;
        }
        case 3: 
        {
            std::string owner;
            std::cout << "Введите владельца для поиска: ";
            std::cin.ignore();
            std::getline(std::cin, owner);
            guide.searchOwner(owner);
            break;
        }
        case 4:
        {
            int phoneNumber;
            std::cout << "Введите номер телефона для поиска: ";
            std::cin >> phoneNumber;
            guide.searchPhoneNumber(phoneNumber);
            break;
        }
        case 5: 
        {
            std::string activity;
            std::cout << "Введите род деятельности для поиска: ";
            std::cin.ignore();
            std::getline(std::cin, activity);
            guide.searchActivity(activity);
            break;
        }
        case 6:
        {
            guide.viewAllCompanies();
            break;
        }
        case 7: 
        {
            guide.saveCurrentCompanyToFile();
            break;
        }
        case 0:
            std::cout << "Выход из программы.\n";
            break;
        default:
            std::cout << "Некорректный выбор.\n";
            break;
        }

    } while (choice != 0);

    return 0;
}

void Guide::printGuide() const 
{
    if (companyName.empty() || owner.empty() || phoneNumber == 0 || address.empty() || activity.empty()) {
        std::cout << "Ошибка печати, проверьте корректность данных" << std::endl;
    }
    else 
    {
        std::cout << std::setw(20) << "Компания:" << companyName << std::endl;
        std::cout << std::setw(20) << "Владелец:" << owner << std::endl;
        std::cout << std::setw(20) << "Телефон:" << phoneNumber << std::endl;
        std::cout << std::setw(20) << "Адрес:" << address << std::endl;
        std::cout << std::setw(20) << "Деятельность:" << activity << std::endl;
    }
}

void Guide::addCompany(const std::string& companyName, const std::string& owner, int phoneNumber, const std::string& address, const std::string& activity) {
    if (companyName.empty() || owner.empty() || phoneNumber == 0 || address.empty() || activity.empty()) 
    {
        std::cout << "Ошибка добавления компании, проверьте корректность данных" << std::endl;
    }
    else 
    {
        this->companyName = companyName;
        this->owner = owner;
        this->phoneNumber = phoneNumber;
        this->address = address;
        this->activity = activity;
        std::cout << "Компания успешно добавлена" << std::endl;
    }
}

void Guide::saveGuide() 
{
    std::ofstream file("Guide.txt", std::ios::app);
    if (!file.is_open()) 
    {
        std::cout << "Ошибка открытия файла 'Guide.txt' для записи. Проверьте корректность пути и права доступа.\n";
        return;
    }
    file << companyName << ";" << owner << ";" << phoneNumber << ";" << address << ";" << activity << std::endl;
    if (file.fail()) 
    {
        std::cout << "Ошибка записи в файл 'Guide.txt'. Проверьте корректность пути и права доступа.\n";
    }
    else
    {
        std::cout << "Компания успешно сохранена в файл 'Guide.txt'.\n";
    }
    file.close();
}


void Guide::loadGuide(const std::string& fileName) 
{
    std::ifstream file(fileName);
    if (!file.is_open())
    {
        std::cout << "Ошибка открытия файла, проверьте корректность пути" << std::endl;
        return;
    }

    std::cout << "\nВсе записи в справочнике:\n";
    while (!file.eof()) {
        file >> companyName >> owner >> phoneNumber >> address >> activity;
        if (file.fail()) {
            break;
        }
        printGuide();
    }

    file.close();
}

void Guide::searchCompanyName(const std::string& companyName) 
{
    std::ifstream file("Guide.txt");
    if (!file.is_open()) 
    {
        std::cout << "Ошибка открытия файла, проверьте корректность пути" << std::endl;
        return;
    }

    std::string compName;
    bool found = false;
    while (file >> compName >> owner >> phoneNumber >> address >> activity)
    {
        if (compName == companyName) 
        {
            found = true;
            std::cout << "\nНайденная компания:\n";
            printGuide();
            break;
        }
    }

    if (!found) {
        std::cout << "Компания с именем " << companyName << " не найдена.\n";
    }

    file.close();
}

void Guide::searchOwner(const std::string& owner)
{
    std::ifstream file("Guide.txt");
    if (!file.is_open()) 
    {
        std::cout << "Ошибка открытия файла, проверьте корректность пути" << std::endl;
        return;
    }

    bool found = false;
    while (!file.eof())
    {
        file >> companyName >> this->owner >> phoneNumber >> address >> activity;
        if (file.fail()) 
        {
            break;
        }
        if (this->owner == owner) 
        {
            found = true;
            std::cout << "\nНайденная компания:\n";
            printGuide();
        }
    }

    if (!found) 
    {
        std::cout << "Компании владельца " << owner << " не найдены.\n";
    }

    file.close();
}

void Guide::searchPhoneNumber(int phoneNumber) 
{
    std::ifstream file("Guide.txt");
    if (!file.is_open()) 
    {
        std::cout << "Ошибка открытия файла, проверьте корректность пути" << std::endl;
        return;
    }

    bool found = false;
    while (!file.eof()) 
    {
        file >> companyName >> owner >> this->phoneNumber >> address >> activity;
        if (file.fail()) 
        {
            break;
        }
        if (this->phoneNumber == phoneNumber) 
        {
            found = true;
            std::cout << "\nНайденная компания:\n";
            printGuide();
        }
    }

    if (!found) {
        std::cout << "Компании с номером телефона " << phoneNumber << " не найдены.\n";
    }

    file.close();
}

void Guide::searchActivity(const std::string& activity)
{
    std::ifstream file("Guide.txt");
    if (!file.is_open()) 
    {
        std::cout << "Ошибка открытия файла, проверьте корректность пути" << std::endl;
        return;
    }

    bool found = false;
    while (!file.eof()) 
    {
        file >> companyName >> owner >> phoneNumber >> address >> this->activity;
        if (file.fail()) 
        {
            break;
        }
        if (this->activity == activity) 
        {
            found = true;
            std::cout << "\nНайденная компания:\n";
            printGuide();
        }
    }

    if (!found) 
    {
        std::cout << "Компании с деятельностью " << activity << " не найдены.\n";
    }

    file.close();
}

void Guide::viewAllCompanies() 
{
    loadGuide("Guide.txt");
}

void Guide::saveCurrentCompanyToFile()
{
    saveGuide();
    std::cout << "Текущая компания сохранена в файле.\n";
}
