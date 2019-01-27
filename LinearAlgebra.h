#pragma once


namespace LinearAlgebra{
	
class TQuaternion;

class TMatrix;

class TVector
{
protected:
	//размерность
	int n;
	//элементы вектора
	double *data;
public:
	//конструктор по умолчанию
	TVector();
	//конструктор с заданным кол-вом эл-ов
	TVector(int n);
	//конструктор копий
	TVector(const TVector& rvalue);
	//оператор присваивания
	TVector& operator = (const TVector& rvalue);
	//деструктор
	virtual ~TVector();
	//получение кол-ва элементов вектора
	inline int size()const {return n;}
	//получение индекса последнего элемента
	inline int high()const {return n - 1;}
	//задание кол-ва элементов вектора
	void resize(int n);
	//оператор доступа к элементам вектора
	inline double& operator [](int i)const {return data[i];}
	//оператор унарный минус
	TVector operator - ()const;
	//оператор вычитания векторов
	TVector operator - (const TVector& arg)const;
	TVector operator + (const TVector& arg)const;
	//оператор умножения вектора на число
	TVector operator * (double arg)const;
	//оператор скалярного умножения векторов
	double operator * (const TVector& arg)const;
	//оператор умножения вектора на матрицу
	TVector operator * (const TMatrix& arg)const;
	//оператор умножения вектора на кватернион
	TQuaternion operator * (const TQuaternion& arg)const;
	//оператор векторного умножения векторов
	TVector operator ^ (const TVector& arg)const;
	//оператор умножения числа на вектор
	friend TVector operator * (double lvalue, TVector& rvalue);
	//получение моудля вектора
	double length() const;
	//функция нормирования вектора
    TVector& norm();
	/*поворот вектора вокруг заданной оси на заданный угол
	 * при помощи формулы Родрига
	 * */
    TVector RodrigRotate(double phi, const TVector& axis) const;
	/*поворот вектора вокруг заданной оси на заданный
	* угол при помощи кватерниона*/
    TVector rotate(double phi, const TVector& axis)const;
	/*поворот вектора при помощи заданного кватерниона*/
    TVector QuaternionRotate(const TQuaternion& L)const;
};

class TMatrix
{
protected:
	//размерность матрицы, строки, столбцы
	//int n, m;
	//элементы матрицы
	double** data;
    int n, m;
public:

	//конструктор по умолчанию
	TMatrix();
	//конструктор с заданием размерности
	TMatrix(int n, int m);
	//конструктор копий
	TMatrix(const TMatrix& rvalue);
	//оператор присваивания
	TMatrix& operator = (const TMatrix& rvalue);
	//деструктор
	virtual ~TMatrix();
	//получение количества строк
	inline int rowCount()const {return n;}
	//получение количества стобцов
	inline int colCount()const {return m;}
	//получения индекса последней строки
	inline int rowHigh()const {return n - 1;}
	//получение индекса последнего столбца
	inline int colHigh()const {return m - 1;}
	//функция задания размерности
	void resize(int n, int m);
	//оператор доступа к элементам матрицы
	inline double& operator()(int i, int j){return data[i][j];}
	
	//константный доступ
	inline const double& operator()(int i, int j) const {return data[i][j];}
	//вычитание матриц
	TMatrix operator - (const TMatrix& arg) const;
	//унаный минус
	TMatrix operator - () const;
	//оператор сложения матриц
	TMatrix operator + (const TMatrix& arg) const;
	//оператор умнодения матрциы на число
	TMatrix operator * (double arg) ;
	//оператор умножения матриц
	TMatrix operator * (const TMatrix& arg) const;
	//оператор умножения матрицы на вектор
	TVector operator * (const TVector& arg) const;
	//оператор умножения числа на матрицу 
	friend TMatrix operator * (double lvalue, const TMatrix& rvalue);
	//обращение матрицы методом Гаусса
	TMatrix operator ! ()const;
	//вычисление детерминанта
	double det() const;
	//формирование единичной матрицы
	static TMatrix E(int n);
	//перестановка строк
	TMatrix& swapRows(int i, int j);
	TMatrix& xhol (TMatrix& arg);
	bool sylvester(TMatrix& arg);
};

class TQuaternion
{	
protected:
	//скалярная часть
	double q0;
	//векторная часть
	TVector Q;
public:
	//конструктор по умолчанию
	TQuaternion();
	//конструктор с заданием компонент кватерниона
	TQuaternion(double l0, double l1, double l2, double l3);
	//констурктор по углу поворота рад и оси вращения
	TQuaternion(double phi, TVector& e);
	//конструктор копирования
	TQuaternion(const TQuaternion& rvalue);
	//конструктор присваивания
	TQuaternion& operator = (const TQuaternion& rvalue);
	//вычитание кватернионов
	TQuaternion operator - (const TQuaternion& arg) const;
	//оператор сложения кватернионов
	TQuaternion operator + (const TQuaternion& arg) const;
	//оператор умножения кватернионов
	TQuaternion operator *(const TQuaternion& arg) const;
	//опрератор умножения кватерниона на вектор
	TQuaternion operator * (const TVector& arg) const;
	//оператор умножения кватерниона на число
	TQuaternion operator * (double arg) const;
	//оператор умножения числа на кватернион
	friend TQuaternion operator * (double lvalue, const TQuaternion& rvalue);
	//оператор обращения кватерниона
	TQuaternion operator ! () const;
	//доступ у скалярной части
	inline double scal()const {return q0;}
	//доступ к векторной части
	inline TVector vect() const {return Q;}
	//нормирование кватерниона
	TQuaternion& norm();
	//получение сопряженного кватерниона
	TQuaternion conj() const;
	//получение матрицы вращения из компонент кватерниона
	TMatrix rotateMatrix() const;
	/* производящая функция для создания кватерниона
	 * по углам Крылова
	 * */
     static TQuaternion fromKrylovAngels(double yaw, double pith, double roll);
};
}
