// asm-v0.3, No STORE mnemonic, abstracted away with LOAD-S-XXXX mnemonic - Load Data on lines and also store them in the register.

LOAD-0-0011 // Load 0011 in Register A
LOAD-1-1000 // Load 1000 in Register B
ADD // ADD Data in Register A and B
FBK // Feedback output back to input (Register A)
SUB // Subtract Data in Register A and B
HOLD-OP // Hold operation/output for arbitrary number of clock cycles
