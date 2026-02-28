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

# OUTPUT -> This Program will load 1001 (9) in Register A and 1100(3) in Register B. At Output we will see A + B = 0011(12) as ADD is default Arithmetic Operation.

// It is advised to Use asm-v0.3 Standard Assembler:-
// Features like Syntax and Semantic Analysis.
// Output Error Statements indicating the error.
// Compatible with asm-v0.2 standard.
