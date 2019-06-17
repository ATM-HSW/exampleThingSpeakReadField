Create project:
```
mbed import https://github.com/ATM-HSW/exampleThingSpeakReadField.git exampleThingSpeakReadField
```

Export to Keil µVision
```
mbed export -m NUCLEO_F767ZI -i uvision
```

or compile directly
```
mbed compile -m NUCLEO_F767ZI -t ARM
```

Make sure using Python 2.7. Python 3 is not (yet) working.

Documentation can be found (soon completed) under: https://github.com/ATM-HSW/exampleThingSpeakReadField/blob/master/ThingSpeak.md
