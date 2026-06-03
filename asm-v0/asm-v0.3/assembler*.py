                                                                                        # ASSEMBLER asmv0.3.1 Source Code
# Type ASM-PROCESS to assemble all instructions entered above it.
# No hardcoded instruction limit - keep entering until ASM-PROCESS
# NOTE: ASM-Process is not part of Assembly Language, its an instruction to the assembler.

print("Directive ASM-PROCESS: asmv0.3.1 start processing \n")

instructions = []
idx = 1

while True:
    ins = input(f"Enter Instruction{idx}: ")
    if ins == "ASM-PROCESS":
        break
    instructions.append(ins)
    idx += 1

print()

# ASM-PROCESS with no instructions above it
if len(instructions) == 0:
    print("----NO INSTRUCTIONS TO PROCESS----")
    print("----Program Not Processed By Assembler asmv0.4----")
    print()
    exit()

# Initializing RUN variables - one per instruction collected
R = ["EXECUTED"] * len(instructions)

# NO INPUT (all blank before ASM-PROCESS)
if all(ins == "" for ins in instructions):
    print("XXXXXXXXXXXXXXXX")
    print("XXXXXXXXXXXXXXXX")
    print("XXXXXXXXXXXXXXXX")
    print("------EMPTY-----")
    print("-----PROGRAM----")
    print("XXXXXXXXXXXXXXXX")
    print("XXXXXXXXXXXXXXXX")
    print("XXXXXXXXXXXXXXXX")
    print()
    exit()

insv1 = instructions[0][0:3]
insv2 = instructions[0][0:4]

# BASIC SEMANTIC ANALYSIS
if insv1 in ("ADD", "SUB", "DIV", "MUL", "FBK"):
    print("-----------ERROR->INVALID SEMANTICS-------------")
    print("----No Data Entered to perform operations on----")
    print("----Program Not Processed By Assembler asmv0.4----")
    print()
    exit()

if insv2 in ("OVRD", "RSTM"):
    print("-----------MACHINE IN INITIAL STATE-------------")
    print("----Program Not Processed By Assembler asmv0.4----")
    print()
    exit()

# SYNTAX ANALYSIS
valid_operations = ("DIV", "ADD", "SUB", "FBK", "OVRD", "RSTM", "HOLD-OP", "")
BINARY = ('0', '1')

for Q in instructions:
    if Q[0:4] != "LOAD" and Q[0:3] != "MUL":
        if Q not in valid_operations:
            print("------INVALID SYNTAX------|INVALID MNEMONIC SYNTAX|")
            print("----Program Not Processed By Assembler asmv0.4----")
            print()
            exit()

for ins in instructions:
    if ins[0:4] == "LOAD":
        if len(ins) != 11 or ins[4] != "-" or ins[6] != "-":
            print("------INVALID SYNTAX------|INVALID LOAD SYNTAX|")
            print("----Program Not Processed By Assembler asmv0.4----")
            print()
            exit()
        if ins[5] not in BINARY:
            print("------INVALID SYNTAX------|Selector-> 0 or 1|")
            print("----Program Not Processed By Assembler asmv0.4----")
            print()
            exit()
        for ch in ins[7:]:
            if ch not in BINARY:
                print("------INVALID SYNTAX------|Data-> Binary Strings|")
                print("----Program Not Processed By Assembler asmv0.4----")
                print()
                exit()
    elif ins[0:3] == "MUL":
        if len(ins) != 8:
            print("------INVALID SYNTAX------|INVALID MUL SYNTAX|")
            print("----Program Not Processed By Assembler asmv0.4----")
            print()
            exit()
        for ch in ins[4:]:
            if ch not in BINARY:
                print("------INVALID SYNTAX------|Data-> Binary Strings|")
                print("----Program Not Processed By Assembler asmv0.4----")
                print()
                exit()

# CODE GENERATION
# last_code tracks the previous instruction's machine code for HOLD-OP repeat logic
last_code = None

print(" Machine Code Program:")

for i, ins in enumerate(instructions):
    if ins[0:4] == "LOAD":
        sel  = ins[5]
        data = ins[7:11]
        mc1 = f"00{sel}{data[0]}00{data[1]}000{data[2]}{data[3]}0000"
        mc2 = f"01{sel}0000000000000"
        print(mc1)
        print(mc2)
        last_code = mc2  # last line printed for this instruction

    elif ins == "FBK":
        last_code = "1000000000000000"
        print(last_code)

    elif ins == "ADD":
        last_code = "DEFAULT ARITHMETIC OPERATION"
        print(last_code)

    elif ins == "SUB":
        last_code = "0000100000000000"
        print(last_code)

    elif ins == "DIV":
        last_code = "0000000010000000"
        print(last_code)

    elif ins == "OVRD":
        last_code = "0000000001000000"
        print(last_code)

    elif ins == "RSTM":
        last_code = "0000010000000000"
        print(last_code)

    elif ins[0:3] == "MUL":
        data = ins[4:8]
        last_code = f"000000010000{data}"
        print(last_code)

    elif ins == "HOLD-OP":
        cycles = int(input("ENTER CLOCK CYCLES FOR HOLD OPERATION: "))
        for _ in range(cycles - 1):
            print(last_code)

    elif ins == "":
        R[i] = "-"

    else:
        R[i] = "-"

# Final validity check if every R ended up "-", nothing was processed
if all(r == "-" for r in R):
    print("------INVALID SYNTAX------|Program Not Processed By Assembler asmv0.4|")
    print()
else:
    print()
    print("==>PROGRAM PROCESSED BY ASSEMBLER asmv0.3.1")
    print()

print("INSTRUCTION EXECUTION REPORT")
for i, r in enumerate(R):
    print(f"Instruction{i+1}: {r}")
print()
