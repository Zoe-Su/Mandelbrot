// Include header file
#include "ComplexPlane.h"

/****** ComplexPlane Constructor ******/
ComplexPlane::ComplexPlane(int pixelWidth, int pixelHeight)
{
    m_pixel_size.x = pixelWidth;
    m_pixel_size.y = pixelHeight;

    m_aspectRatio = float(pixelHeight) / float(pixelWidth);

    m_plane_center.x = 0;
    m_plane_center.y = 0;

    m_plane_size.x = BASE_WIDTH;
    m_plane_size.y = BASE_HEIGHT * m_aspectRatio;

    m_zoomCount = 0;

    m_state = State::CALCULATING;

    m_vArray.setPrimitiveType(Points);
    m_vArray.resize(pixelWidth * pixelHeight);
}

/****** Draw the array ******/
void ComplexPlane::draw(RenderTarget& target, RenderStates states) const
{
    target.draw(m_vArray);
}

/****** Zoom In ******/
void ComplexPlane::zoomIn()
{
    m_zoomCount++;

    Vector2f size;
    size.x = BASE_WIDTH * pow(BASE_ZOOM, m_zoomCount);
    size.y = BASE_HEIGHT * m_aspectRatio * pow(BASE_ZOOM, m_zoomCount);

    m_plane_size.x = size.x;
    m_plane_size.y = size.y;

    m_state = State::CALCULATING;
}

/****** Zoom Out ******/
void ComplexPlane::zoomOut()
{
    m_zoomCount--;

    Vector2f size;
    size.x = BASE_WIDTH * pow(BASE_ZOOM, m_zoomCount);
    size.y = BASE_HEIGHT * m_aspectRatio * pow(BASE_ZOOM, m_zoomCount);

    m_plane_size.x = size.x;
    m_plane_size.y = size.y;

    m_state = State::CALCULATING;
}

// Come back to this later, uses other functions
void ComplexPlane::setCenter(Vector2i mousePixel)
{

}

// Come back to this later, uses other functions
void ComplexPlane::setMouseLocation(Vector2i mousePixel)
{

}

void ComplexPlane::loadText(Text& text)
{
    stringstream strm;
    string title, rightClick, leftClick;
    // Might be wrong, check after completing main
    strm << "Mandelbrot Set" << ' ' << m_plane_center << ' ' << m_mouseLocation << ' ' << "Left Click to Zoom in" << ' ' << "Right Click to Zoom Out";
    strm >> title >> m_plane_center >> leftClick >> rightClick;
    
    cout << title << endl;
    cout << "Center: (" << m_plane_center.x << ", " << m_plane_center.y << ")" << endl;
    cout << "Cursor: (" << m_mouseLocation.x << ", " << m_mouseLocation.y << ")" << endl;
    cout << leftClick << endl;
    cout << rightClick << endl;
}

// Come back to this later, uses other functions
void ComplexPlane::updateRender()
{
    if (m_state == State::CALCULATING)
    {
        for (int j = 0; j < m_pixel_size.x; j++)
        {
            for (int i = 0; i < m_pixel_size.y; i++)
            {
                m_vArray[i * m_pixel_size.x + j].position = { float(j), float(i)};
            }
        }
    }
}

// Come back to this later
int ComplexPlane::countIterations(Vector2f coord)
{
    return 0;
}

void ComplexPlane::iterationsToRGB(size_t count, Uint8& r, Uint8& g, Uint8& b)
{
    
}

Vector2f ComplexPlane::mapPixelToCoords(Vector2i mousePixel)
{
    // Random return value
    return m_plane_center;
}
