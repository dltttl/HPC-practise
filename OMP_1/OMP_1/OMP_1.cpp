// OMP_1.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <omp.h>

double integral(double a, double b, double (*func) (double), bool isParallel);

int main()
{
    double t1 = omp_get_wtime();
    double result;

    for (auto i = 0; i < 10000; i++)
    {
        result = integral(0, 1, [](double x) {return 4.0 / (1 + x * x); }, true);
    }

    double t2 = omp_get_wtime();
    std::cout << "Time parallel: " << t2 - t1 << "   Result: " << result << std::endl;

    for (auto i = 0; i < 10000; i++)
    {
        result = integral(0, 1, [](double x) {return 4.0 / (1 + x * x); }, false);
    }

    double t3 = omp_get_wtime(); 
    std::cout << "Time nonParallel: " << t3 - t2 << "   Result: " << result << std::endl;    
}

double integral(double a, double b, double (*func) (double), bool isParallel)
{
    double result = 0;
    int n = 10000;
    double step = (b - a) / (n + 1);

#pragma omp parallel for if (isParallel) reduction(+:result) num_threads(10)
    for (auto i = 0; i < n; i++)
    {
        result += step * func(a + step * i);
    }

    return result;
}
