#pragma once
#include <iostream>
#include <iomanip> //setw() ���� ������ ���� ���
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
/// �迭 �ʱ�ȭ
/// </summary>
void GraphAdj::InitGraph()
{
	VtxCount = 0;
	memset(Adj, 0, sizeof(Adj));
}

/// <summary>
/// char ���� �޾� ��� �̸��迭�� �߰���
/// </summary>
/// <param name="n"></param>
bool GraphAdj::InserVertex(char n)
{
	if (IsGraphFull())
		return false;

	VertexNames[VtxCount++] = n;
}

/// <summary>
/// �ܹ��� ������ �߰���
/// </summary>
/// <param name="u">���1</param>
/// <param name="v">���2</param>
/// <param name="val">����ġ</param>
/// <returns>���� ����</returns>
bool GraphAdj::InsertEdgeD(int u, int v, int val)
{
	if (u > MAX_VTXS || u < 0 ||
		v > MAX_VTXS || v < 0 ||
		val < 0)
		return false;

	Adj[u][v] = val;
}

/// <summary>
/// ����� ������ �߰���
/// </summary>
/// <param name="u">���1</param>
/// <param name="v">���2</param>
/// <param name="val">����ġ</param>
/// <returns>���� ����</returns>
bool GraphAdj::InsertEdgeUD(int u, int v, int val)
{
	if (u > MAX_VTXS || u < 0 ||
		v > MAX_VTXS || v < 0 ||
		val < 0)
		return false;

	Adj[u][v] = Adj[v][u] = val;
}

/// <summary>
/// �׷��� ���
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
			//�ڸ��� ���߱� ���� setw()
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
/// ���Ϸκ��� �׷��� �ҷ���
/// </summary>
/// <param name="fname"></param>
/// <returns></returns>
bool GraphAdj::LoadGraph(char* fname)
{
	std::ifstream readGraph;
	readGraph.open(fname);

	//���� ó��
	if (!readGraph.is_open())
		return false;

	//�׷��� �ʱ�ȭ
	InitGraph();


	//���� �׷����� ��� ���� �޾ƿ�
	int n = readGraph.get();
	char c;
	for (int i = 0; i < n; i++)
	{
		std::string str;

		//�� �� �о str�� ����
		std::getline(readGraph, str);

		
	}
}