/***************************************************************************************
*Project Name : RandomArrays                                                           *
*File Name    : RandomArrays.cpp                                                       *
*Language     : CPP,MSVS ver 2015 and above                                            *
*Programmers  : Ратников Роман Олегович,Фицайло Александр Александрович                *
*                                         группа:М3О-110Б-20                           *
*                                                                                      *
*Modified By  :                                                                        *
*Created      : 15/09/2021                                                             *
*Last Revision: 03/10/2021                                                             *
*Comment      : Случайные массивы                                                      *
***************************************************************************************/

#include <iostream>
#include <fstream>
#include <ctime>
#include <chrono>
using namespace std;


//Прототипы функций

//Возрастающий массив
void Ordered_Array_Growth(int* array,			 //Массив
						  const int &N_max ,     //Максимальный элемент
						  const int &length);    //Длина массива

void Ordered_Array_Growth_Double(double* array,			 
								 const int& N_max,     
								 const int& length);



//Убывающий массив
void Ordered_Array_Descending(int* array, const int& N_max, const int& length);

void Ordered_Array_Descending_Double(double* array, const int& N_max, const int& length);



//Случайный массив
void Random_Array(int* array, const int& N_max, const int& length);

void Random_Array_Double(double* array, const int& N_max, const int& length);



//Ступенчатый массив
void Step_Array(int* array, const int& N_max, const int& length);

void Step_Array_Double(double* array, const int& N_max, const int& length);



//Квази массив
void Quazy_Array(int* array, const int& N_max, const int& length);

void Quazy_Array_Double(double* array, const int& N_max, const int& length);



//Запись файла
void File_Recording(const char* FNAME, int* array, const int& value);

void File_Recording_Double(const char* FNAME, double* array, const int& value);


//Запись времени работы алгоритма

void Recording_Time(const char* FNAME,double* time);

void Recording_Time_Double(const char* FNAME,double* time);



//Удаление массива
void Delete_Array(int* array);

void Delete_Array_Double(double* array);

const char* FNAME = "Array.txt";								//Файл с данными массива

const char* FNAME_ANSWER[] = { "ArrayAnswerGrowth.txt",			//Файл возрастающего массива
							   "ArrayAnswerDescending.txt",		//Файл убывающего массива
							   "ArrayAnswerRandom.txt",			//Файл случайного массива
							   "ArrayAnswerStep.txt",			//Файл ступенчатого массива
							   "ArrayAnswerQuazy.txt" };		//Файл Квази массива

//С плавающей запятой
const char* FNAME_ANSWER_Double[] = { "ArrayAnswerGrowth_Double.txt",			
									  "ArrayAnswerDescending_Double.txt",		
							          "ArrayAnswerRandom_Double.txt",			
							          "ArrayAnswerStep_Double.txt",				
							          "ArrayAnswerQuazy_Double.txt" };			

const char* FNAME_TIME = "Answer_Time.txt";						//Файл с временем

const char* FNAME_TIME_Double = "Answer_Time_Double.txt";


