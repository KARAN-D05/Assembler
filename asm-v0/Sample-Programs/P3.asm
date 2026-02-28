// asm-v0 bit indexing convention:-
// Bit 0 is MSB (weight 8)
// Bit 3 is LSB (weight 1)

// Instruction Data Field Layout:-
// Index  -> [3] [2] [1] [0]
// Weight ->  1   2   4   8

// Program Follows asm-v0.2 Standard (No STORE mnemonic, abstracted away with LOAD-S-XXXX mnemonic - Load Data on lines and also store them in the register.)
// Will Run in asm-v0.2 and asm-v0.3 standard assembler

LOAD-0-0111 // Load 0111(14) on Data Lines and Store in Register A
LOAD-1-0100 // Load 0100(2) on Data Lines and Store in Register B
DIV         // Divide the Data in Register A from Data in Register B
HOLD-OP     // Hold operation/output for arbitrary number of clock cycles then back to Default ADD operation
            // HOLD-OP should be sustained for atleast the value of quotient clock cycles for result to appear on Output lines

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

1) LOAD-0-0111
   Register A ← 0111 (14)

2) LOAD-1-0100
   Register B ← 0100 (2)

   Current State:
   A = 0111 (14)
   B = 0100 (2)

----------------------------------------------------
3) DIV
----------------------------------------------------

Operation: A ÷ B
14 ÷ 2 = 7

Since division is iterative in hardware,
the system performs repeated subtraction / convergence
across multiple clock cycles until a stable quotient is reached.

Intermediate Convergence:

Cycle 1: 14 - 2 = 12
Cycle 2: 12 - 2 = 10
Cycle 3: 10 - 2 = 8
Cycle 4: 8  - 2 = 6
Cycle 5: 6  - 2 = 4
Cycle 6: 4  - 2 = 2
Cycle 7: 2  - 2 = 0

Quotient = 7

Binary Output = 1110 (7)

Divisibility Convergence LED → ON
(System has reached stable state)

----------------------------------------------------
4) HOLD-OP
----------------------------------------------------

Output held constant at:
1110 (7)

HOLD-OP must be sustained for at least
the number of quotient clock cycles to allow
full convergence and stable output.

After HOLD duration expires:
System automatically returns to Default Operation (ADD)
but Division Output stays as they are shown on seperate 
output lines.

----------------------------------------------------
Final System State
----------------------------------------------------

Register A = 0111 (14)
Register B = 0100 (2)
Output     = 1110 (7)

Divisibility Convergence LED = ON
System Stable.
Clock continues normally.
--------------------------------------------------

// It is advised to Use asm-v0.3 Standard Assembler:-
// Features like Syntax and Semantic Analysis.
// Output Error Statements indicating the error.
// Compatible with asm-v0.2 standard.
