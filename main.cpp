#include "ComplexPlane.h"

int main()
{
  // Get desktop resolution; DIVIDING IT BY 2 RN TO MAKE IT RUN FASTER
  int desktopWidth = VideoMode::getDesktopMode().width / 2;
  int desktopHeight = VideoMode::getDesktopMode().height / 2;

  RenderWindow window(VideoMode(desktopWidth, desktopHeight), "Mandelbrot", Style::Default);

  ComplexPlane plane(desktopWidth, desktopHeight);

  Font font;
  if (!font.loadFromFile("arial.ttf"))
  {
    cout << "Error loading font";
  }

  Text text;
  text.setFont(font);

  plane.loadText(text);

  while (window.isOpen())
  {
    Event event;
    while (window.pollEvent(event))
		{
      if (event.type == Event::Closed)
      {
        // Quit the game when the window is closed
				window.close();
      }
    }
  }
}
