#include<stdio.h>
#include<stdlib.h>

#define MAX_VERTEX 10

typedef struct GraphNode{ // 그래프 노드 구조체
    int vertex; //노드의 번호
    struct GraphNode* link; //다음 노드를 가리키는 포인터
}GraphNode;

typedef struct GraphType{ // 그래프 구조체
    int n; // 노드의 개수   
    GraphNode* adj_list[MAX_VERTEX]; // 노드의 개수만큼의 포인터 배열
    int visited[MAX_VERTEX]; // 방문 여부를 저장하는 배열
}GraphType;


void InitializeGraph(GraphType* Graph);
void InsertVertex(GraphType* Graph);
void InsertEdge(GraphType* Graph, int start, int end);
void DepthFirstSearch(GraphType* Graph, int v);
void BreathFirstSearch(GraphType* Graph);
void Print(GraphType* Graph);
void Quit(GraphType* Graph);

int main(){

    GraphType* Graph = (GraphType*)malloc(sizeof(GraphType));
    Graph->n = 0;
    Graph->adj_list[0] = NULL;
    Graph->visited[0] = 0;
    
    while(1){


        printf("[-----       [KIMGEONWOO]               [2021041010]      -----]\n");

        printf("----------------------------------------------------------------\n");
        printf("                           Grape Price                          \n");
        printf("----------------------------------------------------------------\n");
        printf(" Initialize Graph   = z                                         \n");
        printf(" Insert Vertex      = v                  Insert Edge         = e\n");
        printf(" Depth First Search = d                  Breath First Search = b\n");
        printf(" Print              = p                  Quit                = q\n");
        printf("----------------------------------------------------------------\n");

        printf("Command = ");

        char n = 'q';
        scanf("%c", &n);
        while(getchar() != '\n');

        if(n == 'q' || n == 'Q'){
            Quit(Graph);
            break;
        }
        else if (n == 'z' || n == 'Z'){
            InitializeGraph(Graph);
        }
        else if (n == 'v' || n == 'V'){
            InsertVertex(Graph);
        }
        else if (n == 'e' || n == 'E'){
            int start, end;
            printf("Input Start Vertex Number: ");
            scanf("%d", &start);
            printf("Input End Vertex Number: ");
            scanf("%d", &end);
            while(getchar() != '\n');
            if(start < 0 || end < 0){
                printf("Wrong Vertex Number\n");
                continue;
            }
            else if(start == end){
                printf("Same Vertex Number\n");
                continue;
            }
            InsertEdge(Graph, start, end);
        }
        else if (n == 'd' || n == 'D'){
            DepthFirstSearch(Graph, 0);
            printf("\n");
        }
        else if (n == 'b' || n == 'B'){
            BreathFirstSearch(Graph);
        }
        else if (n == 'p' || n == 'P'){
            Print(Graph);
        }
        else{
            printf("Wrong Input\n");
        }


    }
    return 0;

}

void InitializeGraph(GraphType *Graph){
    for(int i = 0; i < MAX_VERTEX; i++){
        Graph->adj_list[i] = NULL; //포인터 배열을 NULL로 초기화
        Graph->visited[i] = 0; //방문 여부를 저장하는 배열을 0으로 초기화
    }
    Graph->n = 0; //노드의 개수를 0으로 초기화
    printf("Initialize Graph\n");\

    return;

}
void InsertVertex(GraphType* Graph){
    if(Graph->n >= MAX_VERTEX){ //노드의 개수가 최대 노드 개수보다 크거나 같으면
        printf("Graph Full\n"); //그래프가 가득 찼다고 출력
        return;
    }
    Graph->n++; //노드의 개수를 1 증가
    printf("Insert Vertex\n");
}
void InsertEdge(GraphType* Graph, int start, int end){
    GraphNode* node; 
    GraphNode* current;
    GraphNode* previous = NULL;
    
    //링크를 오름차순으로 하면 서치할때 작은것부터 찾아간다.

    if(start >= Graph->n || end >= Graph->n){ 
        printf("Wrong Vertex Number\n");
        return;
    }

    node = (GraphNode*)malloc(sizeof(GraphNode));  //그래프 노드 구조체 동적 할당
    node->vertex = end;  //노드의 번호를 입력 받은 값으로 설정
    node->link = NULL; //다음 노드를 가리키는 포인터를 NULL로 설정

    current = Graph->adj_list[start]; //현재 노드를 시작 노드로 설정

    while(current != NULL && current->vertex < end){ //현재 노드가 NULL이 아니고 현재 노드의 번호가 입력 받은 값보다 작으면
        previous = current; //이전 노드에 현재 노드를 저장
        current = current->link; //현재 노드를 다음 노드로 설정
    }

    if(previous == NULL){ //이전 노드가 NULL이면
        node->link = Graph->adj_list[start]; //노드의 다음 노드를 시작 노드로 설정
        Graph->adj_list[start] = node; //시작 노드를 노드로 설정
    } else {
        node->link = previous->link; //노드의 다음 노드를 이전 노드의 다음 노드로 설정
        previous->link = node; //이전 노드의 다음 노드를 노드로 설정
    }

    printf("Insert Edge\n");
}
void DepthFirstSearch(GraphType* Graph, int v){ //상단 노드는 0으로 고정 GPT의 도움을 받았습니다.
    GraphNode* w;
    Graph->visited[v] = 1; // 정점 v를 방문했다고 표시합니다.
    printf("%5d", v); // 정점 v를 출력합니다.

    for(w = Graph->adj_list[v]; w; w = w->link){ // 인접한 모든 정점에 대해
        if(!Graph->visited[w->vertex]){ // 아직 방문하지 않은 정점이라면
            DepthFirstSearch(Graph, w->vertex); // 재귀 호출합니다.
        }
    }
}

