#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <cmath>

using namespace sf;

// Constants for fixed time step
const float fixedTimeStep = 1.0f / 60.0f; // Time step for 60 FPS

int main() {
    srand(time(NULL));
    RenderWindow window(VideoMode(800, 800), "Life game");

    // CELL DECLARATION
    class Cell {
    public:
        int x, y, vx, vy;
        Cell(int x, int y) : x(x), y(y), vx(3), vy(3) {}

        void setPosition(float x, float y) { this->x = x; this->y = y; }
    };
    // CELL INITIALIZATION
    Cell** cellarray;
    cellarray = new Cell * [10];
    for (int i = 0; i < 10; i++) {
        cellarray[i] = new Cell(rand() % 701 + 50, rand() % 701 + 50);
    }

    // Timer for fixed time step
    Clock clock;
    float accumulator = 0.0f;

    // EXIT HANDLING
    while (window.isOpen()) {
        // Poll events
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
            // MOVE CELLS
            for (int i = 0; i < 10; i++) {
                float fx=0;
                float fy=0;
                for (int j = 0; j < 10; j++) {
                    if (i != j) {
                        int dx = cellarray[j]->x - cellarray[i]->x;
                        int dy = cellarray[j]->y - cellarray[i]->y;
                        float dist = sqrt(dx * dx + dy * dy);
                        if (dist > 0 and dist < 400) {
                            float F = -1.0f / dist;
                            fx += F * dx;
                            fy += F * dy;
                        }
                        cellarray[j]->vx += static_cast<int>(fx);
                        cellarray[j]->vy += static_cast<int>(fy);
                    }
                }
            }

            for (int i = 0; i < 10; i++) {
                if (cellarray[i]->x + cellarray[i]->vx > 780 or cellarray[i]->x + cellarray[i]->vx < 20){
                    cellarray[i]->x -= cellarray[i]->vx;
                    cellarray[i]->vx = cellarray[i]->vx*0.8;
                }else{
                    cellarray[i]->x += cellarray[i]->vx;
                }
                if (cellarray[i]->y + cellarray[i]->vy > 780 or cellarray[i]->y + cellarray[i]->vy < 20){
                    cellarray[i]->y -= cellarray[i]->vy;
                    cellarray[i]->vy = cellarray[i]->vy*0.8;

                }else{
                    cellarray[i]->y += cellarray[i]->vy;
                }
            } 
            accumulator -= fixedTimeStep;
        }

        // DRAW CELLS
        window.clear();
        for (int i = 0; i < 10; i++) {
            RectangleShape rect(Vector2f(5, 5));
            rect.setPosition(cellarray[i]->x, cellarray[i]->y);
            rect.setFillColor(Color::Yellow);
            window.draw(rect);
        }
        window.display();
    }

    // Deallocate memory
    for (int i = 0; i < 10; i++) {
        delete cellarray[i];
    }
    delete[] cellarray;

    return 0;
}
