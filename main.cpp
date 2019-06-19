#include "mbed.h"
#include "bbcar.h"


Ticker servo_ticker;
Ticker encoder_ticker1;
Ticker encoder_ticker2;
PwmOut pin8(D8), pin9(D9);
DigitalIn pin4(D4);
DigitalIn pin3(D3);

Serial pc(USBTX, USBRX);
Serial xbee(D12, D11);

BBCar car(pin8, pin9, servo_ticker);

void reply_messange(char *xbee_reply, char *messange){
    xbee_reply[0] = xbee.getc();
    xbee_reply[1] = xbee.getc();
    xbee_reply[2] = xbee.getc();
    if(xbee_reply[1] == 'O' && xbee_reply[2] == 'K'){
        pc.printf("%s\r\n", messange);
        xbee_reply[0] = '\0';
        xbee_reply[1] = '\0';
        xbee_reply[2] = '\0';
    }
}

int main() {
    pc.baud(9600);
    xbee.baud(9600);
    char xbee_reply[3];
    xbee.printf("+++");
    xbee_reply[0] = xbee.getc();
    xbee_reply[1] = xbee.getc();
    if(xbee_reply[0] == 'O' && xbee_reply[1] == 'K'){
     pc.printf("enter AT mode.\r\n");
     xbee_reply[0] = '\0';
     xbee_reply[1] = '\0';
    }
    xbee.printf("ATMY 0x10\r\n");
    reply_messange(xbee_reply, "setting MY : 0x10");

    xbee.printf("ATDL 0x101\r\n");
    reply_messange(xbee_reply, "setting DL : 0x101");

    xbee.printf("ATID 0x1010\r\n");
    reply_messange(xbee_reply, "setting PAN ID : 0x1010");

    xbee.printf("ATWR\r\n");
    reply_messange(xbee_reply, "write config");

    xbee.printf("ATCN\r\n");
    reply_messange(xbee_reply, "exit AT mode");
    xbee.getc();

    // start
    pc.printf("start\r\n");
    char receive_data = 0;

    parallax_encoder encoder0(pin3, encoder_ticker1);
    parallax_encoder encoder1(pin4, encoder_ticker2);

    encoder0.reset();
    encoder1.reset();

    
    while(1){
        car.goStraight(100);
        wait(1);
        pc.printf("enconder0= %f\r\n", encoder0.get_cm());
        pc.printf("enconder1= %f\r\n", encoder1.get_cm());
        //pc.printf("Receive data %c\r\n", receive_data);
        //if (receive_data == 'a') {
        //    //xbee.printf("A received the data.");
        xbee.printf("enconder0= %f\r\n", encoder0.get_cm());
        xbee.printf("enconder1= %f\r\n", encoder1.get_cm());
        //}
        wait(1);
        receive_data = 0;
            
    }
}
