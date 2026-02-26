// asm-v0.2, No STORE mnemonic, abstracted away with LOAD-S-XXXX mnemonic - Load Data on lines and also store them in the register.
// asm-v0.2 follows Big-Endian format, hence XXXX corresponds to 1 2 4 8.

LOAD-0-0110 // Load 0110(6) in Register A
LOAD-1-0001 // Load 0001(8) in Register B
ADD         // ADD Data in Register A and B
FBK         // Feedback output back to input (Register A)
SUB         // Subtract Data in Register A and B
HOLD-OP     // Hold operation/output for arbitrary number of clock cycles then back to Default ADD operation

// OUTPUT -> 0110(6) for FBK(A)-B, on output lines for HOLD-OP number of cycles, after that back to Default ADD operation as 01101(22).
