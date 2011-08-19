unsigned char readbuff[64] absolute 0x280;  // Buffers should be in USB RAM, please consult datasheet
unsigned char writebuff[64] absolute 0x2c0;
char cnt;

void interrupt(){
   USB_Interrupt_Proc();                  // USB servicing is done inside the interrupt
}
void main(void){
  HID_Enable(&readbuff,&writebuff);       // Initialize HID communication and specify our read and write buffers
  while(1){                               // Main program loop
    while(!HID_Read());                   // Loop until there's data to read on HID

    for(cnt=0;cnt<64;cnt++)               // Loop through our 64 byte buffer.
      writebuff[cnt]=readbuff[cnt];       // Echo each byte from the read buffer to the write buffer

    while(!HID_Write(&writebuff,64));     // Send the write buffer over USB
  }
}
