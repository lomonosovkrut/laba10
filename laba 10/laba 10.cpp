
#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>
#include <locale.h>
#include <climits>
#include <queue>
#include <vector>
#include <algorithm>

// Функция для создания графа
int** createG(int size) {
    int** G = (int**)malloc(size * sizeof(int*));
    for (int i = 0; i < size; i++) {
        G[i] = (int*)malloc(size * sizeof(int));
    }
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            G[i][j] = rand() % 6; // случайный вес
            if (i == j) {
                G[i][j] = 0; // нулевой вес на диагонали
            }
            G[j][i] = G[i][j]; // симметричность
        }
    }
    return G;
}

// Функция для вывода графа
void printG(int** G, int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            printf("%d  ", G[i][j]);
        }
        printf("\n");
    }
}

// Алгоритм BFS для нахождения кратчайших расстояний
void bfs(int** G, int size, int v, int* dist) {
    std::queue<int> Q; // Локальная очередь
    for (int i = 0; i < size; i++) {
        dist[i] = INT_MAX; // Инициализация расстояний
    }
    dist[v] = 0;
    Q.push(v);
    while (!Q.empty()) {
        int current = Q.front();
        Q.pop();
        for (int i = 0; i < size; i++) {
            if (G[current][i] > 0 && dist[i] > dist[current] + G[current][i]) {
                Q.push(i);
                dist[i] = dist[current] + G[current][i];
            }
        }
    }
}

int main() {
    setlocale(LC_ALL, "Rus");
    int size, v;

    // Ввод размера графа
    printf("Введите размер матрицы \n");
    scanf("%d", &size);

    // Создание и вывод графа
    int** G1 = createG(size);
    printf("Матрица смежности графа:\n");
    printG(G1, size);

    // Ввод стартовой вершины
    printf("Введите стартовую вершину \n");
    scanf("%d", &v);

    // Массив для хранения расстояний
    int* dist = (int*)malloc(size * sizeof(int));

    // Нахождение кратчайших расстояний от стартовой вершины
    bfs(G1, size, v, dist);
    for (int i = 0; i < size; i++) {
        printf("Расстояние от %d до %d вершины = %d \n", v, i, dist[i]);
    }

    // Нахождение эксцентриситетов
    std::vector<int> eccentricities(size, 0);
    for (int i = 0; i < size; i++) {
        bfs(G1, size, i, dist);
        eccentricities[i] = *std::max_element(dist, dist + size);
    }

    // Вывод эксцентриситетов
    printf("Эксцентриситеты вершин:\n");
    for (int i = 0; i < size; i++) {
        printf("Вершина %d: %d\n", i, eccentricities[i]);
    }

    // Нахождение радиуса и диаметра
    int radius = *std::min_element(eccentricities.begin(), eccentricities.end());
    int diameter = *std::max_element(eccentricities.begin(), eccentricities.end());

    printf("Радиус графа: %d\n", radius);
    printf("Диаметр графа: %d\n", diameter);

    // Нахождение центральных и периферийных вершин
    printf("Центральные вершины: ");
    for (int i = 0; i < size; i++) {
        if (eccentricities[i] == radius) {
            printf("%d ", i);
        }
    }
    printf("\n");

    printf("Периферийные вершины: ");
    for (int i = 0; i < size; i++) {
        if (eccentricities[i] == diameter) {
            printf("%d ", i);
        }
    }
    printf("\n");

    // Освобождение памяти
    for (int i = 0; i < size; i++) {
        free(G1[i]);
    }
    free(G1);
    free(dist);

    return 0;
}
