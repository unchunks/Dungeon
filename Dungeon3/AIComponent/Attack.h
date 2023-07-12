// プレイヤーに攻撃可能であれば攻撃、不可能であればプレイヤーに向けて移動
/*
switch(e.getState()) {
            case Actor::FOUND:
                // プレイヤーへの経路探索
                vec2 start = vec2(e.getX(), e.getY());
                vec2 goal = vec2(player.getX(), player.getY());
                e.toPlayer = AStar(start, goal);

                e.moveTo(e.toPlayer[e.elapsedTurn]);
                if(!canGetOn(e.getX(), e.getY(), ENEMY))
                    e.back();
                e.elapsedTurn++;
                if(canAttack(player.getX(), player.getY(), ENEMY)) {
                    e.setState(Actor::ATTACK);
                    e.attack(&player);
                }
                if(!isFound(e)) {
                    e.setState(Actor::SEARCH);
                }
                break;

            case Actor::ATTACK:
                if(canAttack(player.getX(), player.getY(), ENEMY))
                    e.attack(&player);
                else
                    e.setState(Actor::SEARCH);
                break;

            case Actor::ESCAPE:
                break;
        }
*/