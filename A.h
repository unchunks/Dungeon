#include <stdio.h>
#include <memory.h>
#include <list>
#include <queue>
#include <vector>
#include <math.h>

#include "DDefine.h"

const int MapWidth = 5;
const int MapHeight = 5;
const int Infinity = 100000;

enum EraseResult
{
	NotFound,		
	Erased,			
	CouldntErased	
};

// Map
struct Cell
{
	Cell() :
		X(-1),
		Y(-1)
	{
	}

	Cell(int x, int y)
	{
		X = x;
		Y = y;
	}

	int X;		
	int Y;		
};

struct Node
{
	Node() :
		Node(0, 0)
	{
	}

	Node(int x, int y) :
		Position(x, y),
		HeuristicCost(Infinity),
		TotalCost(0)
	{
		AdjacentNodes.clear();
	}

	Cell Position;						
	std::vector<Node*> AdjacentNodes;	
	float HeuristicCost;				
	float TotalCost;					
};

int CostTable[FLOOR_H][FLOOR_W];

// グラフ
Node Map[FLOOR_H][FLOOR_W];

bool Less(Node* a, Node* b)
{
	if (a->TotalCost < b->TotalCost) 
	{
		return true;
	}

	return false;
}

// 範囲セルチェック
bool IsCellWithinTheRange(int x, int y)
{
	if (x >= 0 &&
		x < MapWidth &&
		y >= 0 &&
		y < MapHeight)
	{
		return true;
	}

	return false;
}

// ノード作成
void CreateMap()
{
    for (int y = 0; y < FLOOR_H; y++)
	{
		for (int x = 0; x < FLOOR_W; x++){
            if((floorTYPE[y][x] == FLOOR) || (floorTYPE[y][x] == AISLE)) {
                CostTable[y][x] = 1;
            } else {
                CostTable[y][x] = 0;
            }
        }
    }
	for (int y = 0; y < FLOOR_H; y++)
	{
		for (int x = 0; x < FLOOR_W; x++)
		{
			Map[y][x].Position.X = x;
			Map[y][x].Position.Y = y;

			Cell adjacent_cells[] = 
			{
				Cell(x, y - 1),
				Cell(x - 1, y),
				Cell(x + 1, y),
				Cell(x, y + 1),
			};

			// 隣接ノード追加
			for (const Cell& cell : adjacent_cells)
			{
				if (IsCellWithinTheRange(cell.X, cell.Y) == true &&
					CostTable[cell.Y][cell.X] == 1)
				{
					Map[y][x].AdjacentNodes.push_back(&Map[cell.Y][cell.X]);
				}
			}
		}
	}
}

// コスト初期化
void InitCost(int heuristic_cost, int total_cost)
{
	for (int y = 0; y < MapHeight; y++)
	{
		for (int x = 0; x < MapWidth; x++)
		{
			Map[y][x].HeuristicCost = heuristic_cost;
			Map[y][x].TotalCost = total_cost;
		}
	}
}

float CalculateHeuristic(const Node* node, const Node* Goal)
{
	float x = fabsf(Goal->Position.X - node->Position.X);
	float y = fabsf(Goal->Position.Y - node->Position.Y);

	return sqrtf(x * x + y * y);
}

bool IsEqualCell(const Cell& a, const Cell& b)
{
	if (a.X == b.X &&
		a.Y == b.Y)
	{
		return true;
	}

	return false;
}

EraseResult EraseNode(std::list<Node*>& list, Node* new_node, float new_cost)
{
	// クローズリストチェック
	for (auto itr = list.begin(); itr != list.end(); itr++)
	{
		// ノードと同じセルがあるか
		if (IsEqualCell(new_node->Position, (*itr)->Position) == true)
		{
			// コスト比較
			if (new_cost < (*itr)->TotalCost)
			{
				list.erase(itr);
				return EraseResult::Erased;
			}
			else
			{
				return EraseResult::CouldntErased;
			}
		}
	}

	return EraseResult::NotFound;
}

