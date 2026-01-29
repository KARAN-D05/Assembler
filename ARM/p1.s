.global _start // starting point of label
_start: // label
	
	mov r0,#30 // #30 -> Decimal, Hex -> #0x0A
	mov r7,#1 // r7 -> stores system interrupts, #1-> exit
	swi 0 // software interrupt -> lets OS take over to read r7 and compare against a lookup table