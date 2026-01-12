# ASCII Analog clock build with ncurses
Pretty self descriptionary.

## TODO
- [x] Implement working unicode support
- [x] Fix the smooth line drawing bug (the passed angle isnt the actual angle of the line because xFactor scales it)
- [x] Implement surfaces for drawing ascii sprites
- [x] Implement nearest neighbour scaling for surfaces
- [x] Implement first run configuration setup that loads on future runs
- [x] Added cmake
- [ ] Fix it so it pulls resources from system app folders and not from the directory its been ran in
- [ ] Fix flickering on some terminals (ghostty on MacOS)
