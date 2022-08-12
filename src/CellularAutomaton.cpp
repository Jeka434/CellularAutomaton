#include "CellularAutomaton.hpp"
#include <iostream>

Cell::Cell(CellState st, unsigned int counter) {
    state = st;
    death_counter = counter;
}

void Cell::rise() {
    state = alive;
    death_counter = 0;
}

void Cell::inc_counter() {
    switch (state) {
        case dead: return;
        case alive: state = dying;
        case dying: {
            death_counter++;
            if (death_counter >= RULE_C) {
                state = dead;
            }
        }
    }
}

float CellularAutomaton::get_color(unsigned int x, unsigned int y) const {
    return (float)(RULE_C - world[x][y].death_counter) / RULE_C;
}

void CellularAutomaton::initialize(const unsigned int rows, const unsigned int cols) {

    world.resize(rows);
    for (unsigned int r = 0; r < rows; r++) {
        world[r].resize(cols);
    }

    world[rows/2][cols/2].rise();
    world[rows/2-1][cols/2].rise();
    world[rows/2][cols/2-1].rise();

    world[rows/3][cols/3].rise();
    world[rows/3-1][cols/3].rise();
    world[rows/3][cols/3-1].rise();
    world[211][179].rise();
    world[211-1][179].rise();
    world[211][179-1].rise();
}

CellularAutomaton::CellularAutomaton(const unsigned int rows, const unsigned int cols) {
    initialize(rows, cols);
}

unsigned int CellularAutomaton::neighbors(const unsigned int row, const unsigned int col) const {
    unsigned int rows = world.size();
    unsigned int cols = 0;
    if (rows != 0) cols = world[0].size();
    unsigned int count = 0;
    bool top = row <= 0;
    bool bottom = row >= (rows - 1);
    bool left = col <= 0;
    bool right = col >= (cols - 1);

    if (!left && world[row][col - 1].state == alive)
        ++count;
    if (!right && world[row][col + 1].state == alive)
        ++count;

    if (!top) {
        if (world[row - 1][col].state == alive)
            ++count;
        if (!left && world[row - 1][col - 1].state == alive)
            ++count;
        if (!right && world[row - 1][col + 1].state == alive)
            ++count;
    }

    if (!bottom) {
        if (world[row + 1][col].state == alive)
            ++count;
        if (!left && world[row + 1][col - 1].state == alive)
            ++count;
        if (!right && world[row + 1][col + 1].state == alive)
            ++count;
    }

    return count;
}

void CellularAutomaton::iterate() {

    unsigned int rows = world.size();
    unsigned int cols = 0;
    if (rows != 0) {
        cols = world[0].size();
    }

    vector<vector<Cell> > new_world(world);

    for (unsigned int r = 0; r < rows; r++) {
        for (unsigned int c = 0; c < cols; c++) {

            unsigned int count = neighbors(r, c);

            if (rule_s.find('0' + count) == std::string::npos) {
                new_world[r][c].inc_counter();
            }

            if (world[r][c].state == dead && rule_b.find('0' + count) != std::string::npos) {
                new_world[r][c].rise();
            }

        }
    }

    world = new_world;
}
