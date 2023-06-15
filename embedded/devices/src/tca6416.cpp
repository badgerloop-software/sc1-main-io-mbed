#include "tca6416.h"

// Pins to read: 1
// Pins to write: 0
TCA6416::TCA6416(I2C *bus, uint8_t addr) : I2CDevice(bus, addr) {

}

uint8_t TCA6416::read_from_reg(uint8_t reg){
    static char dat[16];
    readI2CWrapper(reg, dat, 1);
    return dat[0];
}

void TCA6416::write_data(uint8_t reg, uint8_t val){
    static char dat[1];
    dat[0] = val;
    writeI2CWrapper(reg, dat, 1);
}

int TCA6416::begin(const uint8_t directions[]){
  this->clear_settings();
  // set directions for pins in the first bank
  for (int i = 0; i < TCA_NUM_PINS_PER_BANK; ++i)
    this->set_dir(0, i, directions[i]);
  // set directions for pins in the second bank
  for (int i = 0; i < TCA_NUM_PINS_PER_BANK; ++i)
    this->set_dir(1, i, directions[TCA_NUM_PINS_PER_BANK + i]);

  // Make sure each pin in bank 0 actually received the correct value
  for (int i = 0; i < TCA_NUM_PINS_PER_BANK; ++i) {
    if (this->get_dir(0, i) != directions[i]) {
      puts("Error setting direction of pin");
      return -EIO;
    }
  }
  // Repeat process for bank 1
  for (int i = 0; i < TCA_NUM_PINS_PER_BANK; ++i) {
    if (this->get_dir(1, i) != directions[TCA_NUM_PINS_PER_BANK + i]) {
      puts("Error setting direction of pin");
      return -EIO;
    }
  }
  return 0;
}

int TCA6416::clear_settings(){
    char dat[1] = {0xFF};

    //Clears settings to initial states
    write_data(TCA_CFG0_REG, 0xFF);
    write_data(TCA_CFG1_REG, 0xFF);
    write_data(TCA_OUT0_REG, 0xFF);
    write_data(TCA_OUT1_REG, 0xFF);

    return 0;
}

int TCA6416::set_state(bool bank, int pin, uint8_t val) {
    if (pin >= TCA_NUM_PINS_PER_BANK || pin < 0) return -1;

    uint8_t dirReg = bank ? TCA_CFG1_REG : TCA_CFG0_REG;
    uint8_t stateReg = bank ? TCA_OUT1_REG : TCA_OUT0_REG;

    uint8_t current_dir = this->read_from_reg(dirReg);
    if ((current_dir >> pin) & 0x1) return -1;

    uint8_t current_status = this->read_from_reg(stateReg);
    if (val)
        write_data(stateReg, current_status | (1 << pin));
    else
        write_data(stateReg, current_status & ~(1 << pin));

    return 0;
}

int TCA6416::get_state(bool bank, int pin) {
    uint8_t current_status;
    uint8_t stateReg;
    uint8_t dir;

    if (pin >= TCA_NUM_PINS_PER_BANK || pin < 0) return -EINVAL;
    dir = get_dir(bank, pin);
    // set stateReg to the correct register
    if (bank) {
        if (dir)
            stateReg = TCA_IN1_REG;
        else
        stateReg = TCA_OUT1_REG;
    } else {
        if (dir)
            stateReg = TCA_IN0_REG;
        else
            stateReg = TCA_OUT0_REG;
    }

  current_status = read_from_reg(stateReg);

  return ((current_status >> pin) & 1);
}

int TCA6416::set_dir(bool bank, int pin, uint8_t dir) {
    uint8_t dirReg = bank ? TCA_CFG1_REG : TCA_CFG0_REG;
    int rc;

    if (pin >= TCA_NUM_PINS_PER_BANK || pin < 0) return -1;

    uint8_t current_status = read_from_reg(dirReg);
    if (dir) {
        write_data(dirReg, current_status | (1 << pin));
    } else {
        write_data(dirReg, current_status & ~(1 << pin));
    }
    return 0;
}

int TCA6416::get_dir(bool bank, int pin) {
    uint8_t dirReg = bank ? TCA_CFG1_REG : TCA_CFG0_REG;
    int rc;

    if (pin >= TCA_NUM_PINS_PER_BANK || pin < 0) return -1;

    uint8_t current_status = read_from_reg(dirReg);

    return ((current_status >> pin) & 1);
}
