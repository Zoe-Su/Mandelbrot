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
    m_vArray.resize(pixelWidth* pixelHeight);
}

/****** Draw the array ******/
void ComplexPlane::draw(RenderTarget& target, RenderStates states) const
{
    target.draw(m_vArray);
}

void ComplexPlane::zoomIn()
{

}

void ComplexPlane::zoomOut()
{

}

void ComplexPlane::setCenter(Vector2i mousePixel)
{

}

void ComplexPlane::setMouseLocation(Vector2i mousePixel)
{

}

void ComplexPlane::loadText(Text& text)
{

}

void ComplexPlane::updateRender()
{

}

int ComplexPlane::countIterations(Vector2f coord)
{
    return 0;
}

void ComplexPlane::iterationsToRGB(size_t count, Uint8& r, Uint8& g, Uint8& b)
{

}

Vector2f ComplexPlane::mapPixelToCoords(Vector2i mousePixel)
{
    return m_plane_center;
}
