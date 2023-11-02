#ifndef GD_OPENCV_EXAMPLE_H
#define GD_OPENCV_EXAMPLE_H

#include <godot_cpp/classes/sprite2d.hpp>
#include <godot_cpp/classes/engine.hpp> // needed to avoid running in the editor 
#include <godot_cpp/classes/image.hpp> // needed for godot::Ref<godot::Image>

#include <opencv2/opencv.hpp> // to start cv::VideoCapture
#include "own_opencv_processing.h" // to process captured frame

namespace godot
{

    class GDOpenCVExample : public Sprite2D
    {
        GDCLASS(GDOpenCVExample, Sprite2D)

        private:
            int camera_id;
            int width;
            int height;
            bool show_processed;

            cv::VideoCapture *cap;
            cv::Mat frame;
            OpenCVProcessing *own_opencv_code_object;

        protected:
            static void _bind_methods();

        public:
            GDOpenCVExample();
            ~GDOpenCVExample();

            void _process(double delta);

            // to select camera
            void set_camera_id(const int cam_id);
            int get_camera_id() const;
            void set_camera_width(const int cam_width);
            int get_camera_width() const;
            void set_camera_height(const int cam_height);
            int get_camera_height() const;
            void init_camera();

            // to select processed/unprocessed image for display
            void set_show_processed(bool do_process);
            bool get_show_processed();

            // to convert from cv::Mat to godot::Ref<godot::Image>
            Ref<Image> cvMat_to_Image(cv::Mat input);
            Array cvMat_to_Image(std::vector<cv::Mat> input);
    };

}

#endif
