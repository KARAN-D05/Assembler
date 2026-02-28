// asm-v0 bit indexing convention:-
// Bit 0 is MSB (weight 8)
// Bit 3 is LSB (weight 1)

// Instruction Data Field Layout:-
// Index  -> [3] [2] [1] [0]
// Weight ->  1   2   4   8

// Program Follows asm-v0.2 Standard (No STORE mnemonic, abstracted away with LOAD-S-XXXX mnemonic - Load Data on lines and also store them in the register.)

LOAD-1-0100 // Load 0100(2) in Register B (Stores Multiplicand)
MUL-0010    // Multiply the Multiplicand in Register B from the ( Multiplier - 1 ) -> 3
HOLD-OP     // Hold operation/output for arbitrary number of clock cycles then back to Default ADD operation
            // HOLD-OP should be sustained for atleast the value of (Multiplier + 1) cycles for result to appear on Output lines

# OUTPUT -> Multiplicative Convergance LED will turn ON once the Machine have settled in a stable state indicating successful computation -> 6 (0110)