void BreathFirstSearch(GraphType* Graph){ //구현이 어려워서 GPT에 도음을 받아 코드를 만들었습니다.
    int i, j = 0;
    GraphNode* w;
    int* queue = (int*)malloc(Graph->n * sizeof(int)); // 큐를 배열로 모방합니다.
    int front = 0, rear = 0; // 배열의 앞과 뒤를 가리키는 인덱스입니다.

    for(i = 0; i < Graph->n; i++){
        Graph->visited[i] = 0; // 모든 정점을 방문하지 않은 상태로 초기화합니다.
    }

    int start = 0; // 시작 정점을 0으로 고정합니다.
    printf("%5d", start); // 시작 정점을 출력합니다.
    Graph->visited[start] = 1; // 시작 정점을 방문했다고 표시합니다.
    queue[rear++] = start; // 시작 정점을 큐에 추가합니다.

    while(front != rear){ // 큐가 비어있지 않은 동안 반복합니다.
        int v = queue[front++]; // 큐에서 정점을 꺼냅니다.
        for(w = Graph->adj_list[v]; w; w = w->link){ // 인접한 모든 정점에 대해
            if(!Graph->visited[w->vertex]){ // 아직 방문하지 않은 정점이라면
                printf("%5d", w->vertex); // 정점을 출력합니다.
                queue[rear++] = w->vertex; // 정점을 큐에 추가합니다.
                Graph->visited[w->vertex] = 1; // 정점을 방문했다고 표시합니다.
            }
        }
    }
    printf("\n");
    free(queue); // 큐를 해제합니다.

    for(i = 0; i < Graph->n; i++){
        Graph->visited[i] = 0; // 모든 정점을 방문하지 않은 상태로 초기화합니다.
    }
}
void Print(GraphType* Graph){
    int i;
    GraphNode* p;   //그래프 노드 구조체 포인터 선언
    for(i = 0; i < Graph->n; i++){ 
        printf("Vertex %d : ", i); //노드 번호 출력
        p = Graph->adj_list[i]; //노드의 다음 노드를 가리키는 포인터를 노드로 설정
        while(p != NULL){ //포인터가 NULL이 아닐 때까지 반복
            printf(" %d ", p->vertex); //포인터가 가리키는 노드의 번호 출력
            p = p->link; //포인터를 다음 노드로 설정
            if(p != NULL){ //포인터가 NULL이 아니면
                printf("-> "); //화살표 출력
            }
        }
        printf("\n");
    }
}
void Quit(GraphType* Graph){
    int i;
    GraphNode* p; 
    GraphNode* temp; 
    for(i = 0; i < Graph->n; i++){ //노드의 개수만큼 반복
        p = Graph->adj_list[i]; //노드의 다음 노드를 가리키는 포인터를 노드로 설정
        while(p != NULL){ //포인터가 NULL이 아닐 때까지 반복
            temp = p; //임시 포인터에 포인터를 저장
            p = p->link; //포인터를 다음 노드로 설정
            free(temp); //임시 포인터 동적 할당 해제
        }
    }
    free(Graph); //그래프 동적 할당 해제
    printf("Quit\n");
}
