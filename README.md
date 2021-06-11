# arduino-moulinette

## Usage
```
python3 arduinette.py --config_file blink/inputs.c --config_header_file blink/config.h --solution blink/blink.c --file blink/mytry.ino 
```
* config_file : C file used to create additional function to represent an input behavior for instance (see button/).
* config_file_header : C header file used to define specifc macros.
* solution : C file containing the code with which each student code will be compared to. The file MUST include the "../fakeArduino.h" header.
* file : C or .ino file to compare with the solution file. This file DOESN'T HAVE to include the "../fakeArduino.h" header.

### Macros
* TIMEOUT_LIMIT : Timout for the code to test in ms. Past this delay, the program will exit (preventing infinite loop).
* LOOPS_LIMIT : The maximum number of time the loop() function is executed before exiting.
* LOOP_TIME : The simulated time each call to loop() will take in ms.

### Exemple
```
python3 arduinette.py --config_file blink/inputs.c --config_header_file blink/config.h --solution blink/blink.c --file blink/mytry.ino
```
```
python3 arduinette.py --config_file button/inputs.c --config_header_file button/config.h --solution button/button.c --file button/mytry.c
```
