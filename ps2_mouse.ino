// DigiMouse test and usage documentation
// CAUTION!!!! This does click things!!!!!!!!
// Originally created by Sean Murphy (duckythescientist)
// modified by Luke (ugg) to accept input from a ps2 mouse/touchpad with ps2 library from Chris J. Kiick



#include <DigiMouse.h>
#include <ps2.h>
PS2 mouse(2, 0);

void setup() {
  DigiMouse.begin(); //start or reenumerate USB - BREAKING CHANGE from old versions that didn't require this
}

uint8_t mstat, mx, my;//mouse vars
bool i;//initial state

void loop() {
  
  // If not using plentiful DigiMouse.delay(), make sure to call
  //  DigiMouse.update(); //at least every 50ms

        //initial state, just send blank data packets till mouse has properly woken up 
        //(mine takes 600-750ms) at which point it will say its performed its POST 
        //and all is well (which is compleltely ignored)
  if (!i)
    DigiMouse.update();
    
  if (i == 0)//if initial state and 3s have passed
  {
    if (millis() < 3000)
      ;//do nothing
    else
    {
      i++;//else leave initial state and initialise the mouse
      mouse_init();
    }
  }
  /*
    unsure where i grabbed the & 0x10 from, but checks to see if the TX system is 
    inactive which with a reduction of the delays on setting ps2 pins to master TX
    mode make for a nice smooth action (one ps2 packet per usb)
    
    before shorter ps2 tx mode delays were used ps2 communication was only every
    ~4th-12th usb packet, more investigation might be good??
  */
  
  if (i && usbTxStatus1.len & 0x10)                                    
  {
    mouse.write(0xeb);  // give me data!
    mouse.read();      // ignore ack
    mstat = mouse.read();
    mx = mouse.read();
    my = mouse.read();
    DigiMouse.move(mx, my*-1,0,mstat);//y var is inverted on my touchpad for some reason, 
    DigiMouse.update();               //and "4th" button bit always on?? (pad only has 2 buttons)
  }
}


void mouse_init()
{
  mouse.write(0xff);  // reset
  mouse.read();  // ack byte
  mouse.read();  // blank */
  mouse.read();  // blank */
  mouse.write(0xf0);  // remote mode
  mouse.read();  // ack
  DigiMouse.delay(25); //this does annoy the usb controller, but its only once 
                       //and previous calls are ~1ms each (a single byte transfered). 
                       //So roughtly 20ms less than a complete usb timeout?
}
