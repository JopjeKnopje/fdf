# NOTES

## General flow
* Parse
* Project
* Draw


## Parsing
- [x] End with .fdf extension
- [x] Empty map
- [ ] Check for map dimensions
- [ ] Invalid characters
- [ ] Invalid color values


### LinkedList version
* Have a `point` datatype (vec3d with pixel color).
* gnl the map file
* split on each space and add each `point` to the linked list

#### Pro's and cons
Dynamic | slow


### 2DArray version `z = points[x][y]`
* Have a 2D int array contianing a `point` with this time containing only the z coord and the colorvalue.
* gnl the map file





# TODO
## Features
- [x] Read norm about global static const char arrays.
- [ ] Some sort of optimization where it doens't draw the pixels that are already there?
- [ ] When there is no user input (so when the scene isn't changing do not update the graphics)
- [ ] Double check if makefile MLX related rules function correctly 
- [ ] Only draw on user input.
- [ ] Rainbow gradient background.
- [ ] Resize window.
- [ ] min max window size.
- [ ] FPS Counter in screen.
- [ ] Support multiple projections in an enum that we can pass to the projector.
- [x] Weird color behaviour on linux.
- [ ] For clearing the screen just memset into the pixel buffer.
- [ ] Dikke read buffer broer
- [ ] Instead of gnl just read a shit ton of data from the map.
- [ ] Spherical projection
- [ ] Gradient on lines
- [ ] Gradient on height
- [ ] Save projection angles on number keys.


## Issues
- [x] Only draw the pixels that are viewable.
- [ ] Segfault when opening a max with scale too large for window. (only on mac)
- [ ] Memset pixel clear


## Resources
* https://clintbellanger.net/articles/isometric_math/
* https://en.wikipedia.org/wiki/Rotation_matrix
* https://en.wikipedia.org/wiki/3D_projection


* https://stackoverflow.com/questions/39440390/deforming-plane-mesh-to-sphere
* http://paulbourke.net/geometry/transformationprojection/
