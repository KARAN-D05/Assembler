// asm-v0 bit indexing convention:-
// Bit 0 is MSB (weight 8)
// Bit 3 is LSB (weight 1)

// Instruction Data Field Layout:-
// Index  -> [3] [2] [1] [0]
// Weight ->  1   2   4   8

// Program Follows asm-v0.2 Standard (No STORE mnemonic, abstracted away with LOAD-S-XXXX mnemonic - Load Data on lines and also store them in the register.)
// Will Run in asm-v0.2 and asm-v0.3 standard assembler

LOAD-1-1000 // Load 1000(1) in Register A
LOAD-0-0010 // Load 0010(4) in Register B
ADD         // A + B
RSTM        // Clears the Machine

---------------------------------------------------
# EXECUTION TRACE
---------------------------------------------------

Initial State:
A = 0000 (0)
B = 0000 (0)
Output = 0000 (0)

----------------------------------------------------
1) LOAD-1-1000
----------------------------------------------------

Register A ← 1000 (1)

Current State:
A = 1000 (1)
B = 0000 (0)

----------------------------------------------------
2) LOAD-0-0010
----------------------------------------------------

Register B ← 0010 (4)

Current State:
A = 1000 (1)
B = 0010 (4)

----------------------------------------------------
3) ADD  (Default Operation)
----------------------------------------------------

A + B = 1 + 4 = 5
Binary Output = 1010 (5)

Current State:
A = 1000 (1)
B = 0010 (4)
Output = 1010 (5)

----------------------------------------------------
4) RSTM  (Reset Machine)
----------------------------------------------------

Machine Reset Triggered.

All Registers Cleared:
A = 0000 (0)
B = 0000 (0)

All Output Lines Cleared:
Output = 0000 (0)

All Control Flags Cleared:
- Overflow = OFF
- Convergence LEDs = OFF
- Halt State = Cleared

Clock continues in normal reset state.

----------------------------------------------------
Final System State
----------------------------------------------------

Register A = 0000 (0)
Register B = 0000 (0)
Output     = 0000 (0)

Machine fully reset.
----------------------------------------------------

// It is advised to Use asm-v0.3 Standard Assembler:-
// Features like Syntax and Semantic Analysis.
// Output Error Statements indicating the error.
// Compatible with asm-v0.2 standard.
