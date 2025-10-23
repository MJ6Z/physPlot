#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>
#include <opencv2/opencv.hpp>
#include <vector>
#include <string>
#include <algorithm>
#include <cmath>

//rendering a simple 2D line plot
void lineplot(pybind11::array_t<double> x, pybind11::array_t<double> y,
                 const std::string& window_name = "plot",
                 const std::string& save_path = "",
                 const int& line_thickness = 2,
                 bool show = true)
{
    //get numpy buffers
    auto buf_x = x.unchecked<1>();
    auto buf_y = y.unchecked<1>();
    size_t n = std::min(buf_x.shape(0), buf_y.shape(0));

    //create window
    const int width = 800, height = 600;
    cv::Mat img(height, width, CV_8UC3, cv::Scalar(255, 255, 255));

    //compute bounds
    double xmin = buf_x(0), xmax = buf_x(0);
    double ymin = buf_y(0), ymax = buf_y(0);
    for (size_t i = 0; i < n; ++i) {
        xmin = std::min(xmin, buf_x(i));
        xmax = std::max(xmax, buf_x(i));
        ymin = std::min(ymin, buf_y(i));
        ymax = std::max(ymax, buf_y(i));
    }

    //map data coords to image pixels
    auto to_px = [&](double vx, double vy) -> cv::Point {
        int px = static_cast<int>((vx - xmin) / (xmax - xmin) * (width - 1));
        int py = height - static_cast<int>((vy - ymin) / (ymax - ymin) * (height - 1));
        return cv::Point(px, py);
    };

    //draw line - img to draw to, point1, point2, colour, thickness.
    for (size_t i = 1; i < n; ++i) {
        cv::line(img, to_px(buf_x(i-1), buf_y(i-1)), to_px(buf_x(i), buf_y(i)), cv::Scalar(255, 0, 0),line_thickness);
    }

    //show in a window
    if (show) {
        cv::imshow(window_name, img);
        cv::waitKey(0);
        cv::destroyAllWindows();
    }

    //save to file
    if (!save_path.empty()) {
        cv::imwrite(save_path, img);
    }
}

PYBIND11_MODULE(physPlot, m) {
    m.doc() = "C++ plotting backend using OpenCV";
    m.def("lineplot", &lineplot,
          "Render and show/save a plot using OpenCV",
          pybind11::arg("x"),
          pybind11::arg("y"),
          pybind11::arg("window_name") = "plot",
          pybind11::arg("save_path") = "",
          pybind11::arg("line_thickness") = 2,
          pybind11::arg("show") = true);
}
