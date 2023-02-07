#include <iostream>
#include <random>
#include <cstdlib>
#include <typeinfo>
#include <cstring>


using namespace std;
//структура поле, рисует поле, высчитывает координаты активного поля, запись в массив в формате 67х22 (1474)
struct POLE
{
	//рисунок поля: 
	char num_0 = 48;
	char num_1 = 49;
	char num = 49;		//57
	char letter = 65;//90
	char prob = { ' ' };
	char palka = { '|' };
	char tire = { '-' };
	char miss = { 'x' }; //мимо
	char hit = { 'O' };	//ранил\убил
	char ship = { '@' };

	//массив поля: 
	char mass_pole[1474]{};	//все занимаемое пространство


	//массив активных позиций
	int mass_activ_pole[100]{};			//позиции где будет сражение


	void creat_pole();//создание поля
	void show_pole();	//вывод поля на экран
	void show_pole_rasstanovka(int* massiv_coord);//заполненое короблями поле
	void poisk_activ();//поиск активных позиций
	void proverka_activ();//проверка активных позиций





};

//структура ships координаты кораблей в формате 10х10(100) (позиция с учетом на Х-1) 
struct ships
{	//однопоалубные
	int one_1{ 11 };
	int one_2{ 18 };
	int one_3{ 32 };
	int one_4{ 51 };
	//двупалубные
	int two_1[2]{ 14,15 };
	int two_2[2]{ 45,55 };
	int two_3[2]{ 77,78 };
	//трехпалубные
	int three_1[3]{ 37,47,57 };
	int three_2[3]{ 39,49,59 };
	//четырехпалубные
	int four[4]{ 70,71,72,73 };

	int pozicion[20]
	{
	 one_1,one_2,one_3,one_4,
	 two_1[0],two_1[1],two_2[0],two_2[1],two_3[0],two_3[1],
	 three_1[0],three_1[1],three_1[2],three_2[0],three_2[1],three_2[2],
	 four[0],four[1], four[2], four[3]
	};


};
/// структура введенные координаты
struct activ
{
	char A = 'A'; //1
	char B = 'B'; //2
	char C = 'C'; //3
	char D = 'D'; //4
	char E = 'E'; //5
	char F = 'F'; //6
	char G = 'G'; //7
	char H = 'H'; //8
	char I = 'I'; //9
	char J = 'J'; //10

	int preobraz_vvoda(char vvod_char, int vvod_int)
	{

		if (vvod_char == A)
		{
			vvod_int += 0;
		}
		else if (vvod_char == B)
		{
			vvod_int += 10;
		}
		else if (vvod_char == C)
		{
			vvod_int += 20;
		}
		else if (vvod_char == D)
		{
			vvod_int += 30;
		}
		else if (vvod_char == E)
		{
			vvod_int += 40;
		}
		else if (vvod_char == F)
		{
			vvod_int += 50;
		}
		else if (vvod_char == G)
		{
			vvod_int += 60;
		}
		else if (vvod_char == H)
		{
			vvod_int += 70;
		}
		else if (vvod_char == I)
		{
			vvod_int += 80;
		}
		else if (vvod_char == J)
		{
			vvod_int += 90;
		}

		return vvod_int - 1;
	}

};
//функция преобразовывает из 10х10 в 22х67 координаты МАССИВА КООРДИНАТ КОРАБЛЕЙ, соотносит с полем
int& poz_in_map(ships newship, POLE newpole, int* mass_22x67)
{


	for (int i = 0; i < 20; ++i)
	{
		mass_22x67[i] = newpole.mass_activ_pole[newship.pozicion[i]];		//преобразование из 10х10 в 22х67
	}

	//сортировка по нарастанию
	int tmp = 0;
	for (size_t i = 0; i < 20; i++)
	{
		for (size_t j = (19); j >= (i + 1); j--)
		{
			if (mass_22x67[j] < mass_22x67[j - 1])
			{
				tmp = mass_22x67[j];
				mass_22x67[j] = mass_22x67[j - 1];
				mass_22x67[j - 1] = tmp;
			}
		}
	}
	return *mass_22x67;
};


