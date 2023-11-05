#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define INFINITY INT_MAX
#define MAX_VERTEX_NUM 20
#define SUCCESS 1
#define ERROR 0

// 图类型-有向图，有向网/有向带权图，无向图，无向网/无向带权图
typedef enum {DG, DN, UDG, UDN} GraphType;

// #define ADJ_LIST
#define ADJ_MATRIX

#if defined(ADJ_LIST)
// 弧
typedef struct ArcNode{
    int adjVex;     // 弧指向顶点位置
    int weight;     // 弧权值
    struct ArcNode *nextArcs;   // 指向下一条弧
    // ArcInfo *info;      // 弧存储的信息
}ArcNode;

// 顶点
typedef struct VexNode{
    char data;  // 弧信息
    ArcNode *firstArc;  // 指向依附该顶点的第一条弧的指针(链式存储)
}VexNode, AdjList[MAX_VERTEX_NUM];

// 图
typedef struct AdjacencyListGraph{
    AdjList vextics;    // 包含的邻接表
    int Vexnum, Arcnum; // 顶点总数和弧总数
    GraphType gType;    // 图类型
}ALGraph;

// 在顶点数组中定位顶点
int LocateVex(ALGraph Graph, char v){
    for(int i = 0; i < Graph.Vexnum; ++i){
        if(Graph.vextics[i].data == v) return i;
    }
    return -1;
}

// 创建无向带权图
int CreateUDN(ALGraph *Graph, int vexnum, int arcnum){
    Graph->gType = UDN;
    Graph->Vexnum = vexnum;
    Graph->Arcnum = arcnum;

    printf("----%d vertexes and %d arces----\n", vexnum, arcnum);

    printf("input vextexes:\n");
    for(int i = 0; i < Graph->Vexnum; ++i){
        // 输入vexnum个顶点
        scanf("%c", &Graph->vextics[i].data);
        Graph->vextics[i].firstArc = NULL;
        printf("%c i=%d\n", Graph->vextics[i].data, i);
    }

    printf("\ninput arcex:\n");
    for(int k = 0; k < Graph->Arcnum; ++k){
        int vex1, vex2, weight;
        scanf("%c %c %d", &vex1, &vex2, &weight);

        // 在顶点数组中找到两顶点的位置
        int i = LocateVex(*Graph, vex1);
        int j = LocateVex(*Graph, vex2);

        // 将弧以头插法插入顶点的弧链表
        ArcNode *p = (ArcNode*)malloc(sizeof(ArcNode));
        p->adjVex = j;
        p->weight = weight;
        p->nextArcs = Graph->vextics[i].firstArc;
        Graph->vextics[i].firstArc = p;

        p = (ArcNode*)malloc(sizeof(ArcNode));
        p->adjVex = i;
        p->weight = weight;
        p->nextArcs = Graph->vextics[j].firstArc;
        Graph->vextics[j].firstArc = p;
    }
    printf("\n--------\n");
    return SUCCESS;
}
#endif // !ADJ_LIST

#if defined(ADJ_MATRIX)
// 弧
typedef struct ArcNode{
    int adj;    // 
}ArcNode, AdjMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM];

// 图
typedef struct AdjacencyMatrixGraph{

}AMGraph;

int LocateVex(AMGraph Graph, char v){

}
#endif // !ADJ_MATRIX