**lf\_reactor\_integration** branch or what are the desired changes into the **HEAD**

# Introduction #
Here I'll try to keep track of the changes that go into the **lf\_reactor\_integration** and what are the desired feautures to be added into the **HEAD**.

## Motivation ##
Since the **HEAD** code is relatively stable, a lot of stress tests have passed, it's not yet ready for a first public version. The reason is that the library interfaces are not cleare enough and easy to use and understand.

# Details #

## Done ##
  * Although `CReactor` and `CLFThreadPool` can be coupled together it is **extremely** hard to understand how to do this and what is the purpose for users that are not part of the implementatiom, like me **:)**. So the decision is the Leaders/Followers to go into Reactor implementation and be hidden from the user. The user passes the number of threads for the reactor operation through `CReactor#handle_events(int)`. If the parameter to this method is 1 the Leaders/Followers model is skipped.

  * Another thing that clutters the usage and understanding of the framework is the fact the user has to pass different objects for one event-source - one for read and one for write.
In most cases these two operation are concerned with one logical entity, for example  connection. In the **HEAD**'s case it's user's responsibility to wrap the **handlers** objects into the connection. This changed into providing `IEventHandler#handle_read()` and `IEventHandler#handle_write()` methods. Thus connection can be just the implementation of `IEventHandler`.

## To be considered ##
What are the benefits of using the Acceptor/Connector patterns? Is this needed for a really light framework like this.
Now the Acceptor pattern is interchanged with the simple start() method that automatically registers the connection (handler), which is created and invoked by the server (handler) when new connection is accepted.

## To do ##

