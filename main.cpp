#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <cmath>
#include <iostream>

using namespace sf;
using namespace std;

const float fixedTimeStep = 1.0f / 60.0f;
int cellc = 100;

class Cell {
public:
    int x, y;
    float vx,vy;
    Cell(int x, int y) : x(x), y(y), vx(), vy(){}

    void setPosition(float x, float y) { this->x = x; this->y = y; }
};

void rule(Cell** cellarray, int g) {
    for (int i = 0; i < cellc; i++) {
        float fx = 0;
        float fy = 0;
        for (int j = 0; j < cellc; j++) {
            if (i != j) {
                int dx = cellarray[i]->x - cellarray[j]->x;
                int dy = cellarray[i]->y - cellarray[j]->y;
                float dist = sqrt(dx * dx + dy * dy);
                if (dist > 0 and dist < 300) {
                    float F = -1.0f / dist * 0.01;
                    fx += F * dx;
                    fy += F * dy;
                }
            }
        }
        cellarray[i]->vx += fx;
        cellarray[i]->vy += fy;
    }
    for (int i = 0; i < cellc; i++) {
        if (cellarray[i]->x + cellarray[i]->vx > 780 or cellarray[i]->x + cellarray[i]->vx < 20) {
            cellarray[i]->x -= cellarray[i]->vx;
            cellarray[i]->vx *= -0.7;
        } else {
            cellarray[i]->x += cellarray[i]->vx;
        }
        if (cellarray[i]->y + cellarray[i]->vy > 780 or cellarray[i]->y + cellarray[i]->vy < 20) {
            cellarray[i]->y -= cellarray[i]->vy;
            cellarray[i]->vy *= -0.7;
        } else {
            cellarray[i]->y += cellarray[i]->vy;
        }
    }
}

int main() {
    srand(time(NULL));
    RenderWindow window(VideoMode(800, 800), "Life game");
    window.setPosition(Vector2i(0,0));

    Cell** cellarray;
    cellarray = new Cell * [cellc];
    for (int i = 0; i < cellc; i++) {
        cellarray[i] = new Cell(rand() % 701 + 50, rand() % 701 + 50);
    }

    // Timer for fixed time step
    Clock clock;
    float accumulator = 0.0f;

    // EXIT HANDLING
    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed)
                window.close();
        }

        // Calculate delta time
        float dt = clock.restart().asSeconds();
        accumulator += dt;

        // Update game logic at fixed time step
        while (accumulator >= fixedTimeStep) {
            rule(cellarray,5);
            accumulator -= fixedTimeStep;
       }

        // DRAW CELLS
        window.clear();
        Vector2i windowPosition = window.getPosition();
        for (int i = 0; i < cellc; i++) {
            RectangleShape rect(Vector2f(5, 5));
            rect.setPosition(cellarray[i]->x - windowPosition.x, cellarray[i]->y - windowPosition.y);
            rect.setFillColor(Color::Yellow);
            window.draw(rect);
        }
        window.display();
    }

    // Deallocate memory
    for (int i = 0; i < cellc; i++) {
        delete cellarray[i];
    }
    delete[] cellarray;

    return 0;
}
