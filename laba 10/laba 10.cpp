#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>
#include <locale.h>
#include <climits>
#include <queue>
std::queue <int> Q;
int** createG(int size) {
    int** G = NULL;
    G = (int**)malloc(size * sizeof(int*));
    for (int i = 0; i < size; i++) {
        G[i] = (int*)malloc(size * sizeof(int));
    }
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            G[i][j] = rand() % 6;
            if (i == j) {
                G[i][j] = 0;
            }
            G[j][i] = G[i][j];
        }
    }
    return G;
}

void printG(int** G, int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            printf("%d  ", G[i][j]);
        }
        printf("\n");
    }
    return;
}

void bfs(int** G, int size, int v, int* dist) {
    dist[v] = 0;
    Q.push(v);
    while (!Q.empty()) {
        v = Q.front();
        Q.pop();
        for (int i = 0; i < size; i++) {
            if (G[v][i] > 0 && dist[i] > dist[v] + G[v][i]) {
                Q.push(i);
                dist[i] = dist[v] + G[v][i];
            }
        }
    }
}
int main()
{
    int v;
    setlocale(LC_ALL, "Rus");
    int size;
    printf("Введите размер матрицы \n");
    scanf("%d", &size);
    int** G1 = createG(size);
    printf("Матрица 1\n");
    printG(G1, size);

    printf("Введите стартовую вершину \n");
    scanf("%d", &v);
    int* dist = NULL;
    dist = (int*)malloc(size * sizeof(int*));
    for (int i = 0; i < size; i++) {
        dist[i] = 100000;
    }

    bfs(G1, size, v, dist);

    for (int i = 0; i < size; i++) {
        printf("расстояние от %d до %d вершины = %d \n", v, i, dist[i]);
    }

    return 0;
}