//функция преобразовывает из 10х10 в 22х67 координаты ОДНОЙ КООРДИНАТЫ
int preobr_10x10_to_22x67(POLE newpole, int coord_10x10)
{
	int coord_22x67{};
	coord_22x67 = newpole.mass_activ_pole[coord_10x10];		//преобразование из 10х10 в 22х67
	return coord_22x67;
}
//функция раставляет miss вокруг убитых кораблей
void ubil(POLE& pole, ships ship, int vibor)
{
	//1_1
	if (vibor == 1)
	{
		pole.mass_pole[preobr_10x10_to_22x67(pole, ship.one_1 + 1)] = pole.miss;
		pole.mass_pole[preobr_10x10_to_22x67(pole, ship.one_1 + 9)] = pole.miss;
		pole.mass_pole[preobr_10x10_to_22x67(pole, ship.one_1 + 10)] = pole.miss;
		pole.mass_pole[preobr_10x10_to_22x67(pole, ship.one_1 + 11)] = pole.miss;
		pole.mass_pole[preobr_10x10_to_22x67(pole, ship.one_1 - 1)] = pole.miss;
		pole.mass_pole[preobr_10x10_to_22x67(pole, ship.one_1 - 9)] = pole.miss;
		pole.mass_pole[preobr_10x10_to_22x67(pole, ship.one_1 - 10)] = pole.miss;
		pole.mass_pole[preobr_10x10_to_22x67(pole, ship.one_1 - 11)] = pole.miss;
	}
	//1_2
	if (vibor == 2)
	{
		pole.mass_pole[preobr_10x10_to_22x67(pole, ship.one_2 + 1)] = pole.miss;
		pole.mass_pole[preobr_10x10_to_22x67(pole, ship.one_2 + 9)] = pole.miss;
		pole.mass_pole[preobr_10x10_to_22x67(pole, ship.one_2 + 10)] = pole.miss;
		pole.mass_pole[preobr_10x10_to_22x67(pole, ship.one_2 + 11)] = pole.miss;
		pole.mass_pole[preobr_10x10_to_22x67(pole, ship.one_2 - 1)] = pole.miss;
		pole.mass_pole[preobr_10x10_to_22x67(pole, ship.one_2 - 9)] = pole.miss;
		pole.mass_pole[preobr_10x10_to_22x67(pole, ship.one_2 - 10)] = pole.miss;
		pole.mass_pole[preobr_10x10_to_22x67(pole, ship.one_2 - 11)] = pole.miss;
	}
	//1_3
	if (vibor == 3)
	{
		pole.mass_pole[preobr_10x10_to_22x67(pole, ship.one_3 + 1)] = pole.miss;
		pole.mass_pole[preobr_10x10_to_22x67(pole, ship.one_3 + 9)] = pole.miss;
		pole.mass_pole[preobr_10x10_to_22x67(pole, ship.one_3 + 10)] = pole.miss;
		pole.mass_pole[preobr_10x10_to_22x67(pole, ship.one_3 + 11)] = pole.miss;
		pole.mass_pole[preobr_10x10_to_22x67(pole, ship.one_3 - 1)] = pole.miss;
		pole.mass_pole[preobr_10x10_to_22x67(pole, ship.one_3 - 9)] = pole.miss;
		pole.mass_pole[preobr_10x10_to_22x67(pole, ship.one_3 - 10)] = pole.miss;
		pole.mass_pole[preobr_10x10_to_22x67(pole, ship.one_3 - 11)] = pole.miss;
	}
	//1_4
	if (vibor == 4)
	{
		pole.mass_pole[preobr_10x10_to_22x67(pole, ship.one_4 + 1)] = pole.miss;
		pole.mass_pole[preobr_10x10_to_22x67(pole, ship.one_4 + 9)] = pole.miss;
		pole.mass_pole[preobr_10x10_to_22x67(pole, ship.one_4 + 10)] = pole.miss;
		pole.mass_pole[preobr_10x10_to_22x67(pole, ship.one_4 + 11)] = pole.miss;
		pole.mass_pole[preobr_10x10_to_22x67(pole, ship.one_4 - 1)] = pole.miss;
		pole.mass_pole[preobr_10x10_to_22x67(pole, ship.one_4 - 9)] = pole.miss;
		pole.mass_pole[preobr_10x10_to_22x67(pole, ship.one_4 - 10)] = pole.miss;
		pole.mass_pole[preobr_10x10_to_22x67(pole, ship.one_4 - 11)] = pole.miss;
	}
	//2_1
	if (vibor == 5)
	{
		pole.mass_pole[preobr_10x10_to_22x67(pole, ship.two_1[0] + 9)] = pole.miss;
		pole.mass_pole[preobr_10x10_to_22x67(pole, ship.two_1[0] + 10)] = pole.miss;
		pole.mass_pole[preobr_10x10_to_22x67(pole, ship.two_1[0] + 11)] = pole.miss;
		pole.mass_pole[preobr_10x10_to_22x67(pole, ship.two_1[0] - 1)] = pole.miss;
		pole.mass_pole[preobr_10x10_to_22x67(pole, ship.two_1[0] - 9)] = pole.miss;
		pole.mass_pole[preobr_10x10_to_22x67(pole, ship.two_1[0] - 10)] = pole.miss;
		pole.mass_pole[preobr_10x10_to_22x67(pole, ship.two_1[0] - 11)] = pole.miss;

		pole.mass_pole[preobr_10x10_to_22x67(pole, ship.two_1[1] + 1)] = pole.miss;
		pole.mass_pole[preobr_10x10_to_22x67(pole, ship.two_1[1] + 9)] = pole.miss;
		pole.mass_pole[preobr_10x10_to_22x67(pole, ship.two_1[1] + 10)] = pole.miss;
		pole.mass_pole[preobr_10x10_to_22x67(pole, ship.two_1[1] + 11)] = pole.miss;
		pole.mass_pole[preobr_10x10_to_22x67(pole, ship.two_1[1] - 9)] = pole.miss;
		pole.mass_pole[preobr_10x10_to_22x67(pole, ship.two_1[1] - 10)] = pole.miss;
		pole.mass_pole[preobr_10x10_to_22x67(pole, ship.two_1[1] - 11)] = pole.miss;
	}
	//2_2
	if (vibor == 6)
	{
		pole.mass_pole[preobr_10x10_to_22x67(pole, ship.two_2[0] + 1)] = pole.miss;
		pole.mass_pole[preobr_10x10_to_22x67(pole, ship.two_2[0] + 9)] = pole.miss;
		pole.mass_pole[preobr_10x10_to_22x67(pole, ship.two_2[0] + 11)] = pole.miss;
		pole.mass_pole[preobr_10x10_to_22x67(pole, ship.two_2[0] - 1)] = pole.miss;
		pole.mass_pole[preobr_10x10_to_22x67(pole, ship.two_2[0] - 9)] = pole.miss;
		pole.mass_pole[preobr_10x10_to_22x67(pole, ship.two_2[0] - 10)] = pole.miss;
		pole.mass_pole[preobr_10x10_to_22x67(pole, ship.two_2[0] - 11)] = pole.miss;

		pole.mass_pole[preobr_10x10_to_22x67(pole, ship.two_2[1] + 1)] = pole.miss;
		pole.mass_pole[preobr_10x10_to_22x67(pole, ship.two_2[1] + 9)] = pole.miss;
		pole.mass_pole[preobr_10x10_to_22x67(pole, ship.two_2[1] + 10)] = pole.miss;
		pole.mass_pole[preobr_10x10_to_22x67(pole, ship.two_2[1] + 11)] = pole.miss;
		pole.mass_pole[preobr_10x10_to_22x67(pole, ship.two_2[1] - 1)] = pole.miss;
		pole.mass_pole[preobr_10x10_to_22x67(pole, ship.two_2[1] - 9)] = pole.miss;
		pole.mass_pole[preobr_10x10_to_22x67(pole, ship.two_2[1] - 11)] = pole.miss;
	}
	//2_3
	if (vibor == 7)
	{

		pole.mass_pole[preobr_10x10_to_22x67(pole, ship.two_3[0] + 9)] = pole.miss;
		pole.mass_pole[preobr_10x10_to_22x67(pole, ship.two_3[0] + 10)] = pole.miss;
		pole.mass_pole[preobr_10x10_to_22x67(pole, ship.two_3[0] + 11)] = pole.miss;
		pole.mass_pole[preobr_10x10_to_22x67(pole, ship.two_3[0] - 1)] = pole.miss;
		pole.mass_pole[preobr_10x10_to_22x67(pole, ship.two_3[0] - 9)] = pole.miss;
		pole.mass_pole[preobr_10x10_to_22x67(pole, ship.two_3[0] - 10)] = pole.miss;
		pole.mass_pole[preobr_10x10_to_22x67(pole, ship.two_3[0] - 11)] = pole.miss;

		pole.mass_pole[preobr_10x10_to_22x67(pole, ship.two_3[1] + 1)] = pole.miss;
		pole.mass_pole[preobr_10x10_to_22x67(pole, ship.two_3[1] + 9)] = pole.miss;
		pole.mass_pole[preobr_10x10_to_22x67(pole, ship.two_3[1] + 10)] = pole.miss;
		pole.mass_pole[preobr_10x10_to_22x67(pole, ship.two_3[1] + 11)] = pole.miss;
		pole.mass_pole[preobr_10x10_to_22x67(pole, ship.two_3[1] - 9)] = pole.miss;
		pole.mass_pole[preobr_10x10_to_22x67(pole, ship.two_3[1] - 10)] = pole.miss;
		pole.mass_pole[preobr_10x10_to_22x67(pole, ship.two_3[1] - 11)] = pole.miss;
	}
	//3_1
	if (vibor == 8)
	{
		pole.mass_pole[preobr_10x10_to_22x67(pole, ship.three_1[0] + 1)] = pole.miss;
		pole.mass_pole[preobr_10x10_to_22x67(pole, ship.three_1[0] + 9)] = pole.miss;
		pole.mass_pole[preobr_10x10_to_22x67(pole, ship.three_1[0] + 11)] = pole.miss;
		pole.mass_pole[preobr_10x10_to_22x67(pole, ship.three_1[0] - 1)] = pole.miss;
		pole.mass_pole[preobr_10x10_to_22x67(pole, ship.three_1[0] - 9)] = pole.miss;
		pole.mass_pole[preobr_10x10_to_22x67(pole, ship.three_1[0] - 10)] = pole.miss;
		pole.mass_pole[preobr_10x10_to_22x67(pole, ship.three_1[0] - 11)] = pole.miss;

		pole.mass_pole[preobr_10x10_to_22x67(pole, ship.three_1[1] + 1)] = pole.miss;
		pole.mass_pole[preobr_10x10_to_22x67(pole, ship.three_1[1] + 9)] = pole.miss;
		pole.mass_pole[preobr_10x10_to_22x67(pole, ship.three_1[1] + 11)] = pole.miss;
		pole.mass_pole[preobr_10x10_to_22x67(pole, ship.three_1[1] - 1)] = pole.miss;
		pole.mass_pole[preobr_10x10_to_22x67(pole, ship.three_1[1] - 9)] = pole.miss;
		pole.mass_pole[preobr_10x10_to_22x67(pole, ship.three_1[1] - 11)] = pole.miss;

		pole.mass_pole[preobr_10x10_to_22x67(pole, ship.three_1[2] + 1)] = pole.miss;
		pole.mass_pole[preobr_10x10_to_22x67(pole, ship.three_1[2] + 9)] = pole.miss;
		pole.mass_pole[preobr_10x10_to_22x67(pole, ship.three_1[2] + 10)] = pole.miss;
		pole.mass_pole[preobr_10x10_to_22x67(pole, ship.three_1[2] + 11)] = pole.miss;
		pole.mass_pole[preobr_10x10_to_22x67(pole, ship.three_1[2] - 1)] = pole.miss;
		pole.mass_pole[preobr_10x10_to_22x67(pole, ship.three_1[2] - 9)] = pole.miss;
		pole.mass_pole[preobr_10x10_to_22x67(pole, ship.three_1[2] - 11)] = pole.miss;

	}
	//3_2
	if (vibor == 9)
	{


		pole.mass_pole[preobr_10x10_to_22x67(pole, ship.three_2[0] + 9)] = pole.miss;
		pole.mass_pole[preobr_10x10_to_22x67(pole, ship.three_2[0] - 1)] = pole.miss;
		pole.mass_pole[preobr_10x10_to_22x67(pole, ship.three_2[0] - 10)] = pole.miss;
		pole.mass_pole[preobr_10x10_to_22x67(pole, ship.three_2[0] - 11)] = pole.miss;


		pole.mass_pole[preobr_10x10_to_22x67(pole, ship.three_2[1] + 9)] = pole.miss;
		pole.mass_pole[preobr_10x10_to_22x67(pole, ship.three_2[1] - 1)] = pole.miss;
		pole.mass_pole[preobr_10x10_to_22x67(pole, ship.three_2[1] - 11)] = pole.miss;


		pole.mass_pole[preobr_10x10_to_22x67(pole, ship.three_2[2] + 9)] = pole.miss;
		pole.mass_pole[preobr_10x10_to_22x67(pole, ship.three_2[2] + 10)] = pole.miss;
		pole.mass_pole[preobr_10x10_to_22x67(pole, ship.three_2[2] - 1)] = pole.miss;
		pole.mass_pole[preobr_10x10_to_22x67(pole, ship.three_2[2] - 11)] = pole.miss;

	}
	//4
	if (vibor == 10)
	{


		pole.mass_pole[preobr_10x10_to_22x67(pole, ship.four[0] + 10)] = pole.miss;
		pole.mass_pole[preobr_10x10_to_22x67(pole, ship.four[0] + 11)] = pole.miss;
		pole.mass_pole[preobr_10x10_to_22x67(pole, ship.four[0] - 9)] = pole.miss;
		pole.mass_pole[preobr_10x10_to_22x67(pole, ship.four[0] - 10)] = pole.miss;


		pole.mass_pole[preobr_10x10_to_22x67(pole, ship.four[1] + 9)] = pole.miss;
		pole.mass_pole[preobr_10x10_to_22x67(pole, ship.four[1] + 10)] = pole.miss;
		pole.mass_pole[preobr_10x10_to_22x67(pole, ship.four[1] + 11)] = pole.miss;
		pole.mass_pole[preobr_10x10_to_22x67(pole, ship.four[1] - 9)] = pole.miss;
		pole.mass_pole[preobr_10x10_to_22x67(pole, ship.four[1] - 10)] = pole.miss;
		pole.mass_pole[preobr_10x10_to_22x67(pole, ship.four[1] - 11)] = pole.miss;

		pole.mass_pole[preobr_10x10_to_22x67(pole, ship.four[2] + 9)] = pole.miss;
		pole.mass_pole[preobr_10x10_to_22x67(pole, ship.four[2] + 10)] = pole.miss;
		pole.mass_pole[preobr_10x10_to_22x67(pole, ship.four[2] + 11)] = pole.miss;
		pole.mass_pole[preobr_10x10_to_22x67(pole, ship.four[2] - 9)] = pole.miss;
		pole.mass_pole[preobr_10x10_to_22x67(pole, ship.four[2] - 10)] = pole.miss;
		pole.mass_pole[preobr_10x10_to_22x67(pole, ship.four[2] - 11)] = pole.miss;

		pole.mass_pole[preobr_10x10_to_22x67(pole, ship.four[3] + 1)] = pole.miss;
		pole.mass_pole[preobr_10x10_to_22x67(pole, ship.four[3] + 9)] = pole.miss;
		pole.mass_pole[preobr_10x10_to_22x67(pole, ship.four[3] + 10)] = pole.miss;
		pole.mass_pole[preobr_10x10_to_22x67(pole, ship.four[3] + 11)] = pole.miss;
		pole.mass_pole[preobr_10x10_to_22x67(pole, ship.four[3] - 9)] = pole.miss;
		pole.mass_pole[preobr_10x10_to_22x67(pole, ship.four[3] - 10)] = pole.miss;
		pole.mass_pole[preobr_10x10_to_22x67(pole, ship.four[3] - 11)] = pole.miss;

	}
}

