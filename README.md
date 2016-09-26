# AVR Disco Bus

A versatile AVR/Arduino library for communicating on multidrop master/slave bus, like RS485.
Put simply, it's an easy way to communication with a lot of devices over a pair of twisted wires. 

You can read more about the Disco Bus [protocol spec here](https://github.com/jgillick/Disco-Bus-Protocol)

## Implementation Quickstart

This is the most basic master/server setup where the slave node address is known and master
just sends messages. (see the [simple example](examples/01_simple))

![Simple Demo](examples/diagrams/serial-simple.png?raw=true)

### Slave

```cpp
DiscobusDataUart serial;
DiscobusSlave slave(&serial);

serial.begin(9600);
slave.setAddress(0x01);

while(1) {
  slave.read();
  if (slave.hasNewMessage() && slave.isAddressedToMe()) {
    // Do something with the received message
    // See: slave.getCommand() and slave.getData()
  }
}
```

### Master

```c
DiscobusDataUart serial;
DiscobusMaster master(&serial);

serial.begin(9600);

// send command 0xA1, to node 1, message data length will be 2
master.startMessage(0xA1, 0x01, 2);
master.sendData('H');
master.sendData('i');
master.finishMessage();
```

### Explanation

Both master and slave nodes need a way to communicate to each other. So the first thing you need to do
is initialize a data object. In this case `DiscobusDataUart` communicates over the main UART line.
There's also a `DiscobusData485`, which can be used to communicate via RS485 transceivers. You can
easily create your own data class by extending `DiscobusData`.

The rest is probably self explanatory. The slave nodes will need to call the `read()` method regularly
in order to read new bytes from the data source. When a full message has been received, `hasNewMessage()`
will return `true`.

## Examples

There are more complex examples in the [examples directory](/MultidropBusProtocol/examples/).

## Fun Fact
The direction of the daisy lines can be determined dynamically. The node will wait
to see which side becomes enabled and then assume that is the input daisy line.


# License

> MIT License
> 
> Copyright (c) 2016 Jeremy Gillick
> 
> Permission is hereby granted, free of charge, to any person obtaining a copy
> of this software and associated documentation files (the "Software"), to deal
> in the Software without restriction, including without limitation the rights
> to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
> copies of the Software, and to permit persons to whom the Software is
> furnished to do so, subject to the following conditions:
> 
> The above copyright notice and this permission notice shall be included in all
> copies or substantial portions of the Software.
> 
> THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
> IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
> FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
> AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
> LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
> OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
> SOFTWARE.