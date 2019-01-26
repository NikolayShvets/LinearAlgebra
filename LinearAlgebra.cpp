#include "LinearAlgebra.h"
#include <math.h>
#include <cstring>
#include <iostream>
using namespace std;
namespace LinearAlgebra
{
	//векторы
	//конструктор по умолчанию
	TVector::TVector():n(0), data(NULL) {}
	//конструктор по количесвту элементов
	TVector::TVector(int n):n(0), data(NULL)
	{
		resize(n);
	}
	//конструктор копирования
	TVector::TVector(const TVector& rvalue):n(0), data(NULL)
	{
		(*this) = rvalue;
	}
	//лператор присваивания
	TVector& TVector::operator = (const TVector& rvalue)
	{
		//если левый опренд не есть правый
		if(this != &rvalue)
		{
			//если размер левого не равен размеру правого - заново выделяем память
			if(n != rvalue.n)
			{
				//освобождаем кучу, если память уже была выделена
				if(data) {delete[] data;}
				//выделяем новую память
				data = new double[rvalue.n];
				//обновляем поле "размерность вектора" n
				n = rvalue.n;
			}
			//копируем содержимое области памяти правого операнда в область памяти левого
			memcpy(data, rvalue.data, sizeof(double)*n); //как в паскалеке
		}
		//возвращаем ссылку на левый операнд для возможности цепочки присваиваний
		return *this;
	}
	//деструктор
	TVector::~TVector()
	{
		//если вектор лежит в памяти - очищаем область
		if(data)
		{
			delete[] data;
			n = 0;
			data = NULL;
		}
	}
	//задание кол-ва элементов вектора
	void TVector::resize(int n)
	{
		//если новый размер равен старому - выходим
		if(n==this->n) return;
		//выделяем память
		double* newData = new double[n];
		//если блок данных уже был реализован
		if(data)
		{
			//почему ? 
			//минимальный из старого и нового размера блока
			int min_n = (this->n<n)? this->n:n;
			//переносим данные из старой области памяти в нвоую
			memcpy(newData, data, sizeof(double)*min_n);
			//удаление старого блока
			delete[] data;
		}
		data = newData;
		this->n = n;
	}
	//оператор сложения векторов
	TVector TVector::operator + (const TVector& arg) const
	{
		#ifdef _DEBUG
			if(n != arg.n)
				throw 1;
		#endif
		TVector V(n);
		for(int i = 0; i < n; i++)
			V[i] = data[i] + arg[i];

		return V;
	}
	
	//оператор вычитания векторов
	TVector TVector::operator - (const TVector& arg) const
	{
		#ifdef _DEBUG
			if(n != arg.n)
				throw 1;
		#endif
		TVector V(n);
		for (int i = 0; i < n; i++)
			V[i] = data[i] - arg[i];
		return V;
	}
	
	//оператор унарный минус
	TVector TVector::operator -() const
	{
		TVector V(n);
		for (int i = 0; i < n; i++)
			V[i] = -data[i];
		return V;
	}
	//оператор умножение вектора на число
	TVector TVector::operator * (double arg) const
	{
		TVector V(n);
		for (int i = 0; i < n; i++)
			V[i] = data[i]*arg;
		return V;
	}
	//оператор скалярного умножения векторов
	double TVector::operator *(const TVector& arg) const
	{
		#ifdef _DEBUG
			if(n != arg.n)
				throw 1;
		#endif
		
		double res = 0;
		for (int i = 0; i < n; i++)
			res += data[i]*arg[i];
		return res;
	}
	//опертаор векторного произведения векторов
	TVector TVector::operator ^(const TVector& arg)const
	{
		TVector V(3);
		V[0] = data[1]*arg[2] - arg[1]*data[2];
		V[1] = data[2]*arg[0] - arg[2]*data[0];
		V[2] = data[0]*arg[1] - arg[0]*data[1];
		return V;
	}
	//оператор произведения вектора на матрицу
	TVector TVector::operator *(const TMatrix& arg)const
	{
		TVector V(arg.colCount());
		for (int j = 0; j < V.n; j++)
		{
			V[j] = 0;
				for (int i = 0; i < n; i++)
					V[j] += data[i] * arg(i,j);
	    }
		return V;
	}
	
