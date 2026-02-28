// asm-v0 bit indexing convention:-
// Bit 0 is MSB (weight 8)
// Bit 3 is LSB (weight 1)

// Instruction Data Field Layout:-
// Index  -> [3] [2] [1] [0]
// Weight ->  1   2   4   8

// Program Follows asm-v0.2 Standard (No STORE mnemonic, abstracted away with LOAD-S-XXXX mnemonic - Load Data on lines and also store them in the register.)

LOAD-0-0111 // Load 0111(14) on Data Lines and Store in Register A
LOAD-1-0100 // Load 0100(2) on Data Lines and Store in Register B
DIV         // Divide the Data in Register A from Data in Register B
HOLD-OP     // Hold operation/output for arbitrary number of clock cycles then back to Default ADD operation
            // HOLD-OP should be sustained for atleast the value of quotient clock cycles for result to appear on Output lines

// Output -> Divisibility Convergance LED will turn ON once the Machine have settled in a stable state indicating successful computation -> 7 (1110)
