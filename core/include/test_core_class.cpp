#include "core_class.h"
#include <iostream>

int main()
{
    Block b{1,2};
    std::cout << b.row() << " + " << b.column() << "\n";
    b.row()=4;
    std::cout << b.row() << "\n";
    Grid board{5,6};
    bool check=board(1,2)==nullptr;
    std::cout << check << " and "<< board(1,2) << "\n";
    board(1,2)=&b;
    check=board(1,2)==nullptr;
    std::cout << check << " and " << board(1,2)->row() << "\n";
    std::cout << true <<"\n";
    std::vector<unsigned int> full_rows=board.get_full_rows();
    for(unsigned int i=0; i<full_rows.size(); ++i)
    {
        std::cout << full_rows[i] << "\n";
    }
    if(full_rows.size()==0) std::cout << "empty\n";
    return 0;
}