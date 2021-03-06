#ifndef THREAD_POOL_H
#define THREAD_POOL_H

#include <list>

class thread;

namespace thread_pool
{
    template<class policy>
    class dynamic_pool
    {
    public:
        dynamic_pool( size_t num_threads );

        void set_poolsize( size_t num_threads );
        size_t get_poolsize( );

        void add_task( );
    private:
        std::list<thread> pool_;
        policy queue_;
    };
}

#endif // THREAD_POOL_H
