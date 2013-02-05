#ifndef BLOCKINTERFACE_H
#define BLOCKINTERFACE_H

#include "boost/any.hpp"

#include <tr1/functional>
#include <vector>
#include <string>

class BlockInterface;

typedef void(*blockinput_callback_fpt)(BlockInterface*, const boost::any&);
typedef void(*blockoutput_callback_fpt)(BlockInterface*, boost::any&);

class Source
{
public:
private:
    std::string label;
    std::string type_id;
    blockoutput_callback_fpt callback_func;
};

class Sink
{
public:
private:
    std::string label;
    std::string type_id;
    blockinput_callback_fpt callback_func;
};

// @todo call it BlockBase instead of BlockInterface?
class BlockInterface
{
public:

    void addInput( blockinput_callback_fpt func, const std::string &type_id, const std::string &label = "" );
    void addOutput( blockoutput_callback_fpt func, const std::string &type_id, const std::string &label = "" );

    // example how to declare inputs/outputs
    //static void input( BlockInterface* this_ptr, const boost::any& buffer ) { }
    //static void output( BlockInterface* this_ptr, boost::any& buffer ) { }

    size_t get_NrInputs( );
    size_t get_NrOutputs( );

    Sink &getInput( size_t nr );
    Source &getOutput( size_t nr );

private:
    std::vector<Sink> inputs_;
    std::vector<Source> outputs_;

};

#endif // BLOCKINTERFACE_H
