#include <SFML/Graphics.hpp>
#include <iostream>

struct TreeNode {
    int value;
    TreeNode* left;
    TreeNode* right;

    TreeNode(int val) : value(val), left(nullptr), right(nullptr) {}
};

// Función para insertar nodos en el árbol binario de búsqueda
TreeNode* insert(TreeNode* node, int value) {
    if (node == nullptr) {
        return new TreeNode(value);
    }
    if (value < node->value) {
        node->left = insert(node->left, value);
    }
    else {
        node->right = insert(node->right, value);
    }
    return node;
}

// Clase para manejar la visualización del árbol binario
class BinaryTreeVisualizer {
public:
    BinaryTreeVisualizer(TreeNode* root) : root(root) {
        if (!font.loadFromFile("arial.ttf")) {
            std::cerr << "No se pudo cargar la fuente 'arial.ttf'. Se usarán círculos sin texto.\n";
            fontLoaded = false;
        }
        else {
            fontLoaded = true;
        }
    }

    void draw(sf::RenderWindow& window, TreeNode* node, float x, float y, float offsetX, float offsetY) {
        if (!node) return;

        // Dibujar el nodo
        sf::CircleShape circle(20);
        circle.setFillColor(sf::Color::Green);
        circle.setOutlineColor(sf::Color::White);
        circle.setOutlineThickness(2);
        circle.setPosition(x, y);

        // Dibujar el texto dentro del círculo si la fuente se cargó
        if (fontLoaded) {
            sf::Text text(std::to_string(node->value), font, 16);
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
        if (node->left) {
            sf::Vertex line[] = {
                sf::Vertex(sf::Vector2f(x + 20, y + 20), sf::Color::White),
                sf::Vertex(sf::Vector2f(x - offsetX + 20, y + offsetY + 20), sf::Color::White)
            };
            window.draw(line, 2, sf::Lines);
            draw(window, node->left, x - offsetX, y + offsetY, offsetX / 2, offsetY);
        }

        // Dibujar la línea hacia el nodo derecho
        if (node->right) {
            sf::Vertex line[] = {
                sf::Vertex(sf::Vector2f(x + 20, y + 20), sf::Color::White),
                sf::Vertex(sf::Vector2f(x + offsetX + 20, y + offsetY + 20), sf::Color::White)
            };
            window.draw(line, 2, sf::Lines);
            draw(window, node->right, x + offsetX, y + offsetY, offsetX / 2, offsetY);
        }
    }

    void display(sf::RenderWindow& window) {
        draw(window, root, 400, 50, 150, 100);
    }

private:
    TreeNode* root;
    sf::Font font;
    bool fontLoaded;
};

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Binary Tree Visualization");

    TreeNode* root = nullptr;

    // Valores predefinidos para el árbol
    int values[] = { 10, 5, 15, 3, 7, 13, 18, 1, 4, 6, 8 };
    int numNodes = sizeof(values) / sizeof(values[0]);

    // Insertar cada valor en el árbol
    for (int i = 0; i < numNodes; ++i) {
        root = insert(root, values[i]);
    }

    BinaryTreeVisualizer visualizer(root);

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
