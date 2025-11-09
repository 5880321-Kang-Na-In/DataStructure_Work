#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>
#include <stdbool.h> // bool 타입 사용

// 상수 정의
#define V 10            // 정점의 개수 (Vertices)
#define E 20            // 간선의 개수 (Edges)
#define INF INT_MAX     // 무한대를 나타내는 값

// 그래프의 인접 행렬을 저장할 전역 배열
int adj[V][V];

// 모든 쌍 최단 경로 결과를 저장할 배열
int all_shortest_paths[V][V];

// --- 1. 그래프 초기화 및 무작위 생성 ---
void initialize_and_generate_graph() {
    int i, j;

    // 인접 행렬 초기화: 0은 자기 자신, INF는 연결 없음
    for (i = 0; i < V; i++) {
        for (j = 0; j < V; j++) {
            if (i == j) {
                adj[i][j] = 0;
            }
            else {
                adj[i][j] = INF;
            }
        }
    }

    // 무작위 그래프 생성 (간선 E개)
    srand(time(NULL));
    int edges_count = 0;
    while (edges_count < E) {
        int u = rand() % V;
        int v = rand() % V;

        if (u != v && adj[u][v] == INF) {
            // 무작위 가중치 (1 ~ 10)
            int weight = (rand() % 10) + 1;

            // 무방향 그래프이므로 양방향 모두 설정
            adj[u][v] = weight;
            adj[v][u] = weight;

            edges_count++;
        }
    }
}

// --- 2. 다익스트라 알고리즘 (특정 출발 노드에서 모든 노드까지의 최단 경로) ---
void dijkstra(int start_node) {
    // dist: start_node로부터 각 노드까지의 최단 거리를 저장
    int dist[V];
    // visited: 이미 최단 거리가 확정된 노드인지 표시
    bool visited[V];

    // 초기화
    for (int i = 0; i < V; i++) {
        dist[i] = INF;
        visited[i] = false;
    }
    dist[start_node] = 0;

    // V-1번 반복 (총 V개의 노드를 방문)
    for (int count = 0; count < V; count++) {

        // 1. 아직 방문하지 않은 노드 중 최소 거리를 가진 노드를 선택 (min_dist)
        int min_dist = INF;
        int u = -1; // 선택된 노드의 인덱스

        for (int i = 0; i < V; i++) {
            if (!visited[i] && dist[i] <= min_dist) {
                min_dist = dist[i];
                u = i;
            }
        }

        // 최단 경로를 찾지 못했거나 (그래프가 단절된 경우) 모든 노드를 방문했으면 종료
        if (u == -1 || min_dist == INF) {
            break;
        }

        // 선택된 노드 u를 방문 처리
        visited[u] = true;

        // 2. 선택된 노드 u와 연결된 이웃 노드들의 거리 갱신
        for (int v = 0; v < V; v++) {
            // v가 방문되지 않았고, u와 v 사이에 간선이 존재하며 (adj[u][v] != INF),
            // u를 거쳐 v로 가는 경로가 현재 v의 거리보다 짧다면 갱신
            if (!visited[v] && adj[u][v] != INF && dist[u] != INF
                && dist[u] + adj[u][v] < dist[v]) {

                dist[v] = dist[u] + adj[u][v];
            }
        }
    }

    // 계산된 최단 거리를 모든 쌍 결과를 저장하는 배열에 복사
    for (int i = 0; i < V; i++) {
        all_shortest_paths[start_node][i] = dist[i];
    }
}

// --- 3. 결과 출력 ---
void print_all_shortest_paths() {
    printf("==========================================\n");
    printf("     다익스트라 반복을 이용한 최단 경로\n");
    printf("==========================================\n");
    printf("정점 수: %d, 간선 수: %d\n", V, E);
    printf("------------------------------------------\n");
    printf("출발 -> 도착: 최단 경로 (INF는 도달 불가능)\n");
    printf("------------------------------------------\n");

    int count = 0; // 노드 쌍 카운트 (V*(V-1)/2 = 45쌍)

    // V*(V-1)/2 쌍만 출력 (i < j)
    for (int i = 0; i < V; i++) {
        for (int j = i + 1; j < V; j++) {
            printf("%2d -> %2d: ", i, j);
            if (all_shortest_paths[i][j] == INF) {
                printf("INF (연결되지 않음)\n");
            }
            else {
                // 무방향 그래프이므로 i->j와 j->i는 거리가 같아야 합니다.
                printf("%3d\n", all_shortest_paths[i][j]);
            }
            count++;
        }
    }
    printf("------------------------------------------\n");
    printf("총 노드 쌍(i < j) 개수: %d쌍\n", count);
    printf("==========================================\n");
}

int main() {
    // 1. 그래프 초기화 및 무작위 간선 생성
    initialize_and_generate_graph();

    // 2. 다익스트라 알고리즘 V번 반복 실행 (모든 노드를 출발점으로)
    for (int i = 0; i < V; i++) {
        dijkstra(i);
    }

    // 3. 최단 경로 결과 출력
    print_all_shortest_paths();

    return 0;
}