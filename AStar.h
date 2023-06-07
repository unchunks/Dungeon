// #pragma once

// #include <map>
// #include <deque>

// #include "DDefine.h"

// #define KEY(X,Y) ((X) * 100 + (Y))
// #define KEYDATA(X, Y, N) std::pair<int, anode>(KEY(X,Y), N)

// typedef struct {
// 	int x;
// 	int y;
// 	int px;
// 	int py;
// 	int cost;
// } anode;

// typedef struct {
// 	int x, y;
// } vec2;

// std::map <int, anode> mapOpen;
// std::map <int, anode> mapClose;

// std::deque<vec2> route;

// int GX, GY, SX, SY;

// // マンハッタン距離を斜め移動ありを考慮して求める
// int GetDistance(int from_x, int from_y, int to_x, int to_y)
// {
// 	int cx = from_x - to_x;
// 	int cy = from_y - to_y;

// 	if(cx < 0) cx *= -1;
// 	if(cy < 0) cy *= -1;

// 	// 推定移動コストを計算
// 	if(cx < cy){
// 		return (cx + (cy - cx));
// 	}else{
// 		return (cy + (cx - cy));
// 	}
// }

// // ノード情報を一度にセットする
// anode *SetNode(anode *n, int _x, int _y, int _px, int _py, int _cost)
// {
// 	n->x    = _x;
// 	n->y    = _y;
// 	n->px   = _px;
// 	n->py   = _py;
// 	n->cost = _cost;

// 	return n;
// }

// // 指定した地点からスタート地点までの距離を求める
// int BackTrace(int x, int y)
// {
// 	if(x == SX && y == SY){
// 		return 1;
// 	}

// 	std::map<int, anode>::iterator tmp = mapClose.find(KEY(x,y)) ;
	
// 	if(tmp == mapClose.end()) return 0;
	
// 	return BackTrace(tmp->second.px, tmp->second.py) + 1;
// }

// // A*で経路探査する
// int Search(int count){
	
// 	// openリストが空なら終了
// 	if(mapOpen.empty()) return -9;

// 	anode nodes[4];

// 	int way[4][2] = {
// 		{  0, -1},
// 		{  1,  0},
// 		{  0,  1},
// 		{ -1,  0}
// 	};

// 	std::map<int, anode>::iterator it;
// 	std::map<int, anode>::iterator it_min;
	
// 	anode n;

// 	int cost_min = 9999;
// 	int BackCost = 0;
	
// 	//Openリストから最小のコストを持つノードを取り出す
// 	it = mapOpen.begin();
// 	while(it != mapOpen.end()){
// 		if(cost_min > GetDistance(it->second.x,it->second.y,GX,GY) ){
// 			cost_min = GetDistance(it->second.x,it->second.y,GX,GY);
// 			it_min = it;
// 		}
// 		it++;
// 	}

// 	SetNode(
// 		&n,
// 		it_min->second.x,   it_min->second.y,
// 		it_min->second.px,  it_min->second.py,
// 		it_min->second.cost
// 	);
	
// 	// OpenリストからCloseリストへ移動
// 	mapClose.insert(KEYDATA( n.x, n.y, n));
// 	mapOpen.erase(KEY(n.x, n.y));

// 	// 最小コストのノードからスタートまでの移動コスト
// 	BackCost = BackTrace(n.x, n.y);

// 	for(int i = 0; i < 4; i++){
// 		// 隣接するマスの座標を計算
// 		int cx = n.x + way[i][0];
// 		int cy = n.y + way[i][1];

// 		if(cx < 0) continue;
// 		if(cy < 0) continue;

// 		if(cx >= FLOOR_W) continue;
// 		if(cy >= FLOOR_H) continue;

// 		// 通れない所をよける
// 		if((floorTYPE[cy][cx] != FLOOR) && (floorTYPE[cy][cx] != AISLE)) continue;

// 		SetNode(
// 			&nodes[i],
// 			cx,  cy,
// 			n.x, n.y,
// 			BackCost + GetDistance(cx, cy, GX, GY) + 1	// 推定移動コスト
// 		);

// 		//Openリストにこの座標と同じノードがあるか確認
// 		if(mapOpen.find(KEY(cx,cy)) != mapOpen.end()){
// 			if(nodes[i].cost < mapOpen[KEY(cx,cy)].cost){
// 				mapOpen[KEY(cx,cy)].px = n.x;
// 				mapOpen[KEY(cx,cy)].py = n.y;

// 				mapOpen[KEY(cx,cy)].cost = nodes[i].cost;
// 			}
// 			continue;
// 		}

// 		//Closeリストにこの座標と同じノードがあるか確認
// 		if(mapClose.find(KEY(cx, cy)) != mapClose.end()){
// 			if(nodes[i].cost < mapClose[KEY(cx,cy)].cost){
// 				anode tmp;

