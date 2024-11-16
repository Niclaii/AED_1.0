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

// Clase Vector creada desde cero
class Vector {
public:
    Vector() : capacidad(10), tamanio(0) {
        elementos = new int[capacidad];
    }

    ~Vector() {
        delete[] elementos;
    }

    void add(int value) {
        if (tamanio == capacidad) {
            redimensionar();
        }
        elementos[tamanio] = value;
        tamanio++;
    }

    bool contains(int value) {
        for (int i = 0; i < tamanio; ++i) {
            if (elementos[i] == value) {
                return true;
            }
        }
        return false;
    }

    void clear() {
        tamanio = 0;
    }

private:
    int* elementos;
    int capacidad;
    int tamanio;

    void redimensionar() {
        capacidad *= 2;
        int* nuevosElementos = new int[capacidad];
        for (int i = 0; i < tamanio; ++i) {
            nuevosElementos[i] = elementos[i];
        }
        delete[] elementos;
        elementos = nuevosElementos;
    }
};

// Clase para manejar la visualización del árbol binario
class BinaryTreeVisualizer {
public:
    BinaryTreeVisualizer(TreeNode* raiz) : raiz(raiz) {
        if (!font.loadFromFile("arial.ttf")) {
            std::cerr << "No se pudo cargar la fuente 'arial.ttf'. Se usarán círculos sin texto.\n";
            fontCargado = false;
        }
        else {
            fontCargado = true;
        }
    }

    // Almacenar los tíos y primos del nodo objetivo (ajustado para considerar 13 y 18 como tíos)
    void almacenarTiosYPrimos(TreeNode* nodo, int objetivo, TreeNode* padre, TreeNode* abuelo, TreeNode* bisabuelo) {
        if (!nodo) return;

        // Si encontramos el nodo objetivo, buscamos sus tíos y primos
        if (nodo->valor == objetivo) {
            // Tíos (hermanos del padre)
            if (abuelo != nullptr) {
                if (abuelo->left && abuelo->left != padre) {
                    tios.add(abuelo->left->valor);
                    almacenarHijosComoPrimos(abuelo->left);
                }
                if (abuelo->right && abuelo->right != padre) {
                    tios.add(abuelo->right->valor);
                    almacenarHijosComoPrimos(abuelo->right);
                }
            }
            // Tíos adicionales (hijos de los hermanos del abuelo)
            if (bisabuelo != nullptr) {
                if (bisabuelo->left && bisabuelo->left != abuelo) {
                    TreeNode* hermanoAbuelo = bisabuelo->left;
                    if (hermanoAbuelo->left) {
                        tios.add(hermanoAbuelo->left->valor); // 13 como tío
                        almacenarHijosComoPrimos(hermanoAbuelo->left);
                    }
                    if (hermanoAbuelo->right) {
                        tios.add(hermanoAbuelo->right->valor); // 18 como tío
                        almacenarHijosComoPrimos(hermanoAbuelo->right);
                    }
                }
                if (bisabuelo->right && bisabuelo->right != abuelo) {
                    TreeNode* hermanoAbuelo = bisabuelo->right;
                    if (hermanoAbuelo->left) {
                        tios.add(hermanoAbuelo->left->valor);
                        almacenarHijosComoPrimos(hermanoAbuelo->left);
                    }
                    if (hermanoAbuelo->right) {
                        tios.add(hermanoAbuelo->right->valor);
                        almacenarHijosComoPrimos(hermanoAbuelo->right);
                    }
                }
            }
            return;
        }

        // Continuar recorriendo el árbol
        almacenarTiosYPrimos(nodo->left, objetivo, nodo, padre, abuelo);
        almacenarTiosYPrimos(nodo->right, objetivo, nodo, padre, abuelo);
    }

    // Almacena los hijos del nodo como primos
    void almacenarHijosComoPrimos(TreeNode* nodo) {
        if (!nodo) return;
        if (nodo->left) primos.add(nodo->left->valor);
        if (nodo->right) primos.add(nodo->right->valor);
    }