// オープンリストに追加
bool AddAdjacentNode(std::list<Node*>& open_list, std::list<Node*>& close_list, Node* adjacent_node, float cost)
{
	bool can_update = true;

	std::list<Node*> node_list[] =
	{
		close_list,
		open_list
	};

	for (std::list<Node*>& list : node_list)
	{
		// 既存のコストが高ければ更新
		if (EraseNode(list, adjacent_node, cost) == EraseResult::CouldntErased)
		{
			can_update = false;
		}
	}
	
	if (can_update == true)
	{
		open_list.push_back(adjacent_node);
		return true;
	}

	return false;
}

void AStar(Cell start, Cell goal)
{
	std::list<Node*> open_list;
	std::list<Node*> close_list;

	//const Node* start_node = &Map[start.Y][start.X];
	const Node* goal_node = &Map[goal.Y][goal.X];

	// 更新ノード位置保存
	Cell last_update_cells[MapHeight][MapWidth];

	// グラフ初期化
	InitCost(Infinity, 0);

	// スタートノード指定
	open_list.push_back(&Map[start.Y][start.X]);

	int count = 0;

	// オープンリストがなくなるまで
	while (open_list.empty() == false)
	{
		count++;

		Node* search_node = (*open_list.begin());
		// 探索リストから除外
		open_list.erase(open_list.begin());

		// ゴールで終わり
		if (IsEqualCell(search_node->Position, goal) == true)
		{
			// クローズリストに最後のノード追加
			close_list.push_back(search_node);
			break;
		}

		for (Node* adjacent_node : search_node->AdjacentNodes)
		{
			// 未計算の場合
			if (adjacent_node->HeuristicCost == Infinity)
			{
				adjacent_node->HeuristicCost = CalculateHeuristic(adjacent_node, goal_node);
			}

			// ノード間コスト
			float edge_cost = CostTable[adjacent_node->Position.Y][adjacent_node->Position.X];
			// 総コスト
			float node_cost = search_node->TotalCost;
			float total_cost = edge_cost + adjacent_node->HeuristicCost + node_cost;

			// ノード追加
			if (AddAdjacentNode(open_list, close_list, adjacent_node, total_cost) == true)
			{
				// 総コスト更新
				adjacent_node->TotalCost = total_cost;

				if (adjacent_node->Position.Y == 0 && adjacent_node->Position.X == 2)
				{
					int xx = 0;
					xx = 100;
				}

				// 更新セル保存
				last_update_cells[adjacent_node->Position.Y][adjacent_node->Position.X] = search_node->Position;
			}
		}

		bool is_add_close = true;

		// クローズリストチェック
		for (auto itr = close_list.begin(); itr != close_list.end(); itr++)
		{
			if (IsEqualCell(search_node->Position, (*itr)->Position) == true)
			{
				is_add_close = false;
				break;
			}
		}

		// ノード追加
		if (is_add_close == true)
		{
			// このノードの探索終了
			close_list.push_back(search_node);
		}

		// 昇順ソート
		open_list.sort(Less);
	}

	// 経路復元
	std::list<Cell> route_list;

	// ゴールから復元
	route_list.push_back(goal);
	while (route_list.empty() == false)
	{
		Cell route = route_list.front();

		// スタート位置なら終了
		if (IsEqualCell(route, start) == true)
		{
			// 復元経路表示
			for (Cell& cell : route_list)
			{
				printf("x = %d y = %d\n", cell.X, cell.Y);
			}
			break;
		}
		else
		{
			if (IsCellWithinTheRange(route.X, route.Y) == true)
			{
				// 追加
				route_list.push_front(last_update_cells[route.Y][route.X]);
			}
			else
			{
				printf("Not Found\n");
				break;
			}
		}
	}

	printf("探索回数 = %d\n", count);
}

// int main()
// {
// 	CreateMap();

// 	Cell start = Cell(3, 1);
// 	Cell goal = Cell(0, 0);

// 	AStar(start, goal);

// 	return 0;
// }