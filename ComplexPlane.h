#ifndef COMPLEXPLANE_H
#define COMPLEXPLANE_H

// C++ Libraries
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <sstream>
#include <vector>
#include <cmath>
#include <complex>

// Makes code easier to write
using namespace sf;
using namespace std;

// Global constants
const unsigned int MAX_ITER = 64;
const float BASE_WIDTH = 4.0;
const float BASE_HEIGHT = 4.0;
const float BASE_ZOOM = 0.5;

// Declaration of state class
enum class State
{
    CALCULATING, DISPLAYING
};

// Declaration of ComplexPlane class
class ComplexPlane : public Drawable
{
    public:
        ComplexPlane(int pixelWidth, int pixelHeight);
        void draw(RenderTarget& target, RenderStates states) const;
        void zoomIn();
        void zoomOut();
        void setCenter(Vector2i mousePixel);
        void setMouseLocation(Vector2i mousePixel);
        void loadText(Text& text);
        void updateRender();
        void setCalcState();

    private:
        VertexArray m_vArray;
        State m_state;
        Vector2f m_mouseLocation;
        Vector2i m_pixel_size;
        Vector2f m_plane_center;
        Vector2f m_plane_size;
        int m_zoomCount;
        float m_aspectRatio;

        int countIterations(Vector2f coord);
        void iterationsToRGB(size_t count, Uint8& r, Uint8& g, Uint8& b);
        Vector2f mapPixelToCoords(Vector2i mousePixel);
};

#endif

