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
- [x] Double check if makefile MLX related rules function correctly 
- [ ] Resize window. 
- [x] Min max window size.
- [ ] FPS Counter in screen.
- [x] Support multiple projections in an enum that we can pass to the projector.
- [x] Weird color behaviour on linux.
- [ ] For clearing the screen just memset into the pixel buffer.
- [ ] Instead of gnl just read a shit ton of data from the map.
- [ ] Spherical projection
- [x] Gradient on lines
- [x] Save projection angles on number keys.
- [ ] Add automatic rotate funcion.
- [ ] Add screensaver mode (like a dvd player has).
- [ ] Switch between gradient for height and gradient for actual map color values.
- [ ] Gradient on height
- [ ] Rainbow colors.
- [ ] Z-buffer to prevent "When loading t1 for example some lines don't get drawn and seem to dissapear at certain angles".
- [ ] Perspective camera.
- [ ] Calculate the initial size of the wireframe so it fits perfectly in the window (also do this on resize).
- [ ] Mouse dragging to move wireframe.




## Issues
- [x] Only draw the pixels that are viewable.
- [x] Segfault when opening a max with scale too large for window. (only on mac)
- [x] Pixels being draw at `x = 0`.
- [x] Colors in map don't correspond to their hex value on linux.
- [x] Use union for colors to get rid of `get_color_x` functions.
- [ ] Map does weird stuff on spaces see `weird_map.fdf`
- [?] Segfault when resizing too quick.
- [?] Color union endianness?

## Todo for next time

- [x] Linedrawing optimization
- [ ] Sidebar
- [ ] Black white gradient
- [ ] Don't use jumptable in `view select`.
- [ ] Check the interpolate function bitshift value on mac.


## Resources
### Projection
* https://clintbellanger.net/articles/isometric_math/
* https://en.wikipedia.org/wiki/Rotation_matrix
* https://en.wikipedia.org/wiki/3D_projection

* https://stackoverflow.com/questions/39440390/deforming-plane-mesh-to-sphere
* http://paulbourke.net/geometry/transformationprojection/


### Color union
* https://www.flipcode.com/archives/Using_a_Union_for_Packed_Color_Values.shtml

### Faster hypotenuse for color gradient.
* https://stackoverflow.com/questions/3506404/fast-hypotenuse-algorithm-for-embedded-processor

### Colors
* https://krazydad.com/tutorials/makecolors.php
