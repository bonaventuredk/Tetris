#include "core_class.h"
#include <iostream>

int main()
{
    Block b{1,2};
    std::cout << b.row() << " + " << b.column() << "\n";
    b.row()=4;
    std::cout << b.row() << "\n";
    Grid board{5,6};
    std::cout << board(1,2).row() << "\n";
    board(1,2).row()=12;
    std::cout << board(1,2).row() << "\n";
    return 0;
}