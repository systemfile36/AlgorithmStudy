#pragma once
#include <iostream>
#include <iomanip> //setw() 등의 조정자 위해 사용
#include <fstream>
#include <string>

constexpr auto MAX_VTXS = 64;
constexpr auto INF = INT_MAX;

class GraphAdj
{
public:
	int Adj[MAX_VTXS][MAX_VTXS] = { 0 };
	char VertexNames[MAX_VTXS];
private:
	int VtxCount = 0;
public:
	GraphAdj() { InitGraph(); }
	bool IsGraphEmpty() { return VtxCount == 0; }
	bool IsGraphFull() { return VtxCount >= MAX_VTXS; }
	void InitGraph();
	bool InserVertex(char n);
	bool InsertEdgeD(int u, int v, int val);
	bool InsertEdgeUD(int u, int v, int val);
	bool PrintGraph();
	bool LoadGraph(char* fname);
};

/// <summary>
/// 배열 초기화
/// </summary>
void GraphAdj::InitGraph()
{
	VtxCount = 0;
	memset(Adj, 0, sizeof(Adj));
}

/// <summary>
/// char 값을 받아 노드 이름배열에 추가함
/// </summary>
/// <param name="n"></param>
bool GraphAdj::InserVertex(char n)
{
	if (IsGraphFull())
		return false;

	VertexNames[VtxCount++] = n;
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
}

/// <summary>
/// 그래프 출력
/// </summary>
/// <returns></returns>
bool GraphAdj::PrintGraph()
{
	if (IsGraphEmpty)
		return false;

	std::cout << VtxCount << std::endl;
	for (int i = 0; i < VtxCount; i++)
	{
		std::cout << VertexNames[i];
		for (int j = 0; j < VtxCount; j++)
		{
			//자리를 맞추기 위한 setw()
			if (Adj[i][j] == INF)
				std::cout << "  -";
			else
				std::cout << " " << std::setw(3) << Adj[i][j];
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

/// <summary>
/// 파일로부터 그래프 불러옴
/// </summary>
/// <param name="fname"></param>
/// <returns></returns>
bool GraphAdj::LoadGraph(char* fname)
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
	char c;
	for (int i = 0; i < n; i++)
	{
		std::string str;

		//한 줄 읽어서 str에 저장
		std::getline(readGraph, str);

		
	}
}