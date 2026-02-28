# ⚙️ asm-v0.2 - Full Machine Code-Mnemonic Mapping
-  All machine code instructions are now mapped to their Assembly Language mnemonics.
-  Temporal Control Added
-  Arithmetic operations can now be held for a specified number of clock cycles.
-  Hardware Arithmetic Enabled
- All arithmetic operations supported by the hardware can now be executed symbolically.
-  Full Control
- Assembly programs can now fully control machine behavior using mnemonic-based instructions.

<p align="center">
  <img src="images/machine-code-output.png" 
       alt="asmv0.2 Machine Code Output" width="600"/>
  <br>
  <sub><b>💾 asmv0.2 - Machine Code Output and Mnemonic Mapping</b></sub>
</p>

## 🔡 Machine Code -> Mnemonic Mapping
- Mnemonic 1: LOAD-S-XXXX
   - As opposed to LOAD mnemonic of v0.1, this LOAD handles data loading onto lines as well as Storing the data, so no need for seperate STORE instruction.
   - S (Selector)
     - 0 = Register A
     - 1 = Register B
   - XXXX (Data Bits)
     - XXXX Corresponds to value 1, 2, 4, 8 respectively.
   - asm-v0 bit indexing convention:-
     - Bit 0 is MSB (weight 8)
     - Bit 3 is LSB (weight 1)
   - Instruction Data Field Layout:-
     - index  -> [3] [2] [1] [0]
     - weight ->  1   2   4   8 
  
- Mnemonic 2: FBK
   - Feeds back the output into Register A, overriding its contents.

- Mnemonic 3: ADD
   - It is the default arithmetic operation of the machine, hence no machine code required
   - For consistency in thinking through a program this mnemonic have been made, but it ouputs "DEFAULT ARITHMETIC OPERATION"

- Mnemonic 4: SUB
   - Subtracts the data in Register A from Register B.

- Mnemonic 5: DIV
   - Divides the data in Register A from Register B.

- Mnemonic 6: MUL-XXXX
  - Multiplies the data in register B from selected ( Multiplier(XXXX) - 1 ), XXXX -> 1, 2, 4, 8, thus 0010 corresponds to multiplier (4 - 1) -> 3.
 
- Mnemonic 7: OVRD
   - Overrides the system halt due to overflow errors.

- Mnemonic 8: RSTM
   - Resets the entire machine, and takes all the registers and lines to 0 state.

- Mnemonic 9: HOLD-OP
   - Keeps the result of an arithmetic operation on the output lines for a given number of clock cycles.
   - It is crucial for synchronizing hardware behaviour
   - As already stated the default operation of our machine is Addition so after the machine code instruction for SUB, DIV or MUL is executed the result at the output is ADD not of the desired operation.
   - Hence there is a need for holding the result before the default operation takes over, so we use HOLD-OP, it asks for number of clock cycles for which output has to be on hold, and generate the machine code accordingly.
   - For correct operation especially in cases of MUL and DIV the HOLD-OP should be sustained for atleast the value of (multiplier+1) clock cycles and the value of quotient clock cycles.

## 🧾Summary
- This version mapped the entire machine functionality from machine code instructions to Assembly languauge instructions.
- Easier reasoning about logic and data-flow
- Less manual error when encoding binary instructions
- Acts as a bridge between human logic and hardware signal execution.
