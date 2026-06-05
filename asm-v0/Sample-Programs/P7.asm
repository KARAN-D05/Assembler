// asm-v0 bit indexing convention:-
// Bit 0 is MSB (weight 8)
// Bit 3 is LSB (weight 1)

// Instruction Data Field Layout:-
// Index  -> [3] [2] [1] [0]
// Weight ->  1   2   4   8

// Program Follows asm-v0.2 Standard (No STORE mnemonic, abstracted away with LOAD-S-XXXX mnemonic - Load Data on lines and also store them in the register.)
// Will Run in asm-v0.2 and asm-v0.3 standard assembler

LOAD-1-0100 // Load 0100(2) in Register B (Stores Constant Increment)
LOAD-0-0000 // Load 0000(0) in Register A
ADD         // 0 + 2 = 2
FBK         // Feed output back to Register A
ADD         // 2 + 2 = 4
FBK         // Feed output back to Register A
ADD         // 4 + 2 = 6
FBK         // Feed output back to Register A
ADD         // 6 + 2 = 8
FBK         // Feed output back to Register A
ADD         // 8 + 2 = 10
FBK         // Feed output back to Register A
ADD         // 10 + 2 = 12
FBK         // Feed output back to Register A
ADD         // 12 + 2 = 14
FBK         // Feed output back to Register A
ADD         // 14 + 2 = 16

---------------------------------------------------
# EXECUTION TRACE
---------------------------------------------------
Initial State:
A = 0000 (0)
B = 0000 (0)
Output = 0000 (0)

---------------------------------------------------
Program Execution (asm-v0.3.1)
---------------------------------------------------

1. LOAD-1-0100
   Register B ← 0100 (2)
   (Stores Constant Increment)

2. LOAD-0-0000
   Register A ← 0000 (0)

Current State:
A = 0000 (0)
B = 0100 (2)

---------------------------------------------------
3. ADD
---------------------------------------------------
A + B = 0 + 2 = 2
Output = 0100 (2)

---------------------------------------------------
4. FBK
---------------------------------------------------
Register A ← 0100 (2)
Current State:
A = 0100 (2)
B = 0100 (2)

---------------------------------------------------
5. ADD
---------------------------------------------------
A + B = 2 + 2 = 4
Output = 0010 (4)

---------------------------------------------------
6. FBK
---------------------------------------------------
Register A ← 0010 (4)
Current State:
A = 0010 (4)
B = 0100 (2)

---------------------------------------------------
7. ADD
---------------------------------------------------
A + B = 4 + 2 = 6
Output = 0110 (6)

---------------------------------------------------
8. FBK
---------------------------------------------------
Register A ← 0110 (6)
Current State:
A = 0110 (6)
B = 0100 (2)

---------------------------------------------------
9. ADD
---------------------------------------------------
A + B = 6 + 2 = 8
Output = 0001 (8)

---------------------------------------------------
10. FBK
---------------------------------------------------
Register A ← 0001 (8)
Current State:
A = 0001 (8)
B = 0100 (2)

---------------------------------------------------
11. ADD
---------------------------------------------------
A + B = 8 + 2 = 10
Output = 0101 (10)

---------------------------------------------------
12. FBK
---------------------------------------------------
Register A ← 0101 (10)
Current State:
A = 0101 (10)
B = 0100 (2)

---------------------------------------------------
13. ADD
---------------------------------------------------
A + B = 10 + 2 = 12
Output = 0011 (12)

---------------------------------------------------
14. FBK
---------------------------------------------------
Register A ← 0011 (12)
Current State:
A = 0011 (12)
B = 0100 (2)

---------------------------------------------------
15. ADD
---------------------------------------------------
A + B = 12 + 2 = 14
Output = 0111 (14)

---------------------------------------------------
16. FBK
---------------------------------------------------
Register A ← 0111 (14)
Current State:
A = 0111 (14)
B = 0100 (2)

---------------------------------------------------
17. ADD
---------------------------------------------------
A + B = 14 + 2 = 16
Output = 00001 (16)

---------------------------------------------------
No Feedback Operation Invoked.
Output remains valid on Output Lines.
Overflow Detection Logic remains inactive
since no attempt is made to store the
5-bit result into a 4-bit register.

---------------------------------------------------
## Final System State
---------------------------------------------------
Register A = 0111 (14)
Register B = 0100 (2)
Output     = 00001 (16)
---------------------------------------------------

Generated Sequence:
2 → 4 → 6 → 8 → 10 → 12 → 14 → 16
Arithmetic Progression Generated Successfully.
Common Difference = 2

Equivalent Multiplication Table:
2×1 = 2
2×2 = 4
2×3 = 6
2×4 = 8
2×5 = 10
2×6 = 12
2×7 = 14
2×8 = 16

---------------------------------------------------
System Stable
---------------------------------------------------
