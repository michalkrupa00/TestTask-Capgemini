#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>
#include <map>

struct Phone {
    std::string brand_name;
    std::string model_name;
    std::string form_factor;
    int year_of_issue;
    double screen_size;
    double price;
};

class PhoneShop {
public:
    PhoneShop() {}

    void add_phone(const Phone& phone) {
        phones_.push_back(phone);       
    }

    void delete_phone(int index) {
        phones_.erase(phones_.begin() + index);
    }

    void report() const {
        std::cout << "Index\tBrand Name\tModel Name\tForm Factor\tYear\tScreen Size\tPrice\n";
        for (int i = 0; i < phones_.size(); ++i) {
            const Phone& phone = phones_[i];
            std::cout << i << "\t" << phone.brand_name << "\t\t" << phone.model_name << "\t\t" << phone.form_factor << "\t\t"
                << phone.year_of_issue << "\t\t" << phone.screen_size << "\t" << phone.price << "\t" << std::endl << std::endl;
        }
    }

    void ShowByBrand() {
        std::string brand;
        std::cout << "Enter brand name: ";
        std::cin >> brand;
        for (const auto& p : phones_) {
            if (p.brand_name == brand) {
                std::cout << "Model: " << p.model_name << std::endl;
                std::cout << "Form Factor: " << p.form_factor << std::endl;
                std::cout << "Year: " << p.year_of_issue << std::endl;
                std::cout << "Screen Size: " << p.screen_size << std::endl;
                std::cout << "Price: " << p.price << std::endl;
                std::cout << std::endl;
            }
        }
    }

    void ShowByFormFactorAndScreenSize() {
        std::string form_factor;
        float screen_size;
        std::cout << "Enter form factor: ";
        std::cin >> form_factor;
        std::cout << "Enter screen size: ";
        std::cin >> screen_size;
        for (const auto& p : phones_) {
            if (p.form_factor == form_factor && p.screen_size == screen_size) {
                std::cout << "Brand: " << p.brand_name << std::endl;
                std::cout << "Model: " << p.model_name << std::endl;
                std::cout << "Year: " << p.year_of_issue << std::endl;
                std::cout << "Price: " << p.price << std::endl;
                std::cout << std::endl;
            }
        }
    }

    void ShowBrandWithMaxQuantity() {
        std::string brand_with_max_quantity;
        int max_quantity = 0;
        for (const auto& p : phones_) {
            int count = 0;
            for (const auto& q : phones_) {
                if (p.brand_name == q.brand_name) {
                    count++;
                }
            }
            if (count > max_quantity) {
                brand_with_max_quantity = p.brand_name;
                max_quantity = count;
            }
        }
        std::cout << "Brand with the maximum quantity of phones: " << brand_with_max_quantity << std::endl;
    }

    void ShowTopThreeScreenSizes() {
        std::vector<std::pair<float, int>> screen_sizes;
        for (const auto& p : phones_) {
            bool found = false;
            for (auto& q : screen_sizes) {
                if (p.screen_size == q.first) {
                    q.second++;
                    found = true;
                    break;
                }
            }
            if (!found) {
                screen_sizes.push_back({ p.screen_size, 1 });
            }
        }
        std::sort(screen_sizes.begin(), screen_sizes.end(),
            [](const auto& a, const auto& b) { return a.second > b.second; });
        std::cout << "Top 3 screen sizes:" << std::endl;
        for (int i = 0; i < 3 && i < screen_sizes.size(); i++) {
            std::cout << screen_sizes[i].first << " - " << screen_sizes[i].second << std::endl;
        }
    }

    void SaveToFile(const std::string& Phone_List) {
        std::ofstream ofs(Phone_List);
        for (const auto& p : phones_) {
            ofs << p.brand_name << " " << p.model_name << " " << p.form_factor << " " << p.year_of_issue << " " << p.screen_size << " " << p.price << std::endl;
        }
        ofs.close();
    }

    void LoadFromFile(const std::string& Phone_List) {
        std::ifstream ifs(Phone_List);
        std::string brand_name, model_name, form_factor;
        int year_of_issue;
        float screen_size, price;
        while (ifs >> brand_name >> model_name >> form_factor >> year_of_issue >> screen_size >> price) {
            phones_.push_back({ brand_name, model_name, form_factor, year_of_issue, screen_size, price });
        }
        ifs.close();
    }


private:
    std::vector<Phone> phones_;
};

int main() {
    PhoneShop phone_shop;
    std::string Phone_List = "Phone_List.txt";
    while (true) {
        std::cout << "1. Add a phone\n"
            << "2. Delete a phone\n"
            << "3. Reports\n"
            << "4. Load from file\n"
            << "0. Exit\n"
            << "Enter your choice: \n";
        int choice;
        std::cin >> choice;
        if (choice == 0) {
            break;
        }
        switch (choice) {
        case 1: {
            Phone phone;
            std::cout << "Enter brand name: ";
            std::cin >> phone.brand_name;
            std::cout << "Enter model name: ";
            std::cin >> phone.model_name;
            std::cout << "Enter form factor: ";
            std::cin >> phone.form_factor;
            std::cout << "Enter year of issue: ";
            std::cin >> phone.year_of_issue;
            std::cout << "Enter screen size: ";
            std::cin >> phone.screen_size;
            std::cout << "Enter price: ";
            std::cin >> phone.price;
            phone_shop.add_phone(phone);
            phone_shop.SaveToFile(Phone_List);
            break;
        }
        case 2: {
            int index;
            std::cout << "Enter the index of the phone to delete: ";
            std::cin >> index;
            phone_shop.delete_phone(index);
            break;
        }
        case 3: {
            int select_report;
            phone_shop.report();
            std::cout << "1. Show By Brand" << std::endl;
            std::cout << "2. Show By Given Factor and Screen Size" << std::endl;
            std::cout << "3. Show Brand with the maxium quantity" << std::endl;
            std::cout << "4. Show TOP-3 screen sizes" << std::endl;
            std::cout << "Select your choice" << std::endl;
            std::cin >> select_report;
            if (select_report == 1) {
                phone_shop.ShowByBrand();
            }
            else if (select_report == 2) {
                phone_shop.ShowByFormFactorAndScreenSize();
            }
            else if (select_report == 3) {
                phone_shop.ShowBrandWithMaxQuantity();
            }
            else if (select_report == 4) {
                phone_shop.ShowTopThreeScreenSizes();
            }
            break;

        case 4: {
            phone_shop.LoadFromFile(Phone_List);
        }

        }
        default: {
            std::cout << "Choose other case\n";
            break;
        }
        }
    }
    return 0;
}
