/**
 * @version v0.1
 * @author Shishkin A.S.
 */
#include <iostream>
#include <fstream>
#include <vector>
#include "lib/json.hpp"

using json = nlohmann::json;

// класс содержащая данные о кредите
class Credit {
public:
    Credit(float _sum, int _term, std::string _name = "Untilted") : sum(_sum), term(_term), name(_name) {
        //id++;
        calculateMontlyPay();
        std::cout << "Добавлен новый кредит\n";
    }
    void printInfo() {
        printf("Сумма кредита: %.2f, срок: %d месяцев, ежемесячный платёж: %.2f\n", sum, term, monthlyPay);
    }
    //static int id;
    std::string name;
    float sum; // Сумма кредита
    int term; // Срок кредита (В месяцах)
    float monthlyPay; // Ежемесечный платёж
private:
    void calculateMontlyPay() {
        monthlyPay = sum / term;
    }
};

void testWork() {
    std::vector<Credit> credits;

    Credit credit1(15000, 24);
    credits.push_back(credit1);
    Credit credit2(30000, 24);
    credits.push_back(credit2);

    for (Credit cred : credits) {
        cred.printInfo();
    }
}

void addCredJsonRecord(Credit credData) {
    json data;
    
    std::ofstream file;

    data["id"] = 1;
    data["name"] = credData.name;
    data["sum"] = credData.sum;
    data["term"] = credData.term;
    data["monthlyPay"] = credData.monthlyPay;

    file.open("Data.json", std::ios::app);

    file << data.dump(2);
    file << ", \n";

    file.close();
}

Credit addNewCredit() {
    float sum;
    int term;
    std::cout << "Введите сумму кредита: ";
    std::cin >> sum;
    std::cout << "Введите срок кредита: ";
    std::cin >> term;

    Credit cred(sum, term);

    addCredJsonRecord(cred);

    return cred;
}

int main() {
    std::vector<Credit> credits_list;

    bool isFirstRun = true;

    std::ifstream file_r("Data.json");
    if (file_r.is_open()) {
        std::cout << "Открыт файл" << std::endl;
        isFirstRun = false;
    } else {
        std::cout << "Файл не существует. Создание файла...\n";
        std::ofstream file_w("Data.json");
        file_w.close(); 
    }

    std::cout << isFirstRun << std::endl;

    json data;

    if (isFirstRun) {
        std::cout << "Создан пустой файл. Ничего не добавлено\n";
        return 0; 
    } else {
        try {
            data = json::parse(file_r);
        }
        catch(nlohmann::json_abi_v3_11_3::detail::parse_error) {
            std::cout << "Файл пуст" << '\n';
        }
    }
    file_r.close();

    credits_list.push_back(addNewCredit());

    credits_list[0].printInfo();

    
    return 0;
}