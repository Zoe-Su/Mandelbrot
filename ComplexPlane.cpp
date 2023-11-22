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

/****** Set center in complex plane ******/
void ComplexPlane::setCenter(Vector2i mousePixel)
{
    m_plane_center = mapPixelToCoords(mousePixel);

    m_state = State::CALCULATING;
}

/****** Set mouse location in complex plane ******/
void ComplexPlane::setMouseLocation(Vector2i mousePixel)
{
    m_mouseLocation = mapPixelToCoords(mousePixel);
}

/****** Display text ******/
void ComplexPlane::loadText(Text& text)
{
    stringstream strm;

    strm << "Mandelbrot Set" << endl;
    strm << "Center: (" << m_plane_center.x << ", " << m_plane_center.y << ")" << endl;
    strm << "Cursor: (" << m_mouseLocation.x << ", " << m_mouseLocation.y << ")" << endl;
    strm << "Left-click to zoom in" << endl;
    strm << "Right-click to zoom out" << endl;

    text.setString(strm.str());
}

// Updates screen
void ComplexPlane::updateRender()
{
    if (m_state == State::CALCULATING)
    {
        for (int j = 0; j < m_pixel_size.x; j++)
        {
            for (int i = 0; i < m_pixel_size.y; i++)
            {
                m_vArray[i * m_pixel_size.x + j].position = { float(j), float(i)};

                Vector2f coords = mapPixelToCoords(Vector2i(j, i));

                int iterations = countIterations(coords);

                Uint8 r, g, b;
                iterationsToRGB(iterations, r, g, b);

                m_vArray[j + i * m_pixel_size.x].color = {r, g, b};
            }
        }

        m_state = State::DISPLAYING;
    }
}

/****** Counts number of iterations ******/
int ComplexPlane::countIterations(Vector2f coord)
{
    double real = coord.x;
    double imaginary = coord.y;

    int iterations = 0;
    complex<double> c(real, imaginary);
    complex<double> z(0.0, 0.0);

    while (iterations < MAX_ITER)
    {
        z = z * z + c;
        
        if (abs(z) > 2.0)
        {
            break;
        }

        iterations++;
    }

    return iterations;
}

/****** Makes it colorful! ******/
void ComplexPlane::iterationsToRGB(size_t count, Uint8& r, Uint8& g, Uint8& b)
{
    if (count == MAX_ITER)
    {
        r = 0;
        g = 0;
        b = 0;
    }
    else
    {
        size_t area = count / (MAX_ITER / 5);

        Uint8 colors[5][3] = 
        {
            {18, 3, 72},     
            {58, 32, 129},
            {46, 44, 154},
            {238, 200, 237},
            {231, 228, 249}
        };

        r = colors[area][0] + count;
        g = colors[area][1] + count;
        b = colors[area][2] + count;
    }
}

/****** Maps pixels to complex plane ******/
Vector2f ComplexPlane::mapPixelToCoords(Vector2i mousePixel)
{
    Vector2f coord;
    coord.x = ((mousePixel.x / float(m_pixel_size.x)) * m_plane_size.x) + (m_plane_center.x - m_plane_size.x / 2.0);
    coord.y = ((mousePixel.y / float(m_pixel_size.y)) * m_plane_size.y) + (m_plane_center.y - m_plane_size.y / 2.0);

    return coord;
}
