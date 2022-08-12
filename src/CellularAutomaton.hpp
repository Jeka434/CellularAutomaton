#ifndef CELLULAR_AUTOMATON
#define CELLULAR_AUTOMATON 1

#include <vector>
using std::vector;
#include <string>
using std::string;

//Rules for automaton
#define RULE_S "2"
#define RULE_B "2"
#define RULE_C 25

const string rule_s = RULE_S;
const string rule_b = RULE_B;

enum CellState {
    dead, dying, alive
};

struct Cell {
    CellState state;
    unsigned int death_counter;
    Cell(CellState st = dead, unsigned int counter = RULE_C);
    void rise();
    void inc_counter();
};

class CellularAutomaton {
public:
    CellularAutomaton(const unsigned int rows, const unsigned int cols);
    void iterate();
    float get_color(unsigned int x, unsigned int y) const;
private:
    vector<vector<Cell> > world;
    void initialize(const unsigned int rows, const unsigned int cols);
    unsigned int neighbors(const unsigned int row, const unsigned int col) const;
};

#endif
