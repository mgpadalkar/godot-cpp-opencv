#include "gd_opencv.h"
#include <godot_cpp/core/class_db.hpp>

using namespace godot;

void GDOpenCVExample::_bind_methods()
{
    ClassDB::bind_method(D_METHOD("get_camera_id"), &GDOpenCVExample::get_camera_id);
    ClassDB::bind_method(D_METHOD("set_camera_id", "cam_id"), &GDOpenCVExample::set_camera_id);
    ClassDB::add_property("GDOpenCVExample", PropertyInfo(Variant::INT, "camera_id"), "set_camera_id", "get_camera_id");

    ClassDB::bind_method(D_METHOD("get_camera_width"), &GDOpenCVExample::get_camera_width);
    ClassDB::bind_method(D_METHOD("set_camera_width", "cam_width"), &GDOpenCVExample::set_camera_width);
    ClassDB::add_property("GDOpenCVExample", PropertyInfo(Variant::INT, "camera_width"), "set_camera_width", "get_camera_width");

    ClassDB::bind_method(D_METHOD("get_camera_height"), &GDOpenCVExample::get_camera_height);
    ClassDB::bind_method(D_METHOD("set_camera_height", "cam_height"), &GDOpenCVExample::set_camera_height);
    ClassDB::add_property("GDOpenCVExample", PropertyInfo(Variant::INT, "camera_height"), "set_camera_height", "get_camera_height");

    ClassDB::bind_method(D_METHOD("get_show_processed"), &GDOpenCVExample::get_show_processed);
    ClassDB::bind_method(D_METHOD("set_show_processed", "do_process"), &GDOpenCVExample::set_show_processed);
    ClassDB::add_property("GDOpenCVExample", PropertyInfo(Variant::BOOL, "show_processed"), "set_show_processed", "get_show_processed");
    
    ADD_SIGNAL(MethodInfo("frame_updated", PropertyInfo(Variant::OBJECT, "node"), PropertyInfo(Variant::OBJECT, "image")));

}

GDOpenCVExample::GDOpenCVExample()
{
    // Initialize any variables here.
    camera_id              = 0;
    width                  = 640;
    height                 = 480;
    cap                    = nullptr;
    show_processed         = false;
    own_opencv_code_object = new OpenCVProcessing();

    // to avoid running in the editor
    // see: https://www.reddit.com/r/godot/comments/117xjbs/gdextension_c_files_run_persistently_in_the_editor/
    if (Engine::get_singleton()->is_editor_hint())
        set_process_mode(Node::ProcessMode::PROCESS_MODE_DISABLED);

}

GDOpenCVExample::~GDOpenCVExample()
{
    // release cv::VideoCapture
    if (cap != nullptr)
        cap->release();

    // release frame
    if (!frame.empty())
        frame.release();

    // delete pointer to our OpenCV code's object
    delete own_opencv_code_object;
}

void GDOpenCVExample::_process(double delta)
{
    // initialize cv::VideoCapture
    if (cap==nullptr)
        init_camera();

    // read frame, get output and emit
    if (cap->isOpened())
    {
        if (cap->read(frame))
        {
            cv::Mat output = own_opencv_code_object->process_image(frame, show_processed);
            Ref<Image> gd_frame = cvMat_to_Image(output); // convert to Godot Image
            emit_signal("frame_updated", this, gd_frame);
        }
    }
}


// set the camera ID
void GDOpenCVExample::set_camera_id(const int cam_id)
{
    camera_id = cam_id;
}


// get the camera ID....not used
int GDOpenCVExample::get_camera_id() const
{
    return camera_id;
}


// set the camera width
void GDOpenCVExample::set_camera_width(const int cam_width)
{
    width = cam_width;
}


// get the camera width....not used
int GDOpenCVExample::get_camera_width() const
{
    return width;
}


// set the camera height
void GDOpenCVExample::set_camera_height(const int cam_height)
{
    height = cam_height;
}


// get the camera height....not used
int GDOpenCVExample::get_camera_height() const
{
    return height;
}


// initialize cv::VideoCapture
void GDOpenCVExample::init_camera()
{
    cap = new cv::VideoCapture(camera_id);
    if (cap->isOpened())
    {
        // set frame size
        cap->set(cv::CAP_PROP_FRAME_WIDTH, width);
        cap->set(cv::CAP_PROP_FRAME_HEIGHT, height);
    }
}


// set show_processed
void GDOpenCVExample::set_show_processed(bool do_process)
{
    show_processed = do_process;
}


// get show_processed....not used
bool GDOpenCVExample::get_show_processed()
{
    return show_processed;
}


// convert cv::Mat to Godot Image
Ref<Image> GDOpenCVExample::cvMat_to_Image(cv::Mat input)
{
    // convert output from BGR to RGB
    cv::Mat cv_rgb;
    cv::cvtColor(input, cv_rgb, cv::COLOR_BGR2RGB);

    // initialize PackedByteArray
    // Note: PoolByteArray -> PackedByteArray
    int numel = cv_rgb.rows * cv_rgb.cols * cv_rgb.channels();
    PackedByteArray bytes;
    bytes.resize(numel);

    // copy data to PackedByteArray
    if (cv_rgb.isContinuous())
    {
        // std::memcpy(bytes.write().ptr(), cv_rgb.ptr(), numel);
        std::memcpy(bytes.ptrw(), cv_rgb.ptr(), numel);
    }
    else
    {
        for (int i=0; i < sizeof(cv_rgb); i++)
        {
            // std::memcpy(bytes.write().ptr(), cv_rgb.ptr(i), numel);
            std::memcpy(bytes.ptrw(), cv_rgb.ptr(i), numel);
        }
    }

    // create Godot Image from the PackedByteArray
    Ref<Image> img;
    img.instantiate();
    img->set_data(cv_rgb.cols, cv_rgb.rows, false, img->FORMAT_RGB8, bytes);

    // return
    return img;
}