int main()
{
	setlocale(LC_ALL, "ru");
	//тест
	/*POLE newPole3;
	ships newShips3;
	int coord_10x103{};
	int coord_22x673{};
	int mass_coord_22x673[20]{};





	newPole.creat_pole();
	newPole.poisk_activ();
	poz_in_map(newShips3, newPole3, mass_coord_22x673);
	newPole.show_pole_rasstanovka(mass_coord_22x673);
	cout << endl;
*/



//игра

	cout << "\n                  ДОБРО ПОЖАЛОВАТЬ В ИГРУ МОРСКОЙ БОЙ        \n";
	int diff{};
	int vihod{};
	cout << "\n               ВЫБИРИТЕ СЛОЖНОСТЬ                    \n";
	cout << "ЛЕГКО(100 попыток)............введите 1\n";
	cout << "НОРМАЛЬНО(50 попыток).........введите 2\n";
	cout << "СЛОЖНО(30 попыток)............введите 3\n";
	cin >> diff;


	switch (diff)
	{
	case 1:
		vihod = 100;
		break;
	case 2:
		vihod = 50;
		break;
	case 3:
		vihod = 30;
		break;
	}
	POLE newPole;
	newPole.creat_pole();
	newPole.show_pole();
	cout << endl;
	POLE newPole2;
	ships newShips2;
	activ vvod_user;
	int vvod_num_2{};
	char vvod_letter_2{};

	int coord_10x10_2{};
	int coord_22x67_2{};
	int mass_coord_22x67_2[20]{};
	int proverka = 0;
	int coord_miss = 0;
	int count_kill{};

	//проверки на ранили или убил
	int two_1_pr = 0;
	int two_2_pr = 0;
	int two_3_pr = 0;
	int three_1_pr = 0;
	int three_2_pr = 0;
	int four_pr = 0;


	newPole2.creat_pole();
	newPole2.poisk_activ();
	poz_in_map(newShips2, newPole2, mass_coord_22x67_2);
	cout << endl;

	while (vihod > 0)
	{
		cout << "\n=================================ВВОД ПОЛЬЗОВАТЕЛЕМ============================================\n";
		
		cout << "\nВведите букву\n";
		cin >> vvod_letter_2;
		if(vvod_letter_2)
		cout << "\nВведите цифру\n";
		cin >> vvod_num_2;
		vvod_user.preobraz_vvoda(vvod_letter_2, vvod_num_2);
		coord_10x10_2 = vvod_user.preobraz_vvoda(vvod_letter_2, vvod_num_2);
		coord_22x67_2 = preobr_10x10_to_22x67(newPole2, coord_10x10_2);

		for (int i = 0; i < 20; ++i)
		{
			if (coord_22x67_2 == mass_coord_22x67_2[i])
			{
				proverka = 1;
			}
		}
		if (proverka == 1)
		{
			cout << "\n---===ПОПАЛ!===---\n";
			if (coord_10x10_2 == newShips2.one_1)
			{
				cout << "\n---===УБИЛ!===---\n";
				ubil(newPole2, newShips2, 1);
				count_kill++;

			}
			if (coord_10x10_2 == newShips2.one_2)
			{
				cout << "\n---===УБИЛ!===---\n";
				ubil(newPole2, newShips2, 2);
				count_kill++;
			}
			if (coord_10x10_2 == newShips2.one_3)
			{
				cout << "\n---===УБИЛ!===---\n";
				ubil(newPole2, newShips2, 3);
				count_kill++;
			}
			if (coord_10x10_2 == newShips2.one_4)
			{
				cout << "\n---===УБИЛ!===---\n";
				ubil(newPole2, newShips2, 4);
				count_kill++;
			}

			if (coord_10x10_2 == newShips2.two_1[0] || coord_10x10_2 == newShips2.two_1[1])
			{
				cout << "\n---===РАНИЛ!===---\n";
				++two_1_pr;
				if (two_1_pr == 2)
				{
					cout << "\n---===УБИЛ!===---\n";
					ubil(newPole2, newShips2, 5);
					count_kill++;
				}
			}
			if (coord_10x10_2 == newShips2.two_2[0] || coord_10x10_2 == newShips2.two_2[1])
			{
				cout << "\n---===РАНИЛ!===---\n";
				++two_2_pr;
				if (two_2_pr == 2)
				{
					cout << "\n---===УБИЛ!===---\n";
					ubil(newPole2, newShips2, 6);
					count_kill++;
				}
			}
			if (coord_10x10_2 == newShips2.two_3[0] || coord_10x10_2 == newShips2.two_3[1])
			{
				cout << "\n---===РАНИЛ!===---\n";
				++two_3_pr;
				if (two_3_pr == 2)
				{
					cout << "\n---===УБИЛ!===---\n";
					ubil(newPole2, newShips2, 7);
					count_kill++;
				}
			}
			if (coord_10x10_2 == newShips2.three_1[0] || coord_10x10_2 == newShips2.three_1[1] || coord_10x10_2 == newShips2.three_1[2])
			{
				cout << "\n---===РАНИЛ!===---\n";
				++three_1_pr;
				if (three_1_pr == 3)
				{
					cout << "\n---===УБИЛ!===---\n";
					ubil(newPole2, newShips2, 8);
					count_kill++;
				}
			}
			if (coord_10x10_2 == newShips2.three_2[0] || coord_10x10_2 == newShips2.three_2[1] || coord_10x10_2 == newShips2.three_2[2])
			{
				cout << "\n---===РАНИЛ!===---\n";
				++three_2_pr;
				if (three_2_pr == 3)
				{
					cout << "\n---===УБИЛ!===---\n";
					ubil(newPole2, newShips2, 9);
					count_kill++;
				}
			}
			if (coord_10x10_2 == newShips2.four[0] || coord_10x10_2 == newShips2.four[1] || coord_10x10_2 == newShips2.four[2] || coord_10x10_2 == newShips2.four[3])
			{
				cout << "\n---===РАНИЛ!===---\n";
				++four_pr;
				if (four_pr == 4)
				{
					cout << "\n---===УБИЛ!===---\n";
					ubil(newPole2, newShips2, 10);
					count_kill++;
				}
			}

			newPole2.mass_pole[coord_22x67_2] = newPole2.hit;

		}
		else if (proverka == 0)
		{
			cout << "\n---===МИМО!===---\n";
			newPole2.mass_pole[coord_22x67_2] = newPole2.miss;

		}




		newPole2.show_pole();

		if (count_kill == 10)
		{
			cout << "\n<< << << << << << << <<ВЫ ВЫИГРАЛИ!!!!!!>> >> >> >> >> >> >> >> >> >> >> >>\n";
		}
		cout << endl;
		cout << "ОСТАЛОСЬ : " << vihod << " ПОПЫТОК..." << endl;
		proverka = 0;
		vihod--;

	}





}
void POLE::creat_pole()
{
	int i = 0;
	for (int g = 0; g < 22; ++g)
	{
		for (int s = 0; s < 67; ++s)
		{
			if (g == 0)
			{
				if ((s == 8) || (s == 14) || (s == 20) || (s == 26) || (s == 32) || (s == 38) || (s == 44) || (s == 50) || (s == 56))
				{
					mass_pole[i] = num;
					++num;
					++i;

				}
				else if (s == 62)
				{
					mass_pole[i] = num_1;
					++i;
				}
				else if (s == 63)
				{
					mass_pole[i] = num_0;
					++i;
				}
				else
				{
					mass_pole[i] = prob;
					++i;
				}
			}
			else if (g % 2 != 0)
			{
				if (s < 7)
				{
					mass_pole[i] = prob;
					++i;
				}
				else
				{
					mass_pole[i] = tire;
					++i;
				}
			}
			else if (g % 2 == 0)
			{
				if (s == 2)
				{
					mass_pole[i] = letter;
					++letter;
					++i;
				}
				else if ((s == 5) || (s == 11) || (s == 17) || (s == 23) || (s == 29) || (s == 35) || (s == 41) || (s == 47) || (s == 53) || (s == 59) || (s == 65))
				{
					mass_pole[i] = palka;
					++i;
				}
				else
				{
					mass_pole[i] = prob;
					++i;


				}
			}

		}
	}
	//сбрасываем для последующих рисований
	num_0 = 48;
	num_1 = 49;
	num = 49;		//57
	letter = 65;//90

}
void POLE::show_pole()
{
	int j = 0;
	int i = 0;



	for (int g = 0; g < 22; ++g)			//по группам
	{
		for (int s = 0; s < 67; ++s)		//по строкам
		{
			cout << mass_pole[j];			//вывод обычного поля
			++j;						//++поле

		}
		cout << endl;
	}
}
void POLE::show_pole_rasstanovka(int* massiv_coord)
{
	int j = 0;
	int i = 0;



	for (int g = 0; g < 22; ++g)			//по группам
	{
		for (int s = 0; s < 67; ++s)		//по строкам
		{
			if (j == massiv_coord[i])
			{
				mass_pole[j] = '@';
				++i;
			}

			cout << mass_pole[j];			//вывод обычного поля
			++j;						//++поле

		}
		cout << endl;
	}
}

