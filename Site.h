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
	travelGuide(istream& in) // конструктор, входным параметром которого является поток входных данных
	{
		getline(in, name);
		getline(in, name);
		getline(in, publisher);
		getline(in, autor);
		getline(in, binding);
		getline(in, format);
		in >> year;
		in >> page;
		in >> photo;
		in >> map;
		in >> curculation;
		article = rand() % 10000;
	}

	void getGuide()//для вывода на экран
	{
		
		cout << "Название: " + name << endl;
		cout << "Издательство: " + publisher << endl;
		cout << "Автора: " << autor << endl;
		cout << "Год выпуска: " << year << endl;
		cout << "Количество страниц: " << page << endl;
		cout << "Наличие фото: " << photo << endl;
		cout << "Наличие карты: " << map << endl;
		cout << "Переплет: " << binding << endl;
		cout << "Формат: " << format << endl;
		cout << "Тираж: " << curculation << endl;
		cout << "=================================" << endl;
		cout << "Артикль " << article << endl;
	}
	ostream& save(ostream& out) //для сохранения в файл
	{
		out << name << endl;
		out << publisher << endl;
		out << autor << endl;
		out << binding << endl;
		out << format << endl;
		out << year << endl;
		out << page << endl;
		out << photo << endl;
		out << map << endl;
		out << curculation << endl;
		return out;
	}



	friend class Shop;
	friend class warehouse;
};


class warehouse
{
	vector <travelGuide*> items;
public:
	bool checkProduct(int index)
	{
		for (unsigned int i = 0; i < items.size(); i++)
		{
			if (items[i]->article == index)
				return true;
		}
		return false;
	}
	travelGuide* retProduct(int index)
	{
		for (unsigned int i = 0; i < items.size(); i++)
		{
			if (items[i]->article == index && items[i]->count>0)
			{
				items[i]->count--;
				return items[i];
			}
			else if(items[i]->article == index && items[i]->count == 0)
			{
				cerr << "Извините, продукта в наличие пока нет!" << endl;
			}
		}
	}

	void setItems(vector<travelGuide*> inItems)
	{
		items = inItems;
		for (unsigned int i = 0; i < inItems.size(); i++)
		{
			setCount(items[i]);
		}
	}


	void setCount(travelGuide* tmp)
	{
		cout << "Текущее количество товара с артиклем " << tmp->article << " :" << tmp->count << endl;
		cout << "Введите новое количество данного товара: "; cin >> tmp->count;
	}

};

class Shop
{
	vector <travelGuide*> items;
	warehouse* wh = nullptr;
	int count = 0; //количество элементов в базе
public:
	vector<travelGuide*>& createShop(istream& in)
	{
		wh = new warehouse();
		
		in >> count;
		for (unsigned int i = 0; i < count; i++)
		{
			items.push_back(new travelGuide(in));
		}
		wh->setItems(items);
		return items;
	}

	bool checkItem(int index) //возвращает 1, если есть товар с артикулом index
	{
		for (unsigned int i = 0; i < items.size(); i++)
		{
			if (items[i]->article == index)
				return true;
		}
		return false;
	}

	bool checkItemAvalible(int index)
	{
		if (wh->checkProduct(index))
		{
			return true;
		}
		return false;
	}

	travelGuide* retProduct(int index)
	{
		for (unsigned int i = 0; i < items.size(); i++)
		{
			if (items[i]->article == index)
			{
				return wh->retProduct(index);
			}
		}
		cout << "Ошибка, товар не найден." << endl;
		return nullptr;
	}

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
	vector <travelGuide*> magazine;

	fstream fs1;//файл, который будет использоваться, как база первого магазина
	fstream fs2;
	fstream fs3;

