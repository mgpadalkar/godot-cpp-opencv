# godot-cpp-opencv
Godot example with C++ and OpenCV functions in GDNative.
Referred from: [https://docs.godotengine.org/it/stable/tutorials/scripting/gdnative/gdnative_cpp_example.html](https://docs.godotengine.org/it/stable/tutorials/scripting/gdnative/gdnative_cpp_example.html)


## clone
```bash
git clone --recursive git@github.com:mgpadalkar/godot-cpp-opencv.git
cd godot-cpp-opencv
```

## submodule init
```bash
git submodule update --init  --recursive
```

## Structure that we now have

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
    │   ├── project.godot             #
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

## compile our library
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
