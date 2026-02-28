                                                                                  # ASSEMBLER V0.3 SOURCE CODE # 
# INPUT ASSEMBLY LANGAUGE PROGRAM
instruction1 = input("Enter Instruction1: ")
instruction2 = input("Enter Instruction2: ")
instruction3 = input("Enter Instruction3: ")
instruction4 = input("Enter Instruction4: ")
instruction5 = input("Enter Instruction5: ")
instruction6 = input("Enter Instruction6: ")
instruction7 = input("Enter Instruction7: ")
instruction8 = input("Enter Instruction8: ")
print()

# Initializing RUN variables to "EXECUTED" for Instruction Execution Analysis
R1 = "EXECUTED"
R2 = "EXECUTED"
R3 = "EXECUTED"
R4 = "EXECUTED"
R5 = "EXECUTED"
R6 = "EXECUTED"
R7 = "EXECUTED"
R8 = "EXECUTED"

# NO INPUT TO ASSEMBLER
if instruction1 == "" and instruction2 == "" and instruction3 == "" and instruction4 == "" and instruction5 == "" and instruction6 == "" and instruction7 == "" and instruction8 == "":
    instruction1 = "XXXXXXXXXXXXXXXX"
    instruction2 = "XXXXXXXXXXXXXXXX"
    instruction3 = "XXXXXXXXXXXXXXXX"
    instruction4 = "------EMPTY-----" 
    instruction5 = "-----PROGRAM----" 
    instruction6 = "XXXXXXXXXXXXXXXX"
    instruction7 = "XXXXXXXXXXXXXXXX"
    instruction8 = "XXXXXXXXXXXXXXXX" 
    print(instruction1)
    print(instruction2)
    print(instruction3)
    print(instruction4)
    print(instruction5)
    print(instruction6)
    print(instruction7)
    print(instruction8)
    print()
    exit()

insv1 = instruction1[0:3]
insv2 = instruction1[0:4]

# BASIC SEMANTIC ANALYSIS
if insv1 == "ADD" or insv1 == "SUB" or insv1 == "DIV" or insv1 == "MUL" or insv1 =="FBK":
    print("-----------ERROR->INVALID SEMANTICS-------------")
    print("----No Data Entered to perform operations on----")
    print("----Program Not Processed By Assembler asmv0.3----")
    print()
    exit()

if insv2 == "OVRD" or insv2 =="RSTM":
    print("-----------MACHINE IN INITIAL STATE-------------")
    print("----Program Not Processed By Assembler asmv0.3----") 
    print()
    exit()

# SYNTAX ANALYSIS

# VALID FIXED SYNTAX MNEMONICS -> DIV, ADD, SUB, FBK, OVRD, RSTM, HOLD-OP, ""
# VALID VARIABLE(Binary X) SYNTAX MNEMONICS -> LOAD-X-XXXX, MUL-XXXX

instructions = [ instruction1, instruction2, instruction3, instruction4, instruction5, instruction6, instruction7, instruction8]
valid_operations = ("DIV","ADD","SUB","FBK","OVRD","RSTM","HOLD-OP","")

# If some part of program is correct and some incorrect the RUN Variable Logic fails, thus this checks for all Mnemonic Syntax.
for Q in instructions:
    if Q[0:4] != "LOAD" and Q[0:3] != "MUL":
       if (Q not in valid_operations):
         print("------INVALID SYNTAX------|INVALID MNEMONIC SYNTAX|")
         print("----Program Not Processed By Assembler asmv0.3----")
         print()
         exit()

BINARY = ('0', '1')

for ins in instructions: # VARIABLE SYNTAX MNEMONICS
    if ins[0:4] == "LOAD":
        if len(ins) != 11 or ins[4] != "-" or ins[6] != "-":
            print("------INVALID SYNTAX------|INVALID LOAD SYNTAX|")
            print("----Program Not Processed By Assembler asmv0.3----")
            print()
            exit()

        if ins[5] not in BINARY:
            print("------INVALID SYNTAX------|Selector-> 0 or 1|")
            print("----Program Not Processed By Assembler asmv0.3----")
            print()
            exit()

        for ch in ins[7:]:
            if ch not in BINARY:
                print("------INVALID SYNTAX------|Data-> Binary Strings|")
                print("----Program Not Processed By Assembler asmv0.3----")
                print()
                exit()

    elif ins[0:3] == "MUL":
        if len(ins) != 8:
            print("------INVALID SYNTAX------|INVALID MUL SYNTAX|")
            print("----Program Not Processed By Assembler asmv0.3----")
            print() 
            exit()

        for ch in ins[4:]:
            if ch not in BINARY:
                print("------INVALID SYNTAX------|Data-> Binary Strings|")
                print("----Program Not Processed By Assembler asmv0.3----")
                print() 
                exit()


# STRING DIVIDED INTO SUB-STRINGS FOR CONTROL FLOW
ins1 = instruction1[0:4] # LOAD

