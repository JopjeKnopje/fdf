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


### Clearing screen performance
#### Test map `42-custom2.fdf`
* Using a while loop for each pixel 400-450 fps
* Using ft_memset 390-440 fps
* Using memset 1800-2100 fps WTFFF??! (colors are incorrect tho because of the 1 byte thing).
* Using a memset32 820-920 pretty good :)

So instead of implementing this and probably facing more endianness related issues, lets just use the white loop. Since this stuff is like 5% percent of the actual performance on bigger maps.



# TODO
## Features
- [x] Read norm about global static const char arrays.
- [x] Double check if makefile MLX related rules function correctly 
- [x] Resize window. 
- [x] Min max window size.
- [x] Support multiple projections in an enum that we can pass to the projector.
- [x] Weird color behaviour on linux.
- [x] Gradient on lines
- [x] Save projection angles on number keys.
- [x] Linedrawing optimization
- [x] Black white gradient
- [x] In `view_saved` just memcopy.
- [x] Don't use jumptable in `view select`.
- [x] FPS Counter in screen.
- [x] Gradient on height.
- [x] Sidebar.
- [x] Use `t_timer` in `fps_hook(void *param)`.
- [ ] For clearing the screen just memset into the pixel buffer.
- [ ] Instead of gnl just read a shit ton of data from the map.
- [ ] Spherical projection.
- [ ] Add automatic rotate funcion.
- [ ] Add screensaver mode (like a dvd player has).
- [ ] Switch between gradient for height and gradient for actual map color values.
- [ ] Rainbow colors.
- [ ] Z-buffer to prevent "When loading t1 for example some lines don't get drawn and seem to dissapear at certain angles".
- [ ] Perspective camera.
- [ ] Calculate the initial size of the wireframe so it fits perfectly in the window (also do this on resize).
- [ ] Mouse dragging to move wireframe.
- [x] Check for newline when counting width.
- [ ] Draw square for all the point colors.
- [ ] Speed-up big maps.



## Issues
- [x] Only draw the pixels that are viewable.
- [x] Segfault when opening a max with scale too large for window. (only on mac)
- [x] Pixels being draw at `x = 0`.
- [x] Colors in map don't correspond to their hex value on linux.
- [x] Use union for colors to get rid of `get_color_x` functions.
- [ ] Map does weird stuff on spaces see `weird_map.fdf`
- [?] Segfault when resizing too quick.
- [x] Color union endianness?
- [ ] Calculating the gradient in `COLOR_MODE_HEIGHT` is pretty slow.

## Todo for next time

- [ ] Refactor the `get_color`.
- [ ] Refactor the way we draw line.
- [ ] Move on `t1` is slow.
- [ ] Is there another way to name `g_control_text_strings`?
- [ ] Look at `t_color_gradient`.
- [ ] Check makefile.


## Resources
### Projection
* https://clintbellanger.net/articles/isometric_math/
* https://en.wikipedia.org/wiki/Rotation_matrix
* https://en.wikipedia.org/wiki/3D_projection

* https://stackoverflow.com/questions/39440390/deforming-plane-mesh-to-sphere
* http://paulbourke.net/geometry/transformationprojection/

### Line drawing algorithm
* https://www.middle-engine.com/blog/posts/2020/07/28/bresenhams-line-algorithm

### Color union
* https://www.flipcode.com/archives/Using_a_Union_for_Packed_Color_Values.shtml

### Faster hypotenuse for color gradient.
* https://stackoverflow.com/questions/3506404/fast-hypotenuse-algorithm-for-embedded-processor

### Colors
* https://krazydad.com/tutorials/makecolors.php

### Sidenotes
* vaporwave type beat colors 
`
c_start.value = 0xff00ffff;
c_end.value = 0x00ffffff;
`
