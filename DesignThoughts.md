To do or not to do...

# Introduction #

Add your content here.


# Details #
What is the best way for implementing the `CReactor#handle_lf(number of threads)`?
The question here is should the invokation thread be joined into the thread pool or the method have to start the number of threads specified and the caller thread to join (block) waiting for the threads from the thread pool exit. For example the two possible implementations are:
```
        void
        handle_events_lf(unsigned int threads)
        {
            utils::CThread<SLFThread>* array[threads];
        
            //start threads
            for(int i = 0; i < threads; i++)
            {
                array[i] = utils::CThread<SLFThread>::getInstance(reinterpret_cast<void*>(&m_LFThreadPool));
                
                if(!array[i]->run())
                    assert(false);
            }
        
            //join threads
            for(int i = 0; i < threads; i++)
                array[i]->join();
        }
```

and
```
        void
        handle_events_lf(unsigned int threads)
        {
            utils::CThread<SLFThread>* array[threads];
        
            //start threads
            for(int i = 0; i < threads-1; i++)
            {
                array[i] = utils::CThread<SLFThread>::getInstance(reinterpret_cast<void*>(&m_LFThreadPool));
                
                if(!array[i]->run())
                    assert(false);
            }

            m_LFThreadPool.join(); //join the invokation thread into the thread pool        
        }
```

The second method seems more logical because in the first we have one thread only waiting for the thread, i.e. not doing any job. For example when invoking from the main thread, main will blocked, waiting to join the threads from the thread pool. When starting the Reactor in the background, i.e. when not invoking `CReactor#handle_events()` from main thread the user shoud wait (join) for the started thread. Here is the example:

```
// Run the reactor in the background
struct SReactorRunner : public std::unary_function<void*,void*>
{
    void* operator()(void* arg)
    {
        CReactor* pReactor = (CReactor*)(arg);
        pReactor->handle_events(4);
    }
};

main()
{
    CThread<SReactorRunner> reactor_thread;
    reactor_thread.run();

    // do something

    reactor_thread.join();
}

//and the easier main ;) - run the Reactor from the main
main()
{
    CReactor reactor;
    reactor.handle_events(4); // the main threadd is joined into the pool
}
```