# INSTRUCTION 1
if ins1 == "LOAD":
    ins2 = instruction1[5]   # SELECTOR
    ins3 = instruction1[7:11]# DATA
    print(" Machine Code Program:")
    print(f"00{ins2}{ins3[0]}00{ins3[1]}000{ins3[2]}{ins3[3]}0000")
    print(f"01{ins2}0000000000000")
else:
    R1 = "-"

# INSTRUCTION 2
if instruction2 != " ":
    if len(instruction2) == 11: # LOAD INSTRUCTION IS 11 CHARACTERS LONG
        ins1 = instruction2[5]
        ins2 = instruction2[7:11]
        print(f"00{ins1}{ins2[0]}00{ins2[1]}000{ins2[2]}{ins2[3]}0000")
        print(f"01{ins1}0000000000000")
    elif instruction2 == "FBK":  # FEEDBACK
        a = "1000000000000000"
        print(a)
    elif instruction2 == "ADD":  # ADDITION
        a = "DEFAULT ARITHMETIC OPERATION"
        print(a)
    elif instruction2 == "SUB":  # SUBTRACTION
        a = "0000100000000000"
        print(a)
    elif instruction2 == "DIV":  # DIVISION
        a = "0000000010000000"
        print(a)
    elif instruction2 == "OVRD": # OVERRIDE SYSTEM HALT
        print("0000000001000000")
    elif instruction2 == "RSTM": # RESET MACHINE
        print("0000010000000000")
    elif len(instruction2) == 8: # MUL INSTRUCTION IS 8 CHARACTERS LONG
        ins3 = instruction2[4:8]
        a = f"000000010000{ins3}"
        print(a)
    else:
        R2 = "-"    

# INSTRUCTION 3
if instruction3 != " ":
    if len(instruction3) == 11:
        ins4 = instruction3[5]
        ins5 = instruction3[7:11]
        print(f"00{ins4}{ins5[0]}00{ins5[1]}000{ins5[2]}{ins5[3]}0000")
        print(f"01{ins4}0000000000000")
    elif instruction3 == "FBK":
        b = "1000000000000000"
        print(b)
    elif instruction3 == "ADD":
        b = "DEFAULT ARITHMETIC OPERATION"
        print(b)
    elif instruction3 == "SUB":
        b = "0000100000000000"
        print(b)
    elif instruction3 == "DIV":
        b = "0000000010000000"
        print(b)
    elif instruction3 == "OVRD":
        print("0000000001000000")
    elif instruction3 == "RSTM":
        print("0000010000000000")
    elif len(instruction3) == 8:
        ins6 = instruction3[4:8]
        b = f"000000010000{ins6}"
        print(b)
    elif instruction3 == "HOLD-OP": # HOLD-OPERATION
        X = int(input("ENTER CLOCK CYCLES FOR HOLD OPERATION:"))
        for x in range (X-1):
            print(a)
    else:
        R3 = "-"
# INSTRUCTION 4
if instruction4 != " ":
    if len(instruction4) == 11:
        ins7 = instruction4[5]
        ins8 = instruction4[7:11]
        print(f"00{ins7}{ins8[0]}00{ins8[1]}000{ins8[2]}{ins8[3]}0000")
        print(f"01{ins7}0000000000000")
    elif instruction4 == "FBK":
        c = "1000000000000000"
        print(c)
    elif instruction4 == "ADD":
        c = "DEFAULT ARITHMETIC OPERATION"
        print(c)
    elif instruction4 == "SUB":
        c = "0000100000000000"
        print(c)
    elif instruction4 == "DIV":
        c = "0000000010000000"
        print(c)
    elif instruction4 == "OVRD":
        print("0000000001000000")
    elif instruction4 == "RSTM":
        print("0000010000000000")
    elif len(instruction4) == 8:
        ins9 = instruction4[4:8]
        c = f"000000010000{ins9}"
        print(c)
    elif instruction4 == "HOLD-OP":
        Y = int(input("ENTER CLOCK CYCLES FOR HOLD OPERATION:"))
        for x in range (Y-1):
            print(b)
    else:
        R4 = "-"
# INSTRUCTION 5
if instruction5 != " ":
    if len(instruction5) == 11:
        ins10 = instruction5[5]
        ins11 = instruction5[7:11]
        print(f"00{ins10}{ins11[0]}00{ins11[1]}000{ins11[2]}{ins11[3]}0000")
        print(f"01{ins10}0000000000000")
    elif instruction5 == "FBK":
        d = "1000000000000000"
        print(d)
    elif instruction5 == "ADD":
        d = "DEFAULT ARITHMETIC OPERATION"
        print(d)
    elif instruction5 == "SUB":
        d = "0000100000000000"
        print(d)
    elif instruction5 == "DIV":
        d = "0000000010000000"
        print(d)
    elif instruction5 == "OVRD":
        print("0000000001000000")
    elif instruction5 == "RSTM":
        print("0000010000000000")
    elif len(instruction5) == 8:
        ins12 = instruction5[4:8]
        d = f"000000010000{ins12}"
        print(d)
    elif instruction5 == "HOLD-OP":
        Z = int(input("ENTER CLOCK CYCLES FOR HOLD OPERATION:"))
        for x in range (Z-1):
            print(c)
    else:
        R5 = "-"
