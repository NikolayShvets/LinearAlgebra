#include "model.h"

void TModel::addResult(const TVector& X, long double t)
{
	/* проверка выходит ли счетчик строк в
	 * матрице результатов за пределы последней
	 * строки, если да, увеличиваем количество 
	 * строк на 1
	 * */
     if (N == Result.rowCount())
		Result.resize(N+1, getOrder()+1);
	/* поместим резудьтаты в последнюю строку матрицы Result
	  * момент времени помещается в 0-ой столбец,
	  * вектор состояния - в остальные столбцы
	  * */
	Result(N,0) = t;
	for(int i = X.size(); i > 0; i--)
		Result(N,i) = X[i-1];
	N++;
}

void TModel::clearResult()
{
	Result.resize(0,0);
	N = 0;
}

void TModel::prepareResult()
{
	/* задаем матрице результатов такой размер
	 * чтобы поместить все значения вектора состояния
	 * и соотвествующих этим значениям моменты времени на
	 * интервале [t0, t1] с шагом SamplingIncrement
	 * */
     Result.resize((int)((t1-t0)/SamplingIncrement)+1, getOrder()+1/*(int)((t1-t0)/SamplingIncrement)+1*/);
	 N = 0;
}
