#include <iostream>
#include <ctime>
#include <iomanip>
using namespace std;

int main(int argc, char* argv[])
{
    srand(time(NULL));
    setlocale(LC_ALL, "rus");
    int number_rows,// строки
        number_columns; // столбцы
    cout << "Введите количество строк матрицы: ";
    cin >> number_rows;
    cout << "Введите количество столбцов матрицы: ";
    cin >> number_columns;

    // динамическое создание двумерного массива для хранения сгенерированных чисел
    int** ptrarray = new int* [number_rows];
    for (int count = 0; count < number_rows; count++)
        ptrarray[count] = new int[number_columns];

    cout << "nИсходный массив:n";
    for (int counter_rows = 0; counter_rows < number_rows; counter_rows++)
    {
        for (int counter_columns = 0; counter_columns < number_columns; counter_columns++)
        {
            ptrarray[counter_rows][counter_columns] = rand() % 100 - rand() % 100; // заполнение массива случайными числами
            cout << setw(3) << ptrarray[counter_rows][counter_columns] << "  "; // вывод на экран двумерного массива
        }
        cout << endl;
    }
    cout << endl;

    int* ptrsum = new int[number_columns]; // массив характеристик столбцов
    for (int counter_columns = 0; counter_columns < number_columns; counter_columns++)
    {
        ptrsum[counter_columns] = 0; // обнуляем элементы массива характеристик столбцов
        for (int counter_rows = 0; counter_rows < number_rows; counter_rows++)
            if ((ptrarray[counter_rows][counter_columns] < 0)/*отрицательное число*/ && ((ptrarray[counter_rows][counter_columns] % 2 != 0))/*нечётное*/)
                ptrsum[counter_columns] += abs(ptrarray[counter_rows][counter_columns]); // сумма элементов столбца матрицы
    }

    cout << "nМассив характеристик:n";
    for (int counter = 0; counter < number_columns; counter++)
        cout << setw(3) << ptrsum[counter] << "  "; // печать характеристик массива
    cout << endl << endl;

    int* ptrindex = new int[number_columns]; // массив индексов, для формирования порядка перестановок столбцов
    int min = 1000, // переменная для упорядочивания характеристик массива по возрастанию
        index_column; // переменная для хранения индекса минимальной характеристики

    // формируем порядок перестановки столбцов
    for (int counter_value = 0; counter_value < number_columns; counter_value++)
    {
        for (int counter = 0; counter < number_columns; counter++)
        {
            if (min > ptrsum[counter] && ptrsum[counter] != -1)
            {
                min = ptrsum[counter]; // поиск минимального
                index_column = counter; // запоминаем номер столбца
            }
        }
        ptrindex[counter_value] = index_column; // сохраняем индекс столбца в массив индексов
        ptrsum[index_column] = -1; // исключаем из поиска данный элемент массива
        min = 1000; // увеличиваем минимум
    }

    delete[] ptrsum; // удаляем массив характеристик столбцов

    // динамическое создание двумерного массива для перестановок столбцов согласно возрастанию характеристик
    int** ptrarray_relocation = new int* [number_rows];
    for (int count = 0; count < number_rows; count++)
        ptrarray_relocation[count] = new int[number_columns];

    // выполняем перестановку столбцов
    for (int counter_columns = 0; counter_columns < number_columns; counter_columns++)
        for (int counter_rows = 0; counter_rows < number_rows; counter_rows++)
            ptrarray_relocation[counter_rows][counter_columns] = ptrarray[counter_rows][ptrindex[counter_columns]]; // перестановка столбцов

    // вывод массива, с перестановленными столбцами, на экран
    cout << "nМассив после перестановок столбцов:n";
    for (int counter_rows = 0; counter_rows < number_rows; counter_rows++)
    {
        for (int counter_columns = 0; counter_columns < number_columns; counter_columns++)
        {
            cout << setw(3) << ptrarray_relocation[counter_rows][counter_columns] << "  ";
        }
        cout << endl;
    }
    cout << endl;

    // удаление двумерного динамического массива ptrarray
    for (int count = 0; count < number_rows; count++)
        delete[]ptrarray[count];

    delete[] ptrindex; // удаление массива индексов характеристик

    // удаление двумерного динамического массива ptrarray_relocation
    for (int count = 0; count < number_rows; count++)
        delete[]ptrarray_relocation[count];

    system("pause");
    return 0;
}