#ifndef BLOCKINTERFACE_H
#define BLOCKINTERFACE_H

#include "boost/any.hpp"

#include <vector>
#include <string>

class Source
{
public:
private:
    std::string type_id( );
    output_callback callback_func;
};

// @todo call it BlockBase instead of BlockInterface?
class BlockInterface
{
public:
    typedef void(*input_callback)(BlockInterface*, const boost::any&);
    typedef void(*output_callback)(BlockInterface*, boost::any&);

    void addInput( input_callback func, std::string type_id );
    void addOutput( output_callback func, std::string type_id );

    // example how to declare inputs/outputs
    //static void input( BlockInterface* this_ptr, const boost::any& buffer ) { }
    //static void output( BlockInterface* this_ptr, boost::any& buffer ) { }

    size_t get_NrInputs( );
    size_t get_NrOutputs( );

private:
    std::vector<Sink> inputs_;
    std::vector<Source> outputs_;

};

#endif // BLOCKINTERFACE_H