int main()
{
	setlocale(LC_ALL, "Rus");
	
	ifstream fin;
	fin.open(FNAME);
	
	int length;
	int N_max;
	fin >> length;
	fin >> N_max;
	fin.close();

	 int* pa[5];           //Массив указателей на массивы
	 double* pa_double[5];

	 double time[5];		//Массив времени работы алгоритмов
	 double time_double[5];
	
	
    for(int i =0;i<5;i++)
	{ 
		pa[i] = new int[length];
		pa_double[i] = new double[length];
	}
	
	//Массив указателей на функции
	void (*func_ar[5])(int*, const int&, const int&) = { Ordered_Array_Growth,
													   Ordered_Array_Descending,
													   Random_Array,
													   Step_Array,
													   Quazy_Array };

	void (*func_ar_d[5])(double*, const int&, const int&) = { Ordered_Array_Growth_Double,
													   Ordered_Array_Descending_Double,
													   Random_Array_Double,
													   Step_Array_Double,
													   Quazy_Array_Double};
	
	for (int i = 0; i < 5;i++)
	{   
		//Получение времени начала функции
		auto begin = chrono::high_resolution_clock::now();
		func_ar[i](pa[i], N_max, length);
		//Получение времени окончания функции
	
		chrono::duration<double> elapsed_ms = chrono::high_resolution_clock::now() - begin;

		time[i] = elapsed_ms.count() * 1000000;
		if (length <= 200)
		{
			File_Recording(FNAME_ANSWER[i], pa[i], length);
		}
		Delete_Array(pa[i]);
	}

	Recording_Time(FNAME_TIME,time);

	//С плавающей запятой
	for (int i = 0; i < 5;i++)
	{
		
		auto begin = chrono::steady_clock::now();
		func_ar_d[i](pa_double[i], N_max, length);
		auto end = chrono::steady_clock::now();
		chrono::duration<double> elapsed_ms = chrono::duration_cast<chrono::microseconds>(end - begin);
		time_double[i] = elapsed_ms.count() *1000000;
		if (length <= 200)
		{
			File_Recording_Double(FNAME_ANSWER_Double[i], pa_double[i], length);
		}
		Delete_Array_Double(pa_double[i]);
	}
	Recording_Time_Double(FNAME_TIME_Double, time_double);
	
	return 0;
}

void Ordered_Array_Growth(int* array, const int& N_max, const int& length)
{
	
	float min = float(N_max) / length;
	float value = min;
	for (int i = 0;i < length;i ++)
	{
		array[i] = int(value);
		value+=min;
	}

}

void Ordered_Array_Growth_Double(double* array, const int& N_max, const int& length)
{

	float min = float(N_max) / length;
	float value = min;
	for (int i = 0;i < length;i++)
	{
		array[i] = value;
		value += min;
	}

}



void Ordered_Array_Descending(int* array, const int& N_max, const int& length)
{
	float min = float(N_max) / length;
	float value = N_max;
	for (int i = 0;i < length;i++)
	{
		array[i] = int(value);
		value -= min;
	}
}

void Ordered_Array_Descending_Double(double* array, const int& N_max, const int& length)
{
	float min = float(N_max) / length;
	float value = N_max;
	for (int i = 0;i < length;i++)
	{
		array[i] = value;
		value -= min;
	}
}



void Random_Array(int* array, const int& N_max, const int& length)
{
	srand(time(0));
	float min = float(N_max) / length;
	for (int i = 0;i <length;i++)
	{
		array[i] = rand()% (N_max - int(min)) + int(min);
		
	}
}

void Random_Array_Double(double* array, const int& N_max, const int& length)
{
	srand(time(0));
	float min = float(N_max) / length;
	for (int i = 0;i < length;i++)
	{
		array[i] = rand() % (N_max - int(min)) + int(min);

		float value = float(rand()) / RAND_MAX;

		

		if (array[i] + value < N_max)
		{
			array[i] += value;
		}

	}
}

void Quazy_Array(int* array, const int& N_max, const int& length)
{
	float min = float(N_max) / length;
	int BorderUp, BorderDown;
	
	for (int i = 0;i < length;i++)
	{
		if (i % int(ceil(length/10)) == 0)
		{
			BorderDown = int( min * (i+1)/ ((i*0.2/length)+1));

			if (i != length - 1)
			{
				BorderUp = ceil(N_max - (length - 2 - i) * min / ((i * 0.5 / length) + 1));
			}
				/*cout << i << endl;
				cout << BorderUp << endl;
				cout << BorderDown<<endl;
				cout << i *0.5 / length << endl;
				cout << '\n';*/
			
		}

			array[i] =rand()%(BorderUp-BorderDown) + BorderDown;
		
	}

}


