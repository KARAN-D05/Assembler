// asm-v0 bit indexing convention:-
// Bit 0 is MSB (weight 8)
// Bit 3 is LSB (weight 1)

// Instruction Data Field Layout:-
// Index  -> [3] [2] [1] [0]
// Weight ->  1   2   4   8

// Program Follows asm-v0.2 Standard (No STORE mnemonic, abstracted away with LOAD-S-XXXX mnemonic - Load Data on lines and also store them in the register.)
// Will Run in asm-v0.2 and asm-v0.3 standard assembler

LOAD-0-0010 // Load 0010(4) in Register B
LOAD-1-0001 // Load 0001(8) in Register A
ADD         // A + B, Default Operation
FBK         // Feed output back to A
ADD         // A + B, Default Operation
FBK         // Feed output back to A
HOLD-OP     // Hold operation/output
OVRD        // Override System Halt
FBK         // Feed output back to A

# Execution Trace:

Initial:
A = 8
B = 4

After 1st ADD:
Output = 12

After FBK:
A = 12
B = 4

After 2nd ADD:
Output = 16 (Overflow)

System Response:
- Overflow detected
- Clock disengaged
- System halted
- LEDs: Clock Disengaged, Halted, Feedback Overflow ON

After OVRD:
System resumes
Feedback proceeds (computation corrupted)


// It is advised to Use asm-v0.3 Standard Assembler:-
// Features like Syntax and Semantic Analysis.
// Output Error Statements indicating the error.
// Compatible with asm-v0.2 standard.
