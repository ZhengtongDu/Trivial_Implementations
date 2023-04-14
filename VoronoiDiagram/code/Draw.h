#ifndef DRAW_H
#define DRAW_H

#include "Vector.h"
#include "Triangle.h"
#include "GLOBAL.h"
#include <opencv2/opencv.hpp>
#include <string>

/**
 * @brief A class that represents a 2D screen to draw on
 */
class Screen
{
public:
    /**
     * @brief Constructs a default Screen object with size 700x700
     */
    Screen() {
        height = 700, width = 700;
        window = cv::Mat(height, width, CV_8UC3, cv::Scalar(0));
        cv::cvtColor(window, window, cv::COLOR_BGR2RGB);
        cv::namedWindow("Default Window", cv::WINDOW_AUTOSIZE);
    }

    /**
     * @brief Constructs a Screen object with specified size and name
     * @param _size The size of the screen (both height and width)
     * @param _name The name of the screen window
     */
    Screen(int _size, std::string _name = "Default Window")
        : height(_size), width(_size), windowName(_name) {
        window = cv::Mat(height, width, CV_8UC3, cv::Scalar(0));
        cv::cvtColor(window, window, cv::COLOR_BGR2RGB);
        cv::namedWindow(_name, cv::WINDOW_AUTOSIZE);
    }

    /**
     * @brief Constructs a Screen object with specified height, width, and name
     * @param _height The height of the screen
     * @param _width The width of the screen
     * @param _name The name of the screen window
     */
    Screen(int _height, int _width, std::string _name = "Default Window")
        : height(_width), width(_height), windowName(_name) {
        window = cv::Mat(height, width, CV_8UC3, cv::Scalar(0));
        cv::cvtColor(window, window, cv::COLOR_BGR2RGB);
        cv::namedWindow(_name, cv::WINDOW_AUTOSIZE);
    }

    /**
     * @brief Displays the screen window and waits for a key event
     */
    void screenShow() {
        int key = -1;
        while(key != 27) {
            cv::imshow(windowName, window);
            key = cv::waitKey(0);
        }
    }

    /**
     * @brief Writes the screen as an image with specified name
     * @param _name The name of the image file to write
     */
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