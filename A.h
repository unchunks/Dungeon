#pragma once

#include <stdio.h>
#include <glm/glm.hpp>
#include <deque>

#include "Enum.h"
#include "Const.h"

enum {
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
	{  0,  1 },		// 0
	{ -1,  0 },		// 1
	{  0, -1 },		// 2
	{  1,  0 },		// 3
};

typedef struct 
{
	int no;
	int chip;
	int status;
	int event_no;

	int cost;
	int SearchStatus;	// 0:未調査 1:オープン 2:クローズ
	int parent;		// 親の向き
} MAPCELL;

MAPCELL data[FLOOR_H][FLOOR_W];
glm::vec2 START, GOAL;
std::deque<glm::vec2> route;


void A(CELL_TYPE def_data[FLOOR_H][FLOOR_W], glm::vec2 _start, glm::vec2 _goal)
{
	for(int h = 0; h < FLOOR_H; h++){
		for(int w = 0; w < FLOOR_W; w++){
			data[h][w].cost = 0;
			data[h][w].SearchStatus = 0;
		}
	}
    for(int h = 0; h < FLOOR_H; h++){
		for(int w = 0; w < FLOOR_W; w++){
            if((def_data[h][w] == FLOOR) || (def_data[h][w] == AISLE))
                data[h][w].status = 0;
            else 
                data[h][w].status = -1;
		}
	}
    data[(int)START.y][(int)START.x].SearchStatus = SEARCH_OPEN;
    Search(0);
}

// マンハッタン距離を求める
int GetDistance(int from_x, int from_y, int to_x, int to_y)
{
	return abs(from_x - to_x) + abs(from_y - to_y);
}

int BackTrace(int x, int y)
{
	if(x == START.x && y == START.y) return 1;

	int parent_way = data[y][x].parent;

	return BackTrace(
		x + CheckMatrix[parent_way].x,
		y + CheckMatrix[parent_way].y
	) + 1;
}

// A*で経路探査する
int Search(int count){

	int cost_min = 9999;
	int BackCost = 0;
	int CX = 0;
	int CY = 0;

	MAPCELL *n = NULL;
	
	// コストが最小のオープンノードを探す
	// TODO: ここを全マス探査しないようにすると、
	//       もっと早くなるかも
	for(int h = 0; h < FLOOR_H; h++){
		for(int w = 0; w < FLOOR_W; w++){

			if(data[h][w].SearchStatus != SEARCH_OPEN)continue;
			if(GetDistance(w,h, GOAL.x, GOAL.y) > cost_min)continue;
			
			cost_min = GetDistance(w, h, GOAL.x, GOAL.y);
			n = &data[h][w];

			CX = w;
			CY = h;
		}
	}

	// オープンノードがなければ終了(ゴールが見つからない)
	if(n == NULL) return -9;

	// ノードをクローズする
	n->SearchStatus = SEARCH_CLOSE;

	BackCost = BackTrace(CX, CY);

	for(int i = 0; i < 8; i++){
		int check_x = CX + CheckMatrix[i].x;
		int check_y = CY + CheckMatrix[i].y;

		if(check_x < 0) continue;
		if(check_y < 0) continue;

		if(check_x >= FLOOR_W ) continue;
		if(check_y >= FLOOR_H) continue;

		// 通れないところをよける
		if(data[check_y][check_x].status == -1) continue;
		
		int estimate_cost = BackCost + GetDistance(check_x, check_y, GOAL.x, GOAL.y) + 1;
		
		MAPCELL *cell = &data[check_y][check_x];

		if(data[check_y][check_x].SearchStatus == SEARCH_NO_CHECK){

			cell->parent = (i + 4) % 8;
			cell->SearchStatus = SEARCH_OPEN;

		}else if(estimate_cost < cell->cost){

			cell->parent       = (i + 4) % 8;
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

void TraceRoute(int x, int y)
{
	if(x == START.x && y == START.y){
		printf("開始ノード>");
		return;
	}

	POINT *parent_way = &CheckMatrix[data[y][x].parent];

	data[y][x].status = 1;

	TraceRoute(x + parent_way->x, y + parent_way->y);
	
	if(x == GOAL.x && y == GOAL.y){
		printf("ゴール\n");
		return;
	}else{
		printf("(%d,%d)>", x, y);
	}

	return;
}

void out(void)
{
	for(int h = 0; h < FLOOR_H; h++){
		for(int w = 0; w < FLOOR_W; w++){
			char ch = ' ';
			if(w == GOAL.x && h == GOAL.y) ch = '*';
			if(w == START.x && h == START.y) ch = '@';

			printf("%c", ch);

			if(data[h][w].status > 0)  ch = 'o';
			if(data[h][w].status < 0)  ch = '#';
			if(data[h][w].status == 0) ch = '.';

			printf("%c", ch);
		}
		printf("\n");
	}
	printf("OK.\n");
	return;	
}