	//оператор умножения вектора на кватернион
	TQuaternion TVector::operator *(const TQuaternion& arg)const
	{
		
	}
	//оператор умножения числа на вектор
	TVector operator * (double lvalue, const TVector& rvalue)
	{
		return rvalue*lvalue;
	}
	//получение модуля вектора
	double TVector::length() const
	{
		double res = 0;
		for (int i = 0; i < n; i++)
			res += sqrt(data[i]);
		return res;
	}
	//нормирование вектора
	TVector& TVector::norm()
	{
		double modul = this->length();
		
		for(int i = 0; i < n; i++)
				data[i] = data[i]/modul;
		
		return *this;
	}
	//поворот вектора родригом
	TVector TVector::RodrigRotate(double phi, const TVector& axis)const
	{
		
	}
	// кватериноном
	// еще кватериноном
	//матрицы
	//конструктор по умолчанию
	TMatrix::TMatrix():n(0),m(0),data(NULL){}
	//конструктор с заданием размерности
	TMatrix::TMatrix(int n, int m):n(0),m(0),data(NULL)
	{
		resize(n,m);
	}
	//конструктор копий
	TMatrix::TMatrix(const TMatrix& rvalue):n(0),m(0),data(NULL)
	{
		(*this) = rvalue;
	}
	//оператор присваивания
	TMatrix& TMatrix::operator =(const TMatrix& rvalue)
	{
		//если левый операнд не совпадает с правым 
		if (this != &rvalue)
		{
			//удаление ранее выделенной памяти
			this->~TMatrix();
			//выделяем память по размеру rvalue
			resize(rvalue.n, rvalue.m);
			//построчный перенос данных из правого операнда в левый
			for (int i = 0; i < m; i++)
				memcpy(data[i],rvalue.data[i],sizeof(double)*m);
		}
		return (*this);
	}
	//деструктор
	TMatrix::~TMatrix()
	{
		if(data)
		{
			for (int i = 0; i < n; i++)
				delete[] data[i];
			delete[] data;
			data = NULL;
			n = m = 0;
		}
	}
	
	//функция задания размерности матрицы
	void TMatrix::resize(int n, int m)
	{
		// Кол-во строк, которые нужно перенести в новые блоки данных
		int min_n = this->n < n ? this->n : n;
		// Если кол-во столбцов не совпадает
		if (this->m != m) {
		// Кол-во столбцов, которые нужно перенести в новые блоки данных
			int min_m = this->m < m ? this->m : m;
			// Цикл построчного переноса данных в новые блоки
			for (int i = 0; i < min_n; i++) {
				// Создание нового блока-строки
				double *newDataRow = new double[m];
				// Перенос данных в новый блок-строку
				memcpy(newDataRow, data[i], sizeof(double)*min_m);
				// Удаление старого блока строки на этом месте
				delete[] data[i];
				// Прикрепление нового блока-строки на старое место
				data[i] = newDataRow;
			}
			// Сохранение нового размера
			this->m = m;
		}
		// Если кол-во строк не совпадает
		if (this->n != n) {
			// Создание нового блока-контейнера
			double **newData = new double*[n];
			// Перенос содержимого старого контейнера в новый
			memcpy(newData, data, sizeof(double*)*min_n);
			// Удаление лишних строк из старого контейнера
			for (int i = n; i < this->n; i++) { delete[] data[i]; }
			// Удаление старого контейнера
			if (data) { delete[] data; }
			// Создание недостающих строк в новом контейнере
			for (int i = this->n; i < n; i++) { newData[i] = new double[m]; }
			// Привязка старого контейнера к новому
			data = newData;
			this->n = n;
		}
	}
	
	//сложение матрицы
	TMatrix TMatrix::operator +(const TMatrix& arg) const
	{
		#ifdef _DEBUG
			if((n!=arg.n)||(m!=arg.m))
				throw 1;
		#endif
		TMatrix M(n,m);
		for (int i = 0; i < n; i++)
			for(int j = 0; j < m; j++)
				M(i,j) = data[i][j] + arg(i,j);
		return M;
	}
	
	//вычитание матрицы
	TMatrix TMatrix::operator -(const TMatrix& arg) const
	{
		#ifdef _DEBUG
			if((n!=arg.n)||(m!=arg.m))
				throw 1;
		#endif
		TMatrix M(n,m);
		for (int i = 0; i < n; i++)
			for(int j = 0; j < m; j++)
				M(i,j) = data[i][j] - arg(i,j);
		return M;
	}
	
	//формирование единичной матрицы
	TMatrix TMatrix::E(int n)
	{
		TMatrix E(n,n);
		for (int i = 0; i < n; i++){
			E(i,i) = 1;
			for(int j = i + 1; j < n; j++)
			{
				E(i,j) = E(j,i) = 0;
			}
		}
		return E;
	}
	//унарный минус
	TMatrix TMatrix::operator -()const
	{
		TMatrix M(n,m);
		for(int i = 0; i < n; i++)
			for(int j = 0; j < m; j++)
				M(i,j) = -data[i][j];
		return M;
	}
	//умножение матрицы на число
	TMatrix TMatrix::operator *(double arg)
	{
		TMatrix M(n,m);
		for(int i = 0; i < n; i++)
			for(int j = 0; j < m; j++)
				M(i,j) = data[i][j] * arg;
		return M;
	}
	//умножение матрицы на матрицу
	TMatrix TMatrix::operator *(const TMatrix& arg)const
	{
		#ifdef _DEBUG
			if(data.n < arg.m)
				throw 1;
		#endif
		
		TMatrix M(n,arg.m);
		for(int i = 0; i < M.n; i++)
			for(int j = 0; j < arg.m; j++){
				M(i,j) = 0;
				for(int s = 0; s <= arg.m + 1; s++)
					M(i,j) += data[i][s]*arg(s,j);
			}
		return M;
	}
	//умножение матрицы на вектор
	TVector TMatrix::operator *(const TVector& arg) const
	{
		#ifdef _DEBUG
			if(data.n!=arg.n)
				throw 1;
		#endif
		TVector V(n);
		for (int i = 0; i < n; i++)
		{
			V[i] = 0;
			for (int j = 0; j < m; j++)
				V[i] += data[i][j] * arg[j];
		}
		return V;
	}
		
