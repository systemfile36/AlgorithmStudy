// A_StarAlgorithmExample.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>
#include <queue>
#include "GraphAdj.h" //인접행렬 헤더

//https://blog.naver.com/loliisjinri/222685578542 참고

//노드를 정의함
struct Node
{
    //f(n)의 값, 우선 순위로 사용될 것
    int f_value;
    int index;
    char name;
    
    //편한 생성을 위한 구조체 생성자
    Node(int f, int i, char c) : f_value(f), index(i), name(c) {}

    //우선 순위 큐를 위한 연산자 오버로딩
    //f_value가 작으면 크다고 리턴한다.
    //cpp의 priority_queue는 큰 것이 Top을 유지하기 때문에
    //크고 작은 것을 반대로 뒤집어주면 작은 값이 앞에 온다.
    //함수 뒤의 const는 비교 연산을 위함, 이 연산자의 왼쪽 피연산자가 const임을 의미, 함수 내에서 변경이 일어나지 않음을 보장
    bool operator<(Node n) const
    {
        return this->f_value > n.f_value;
    }

    //노드 끼리 일치 비교할 때
    bool operator==(const Node n) const
    {
        return this->index == n.index;
    }
};



bool IsContainNode(std::vector<Node>& vector, int index);

int main()
{
    GraphAdj graph;

    int startIndex;

    int goalIndex;

    int shortestDistance = INF;

    //출발점으로부터 노드까지의 거리, g(n)에 사용하기 위함
    //d[Node.index]는 출발점으로부터 Node까지의 거리이다.
    int d[MAX_VTXS];

    //휴리스틱 함수 목록
    //목적지 까지의 직선 거리
    //h[Node.index]는 그 Node의 h(n)을 뜻한다.
    int h[MAX_VTXS] = { 0 };

    //A* 를 위한 우선 순위 큐
    std::priority_queue<Node> OpenQue;
    //우선 순위 큐, 거리(f(n))가 짧은 것이 앞에 온다.

    //방문한 노드 기록
    std::vector<Node> Close;

    //최단 경로 저장
    std::vector<Node> sPath;
    
    std::string fname;
    std::cout << "Input Your Graph File Name : ";
    std::cin >> fname;

    //먼저 그래프를 로드함
    if (!graph.LoadGraph(fname))
    {
        std::cout << std::endl << "No file" << std::endl;
        exit(0);
    }

    std::cout << std::endl;

    //노드 개수 만큼 h(n)값 입력 받음
    for (int i = 0; i < graph.GetVtxCount(); i++)
    {
        std::cout << "Input Your Heuristic(" << graph.VertexNames[i] << ") : ";
        std::cin >> h[i];
    }

    std::cout << std::endl;

    //시작 노드
    std::cout << "Input your Start Node's Index : ";
    std::cin >> startIndex;
    std::cout << std::endl;

    //목표 노드
    std::cout << "Input your Goal Node's Index : ";
    std::cin >> goalIndex;
    
    //d[]값들 설정, d[startIndex]는 초기값 0, 나머지는 INF
    for (int i = 0; i < graph.GetVtxCount(); i++)
    {
        d[i] = INF;
    }
    d[startIndex] = 0;

    std::cout << std::endl;

    std::cout << "Press Enter to Start Find Path...";
    system("pause > nul");
    
    system("cls");

    //시작 점 노드를 넣음
    Node start(0, startIndex, graph.VertexNames[startIndex]);
    OpenQue.push(start);

    //메인 루프
    while (OpenQue.empty() == false)
    {
        //큐의 맨 앞을 참조
        Node current = OpenQue.top();

        //노드 이름과 f(n) 출력
        std::cout << "Node : " << current.name << ", f(" << current.name << ") : " << current.f_value << std::endl;

        //맨 앞을 삭제
        OpenQue.pop();

        //골에 도달했다면
        if (current.index == goalIndex)
        {
            //골의 f(n)과 최단 거리 비교해서 더 작다면
            //갱신하고 다음 반복으로
            //만약 current.f_value가 최단 거리보다 작지 않다면
            //이미 우선 순위 큐에는 이것보다 작은 값은 남아 있지 않으므로 체크할 필요가 없다.
            //따라서 break
            if (current.f_value < shortestDistance)
            {
                shortestDistance = current.f_value;
            
                continue;
            }
            else
            {
                break;
            }

            
        }

        for (int i = 0; i < graph.GetVtxCount(); i++)
        {   
            //접근 가능하고, Close에 i번재 노드가 포함되어 있지 않다면
            //current.index와 i가 일치하지 않아야 한다.(안 그러면 중복해서 들어감)
            if (graph.Adj[current.index][i] != INF && current.index != i && !IsContainNode(Close, i))
            {
                //f(n)값과 현재 인덱스, 이름 배열 참조하여 Node 생성
                Node temp(
                    d[current.index] + graph.Adj[current.index][i] + h[i],
                    i,
                    graph.VertexNames[i]
                );

                OpenQue.push(temp);

                //시작 점 부터 current까지의 거리 + current에서 i번째 노드까지의 거리합
                d[i] = d[current.index] + graph.Adj[current.index][i];

            }
        }

        //닫은 목록에 추가
        Close.push_back(current);

    }

    //닫은 목록에 추가되지 못한 목표지점 추가
    Node goal(0, goalIndex, graph.VertexNames[goalIndex]);
    Close.push_back(goal);

    //만약 최단거리를 찾지 못했다면 실패판정
    if (shortestDistance == INF)
    {
        std::cout << "Failed To Find Shortest Path..." << std::endl;
        std::cout << "Press Enter To Exit";
        system("pause > nul");
        exit(0);
    }

    //최단 경로 계산 알고리즘, sPath에 역순으로 최단 경로를 넣는다.
    //Close의 맨 끝의 노드(목표 노드)를 받아온다.
    Node a = Close[Close.size() - 1];
    //Close의 뒤에서 부터 순회하며 부모 여부를 확인하고 a를 갱신한다.
    for (int i = Close.size() - 2; i >= 0; i--)
    {
        Node temp = Close[i];
        //만약 a가 temp의 부모라면(접근 가능하다면)
        if (graph.Adj[a.index][temp.index] != INF)
        {
            //a를 넣고 a를 temp로 갱신
            sPath.push_back(a);
            a = temp;
        }
    }
    sPath.push_back(start);

    std::cout << std::endl;

    std::cout << "Shortest Path : ";

    //최단 경로 역순으로 출력
    for (int i = sPath.size() - 1; i >= 0; i--)
    {
        std::cout << sPath[i].name << " ";
    }

    std::cout << std::endl;

    std::cout << "Shortest Distance : ";
    std::cout << shortestDistance << std::endl;

    std::cout << "Press Enter To End Program...";
    system("pause > nul");
}

