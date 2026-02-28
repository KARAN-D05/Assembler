// asm-v0 bit indexing convention:-
// Bit 0 is MSB (weight 8)
// Bit 3 is LSB (weight 1)

// Instruction Data Field Layout:-
// index  -> [3] [2] [1] [0]
// weight ->  1   2   4   8

// Program follows asm-v0.2 standard, No STORE mnemonic, abstracted away with LOAD-S-XXXX mnemonic - Load Data on lines and also store them in the register.
// Will Run in asm-v0.2 and asm-v0.3 standard assembler

LOAD-0-0110 // Load 0110(6) in Register A
LOAD-1-0001 // Load 0001(8) in Register B
ADD         // ADD Data in Register A and B
FBK         // Feedback output back to input (Register A)
SUB         // Subtract Data in Register A and B
HOLD-OP     // Hold operation/output for arbitrary number of clock cycles then back to Default ADD operation

---------------------------------------------------
# EXECUTION TRACE
---------------------------------------------------

Initial State:
A = 0000 (0)
B = 0000 (0)
Output = 0000 (0)

----------------------------------------------------
Program Execution (asm-v0.2 / asm-v0.3)
----------------------------------------------------

1) LOAD-0-0110
   Register A ← 0110 (6)

2) LOAD-1-0001
   Register B ← 0001 (8)

   Current State:
   A = 0110 (6)
   B = 0001 (8)

----------------------------------------------------
3) ADD  (Default Operation)
----------------------------------------------------

A + B = 6 + 8 = 14
Binary Output = 0111 (14)

----------------------------------------------------
4) FBK  (Feedback)
----------------------------------------------------

Register A ← 0111 (14)

   Current State:
   A = 0111 (14)
   B = 0001 (8)

----------------------------------------------------
5) SUB
----------------------------------------------------

A - B = 14 - 8 = 6
Binary Output = 0110 (6)

----------------------------------------------------
6) HOLD-OP
----------------------------------------------------

Output held constant at:
0110 (6)

The value remains on the output lines for the specified
number of clock cycles.

After HOLD duration expires:
System automatically returns to Default Operation (ADD).

----------------------------------------------------
Post-HOLD Default ADD
----------------------------------------------------

A + B = 14 + 8 = 22
Binary Output = 01101 (22)

----------------------------------------------------
Final System State
----------------------------------------------------

Register A = 0111 (14)
Register B = 0001 (8)
Output during HOLD = 0110 (6)
Post-HOLD Output   = 01101 (22)

---------------------------------------------------

// It is advised to Use asm-v0.3 Standard Assembler:-
// Features like Syntax and Semantic Analysis.
// Output Error Statements indicating the error.
// Compatible with asm-v0.2 standard.
