#include "Site.h"


travelGuide::travelGuide(istream& in) // �����������, ������� ���������� �������� �������� ����� ������� ������
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

void travelGuide::getGuide()//��� ������ �� �����
{

	cout << "��������: " + name << endl;
	cout << "������������: " + publisher << endl;
	cout << "������: " << autor << endl;
	cout << "��� �������: " << year << endl;
	cout << "���������� �������: " << page << endl;
	cout << "������� ����: " << photo << endl;
	cout << "������� �����: " << map << endl;
	cout << "��������: " << binding << endl;
	cout << "������: " << format << endl;
	cout << "�����: " << curculation << endl;
	cout << "=================================" << endl;
	cout << "������� " << article << endl;
}
ostream& travelGuide::save(ostream& out) //��� ���������� � ����
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

bool warehouse::checkProduct(int index)
{
	for (unsigned int i = 0; i < items.size(); i++)
	{
		if (items[i]->article == index)
			return true;
	}
	return false;
}
travelGuide* warehouse::retProduct(int index)
{
	for (unsigned int i = 0; i < items.size(); i++)
	{
		if (items[i]->article == index && items[i]->count > 0)
		{
			items[i]->count--;
			return items[i];
		}
		else if (items[i]->article == index && items[i]->count == 0)
		{
			cerr << "��������, �������� � ������� ���� ���!" << endl;
		}
	}
}

void warehouse::setItems(vector<travelGuide*> inItems)
{
	items = inItems;
	for (unsigned int i = 0; i < inItems.size(); i++)
	{
		setCount(items[i]);
	}
}


void warehouse::setCount(travelGuide* tmp)
{
	cout << "������� ���������� ������ � �������� " << tmp->article << " :" << tmp->count << endl;
	cout << "������� ����� ���������� ������� ������: "; cin >> tmp->count;
}

vector<travelGuide*>& Shop::createShop(istream& in)
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

bool Shop::checkItem(int index) //���������� 1, ���� ���� ����� � ��������� index
{
	for (unsigned int i = 0; i < items.size(); i++)
	{
		if (items[i]->article == index)
			return true;
	}
	return false;
}

bool Shop::checkItemAvalible(int index)
{
	if (wh->checkProduct(index))
	{
		return true;
	}
	return false;
}

travelGuide* Shop::retProduct(int index)
{
	for (unsigned int i = 0; i < items.size(); i++)
	{
		if (items[i]->article == index)
		{
			return wh->retProduct(index);
		}
	}
	cout << "������, ����� �� ������." << endl;
	return nullptr;
}

void Site::createSite()
{
	s1 = new Shop();
	s2 = new Shop();
	s3 = new Shop();
	/* ������� �������� ����� � ����� ������� ��������*/
	try
	{
		fs1.open("shop1.txt", ios_base::in);
		if (!fs1.is_open()) throw "�� ������� ������� ���� � ����� ������� ��������.";
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
	/* ������� �������� ����� � ����� ������� ��������*/
	try
	{
		fs2.open("shop1.txt", ios_base::in);
		if (!fs2.is_open()) throw "�� ������� ������� ���� � ����� ������� ��������.";
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

	/* ������� �������� ����� � ����� ������� ��������*/
	try
	{
		fs3.open("shop1.txt", ios_base::in);
		if (!fs3.is_open()) throw "�� ������� ������� ���� � ����� ������� ��������.";
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
void Site::saveSite()// ����� ��� ���������� �����
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


travelGuide* Site::findGuide(int finde_article)
{

	if (s1->checkItem(finde_article))
	{
		cout << "������� ������� � �������� " << s1 << ". ���� �������� ������� �� ������..." << endl;
		if (s1->checkItemAvalible(finde_article))
		{
			cout << "����� ������." << endl;
			return s1->retProduct(finde_article);

		}
		cout << "� ���������, � ������� ������ ���." << endl;
		return nullptr;
	}
	else if (s2->checkItem(finde_article))
	{
		cout << "������� ������� � �������� " << s2 << ". ���� �������� ������� �� ������..." << endl;
		if (s2->checkItemAvalible(finde_article))
		{
			return s2->retProduct(finde_article);
		}
		cout << "� ���������, � ������� ������ ���." << endl;
		return nullptr;
	}
	else if (s3->checkItem(finde_article))
	{
		cout << "������� ������� � �������� " << s3 << ". ���� �������� ������� �� ������..." << endl;
		if (s3->checkItemAvalible(finde_article))
		{
			return s3->retProduct(finde_article);
		}
		cout << "� ���������, � ������� ������ ���." << endl;
		return nullptr;
	}
	else
	{
		cerr << "������ ������������ �� ��� ������ �� � ����� �� ���������." << endl;
	}
}

void Site::getSite()
{
	cout << "������ ������� ��������: " << endl;
	for (unsigned int i = 0; i < s1->items.size(); i++)
	{

		s1->items[i]->getGuide();
	}
	cout << "������ ������� ��������: " << endl;
	for (unsigned int i = 0; i < s2->items.size(); i++)
	{

		s2->items[i]->getGuide();
	}
	cout << "������ �������� ��������: " << endl;
	for (unsigned int i = 0; i < s3->items.size(); i++)
	{

		s3->items[i]->getGuide();
	}
}