#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <cmath>
#include <iostream>
#include <vector>

using namespace sf;
using namespace std;

const float fixedTimeStep = 1.0f / 60.0f;

class Cell
{
public:
    int x, y;
    float vx, vy;
    Color color;
    Cell(int x, int y, Color color) : x(x), y(y), vx(0), vy(0), color() {}

    int getX() { return x; }
    int getY() { return y; }
    Color getColor() const { return color; }

    void setPosition(float x, float y)
    {
        this->x = x;
        this->y = y;
    }
};
/*
void rule(vector<Cell> &arr1, vector<Cell> &arr2, int g)
{
    for (size_t i = 0; i < arr1.size(); i++)
    {
        float fx = 0;
        float fy = 0;
        for (size_t j = 0; j < arr2.size(); j++)
        {
            if (i != j)
            {
                int dx = arr1[i].x - arr2[j].x;
                int dy = arr1[i].y - arr2[j].y;
                float dist = sqrt(dx * dx + dy * dy);
                if (dist > 0 and dist < 300)
                {
                    float F = -1.0f / dist * 0.01 * g;
                    fx += F * dx;
                    fy += F * dy;
                }
            }
        }
        arr1[i].vx += fx;
        arr1[i].vy += fy;

        if (arr1[i].x + arr1[i].vx > 780 or arr1[i].x + arr1[i].vx < 20)
        {
            arr1[i].x -= arr1[i].vx;
            arr1[i].vx *= -0.7;
        }
        else
        {
            arr1[i].x += arr1[i].vx;
        }
        if (arr1[i].y + arr1[i].vy > 780 or arr1[i].y + arr1[i].vy < 20)
        {
            arr1[i].y -= arr1[i].vy;
            arr1[i].vy *= -0.7;
        }
        else
        {
            arr1[i].y += arr1[i].vy;
        }
    }
}
*/
/*
vector<Cell> cellinit(int num, Color color, vector<Cell*>* target) {
    vector<Cell> cells;
    for (int i = 0; i < num; i++) {
        Cell newCell((rand() % 700) + 50, (rand() % 700) + 50, color);
        cells.push_back(newCell);
        Cell* cellPtr = &cells[i];
        target->push_back(cellPtr);
    }
    return cells;
}*/
void cellinit(int num, Color color, vector<Cell&> all, vector<Cell> &target)
{
    for (int i = 0; i < num; i++)
    {
        Cell newCell = Cell((rand() % 700) + 50, (rand() % 700) + 50, color);
        target.push_back(newCell);
        all.push_back(target.back());
    }
}

int main()
{
    srand(time(NULL));
    RenderWindow window(VideoMode(800, 800), "Game");
    window.setPosition(Vector2i(0, 0));

    vector<Cell&> allCells;
    vector<Cell> yellow;
    cellinit(5, Color::Yellow, allCells, yellow);


    Clock clock;
    float accumulator = 0.0f;

    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
        }

        // Calculate delta time
        float dt = clock.restart().asSeconds();
        accumulator += dt;

        // Update game logic at fixed time step
        while (accumulator >= fixedTimeStep)
        {
            //rule(yellow, yellow, 5);
            // rule(red,red,-2);
            accumulator -= fixedTimeStep;
        }

        // DRAW CELLS
        window.clear();
        // Vector2i windowPosition = window.getPosition();
        for (size_t i = 0; i < allCells.size(); i++)
        {
            RectangleShape rect(Vector2f(5, 5));
            rect.setPosition(allCells[i].x, allCells[i].y); // rect.setPosition(allCells[i]->getX() - windowPosition.x, allCells[i]->getY() - windowPosition.y);
            rect.setFillColor(Color::Yellow);
            window.draw(rect);
        }
        /*
        cout << yellow[4].x << "," << yellow[4].y << endl;
        cout << allCells[2] << endl;
        cout << &yellow[2] << endl;
        */
        window.display();
        
    }
    return 0;
}
