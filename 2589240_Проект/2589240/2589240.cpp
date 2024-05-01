// Найти три треугольника с вершинами в заданном множестве из n точек на
// плоскости так, чтобы второй треугольник лежал строго внутри первого, а
// третий внутри второго.

#include <iostream>
#include <Windows.h>
#include <fstream>
#include<array>

using namespace std;

//структура точка
struct Point
{
	double x, y;
};

//ввод массива с клавиатуры
pair<Point*, int> Rkey()
{
	int n;
	cout << endl << "Введите количество точек в массиве:  ";
	cin >> n;
	Point* mas = new Point[n];
	cout << endl;
	for (int i = 0; i < n; i++)
	{
		cout << "Введите x и y точки ["<<i+1<<"]: ";
		cin >> mas[i].x;
		cin >> mas[i].y;
	}
	return make_pair(mas, n);
}

//ввод массива с файла
pair<Point*, int> Rfile()
{
	ifstream fin("input.txt");
	int N, k;
	int A[1000];
	Point* mas;
	if (!fin.good())
	{
		cout << "Файл input.txt не найден!" << endl;
	}
	else
	{
		k = 0;
		while (fin >> N)
		{
			A[k++] = N;
		}
		mas = new Point[k / 2];
		for (int i = 0; i < k; i += 2)
		{
			mas[i / 2].x = A[i];
			mas[i / 2].y = A[i + 1];
		}
		fin.close();
		return make_pair(mas, k / 2);
	}
	fin.close();
	return make_pair(mas, 0);
}

//вывод массива точек
void writeP(Point* mas,int n)
{
	cout << "Входной массив точек:" << endl;
	for (int i = 0; i <n; i++)
	{
		cout << "[" << mas[i].x << "; " << mas[i].y << "]    ";
	}
	cout << endl;
}
//являются ли три точки треугольником
bool trian(Point a, Point b, Point c)
{
	double lab, lac, lbc;
	lab = sqrt(pow((a.x - b.x), 2) + pow((a.y - b.y), 2));
	lac = sqrt(pow((a.x - c.x), 2) + pow((a.y - c.y), 2));
	lbc = sqrt(pow((b.x - c.x), 2) + pow((b.y - c.y), 2));
	if (lab + lac > lbc)
		return true;
	else
		if (lab + lbc > lac)
			return true;
		else
			if (lac + lbc > lab)
				return true;
			else
				return false;
}

bool IsPIn_(Point a, Point b, Point c, Point p)
{
	int af = (a.x - p.x) * (b.y - a.y) - (b.x - a.x) * (a.y - p.y);
	int bf = (b.x - p.x) * (c.y - b.y) - (c.x - b.x) * (b.y - p.y);
	int cf = (c.x - p.x) * (a.y - c.y) - (a.x - c.x) * (c.y - p.y);

	if ((af > 0 && bf > 0 && cf > 0) || (af < 0 && bf < 0 && cf < 0))
	{
		return true;
	}
	else
	{
		return false;
	}
}

