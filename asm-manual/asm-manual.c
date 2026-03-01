// ============================================================
//  asm-manual.c
// ------------------------------------------------------------
//  When you build your own hardware, you build your own rules.
//  This machine does not follow any existing assembly standard
//  so there is no textbook to refer to, no online resource
//  to look up. The only reference is what was designed here.
//
//  This program is that reference. A manual baked directly
//  into the toolchain so the language standard is always
//  one command away, no browser, no file explorer, just run
//  it and get your answer.
//
//  Every time the hardware evolves, the language evolves.
//  Every time the language evolves, this manual evolves.
// ------------------------------------------------------------
//  Project  : Custom Hardware Assembler
//  File     : asm-manual.c
//  Covers   : asm-v0.1, asm-v0.2, asm-v0.3
//  Author   : Karan Diwan
//  Date     : 1.03.26
// ============================================================

#include <stdio.h>
#include <string.h>

void manual_v01() {
    printf("\n");
    printf("+------------------------------------------------------+\n");
    printf("|          asm-v0.1 - Data Load & Store                |\n");
    printf("+------------------------------------------------------+\n");

    printf("\n OVERVIEW\n");
    printf(" --------\n");
    printf(" Mapped machine code instructions for loading data onto\n");
    printf(" lines and storing it to registers using mnemonics.\n");
    printf(" Built a simple program where you can enter assembly\n");
    printf(" commands one by one and it generates corresponding\n");
    printf(" machine code for LOAD and STORE operations.\n");
    printf(" Serves as a proof of concept for assembler-to-machine\n");
    printf(" code translation.\n");

    printf("\n MNEMONICS\n");
    printf(" ---------\n");

    printf("\n [1] LOAD-S-XXXX\n");
    printf("     Function : Loads data onto the data lines.\n");
    printf("     S        : Selector pin to choose register.\n");
    printf("                S=0 -> Register A\n");
    printf("                S=1 -> Register B\n");
    printf("     XXXX     : 4 binary bits corresponding to\n");
    printf("                weights 1, 2, 4, 8 respectively.\n");
    printf("                Example: 0011 -> 8+4 = 12\n");

    printf("\n     Bit Indexing Convention (asm-v0):\n");
    printf("       Bit 0 = MSB (weight 8)\n");
    printf("       Bit 3 = LSB (weight 1)\n");

    printf("\n     Instruction Data Field Layout:\n");
    printf("       Index  -> [3] [2] [1] [0]\n");
    printf("       Weight ->  1   2   4   8\n");

    printf("\n     Note: Enter instruction with hyphens as shown.\n");

    printf("\n [2] STORE\n");
    printf("     Function : Stores data on lines to registers.\n");
    printf("     Note     : No need to specify selector.\n");
    printf("                Program reads selector from LOAD\n");
    printf("                and inserts it into machine code.\n");
    printf("                Value from LOAD is retained and\n");
    printf("                inserted into correct bit location.\n");

    printf("\n+------------------------------------------------------+\n");
}

void manual_v02() {
    printf("\n");
    printf("+------------------------------------------------------+\n");
    printf("|      asm-v0.2 - Full Machine Code Mapping            |\n");
    printf("+------------------------------------------------------+\n");

    printf("\n OVERVIEW\n");
    printf(" --------\n");
    printf(" All machine code instructions are now mapped to their\n");
    printf(" Assembly Language mnemonics.\n");
    printf(" Temporal Control Added: arithmetic operations can be\n");
    printf(" held for a specified number of clock cycles.\n");
    printf(" All arithmetic operations supported by hardware can\n");
    printf(" now be executed symbolically.\n");
    printf(" Full control of machine behavior using mnemonics.\n");

    printf("\n MNEMONICS\n");
    printf(" ---------\n");

    printf("\n [1] LOAD-S-XXXX\n");
    printf("     Function : Loads AND stores data (combined).\n");
    printf("                No separate STORE needed in v0.2.\n");
    printf("     S        : Selector\n");
    printf("                0 -> Register A\n");
    printf("                1 -> Register B\n");
    printf("     XXXX     : Data bits, weights 1,2,4,8 respectively.\n");
    printf("     Convention: Bit 0 = MSB (weight 8)\n");
    printf("                 Bit 3 = LSB (weight 1)\n");
    printf("     Layout  :  Index  -> [3][2][1][0]\n");
    printf("                Weight ->  1  2  4  8\n");

    printf("\n [2] FBK\n");
    printf("     Function : Feeds output back into Register A,\n");
    printf("                overriding its current contents.\n");

    printf("\n [3] ADD\n");
    printf("     Function : Default arithmetic operation.\n");
    printf("                No machine code required.\n");
    printf("     Output   : \"DEFAULT ARITHMETIC OPERATION\"\n");

    printf("\n [4] SUB\n");
    printf("     Function : Subtracts Register A from Register B.\n");

    printf("\n [5] DIV\n");
    printf("     Function : Divides Register A by Register B.\n");

    printf("\n [6] MUL-XXXX\n");
    printf("     Function : Multiplies Register B by (XXXX value - 1).\n");
    printf("     XXXX     : Binary bits -> weights 1,2,4,8.\n");
    printf("     Example  : 0010 -> value=4, multiplier=(4-1)=3\n");

    printf("\n [7] OVRD\n");
    printf("     Function : Overrides system halt caused by\n");
    printf("                overflow errors.\n");

    printf("\n [8] RSTM\n");
    printf("     Function : Resets entire machine.\n");
    printf("                All registers and lines go to 0.\n");

    printf("\n [9] HOLD-OP\n");
    printf("     Function : Keeps result of arithmetic operation\n");
    printf("                on output lines for N clock cycles.\n");
    printf("     Purpose  : Synchronizes hardware behaviour.\n");
    printf("                Default operation is ADD, so after\n");
    printf("                SUB/DIV/MUL the result must be held\n");
    printf("                before ADD takes over again.\n");
    printf("     Usage    : Prompts for number of clock cycles.\n");
    printf("     Rule     : For MUL -> hold for (multiplier+1) cycles\n");
    printf("                For DIV -> hold for (quotient) cycles\n");

    printf("\n+------------------------------------------------------+\n");
}

