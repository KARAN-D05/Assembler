// asm-v0 bit indexing convention:-
// Bit 0 is MSB (weight 8)
// Bit 3 is LSB (weight 1)

// Instruction Data Field Layout:-
// Index  -> [3] [2] [1] [0]
// Weight ->  1   2   4   8

// asm-v0.1 has seperate instructions for bringing Data on the Line (LOAD-S-XXXX) and then storing it (STORE)
// Will Only Run in asm-v0.1 standard assembler

LOAD-0-1001 // Load 1001(9) on Data Lines
STORE       // Store data in Register A
LOAD-1-1100 // Load 1100(3) on Data Lines
STORE       // Store data in Register B

// asm-v0.2, No STORE mnemonic, abstracted away with LOAD-S-XXXX mnemonic - Load Data on lines and also store them in the register.
// Will Run in asm-v0.2 and asm-v0.3 standard assembler

LOAD-0-1001 // Load 1001(9) on Data Lines and Store in Register A
LOAD-1-1100 // Load 1100(3) on Data Lines and store in Register B

----------------------------------------------------
# EXECUTION TRACE                                  
----------------------------------------------------

Initial State:
A = 0000 (0)
B = 0000 (0)
Output = 0000 (0)

----------------------------------------------------
asm-v0.1 Execution (LOAD + STORE separated)
----------------------------------------------------

1) LOAD-0-1001
   Data Lines ← 1001 (9)

2) STORE
   Register A ← 1001 (9)

   Current State:
   A = 1001 (9)
   B = 0000 (0)

3) LOAD-1-1100
   Data Lines ← 1100 (3)

4) STORE
   Register B ← 1100 (3)

   Current State:
   A = 1001 (9)
   B = 1100 (3)

----------------------------------------------------
asm-v0.2 / asm-v0.3 Execution (STORE abstracted)
----------------------------------------------------

1) LOAD-0-1001
   Register A ← 1001 (9)

2) LOAD-1-1100
   Register B ← 1100 (3)

   Current State:
   A = 1001 (9)
   B = 1100 (3)

----------------------------------------------------
Arithmetic Operation
----------------------------------------------------

Default Operation: ADD

A + B = 9 + 3 = 12
Binary Output = 0011 (12)

----------------------------------------------------
Final System State
----------------------------------------------------

Register A = 1001 (9)
Register B = 1100 (3)
Output     = 0011 (12)

No overflow occurs.
No error detection triggered.
Clock continues normally.
----------------------------------------------------

// It is advised to Use asm-v0.3 Standard Assembler:-
// Features like Syntax and Semantic Analysis.
// Output Error Statements indicating the error.
// Compatible with asm-v0.2 standard.
