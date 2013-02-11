#ifndef BLOCKINTERFACE_H
#define BLOCKINTERFACE_H

#include "boost/any.hpp"

#include <vector>
#include <string>

class BlockInterface;

struct sampletype;

typedef void(*sink_callback_fpt)(BlockInterface*, const sampletype&);
typedef void(*source_callback_fpt)(BlockInterface*, sampletype&);

class Source
{
public:
    void getSample( sampletype& sample ) { callback_func( block, sample); }
private:
    BlockInterface *block;
    std::string label;
    std::string type_id;
    source_callback_fpt callback_func;
};

class Sink
{
public:
    void setSample( sampletype& sample ) { callback_func( block, sample); }
private:
    BlockInterface *block;
    std::string label;
    std::string type_id;
    sink_callback_fpt callback_func;
};

class BlockInterface
{
public:

    // do these really belong to the interface?
    //void addInput( sink_callback_fpt func, const std::string &type_id, const std::string &label = "" );
    //void addOutput( source_callback_fpt func, const std::string &type_id, const std::string &label = "" );

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
