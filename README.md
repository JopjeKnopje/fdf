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


### Color values map

#### The colors values in the map
* `0xaabbccdd` with the layout 0x[RED][GREEN][BLUE][ALPHA]

#### In little endian it should look like
* `0xaabbccdd` with the layout 0x[ALPHA][BLUE][GREEN][RED]

#### In big endian it should look like
* `0xaabbccdd` with the layout 0x[RED][GREEN][BLUE][ALPHA]



# TODO
## Features
- [x] Read norm about global static const char arrays.
- [ ] Some sort of optimization where it doens't draw the pixels that are already there?
- [ ] When there is no user input (so when the scene isn't changing do not update the graphics)
- [ ] Double check if makefile MLX related rules function correctly 
- [ ] Resize window. 
- [x] Min max window size.
- [ ] FPS Counter in screen.
- [x] Support multiple projections in an enum that we can pass to the projector.
- [x] Weird color behaviour on linux.
- [ ] For clearing the screen just memset into the pixel buffer.
- [ ] Instead of gnl just read a shit ton of data from the map.
- [ ] Spherical projection
- [x] Gradient on lines
- [ ] Gradient on height
- [x] Save projection angles on number keys.
- [ ] Add automatic rotate funcion.
- [ ] Add screensaver mode (like a dvd player has).
- [ ] Switch between gradient for height and gradient for actual map color values.
- [ ] Rainbow colors.


## Issues
- [x] Only draw the pixels that are viewable.
- [?] Segfault when resizing too quick.
- [x] Segfault when opening a max with scale too large for window. (only on mac)
- [ ] Memset pixel clear
- [ ] When loading t1 for example some lines don't get drawn and seem to dissapear at certain angles,
      It has to do with not having a Z-buffer.
- [x] Pixels being draw at `x`.
- [?] Endianness check in get_color();
- [ ] Colors in map don't correspond to their hex value.
- [x] Use union for colors to get rid of `get_color_x` functions.
- [?] Color union endianness?
- [ ] Check the interpolate function bitshift value on mac.

## Todo for next time

- [ ] Continue working on whack ass colors
- [ ] Black white gradient
- [ ] Linedrawing optimization
- [ ] Sidebar


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
