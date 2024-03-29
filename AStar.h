#pragma once

#include <glm/glm.hpp>
#include <deque>

#include "Enum.h"
#include "Const.h"

enum SEARCH_STATUS{
	SEARCH_NO_CHECK	= 0,
	SEARCH_OPEN		= 1,
	SEARCH_CLOSE	= 2,
};

typedef struct {
	int x;
	int y;
} POINT;

// 4方向のベクトル設定
POINT CheckMatrix[] = {
	{ -1,  0 },		// 左
	{  1,  0 },		// 右
	{  0, -1 },		// 上
	{  0,  1 },		// 下
};

class MAPCELL {
public:
	MAPCELL()
	:status(2), cost(0), SearchStatus(SEARCH_NO_CHECK), parent(NO_DIRECTION)
	{}
	int status;					// 2:壁 0:床 1:ルート
	int cost;
	SEARCH_STATUS SearchStatus;	// 0:未調査 1:オープン 2:クローズ
	DIRECTION parent;			// 親の向き
};

MAPCELL data[FLOOR_H][FLOOR_W];
glm::vec2 START, GOAL;
std::deque<glm::vec2> route;

// マンハッタン距離を求める
int GetDistance(int from_x, int from_y)
{
	int dis = abs(from_x - GOAL.x) + abs(from_y - GOAL.y);
	return dis;
}

// スタート位置から現在地までのコスト集計
int BackTrace(int x, int y)
{
	if(x == START.x && y == START.y) return 0;

	int parent_way = data[y][x].parent;
	return BackTrace(
		x + CheckMatrix[parent_way].x,
		y + CheckMatrix[parent_way].y
	) + 1;
}

// A*で経路探査する
int Search(int count){
	// 検索中のノード、X・Y座標、実コスト
	MAPCELL *n = NULL;
	int CX = 0;
	int CY = 0;
	int BackCost = 0;

	// コストが最小のオープンノードを探す
	int cost_min = 9999;
	for(int y = 0; y < FLOOR_H; y++){
		for(int x = 0; x < FLOOR_W; x++){
			if(data[y][x].SearchStatus != SEARCH_OPEN)continue;	// オープンでなければスキップ
			int cost = GetDistance(x,y);
			if(cost > cost_min)continue;	// 今よりゴールに遠ければスキップ
			
			cost_min = cost;
			n = &data[y][x];
			CX = x;
			CY = y;

		}
	}

	// オープンノードがなければ終了(ゴールが見つからない)
	if(n == NULL) return -9;

	// ノードをクローズする
	n->SearchStatus = SEARCH_CLOSE;

	BackCost = BackTrace(CX, CY);

	// 4方向の移動先のコスト計算
	for(int i = 0; i < 4; i++){
		// 計算中の座標
		int check_x = CX + CheckMatrix[i].x;
		int check_y = CY + CheckMatrix[i].y;

		// マップ外でスキップ
		if(check_x < 0) continue;
		if(check_y < 0) continue;
		if(check_x >= FLOOR_W ) continue;
		if(check_y >= FLOOR_H) continue;

		// 通れないところをよける
		if(data[check_y][check_x].status == 2) continue;

		int estimate_cost = BackCost + GetDistance(check_x, check_y) + 1;
		MAPCELL *cell = &data[check_y][check_x];

		if(data[check_y][check_x].SearchStatus == SEARCH_NO_CHECK){	// 計算中の座標が未チェック
			cell->parent 	   = (DIRECTION)(int)(-1.33 * i*i*i + 6 * i*i + -5.67 * i + 1);
			cell->SearchStatus = SEARCH_OPEN;

		}else if(estimate_cost < cell->cost){	// 計算中の座標のコストが更新可能
			cell->parent       = (DIRECTION)(int)(-1.33 * i*i*i + 6 * i*i + -5.67 * i + 1);
			cell->cost         = estimate_cost;
			cell->SearchStatus = SEARCH_OPEN;
		}
	}

	// 見つかったら探索終了
	if(CX == GOAL.x && CY == GOAL.y){
		return -1;
	}

	return Search(count + 1);
}

// ゴールから逆算
void TraceRoute(int x, int y)
{
	POINT *parent_way = &CheckMatrix[data[y][x].parent];
	route.push_front(glm::vec2(x, y));
	data[y][x].status = 1;
	if((x == START.x) && (y == START.y))
		return;
	TraceRoute(x + parent_way->x, y + parent_way->y);
}

std::deque<glm::vec2> AStar(CELL_TYPE def_data[FLOOR_H][FLOOR_W], glm::vec2 _start, glm::vec2 _goal)
{
	route.clear();
	START = _start;
	GOAL = _goal;
	for(int y = 0; y < FLOOR_H; y++)
		for(int x = 0; x < FLOOR_W; x++)
			data[y][x] = MAPCELL();
	// マップ変換
    for(int y = 0; y < FLOOR_H; y++){
		for(int x = 0; x < FLOOR_W; x++){
            if((def_data[y][x] == FLOOR) || (def_data[y][x] == AISLE))
                data[y][x].status = 0;	// 床
            else 
                data[y][x].status = 2;	// 壁
		}
	}

	// 開始位置をオープンに
    data[(int)START.y][(int)START.x].SearchStatus = SEARCH_OPEN;
    Search(0);
	TraceRoute(GOAL.x, GOAL.y);
	return route;
}