#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

// 定义图的节点结构体
typedef struct Node {
    int vertex;
    struct Node* next;
} Node;

// 定义图的结构体
typedef struct {
    Node** adjacencyList;
    int vertexNum;
} Graph;

// 初始化图
void initGraph(Graph* graph, int vNum) {
    graph->vertexNum = vNum;
    graph->adjacencyList = (Node**)malloc(vNum * sizeof(Node*));
    for (int i = 0; i < vNum; i++) {
        graph->adjacencyList[i] = NULL;
    }
}

// 添加边
void addEdge(Graph* graph, int v1, int v2) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->vertex = v2;
    newNode->next = graph->adjacencyList[v1 - 1];
    graph->adjacencyList[v1 - 1] = newNode;
}

// 深度优先遍历的辅助函数
void dfsUtil(Graph graph, bool visited[], int start) {
    visited[start - 1] = true;
    printf("%d ", start);
    Node* current = graph.adjacencyList[start - 1];
    while (current!= NULL) {
        if (!visited[current->vertex - 1]) {
            dfsUtil(graph, visited, current->vertex);
        }
        current = current->next;
    }
}

// 深度优先遍历
void dfs(Graph graph, int start) {
    bool* visited = (bool*)malloc(graph.vertexNum * sizeof(bool));
    for (int i = 0; i < graph.vertexNum; i++) {
        visited[i] = false;
    }
    dfsUtil(graph, visited, start);
    free(visited);
}

// 广度优先遍历
void bfs(Graph graph, int start) {
    bool* visited = (bool*)malloc(graph.vertexNum * sizeof(bool));
    for (int i = 0; i < graph.vertexNum; i++) {
        visited[i] = false;
    }

    int* queue = (int*)malloc(graph.vertexNum * sizeof(int));
    int front = 0;
    int rear = 0;

    visited[start - 1] = true;
    queue[rear++] = start;

    while (front < rear) {
        int current = queue[front++];
        Node* node = graph.adjacencyList[current - 1];
        while (node!= NULL) {
            if (!visited[node->vertex - 1]) {
                visited[node->vertex - 1] = true;
                queue[rear++] = node->vertex;
            }
            node = node->next;
        }
    }

    for (int i = 0; i < graph.vertexNum; i++) {
        if (i + 1!= start && visited[i]) {
            printf("%d ", i + 1);
        }
    }

    free(queue);
    free(visited);
}

int main() {
    Graph graph;
    int vertexNum;

    // 输入顶点数量
    printf("请输入顶点数量：");
    scanf("%d", &vertexNum);

    initGraph(&graph, vertexNum);

    // 输入各顶点的邻接顶点
    for (int i = 1; i <= vertexNum; i++) {
        int num;
        printf("请输入顶点%d指向的邻接顶点数量：", i);
        scanf("%d", &num);

        printf("请输入顶点%d指向的邻接顶点：", i);
        for (int j = 0; j < num; j++) {
            int adjVertex;
            scanf("%d", &adjVertex);
            addEdge(&graph, i, adjVertex);
        }
    }

    printf("深度优先遍历: ");
    dfs(graph, 1);
    printf("\n");

    printf("广度优先遍历: ");
    bfs(graph, 1);
    printf("\n");

    return 0;
}
