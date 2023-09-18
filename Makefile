all : main.cpp
	g++ main.cpp -g -o dungeon && ./dungeon

commit-% :
	git add -A
	git commit -m "${@:commit-%=%}"

push-% :
	git add -A
	git commit -m "${@:push-%=%}"
	git push

test : test.cpp
	g++ test.cpp -g -o test && ./test