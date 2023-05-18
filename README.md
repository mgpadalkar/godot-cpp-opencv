# Using OpenCV C++ code with Godot 3.5.2
Godot example with C++ and OpenCV functions in GDNative.   
Referred from: [https://docs.godotengine.org/en/3.5/tutorials/scripting/gdnative/gdnative_cpp_example.html](https://docs.godotengine.org/en/3.5/tutorials/scripting/gdnative/gdnative_cpp_example.html)

## How was this repository created?
1. Downloading the GDNative C++ Example [Watch Video](https://www.youtube.com/watch?v=J4fD2DpdZFY)
2. Downloading Godot 3.5.2 [Watch Video](https://www.youtube.com/watch?v=uGxEqEZcE34)
3. Making an empty project [Watch Video](https://www.youtube.com/watch?v=O7mk8gXt0SQ)
4. Writing our own OpenCV code [Watch Video](https://www.youtube.com/watch?v=fTQO1rdPL2A)
5. Creating the GDNative wrapper [Watch Video](https://www.youtube.com/watch?v=xmIunfSEQps)
6. Compiling our code + wrapper with SConstruct [Watch Video](https://www.youtube.com/watch?v=pSwlfsST6oc)
7. Creating files necessary for using our code in Godot [Watch Video](https://www.youtube.com/watch?v=cGgGFl-IFkk)
8. Using our code to access webcam in a 2D scene [Watch Video](https://www.youtube.com/watch?v=klEPolEk2aA)


## How to use this repository?
1. [Clone](#clone)
2. Compile godot-cpp
3. Compile our OpenCV code with Godot wrapper
4. Using our code to access webcam in a 2D scene [Watch Video](https://www.youtube.com/watch?v=klEPolEk2aA)
5. Showing the webcam frames in a 3D scene [Watch Video](https://www.youtube.com/watch?v=_CPhs4S6hZM)
6. Displaying the OpenCV output in HMD [Watch Video](https://www.youtube.com/watch?v=34rrUbCTPwg)

## Clone Recursive
```bash
git clone --recursive git@github.com:mgpadalkar/godot-cpp-opencv.git
cd godot-cpp-opencv
git submodule update --init --recursive
```

### Structure that we now have
    godot-cpp-opencv                  # the repository
    ├── godot-cpp                     #
    │   ├── godot-headers             #
    │   │   ├── <lots of files>       #
    │   ├── <lots of other files>     #
    ├── demo                          # project folder
    │   ├── bin                       #
    │   │   ├── gd_opencv.gdnlib      #
    │   │   ├── gd_opencv.gdns        #
    │   ├── default_env.tres          #
    │   ├── icon.png                  #
    │   ├── Main2D.tscn               #
    │   ├── Main2D.gd                 #
    │   ├── project.godot             #
    ├── misc                          #
    │   ├── set_opencv4.sh            # my opencv install settings
    ├── README.md                     #
    ├── SConstruct                    #
    ├── src                           # C++ code folder
    │   ├── gd_opencv.h               #
    │   ├── gd_opencv.cpp             #
    │   ├── gd_opencv_library.cpp     #
    │   ├── own_opencv_processing.h   #
    │   ├── own_opencv_processing.cpp #
    └── ...


##  compile godot-cpp
```bash
cd godot-cpp
scons platform=linux generate_bindings=yes -j8 
# It generates: godot-cpp/bin/libgodot-cpp.linux.debug.64.a
```

## Compile our OpenCV code with Godot wrapper
 - Compile OpenCV from source if needed.   
   I had followed this for Ubuntu 20.04: https://gist.github.com/raulqf/f42c718a658cddc16f9df07ecc627be7

```bash
# This step requires opencv to be installed and available in the path.
# In my case, I had compiled OpenCV myself and set the path
# using the script misc/set_opencv4.sh
# (OpenCV was installed in ${HOME}/localInstalls/opencv-4.5.2/).
# I had to do `source misc/set_opencv4.sh` to set the paths. 

cd ..
scons platform=linux

# It generates: demo/bin/x11/libgdopencvexample.so
```

Now use Godot (I used v3.5.2) to use the generated library.   
Note: If OpenCV is built from source, like in my case,
start Godot from the terminal in which the OpenCV paths are
already set so that the OpenCV shared libs are available to
Godot.


## Using our code to access webcam in a 2D scene
I am using Godot 3.5.2 downloaded from https://github.com/godotengine/godot/releases/download/3.5.2-stable/Godot_v3.5.2-stable_x11.64.zip

The scene is already created using the following steps.  
Simply run to view the webcam output in Godot.   

* Add a `TextureRect` to `Main2D` and rename it to `webcamView`
* Add a `Sprite` to `Main2D`
* Attach the `bin\gd_opencv.gdns` script to `Sprite`
* Create a `Main2D.gd` script and attach it to `Main2D`
* Connect `frame_updated` signal of `Sprite` to `Main2D`
* Modify the `Main2D.gd` scripts' `func _on_Sprite_frame_updated(node image)` function with the following lines:
```gdscript
func _on_Sprite_frame_updated(node, image):
	var image_texture:ImageTexture = ImageTexture.new()
	image_texture.create_from_image(image)
	$webcamView.texture = image_texture
```

For more details, watch the following video.   
[![Using our code to access webcam in a 2D scene](https://img.youtube.com/vi/klEPolEk2aA/0.jpg)](https://www.youtube.com/watch?v=klEPolEk2aA)

## Showing the webcam frames in a 3D scene

[![Showing the webcam frames in a 3D scene](https://img.youtube.com/vi/_CPhs4S6hZM/0.jpg)](https://www.youtube.com/watch?v=_CPhs4S6hZM)


## Displaying the OpenCV output in HMD
[![Displaying the OpenCV output in HMD](https://img.youtube.com/vi/34rrUbCTPwg/0.jpg)](https://www.youtube.com/watch?v=34rrUbCTPwg)

