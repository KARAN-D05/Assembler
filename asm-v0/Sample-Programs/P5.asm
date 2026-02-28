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

---------------------------------------------------
# EXECUTION TRACE
---------------------------------------------------

Initial State:
A = 0001 (8)
B = 0010 (4)
Output = 0000 (0)

----------------------------------------------------
1) ADD  (Default Operation)
----------------------------------------------------

A + B = 8 + 4 = 12
Binary Output = 0011 (12)

----------------------------------------------------
2) FBK  (Feedback)
----------------------------------------------------

Register A ← 0011 (12)

Current State:
A = 0011 (12)
B = 0010 (4)

----------------------------------------------------
3) ADD
----------------------------------------------------

A + B = 12 + 4 = 16
Binary Output = 00001 (16)

(5-bit result exceeds 4-bit register width)

----------------------------------------------------
Overflow Detection
----------------------------------------------------

Since the result occupies the 5th bit,
it cannot be stored within the 4-bit register width
with feedback.

Overflow Condition Triggered.

System Response:
- Overflow Detection Logic Activated
- Clock Disengaged
- System Halted
- LEDs ON:
    • Clock Disengaged
    • System Halted
    • Feedback Overflow

Architectural State Preserved.

----------------------------------------------------
4) HOLD-OP
----------------------------------------------------

Output held constant at:
00001 (16)

System remains halted until override.

----------------------------------------------------
5) OVRD  (Override)
----------------------------------------------------

Clock Re-enabled.
System resumes from halted state.

----------------------------------------------------
6) FBK
----------------------------------------------------

Feedback attempts to store output into Register A.

Since only lower 4 bits can be stored:

00001 → 0000 (lower 4 bits)

Register A ← 0000 (0)

Current State:
A = 0000 (0)
B = 0010 (4)

Subsequent Default ADD:
A + B = 0 + 4 = 4
Binary Output = 0010 (4)

----------------------------------------------------
Final System State
----------------------------------------------------

Register A = 0000 (0)
Register B = 0010 (4)
Output     = 0010 (4)

Overflow condition was overridden.
Computation integrity lost after OVRD.
System running normally.
----------------------------------------------------

// It is advised to Use asm-v0.3 Standard Assembler:-
// Features like Syntax and Semantic Analysis.
// Output Error Statements indicating the error.
// Compatible with asm-v0.2 standard.
