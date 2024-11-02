#include <SFML/Graphics.hpp>
#include <iostream>

struct TreeNode {
    int valor;
    TreeNode* left;
    TreeNode* right;

    TreeNode(int val) : valor(val), left(nullptr), right(nullptr) {}
};

// Función para insertar nodos en el árbol binario de búsqueda
TreeNode* insert(TreeNode* nodo, int valor) {
    if (nodo == nullptr) {
        return new TreeNode(valor);
    }
    if (valor < nodo->valor) {
        nodo->left = insert(nodo->left, valor);
    }
    else {
        nodo->right = insert(nodo->right, valor);
    }
    return nodo;
}

// Clase para manejar la visualización del árbol binario
class BinaryTreeVisualizer {
public:
    BinaryTreeVisualizer(TreeNode* raiz) : raiz(raiz) {
        if (!font.loadFromFile("arial.ttf")) {
            std::cerr << "No se pudo cargar la fuente 'arial.ttf'. Se usarán círculos sin texto.\n";
            fontcargado = false;
        }
        else {
            fontcargado = true;
        }
    }

    void draw(sf::RenderWindow& window, TreeNode* nodo, float x, float y, float offsetX, float offsetY) {
        if (!nodo) return;

        // Dibujar el nodo
        sf::CircleShape circle(20);
        circle.setFillColor(sf::Color::Green);
        circle.setOutlineColor(sf::Color::White);
        circle.setOutlineThickness(2);
        circle.setPosition(x, y);

        // Dibujar el texto dentro del círculo si la fuente se cargó
        if (fontcargado) {
            sf::Text text(std::to_string(nodo->valor), font, 16);
            text.setFillColor(sf::Color::Black);

            // Centramos el texto en el círculo
            sf::FloatRect textRect = text.getLocalBounds();
            text.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
            text.setPosition(x + circle.getRadius(), y + circle.getRadius());

            window.draw(circle);
            window.draw(text);
        }
        else {
            // Dibujar solo el círculo si no hay fuente
            window.draw(circle);
        }

        // Dibujar la línea hacia el nodo izquierdo
        if (nodo->left) {
            sf::Vertex line[] = {
                sf::Vertex(sf::Vector2f(x + 20, y + 20), sf::Color::White),
                sf::Vertex(sf::Vector2f(x - offsetX + 20, y + offsetY + 20), sf::Color::White)
            };
            window.draw(line, 2, sf::Lines);
            draw(window, nodo->left, x - offsetX, y + offsetY, offsetX / 2, offsetY);
        }

        // Dibujar la línea hacia el nodo derecho
        if (nodo->right) {
            sf::Vertex line[] = {
                sf::Vertex(sf::Vector2f(x + 20, y + 20), sf::Color::White),
                sf::Vertex(sf::Vector2f(x + offsetX + 20, y + offsetY + 20), sf::Color::White)
            };
            window.draw(line, 2, sf::Lines);
            draw(window, nodo->right, x + offsetX, y + offsetY, offsetX / 2, offsetY);
        }
    }

    void display(sf::RenderWindow& window) {
        draw(window, raiz, 400, 50, 150, 100);
    }

private:
    TreeNode* raiz;
    sf::Font font;
    bool fontcargado;
};

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Binary Tree Visualization");

    TreeNode* raiz = nullptr;

    // Valores predefinidos para el árbol
    int valores[] = { 10, 5, 15, 3, 7, 13, 18, 1, 4, 6, 8 };
    int numnodos = sizeof(valores) / sizeof(valores[0]);

    // Insertar cada valor en el árbol
    for (int i = 0; i < numnodos; ++i) {
        raiz = insert(raiz, valores[i]);
    }

    BinaryTreeVisualizer visualizer(raiz);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        // Limpiar la ventana y dibujar el árbol
        window.clear(sf::Color::Black);
        visualizer.display(window);
        window.display();
    }

    return 0;
}
