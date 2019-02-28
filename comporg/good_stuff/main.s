		.text
		.global		main
		.align		2

		.equ		BOX_WIDTH, 0
		.equ		BOX_HEIGHT, 4
		.equ		BOX_DEPTH, 8
		.equ		BOX_SIZEOF, 12
		
		.equ		BOX_VOLUME, 0
		.equ		BOX_PRINT, 1

main:	stp			x19, x30, [sp, -16]!
		
		ldr			x0, =box
		mov			x1, BOX_VOLUME
		ldr			x2, =BoxJumpTable
		ldr			x2, [x2, x1, lsl 3]
		blr			x2
		mov			x1, x0
		ldr			x0, =bv
		bl			printf

		ldr			x0, =box
		mov			x1, BOX_PRINT
		ldr			x2, =BoxJumpTable
		ldr			x2, [x2, x1, lsl 3]
		blr			x2

		mov			x0, xzr
		ldp			x19, x30, [sp], 16
		ret

/*		int Box::BoxVolume(this)

		Returns in x0, the box's volume.
*/	
BoxVolume:
		ldr			w1, [x0, BOX_WIDTH]
		ldr			w2, [x0, BOX_HEIGHT]
		mul			w1, w1, w2
		ldr			w2, [x0, BOX_DEPTH]
		mul			w1, w1, w2
		mov			w0, w1		
		ret

/*		void Box::Print(this)

		Prints the box's width, height and depth.
*/
BoxPrint:
		str			x30, [sp, -16]!
		mov			x4, x0
		ldr			x0, =bp
		ldr			w1, [x4, BOX_WIDTH]
		ldr			w2, [x4, BOX_HEIGHT]
		ldr			w3, [x4, BOX_DEPTH]
		bl			printf
		ldr			x30, [sp], 16
		ret

		.data

		.align	8
BoxJumpTable:
		.quad	BoxVolume
		.quad	BoxPrint
		.quad	0

bp:		.asciz		"Box width: %d height: %d depth: %d\n"
bv:		.asciz		"Box volume: %d\n"

		.align	2
box:	.word	10
		.word	5
		.word	1


/*
		.macro		HW, label
		ldr			x0, =\label
		bl			puts
		.endm


		add 		x1, x1, #ADDR_SIZE
		tbz			x0, 0, good
		ldr			x0, =s
		bl			puts
		HW			h
*/
		.end

