#include <SFML/Graphics.hpp>

int main() {
    // Crear una ventana de 800x600 píxeles
    sf::RenderWindow window(sf::VideoMode(800, 600), "Ventana de SFML");

    sf::RectangleShape rectangle(sf::Vector2f(500,100));
    rectangle.setFillColor(sf::Color::White);
    rectangle.setPosition(50, 60);

    // Configurar la figura, en este caso un círculo
    sf::CircleShape circle(50); // Crear un círculo de radio 50 píxeles
    circle.setFillColor(sf::Color::Green); // Color de relleno verde
    circle.setPosition(375, 275); // Posición en el centro de la ventana

    // Bucle principal
    while (window.isOpen()) {
        // Procesar eventos
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close(); // Cerrar la ventana al recibir el evento "cerrar"
            }
        }

        // Limpiar la ventana
        window.clear(sf::Color::Black);

        // Dibujar el círculo
        window.draw(circle);
        window.draw(rectangle);

        // Mostrar el contenido en pantalla
        window.display();
    }

    return 0;
}