/// <summary>
/// vector에 index번째인 Node가 있는지 반환
/// </summary>
/// <param name="vector"></param>
/// <param name="index"></param>
/// <returns></returns>
bool IsContainNode(std::vector<Node>& vector, int index)
{
    for(int i = 0; i < (int)vector.size(); i++)
    { 
        if (vector[i].index == index)
        {
            return true;
        }
    }
    return false;
}

// 프로그램 실행: <Ctrl+F5> 또는 [디버그] > [디버깅하지 않고 시작] 메뉴
// 프로그램 디버그: <F5> 키 또는 [디버그] > [디버깅 시작] 메뉴

// 시작을 위한 팁: 
//   1. [솔루션 탐색기] 창을 사용하여 파일을 추가/관리합니다.
//   2. [팀 탐색기] 창을 사용하여 소스 제어에 연결합니다.
//   3. [출력] 창을 사용하여 빌드 출력 및 기타 메시지를 확인합니다.
//   4. [오류 목록] 창을 사용하여 오류를 봅니다.
//   5. [프로젝트] > [새 항목 추가]로 이동하여 새 코드 파일을 만들거나, [프로젝트] > [기존 항목 추가]로 이동하여 기존 코드 파일을 프로젝트에 추가합니다.
//   6. 나중에 이 프로젝트를 다시 열려면 [파일] > [열기] > [프로젝트]로 이동하고 .sln 파일을 선택합니다.
