# Using OpenCV C++ code with Godot 4.1.2 on Ubuntu 20.04
Godot's GDExtension example with C++ and OpenCV functions.   

Purpose:   
- [x] Acquire video with a webcam
- [x] Process frames with OpenCV
- [x] Display output in AR/VR headset

Referred from: [https://docs.godotengine.org/en/4.1/tutorials/scripting/gdextension/gdextension_cpp_example.html](https://docs.godotengine.org/en/4.1/tutorials/scripting/gdextension/gdextension_cpp_example.html)


## How to use this repository?
1. [Clone](#clone-recursive)
2. [Compile godot-cpp](#compile-godot-cpp)
3. [Compile our OpenCV code with Godot wrapper](#compile-our-opencv-code-with-godot-wrapper)
4. [Using our code to access webcam in a 2D scene](#using-our-code-to-access-webcam-in-a-2d-scene) | [Watch Video](https://www.youtube.com/watch?v=klEPolEk2aA)
5. [Showing the webcam frames in a 3D scene](#showing-the-webcam-frames-in-a-3d-scene) | [Watch Video](https://www.youtube.com/watch?v=_CPhs4S6hZM)
6. [Displaying the OpenCV output in HMD](#displaying-the-opencv-output-in-hmd) | [Watch Video](https://www.youtube.com/watch?v=34rrUbCTPwg)

## Clone Recursive
```bash
git clone -b 4.1 --recursive https://github.com/mgpadalkar/godot-cpp-opencv.git
cd godot-cpp-opencv
# git submodule update --init --recursive
```

P.S.: If you are downloading the .zip file, ensure that the `godot-cpp` folder if populated. See the structure below to be sure.
<details>
  <summary>Structure that we now have (click to expand)</summary>
	
    godot-cpp-opencv                           # the repository
    ├── godot-cpp                              #
    │   ├── godot-headers                      #
    │   │   ├── <lots of files>                #
    │   ├── <lots of other files>              #
    ├── demo                                   # project folder
    │   ├── bin                                #
    │   │   ├── gd_opencv_example.gdextension  #
    │   ├── icon.png                           #
    │   ├── Main2D.tscn                        #
    │   ├── Main2D.gd                          #
    │   ├── project.godot                      #
    ├── misc                                   #
    │   ├── set_opencv4.sh                     # my opencv install settings
    ├── README.md                              #
    ├── SConstruct                             #
    ├── src                                    # C++ code folder
    │   ├── gd_opencv.h                        # header for wrapper to use OpenCV in Godot
    │   ├── gd_opencv.cpp                      # wrapper to use OpenCV in Godot
    │   ├── register_types.cpp                 # library for the wrapper
    │   ├── register_types.h                   # header for the wrapper
    │   ├── own_opencv_processing.h            # our OpenCV header
    │   ├── own_opencv_processing.cpp          # out OpenCV code
    └── ...
</details>

##  Compile godot-cpp
```bash
cd godot-cpp
scons target=template_debug platform=linux generate_bindings=yes 
# It generates: godot-cpp/bin/libgodot-cpp.linux.template_debug.x86_64.a
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

# It generates: demo/bin/libgd_opencv_example.linux.template_debug.x86_64.so
```

Now use Godot (I used v4.1.2) to use the generated library.   
Note: If OpenCV is built from source, like in my case,
start Godot from the terminal in which the OpenCV paths are
already set so that the OpenCV shared libs are available to
Godot.


## Using our code to access webcam in a 2D scene
I am using Godot 4.1.2 downloaded from [https://github.com/godotengine/godot/releases/download/4.1.2-stable/Godot_v4.1.2-stable_linux.x86_64.zip](https://github.com/godotengine/godot/releases/download/4.1.2-stable/Godot_v4.1.2-stable_linux.x86_64.zip)

The scene is already created using the following steps.  
Simply run to view the webcam output in Godot.   

1. Create a new scene by adding `Other Node` -> `CanvasLayer` and rename it to `Main2D`
2. Add a `TextureRect` to `Main2D` and rename it to `webcamView`
3. Add a `Sprite2D` to `Main2D`
4. Add a `GDOpenCVExample` to `Sprite2D`
5. Create a `Main2D.gd` script and attach it to `Main2D`
6. Connect `frame_updated` signal of `GDOpenCVExample` to `Main2D`
7. Modify the `Main2D.gd` scripts' `func _on_gd_open_cv_example_frame_updated(node, image)` function with the following lines:
```gdscript
func _on_gd_open_cv_example_frame_updated(node, image):
        var image_texture:ImageTexture = ImageTexture.new()
	image_texture.set_image(image)
	$webcamView.set_texture(image_texture)
```

For more details, watch the following video.   
[![Using our code to access webcam in a 2D scene](https://img.youtube.com/vi/klEPolEk2aA/0.jpg)](https://www.youtube.com/watch?v=klEPolEk2aA)

## Showing the webcam frames in a 3D scene

1. Create a new 3D Scene
2. Rename `Spatial` to `Main3D`
3. Save the scene as `Main3D.tscn` and set it as the main scene.
4. Go to `AssetLib` and search for `xr`
5. Download and install `Godot XR Tools - AR and VR helper library`
6. Go to `Project` -> `Project Settings` -> `Plugins` tab and enable the `Godot XR Tools` plugin.
7. Save and go to `Project` -> `Reload Current Project`
8. Add a `WorldEnvironment` to `Main3D`
9. Add a `ARVROrigin` to `Main3D`
10. Add a `ARVRCamera` to `ARVROrigin`
11. In `FileSystem` got to `addons` -> `godot-xr-tools` -> `objects` -> `viewport_2d_in_3d.tscn`, drag and drop it onto `ARVRCamera`
12. The above step creates a `Viewport2Din3D`.
    - Set `Viewport Size` to `640x480` and `Transform` to `[0, 0, -1.63]`
    - Drag and drop `Main2D.tscn` from `FileSystem` onto `Scene` for the `Viewport2Din3D`
    - Select `Unshaded`
14. In `FileSystem` got to `addons` -> `godot-xr-tools` -> `xr` -> `start_xr.gd`, drag and drop it onto `ARVROrigin`
15. Save the scene and run to view the output in the 3D scene.

For more details watch the following video.   
[![Showing the webcam frames in a 3D scene](https://img.youtube.com/vi/_CPhs4S6hZM/0.jpg)](https://www.youtube.com/watch?v=_CPhs4S6hZM)


## Displaying the OpenCV output in HMD

1. Go to `AssetLib` and search for `xr`
2. Download and install `OpenXR Plugin`
3. Go to `Project` -> `Project Settings` -> `Plugins` tab and enable the `Godot OpenXR` plugin.
4. Save and go to `Project` -> `Reload Current Project`
5. Start your XR runtime:
   - If you have a XR runtime like [Monado](https://monado.freedesktop.org/) start with in a new terminal with `monado-service`
   - If you have SteamVR, start it so that your HMD is available
6. Now run the project. The output should be visible to you in your HMD.    
   (In my case, I did not have a HMD attached, so the output was shown on screen in a Dummy HMD)

<details>
	<summary>How I installed Monado? (click to expand)</summary>
	
	# the following should be sufficient
	sudo add-apt-repository ppa:monado-xr/monado
	sudo apt-get update
	sudo apt-get install libopenxr-loader1 libopenxr-dev libopenxr1-monado
	sudo apt-get install xr-hardware libopenxr-utils openxr-layer-apidump monado-cli monado-gui
	
	# if you need to build from source, see https://monado.freedesktop.org/getting-started.html#monado-installation
	sudo apt-get install build-essential cmake libgl1-mesa-dev libvulkan-dev libx11-xcb-dev libxcb-dri2-0-dev libxcb-glx0-dev libxcb-icccm4-dev libxcb-keysyms1-dev libxcb-randr0-dev libxrandr-dev libxxf86vm-dev mesa-common-dev
	
	# to run cretain demos on https://gitlab.freedesktop.org/monado/demos, you may also need the following
	sudo apt-get install libsdl2-dev
	sudo apt-get install libglm-dev
	sudo apt-get install glslang-tools

</details>	
	
For more details watch the following video.  
[![Displaying the OpenCV output in HMD](https://img.youtube.com/vi/34rrUbCTPwg/0.jpg)](https://www.youtube.com/watch?v=34rrUbCTPwg)



## How was this repository created?
1. Downloading the GDNative C++ Example | [Watch Video](https://www.youtube.com/watch?v=J4fD2DpdZFY)
2. Downloading Godot 3.5.2 | [Watch Video](https://www.youtube.com/watch?v=uGxEqEZcE34)
3. Making an empty project | [Watch Video](https://www.youtube.com/watch?v=O7mk8gXt0SQ)
4. Writing our own OpenCV code | [Watch Video](https://www.youtube.com/watch?v=fTQO1rdPL2A)
5. Creating the GDNative wrapper | [Watch Video](https://www.youtube.com/watch?v=xmIunfSEQps)
6. Compiling our code + wrapper with SConstruct | [Watch Video](https://www.youtube.com/watch?v=pSwlfsST6oc)
7. Creating files necessary for using our code in Godot | [Watch Video](https://www.youtube.com/watch?v=cGgGFl-IFkk)
8. Using our code to access webcam in a 2D scene | [Watch Video](https://www.youtube.com/watch?v=klEPolEk2aA)
	
P.S.: All above videos are without audio.
