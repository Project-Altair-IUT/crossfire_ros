/*
This example outputs values from all PPM channels to Serial
in a format compatible with Arduino IDE Serial Plotter
*/
#include <ros.h>
#include <std_msgs/String.h>
#include <std_msgs/Int16MultiArray.h>
#include <PPMReader.h>

ros::NodeHandle  nh;
std_msgs::Int16MultiArray int_msg;
ros::Publisher rc_signal("rc_signal", &int_msg);

int16_t ch[8];
// Initialize a PPMReader on digital pin 2 with 8 expected channels.
byte interruptPin = 2;
byte channelAmount = 8;
PPMReader ppm(interruptPin, channelAmount);

void setup() {
    Serial.begin(115200);
    nh.initNode();
    nh.advertise(rc_signal);
}

void loop() {
  
    // Print latest valid values from all channels
    for (byte channel = 1; channel <= channelAmount; ++channel) {
        ch[channel - 1] = ppm.latestValidChannelValue(channel, 0);
//        Serial.print(ch[channel - 1]);
//        if(channel < channelAmount) Serial.print('\t');
    }
//    Serial.println();
    int_msg.data = ch;
    int_msg.data_length = 8;
    rc_signal.publish(&int_msg);
    nh.spinOnce();
    delay(20);
}
