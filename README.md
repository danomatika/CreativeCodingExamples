# CreativeCodingExamples

[openFrameworks](http://openframeworks.cc) examples for the [EDP](http://www.du.edu/ahss/edp/) Creative Coding class @ the University of Denver.

## Examples

**Bounce**: bounce a circle (or rectangle) around the screen

**Easing**: move circles horizontally towards a target x position using an easing calculation

**Follow**: move a circle towards a target using easing movement calculations

**Gravity**: simulate gravity to bounce a circle using vector math for velocity and acceleration

**Noise**: movement animation using Perlin noise

**SinCos**: movement animation using the sine & cosine functions

**Typewriter**: type into a string buffer using std::set to keep track of the keys being held down

**Web**: a small particle system visualization using a classes & vector

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