void POLE::poisk_activ()
{
	int count = 0;
	int hoh = 142;					//находим первую позицию активной клетки
	for (int u = 0; u < 10; ++u)			// по группам
	{
		for (int y = 0; y < 10; ++y)		//по строкам
		{
			mass_pole[hoh] = 'o';			//приравниваем активную клетку к букве о
			hoh += 6;				//сдвигаемся на 6 вправо по строке
		}
		hoh += 74;					//сдвигаемся вниз до следующей активной строки
	}

	for (int v = 0, b = 0; v < strlen(mass_pole); ++v)			//вывод на экроан полностью заполненого поля и выписка в массив позиций
	{
		if ('o' == mass_pole[v])
		{
			mass_activ_pole[b] = v;							//здесь мы записываем позицию с буквой о
			++b;
			++count;					//и считаем сколько всего их(должнго быть 100)

		}

	}

	hoh = 142;				//возвращаем обратно пустые клетки меняем о на пробел

	for (int u = 0; u < 10; ++u)
	{
		for (int y = 0; y < 10; ++y)
		{
			mass_pole[hoh] = ' ';
			hoh += 6;
		}
		hoh += 74;
	}
}
void POLE::proverka_activ()	//вывод на экран активных позиций в реальности 
{
	for (int i = 0; i < 100; ++i)
	{
		if (i % 10 == 0)
		{
			cout << endl;
		}
		cout << mass_activ_pole[i] << " ";
	}
}
