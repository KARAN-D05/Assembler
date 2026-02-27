# ⚙️ Assembler
- This is an extension to my [Computing Machinery from Scratch](https://github.com/KARAN-D05/Computing_Machinery_from_Scratch) project, after building an advanced arithmetic machine (called Repeated  Arithmetic Machine aka r_a_m) and in version4 (r_a_mv4) we succesfully implemented 
**Machine-Code Programming** by storing machine code instructions in the program memory.
- So next logical step was to go up the computing stack from machine code to language having instructions in an english like language, called Mnemonics, so after mapping all the machine codes to
 mnemonics we get -**The Assembly Language**.

<p align="center">
  <img src="asm-v0/asm-v0.2/images/machine-code-output.png" alt="Machine Code Output v0.2" width="600"/>
  <br>
  <sub><b>🧾 Machine Code Output - Assembler v0.2</b></sub>
</p>

## ⚙️ Implementation Stack
![Python](https://img.shields.io/badge/Python-00B0FF?style=for-the-badge)
![Custom Assembly](https://img.shields.io/badge/Custom%20Assembly-D50000?style=for-the-badge)

## 🧱 Versions Built
- [asmv0.1](asm-v0/asm-v0.1) -> Mapped Data control operations to assembly Language.
- [asmv0.2](asm-v0/asm-v0.2) -> Mapped arithmetic, system and temporal Control to assembly Language.
- [asmv0.3](asm-v0/asm-v0.3) -> Added Syntax Analysis, primitive semantic analysis and an instruction execution report.

<!DOCTYPE html>
<html lang="en">
<head>
<meta charset="UTF-8">
<meta name="viewport" content="width=device-width, initial-scale=1.0">
<title>asm-v0 Instruction Set Reference</title>
<link href="https://fonts.googleapis.com/css2?family=Share+Tech+Mono&family=Orbitron:wght@400;700;900&family=Space+Mono:ital,wght@0,400;0,700;1,400&display=swap" rel="stylesheet">
<style>
  :root {
    --bg: #050a08;
    --surface: #0a1210;
    --surface2: #0f1a17;
    --border: #1a3028;
    --border-bright: #1f4035;
    --green: #00ff88;
    --green-dim: #00c868;
    --green-muted: #005535;
    --amber: #ffaa00;
    --amber-dim: #cc8800;
    --red: #ff4455;
    --cyan: #00d4ff;
    --white: #e8f5f0;
    --muted: #3a6050;
    --scanline: rgba(0,255,136,0.02);
  }

  * { margin: 0; padding: 0; box-sizing: border-box; }

  body {
    background: var(--bg);
    color: var(--white);
    font-family: 'Share Tech Mono', monospace;
    min-height: 100vh;
    overflow-x: hidden;
    position: relative;
  }

  /* Scanline overlay */
  body::before {
    content: '';
    position: fixed;
    inset: 0;
    background: repeating-linear-gradient(
      0deg,
      transparent,
      transparent 2px,
      var(--scanline) 2px,
      var(--scanline) 4px
    );
    pointer-events: none;
    z-index: 1000;
  }

  /* Noise texture */
  body::after {
    content: '';
    position: fixed;
    inset: 0;
    background-image: url("data:image/svg+xml,%3Csvg viewBox='0 0 256 256' xmlns='http://www.w3.org/2000/svg'%3E%3Cfilter id='noise'%3E%3CfeTurbulence type='fractalNoise' baseFrequency='0.9' numOctaves='4' stitchTiles='stitch'/%3E%3C/filter%3E%3Crect width='100%25' height='100%25' filter='url(%23noise)' opacity='0.03'/%3E%3C/svg%3E");
    pointer-events: none;
    z-index: 999;
    opacity: 0.4;
  }

  .container {
    max-width: 1100px;
    margin: 0 auto;
    padding: 0 2rem 4rem;
    position: relative;
    z-index: 1;
  }

  /* ── HEADER ── */
  header {
    padding: 3rem 0 2rem;
    border-bottom: 1px solid var(--border);
    margin-bottom: 3rem;
    position: relative;
  }

  .header-top {
    display: flex;
    align-items: flex-start;
    justify-content: space-between;
    flex-wrap: wrap;
    gap: 1rem;
  }

  .chip-label {
    font-family: 'Orbitron', monospace;
    font-size: 0.6rem;
    font-weight: 700;
    letter-spacing: 0.3em;
    color: var(--green);
    text-transform: uppercase;
    border: 1px solid var(--green-muted);
    padding: 0.3rem 0.8rem;
    background: rgba(0,255,136,0.05);
    animation: pulse-border 3s ease-in-out infinite;
  }

  @keyframes pulse-border {
    0%, 100% { border-color: var(--green-muted); }
    50% { border-color: var(--green); box-shadow: 0 0 8px rgba(0,255,136,0.2); }
  }

  .status-indicator {
    display: flex;
    align-items: center;
    gap: 0.5rem;
    font-size: 0.65rem;
    color: var(--muted);
    letter-spacing: 0.15em;
  }

  .status-dot {
    width: 6px;
    height: 6px;
    border-radius: 50%;
    background: var(--green);
    box-shadow: 0 0 6px var(--green);
    animation: blink 1.4s ease-in-out infinite;
  }

  @keyframes blink {
    0%, 100% { opacity: 1; }
    50% { opacity: 0.2; }
  }

  h1 {
    font-family: 'Orbitron', monospace;
    font-size: clamp(1.8rem, 5vw, 3.2rem);
    font-weight: 900;
    color: var(--green);
    letter-spacing: 0.05em;
    text-shadow: 0 0 30px rgba(0,255,136,0.3), 0 0 60px rgba(0,255,136,0.1);
    margin: 1rem 0 0.4rem;
    line-height: 1.1;
  }

  .subtitle {
    font-size: 0.8rem;
    color: var(--muted);
    letter-spacing: 0.2em;
    text-transform: uppercase;
    margin-bottom: 1.5rem;
  }

  .meta-row {
    display: flex;
    gap: 2rem;
    flex-wrap: wrap;
    margin-top: 1.5rem;
  }

  .meta-item {
    display: flex;
    flex-direction: column;
    gap: 0.2rem;
  }

  .meta-label {
    font-size: 0.55rem;
    letter-spacing: 0.25em;
    color: var(--muted);
    text-transform: uppercase;
  }

  .meta-value {
    font-size: 0.75rem;
    color: var(--amber);
    letter-spacing: 0.1em;
  }

  /* ── BIT CONVENTION BOX ── */
  .convention-box {
    background: var(--surface);
    border: 1px solid var(--border);
    border-left: 3px solid var(--amber);
    padding: 1.2rem 1.5rem;
    margin-bottom: 3rem;
    position: relative;
    overflow: hidden;
  }

  .convention-box::before {
    content: 'BIT CONVENTION';
    position: absolute;
    top: 0.6rem;
    right: 1rem;
    font-size: 0.5rem;
    letter-spacing: 0.3em;
    color: var(--muted);
  }

  .convention-box h3 {
    font-family: 'Orbitron', monospace;
    font-size: 0.6rem;
    letter-spacing: 0.25em;
    color: var(--amber);
    margin-bottom: 0.8rem;
  }

  .bit-grid {
    display: grid;
    grid-template-columns: auto repeat(4, 3rem);
    gap: 0;
    width: fit-content;
    margin: 0.5rem 0;
  }

  .bit-cell {
    border: 1px solid var(--border-bright);
    padding: 0.3rem 0.6rem;
    text-align: center;
    font-size: 0.7rem;
  }

  .bit-cell.header { color: var(--muted); font-size: 0.6rem; background: var(--surface2); }
  .bit-cell.index { color: var(--cyan); }
  .bit-cell.weight { color: var(--amber); font-weight: bold; }
  .bit-cell.label { color: var(--muted); font-size: 0.6rem; border: none; text-align: right; padding-right: 1rem; }

  /* ── SECTION TITLE ── */
  .section-title {
    font-family: 'Orbitron', monospace;
    font-size: 0.6rem;
    font-weight: 700;
    letter-spacing: 0.35em;
    color: var(--muted);
    text-transform: uppercase;
    margin-bottom: 1.5rem;
    display: flex;
    align-items: center;
    gap: 1rem;
  }

  .section-title::after {
    content: '';
    flex: 1;
    height: 1px;
    background: linear-gradient(to right, var(--border), transparent);
  }

  /* ── INSTRUCTION CARDS ── */
  .instructions-grid {
    display: flex;
    flex-direction: column;
    gap: 1px;
    background: var(--border);
    border: 1px solid var(--border);
  }

  .instr-card {
    background: var(--surface);
    display: grid;
    grid-template-columns: 260px 1fr;
    min-height: 80px;
    transition: background 0.15s;
    animation: fadeIn 0.4s ease both;
  }

  .instr-card:hover {
    background: var(--surface2);
  }

  @keyframes fadeIn {
    from { opacity: 0; transform: translateX(-8px); }
    to { opacity: 1; transform: translateX(0); }
  }

  .instr-card:nth-child(1) { animation-delay: 0.05s; }
  .instr-card:nth-child(2) { animation-delay: 0.1s; }
  .instr-card:nth-child(3) { animation-delay: 0.15s; }
  .instr-card:nth-child(4) { animation-delay: 0.2s; }
  .instr-card:nth-child(5) { animation-delay: 0.25s; }
  .instr-card:nth-child(6) { animation-delay: 0.3s; }
  .instr-card:nth-child(7) { animation-delay: 0.35s; }
  .instr-card:nth-child(8) { animation-delay: 0.4s; }
  .instr-card:nth-child(9) { animation-delay: 0.45s; }

  .instr-left {
    padding: 1.2rem 1.5rem;
    border-right: 1px solid var(--border);
    display: flex;
    flex-direction: column;
    justify-content: center;
    gap: 0.4rem;
    position: relative;
  }

  .instr-number {
    font-size: 0.5rem;
    letter-spacing: 0.3em;
    color: var(--muted);
    font-family: 'Orbitron', monospace;
  }

  .instr-mnemonic {
    font-family: 'Space Mono', monospace;
    font-size: 1rem;
    font-weight: 700;
    color: var(--green);
    text-shadow: 0 0 12px rgba(0,255,136,0.25);
    letter-spacing: 0.05em;
    line-height: 1.3;
  }

  .instr-mnemonic .param {
    color: var(--cyan);
  }

  .instr-type-badge {
    display: inline-block;
    font-size: 0.5rem;
    letter-spacing: 0.2em;
    padding: 0.15rem 0.5rem;
    border: 1px solid;
    width: fit-content;
    margin-top: 0.2rem;
  }

  .badge-data { border-color: var(--cyan); color: var(--cyan); }
  .badge-arithmetic { border-color: var(--amber); color: var(--amber); }
  .badge-system { border-color: var(--red); color: var(--red); }
  .badge-temporal { border-color: #aa66ff; color: #aa66ff; }

  .instr-right {
    padding: 1.2rem 1.5rem;
    display: flex;
    flex-direction: column;
    justify-content: center;
    gap: 0.6rem;
  }

  .instr-desc {
    font-size: 0.78rem;
    color: #8ab0a0;
    line-height: 1.6;
  }

  .instr-params {
    display: flex;
    flex-wrap: wrap;
    gap: 0.5rem;
    margin-top: 0.2rem;
  }

  .param-block {
    background: rgba(0,212,255,0.05);
    border: 1px solid rgba(0,212,255,0.15);
    padding: 0.3rem 0.7rem;
    font-size: 0.65rem;
    line-height: 1.5;
  }

  .param-block .param-name {
    color: var(--cyan);
    font-weight: 700;
    letter-spacing: 0.1em;
  }

  .param-block .param-vals {
    color: var(--muted);
  }

  .instr-note {
    font-size: 0.65rem;
    color: var(--amber-dim);
    border-left: 2px solid var(--amber-dim);
    padding-left: 0.7rem;
    margin-top: 0.2rem;
    line-height: 1.5;
    font-style: italic;
  }

  .default-badge {
    display: inline-block;
    background: rgba(0,255,136,0.08);
    border: 1px solid var(--green-muted);
    color: var(--green-dim);
    font-size: 0.5rem;
    letter-spacing: 0.2em;
    padding: 0.1rem 0.5rem;
    margin-left: 0.5rem;
    vertical-align: middle;
  }

  /* ── FOOTER ── */
  footer {
    margin-top: 4rem;
    padding-top: 2rem;
    border-top: 1px solid var(--border);
    display: flex;
    justify-content: space-between;
    align-items: center;
    flex-wrap: wrap;
    gap: 1rem;
  }

  .footer-text {
    font-size: 0.6rem;
    color: var(--muted);
    letter-spacing: 0.15em;
  }

  .footer-link {
    font-size: 0.6rem;
    color: var(--green-dim);
    letter-spacing: 0.15em;
    text-decoration: none;
    border-bottom: 1px solid var(--green-muted);
  }

  /* ── RESPONSIVE ── */
  @media (max-width: 680px) {
    .instr-card {
      grid-template-columns: 1fr;
    }
    .instr-left {
      border-right: none;
      border-bottom: 1px solid var(--border);
      padding-bottom: 0.8rem;
    }
  }
</style>
</head>
<body>
<div class="container">

  <!-- HEADER -->
  <header>
    <div class="header-top">
      <span class="chip-label">⚙ asm-v0 · Instruction Set Reference</span>
      <div class="status-indicator">
        <div class="status-dot"></div>
        ACTIVE · v0.3
      </div>
    </div>

    <h1>INSTRUCTION<br>SET REFERENCE</h1>
    <div class="subtitle">Custom Assembly Language · Repeated Arithmetic Machine</div>

    <div class="meta-row">
      <div class="meta-item">
        <span class="meta-label">Total Mnemonics</span>
        <span class="meta-value">09</span>
      </div>
      <div class="meta-item">
        <span class="meta-label">Implementation</span>
        <span class="meta-value">Python</span>
      </div>
      <div class="meta-item">
        <span class="meta-label">Data Width</span>
        <span class="meta-value">4-bit</span>
      </div>
      <div class="meta-item">
        <span class="meta-label">License</span>
        <span class="meta-value">MIT</span>
      </div>
    </div>
  </header>

  <!-- BIT CONVENTION -->
  <div class="convention-box">
    <h3>▸ asm-v0 Bit Indexing Convention</h3>
    <div class="bit-grid">
      <div class="bit-cell label"></div>
      <div class="bit-cell header">Bit 3</div>
      <div class="bit-cell header">Bit 2</div>
      <div class="bit-cell header">Bit 1</div>
      <div class="bit-cell header">Bit 0</div>

      <div class="bit-cell label">INDEX →</div>
      <div class="bit-cell index">[3]</div>
      <div class="bit-cell index">[2]</div>
      <div class="bit-cell index">[1]</div>
      <div class="bit-cell index">[0]</div>

      <div class="bit-cell label">WEIGHT →</div>
      <div class="bit-cell weight">1</div>
      <div class="bit-cell weight">2</div>
      <div class="bit-cell weight">4</div>
      <div class="bit-cell weight">8</div>
    </div>
    <p style="font-size:0.65rem; color:var(--muted); margin-top:0.8rem;">Bit 0 = MSB (weight 8) &nbsp;·&nbsp; Bit 3 = LSB (weight 1)</p>
  </div>

  <!-- INSTRUCTION TABLE -->
  <div class="section-title">Mnemonic Definitions</div>

  <div class="instructions-grid">

    <!-- 01 LOAD -->
    <div class="instr-card">
      <div class="instr-left">
        <div class="instr-number">MNEMONIC · 01</div>
        <div class="instr-mnemonic">LOAD-<span class="param">S</span>-<span class="param">XXXX</span></div>
        <span class="instr-type-badge badge-data">DATA CONTROL</span>
      </div>
      <div class="instr-right">
        <div class="instr-desc">Loads data onto the bus lines and simultaneously stores it in the selected register. Combines the v0.1 LOAD and STORE into a single atomic instruction.</div>
        <div class="instr-params">
          <div class="param-block">
            <div class="param-name">S — SELECTOR</div>
            <div class="param-vals">0 = Register A &nbsp;|&nbsp; 1 = Register B</div>
          </div>
          <div class="param-block">
            <div class="param-name">XXXX — DATA BITS</div>
            <div class="param-vals">4-bit value · e.g. 0110 = 6, 0001 = 8</div>
          </div>
        </div>
      </div>
    </div>

    <!-- 02 FBK -->
    <div class="instr-card">
      <div class="instr-left">
        <div class="instr-number">MNEMONIC · 02</div>
        <div class="instr-mnemonic">FBK</div>
        <span class="instr-type-badge badge-data">DATA CONTROL</span>
      </div>
      <div class="instr-right">
        <div class="instr-desc">Feeds the current output back into Register A, overriding its existing contents. Enables iterative computation using previous results.</div>
      </div>
    </div>

    <!-- 03 ADD -->
    <div class="instr-card">
      <div class="instr-left">
        <div class="instr-number">MNEMONIC · 03</div>
        <div class="instr-mnemonic">ADD <span class="default-badge">DEFAULT</span></div>
        <span class="instr-type-badge badge-arithmetic">ARITHMETIC</span>
      </div>
      <div class="instr-right">
        <div class="instr-desc">Adds the contents of Register A and Register B. This is the machine's default arithmetic operation — no machine code is emitted. Included as a mnemonic for program clarity and consistency.</div>
        <div class="instr-note">Outputs "DEFAULT ARITHMETIC OPERATION" — the machine returns to ADD automatically after any other operation completes.</div>
      </div>
    </div>

    <!-- 04 SUB -->
    <div class="instr-card">
      <div class="instr-left">
        <div class="instr-number">MNEMONIC · 04</div>
        <div class="instr-mnemonic">SUB</div>
        <span class="instr-type-badge badge-arithmetic">ARITHMETIC</span>
      </div>
      <div class="instr-right">
        <div class="instr-desc">Subtracts the value in Register B from Register A. Result is held momentarily before the machine reverts to default ADD operation — use HOLD-OP to capture output.</div>
      </div>
    </div>

    <!-- 05 DIV -->
    <div class="instr-card">
      <div class="instr-left">
        <div class="instr-number">MNEMONIC · 05</div>
        <div class="instr-mnemonic">DIV</div>
        <span class="instr-type-badge badge-arithmetic">ARITHMETIC</span>
      </div>
      <div class="instr-right">
        <div class="instr-desc">Divides the value in Register A by Register B. As with SUB and MUL, the result must be latched using HOLD-OP before the default ADD operation resumes.</div>
        <div class="instr-note">Sustain HOLD-OP for at least the quotient number of clock cycles for correct output.</div>
      </div>
    </div>

    <!-- 06 MUL -->
    <div class="instr-card">
      <div class="instr-left">
        <div class="instr-number">MNEMONIC · 06</div>
        <div class="instr-mnemonic">MUL-<span class="param">XXXX</span></div>
        <span class="instr-type-badge badge-arithmetic">ARITHMETIC</span>
      </div>
      <div class="instr-right">
        <div class="instr-desc">Multiplies the value in Register B by the selected multiplier encoded in XXXX. The 4-bit operand selects from multipliers 1, 2, 4, or 8.</div>
        <div class="instr-params">
          <div class="param-block">
            <div class="param-name">XXXX — MULTIPLIER SELECT</div>
            <div class="param-vals">0001=×8 · 0010=×4 · 0100=×2 · 1000=×1</div>
          </div>
        </div>
        <div class="instr-note">HOLD-OP must be sustained for at least (multiplier + 1) clock cycles to capture result before ADD resumes.</div>
      </div>
    </div>

    <!-- 07 OVRD -->
    <div class="instr-card">
      <div class="instr-left">
        <div class="instr-number">MNEMONIC · 07</div>
        <div class="instr-mnemonic">OVRD</div>
        <span class="instr-type-badge badge-system">SYSTEM</span>
      </div>
      <div class="instr-right">
        <div class="instr-desc">Overrides a system halt triggered by an overflow error, allowing the machine to continue execution past a detected overflow condition.</div>
      </div>
    </div>

    <!-- 08 RSTM -->
    <div class="instr-card">
      <div class="instr-left">
        <div class="instr-number">MNEMONIC · 08</div>
        <div class="instr-mnemonic">RSTM</div>
        <span class="instr-type-badge badge-system">SYSTEM</span>
      </div>
      <div class="instr-right">
        <div class="instr-desc">Performs a full machine reset. All registers and bus lines are driven to 0. Use to reinitialize state between programs or after a fault condition.</div>
      </div>
    </div>

    <!-- 09 HOLD-OP -->
    <div class="instr-card">
      <div class="instr-left">
        <div class="instr-number">MNEMONIC · 09</div>
        <div class="instr-mnemonic">HOLD-OP</div>
        <span class="instr-type-badge badge-temporal">TEMPORAL</span>
      </div>
      <div class="instr-right">
        <div class="instr-desc">Holds the current arithmetic result on the output lines for a programmer-specified number of clock cycles. Critical for synchronizing hardware behaviour — prevents the default ADD operation from overwriting a SUB, DIV, or MUL result before it can be read.</div>
        <div class="instr-note">
          MUL: hold for at least (multiplier + 1) cycles &nbsp;·&nbsp;
          DIV: hold for at least (quotient) cycles &nbsp;·&nbsp;
          SUB: hold as needed. Assembler prompts for cycle count at translation time.
        </div>
      </div>
    </div>

  </div><!-- /instructions-grid -->

  <!-- FOOTER -->
  <footer>
    <span class="footer-text">KARAN-D05 · ASSEMBLER PROJECT · MIT LICENSE</span>
    <a class="footer-link" href="https://github.com/KARAN-D05/Assembler">github.com/KARAN-D05/Assembler</a>
  </footer>

</div>
</body>
</html>

<p align="center">
  <img src="asm-v0/asm-v0.3/images/syntax_analysis1.png" 
       alt="asmv0.3 Syntax Analysis" width="600"/>
  <br>
  <sub><b>🔍 Syntax Analysis - Assembler v0.3</b></sub>
</p>

<p align="center">
  <img src="asm-v0/asm-v0.3/images/semantic_analysis.png" 
       alt="asmv0.3 Semantic Analysis" width="600"/>
  <br>
  <sub><b>🕵️ Semantic Analysis - Assembler v0.3</b></sub>
</p>

## 🧩 Latest Development 
- Syntax Analysis of assembly program before being processed by assembler to save computational resources.
- Primitive semantic analysis to detect logical flaws in assembly program before converting to machine code. 

## 🚀 Future Development 
- Advanced Semantic Analysis for the assembly language, enabling validation and structured interpretation of programs before translation to machine code.
- Mapping multiple sequences of low-level instructions into a single mnemonic, enabling higher-level abstractions and more complex machine functionality with fewer lines of assembly code - `MACROS`
  
## 🧰 Computing Machinery from Scratch
- To follow along it is advised to check out the underlying hardware upon which we are building the assembly language.
- [Check out Computing Machinery from scratch](https://github.com/KARAN-D05/Computing_Machinery_from_Scratch)

## 📜 License
- Source code, HDL, and Logisim circuit files are licensed under the MIT License.
- Documentation, diagrams, images, and PDFs are licensed under Creative Commons Attribution 4.0 (CC BY 4.0).
