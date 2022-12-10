#include "DFS.h"
#include "STLheader.h"

using namespace std;

void DFS()
{
	// 인접 List 방식을 사용한 구현.

	//1. Graph 제작
	struct Node
	{
		int value;
		std::vector<Node*> link;
		bool check;
	};

	std::vector<Node*> Graph;
	std::stack<Node*> Visit;

	for (int i = 0; i < 8; ++i)
	{
		Node* pNode = new Node;
		pNode->value = i;
		pNode->check = false;
		Graph.push_back(pNode);
	}

	//0번 노드
	Graph[0]->link.push_back(Graph[1]);

	//1번 노드
	Graph[1]->link.push_back(Graph[0]);
	Graph[1]->link.push_back(Graph[2]);

	//2번 노드
	Graph[2]->link.push_back(Graph[1]);
	Graph[2]->link.push_back(Graph[3]);
	Graph[2]->link.push_back(Graph[4]);

	//3번 노드
	Graph[3]->link.push_back(Graph[2]);

	//4번 노드
	Graph[4]->link.push_back(Graph[2]);
	Graph[4]->link.push_back(Graph[5]);
	Graph[4]->link.push_back(Graph[6]);
	Graph[4]->link.push_back(Graph[7]);

	//5번 노드
	Graph[5]->link.push_back(Graph[4]);

	//6번 노드
	Graph[6]->link.push_back(Graph[4]);

	//7번 노드
	Graph[7]->link.push_back(Graph[4]);


	//2. DFS
	int i = 4;
	while (true)
	{
		// 한번도 방문하지 않은 노드일 경우
		if (!Graph[i]->check)
		{
			// 방문 처리
			Graph[i]->check = true;
			Visit.push(Graph[i]);
			std::cout << i << "->";
		}


		// 방문 했던 노드라면
		else
		{
			// 방문하지 않은 연결된 노드가 있는지 체크.
			for (size_t j = 0; j < Graph[i]->link.size(); ++j)
			{
				// 연결된 노드가 방문된 적 없는 노드라면
				if (!Graph[i]->link[j]->check)
				{
					// 다음 방문할 노드 번호로 정해준다.
					i = Graph[i]->link[j]->value;
					break;
				}
			}

			// 방문하지 않은 연결 노드가 없다면
			// 스택에서 꺼낸 후 다음 최상단 노드를 다음 탐색할 노드로 설정해준다.
			if (Graph[i] == Visit.top())
			{
				Visit.pop();

				if (0 != Visit.size())
				{
					i = Visit.top()->value;

				}

				else
				{
					std::cout <<'\n';
					break;
				}
			}

		}

	}



	std::vector<Node*>::iterator iter = Graph.begin();
	std::vector<Node*>::iterator iterEnd = Graph.end();

	// 메모리 해제
	for (; iter != iterEnd; ++iter)
	{
		delete (*iter);
	}

	// 벡터에 할당된 메모리 삭제
	
	Graph.clear();
}

bool CheckIceBox(int _x, int _y, int _n, int _m, int _Graph[][1000])
{
	if (_x <= -1 || _x >= _n || _y <= -1 || _y >= _m)
	{
		return false;
	}
	// 현재 노드를 아직 방문하지 않았다면
	if (_Graph[_x][_y] == 0)
	{
		// 해당 노드 방문 처리
		_Graph[_x][_y] = 1;

		// 상, 하, 좌, 우의 위치들도 모두 재귀적으로 호출
		CheckIceBox(_x - 1, _y,_n,_m, _Graph);
		CheckIceBox(_x, _y - 1,_n,_m,_Graph);
		CheckIceBox(_x + 1, _y, _n, _m, _Graph);
		CheckIceBox(_x, _y + 1, _n, _m, _Graph);
		return true;
	}
	return false;
}

void FreezingDrinks()
{
	int N, M;
	int Graph[1000][1000];
	std::cin >> N >> M;

	// 2차원 리스트의 맵 정보 입력 받기
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++)
		{
			scanf_s("%1d", &Graph[i][j]);
		}
	}

	// 모든 노드(위치)에 대하여 음료수 채우기
	int result = 0;

	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++) 
		{
			// 현재 위치에서 DFS 수행
			if (CheckIceBox(i, j, N,M, Graph)) {
				result += 1;
			}
		}
	}
	std::cout << result << '\n'; // 정답 출력 
}

void CheckNetwork(bool* visited, int currentDepth, std::vector<std::vector<int>>& computers)
{
	visited[currentDepth] = true;

	for (int i = currentDepth, j = 0; j < computers.size(); ++j)
	{
		if (i == j)
		{
			continue;
		}

		if (!visited[j] && computers[i][j])
		{
			CheckNetwork(visited,j,computers);
		}
	}
}

int Network(int n, std::vector<std::vector<int>> computers)
{
	bool visited[200] = { false };
	int answer = 0;

	for (int i = 0; i < n; ++i)
	{
		// 방문한 적이 없는 노드라면 (연결이 끊겼을 경우)
		if (!visited[i])
		{
			++answer;

			// 연결된 네트워크를 순회
			CheckNetwork(visited, i, computers);
		}
	}
		return answer;
}

void CalculateNumber(std::vector<int> numbers, int target, int index, int totalSum, int& answer)
{
	if (index == numbers.size() - 1)
	{
		if (totalSum == target)
		{
			++answer;
		}

		return;
	}

	CalculateNumber(numbers, target, index + 1, numbers[index + 1] + totalSum, answer);
	CalculateNumber(numbers, target, index + 1, -numbers[index + 1] + totalSum, answer);
}

int TargetNumber(std::vector<int> numbers, int target)
{
	int i = 0;
	int answer = 0;

	CalculateNumber(numbers, target, i, numbers[0], answer);
	CalculateNumber(numbers, target, i, -numbers[0], answer);

	return answer;
}

void MakeArea(std::vector<vector<char>> grid, bool** visit, int indexX, int indexY, char color)
{
	// 이미 방문했거나 탐색할 수 없으면 종료
	if (visit[indexY][indexX] ||
		indexX > 0 || indexY > 0 || indexX >= grid.size() || indexY >= grid.size())
	{
		return;
	}

	visit[indexY][indexX] = true;

	int dirX[] = { 1,0,-1,0 };
	int dirY[] = { 0,1, 0,-1 };

	for (int i = 0; i < 4; ++i)
	{
		int nextX = indexX + dirX[i];
		int nextY = indexX + dirY[i];

		MakeArea(grid, visit, nextX, nextY, color);
	}
}

void RedGreenColorWeakness()
{
	int result = 0;
	int blueCount = 0;

	int N;
	vector<vector<char>> grid;
	bool visit[100][100] = { false };

	// Input
	cin >> N;
	grid.resize(N);

	for (int i = 0; i < N; ++i)
	{
		string line;
		cin >> line;

		for (int j = 0; j < line.length(); ++j)
		{
			char color = line[j];
			grid[i].push_back(color);
		}
	}

	/*for (int y = 0; y < N; ++y)
	{
		for (int x = 0; x < N; ++x)
		{
			cin >> grid[y][x];
		}
	}*/

	for (int y = 0; y < N; ++y)
	{
		for (int x = 0; x < N; ++x)
		{
			if (visit[y][x])
			{
				continue;
			}

			MakeArea(grid, visit, x, y, grid[y][x]);

			if (grid[y][x] == 'B')
			{
				++blueCount;
			}

		}
	}




	cout << result << ' ' << result - blueCount;
}


