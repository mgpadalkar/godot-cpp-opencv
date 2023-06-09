#ifndef GDOPENCVEXAMPLE_H
#define GDOPENCVEXAMPLE_H

#include <Godot.hpp>
#include <Sprite.hpp>
#include <Image.hpp>

#include <opencv2/opencv.hpp> // to start cv::VideoCapture

#include "own_opencv_processing.h" // to process captured frame


namespace godot
{
    class GDOpenCVExample : public Sprite
    {
        GODOT_CLASS(GDOpenCVExample, Sprite)

        private:
            int camera_id;
            int width;
            int height;
            bool show_processed;

            cv::VideoCapture *cap;
            cv::Mat frame;
            cv::Mat output;
            Ref<Image> gd_frame;
            OpenCVProcessing *own_opencv_code_object;

        public:
            static void _register_methods();

            GDOpenCVExample();
            ~GDOpenCVExample();

            void _init(); // our initializer called by Godot

            void _process(float delta); // called at every time instant by Godot

            // to select camera
            void set_camera_id(int cam_id);
            int get_camera_id();
            void init_camera();

            Ref<Image> cvMat_to_Image();  // converts cv::Mat to Godot Image

            // to select processed/unprocessed image for display
            void set_show_processed(bool do_process);
            bool get_show_processed();
    };
}

#endif
