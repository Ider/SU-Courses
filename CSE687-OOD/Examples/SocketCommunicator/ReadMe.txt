
Note:

If you build the cleaned solution you will get an error do to a missing Communicator.lib file,  
a static library.  Build the solution again and it will succeed.

Alternately, you can simply build the Communicator project, which is set to build a static library,
first, then build the solution.

The ReceiverApp and SenderApp projects are the only ones that use Communicator.lib