// 				SetNode(
// 					&tmp,
// 					cx, cy,
// 					n.x, n.y,
// 					nodes[i].cost
// 				);

// 				mapOpen.insert(KEYDATA(cx, cy, tmp));
// 				mapClose.erase(KEY(cx, cy));
// 			}
// 			continue;
// 		}

// 		// 見つからなければ新規としてOpenリストへ追加
// 		mapOpen.insert(KEYDATA(nodes[i].x, nodes[i].y, nodes[i]));
// 	}

// 	//見つかったら探索終了
// 	if(n.x == GX && n.y == GY) {
// 		route.push_front({n.x, n.y});
// 		return -1;
// 	}
// 	if(Search(count + 1) == -1) {
// 		route.push_front({n.x, n.y});
// 		return -1;
// 	}
// 	return 0;
// }

// // A*で経路探査する
// std::deque<vec2> FirstSearch(int count, int sx, int sy, int gx, int gy){

// 	SX = sx;
// 	SY = sy;
// 	GX = gx;
// 	GY = gy;
	
// 	// openリストが空なら終了
// 	if(mapOpen.empty()) return -9;

// 	anode nodes[4];

// 	int way[4][2] = {
// 		{  0, -1},
// 		{  1,  0},
// 		{  0,  1},
// 		{ -1,  0}
// 	};

// 	std::map<int, anode>::iterator it;
// 	std::map<int, anode>::iterator it_min;
	
// 	anode n;

// 	int cost_min = 9999;
// 	int BackCost = 0;
	
// 	//Openリストから最小のコストを持つノードを取り出す
// 	it = mapOpen.begin();
// 	while(it != mapOpen.end()){
// 		if(cost_min > GetDistance(it->second.x,it->second.y,GX,GY) ){
// 			cost_min = GetDistance(it->second.x,it->second.y,GX,GY);
// 			it_min = it;
// 		}
// 		it++;
// 	}

// 	SetNode(
// 		&n,
// 		it_min->second.x,   it_min->second.y,
// 		it_min->second.px,  it_min->second.py,
// 		it_min->second.cost
// 	);
	
// 	// OpenリストからCloseリストへ移動
// 	mapClose.insert(KEYDATA( n.x, n.y, n));
// 	mapOpen.erase(KEY(n.x, n.y));

// 	// 最小コストのノードからスタートまでの移動コスト
// 	BackCost = BackTrace(n.x, n.y);

// 	for(int i = 0; i < 4; i++){
// 		// 隣接するマスの座標を計算
// 		int cx = n.x + way[i][0];
// 		int cy = n.y + way[i][1];

// 		if(cx < 0) continue;
// 		if(cy < 0) continue;

// 		if(cx >= FLOOR_W) continue;
// 		if(cy >= FLOOR_H) continue;

// 		// 通れない所をよける
// 		if((floorTYPE[cy][cx] != FLOOR) && (floorTYPE[cy][cx] != AISLE)) continue;

// 		SetNode(
// 			&nodes[i],
// 			cx,  cy,
// 			n.x, n.y,
// 			BackCost + GetDistance(cx, cy, GX, GY) + 1	// 推定移動コスト
// 		);

// 		//Openリストにこの座標と同じノードがあるか確認
// 		if(mapOpen.find(KEY(cx,cy)) != mapOpen.end()){
// 			if(nodes[i].cost < mapOpen[KEY(cx,cy)].cost){
// 				mapOpen[KEY(cx,cy)].px = n.x;
// 				mapOpen[KEY(cx,cy)].py = n.y;

// 				mapOpen[KEY(cx,cy)].cost = nodes[i].cost;
// 			}
// 			continue;
// 		}

// 		//Closeリストにこの座標と同じノードがあるか確認
// 		if(mapClose.find(KEY(cx, cy)) != mapClose.end()){
// 			if(nodes[i].cost < mapClose[KEY(cx,cy)].cost){
// 				anode tmp;

// 				SetNode(
// 					&tmp,
// 					cx, cy,
// 					n.x, n.y,
// 					nodes[i].cost
// 				);

// 				mapOpen.insert(KEYDATA(cx, cy, tmp));
// 				mapClose.erase(KEY(cx, cy));
// 			}
// 			continue;
// 		}

// 		// 見つからなければ新規としてOpenリストへ追加
// 		mapOpen.insert(KEYDATA(nodes[i].x, nodes[i].y, nodes[i]));
// 	}

// 	//見つかったら探索終了
// 	if(n.x == GX && n.y == GY) {
// 		route.push_front({n.x, n.y});
// 	}

// 	if(Search(count + 1) == -1) {
// 		route.push_front({n.x, n.y});
// 	}

// 	return route;
// }
