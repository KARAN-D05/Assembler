// asm-v0 bit indexing convention:-
// Bit 0 is MSB (weight 8)
// Bit 3 is LSB (weight 1)

// Instruction Data Field Layout:-
// Index  -> [3] [2] [1] [0]
// Weight ->  1   2   4   8

// Program Follows asm-v0.2 Standard (No STORE mnemonic, abstracted away with LOAD-S-XXXX mnemonic - Load Data on lines and also store them in the register.)
// Will Run in asm-v0.2 and asm-v0.3 standard assembler

LOAD-1-0100 // Load 0100(2) in Register B (Stores Multiplicand)
MUL-0010    // Multiply the Multiplicand in Register B from the ( Multiplier - 1 ) -> 3
HOLD-OP     // Hold operation/output for arbitrary number of clock cycles then back to Default ADD operation
            // HOLD-OP should be sustained for atleast the value of (Multiplier + 1) cycles for result to appear on Output lines

# OUTPUT -> Multiplicative Convergance LED will turn ON once the Machine have settled in a stable state indicating successful computation -> 6 (0110)

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

1) LOAD-1-0100
   Register B ← 0100 (2)
   (Multiplicand stored in Register B)

   Current State:
   A = 0000 (0)
   B = 0100 (2)

----------------------------------------------------
2) MUL-0010
----------------------------------------------------

Multiplier Field = 0010 (4)
Effective Multiplication = B × (Multiplier - 1)
                         = 2 × 3

Since multiplication is sequential in hardware,
the system performs repeated addition / convergence
across multiple clock cycles until the final product stabilizes.

Intermediate Convergence:

Cycle 1: 2
Cycle 2: 2 + 2 = 4
Cycle 3: 4 + 2 = 6

Final Product = 6

Binary Output = 0110 (6)

Multiplicative Convergence LED → ON
(Indicates product stabilization and completion of multiplication cycle)

----------------------------------------------------
3) HOLD-OP
----------------------------------------------------

Output held constant at:
0110 (6)

HOLD-OP must be sustained for at least
(Multiplier + 1) clock cycles to allow
full convergence and stable output visibility.

After HOLD duration expires:
System automatically returns to Default Operation (ADD).
But MUL Output remains stable after HOLD-OP as multiplication
is implemented using repeated Addition using Register A and B.

----------------------------------------------------
Final System State
----------------------------------------------------

Register A = 0000 (0)
Register B = 0100 (2)
Output     = 0110 (6)

Multiplicative Convergence LED = ON
System Stable.
Clock continues normally.
----------------------------------------------------

// It is advised to Use asm-v0.3 Standard Assembler:-
// Features like Syntax and Semantic Analysis.
// Output Error Statements indicating the error.
// Compatible with asm-v0.2 standard.
