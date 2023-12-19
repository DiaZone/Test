#include <iostream>
#include <cmath>
#include <mpi.h>

//Промежуток поиска и точность
int A = -200;
int B = 200;
double epsilon = 0.000001;

//Заданная функция
double equation(double x) {
    return 6*x * x - 3 * x - 29;
}


int main(int argc, char* argv[]) {

  //Начальная конфигурация MPI
  int numProcs, myRank;
  MPI_Init(&argc, &argv);
  MPI_Comm_size(MPI_COMM_WORLD, &numProcs);
  MPI_Comm_rank(MPI_COMM_WORLD, &myRank);

  double solutions[numProcs]; //Массив решений

  double step = (B - A) / numProcs; //Шаг поиска в промежутке
  double myStart = A + myRank * step; //Начало интервала поиска для процесса
  double myEnd = myStart + step; //Конец интервала поиска для процесса

  //std::cout << myStart << " " << myEnd << std::endl;

  double min_fx = abs(equation(myStart)); //Минимальное значение функции

  double x = myStart; //Начальное решение
  double root;

  //Проходим по интервалу
  while(x <= myEnd){

    //Получаем значение функции по модулю
    double mod_fx = abs(equation(x));
    //std::cout << mod_fx << std::endl;

    //Если значение меньше предыдущего
    if(mod_fx <= epsilon && mod_fx <= min_fx){

      root = x; //Запоминаем новое значение
      //std::cout << root << std::endl;

      min_fx = mod_fx;//Запоминаем новое значение функции
      //std::cout << min_fx << std::endl;
      
    }
    x += epsilon;//Прибавляем шаг

  }

  //Собираем информация со всех процессов
  MPI_Gather(&root, 1, MPI_DOUBLE, solutions, 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);

  //Мастер-процесс выводит информацию о решении
  if(myRank == 0){

    std::cout << "Solutions:" << std::endl;
    for (int i = 0; i < numProcs; i++) {

      //Фильтруем неправильные решения
      if ((solutions[i] >= A + i * step) && (solutions[i] < A + (i + 1) * step)) {
        std::cout << solutions[i] << std::endl;
      }
    }
  }

  MPI_Finalize();
  return 0;
}
