# fract.ol
## Project
This project was made for learning purposes fully in C with a bare-bones graphical library and limited skills, 
it shows different types of fractals and implies some techniques like the smooth coloring

## Purposes
  * Learn how to work with complex equations in loops
  * Practice to work with graphical libraries at a really low-level

## Requirements
  * gcc
  * make
  * MacOS 10.X or higher, not tested on earlier versions

## Installation
### Terminal
    git clone git@github.com:XEDGit/fract.ol.git
    cd fract.ol/
    make prod
    cd Executables/
## Use
### Before
You can now run different versions of the executable, since the graphical library doesn't support resizing there's different sized executables

* xtra => 2560x1440
* big => 1920x1080
* medium => 1000x1000
* small => 640x480
* xsmall => 100x100

Choose what suits your hardware best, consider the xtra version is supposed to run at around 2-3 fps when zooming deep.
Now you can just choose the color set between

* 0 => Procedurally generated palette
* 1 => User-defined palette

### Run
      ./fractol_<window size><color set> <selected fractal> <number of iterations>
      
#### <selected fractal>
You can choose between three different equations:

* Mandelbrot
* Julia
* Burning ship

To run the corresponding fractal use the initial letter of the equation

#### <number of iterations>
Play with this value to be able to zoom deeper, the higher is the value the slower is the program, but you can zoom 
really deep, a  really high value could be 2000

### Examples
To run the Mandelbrot set with 500 iterations you have to write:
    ./fractol_medium0 m 500
To run the Julia set:
    ./fractol_big1 j 250
To run the Burning ship set:
    ./fractol_small0 b 1000
    
## Extra features

* Smooth coloring
* Color shifting (press ',' or '.' to shift the colors)
* Viewport reset (press 'r' to reset the zoom to the initial state)
* **ONLY FOR JULIA SET** fractal shape manipulator (press 'w', 'a', 's' or 'd' to change the equation values)
