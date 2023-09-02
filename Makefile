all : main.cpp
	g++ main.cpp -o dungeon && ./dungeon

commit : *
	git add -A
	git commit -m "$(m)"

push : *
	git add -A
	git commit -m "$(m)"
	git push