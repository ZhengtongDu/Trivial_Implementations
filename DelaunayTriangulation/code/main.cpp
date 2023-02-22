#include"Triangle.h"
#include <chrono>
#include <opencv2/opencv.hpp>

std::vector<cv::Point2f> control_points;

void mouse_handler(int event, int x, int y, int flags, void *userdata) 
{
    if (event == cv::EVENT_LBUTTONDOWN && control_points.size() < 8) 
    {
        std::cout << "Left button of the mouse is clicked - position (" << x << ", "
        << y << ")" << '\n';
        control_points.emplace_back(x, y);
    }     
}

void naive_bezier(const std::vector<cv::Point2f> &points, cv::Mat &window) 
{
    auto &p_0 = points[0];
    auto &p_1 = points[1];
    auto &p_2 = points[2];
    auto &p_3 = points[3];

    for (double t = 0.0; t <= 1.0; t += 0.001) 
    {
        auto point = std::pow(1 - t, 3) * p_0 + 3 * t * std::pow(1 - t, 2) * p_1 +
                 3 * std::pow(t, 2) * (1 - t) * p_2 + std::pow(t, 3) * p_3;

        window.at<cv::Vec3b>(point.y, point.x)[2] = 255;
    }
}

cv::Point2f recursive_bezier(const std::vector<cv::Point2f> &control_points, float t) 
{
    // TODO: Implement de Casteljau's algorithm
    if(control_points.size() != 2){
        int n = control_points.size();
        std::vector<cv::Point2f> new_points(n - 1);
        for(int i = 0; i < n - 1; i++){
            new_points[i].x = control_points[i].x * t + control_points[i + 1].x * (1 - t);
            new_points[i].y = control_points[i].y * t + control_points[i + 1].y * (1 - t);
        }
        return recursive_bezier(new_points, t);
    }
    float x = control_points[0].x * t + control_points[1].x * (1 - t);
    float y = control_points[0].y * t + control_points[1].y * (1 - t);
    return cv::Point2f(x, y);
}

void bezier(const std::vector<cv::Point2f> &control_points, cv::Mat &window) 
{
    // TODO: Iterate through all t = 0 to t = 1 with small steps, and call de Casteljau's 
    // recursive Bezier algorithm.
    for(double t = 0; t <= 1; t += 0.001){
        auto point = recursive_bezier(control_points, t);
        double x = point.y;
        double y = point.x;
        for(int i = -1; i <= 1; i = i + 2){
            double distance = sqrt((int(x) + i + 0.5 - x) * (int(x) + i + 0.5 - x) + (int(y) + 0.5 - y) * (int(y) + 0.5 - y));
            if(window.at<cv::Vec3b>(x + i, y)[1] != 255)
                window.at<cv::Vec3b>(x + i, y)[1] = 255 * 0.5 / distance;
        }
        for(int i = -1; i <= 1; i = i + 2){
            double distance = sqrt((int(x) + 0.5 - x) * (int(x) + 0.5 - x) + (int(y) + i + 0.5 - y) * (int(y) + i + 0.5 - y));
            if(window.at<cv::Vec3b>(x, y + i)[1] != 255)
                window.at<cv::Vec3b>(x, y + i)[1] = 255 * 0.5 / distance;
        }
        window.at<cv::Vec3b>(x, y)[1] = 255;
    }
}


int main(int argc, char* argv[]){
    cv::Mat window = cv::Mat(700, 700, CV_8UC3, cv::Scalar(0));
    cv::cvtColor(window, window, cv::COLOR_BGR2RGB);
    cv::namedWindow("Bezier Curve", cv::WINDOW_AUTOSIZE);

    cv::setMouseCallback("Bezier Curve", mouse_handler, nullptr);

    int key = -1;
    while (key != 27) 
    {
        for (auto &point : control_points) 
        {
            cv::circle(window, point, 3, {255, 255, 255}, 3);
        }

        if (control_points.size() == 8) 
        {
            // naive_bezier(control_points, window);
            bezier(control_points, window);

            cv::imshow("Delaunay Triangulation", window);
            cv::imwrite("DelaunayTriangulation.png", window);
            key = cv::waitKey(0);

            return 0;
        }

        cv::imshow("Bezier Curve", window);
        key = cv::waitKey(20);
    }
  return 0;
}
