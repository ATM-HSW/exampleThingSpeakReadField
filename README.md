Prerequisite
------------
Based on the principle described in: https://os.mbed.com/docs/mbed-os/v5.12/tools/working-with-mbed-cli.html topic 'Managing multiple Mbed projects'
```
$ cd <projects directory>
$ mbed add mbed-os mbed-os-5.12.4
$ cd mbed-os-5.12.4
$ mbed update mbed-os-5.12.4
$ mbed config -G MBED_OS_DIR <projects directory>/mbed-os-5.12.4
[mbed] <projects directory>/mbed-os-5.12.4 now set as global MBED_OS_DIR
```

Create/import project (working directory: <projects directory>)
---------------------------------------------------------------
```
mbed import https://github.com/ATM-HSW/exampleThingSpeakReadField.git exampleThingSpeakReadField
```

Export (working directory: <projects directory>)
------------------------------------------------
e.g. to Keil µVision using Mbed platform NUCLEO_F767ZI
```
$ mbed export -m NUCLEO_F767ZI -i uvision6 --source .\exampleThingSpeakReadField  --source .\mbed-os-5.12.4
```

Make sure using Python 2.7. Python 3 is not (yet) working.

Tested with Mbed OS 5.12.4 and NUCLEO_F767ZI

Documentation can be found (soon completed) under: https://github.com/ATM-HSW/libThingSpeak/blob/master/README.md
