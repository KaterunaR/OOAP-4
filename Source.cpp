#include <iostream>
#include <vector>
#include <string>
using namespace std;

/*Американська фірма - виробник мобільних телефонів відкрила філіал у
одній з країн сходу.Моделі телефонів, що виготовляються у філіалі ті ж самі,
що і у США, але вартість суттєво відрізняється за рахунок економії на оплаті
праці.Інтернет - магазин, який займається продажем телефонів даної марки, дає
покупцю можливість обрати країну виробника.Після оформлення замовлення
покупець отримує інформацію про термін доставки та вартість телефону.Дані
характеристики залежать від країни виробника.Розробити програму для
покупки телефону через інтернет - магазин.Для створення об’єктів
скористатись шаблоном Абстрактна фабрика(Abstract Factory).*/

// абстрактний клас для телефонів
class Phone {
public:
    virtual string getModel() = 0;
    virtual double getPrice() = 0;
    virtual string getDeliveryTime() = 0;
    virtual ~Phone() {}
};


class USPhone : public Phone {
    string model;
    double price;
    string deliveryTime;

public:
    USPhone(string model) : model(model), price(800), deliveryTime("1 week") {}

    string getModel() override {
        return model;
    }

    double getPrice() override {
        return price;
    }

    string getDeliveryTime() override {
        return deliveryTime;
    }
};

class ChinaPhone : public Phone {
    string model;
    double price;
    string deliveryTime;

public:
    ChinaPhone(string model) : model(model), price(500), deliveryTime("3 weeks") {}

    string getModel() override {
        return model;
    }

    double getPrice() override {
        return price;
    }

    string getDeliveryTime() override {
        return deliveryTime;
    }
};

class IndiaPhone : public Phone {
    string model;
    double price;
    string deliveryTime;

public:
    IndiaPhone(string model) : model(model), price(400), deliveryTime("2 weeks") {}

    string getModel() override {
        return model;
    }

    double getPrice() override {
        return price;
    }

    string getDeliveryTime() override {
        return deliveryTime;
    }
};

// Абстрактна фабрика 
class PhoneFactory {
public:
    virtual Phone* createPhone(string model) = 0;
    virtual ~PhoneFactory() {}
};

// Конкретні фабрики 
class USPhoneFactory : public PhoneFactory {
public:
    Phone* createPhone(string model) override {
        return new USPhone(model);
    }
};

class ChinaPhoneFactory : public PhoneFactory {
public:
    Phone* createPhone(string model) override {
        return new ChinaPhone(model);
    }
};

class IndiaPhoneFactory : public PhoneFactory {
public:
    Phone* createPhone(string model) override {
        return new IndiaPhone(model);
    }
};


class Order {
    vector<Phone*> phones;
    PhoneFactory* factory;

public:
    Order(PhoneFactory* f) : factory(f) {}

    void addPhone(string model) {
        phones.push_back(factory->createPhone(model));
    }

    void showOrderDetails() {
        for (auto& phone : phones) {
            cout << "Model: " << phone->getModel()
                << ", Price: " << phone->getPrice() << " USD"
                << ", Delivery Time: " << phone->getDeliveryTime() << "\n";
        }
    }

    ~Order() {
        for (auto& phone : phones) {
            delete phone;
        }
    }
};


int main() {

    PhoneFactory* usFactory = new USPhoneFactory();
    Order usOrder(usFactory);
    usOrder.addPhone("US Model X");
    usOrder.addPhone("US Model Y");
    cout << "US Order Details:\n";
    usOrder.showOrderDetails();
    delete usFactory;

    PhoneFactory* chinaFactory = new ChinaPhoneFactory();
    Order chinaOrder(chinaFactory);
    chinaOrder.addPhone("China Model A");
    chinaOrder.addPhone("China Model B");
    cout << "\nChina Order Details:\n";
    chinaOrder.showOrderDetails();
    delete chinaFactory;

    PhoneFactory* indiaFactory = new IndiaPhoneFactory();
    Order indiaOrder(indiaFactory);
    indiaOrder.addPhone("India Model M");
    cout << "\nIndia Order Details:\n";
    indiaOrder.showOrderDetails();
    delete indiaFactory;

    return 0;
}
