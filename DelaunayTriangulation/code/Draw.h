#ifndef DRAW_H
#define DRAW_H

#include "Vector.h"
#include "Triangle.h"
#include <opencv2/opencv.hpp>
#include <string>

class Screen
{
public:

    Screen() {
        height = 700, width = 700;
        window = cv::Mat(height, width, CV_8UC3, cv::Scalar(0));
        cv::cvtColor(window, window, cv::COLOR_BGR2RGB);
        cv::namedWindow("Default Window", cv::WINDOW_AUTOSIZE);
    }

    Screen(int _size, std::string _name = "Default Window")
        : height(_size), width(_size), windowName(_name) {
        window = cv::Mat(height, width, CV_8UC3, cv::Scalar(0));
        cv::cvtColor(window, window, cv::COLOR_BGR2RGB);
    }

    Screen(int _height, int _width, std::string _name = "Default Window")
        : height(_width), width(_height), windowName(_name) {
        window = cv::Mat(height, width, CV_8UC3, cv::Scalar(0));
        cv::cvtColor(window, window, cv::COLOR_BGR2RGB);
    }

    void screenShow() {
        int key = -1;
        while(key != 27) {
            cv::imshow(windowName, window);
            key = cv::waitKey(0);
        }
        
    }

    void imageWrite(std::string _name = "Default.png") {
        cv::imwrite(_name, window);
    }

    void setPixel(const float& x, const float& y, cv::Point3f color = cv::Point3f(255, 255, 255)) {
        if(x + 0.5 > width || x < 0)    return;
        if(y + 0.5 > height || y < 0)    return;
        window.at<cv::Vec3b>(height - y - 0.5, x + 0.5)[0] = color.x;
        window.at<cv::Vec3b>(height - y - 0.5, x + 0.5)[1] = color.y;
        window.at<cv::Vec3b>(height - y - 0.5, x + 0.5)[2] = color.z;
    }

    cv::Mat window;
    int height, width;
    std::string windowName;
};

cv::Point2f toPoint2f(const Vector2f& v) {
    return cv::Point2f(v.x, v.y);
}

void drawLine(const Vector2f& a, const Vector2f& b, Screen& scn) {
    float ax = a.x, ay = a.y, bx = b.x, by = b.y;
    for(float t = 0; t <= 1.0; t += 0.001)
        scn.setPixel(ax + t * (bx - ax), ay + t * (by - ay));
}

void drawPoint(const Vector2f& a, Screen& scn, int radius = 3) {
    float x = a.x, y = a.y;
    for(float t = 0; t < radius; t += 0.1) {
        for(float angle = 0; angle < 360; angle += 0.01)
            scn.setPixel(x + t * cos(angle * PI / 180.0f), y + t * sin(angle * PI / 180.0f));
    }
}

void drawTriangle(const Triangle& tri, Screen& scn) {
    drawPoint(tri.v0, scn);
    drawPoint(tri.v1, scn);
    drawPoint(tri.v2, scn);
    drawLine(tri.v0, tri.v1, scn);
    drawLine(tri.v1, tri.v2, scn);
    drawLine(tri.v2, tri.v0, scn);
}

#endif // DRAW_H