# fract.ol
## Project
This project was made for learning purposes fully in C with a bare-bones graphical library and limited skills, 
it shows different types of fractals and implies some techniques like the smooth coloring

## Purposes
  * Learn how to use structs in order to avoid global variables
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
    make

## Use
### Run
      ./fractol <selected fractal> <julia values(optional, only for julia set)> <number of iterations> <additional settings(optional)>

#### selected fractal

You can choose between three different equations:

* Mandelbrot
* Julia
* Burning ship

To run the corresponding fractal use the initial letter of the equation

#### number of iterations

Play with this value to be able to zoom deeper, the higher is the value the slower is the program, but you can zoom 
really deep, a  really high value could be 2000

#### additional settings(optional)
You can specify three types of additional settings without a specific order:

* Window size:    type "X_SIZExY_SIZE", default is 1000x1000
* Color palette:  specify 0 for a procedurally generated palette, 1 for a fixed one, default is 0
* Julia's step:   defines the intensity of the WASD controls for Julia's set, default is 0.1

#### julia values(optional, only for julia set)
For rendering the Julia's set you have to specify the values to be used in the equation, specify two decimal (not integer) values

### Examples
* To run the Mandelbrot set with 500 iterations you have to write:
		./fractol m 500
* To run the Julia set:
		./fractol j 0.1 -0.4 250
* To run the Burning ship set:
		./fractol b 1000
* To run the Mandelbrot set with additional arguments:
		./fractol m 500 1920x1080 1
* To run the Mandelbrot set with a WASD step of 0.01:
		./fractol m 500 0.01 1 1920x1080

## Extra features

* Smooth coloring
* Color shifting (press ',' or '.' to shift the colors)
* Color shift reset (press 'p' to reset to initial state)
* Viewport reset (press 'r' to reset the zoom to the initial state)
* **ONLY FOR JULIA SET** Fractal shape manipulator (press 'w', 'a', 's' or 'd' to change the equation values)
