#pragma once
#include <iostream>
#include <iomanip> //setw() ���� ������ ���� ���
#include <fstream>
#include <string>

constexpr int MAX_VTXS = 64;
constexpr int INF = INT_MAX;

class GraphAdj
{
public:
	//int Adj[MAX_VTXS][MAX_VTXS] = { 0 };
	//���� ���� ���� ������(2���� �迭�� ���)
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
/// �迭 �ʱ�ȭ
/// </summary>
void GraphAdj::InitGraph()
{
	VtxCount = 0;

	//�ϴ� �������� 1���� �迭 ����
	//��
	Adj = new int* [MAX_VTXS];

	for (int i = 0; i < MAX_VTXS; i++)
	{
		//�� ���� �����Ϳ� ���� �Ҵ�
		Adj[i] = new int[MAX_VTXS];
	}
}

/// <summary>
/// char ���� �޾� ��� �̸��迭�� �߰���
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

	return true;
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

	return true;
}

/// <summary>
/// �׷��� ���
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
			//�ڸ��� ���߱� ���� setw()
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
/// ���Ϸκ��� �׷��� �ҷ���
/// </summary>
/// <param name="fname">���ڿ� ���</param>
/// <returns></returns>
bool GraphAdj::LoadGraph(const char* fname)
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

	//ifstream�� int get()�� ���ڰ� �ƽ�Ű �ڵ�� �� 
	//�ƽ�Ű �ڵ� -> int�� ����
	n -= 48;

	char c;

	//�ӽ� ����
	char* buf = new char[MAX_VTXS];

	//��� ������ŭ �ݺ�
	for (int i = 0; i < n; i++)
	{
		//��� �̸� �޾ƿ�
		readGraph >> c;
		InsertVertex(c);

		for (int j = 0; j < n; j++)
		{
			//���� �� �о��
			//���� ���� ������ �о��
			readGraph >> buf;

			//���ڿ� �����͸� �����ڷ� �Ѱ� string ����
			std::string str(buf);

			//string -> int�� �ٲ�
			int temp = std::stoi(str);

			//��� �ڽ������� ������ �ƴѵ���
			//�Ÿ��� 0�̸� INF�� ǥ��
			if (i != j && temp == 0)
			{
				InsertEdgeD(i, j, INF);
			}
			else
				InsertEdgeD(i, j, temp);
		}
		//���� ����
		memset(buf, 0, MAX_VTXS * sizeof(char));
		
	}
	readGraph.close();

	return true;
}

/// <summary>
/// ���Ϸκ��� �׷��� �ҷ���
/// </summary>
/// <param name="fname">���ڿ� ������</param>
/// <returns></returns>
bool GraphAdj::LoadGraph(char* fname)
{
	//�ڷ��� ȣȯ�� ���� �����ε�
	const char* temp = fname;
	return this->LoadGraph(temp);
}

/// <summary>
/// ���Ϸκ��� �׷��� �ҷ���
/// </summary>
/// <param name="fname">std::string</param>
/// <returns></returns>
bool GraphAdj::LoadGraph(std::string fname)
{
	const char* temp = fname.c_str();
	return this->LoadGraph(temp);
}