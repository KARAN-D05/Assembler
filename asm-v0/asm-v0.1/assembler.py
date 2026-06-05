                                                                                    # ASSEMBLER V0.1 SOURCE CODE #
# INPUT ASSEMBLY LANGUAGE PROGRAM
instruction1 = input("Enter Instruction1: ")
instruction2 = input("Enter Instruction2: ")
instruction3 = input("Enter Instruction3: ")
instruction4 = input("Enter Instruction4: ")

# STRING DIVISION
ins1 = instruction1[0:4]
ins2 = instruction1[5]
ins3 = instruction1[7:11]
ins4 = instruction3[0:4]
ins5 = instruction3[5]
ins6 = instruction3[7:11]

# INSTRUCTION 1
if ins1 == "LOAD":
    print("Machine Code Program:")
    print(f"00{ins2}{ins3[0]}00{ins3[1]}000{ins3[2]}{ins3[3]}0000")

# INSTRUCTION 2
if instruction2 == "STORE":

    print(f"01{ins2}0000000000000")

# INSTRUCTION 3
if ins4 == "LOAD":
    print(f"00{ins5}{ins6[0]}00{ins6[1]}000{ins6[2]}{ins6[3]}0000")

# INSTRUCTION 4
if instruction4 == "STORE":

    print(f"01{ins5}0000000000000")
  
# Only Supports LOAD and STORE instructions
