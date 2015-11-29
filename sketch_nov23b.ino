
#define DPTR(x) (*(volatile uint32_t*)(x)) //dereference volatile memory

extern "C" {
  __attribute__((naked))
  void myDelay(uint32_t cycles)
  {
    __asm("subs r0, #1\n"
          "bne myDelay\n"
          "bx lr\n");
  }
}

int main(void) {
  DPTR(0x400FE608) |= 0x00000020;
  DPTR(0x40025420) &= ~0x0000000E; //clear 4th pin
  DPTR(0x40025500) |= 0x0000000E; //set pin 2ma drive strength
  DPTR(0x40025510) &= ~0x0000000E; //disable pullup resistor
  DPTR(0x40025514) &= ~0x0000000E; //disable pulldown resistor
  DPTR(0x40025518) &= ~0x0000000E; //disable slew rate control
  DPTR(0x4002551C) |= 0x0000000E; //enables pins so direction can be set
  DPTR(0x40025400) |= 0x0000000E; //pin diretion (input or output)
  
  //To enable switch functionality, disable the pullup resistor so
  //that the voltage is connected to V+
  
  while(1) {
    DPTR(0x40025000 + (0x0E << 2)) = 0x0E;
    myDelay(10000000ul);
    DPTR(0x40025000 + (0x0E << 2)) = 0x00;
    myDelay(10000000ul);
 /* DPTR(0x40025000 + (0x0E << 2)) = 0x02;
    myDelay(10000000ul);
    DPTR(0x40025000 + (0x0E << 2)) = 0x04;
    myDelay(10000000ul);
    DPTR(0x40025000 + (0x0E << 2)) = 0x08;
    myDelay(10000000ul); */
  }
  return 0;
}
