#pragma once
#include <iostream>
#include <iomanip> //setw() 등의 조정자 위해 사용
#include <fstream>
#include <string>

constexpr int MAX_VTXS = 64;
constexpr int INF = INT_MAX;

class GraphAdj
{
public:
	//int Adj[MAX_VTXS][MAX_VTXS] = { 0 };
	//맵을 위한 이중 포인터(2차원 배열로 사용)
	int** Adj;
	char VertexNames[MAX_VTXS];
private:
	int VtxCount = 0;
public:
	GraphAdj() { InitGraph(); }
	bool IsGraphEmpty() { return VtxCount == 0; }
	bool IsGraphFull() { return VtxCount >= MAX_VTXS; }
	char GetVtxCount() { return VtxCount; }
	void InitGraph();
	bool InsertVertex(char n);
	bool InsertEdgeD(int u, int v, int val);
	bool InsertEdgeUD(int u, int v, int val);
	bool PrintGraph();
	bool LoadGraph(char* fname);
	bool LoadGraph(const char* fname);
	bool LoadGraph(std::string fname);
};

/// <summary>
/// 배열 초기화
/// </summary>
void GraphAdj::InitGraph()
{
	VtxCount = 0;

	//일단 포인터의 1차원 배열 만듬
	//행
	Adj = new int* [MAX_VTXS];

	for (int i = 0; i < MAX_VTXS; i++)
	{
		//각 행의 포인터에 열을 할당
		Adj[i] = new int[MAX_VTXS];
	}
}

/// <summary>
/// char 값을 받아 노드 이름배열에 추가함
/// </summary>
/// <param name="n"></param>
bool GraphAdj::InsertVertex(char n)
{
	if (IsGraphFull())
		return false;

	VertexNames[VtxCount++] = n;

	return true;
}

/// <summary>
/// 단방향 간선을 추가함
/// </summary>
/// <param name="u">노드1</param>
/// <param name="v">노드2</param>
/// <param name="val">가중치</param>
/// <returns>성공 여부</returns>
bool GraphAdj::InsertEdgeD(int u, int v, int val)
{
	if (u > MAX_VTXS || u < 0 ||
		v > MAX_VTXS || v < 0 ||
		val < 0)
		return false;

	Adj[u][v] = val;

	return true;
}

/// <summary>
/// 양방향 간선을 추가함
/// </summary>
/// <param name="u">노드1</param>
/// <param name="v">노드2</param>
/// <param name="val">가중치</param>
/// <returns>성공 여부</returns>
bool GraphAdj::InsertEdgeUD(int u, int v, int val)
{
	if (u > MAX_VTXS || u < 0 ||
		v > MAX_VTXS || v < 0 ||
		val < 0)
		return false;

	Adj[u][v] = Adj[v][u] = val;

	return true;
}

/// <summary>
/// 그래프 출력
/// </summary>
/// <returns></returns>
bool GraphAdj::PrintGraph()
{
	if (IsGraphEmpty())
		return false;

	std::cout << VtxCount << std::endl;
	for (int i = 0; i < VtxCount; i++)
	{
		std::cout << VertexNames[i] << " ";
		for (int j = 0; j < VtxCount; j++)
		{
			//자리를 맞추기 위한 setw()
			if (Adj[i][j] == INF)
				std::cout << std::setw(3) << "-" << " ";
			else
				std::cout << std::setw(3) << Adj[i][j] << " ";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;

	return true;
}

/// <summary>
/// 파일로부터 그래프 불러옴
/// </summary>
/// <param name="fname">문자열 상수</param>
/// <returns></returns>
bool GraphAdj::LoadGraph(const char* fname)
{
	std::ifstream readGraph;
	readGraph.open(fname);

	//예외 처리
	if (!readGraph.is_open())
		return false;

	//그래프 초기화
	InitGraph();


	//먼저 그래프의 노드 수를 받아옴
	int n = readGraph.get();

	//ifstream의 int get()은 숫자가 아스키 코드로 됨 
	//아스키 코드 -> int로 변경
	n -= 48;

	char c;

	//임시 버퍼
	char* buf = new char[MAX_VTXS];

	//노드 개수만큼 반복
	for (int i = 0; i < n; i++)
	{
		//노드 이름 받아옴
		readGraph >> c;
		InsertVertex(c);

		for (int j = 0; j < n; j++)
		{
			//간선 값 읽어옴
			//공백 만날 때까지 읽어옴
			readGraph >> buf;

			//문자열 포인터를 생성자로 넘겨 string 만듬
			std::string str(buf);

			//string -> int로 바꿈
			int temp = std::stoi(str);

			//노드 자신으로의 간선이 아닌데도
			//거리가 0이면 INF로 표기
			if (i != j && temp == 0)
			{
				InsertEdgeD(i, j, INF);
			}
			else
				InsertEdgeD(i, j, temp);
		}
		//버퍼 비우기
		memset(buf, 0, MAX_VTXS * sizeof(char));
		
	}
	readGraph.close();

	return true;
}

/// <summary>
/// 파일로부터 그래프 불러옴
/// </summary>
/// <param name="fname">문자열 포인터</param>
/// <returns></returns>
bool GraphAdj::LoadGraph(char* fname)
{
	//자료형 호환을 위한 오버로딩
	const char* temp = fname;
	return this->LoadGraph(temp);
}

/// <summary>
/// 파일로부터 그래프 불러옴
/// </summary>
/// <param name="fname">std::string</param>
/// <returns></returns>
bool GraphAdj::LoadGraph(std::string fname)
{
	const char* temp = fname.c_str();
	return this->LoadGraph(temp);
}