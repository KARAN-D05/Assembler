# asm-v0.3 - Syntax & Primitive Semantic Analysis

## 🧩 Overview
- In this version, the assembler evolves from a simple instruction-to-machine-code translator into an early-stage compiler system capable of performing syntax validation and primitive semantic checks.
- The assembler now ensures that every assembly instruction follows valid structural rules (syntax) and that operations occur in a meaningful order (basic semantics).

## ⚙️ Key Features
1. 🧾 Syntax Analysis
  - Each instruction is validated for correct structure and formatting before translation.
  - Detects and reports malformed mnemonics such as:
      - Invalid LOAD structure e.g. missing -S-XXXX pattern.
      - Non-binary selector or data bits.
      - Incorrect instruction length for MUL or other variable-length mnemonics.

<p align="center">
  <img src="images/syntax_analysis1.png" 
       alt="asmv0.3 Syntax Analysis 1" width="600"/>
  <br>
  <sub><b>🔍 Syntax Analysis - v0.3</b></sub>
</p>
   
2. 🧮 Primitive Semantic Analysis
  - Checks for logical execution order (e.g. preventing arithmetic operations before any data load).
  - Detects invalid machine states (e.g. system reset or override at incorrect times).
  - Ensures the assembler halts with descriptive error messages.
    
   <p align="center">
  <img src="images/semantic_analysis.png" 
       alt="asmv0.3 Semantic Analysis" width="600"/>
  <br>
  <sub><b>🕵️ Semantic Analysis - v0.3</b></sub>
</p>

3. 🧠 Enhanced Error Reporting
  - Distinct syntax and semantic error messages.
  - Clear differentiation between invalid syntax and invalid semantics.

<p align="center">
  <img src="images/syntax_analysis3.png" 
       alt="asmv0.3 Syntax Analysis 3" width="600"/>
  <br>
  <sub><b>🔍 Syntax Analysis</b></sub>
</p>

4. 🔸Detects No Input
   
  <p align="center">
  <img src="images/asmv0.3_no_input.png" 
       alt="asmv0.3 No Input Screen" width="600"/>
  <br>
  <sub><b>🖥️ asmv0.3 - No Input Screen</b></sub>
</p>

5. 🧾 Instruction Execution Report
   
<p align="center">
  <img src="images/asmv0.3_output.png" 
       alt="asmv0.3 Assembler Output" width="600"/>
  <br>
  <sub><b>💾 asmv0.3 - Assembler Output with Instruction Execution Report</b></sub>
</p>
