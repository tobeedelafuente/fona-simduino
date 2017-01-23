# fona-simduino
This is a sample code for Simduino using the Adafruit Fona library.
The logic for the SIM808 module is in fona.ino. All of the functions can be used to the your main arduino file (in this case, main.ino)

#Prerequisites
Make sure that the jumper wires are set to Software UART on the Simduino. 


![logo](https://www.elecrow.com/wiki/images/c/cb/SIMduino_interface1.jpg "Simduino")

Also, make sure that when you try to turn on the SIM808 module (the NET LED should light up to signify this), you have a good power supply. Otherwise, the GSM module will turn off. For more information, check the [Simduino product wiki] (https://www.elecrow.com/wiki/index.php?title=Elecrow_SIMduino_UNO%2BSIM808_GPRS/GSM_Board).


#Functions
setupFona() - initiate communication between the Arduino and the SIM808 module through SoftwareSerial. The debug logs should reveal whether the board is able to communicate to the SIM808 module. When the communication is successful, the GPS and GPRS modules are initialized. After initializing the GPS and GPRS modules, the ten (10) most recent messages saved on the SIM card are deleted. This is because the SIM808 module can only support a few saved messages on the SIM card. If we don't delete, the module behaves erratically.

deleteMessages() - delete the ten (10) recently saved messages on the SIM card.

sendSMS(number, message) - send a message on the number. NOTE: If String variables are to be passed as a parameter, use the ".c_str()" function. Example:
```
String message = "Hello"!;
sendSMS("09XXXXXXXXX", message.c_str());
```

readSMS(number) - the Adafruit Fona library has an example for getting unread messages. However it does not seem to work properly. As a work around, reading SMS is done inside the loop function (see main.ino). This means that we are polling. The readSMS function checks whether the SIM808 module has received a message from the number that was passed as a parameter. If the sender is not the same with the number supplied, then the SMS is flagged as "unauthorized". Otherwise, we get the message to be processed outside fona.ino

getGPS(latitude, longitude, speed_kph, heading, altitude) - get GPS data and store the data to the parameters. The function returns 0 when there is no GPS fix. NOTE: It is important that you use a good GPS antenna otherwise the SIM808 module won't get a 
GPS fix. 
