
/*
    ������ �4
������ ������-����������� ������� � ��������� ����� N666. ����� ���������� � ����������� ����� ��������, ��� 
�� ����� �� ����� �� ������� ��������� ������ ������ ����� ������ ����. ���������, ������ �� � ��������� ��������� 
�������, ������������ ����������� �� 1 �� N. ����� ����� �� ����� �� ����������� �� ����� (������� � ������ ��������). 
� ���� ��������� ������� ����� ���������� ���� ������ ����������� ����������, �� ��� ����, ��������� ������ ����, ��� 
����� ��� ��������� ������, ��� �� ��� ���� ����, � ��� ������ �� ������ ������������� ������.

����� ���� ���� �������� ����������� ������� ��������, ��� ����� (� ������, ������, ��� �����) ���������. �������� ��, 
��������� ��� ������, ����������� ���, ����� ������� ��������� ������� �������.

������� ������
    ������� �� ���� ��������� ��������� ����� N � M (1 < N <= 100, 1 <= M <= 5000) � ���������� ������ � ���� � 
    ���������� ��� ������, ��� ������� ��������� �����, ��� �� ��� ����. ����� ���� ��� ���� ����� A � B �� ����� 
    �� ������ (1 <= A,B <= N), ��� ��������, ���, �� ������ ����������, ������ A ����, ��� B. �� �������������, 
    ��� ��� ���� ����� �� ������� ������ ��������.

�������� ������
    � ������ ������ �������� "Yes" (���� ����� ����������� ���, ����� ��������� ������� �������) ��� "No" (���� ���). 
    ����� ������ "Yes" �� ��������� ������ �������� N �����, ����������� ���������, - ���� �� ��������� ����������.

*/

#include <iostream>
#include <iomanip>
#include <vector>

using namespace std;

int range(int lowBorder, int highBorder); //�������� �� ������������ ����� � ������������� ����������
bool dfs_cycle(vector<int> adj[], vector<char> cl, vector<int> p, int v); // �������� �� ������������ �����
void dfs(vector<int> adj[], bool* used, int v); // ����� � ������� ��� �������������� ����������
void topological_sort(vector<int> adj[], bool* used, int N);
vector<int> answer; // ����� - ���� �� ��������� ����������

int main()
{
    setlocale(0, "");
    cout << "\n������� ���-�� ����������� N: ";
    int N = range(1, 100); // N � (1, 100]
    cout << "\n������� ���-�� ��� M: ";
    int M = range(0, 5001); // M � [1, 5000]

    vector<int>* g = new vector<int>[N]; // ����
    bool* used = new bool[N];
    for (int i = 0; i < N; i++)
        used[i] = 0;
 
    cout << "\n ������� ����: \n";
    for (int i = 0; i < M; i++) // ����������
    {
        // ������ ������, ����������� ������: u -> v
        int u = range(0, INT_MAX);
        int v = range(-1, N);
        u--, v--;
        g[u].push_back(v);
    }
   
    vector<char> cl; // ������ ������ (��� �������� �� ����������� ������)
    vector<int> p; // ���������������� ������

    p.assign(N, -1); // ����������� ����� ������� �������� -1
    cl.assign(N, 0);
    
    bool cycle = false;
    for (int i = 0; i < N; ++i)
        if (dfs_cycle(g, cl, p, i))//���� ���� ������
        {
            cycle = true;
            break;
        }

    cout << "\n�������� �� ����������� ���, ����� ��������� ������� �������?";
    if (cycle == false) // ���� ���� �� �������� ������, �� ��
    {                   // ������ ��� ����� �������������� ���������� ��������
        cout << " Yes \n";
        topological_sort(g, used, N);
        for (size_t i = 0; i < answer.size(); i++) // ����� ������ �� ��������� ����������
            cout << (answer[i] + 1) << " ";
    }
    else cout << " No \n";

    cout << endl;
    system("pause");
    return 0;
}

int range(int lowBorder, int highBorder) //�������� �� ������������ ����� � ������������� ����������
{
    int range;

    while (!(cin >> range && range > lowBorder&& range <= highBorder))
    {
        cout << "\n���� �����������. ��������� ����: ";
        cin.clear();
        while (cin.get() != '\n');
    }
    return range;
}

bool dfs_cycle(vector<int> adj[], vector<char> cl, vector<int> p, int v) // �������� �� ������������ �����
{
    cl[v] = 1; // - ����� � ������� � ������ ���
    for (size_t i = 0; i < adj[v].size(); ++i) 
    {
        int to = adj[v][i];
        if (cl[to] == 0) //���� ������� �� ���� ��������
        {
            p[to] = v;
            if (dfs_cycle(adj, cl, p, to)) // ��������� ����� � �������
                return true;
        }
        else if (cl[to] == 1) // ���� ������� ���� ��������
            return true;
    }
    cl[v] = 2;
    return false;
}

void dfs(vector<int> adj[], bool* used, int v) // ������� ������ � �������
{                                              // ������������ �������������� �����������
    used[v] = true;
    for (size_t i = 0; i < adj[v].size(); ++i) 
    {
        int to = adj[v][i];
        if (!used[to])
            dfs(adj, used, to);
    }
    answer.push_back(v); // ��������� ������� � ������ ������ 
}

void topological_sort(vector<int> adj[], bool* used, int N)
{
    for (int i = 0; i < N; ++i)
        used[i] = false;
    answer.clear();
    for (int i = 0; i < N; ++i)
        if (!used[i]) // ���� ������� ���� ����� ��������, �� ����� �� ����������
            dfs(adj, used, i);
    reverse(answer.begin(), answer.end());
}