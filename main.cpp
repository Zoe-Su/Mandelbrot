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
  text.setCharacterSize(20);
  text.setPosition(10, 10);
  text.setFillColor(Color::White);

  while (window.isOpen())
  {
    Event event;
    while (window.pollEvent(event))
		{
      if (event.type == Event::Closed)
      {
        // Quit the program when the window is closed
				window.close();
      }
      else if (event.type == Event::MouseButtonPressed)
      {
        if (event.mouseButton.button == Mouse::Right)
        {
          plane.zoomOut();
          plane.setCenter(Mouse::getPosition(window));
          plane.setCalcState();
        }
        else if (event.mouseButton.button == Mouse::Left)
        {
          plane.zoomIn();
          plane.setCenter(Mouse::getPosition(window));
          plane.setCalcState();
        }
      }
      else if (event.type == Event::MouseMoved)
      {
        plane.setMouseLocation(Mouse::getPosition(window));
      }
      else if (event.type == Keyboard::isKeyPressed(Keyboard::Escape))
      {
        window.close();
      }
    }

    plane.updateRender();
    plane.loadText(text);

    window.clear();
    window.draw(plane);
    window.draw(text);
    window.display();
  }

  return 0;
}
