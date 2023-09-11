all : main.cpp
	g++ main.cpp -o dungeon && ./dungeon

commit-% :
	git add -A
	git commit -m "${@:commit-%=%}"

push-% :
	git add -A
	git commit -m "${@:push-%=%}"
	git push
	