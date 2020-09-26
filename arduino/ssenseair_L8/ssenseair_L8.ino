// 12/30/16 LP8 correctly creates transmit packet+ CRC, sends and turns sensor power off, then on
#include <SoftwareSerial.h>
/*
 Basic Arduino example for LP8-Series sensor
 Created by Marv Kausch
 Co2meter.com
*/
#include "SoftwareSerial.h"
int rdy = 2;
int vbb_en = 3;
int nreset = 4;
int first_loop = 0;
int temp_cntr = 0;
SoftwareSerial LP8_Serial(12, 13); //Sets up a virtual serial port
//Using pin 12 for Rx and pin 13 for Tx
static byte simple_write[] = {0xfe, 0x41, 0x00, 0x80, 0x01, 0x10,
0x28, 0x7e}; //Write 0x010 to address 0x0080
static byte write_to_0x20[] = {0xfe, 0x41, 0x00, 0x80, 0x01, 0x20,
0x28, 0x6a};
static byte read_32_bytes[] = {0xfe, 0x44, 0x00, 0x80, 0x20, 0x79,
0x3C}; // Actual butes sent: fe 41 00 80 01 20 28 6a
byte response[40];// No need to specifiy each entry
byte transmit_packet[45]; //Used to create a transmit packet
int crc_result = 0;
void setup()
{
 // put your setup code here, to run once:
 Serial.begin(9600); //Opens the main serial port to communicate with the computer
 LP8_Serial.begin(9600); //Opens the virtual serial port with a baud of 9600
 delay(1000); // one second delay
 Serial.println("\n Demo of AN162_ardunio_LP8_uart");
 pinMode(rdy, INPUT); // Define rdy pin 2 as input
 pinMode(vbb_en, OUTPUT); // Define vbb_en pin 3 as output
 pinMode(nreset, OUTPUT); // Define nreset (!reset)pin 4 as output
 Serial.println("Pins defined");
 digitalWrite(vbb_en, HIGH); // turn on vbb
 Serial.println("vbb ON");
}
void loop()
{
// reset_device(); // includes a 500 msec delay
 if (first_loop == 0) {
 reset_device(); // includes a 500 msec delay
 sendRequest(simple_write, 8, 4); // send to address 0x0080 a 0x10 first_loop = 1;
 }
 else sendRequest(write_to_0x20, 8, 4); // send to address 0x0080 a 0x10
 delay(2000);
 unsigned long valCO2 = getValue(response);
 delay(3000);
 Serial.println("Now reading 32 bytes");
 //sendRequest(read_16_bytes,7,21);
 sendRequest(read_32_bytes, 7, 37);
 Serial.print("CO2 from 0x9a-0x9b = ");
 Serial.print(response[29], HEX);
 Serial.print(response[30], HEX);
 Serial.print(" = ");
 int decimal = 256 * response[29] + response[30];
 Serial.print(decimal);
 Serial.println("d");
 // Call ModBUS CRC clculator
 crc_result = ModRTU_CRC(response, 35); // Function call to calculate CRC
 Serial.print("**** CRC result =");
 int crc_result_h = crc_result & 0xff;
 Serial.print(crc_result_h, HEX);
 Serial.print(" ");
 int crc_result_l = (crc_result >> 8) & 0xff;
 Serial.println(crc_result_l, HEX);
 // Verify that the sensor's CRC matches the just now calculated CRC
 if ((response[35] != crc_result_h) && (response[36] ==
crc_result_l)) {
 Serial.println("! ! ! CRC Sensor and Calulated Do NOT MATCH");
 }
 else {
 Serial.println(" CRC Sensor and Calulated MATCH");
 ////////POWER DOWN sensor here for 20 seconds
 digitalWrite(vbb_en, LOW); // turn on vbb
 Serial.println("vbb OFF");
 delay(20000);// wait 20 seconds befoe next sensor read
 digitalWrite(vbb_en, HIGH); // turn on vbb
 Serial.println("vbb ON");
 while (digitalRead(rdy) == HIGH) {
 Serial.println("waiting for rdy to go low");
 }
 Serial.println("rdy now LOW, an active LOW signal. Low means READY.");

 /* Since calculated and sensor CRC match, write contents of
sensor[],
 replacing received the two CRC bytes with newly calculated
CRC.
 This is necessary since a Modbus write command requires an
appropriateModBUS write command
 PLUS sensor[] data PLUS CEC added as the last 2 bytes.
 Write command is: 0xfe 0x41 0x00 0x81 0x
 Prepare transmit buffer to write Modbus commwnd PLUS
0x0081-0x099 = 0x18+1 = 0x19 = 25d
 */
 transmit_packet[0] = 0xfe; //
 transmit_packet[1] = 0x41; //Write to LP8 ModBus command
 transmit_packet[2] = 0x0; // Address H
 transmit_packet[3] = 0x80; //address L
 transmit_packet[4] = 0x19;//number of bytes = 0x0080 thru 0x0099 
 transmit_packet[5] = 0x20; //INCLUDING calculation control byte
  for (int i = 6; i < (6+25); i++) {
      for (int i = 6; i < (0X19+6); i++) {
      transmit_packet[i] = response[i-3];
 }
// Now compute new CRC of all data in transmit_packet[]:
 crc_result = ModRTU_CRC(transmit_packet, (6+23)); // Function
call to calculate CRC 37=0 to 36
// Sometimes thif function responds with FFFFxxxx rather tha
xxxx. So, strip off any possible FFFF...
 int crc_result_h = crc_result & 0xff;
 Serial.print("transmit_packet crc_result =");
 Serial.print(crc_result_h, HEX);
 Serial.print(" ");
 int crc_result_l = (crc_result >> 8) & 0xff;
 Serial.println(crc_result_l, HEX);
 transmit_packet[37]=crc_result_h; // Add CRC to last two bytes
of transmit_packet
 transmit_packet[38]=crc_result_l;
 for (int i = 0; i < (6+25); i++) {
 Serial.print(" response[");
 Serial.print(i);
 Serial.print("] = 0x");
 Serial.print(response[i], HEX);
 Serial.print(" transmit_packet[");
 Serial.print(i);
 Serial.print("] = 0x");
 Serial.print(transmit_packet[i], HEX);
 if (i>5){
 Serial.print(" = RAM location[");
 Serial.print((0x80+i-5),HEX);
 Serial.println("]");
 }
 else Serial.print("\n");
 }

// Send transmit_packet[] to LP8
sendRequest(transmit_packet, 39, 4); // send 38 bytes total,
expect 4 byte response
Serial.println("\n ****** transmit_packet sent to LP8 RAM ******.");
Serial.println("Sensor response:");
temp_cntr++;
if (temp_cntr==2)while(1);// limits times thru loop for Serial
Monitor display. No other limitations
 }
} //Bottom of main loop
void sendRequest(byte packet[], int m, int n)
{
 while (!LP8_Serial.available()) //keep sending request until we
start to get a response
 {
 Serial.println("waiting for Software.serial port availability");
 LP8_Serial.write(packet, m);
 delay(1000); // Necessary to get consistent loading of
response[i]
 }
 int timeout = 0; //set a timeout counter
 while (LP8_Serial.available() < n ) //Wait to get a n byte
response
 {
 timeout++;
 if (timeout > 10) //if it takes too long there was probably an
error
 {
 while (LP8_Serial.available()) //flush whatever we have
 LP8_Serial.read();
 break; //exit and try again
 }
 delay(50);
 }
 for (int i = 0; i < n; i++)
 {
 response[i] = LP8_Serial.read();
 // Serial.print("response[i] = ");
 Serial.print("response[");
 Serial.print(i);
 Serial.print("] = ");
 Serial.println(response[i], HEX);
 }
 Serial.print("\n\n");
 Serial.flush();
}
int reset_device() {
 digitalWrite(nreset, LOW); // assert RESET
 Serial.println("nreset now low");
 delay(500);//500 msec delay
 digitalWrite(nreset, HIGH); // assert RESET
 Serial.println("nreset now high");
 while (digitalRead(rdy) == HIGH) {
 Serial.println("waiting for rdy to go low");
 }
 Serial.println("rdy now LOW, an active LOW signal. Low means READY.");
}
unsigned long getValue(byte packet[])
{
 int high = packet[3]; //high byte for value is 4th byte in
packet in the packet
 int low = packet[4]; //low byte for value is 5th byte in the
packet
 unsigned long val = high * 256 + low; //Combine high byte and
low byte with this formula to get value
 return val;
}
///////////////////// CRC routine here ///////////////////
// Compute the MODBUS RTU CRC
int ModRTU_CRC(byte sensor_data[], byte n1) {
 int ij;
 //Calc the raw_msg_data_byte CRC code
 uint16_t crc = 0xFFFF;
 String crc_string = "";
 // for (int pos = 0; pos < raw_msg_data.length()/2; pos++) {
 for (int pos = 0; pos < n1; pos++) {
 crc ^= (uint16_t)sensor_data[pos]; // XOR byte into
least sig. byte of crc
 for (int ij = 8; ij != 0; ij--) { // Loop over each bit
 if ((crc & 0x0001) != 0) { // If the LSB is set
 crc >>= 1; // Shift right and XOR
0xA001
 crc ^= 0xA001;
 }
 else // Else LSB is not set
 crc >>= 1; // Just shift right
 }
 }
 Serial.print("\n"); // Note, this number has low and high bytes
swapped, so use it accordingly (or swap bytes)
 Serial.print(" CRC HEX VALUE = ");
 Serial.println(crc, HEX);
 crc_string = String(crc, HEX);
 return crc;
}