    // Dibuja el nodo con un color específico
    void dibujarNodo(sf::RenderWindow& window, float x, float y, sf::Color color, int valor) {
        sf::CircleShape circle(20);
        circle.setFillColor(color);
        circle.setOutlineColor(sf::Color::White);
        circle.setOutlineThickness(2);
        circle.setPosition(x, y);
        window.draw(circle);

        if (fontCargado) {
            sf::Text text(std::to_string(valor), font, 16);
            text.setFillColor(sf::Color::Black);
            sf::FloatRect textRect = text.getLocalBounds();
            text.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
            text.setPosition(x + circle.getRadius(), y + circle.getRadius());
            window.draw(text);
        }
    }

    // Dibuja los nodos utilizando los vectores de tíos y primos
    void dibujarNodos(TreeNode* nodo, sf::RenderWindow& window, float x, float y, float offsetX, float offsetY) {
        if (!nodo) return;

        if (nodo->valor == objetivo) {
            dibujarNodo(window, x, y, sf::Color::Red, nodo->valor); // Rojo para el nodo objetivo
        }
        else if (tios.contains(nodo->valor)) {
            dibujarNodo(window, x, y, sf::Color::Green, nodo->valor); // Verde para tíos
        }
        else if (primos.contains(nodo->valor)) {
            dibujarNodo(window, x, y, sf::Color::Yellow, nodo->valor); // Amarillo para primos
        }
        else {
            dibujarNodo(window, x, y, sf::Color::White, nodo->valor); // Blanco para nodos normales
        }

        if (nodo->left) {
            sf::Vertex line[] = { sf::Vertex(sf::Vector2f(x + 20, y + 20), sf::Color::White),
                                 sf::Vertex(sf::Vector2f(x - offsetX + 20, y + offsetY + 20), sf::Color::White) };
            window.draw(line, 2, sf::Lines);
            dibujarNodos(nodo->left, window, x - offsetX, y + offsetY, offsetX / 2, offsetY);
        }
        if (nodo->right) {
            sf::Vertex line[] = { sf::Vertex(sf::Vector2f(x + 20, y + 20), sf::Color::White),
                                 sf::Vertex(sf::Vector2f(x + offsetX + 20, y + offsetY + 20), sf::Color::White) };
            window.draw(line, 2, sf::Lines);
            dibujarNodos(nodo->right, window, x + offsetX, y + offsetY, offsetX / 2, offsetY);
        }
    }

    void display(sf::RenderWindow& window) {
        dibujarNodos(raiz, window, 400, 50, 150, 100);
    }

    void prepararDibujos(int objetivo) {
        this->objetivo = objetivo; // Guardar el nodo objetivo
        tios.clear(); // Limpiar el vector de tíos
        primos.clear(); // Limpiar el vector de primos
        almacenarTiosYPrimos(raiz, objetivo, nullptr, nullptr, nullptr);
    }

private:
    TreeNode* raiz;
    sf::Font font;
    bool fontCargado;
    int objetivo; // Nodo objetivo para resaltarlo

    Vector tios;
    Vector primos;
};

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Visualización del Árbol Binario");

    TreeNode* raiz = nullptr;
    int valores[] = { 10, 5, 15, 3, 7, 13, 18, 1, 4, 6, 8 ,11,19};
    int numnodos = sizeof(valores) / sizeof(valores[0]);

    for (int i = 0; i < numnodos; ++i) {
        raiz = insert(raiz, valores[i]);
    }

    BinaryTreeVisualizer visualizer(raiz);

    int objetivo = 1; // Nodo objetivo para encontrar los tíos y primos
    visualizer.prepararDibujos(objetivo);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        window.clear(sf::Color::Black);
        visualizer.display(window);
        window.display();
    }

    return 0;
}
