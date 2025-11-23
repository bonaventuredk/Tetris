// Class design propasal for the core part of the game 

#ifndef CORE_CLASS
#define CORE_CLASS

class Grid
{
    //abstract grid class
    virtual void abstract_method() =0 ;
};

class GameGrid : public Grid
{
    // contain a grid filled boolean to represent the state of a given game 
    // Which container to emulate a matrix ? 
};

class BlockGrid : public Grid 
{
    // contain a grid filled boolean to represent the default configuration of a block
};


class Block
{
    //abstract grid class
    virtual void abstract_method() =0 ;
};

class L_Block : public Block 
{
    // contain BlockGrid representing the L configuration by default
    // a rotation state (int beetween 0 and 2 mod 3) to register if the block 
    // has been applied 90 degree rotations. 0 corresponding to the default
    // configuration, 1 after one direct rotation of the default state
    //, 2 after two direct rotations, and 3 after two direct rotations

};

class J_block : public Block 
{
    // contain BlockGrid representing the J (or reversed L) configuration by default
    // a rotation state (int beetween 0 and 2 mod 3) to register if the block 
    // has been applied 90 degree rotations. 0 corresponding to the default
    // configuration, 1 after one direct rotation of the default state
    //, 2 after two direct rotations, and 3 after two direct rotations
};

class Z_Block : public Block 
{
    // contain BlockGrid representing the Z configuration by default
    // a rotation state (int beetween 0 and 2 mod 3) to register if the block 
    // has been applied 90 degree rotations. 0 corresponding to the default
    // configuration, 1 after one direct rotation of the default state
    //, 2 after two direct rotations, and 3 after two direct rotations
};

class S_Block : public Block 
{
    // contain BlockGrid representing the S ( or reversed-Z ) configuration by default
    // a rotation state (int beetween 0 and 2 mod 3) to register if the block 
    // has been applied 90 degree rotations. 0 corresponding to the default
    // configuration, 1 after one direct rotation of the default state
    //, 2 after two direct rotations, and 3 after two direct rotations
};

class I_Block : public Block {
    // contain BlockGrid representing the I-configuration by default
    // a rotation state (int beetween 0 and 2 mod 3) to register if the block 
    // has been applied 90 degree rotations. 0 corresponding to the default
    // configuration, 1 after one direct rotation of the default state
    //, 2 after two direct rotations, and 3 after two direct rotations
};

class T_Block : public Block {
    // contain BlockGrid representing the T-configuration by default
    // a rotation state (int beetween 0 and 2 mod 3) to register if the block 
    // has been applied 90 degree rotations. 0 corresponding to the default
    // configuration, 1 after one direct rotation of the default state
    //, 2 after two direct rotations, and 3 after two direct rotations
};

class O_Block : public Block {
    // a rotation state (int beetween 0 and 2 mod 3) to register if the block 
    // has been applied 90 degree rotations. 0 corresponding to the default
    // configuration, 1 after one direct rotation of the default state
    //, 2 after two direct rotations, and 3 after two direct rotations
};


#endif