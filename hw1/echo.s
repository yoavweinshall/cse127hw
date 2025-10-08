  .section .rodata

error_message:
  # Constant holding the message string to print.
  .ascii "This command expects exactly one argument."

new_line:
 .ascii "\n"

.section .text

.globl _start

error:
  movl $error_message, %ecx
  movl $42, %edx
  ret

one_arg:
  movl 12(%esp), %ebx
  movl %ebx, %edi

  # compute the length of the argument to the function
  count_length:
    cmpb $0, (%edi)
    je end_str
    incl %edi
    jmp count_length
  end_str:
   subl %ebx, %edi
  
  movl %ebx, %ecx
  movl %edi, %edx
  ret

_start:

  mov (%esp), %eax
  cmp $2, %eax
  je set_print_arg
  jmp set_error_message  

  set_error_message:
    call error
    movl $2, %ebx
    jmp print
 
  set_print_arg:
    call one_arg
    movl $1, %ebx

   

  ## Print message to standard output.
  print:
    movl  $4, %eax
    # Select the 'sys_write' syscall.
    # ===============================
    # The value in %eax determines which syscall the kernel will execute when
    # interrupt 0x80 is triggered by our code.


    int   $0x80
    # Invoke the syscall and print the message string.
    # ===================
    # This triggers interrupt number 0x80, which the Linux kernel intercepts to
    # run the syscall we select in the %eax register, using the %ebx-%edx
    # registers as its arguments.
    

    ##print new line
    movl $4, %eax
    movl $new_line, %ecx
    movl $1, %edx
    int $0x80

    ## Exit the program with code 0 (success).
    movl  $1, %eax      # Select the 'sys_exit' syscall
    sub $1, %ebx
    int   $0x80         # Invoke the syscall
