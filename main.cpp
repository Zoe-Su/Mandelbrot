#include "ComplexPlane.h"

int main()
{
  // Get desktop resolution; DIVIDING IT BY 2 RN TO MAKE IT RUN FASTER
  VideoMode vm(VideoMode::getDesktopMode().width / 2, VideoMode::getDesktopMode().height / 2);

  RenderWindow window(vm, "Mandelbrot", Style::Default);

  ComplexPlane plane(VideoMode::getDesktopMode().width / 2, VideoMode::getDesktopMode().height / 2);

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