# INSTRUCTION 6
if instruction6 != " ":
    if len(instruction6) == 11:
        ins13 = instruction6[5]
        ins14 = instruction6[7:11]
        print(f"00{ins13}{ins14[0]}00{ins14[1]}000{ins14[2]}{ins14[3]}0000")
        print(f"01{ins13}0000000000000")
    elif instruction6 == "FBK":
        e = "1000000000000000"
        print(e)
    elif instruction6 == "ADD":
        e = "DEFAULT ARITHMETIC OPERATION"
        print(e)
    elif instruction6 == "SUB":
        e = "0000100000000000"
        print(e)
    elif instruction6 == "DIV":
        e = "0000000010000000"
        print(e)
    elif instruction6 == "OVRD":
        print("0000000001000000")
    elif instruction6 == "RSTM":
        print("0000010000000000")
    elif len(instruction6) == 8:
        ins15 = instruction6[4:8]
        e = f"000000010000{ins12}"
        print(e)
    elif instruction6 == "HOLD-OP":
        K = int(input("ENTER CLOCK CYCLES FOR HOLD OPERATION:"))
        for x in range(K-1):
            print(d)
    else:
        R6 = "-"
# INSTRUCTION 7
if instruction7 != " ":
    if len(instruction7) == 11:
        ins16 = instruction7[5]
        ins17 = instruction7[7:11]
        print(f"00{ins16}{ins17[0]}00{ins17[1]}000{ins17[2]}{ins17[3]}0000")
        print(f"01{ins16}0000000000000")
    elif instruction7 == "FBK":
        f = "1000000000000000"
        print(f)
    elif instruction7 == "ADD":
        f = "DEFAULT ARITHMETIC OPERATION"
        print(f)
    elif instruction7 == "SUB":
        f = "0000100000000000"
        print(f)
    elif instruction7 == "DIV":
        f = "0000000010000000"
        print(f)
    elif instruction7 == "OVRD":
        print("0000000001000000")
    elif instruction7 == "RSTM":
        print("0000010000000000")
    elif len(instruction7) == 8:
        ins18 = instruction7[4:8]
        f = f"000000010000{ins18}"
        print(f)
    elif instruction7 == "HOLD-OP":
        S = int(input("ENTER CLOCK CYCLES FOR HOLD OPERATION:"))
        for x in range(S-1):
            print(e)
    else:
        R7 = "-"
# INSTRUCTION 8
if instruction8 != " ":
    if len(instruction8) == 11:
        ins19 = instruction8[5]
        ins20 = instruction8[7:11]
        print(f"00{ins19}{ins20[0]}00{ins20[1]}000{ins20[2]}{ins20[3]}0000")
        print(f"01{ins19}0000000000000")
    elif instruction8 == "FBK":
        g = "1000000000000000"
        print(g)
    elif instruction8 == "ADD":
        g = "DEFAULT ARITHMETIC OPERATION"
        print(g)
    elif instruction8 == "SUB":
        g = "0000100000000000"
        print(g)
    elif instruction8 == "DIV":
        g = "0000000010000000"
        print(g)
    elif instruction8 == "OVRD":
        print("0000000001000000")
    elif instruction8 == "RSTM":
        print("0000010000000000")
    elif len(instruction8) == 8:
        ins21 = instruction8[4:8]
        g = f"000000010000{ins21}"
        print(g)
    elif instruction8 == "HOLD-OP":
        D = int(input("ENTER CLOCK CYCLES FOR HOLD OPERATION:"))
        for x in range(D-1):
            print(f)            
    else:
        R8 = "-"        

# If All RUN Variables(R1-R8) have become empty, we can conclucde that No Instruction Inputted have been able to be processed by Assembler, thus Invalid Syntax was Entered
if R1 == "" and R2 == "" and R3 == "" and R4 == "" and R5 == "" and R6 == "" and R7 == "" and R8 == "": # Asembly Language Instructions cannot be processed by the Assembler asmv0.3
    print("------INVALID SYNTAX------|Program Not Processed By Assembler asmv0.3|")
    print()
else:
    print()
    print("==>PROGRAM PROCESSED BY ASSEMBLER asmv0.3")   
    print()

print("INSTRUCTION EXECUTION REPORT")
print(f"Instruction1: {R1}")    
print(f"Instruction2: {R2}")
print(f"Instruction3: {R3}")    
print(f"Instruction4: {R4}")
print(f"Instruction5: {R5}")    
print(f"Instruction6: {R6}")
print(f"Instruction7: {R7}")    
print(f"Instruction8: {R8}")
print()
