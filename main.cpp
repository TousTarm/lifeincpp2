#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Color.hpp>
#include <cstdlib>
#include <cmath>
#include <iostream>
#include <vector>

using namespace sf;
using namespace std;

const float fixedTimeStep = 1.0f / 60.0f;

class Cell {
public:
    int x, y;
    float vx, vy;
    Color color;
    int group;
    sf::RectangleShape shape;

    Cell(int x, int y, Color color,int group) : x(x), y(y), vx(0), vy(0), color(color), group(group) {
        shape.setSize(sf::Vector2f(5, 5));
        shape.setPosition(sf::Vector2f(x, y));
        shape.setFillColor(color);
    }

    void setPosition(float x, float y) {
        this->x = x;
        this->y = y;
        shape.setPosition(Vector2f(x, y));
    }
};

void cellinit(int num,Color color, vector<Cell>& all,int group){
    for (int i = 0;i<num;i++){
        Cell newCell = Cell((rand() % 700) + 50, (rand() % 700) + 50, color, group);
        all.push_back(newCell);
    }
}

void rule(Cell cell1, Cell cell2, int test1, int test2, int g, float dist,float& F){
    if(cell1.group == test1 and cell2.group == test2){
        F = -1.0f / dist * 0.01 * g;
    }
}

void gravity(vector<Cell>& cells) {
    for (size_t i = 0; i < cells.size(); i++) {
        float fx = 0;
        float fy = 0;
        for (size_t j = 0; j < cells.size(); j++) {
            if (i != j) {
                int dx = cells[i].x - cells[j].x;
                int dy = cells[i].y - cells[j].y;
                float dist = sqrt(dx * dx + dy * dy);
                if (dist > 0 and dist < 300) {
                    float F = 0.0f;

                    rule(cells[i],cells[j],1,1,5,dist,F);
                    rule(cells[i],cells[j],2,2,10,dist,F);
                    rule(cells[i],cells[j],1,2,-5,dist,F);
                    rule(cells[i],cells[j],2,1,5,dist,F);

                    fx += F * dx;
                    fy += F * dy;
                }
            }
        }
        cells[i].vx += fx;
        cells[i].vy += fy;
    }
    for (size_t i = 0; i < cells.size(); i++) {
        if (cells[i].x + cells[i].vx > 780 or cells[i].x + cells[i].vx < 20) {
            cells[i].x -= cells[i].vx;
            cells[i].vx *= -0.7;
        } else {
            cells[i].x += cells[i].vx;
        }
        if (cells[i].y + cells[i].vy > 780 or cells[i].y + cells[i].vy < 20) {
            cells[i].y -= cells[i].vy;
            cells[i].vy *= -0.7;
        } else {
            cells[i].y += cells[i].vy;
        }
        cells[i].setPosition(cells[i].x,cells[i].y);
    }
}

int main()
{
    srand(time(NULL));
    RenderWindow window(VideoMode(800, 800), "Game");
    window.setPosition(Vector2i(0, 0));

    vector<Cell> cells;
    cellinit(40,Color::Yellow,cells,1);
    cellinit(20,Color::Red,cells,2);

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
            gravity(cells);
            accumulator -= fixedTimeStep;
        }

        window.clear();
        for (const auto& cell : cells)
        {
            window.draw(cell.shape);
        }
        window.display();
    }
    return 0;
}