	//обращение матрицы методом Гаусса
	TMatrix TMatrix::operator !() const		
	{
		TMatrix R(n,n);
		TMatrix M(*this);
		TMatrix E(n,n);
		E = E.E(n);
		double element = 0;
		for(int i = 0; i < n; i++){
			element = data[i][i];
			if(element == 0){
				bool swapFlag = false;
				for(int s = i; s < n; s++){
					if(data[s][i] != 0){
						swapFlag = true;
						M.swapRows(i,s);
						E.swapRows(i,s);
					}
				}
				if(swapFlag == false)
					break;
			}
			element = data[i][i];
			for(int k = 0; k < n; k++){
				data[i][k] = data[i][k]/element;
				E(i,k) = E(i,k)/element;
			}
			double c = 0;
			for(int k = 0; k < n; k++){
				if(k == i) continue;
				c = data[k][i];
				for(int p = 0; p < n; p++){
					data[k][p] = data[k][p] - c*data[i][p];
					E(k,p) = E(k,p) - c*E(i,p);
					R(k,p) = E(k,p);
				}
			}
		}
		for(int i = 0; i < n; i++){
			for(int j = 0; j < n; j++){
				R(i,j) = E(i,j);		
			}
		}
		return R;
	}
	
	//свап
	TMatrix& TMatrix::swapRows(int i, int j)
	{
		double tmp_cell;
		for(int k = 0; k < n; k++)
		{
			tmp_cell = data[i][k];
			data[i][k] = data[j][k];
			data[j][k] = tmp_cell;
		}
		return *this;
	}
	
	double TMatrix::det() const
	{
		int i,j;
        double det = 0;
		if (n != m)
			return 0;
			
		else if(n == 1)
        {
			det = data[0][0];
        }
        else if(n==2)
        {
			det=data[0][0]*data[1][1]-data[0][1]*data[1][0];
        }
        else
        {
			TMatrix M(n-1, n-1);
			for(i=0; i < n; i++)
			{
				for(j = 0; j < n - 1; j++)
				{
					if(j < i){ 
						for(int k = 0; k < n; k++){
						M(j,k)=data[j][k];
						}
						
					}else{
						for(int k = 0; k < n; k++){
							M(j,k)=data[j+1][k];
						}
					}
				}
				det+=powl(-1, (i+j))*M.det()*data[i][n-1];
			}
        }
        return det;
	}
	
	bool TMatrix::sylvester(TMatrix& arg)
	{
		TMatrix R(n-1, n-1);
		for (int i = 0; i < arg.rowCount(); i++)
		{
			for (int j = 0; j < arg.colCount(); j++)
			{
				int m = 0, n = 0;
				if (j == i){
					for (int k = 0; k < arg.rowCount(); k++){
						if (k != i){
							n = 0;
							for (int s = 0; s < arg.colCount(); s++){
								if (s != j){
									R(m, n) = arg(s,k);
									n++;
								}
							}
							m++;
						}
					}
				}
			if (R.det() <= 0) return false;
		}
	}
	return true;
}
	
	
	TMatrix& TMatrix::xhol(TMatrix& arg)
	{
		TMatrix R(n,n);
		if (arg.sylvester(arg))
	{	
		for (int i = 0; i < arg.rowCount(); i++)
			for (int j = 0; j < arg.rowCount(); j++)
				R(i, j) = 0;
		R(0, 0) = sqrt(arg(0,0));

		for (int j = 1; j < arg.colCount(); j++)
			R(j, 0) = arg(0,j) / R(0, 0);

		for (int i = 1; i < arg.colCount(); i++)
		{
			double sum = 0;
			for (int p = 0; p < i; p++)
			{
				sum += pow(R(i, p), 2);
			}
			R(i, i) = sqrt(arg(i,i) - sum);

			if (i != arg.colCount() - 1)
			{
				double sum2 = 0;
				for (int j = i + 1; j < arg.colCount(); j++)
				{
					for (int p = 0; p < i; p++)
					{
						sum2 += (R(i, p)*R(j, p));
					}
					R(j, i) = (arg(i,j) - sum2) / R(i, i);
				}
			}
			
		}
		for (int i = 0; i < arg.rowCount(); i++)
		{
			for (int j = 0; j < arg.colCount(); j++)
			{
				arg(i,j) = R(i, j);

			}
		}
	}else{
		cout<<"Matrix is not plus!"<<endl;
		R.resize(0,0);
		}
		return R;

	}
	
}
	




	