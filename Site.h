#pragma once

#include<iostream>
#include<string>
#include<vector>
#include<fstream>
using namespace std;
class travelGuide
{
	int count = 0;		//количество оставшихся экземпляров на складе
	int article;		//арткиль будет генерироваться случайным образом на этапе 
	string name;		//название
	string publisher;	//издатель
	int year;			//год выпуска
	int page;			// количество страниц
	bool photo;			// наличие фото
	bool map;			//наличие карт
	string binding;		//переплеты
	string format;		//формат
	string autor;		//автор
	int curculation;	//тираж
public:
	travelGuide(istream& in); // конструктор, входным параметром которого является поток входных данных
	void getGuide();//для вывода на экран
	ostream& save(ostream& out); //для сохранения в файл
	friend class Shop;
	friend class warehouse;
};


class warehouse
{
	vector <travelGuide*> items;
public:
	bool checkProduct(int index);//проверить есть ли продукт
	travelGuide* retProduct(int index);// вернуть продукт магазину
	void setItems(vector<travelGuide*> inItems);// инициализировать товар на складе
	void setCount(travelGuide* tmp);//установить количество товаров
};

class Shop
{
	vector <travelGuide*> items;//база путеводителей
	warehouse* wh = nullptr;// свой собственный склад магазина
	int count = 0; //количество элементов в базе
public:
	vector<travelGuide*>& createShop(istream& in);//создать магазин
	bool checkItem(int index); //возвращает 1, если есть товар с артикулом index
	bool checkItemAvalible(int index);// проверить есть ли товар на складе
	travelGuide* retProduct(int index);// вернуть товар со склада заказчику
	~Shop()
	{
		delete wh;
	}
	friend class Site;
	//должен быть метод возвращающий логическое значение в знак того, что товар найден или не найден
};

// характеристик: название, издательство, год, число страниц, наличие фотографий, наличие карты, переплет, формат, автор, количество.

class Site
{
	fstream fs1;//файл, который будет использоваться, как база первого магазина
	fstream fs2;
	fstream fs3;

	Shop* s1 = nullptr;// указатель на один из магазинов
	Shop* s2 = nullptr;
	Shop* s3 = nullptr;
public:
	void createSite();// создание сайта
	void saveSite();// метод для сохранения сайта
	travelGuide* findGuide(int finde_article); // найти путеводитель
	void getSite();//вывести сайт
	~Site()
	{
		delete s1;
		delete s2;
		delete s3;
	}
	

};
