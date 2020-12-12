#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <iterator>

using namespace std;

class Product {
    string name;
    size_t count;
    size_t price;
    string id;
public:
    Product(string name_param, size_t count_param, size_t price_param, string id_param) {
        name = name_param;
        count = count_param;
        price = price_param;
        id = id_param;

    }

    void setName(string name_param) {
        name = name_param;
    }

    string getName() {
        return name;
    }

    void setPrice(size_t price_param) {
        price = price_param;
    }

    void setId(const string id_param){
        id = id_param;
    }

    size_t getPrice() {
        return price;
    }

    void setCount(size_t count_param) {
        count = count_param;
    }

    size_t getCount() {
        return count;
    }

    string getId(){
        return id;
    }
};

class Shop {
    vector<Product*> products;
    string sId;
public:
    vector<Product*> getProducts() {
        return products;
    }
    Shop(string _sId){
        sId = _sId;
    }

    // пункт 3
    void goodsDelivery(vector<Product*> new_products, vector<size_t> new_price = {}) {
        if (new_price.size() > 0 && new_price.size() < new_products.size()) { // если список новых цен имеет цены и размер не болшьше количества добавляемых продуктов
            for (size_t i = new_price.size(); i < new_products.size(); i++) {
                new_price.push_back(0);
            }

            for (size_t i = 0; i < new_products.size(); i++) {
                if (new_price[i] != 0) { // если 0 изменять цену товара не надо
                    cout << "Продукту " << new_products[i]->getName() << " установлена новая цена " << new_price[i] << endl;
                    new_products[i]->setPrice(new_price[i]);
                    this->products.push_back(new_products[i]);
                }
            }
        }
    }

    // 5 пункт
    vector<Product*> calcCountProducts(size_t money) {
        vector<Product*> result_products;
        for (auto p : this->products) {
            if (p->getPrice() <= money) {
                result_products.push_back(p);
            }
            else if (p->getPrice() > money) {
                result_products.pop_back();
                break;
            }
            else {
                break;
            }
        }
        return result_products;
    }

    // 6 пункт
    size_t buyProducts(vector<Product*> products) {
        size_t sum = 0;
        for (auto p : this->products) {
            vector<Product*>::iterator it = find(products.begin(), products.end(), p);
            if (it != products.end()) {
                int index = distance(products.begin(), it);
                if (products[index]->getCount() > p->getCount()) {
                    cout << "Простите товара " << products[index]->getName() << " не хватает для покупки." << endl;
                    return 0; // товара не хватает для покупки
                }
                else {
                    sum += products[index]->getPrice();
                }
            }
        }
        return sum;
    }
};

// пункт 4
Shop* getBestPriceProduct(vector<Shop> list_shops, Product product) {
    Shop* ptr;
    for (auto s : list_shops) {
        vector<Product*> products = s.getProducts();
        size_t lowest_price = products[0]->getPrice();
        for (auto p : products) {
            if (p->getPrice() < lowest_price) {
                lowest_price = p->getPrice();
                ptr = &s; // передаем указатель на магазин в котором наименьшая цена
            }
        }
    }
    return ptr;
}

// пункт 7
Shop* getBestPriceProductList(vector<Shop> list_shops, vector<Product*> products) {
    Shop* ptr = nullptr;
    vector<size_t> sumPriceShops; // вектор сумм наименьших цен на список товаров products
    for (auto s : list_shops) {
        vector<Product*> shop_products = s.getProducts(); // получаем из каждого магазина прайс товаров и их наличие
        for (size_t i = 0; i < products.size(); i++) {
            vector<Product*>::iterator it = find(shop_products.begin(), shop_products.end(), products[i]); // ищем все товары из нашего списка
            if (it != shop_products.end()) {
                int index = distance(shop_products.begin(), it); // если товар найден получаем его индекс
                if (products[index]->getCount() > 0) { // в наличии
                    sumPriceShops.push_back(products[index]->getPrice());
                }
                else {
                    sumPriceShops.push_back(0);
                }
            }
        }
    }

    cout << '\n';
    size_t lowest_price = sumPriceShops[0];
    for (auto s : sumPriceShops) { // идем по всем суммам продуктов, если 0 значит продуктов нет в наличии
        cout << s << ' '; // выводим наименьшие суммы товаров
        if (s != 0) {
            if (s < lowest_price) { // в наличии
                lowest_price = s;
            }
        }
    }

    vector<size_t>::iterator it = find(sumPriceShops.begin(), sumPriceShops.end(), lowest_price);
    int index = distance(sumPriceShops.begin(), it);
    ptr = &list_shops[index]; // передаем указатель на магазин в котором наименьшая цена на партию товаров

    return ptr;
}

int main()
{
    Shop shop, shop2, shop3;
    Product milk("Молоко 900мл", 2, 50);
    Product chocolate("Шоколад 100гр", 1, 40);
    Product coffee("Кофе 200гр", 2, 250);
    Product meat("Мясо 1кг", 3, 350);
    Product nut("Орехи 100гр", 1, 550);
    Product bread("Батон 300гр", 8, 20);
    Product snickers("Сникерс 50гр", 2, 40);
    Product jellybeam("Мармелад 200гр", 1, 70);
    Product breadblack("Черный хлеб 350гр", 6, 30);
    Product jam("Варенье 300гр", 1, 170);
    shop.goodsDelivery({ &jam, &bread, &coffee });
    shop2.goodsDelivery({ &snickers, &nut, &milk, &coffee, &jellybeam }, {49, 499, 39});
    shop3.goodsDelivery({ &chocolate, &meat, &breadblack, &snickers });
}
