#include "can.h"

Can::Can(CAN* canBus) : t(osPriorityHigh) {
    this->canBus = canBus;
    this->isInit = true;

    canBus->frequency(CAN_FREQ);
    t.start(callback(this, &Can::canThread));
}

Can::~Can() {
  isInit = 0;
  eventFlags.set(CAN_STOP);
  t.join();
}

void Can::interrupt() { eventFlags.set(CAN_RX_INT_FLAG); }

void Can::canThread() {
  printf("in thread\n");
  CANMessage msg;
  while (isInit) {
    if (canBus->tderror() || canBus->rderror()) {
        reset();
    }
    
    eventFlags.wait_any(CAN_RX_INT_FLAG | CAN_STOP);
    printf("Here\n");
    CANMessage msg;
    if (read(msg) < 0)
      break;
    for (auto d : devices)
      if (!d->callback(msg))
        break;
  }

}

void Can::reset() {
    canBus->reset();
    wait_us(1000);
    canBus->attach(callback(this, &Can::interrupt), CAN::RxIrq);
}

int Can::read(CANMessage &msg) {
  canBus->read(msg);
  return 0;
}

int Can::send(unsigned int id, char *data, unsigned int len) {
  if (len > 8)
    return -1;
  CANMessage msg(id, data, len);
  return !(canBus->write(msg));
}