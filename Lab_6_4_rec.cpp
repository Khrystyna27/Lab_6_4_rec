// Лабораторна робота № 6.4
// Опрацювання та впорядкування одновимірних динамічних масивів
// Рекурсивний спосіб
// Варіант 30
 
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
 
using namespace std;
 
// Рекурсивно заповнює масив випадковими цілими числами з діапазону [Low, High]
void Create(int* a, const int size, const int Low, const int High, int i);
 
// Рекурсивно виводить елементи масиву в один рядок (кожен - 4 позиції)
void Print(const int* a, const int size, int i);
 
// Рекурсивно повертає мінімальний за модулем елемент масиву
// (якщо таких кілька - перший з них)
int MinAbs(const int* a, const int size, int i);
 
// Рекурсивно повертає індекс першого нульового елемента масиву
// (або -1, якщо нульових елементів немає)
int IndexOfFirstZero(const int* a, const int size, int i);
 
// Рекурсивно повертає суму модулів елементів масиву, починаючи з індексу i
int SumAbsFrom(const int* a, const int size, int i);
 
// Рекурсивно копіює елементи a[i], a[i+2], ... у масив t, починаючи з індексу k
void CollectEveryOther(const int* a, int* t, const int size, int i, int& k);
 
// Рекурсивно копіює елементи масиву src у масив dest
void CopyArray(const int* src, int* dest, const int size, int i);
 
// Переставляє елементи масиву: у першій половині - елементи, що стояли
// в парних позиціях (2, 4, ...), у другій - елементи з непарних позицій
// (1, 3, ...); відносне розташування елементів зберігається
void MoveEvenPositionsFirst(int* a, const int size);
 
int main()
{
   int n;
   do
   {
       cout << "n = ";
       cin >> n;
   } while (n < 1);
 
   const int Low = -9;
   const int High = 9;
 
   srand((unsigned)time(NULL));
 
   int* a = new int[n];            // створили динамічний масив
 
   Create(a, n, Low, High, 0);
   cout << "Початковий масив:" << endl;
   Print(a, n, 0);
 
   cout << "1.1. Мінімальний за модулем елемент = " << MinAbs(a, n, 0) << endl;
 
   int z = IndexOfFirstZero(a, n, 0);
   if (z == -1)
       cout << "1.2. Нульових елементів немає, сума модулів = 0" << endl;
   else
       cout << "1.2. Сума модулів елементів після першого нуля = "
            << SumAbsFrom(a, n, z + 1) << endl;
 
   MoveEvenPositionsFirst(a, n);
   cout << "2. Перетворений масив:" << endl;
   Print(a, n, 0);
 
   delete[] a;                     // знищили динамічний масив
 
   return 0;
}
 
void Create(int* a, const int size, const int Low, const int High, int i)
{
   a[i] = Low + rand() % (High - Low + 1);
   if (i < size - 1)                           // умова продовження рекурсії
       Create(a, size, Low, High, i + 1);
}
 
void Print(const int* a, const int size, int i)
{
   cout << setw(4) << a[i];
   if (i < size - 1)                           // умова продовження рекурсії
       Print(a, size, i + 1);
   else
       cout << endl;                           // дія після циклу: кінець рядка
}
 
int MinAbs(const int* a, const int size, int i)
{
   if (i == size - 1)
       return a[i];                            // базова задача: останній елемент
 
   int min = MinAbs(a, size, i + 1);           // мінімум серед елементів після i
   if (abs(a[i]) <= abs(min))                  // <= : при рівності - перший
       return a[i];
   else
       return min;
}
 
int IndexOfFirstZero(const int* a, const int size, int i)
{
   if (i >= size)
       return -1;                              // базова задача: нуля немає
   if (a[i] == 0)
       return i;
   return IndexOfFirstZero(a, size, i + 1);
}
 
int SumAbsFrom(const int* a, const int size, int i)
{
   if (i >= size)
       return 0;                               // базова задача
   return abs(a[i]) + SumAbsFrom(a, size, i + 1);
}
 
void CollectEveryOther(const int* a, int* t, const int size, int i, int& k)
{
   if (i < size)
   {
       t[k++] = a[i];
       CollectEveryOther(a, t, size, i + 2, k);
   }
}
 
void CopyArray(const int* src, int* dest, const int size, int i)
{
   if (i < size)
   {
       dest[i] = src[i];
       CopyArray(src, dest, size, i + 1);
   }
}
 
void MoveEvenPositionsFirst(int* a, const int size)
{
   int* t = new int[size];         // допоміжний динамічний масив
   int k = 0;
 
   CollectEveryOther(a, t, size, 1, k);    // позиції 2, 4, ... (індекси 1, 3, ...)
   CollectEveryOther(a, t, size, 0, k);    // позиції 1, 3, ... (індекси 0, 2, ...)
   CopyArray(t, a, size, 0);
 
   delete[] t;
}
