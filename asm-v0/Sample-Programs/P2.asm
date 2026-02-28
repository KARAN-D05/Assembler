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

# OUTPUT -> 0110(6) for FBK(A)-B, on output lines for HOLD-OP number of cycles, after that back to Default ADD operation as 01101(22).

// It is advised to Use asm-v0.3 Standard Assembler:-
// Features like Syntax and Semantic Analysis.
// Output Error Statements indicating the error.
// Compatible with asm-v0.2 standard.
