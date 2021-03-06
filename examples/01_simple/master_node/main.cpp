/*----------------------------------------*/
// Test sending messages from master.
//
// In this script, master sends a message (command = 0x01)
// with alternating 0s and 1s for each node on the bus.
//
/*----------------------------------------*/

#include <stdint.h>
#include <util/delay.h>

#include "DiscobusMaster.h"
#include "DiscobusDataUart.h"

#define NODE_COUNT 1

int main() {
  uint8_t iteration = 1, i = 0;

  DiscobusDataUart serial;
	DiscobusMaster master(&serial);

  serial.begin(9600);
  master.setNodeLength(NODE_COUNT);
  
  while(1) {
    master.startMessage(0x01, DiscobusMaster::BROADCAST_ADDRESS, 1, true);

    // Send alternating 1s and 0s
    for (i = 0; i < NODE_COUNT; i++) {
      if ((i + iteration) % 2 == 0) {
        master.sendData(0x01);
      } else {
        master.sendData(0x00);
      }
    }

    master.finishMessage();

    iteration++;
    _delay_ms(1000);
  }
}