void manual_v03() {
    printf("\n");
    printf("+------------------------------------------------------+\n");
    printf("|   asm-v0.3 - Syntax & Primitive Semantic Analysis    |\n");
    printf("+------------------------------------------------------+\n");

    printf("\n OVERVIEW\n");
    printf(" --------\n");
    printf(" The assembler evolves from a simple instruction-to-\n");
    printf(" machine-code translator into an early-stage compiler\n");
    printf(" system capable of performing syntax validation and\n");
    printf(" primitive semantic checks.\n");
    printf(" Ensures every instruction follows valid structural\n");
    printf(" rules (syntax) and operations occur in a meaningful\n");
    printf(" order (basic semantic checks).\n");

    printf("\n KEY FEATURES\n");
    printf(" ------------\n");

    printf("\n [1] SYNTAX ANALYSIS\n");
    printf("     - Each instruction validated before translation.\n");
    printf("     - Detects malformed mnemonics such as:\n");
    printf("       * Invalid LOAD structure (missing -S-XXXX).\n");
    printf("       * Non-binary selector or data bits.\n");
    printf("       * Incorrect instruction length for MUL\n");
    printf("         or other variable-length mnemonics.\n");

    printf("\n [2] PRIMITIVE SEMANTIC ANALYSIS\n");
    printf("     - Checks logical execution order.\n");
    printf("       Example: prevents arithmetic before any LOAD.\n");
    printf("     - Detects invalid machine states.\n");
    printf("       Example: reset or override at wrong time.\n");
    printf("     - Assembler halts with descriptive error messages.\n");

    printf("\n [3] ENHANCED ERROR REPORTING\n");
    printf("     - Distinct syntax and semantic error messages.\n");
    printf("     - Clear differentiation between:\n");
    printf("       * Invalid syntax   (wrong format/structure)\n");
    printf("       * Invalid semantics (wrong order/context)\n");

    printf("\n ERROR TYPES DETECTED\n");
    printf(" -------------------\n");
    printf("     * No input detected\n");
    printf("     * Instruction out of order\n");
    printf("     * Malformed mnemonic\n");
    printf("     * Invalid binary fields\n");
    printf("     * Operation before data load\n");

    printf("\n INSTRUCTION EXECUTION REPORT\n");
    printf(" ----------------------------\n");
    printf("     After running a program, v0.3 generates a full\n");
    printf("     execution report showing each instruction, its\n");
    printf("     result, and any errors encountered.\n");

    printf("\n+------------------------------------------------------+\n");
}

void manual_all() {
    printf("\n");
    printf("+------------------------------------------------------+\n");
    printf("|             ASM Manual - All Versions                |\n");
    printf("+------------------------------------------------------+\n");
    printf("\n  v0.1 -> Data Load & Store Mnemonics Mapped\n");
    printf("  v0.2 -> Full Machine Code & Mnemonic Mapping\n");
    printf("  v0.3 -> Syntax & Primitive Semantic Analysis\n");
    printf("\n Showing all versions...\n");
    manual_v01();
    manual_v02();
    manual_v03();
}

int main() {
    char input[20];

    printf("+------------------------------------------------------+\n");
    printf("|              ASM Language Manual                     |\n");
    printf("|          Custom Hardware Assembler Docs              |\n");
    printf("+------------------------------------------------------+\n");

    while (1) {
        printf("\n Available versions: v0.1 | v0.2 | v0.3 | all\n");
        printf(" Type 'exit' to quit.\n");
        printf("\n Enter ASM standard: ");
        scanf("%s", input);

        if (strcmp(input, "v0.1") == 0) {
            manual_v01();
        } else if (strcmp(input, "v0.2") == 0) {
            manual_v02();
        } else if (strcmp(input, "v0.3") == 0) {
            manual_v03();
        } else if (strcmp(input, "all") == 0) {
            manual_all();
        } else if (strcmp(input, "exit") == 0) {
            printf("\n Goodbye!\n");
            break;
        } else {
            printf("\n [ERROR] Unknown version '%s'\n", input);
            printf(" Try: v0.1, v0.2, v0.3, or all\n");
        }
    }

    return 0;
}
