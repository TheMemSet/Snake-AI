#include "Grid.hpp"
#include <cstdlib>

Grid::Grid (uint8_t gridWidth_in, uint8_t gridHeight_in) : alive (true)
{
    gridHeight = gridHeight_in;
    gridWidth  = gridWidth_in;

    moves = 0;

    vertArray.setPrimitiveType (sf::Quads);

    srand (time (NULL));

    reset();
}

void Grid::draw (sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw (vertArray, states);
}

uint32_t Grid::getScore() const
{
    return score;
}

void Grid::terminate()
{
    alive = false;
}

bool Grid::isAlive() const
{
    return alive;
}

void Grid::reset()
{
    snake.clear();
    fruit.clear();
    alive = true;
    score = 0;
    moves = 0;

    for (uint8_t i = 0;i < 5;++i)
    {
        snake.push_back (Segment ((gridWidth / 2) - i, gridHeight / 2, right));
    }

    addFruit();
}

void Grid::updateSnake()
{
    if (!alive)
    {
        return;
    }

    std::vector <std::pair <int, int>> vectSnake, vectFruit;

    vectSnake.resize (snake.size());
    vectFruit.resize (fruit.size());

    for (int i = 0;i < snake.size();i++)
    {
        vectSnake [i] = std::make_pair ((int)snake [i].x, (int)snake [i].y);
    }

    for (int i = 0;i < fruit.size();i++)
    {
        vectFruit [i] = std::make_pair ((int)fruit [i].x, (int)fruit [i].y);
    }

    char dir = AIRijad.update (vectSnake, vectFruit);

    if (dir == 'U')
    {
        snake [0].next = up;
    }
    else if (dir == 'R')
    {
        snake [0].next = right;
    }
    else if (dir == 'D')
    {
        snake [0].next = down;
    }
    else if (dir == 'L')
    {
        snake [0].next = left;
    }

    snake [0].x += offX [snake [0].next];
    snake [0].y += offY [snake [0].next];

    if (fruitOnRemove (snake [snake.size() - 1]))
    {
        addSegment = true;
        newSegment = snake [snake.size() - 1];
    }
    else
    {
        addSegment = false;
    }


    for (uint16_t i = 1;i < snake.size();++i)
    {
        snake [i].x += offX [snake [i].next];
        snake [i].y += offY [snake [i].next];
    }

    for (uint16_t i = snake.size() - 1;i > 0;--i)
    {
        snake [i].next = snake [i - 1].next;
    }

    if (addSegment)
    {
        snake.push_back (newSegment);
    }

    if (fruitOn (snake [0]))
    {
        score++;
        addFruit();
    }

    moves++;

    alive = !testForCollision();

//    if (score >= 50)
//    {
//        alive = false;
//    }
}

bool Grid::testForCollision() const
{
    if ((snake [0].x < 0) || (snake [0].x >= gridWidth) || (snake [0].y < 0) || (snake [0].y >= gridHeight))
    {
        return true;
    }

    for (uint16_t i = 1;i < snake.size();++i)
    {
        if (snake [i] == snake [0])
        {
            return true;
        }
    }

    return false;
}

void Grid::updateVertexArray()
{
    if (!alive)
    {
        return;
    }

    vertArray.clear();

    for (uint16_t i = 0;i < fruit.size();++i)
    {
        fruit [i].x *= CELL_SIZE;
        fruit [i].y *= CELL_SIZE;

        vertArray.append (sf::Vertex (sf::Vector2f (fruit [i].x, fruit [i].y),
        fruitColor));

        vertArray.append (sf::Vertex (sf::Vector2f (fruit [i].x + (CELL_SIZE - GRID_GAP), fruit [i].y),
        fruitColor));

        vertArray.append (sf::Vertex (sf::Vector2f (fruit [i].x + (CELL_SIZE - GRID_GAP), fruit [i].y + (CELL_SIZE - GRID_GAP)),
        fruitColor));

        vertArray.append (sf::Vertex (sf::Vector2f (fruit [i].x, fruit [i].y + (CELL_SIZE - GRID_GAP)),
        fruitColor));

        fruit [i].x /= CELL_SIZE;
        fruit [i].y /= CELL_SIZE;
    }

    for (uint16_t i = 0;i < snake.size();++i)
    {
        snake [i].x *= CELL_SIZE;
        snake [i].y *= CELL_SIZE;

        vertArray.append (sf::Vertex (sf::Vector2f (snake [i].x, snake [i].y),
        (!i) ? headColor : bodyColor));

        vertArray.append (sf::Vertex (sf::Vector2f (snake [i].x + (CELL_SIZE - GRID_GAP), snake [i].y),
        (!i) ? headColor : bodyColor));

        vertArray.append (sf::Vertex (sf::Vector2f (snake [i].x + (CELL_SIZE - GRID_GAP), snake [i].y + (CELL_SIZE - GRID_GAP)),
        (!i) ? headColor : bodyColor));

        vertArray.append (sf::Vertex (sf::Vector2f (snake [i].x, snake [i].y + (CELL_SIZE - GRID_GAP)),
        (!i) ? headColor : bodyColor));

        snake [i].x /= CELL_SIZE;
        snake [i].y /= CELL_SIZE;
    }
}

bool Grid::fruitOn (Segment seg) const
{
    for (uint16_t i = 0;i < fruit.size();++i)
    {
        if (fruit [i] == seg) return true;
    }

    return false;
}

bool Grid::fruitOnRemove (Segment seg)
{
    for (uint16_t i = 0;i < fruit.size();++i)
    {
        if (fruit [i] == seg)
        {
            fruit.erase (fruit.begin() + i);
            return true;
        }
    }

    return false;
}

void Grid::inputKey (char key)
{

}

void Grid::addFruit()
{
    if (((gridHeight * gridWidth) - snake.size() - 1) <= 0)
    {
        return;
    }

    uint32_t nextFruitCell = (rand() % ((gridHeight * gridWidth) - snake.size())) + 1;

    for (uint16_t xx = 0;xx < gridWidth;++xx)
    {
        for (uint16_t yy = 0;yy < gridHeight;++yy)
        {
            if (!(fruitOn (Segment (xx, yy)) || snakeOn (Segment (xx, yy))))
            {
                nextFruitCell--;

                if (!nextFruitCell)
                {
                    fruit.push_back (Segment (xx, yy));
                    return;
                }
            }
        }
    }
}

bool Grid::snakeOn (Segment seg) const
{
    for (uint32_t i = 0;i < snake.size();++i)
    {
        if (snake [i] == seg) return true;
    }

    return false;
}