void Quazy_Array_Double(double* array, const int& N_max, const int& length)
{
	float min = float(N_max) / length;
	int BorderUp, BorderDown;

	for (int i = 0;i < length;i++)
	{
		if (i % int(ceil(length / 10)) == 0)
		{
			BorderDown = int(min * (i + 1) / ((i * 0.2 / length) + 1));

			if (i != length - 1)
			{
				BorderUp = ceil(N_max - (length - 2 - i) * min / ((i * 0.5 / length) + 1));
			}
			/*cout << i << endl;
			cout << BorderUp << endl;
			cout << BorderDown<<endl;
			cout << i *0.5 / length << endl;
			cout << '\n';*/

		}

		array[i] = rand() % (BorderUp - BorderDown) + BorderDown;

		float value = float(rand()) / RAND_MAX;

		if (array[i] + value < N_max)
		{
			array[i] += value;
		}

	}

}







void Step_Array(int* array, const int& N_max, const int& length)
{

	float min = float(N_max) / length;
	int BorderUp, BorderDown;

	for (int i = 0;i < length;i++)
	{
		if (i % int(ceil(length/10)) == 0)
		{
			BorderDown = int(min * (i + 1));
			if (i!=length-1)
			BorderUp = ceil(N_max - (length - 2 - i) * min);


			/*cout << BorderUp << endl;
			cout << BorderDown<<endl;
			cout << '\n';
			*/
		}

		array[i] = rand() % (BorderUp - BorderDown) + BorderDown;

	}
}


void Step_Array_Double(double* array, const int& N_max, const int& length)
{

	float min = float(N_max) / length;
	int BorderUp, BorderDown;

	for (int i = 0;i < length;i++)
	{
		if (i % int(ceil(length / 10)) == 0)
		{
			BorderDown = int(min * (i + 1));
			if (i != length - 1)
				BorderUp = ceil(N_max - (length - 2 - i) * min);


			/*cout << BorderUp << endl;
			cout << BorderDown<<endl;
			cout << '\n';
			*/
		}

		array[i] = rand() % (BorderUp - BorderDown) + BorderDown;

		float value = float(rand()) / RAND_MAX;

		if (array[i] + value < N_max)
		{
			array[i] += value;
		}
	}
}
void File_Recording(const char* FNAME, int* array, const int& value)
{
	fstream fin;
	fin.open(FNAME, ios::out);
	for (int i = 0;i < value;i++)
	{
		fin << array[i] << endl;
	}
	fin.close();
}

void File_Recording_Double(const char* FNAME, double* array, const int& value)
{
	ofstream fin;
	fin.open(FNAME, ios::out);
	for (int i = 0;i < value;i++)
	{
		fin << array[i] << endl;
	}
	fin.close();
}

void Delete_Array(int* array)
{
	delete[] array;
}

void Delete_Array_Double(double* array)
{
	delete[] array;
}

void Recording_Time(const char* FNAME, double* time)
{
	ofstream fin;
	fin.open(FNAME, ios::out);
	fin << "Time.Growth : " << time[0] << " ПкС" << endl;
	fin << "Time.Descending : " << time[1] << " ПкС" << endl;
	fin << "Time.Random : " << time[2] << " ПкС" << endl;
	fin << "Time.Step : " << time[3] << " ПкС" << endl;
	fin << "Time.Quazy : " << time[4] << " ПкС" << endl;
	fin.close();
}

void Recording_Time_Double(const char* FNAME, double* time)
{
	ofstream fin;
	fin.open(FNAME, ios::out);
	fin << "Time.Growth :" << time[0] << " ПкС" << endl;
	fin << "Time.Descending :" << time[1] << " ПкС" << endl;
	fin << "Time.Random :" << time[2] << " ПкС" << endl;
	fin << "Time.Step :" << time[3] << " ПкС" << endl;
	fin << "Time.Quazy :" << time[4] << " ПкС" << endl;
	fin.close();
}