#pragma once

#include<iostream>
#include<string>
#include<vector>
#include<fstream>
using namespace std;
class Site
{
	vector <travelGuide*> magazine;

	fstream fs1;//файл, который будет использоваться, как база первого магазина
	fstream fs2;
	fstream fs3;

	Shop* s1;// указатель на один из магазинов
	Shop* s2;
	Shop* s3;
	void createSite()
	{
		s1 = new Shop();
		s2 = new Shop();
		s3 = new Shop();

		fs1.open("shop1.txt", ios_base::in);
		s1->createShop(cin);
		fs1.close();
		fs2.open("shop2.txt", ios_base::in);
		s2->createShop(cin);
		fs2.close();
		fs3.open("shop3.txt", ios_base::in);
		s3->createShop(cin);
		fs3.close();

	}
	void updateSite()
	{
		int ans;
		cout << "Выберите магазин, который будет обновляться: " << endl;
		cout << "|1| магазин " << s1 << endl;
		cout << "|2| магазин " << s2 << endl;
		cout << "|3| магазин " << s3 << endl;
		switch (ans)
		{
			case 1:
			{
				s1->createShop(cin);
				break;
			}
		}
	}

	void saveSite()// метод для сохранения сайта
	{
		fs1.open("shop1.txt", ios_base::out);
		for (int i = 0; i < s1->items.size(); i++)
		{
			s1->items[i]->save(fs1);
		}
		fs1.close();

		fs2.open("shop2.txt", ios_base::out);
		for (int i = 0; i < s2->items.size(); i++)
		{
			s2->items[i]->save(fs2);
		}
		fs2.close();

		fs3.open("shop3.txt", ios_base::out);
		for (int i = 0; i < s3->items.size(); i++)
		{
			s3->items[i]->save(fs3);
		}
		fs3.close();
	}

	void deleteGuid(int index)
	{
		magazine.erase(magazine.begin() + index);
	}

	void findGuide(int finde_article)
	{
		
	}
	//должен быть метод, отправляющий какое то свойство товара одному из магазинов

};

class Shop
{
	vector <travelGuide*> items;
public:
	vector<travelGuide*>& createShop(istream& in)
	{
		int answer;
		while (1)
		{
			cout << "Создается магазин " << this << " нужно пополнить список товаров. Выберите операцию: " << endl;
			cout << "|1| - добавить новый путеводитель" << endl;
			cout << "|2| - выйти" << endl;
			cin >> answer;
			if (answer == 1)
			{
				items.push_back(new travelGuide(in));
			}
			else
			{
				break;
			}
		}
		return items;
	}

	bool retItem(int index) //возвращает 1, если есть товар с артикулом index
	{
		for (int i = 0; i < items.size(); i++)
		{
			if (items[i]->article == index)
				return true;
		}
		return false;
	}
	friend class Site;
	//должен быть метод возвращающий логическое значение в знак того, что товар найден или не найден
};


// склад !надо доработать!
class warehouse
{
	vector <travelGuide*> shop;

	bool chekProduct(int index)
	{
		for (int i = 0; i < shop.size(); i++)
		{
			if (shop[i]->article == index)
				return true;
		}
		return false;
	}
	travelGuide* retProduct(int index)
	{
		for (int i = 0; i < shop.size(); i++)
		{
			if (shop[i]->article == index)
				return shop[i];
		}
	}

};
// характеристик: название, издательство, год, число страниц, наличие фотографий, наличие карты, переплет, формат, автор, количество.
class travelGuide
{

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
		cout << "Введите название: ";
		getline(in,name);
		cout << endl;

		cout << "Введите издательство: ";
		getline(in, publisher);
		cout << endl;

		cout << "Введите автора: ";
		getline(in, autor);
		cout << endl;

		cout << "Введите год выпуска: ";
		in >> year;
		cout << endl;

		cout << "Введите количество страниц: ";
		in >> page;
		cout << endl;

		cout << "Введите 0, если нет фото, 1 - если есть: ";
		in >> photo;
		cout << endl;

		cout << "Введите 0, если нет карты, 1 - если есть: ";
		in >> map;
		cout << endl;

		cout << "Введите переплет: ";
		getline(in, binding);
		cout << endl;

		cout << "Введите формат: ";
		getline(in, format);
		cout << endl;

		cout << "Введите тираж: ";
		in >> curculation;
		cout << endl;
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
	}
	ostream& save(ostream& out) //для сохранения в файл
	{
		cout <<  name << endl;
		cout <<  publisher << endl;
		cout <<  autor << endl;
		cout <<  year << endl;
		cout <<  page << endl;
		cout <<  photo << endl;
		cout  << map << endl;
		cout <<  binding << endl;
		cout <<  format << endl;
		cout <<  curculation << endl;
	}

	friend class Shop;
	friend class warehouse;
};
