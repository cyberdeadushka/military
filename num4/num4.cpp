
/*
    Задача №4
Группа солдат-новобранцев прибыла в армейскую часть N666. После знакомства с прапорщиком стало очевидно, что 
от работ на кухне по очистке картофеля спасти солдат может только чудо. Прапорщик, будучи не в состоянии запомнить 
фамилии, пронумеровал новобранцев от 1 до N. После этого он велел им построиться по росту (начиная с самого высокого). 
С этой несложной задачей могут справиться даже совсем необученные новобранцы, да вот беда, прапорщик уверил себя, что 
знает про некоторых солдат, кто из них кого выше, и это далеко не всегда соответствует истине.

После трех дней обучения новобранцам удалось выяснить, что знает (а точнее, думает, что знает) прапорщик. Помогите им, 
используя эти знания, построиться так, чтобы товарищ прапорщик остался доволен.

Входные данные
    Сначала на вход программы поступают числа N и M (1 < N <= 100, 1 <= M <= 5000) – количество солдат в роте и 
    количество пар солдат, про которых прапорщик знает, кто из них выше. Далее идут эти пары чисел A и B по одной 
    на строке (1 <= A,B <= N), что означает, что, по мнению прапорщика, солдат A выше, чем B. Не гарантируется, 
    что все пары чисел во входных данных различны.

Выходные данные
    В первой строке выведите "Yes" (если можно построиться так, чтобы прапорщик остался доволен) или "No" (если нет). 
    После ответа "Yes" на следующей строке выведите N чисел, разделенных пробелами, - одно из возможных построений.

*/

#include <iostream>
#include <iomanip>
#include <vector>

using namespace std;

int range(int lowBorder, int highBorder); //проверка на правильность ввода с установленным диапазоном
bool dfs_cycle(vector<int> adj[], vector<char> cl, vector<int> p, int v); // проверка на ацикличность графа
void dfs(vector<int> adj[], bool* used, int v); // обход в глубину для топологической сортировки
void topological_sort(vector<int> adj[], bool* used, int N);
vector<int> answer; // ответ - одно из возможных построений

int main()
{
    setlocale(0, "");
    cout << "\nВведите кол-во новобранцев N: ";
    int N = range(1, 100); // N э (1, 100]
    cout << "\nВведите кол-во пар M: ";
    int M = range(0, 5001); // M э [1, 5000]

    vector<int>* g = new vector<int>[N]; // граф
    bool* used = new bool[N];
    for (int i = 0; i < N; i++)
        used[i] = 0;
 
    cout << "\n Введите пары: \n";
    for (int i = 0; i < M; i++) // заполнение
    {
        // номера вершин, соединенных ребром: u -> v
        int u = range(0, INT_MAX);
        int v = range(-1, N);
        u--, v--;
        g[u].push_back(v);
    }
   
    vector<char> cl; // массив цветов (для проверки на цикличность графов)
    vector<int> p; // воспомогательный вектор

    p.assign(N, -1); // присваиваем всему массиву значение -1
    cl.assign(N, 0);
    
    bool cycle = false;
    for (int i = 0; i < N; ++i)
        if (dfs_cycle(g, cl, p, i))//если цикл найден
        {
            cycle = true;
            break;
        }

    cout << "\nВозможно ли построиться так, чтобы прапорщик остался доволен?";
    if (cycle == false) // если граф не содержит циклов, то да
    {                   // потому что тогда топологическая сортировка возможна
        cout << " Yes \n";
        topological_sort(g, used, N);
        for (size_t i = 0; i < answer.size(); i++) // вывод одного из возможных построений
            cout << (answer[i] + 1) << " ";
    }
    else cout << " No \n";

    cout << endl;
    system("pause");
    return 0;
}

int range(int lowBorder, int highBorder) //проверка на правильность ввода с установленным диапазоном
{
    int range;

    while (!(cin >> range && range > lowBorder&& range <= highBorder))
    {
        cout << "\nВвод некорректен. Повторите ввод: ";
        cin.clear();
        while (cin.get() != '\n');
    }
    return range;
}

bool dfs_cycle(vector<int> adj[], vector<char> cl, vector<int> p, int v) // проверка на ацикличность графа
{
    cl[v] = 1; // - зашли в вершину в первый раз
    for (size_t i = 0; i < adj[v].size(); ++i) 
    {
        int to = adj[v][i];
        if (cl[to] == 0) //если вершина не была посещена
        {
            p[to] = v;
            if (dfs_cycle(adj, cl, p, to)) // запускаем поиск в глубину
                return true;
        }
        else if (cl[to] == 1) // если вершина была посещена
            return true;
    }
    cl[v] = 2;
    return false;
}

void dfs(vector<int> adj[], bool* used, int v) // функция обхода в глубину
{                                              // используемая топологической сортировкой
    used[v] = true;
    for (size_t i = 0; i < adj[v].size(); ++i) 
    {
        int to = adj[v][i];
        if (!used[to])
            dfs(adj, used, to);
    }
    answer.push_back(v); // добавляем вершину в момент выхода 
}

void topological_sort(vector<int> adj[], bool* used, int N)
{
    for (int i = 0; i < N; ++i)
        used[i] = false;
    answer.clear();
    for (int i = 0; i < N; ++i)
        if (!used[i]) // если вершина была ранее посещена, то обход не запустится
            dfs(adj, used, i);
    reverse(answer.begin(), answer.end());
}