```
AARCH64 GAS  main.s 			page 1


   1              		.arch	armv8-a
   2              		.file	"main.s"
   3              	
   4              		.text
   5              		.align	2
   6              		.global main
   7              	
   8              	main:
   9 0000 F57BBFA9 		stp		x21, x30, [sp, -16]!	
  10 0004 A0000058 		ldr		x0,=s
  11 0008 00000094 		bl		puts
  12              	
  13 000c E0031FAA 		mov		x0, xzr	
  14 0010 F57BC1A8 		ldp		x21, x30, [sp], 16	
  15 0014 C0035FD6 		ret
  16              	
  17              		.data
  18 0000 68656C6C 	s:	.asciz	"hello, world"
  18      6F2C2077 
  18      6F726C64 
  18      00
  19              		.end

AARCH64 GAS  main.s 			page 2


DEFINED SYMBOLS
                            *ABS*:0000000000000000 main.s
              main.s:5      .text:0000000000000000 $x
              main.s:8      .text:0000000000000000 main
              main.s:18     .data:0000000000000000 s
              main.s:19     .text:0000000000000018 $d

UNDEFINED SYMBOLS
puts
```
