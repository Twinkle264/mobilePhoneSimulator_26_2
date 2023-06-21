#include <iostream>
#include <string>
#include <vector>
#include <map>

class Contact {
private:
    std::map<std::string, std::string> numberToName = {{"+79624423444", "Ivanov"},
                                                       {"+79553442454", "Ivanov"},
                                                       {"+79926657483", "Petrov"},
                                                       {"+79779931414", "Sidorov"}};
    std::map<std::string, std::vector<std::string>> nameToNumber = {{"Ivanov",  {"+79624423444", "+79553442454"}},
                                                                    {"Petrov",  {"+79926657483"}},
                                                                    {"Sidorov", {"+79779931414"}}};

    static bool isValidNumber(std::string phoneNumber) {
        if (phoneNumber.size() != 12 || phoneNumber.substr(0, 2) != "+7") {
            return false;
        }
        for (int i = 2; i < phoneNumber.size(); ++i) {
            if (!isdigit(phoneNumber[i])) {
                return false;
            }
        }
        return true;
    }

public:

    void addContact(std::string &request_name, std::string &request_number) {
        if (isValidNumber(request_number)) {
            numberToName.insert(make_pair(request_number, request_name));
            nameToNumber[request_name].resize(nameToNumber[request_name].size() + 1);
            auto it = nameToNumber.find(request_name);
            it->second[nameToNumber[request_name].size() - 1] = request_number;
        } else {
            std::cerr << "Error! Invalid input of phone number." << std::endl;
        }
    }


    std::pair<std::string, std::string> getName(std::string &request_number) {
        auto it = numberToName.find(request_number);

        if (it == numberToName.end()) {
            std::cerr << "Error request!" << std::endl;
        } else {
            return std::make_pair(it->second, it->first);
        }
    }

    std::pair<std::string, std::string> getNumber(std::string &request_name) {
        auto it = nameToNumber.find(request_name);

        if (it == nameToNumber.end()) {
            std::cerr << "Error request!" << std::endl;
        } else if (it->first.length() > 0) {
            if (it->second.size() < 2) {
                for (int i = 0; i < nameToNumber[request_name].size();) {
                    return std::make_pair(it->first, it->second[i]);
                }
            } else {
                std::cout << "There are several contacts with the name " << request_name << std::endl;
                for (int i = 0; i < nameToNumber[request_name].size(); ++i) {
                    std::cout << it->first << ' ' << it->second[i] << std::endl;
                }
                std::cout << "Enter phone number of contact: ";
                std::string number_contact;
                getline(std::cin, number_contact);
                return getName(number_contact);
            }
        }
    }
};

class Phone {
private:
    Contact *contact = new Contact;

public:
    void addContact() {
        std::string name, number;

        std::cout << "\tAdd the contact!" << std::endl << std::endl;
        std::cout << "Enter the name of contact: ";
        getline(std::cin, name);
        std::cout << "Enter the phone number: ";
        getline(std::cin, number);
        contact->addContact(name, number);

    }

    void call(std::string &request) {
        std::cout << "\tCALL" << std::endl;
        std::pair<std::string, std::string> name_and_number;
        if (request.substr(0, 2) == "+7") {
            name_and_number = contact->getName(request);
        } else {
            name_and_number = contact->getNumber(request);
        }
        std::cout << "CALL: " << name_and_number.first << ' ' << name_and_number.second << std::endl;
    }

    void sms(std::string &request) {

        std::pair<std::string, std::string> name_and_number;
        if (request.substr(0, 2) == "+7") {
            name_and_number = contact->getName(request);
        } else {
            name_and_number = contact->getNumber(request);
        }
        std::cout << "SMS: " << name_and_number.first << ' ' << name_and_number.second << std::endl;
        std::string message;
        std::cout << "Enter the message: ";
        getline(std::cin, message);
        std::cout << "The message has been sent!" << std::endl;
    }

    void exit() {
        delete contact;
        contact = nullptr;
    }
};

int main() {
    Phone *phone = new Phone;
    std::string command;

    while (true) {
        std::cout << "Enter the commands (add, call, sms, exit): ";
        std::cin >> command ;

        if (command == "add") {
            std::cin.ignore();
            phone->addContact();
        } else if (command == "call") {
            std::cin.ignore();
            std::string request;
            std::cout << "\tCALL" << std::endl;
            std::cout << "Enter the name or the number of contact: ";
            getline(std::cin, request);
            phone->call(request);
        } else if (command == "sms") {
            std::cin.ignore();
            std::string request;
            std::cout << "\tSMS" << std::endl;
            std::cout << "Enter the name or the number of contact: ";
            getline(std::cin, request);
            phone->sms(request);
        } else if (command == "exit") {
            std::cin.ignore();
            phone->exit();
            delete phone;
            phone = nullptr;
            break;
        }
    }
    return 0;
}
