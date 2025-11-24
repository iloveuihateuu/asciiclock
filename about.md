# ASCII Analog clock build with ncurses
Pretty self descriptionary.

## Build flags
``bash
clang++ main.cpp renderer.cpp shapes.cpp clock.cpp input.cpp surface.cpp -o app -g -lncursesw -lpanel -lmenu
``
## TODO
- [x] Implement working unicode support
- [x] Fix the smooth line drawing bug (the passed angle isnt the actual angle of the line because xFactor scales it)
- [x] Implement surfaces for drawing ascii sprites
- [ ] Implement nearest neighbour scaling for surfaces
- [ ] Implement first run configuration setup that loads on future runs


