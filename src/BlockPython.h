#ifndef BLOCKPYTHON_H
#define BLOCKPYTHON_H

#include "BlockInterface."

class BlockPython : public BlockInterface
{
public:
    BlockPython( PyObject *pBlock );

    size_t get_NrInputs( );
    size_t get_NrOutputs( );
private:
};

#endif // BLOCKPYTHON_H
