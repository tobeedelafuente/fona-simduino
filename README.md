# fona-simduino
This is a sample code for Elecrow's SIMduino UNO+SIM808 GPRS/GSM Board using the Adafruit Fona library.
The logic for the SIM808 module is in fona.ino. All of the functions can be used to the your main arduino file (in this case, main.ino)

# Prerequisites
Make sure that the jumper wires are set to Software UART on the Simduino. 


![logo](https://www.elecrow.com/wiki/images/c/cb/SIMduino_interface1.jpg "Simduino")

Also, make sure that when you try to turn on the SIM808 module (the NET LED should light up to signify this), you have a good power supply. Otherwise, the GSM module will turn off. For more information, check the [Simduino product wiki](https://www.elecrow.com/wiki/index.php?title=Elecrow_SIMduino_UNO%2BSIM808_GPRS/GSM_Board).

# Optional
As of now, Simduino does not have any mechanism to programatically turn on or off the GSM module. As an alternative, you can solder a wire on the KEY button and connect it to any pin. Check the ![link](https://drive.google.com/file/d/1DeicUCUEfRc5JIkgSV_9X6LegQt_vMFy/view?usp=sharing "Simduino") for the picture (The wire is connected to Analog pin A5). 

With this you do not need to press the KEY button anymore.

# Functions
## setupFona()
Initiate communication between the Arduino and the SIM808 module through SoftwareSerial. The debug logs should reveal whether the board is able to communicate to the SIM808 module. When the communication is successful, the GPS and GPRS modules are initialized. After initializing the GPS and GPRS modules, the fifteen (15) most recent messages saved on the SIM card are deleted. This is because the SIM808 module can only support a few saved messages on the SIM card. If we don't delete, the module behaves erratically.

## deleteMessages()
Delete fifteen (15) recently saved messages on the SIM card.

## sendSMS(number, message)
Send a message on the number. 

## readSMS(number)
The Adafruit Fona library has an example for getting unread messages. However it does not seem to work properly. As a work around, reading SMS is done inside the loop function (see main.ino). This means that we are polling. The readSMS function checks whether the SIM808 module has received a message from the number that was passed as a parameter. If the sender is not the same with the number supplied, then the SMS is flagged as "unauthorized". Otherwise, we get the message to be processed outside fona.ino

## getGPS(latitude, longitude, speed_kph, heading, altitude)
Get GPS data and store the data to the parameters. The function returns 0 when there is no GPS fix. NOTE: It is important that you use a good GPS antenna otherwise the SIM808 module won't get a GPS fix. 

##getGSMLoc(latitude, longitude)
This is an alternative way for acquiring latitude and longitude if you do not have any GPS antenna. This function gets the location of the GSM module.