//поиск трех вложенных треугольников
void serh(Point* mas, int n)
{
	int trian1[3];
	int trian2[3];
	int trian3[3];
	bool ress = false;
	//первый треугольник
	for (int i1 = 0; i1 < n - 2; i1++)
	{
		for (int j1 = i1+1; j1 < n - 1; j1++)
		{
			for (int k1 = j1+1; k1 < n; k1++)
			{
				if (trian(mas[i1], mas[j1], mas[k1]))
				{
					//Первы треугольник найден
					trian1[0] = i1; trian1[1] = j1; trian1[2] = k1;
					//поиск второго треугольника
					for (int i2 = 0; i2 < n-2 ; i2++)
					{
						if (IsPIn_(mas[trian1[0]], mas[trian1[1]], mas[trian1[2]], mas[i2])
							&& (i2 !=i1 ) && i2!=j1 &&i2!=k1)
						{
							for (int j2 = i2 + 1; j2 < n - 1; j2++)
							{
								if (IsPIn_(mas[trian1[0]], mas[trian1[1]], mas[trian1[2]], mas[j2])
									&& (j2 != i1) && j2 != j1 && j2 != k1)
								{
									for (int k2 = j2 + 1; k2 < n; k2++)
									{
										if (IsPIn_(mas[trian1[0]], mas[trian1[1]], mas[trian1[2]], mas[k2])
											&& (k2 != i1) && k2 != j1 && k2 != k1)
										{
											if (trian(mas[i2], mas[j2], mas[k2]))
											{
												//Второй треугольник найден
												trian2[0] = i2; trian2[1] = j2; trian2[2] = k2;
												//Поиск третьего треугольника
												for (int i3 = 0; i3 < n - 2; i3++)
												{
													if (IsPIn_(mas[trian2[0]], mas[trian2[1]], mas[trian2[2]], mas[i3])
														&& (i3 != i2) && i3 != j2 && i3 != k2)
													{
														for (int j3 = i3 + 1; j3 < n - 1; j3++)
														{
															if (IsPIn_(mas[trian2[0]], mas[trian2[1]], mas[trian2[2]], mas[j3])
																&& (j3 != i2) && j3 != j2 && j3 != k2)
															{
																for (int k3 = j3 + 1; k3 < n; k3++)
																{
																	if (IsPIn_(mas[trian2[0]], mas[trian2[1]], mas[trian2[2]], mas[k3])
																		&& (k3 != i2) && k3 != j2 && k3 != k2)
																	{
																		if (trian(mas[i3], mas[j3], mas[k3]))
																		{
																			ress = true;
																			//Второй треугольник найден
																			trian3[0] = i3; trian3[1] = j3; trian3[2] = k3;
																			cout << "===============================================" << endl;
																			cout << "Вершины первого треугольника имеют координаты:" << endl;
																			cout << "[{" << mas[trian1[0]].x << " " << mas[trian1[0]].y <<
																				"}{" << mas[trian1[1]].x << " " << mas[trian1[1]].y <<
																				"}{" << mas[trian1[2]].x << " " << mas[trian1[2]].y << "}]" << endl;

																			cout << "Вершины второго треугольника имеют координаты:" << endl;
																			cout << "[{" << mas[trian2[0]].x << " " << mas[trian2[0]].y <<
																				"}{" << mas[trian2[1]].x << " " << mas[trian2[1]].y <<
																				"}{" << mas[trian2[2]].x << " " << mas[trian2[2]].y << "}]" << endl;

																			cout << "Вершины третьего треугольника имеют координаты:" << endl;
																			cout << "[{" << mas[trian3[0]].x << " " << mas[trian3[0]].y <<
																				"}{" << mas[trian3[1]].x << " " << mas[trian3[1]].y <<
																				"}{" << mas[trian3[2]].x << " " << mas[trian3[2]].y << "}]" << endl;
																		}
																	}
																}
															}
														}
													}

												}
											}
										}
									}
								}
							}
						}

					}
				}
			}
		}
	}
	if (!ress)
	{
		cout << "Нет треугольников, удовлетворяющих условию" << endl;
	}
}

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	Point* masP;
	int n;
	cout << "Задание:" << endl;
	cout << "Найти три треугольника с вершинами в заданном множестве из n точек на" << endl;
	cout << "плоскости так, чтобы второй треугольник лежал строго внутри первого, а" << endl;
	cout << "третий внутри второго." << endl << endl;

	cout << "Выберете способ загрузки масива точек:" << endl;
	cout << "  1. Ввод из файла." << endl;
	cout << "  2. Ввод с клавиатуры." << endl;
	int choise;
	cin >> choise;
	switch (choise)
	{
	case 1:
	{
		pair< Point*, int > p = Rfile();
		masP = p.first;
		n = p.second;
		break;
	}
	case 2:
	{
		pair< Point*, int > p = Rkey();
		masP = p.first;
		n = p.second;
		break;
	}
	default:
		masP = NULL;
		break;
	}
	system("cls");

	cout << "Задание:" << endl;
	cout << "Найти три треугольника с вершинами в заданном множестве из n точек на" << endl;
	cout << "плоскости так, чтобы второй треугольник лежал строго внутри первого, а" << endl;
	cout << "третий внутри второго." << endl << endl;

	writeP(masP,n);
	serh(masP, n);
	system("pause");
	return 0;
}