	Shop* s1 = nullptr;// указатель на один из магазинов
	Shop* s2 = nullptr;
	Shop* s3 = nullptr;
public:
	void createSite()
	{
		s1 = new Shop();
		s2 = new Shop();
		s3 = new Shop();
		/* Попытка открытия файла с базой первого магазина*/
		try
		{
			fs1.open("shop1.txt", ios_base::in);
			if (!fs1.is_open()) throw "Не удалось открыть файл с базой первого магазина.";
		}
		catch (const char* serr)
		{
			cerr << serr << endl;
			fs1.open("shop1.txt", ios_base::out);
			fs1 << 0 << endl;
			fs1.close();
			fs1.open("shop1.txt", ios_base::in);
		}
		s1->createShop(fs1);
		fs1.close();
		/* Попытка открытия файла с базой второго магазина*/
		try
		{
			fs2.open("shop1.txt", ios_base::in);
			if (!fs2.is_open()) throw "Не удалось открыть файл с базой первого магазина.";
		}
		catch (const char* serr)
		{
			cerr << serr << endl;
			fs2.open("shop1.txt", ios_base::out);
			fs2 << 0 << endl;
			fs2.close();
			fs2.open("shop1.txt", ios_base::in);
		}
		fs2.open("shop2.txt", ios_base::in);
		s2->createShop(fs2);
		fs2.close();

		/* Попытка открытия файла с базой второго магазина*/
		try
		{
			fs3.open("shop1.txt", ios_base::in);
			if (!fs3.is_open()) throw "Не удалось открыть файл с базой первого магазина.";
		}
		catch (const char* serr)
		{
			cerr << serr << endl;
			fs3.open("shop1.txt", ios_base::out);
			fs3 << 0 << endl;
			fs3.close();
			fs3.open("shop1.txt", ios_base::in);
		}
		s3->createShop(fs3);
		fs3.close();

	}
	void saveSite()// метод для сохранения сайта
	{
		fs1.open("shop1.txt", ios_base::out);
		fs1 << s1->count << endl;
		for (unsigned int i = 0; i < s1->items.size(); i++)
		{
			s1->items[i]->save(fs1);
		}
		fs1.close();
		fs2 << s2->count << endl;
		fs2.open("shop2.txt", ios_base::out);
		for (unsigned int i = 0; i < s2->items.size(); i++)
		{
			s2->items[i]->save(fs2);
		}
		fs2.close();
		fs3 << s3->count << endl;
		fs3.open("shop3.txt", ios_base::out);
		for (unsigned int i = 0; i < s3->items.size(); i++)
		{
			s3->items[i]->save(fs3);
		}
		fs3.close();
	}


	travelGuide* findGuide(int finde_article)
	{
		
		if (s1->checkItem(finde_article))
		{
			cout << "Продукт нашелся в магазине " << s1 << ". Идет проверка наличия на складе..." << endl;
			if(s1->checkItemAvalible(finde_article))
			{
				cout << "Товар найден." << endl;
				return s1->retProduct(finde_article);

			}	
			cout << "К сожалению, в наличие товара нет." << endl;
			return nullptr;
		}
		else if (s2->checkItem(finde_article))
		{
			cout << "Продукт нашелся в магазине " << s2 << ". Идет проверка наличия на складе..." << endl;
			if (s2->checkItemAvalible(finde_article))
			{
				return s2->retProduct(finde_article);
			}
			cout << "К сожалению, в наличие товара нет." << endl;
			return nullptr;
		}
		else if (s3->checkItem(finde_article))
		{
			cout << "Продукт нашелся в магазине " << s3 << ". Идет проверка наличия на складе..." << endl;
			if (s3->checkItemAvalible(finde_article))
			{
				return s3->retProduct(finde_article);
			}
			cout << "К сожалению, в наличие товара нет." << endl;
			return nullptr;
		}
		else
		{
			cerr << "Данный путеводитель не был найден ни в одном из магазинов." << endl;
		}
	}

	void getSite()
	{
		cout << "Товары первого магазина: " << endl;
		for (unsigned int i = 0; i < s1->items.size(); i++)
		{
			
			s1->items[i]->getGuide();
		}
		cout << "Товары второго магазина: " << endl;
		for (unsigned int i = 0; i < s2->items.size(); i++)
		{

			s2->items[i]->getGuide();
		}
		cout << "Товары третьего магазина: " << endl;
		for (unsigned int i = 0; i < s3->items.size(); i++)
		{

			s3->items[i]->getGuide();
		}
	}
	~Site()
	{
		delete s1;
		delete s2;
		delete s3;
	}
	//должен быть метод, отправляющий какое то свойство товара одному из магазинов

};





