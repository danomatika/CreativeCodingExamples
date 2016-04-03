# CreativeCodingExamples

[openFrameworks](http://openframeworks.cc) examples for the [EDP](http://www.du.edu/ahss/edp/) Creative Coding class @ the University of Denver.

## Examples

<p align="center">
<img src="https://raw.github.com/danomatika/CreativeCodingExamples/master/_screenshots/Bounce.png"/>
</p>

**Bounce**: bounce a circle (or rectangle) around the screen

<p align="center">
<img src="https://raw.github.com/danomatika/CreativeCodingExamples/master/_screenshots/Easing.png"/>
</p>

**Easing**: move circles horizontally towards a target x position using an easing calculation

<p align="center">
<img src="https://raw.github.com/danomatika/CreativeCodingExamples/master/_screenshots/Follow.png"/>
</p>

**Follow**: move a circle towards a target using easing movement calculations

<p align="center">
<img src="https://raw.github.com/danomatika/CreativeCodingExamples/master/_screenshots/Gravity.png"/>
</p>

**Gravity**: simulate gravity to bounce a circle using vector math for velocity and acceleration

<p align="center">
<img src="https://raw.github.com/danomatika/CreativeCodingExamples/master/_screenshots/Noise.png"/>
</p>

**Noise**: movement animation using Perlin noise

<p align="center">
<img src="https://raw.github.com/danomatika/CreativeCodingExamples/master/_screenshots/SinCos.png"/>
</p>

**SinCos**: movement animation using the sine & cosine functions

<p align="center">
<img src="https://raw.github.com/danomatika/CreativeCodingExamples/master/_screenshots/Typewriter.png"/>
</p>

**Typewriter**: type into a string buffer using std::set to keep track of the keys being held down

<p align="center">
<img src="https://raw.github.com/danomatika/CreativeCodingExamples/master/_screenshots/Web.png"/>
</p>

**Web**: a small particle system visualization using a class & vector

## Downloading

You can download this repository as a .zip file using the "Download ZIP" button.

If you have git set up, you can clone this repo using:

    git clone https://github.com/danomatika/CreativeCodingExamples.git

The resulting "CreativeCodingExamples" folder should be placed within the `openFrameworks/apps` folder.

## Generating Project Files

These examples do *not* come with the project files pre-generated. You will need to use the [OF ProjectGenerator](http://openframeworks.cc/learning/01_basics/create_a_new_project) to create them for each example (you should only need to do this once).

To (re)generate project files for an *existing* project:

* click the "Import" button in the ProjectGenerator
* navigate the to base folder for the project ie. "Bounce"
* click the "Update" button

If everything went OK, you should now be able to open the generated project and build/run the example.
