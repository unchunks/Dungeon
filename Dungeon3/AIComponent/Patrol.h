#pragma once

// プレイヤー未発見の状態。発見次第Attack || Escape に移行
class Patrol {
public:
private:
};
/*
switch(e.getState()) {
            case Actor::SEARCH:
                // e.setDir(static_cast<Actor::DIRECTION> (rand() % 4));
                e.move(e.getDir());
                if(isFound(e)) {
                    e.setState(Actor::FOUND);
                }
                while(true) {
                    if(canGetOn(e.getX(), e.getY(), ENEMY))
                        break;
                    else {
                        e.back();
                        e.setDir(static_cast<Actor::DIRECTION> (rand() % 4));
                    }
                }
                break;
        }
*/