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
//  Date     : 2026
// ============================================================

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// ─────────────────────────────────────────
// ANSI COLOR CODES
// ─────────────────────────────────────────

#define RESET       "\033[0m"
#define BOLD        "\033[1m"
#define DIM         "\033[2m"
#define RED         "\033[31m"
#define GREEN       "\033[32m"
#define YELLOW      "\033[33m"
#define CYAN        "\033[36m"
#define BOLD_WHITE  "\033[1;37m"
#define BOLD_CYAN   "\033[1;36m"
#define BOLD_YELLOW "\033[1;33m"
#define BOLD_GREEN  "\033[1;32m"
#define BOLD_RED    "\033[1;31m"

// ─────────────────────────────────────────
// PRINT HELPERS
// ─────────────────────────────────────────

void print_divider() {
    printf(DIM "+------------------------------------------------------+" RESET "\n");
}

void print_header(char *title) {
    print_divider();
    printf(DIM "|" RESET BOLD_CYAN "  %-52s" RESET DIM "|" RESET "\n", title);
    print_divider();
}

void print_section(char *title) {
    printf("\n" BOLD_WHITE " %s" RESET "\n", title);
    printf(DIM " ");
    for (int i = 0; i < (int)strlen(title); i++) printf("-");
    printf(RESET "\n");
}

void print_mnemonic(int num, char *name) {
    printf("\n" BOLD_YELLOW "  [%d] %s" RESET "\n", num, name);
}

void print_field(char *key, char *value) {
    printf(CYAN "       %-10s" RESET ": %s\n", key, value);
}

void print_note(char *note) {
    printf(DIM "       Note      : %s" RESET "\n", note);
}

void print_bullet(char *text) {
    printf(GREEN "     * " RESET "%s\n", text);
}

void print_arrow(char *key, char *value) {
    printf("       " CYAN "%s" RESET " -> %s\n", key, value);
}

void print_limitation(char *text) {
    printf(YELLOW "     ! " RESET "%s\n", text);
}

// ─────────────────────────────────────────
// MNEMONIC DATABASE
// ─────────────────────────────────────────

typedef struct {
    char name[20];
    char version[20];
    char syntax[30];
    char function[200];
    char note[200];
} Mnemonic;

Mnemonic mnemonics[] = {
    {
        "LOAD",
        "v0.1+",
        "LOAD-S-XXXX",
        "Loads data onto the data lines. In v0.1 a separate STORE is needed. From v0.2 onward LOAD handles storing automatically.",
        "S=0 -> Register A | S=1 -> Register B | XXXX = 4 binary bits (weight 8,4,2,1) | Bit 0 is MSB (weight 8), Bit 3 is LSB (weight 1)"
    },
    {
        "STORE",
        "v0.1 only",
        "STORE",
        "Stores data on lines to the selected register.",
        "Only exists in v0.1. From v0.2 onward STORE is abstracted away -- LOAD handles both loading and storing automatically."
    },
    {
        "FBK",
        "v0.2+",
        "FBK",
        "Feeds the ALU output back into Register A, overriding its current contents.",
        "Useful for chaining arithmetic operations using the result of the previous one."
    },
    {
        "ADD",
        "v0.2+",
        "ADD",
        "Default arithmetic operation of the machine. Adds Register A and Register B.",
        "No machine code required. Outputs: DEFAULT ARITHMETIC OPERATION."
    },
    {
        "SUB",
        "v0.2+",
        "SUB",
        "Subtracts Register B from Register A.",
        "Use HOLD-OP after SUB to retain result before default ADD takes over."
    },
    {
        "DIV",
        "v0.2+",
        "DIV",
        "Divides Register A by Register B.",
        "Use HOLD-OP for at least (quotient) clock cycles after DIV."
    },
    {
        "MUL",
        "v0.2+",
        "MUL-XXXX",
        "Multiplies Register B by (XXXX value - 1).",
        "XXXX -> weights 1,2,4,8 | Example: 0010 -> value=4, multiplier=3 | Use HOLD-OP for at least (multiplier+1) cycles."
    },
    {
        "OVRD",
        "v0.2+",
        "OVRD",
        "Overrides the system halt caused by overflow errors.",
        "Use when you want to continue execution despite overflow."
    },
    {
        "RSTM",
        "v0.2+",
        "RSTM",
        "Resets the entire machine. All registers and lines go to 0.",
        "Full hardware reset. Clock cycle counter also resets."
    },
    {
        "HOLD",
        "v0.2+",
        "HOLD-OP",
        "Keeps the result of an arithmetic operation on output lines for N clock cycles.",
        "Critical for synchronizing hardware. For MUL hold (multiplier+1) cycles. For DIV hold (quotient) cycles."
    },
};

int mnemonic_count = 10;

// ─────────────────────────────────────────
// SEARCH HELPER
// ─────────────────────────────────────────

void to_upper(char *str) {
    for (int i = 0; str[i]; i++)
        if (str[i] >= 'a' && str[i] <= 'z')
            str[i] -= 32;
}

// ─────────────────────────────────────────
// SEARCH FUNCTION
// ─────────────────────────────────────────

void search(char *query) {
    char q[50];
    strncpy(q, query, 49);
    q[49] = '\0';
    to_upper(q);

    int found = 0;

    printf("\n");
    print_divider();
    printf(BOLD_CYAN "  Search results for: %s" RESET "\n", q);
    print_divider();

    for (int i = 0; i < mnemonic_count; i++) {
        char name_upper[20];
        char syntax_upper[30];
        char func_upper[200];
        char note_upper[200];

        strncpy(name_upper,   mnemonics[i].name,     19);  name_upper[19]   = '\0';
        strncpy(syntax_upper, mnemonics[i].syntax,   29);  syntax_upper[29] = '\0';
        strncpy(func_upper,   mnemonics[i].function, 199); func_upper[199]  = '\0';
        strncpy(note_upper,   mnemonics[i].note,     199); note_upper[199]  = '\0';

        to_upper(name_upper);
        to_upper(syntax_upper);
        to_upper(func_upper);
        to_upper(note_upper);

        if (strstr(name_upper,   q) ||
            strstr(syntax_upper, q) ||
            strstr(func_upper,   q) ||
            strstr(note_upper,   q)) {

            printf("\n");
            printf(BOLD_YELLOW "  Mnemonic" RESET " : " BOLD_WHITE "%s" RESET "\n", mnemonics[i].name);
            printf(CYAN        "  Version " RESET " : %s\n", mnemonics[i].version);
            printf(CYAN        "  Syntax  " RESET " : %s\n", mnemonics[i].syntax);
            printf(            "  Function : %s\n", mnemonics[i].function);
            printf(DIM         "  Notes    : %s" RESET "\n", mnemonics[i].note);
            printf(DIM "\n  ------------------------------------------------------" RESET "\n");
            found++;
        }
    }

    if (found == 0)
        printf(BOLD_RED "\n  No results found for '%s'\n" RESET, q);
    else
        printf(BOLD_GREEN "\n  %d result(s) found.\n" RESET, found);

    print_divider();
}

// ─────────────────────────────────────────
// VERSION MANUALS
// ─────────────────────────────────────────

void manual_v01() {
    printf("\n");
    print_header("asm-v0.1 - Data Load & Store");

    print_section("OVERVIEW");
    printf(" Mapped machine code instructions for loading data onto\n");
    printf(" lines and storing it to registers using mnemonics.\n");
    printf(" Built a simple program where you can enter assembly\n");
    printf(" commands one by one and it generates corresponding\n");
    printf(" machine code for LOAD and STORE operations.\n");
    printf(" Serves as a proof of concept for assembler-to-machine\n");
    printf(" code translation.\n");

    print_section("MNEMONICS (v0.1 only has these two)");

    print_mnemonic(1, "LOAD-S-XXXX");
    print_field("Function", "Loads data onto the data lines.");
    print_field("S", "Selector pin to choose register.");
    print_arrow("S=0", "Register A");
    print_arrow("S=1", "Register B");
    print_field("XXXX", "4 binary bits, weights 1,2,4,8.");
    printf("                Example: 0011 -> 8+4 = 12\n");
    printf("\n" BOLD_WHITE "       Bit Indexing Convention (asm-v0):\n" RESET);
    printf("         Bit 0 = MSB (weight 8)\n");
    printf("         Bit 3 = LSB (weight 1)\n");
    printf("\n" BOLD_WHITE "       Instruction Data Field Layout:\n" RESET);
    printf("         Index  -> [3] [2] [1] [0]\n");
    printf("         Weight ->  1   2   4   8\n");
    print_note("Enter instruction with hyphens as shown.");

    print_mnemonic(2, "STORE");
    print_field("Function", "Stores data on lines to registers.");
    print_note("No need to specify selector.");
    printf(DIM "                Program reads selector from LOAD\n" RESET);
    printf(DIM "                and inserts it into machine code.\n" RESET);
    printf(DIM "                Value from LOAD is retained and\n" RESET);
    printf(DIM "                inserted into correct bit location.\n" RESET);
    printf(YELLOW "       v0.1 only: STORE is abstracted away in v0.2+\n" RESET);

    printf("\n");
    print_divider();
}

void manual_v02() {
    printf("\n");
    print_header("asm-v0.2 - Full Machine Code Mapping");

    print_section("OVERVIEW");
    printf(" All machine code instructions are now mapped to their\n");
    printf(" Assembly Language mnemonics.\n");
    printf(" STORE is abstracted away -- LOAD now handles both\n");
    printf(" loading and storing in a single instruction.\n");
    printf(" Temporal Control Added: arithmetic operations can be\n");
    printf(" held for a specified number of clock cycles.\n");
    printf(" All arithmetic operations supported by hardware can\n");
    printf(" now be executed symbolically.\n");
    printf(" Full control of machine behavior using mnemonics.\n");

    print_section("MNEMONICS");

    print_mnemonic(1, "LOAD-S-XXXX");
    print_field("Function", "Loads AND stores data (combined).");
    printf("                No separate STORE needed from v0.2.\n");
    print_arrow("S=0", "Register A");
    print_arrow("S=1", "Register B");
    printf("       Bit 0 = MSB (weight 8) | Bit 3 = LSB (weight 1)\n");
    printf("       Layout: Index -> [3][2][1][0] | Weight -> 1 2 4 8\n");

    print_mnemonic(2, "FBK");
    print_field("Function", "Feeds output back into Register A.");

    print_mnemonic(3, "ADD");
    print_field("Function", "Default arithmetic operation.");
    print_field("Output", "DEFAULT ARITHMETIC OPERATION");

    print_mnemonic(4, "SUB");
    print_field("Function", "Subtracts Register B from Register A.");
    print_note("Use HOLD-OP after to retain result.");

    print_mnemonic(5, "DIV");
    print_field("Function", "Divides Register A by Register B.");
    print_note("Use HOLD-OP for (quotient) cycles.");

    print_mnemonic(6, "MUL-XXXX");
    print_field("Function", "Multiplies Register B by (XXXX - 1).");
    printf("                Example: 0010 -> value=4, multiplier=3\n");
    print_note("Use HOLD-OP for (multiplier+1) cycles.");

    print_mnemonic(7, "OVRD");
    print_field("Function", "Overrides overflow halt.");

    print_mnemonic(8, "RSTM");
    print_field("Function", "Resets entire machine to 0.");

    print_mnemonic(9, "HOLD-OP");
    print_field("Function", "Holds output for N clock cycles.");
    printf("                MUL -> hold (multiplier+1) cycles\n");
    printf("                DIV -> hold (quotient) cycles\n");

    printf("\n");
    print_divider();
}

void manual_v03() {
    printf("\n");
    print_header("asm-v0.3 - Syntax & Primitive Semantic Analysis");

    print_section("OVERVIEW");
    printf(" The assembler evolves into an early-stage compiler\n");
    printf(" capable of syntax validation and primitive semantic\n");
    printf(" checks. All mnemonics from v0.2 are supported.\n");
    printf(" Ensures every instruction follows valid structural\n");
    printf(" rules and operations occur in meaningful order.\n");

    print_section("MNEMONICS");
    printf(" All mnemonics from v0.2 are supported.\n");
    printf(DIM " See v0.2 for the full mnemonic list.\n" RESET);
    printf(DIM " v0.3 adds a validation layer on top of them.\n" RESET);

    print_section("KEY FEATURES");

    printf("\n" BOLD_YELLOW "  [1] SYNTAX ANALYSIS\n" RESET);
    print_bullet("Validates each instruction before translation.");
    print_bullet("Detects invalid LOAD structure.");
    print_bullet("Detects non-binary selector or data bits.");
    print_bullet("Detects incorrect instruction length.");

    printf("\n" BOLD_YELLOW "  [2] PRIMITIVE SEMANTIC ANALYSIS\n" RESET);
    print_bullet("Prevents arithmetic before any LOAD.");
    print_bullet("Detects invalid machine states.");
    print_bullet("Halts with descriptive error messages.");

    printf("\n" BOLD_YELLOW "  [3] ENHANCED ERROR REPORTING\n" RESET);
    print_bullet("Distinct syntax and semantic error messages.");
    printf(GREEN "     * " RESET "Invalid syntax    -> wrong format/structure\n");
    printf(GREEN "     * " RESET "Invalid semantics -> wrong order/context\n");

    print_section("ERROR TYPES DETECTED");
    print_limitation("No input detected");
    print_limitation("Instruction out of order");
    print_limitation("Malformed mnemonic");
    print_limitation("Invalid binary fields");
    print_limitation("Operation before data load");

    printf("\n");
    print_divider();
}

void manual_all() {
    printf("\n");
    print_header("ASM Manual - All Versions");
    printf(CYAN "  v0.1" RESET " -> LOAD-S-XXXX + STORE only\n");
    printf(CYAN "  v0.2" RESET " -> STORE abstracted, full mnemonic set added\n");
    printf(CYAN "  v0.3" RESET " -> Syntax & Primitive Semantic Analysis layer\n");
    printf(DIM "\n Showing all versions...\n" RESET);
    manual_v01();
    manual_v02();
    manual_v03();
}

// ─────────────────────────────────────────
// SAMPLE PROGRAMS
// ─────────────────────────────────────────

void samples_index() {
    printf("\n");
    print_header("Sample Programs - asm-v0");
    printf(" Verified assembly programs written in the custom\n");
    printf(" asm-v0 assembly language, tested on the Custom\n");
    printf(" Computing Machine.\n");

    print_section("ASSEMBLER COMPATIBILITY");
    printf(CYAN "   asm-v0.1" RESET "          -> asm-v0.1 assembler only\n");
    printf(CYAN "   asm-v0.2 / v0.3" RESET "   -> asm-v0.2 or asm-v0.3 assembler\n");
    printf(YELLOW "\n   ! Recommended: use asm-v0.3 assembler\n" RESET);
    printf(DIM "     Includes syntax analysis, semantic analysis\n");
    printf("     and execution report.\n" RESET);

    print_section("PROGRAMS");
    printf(BOLD_YELLOW "   P1" RESET " -> Basic Load & ADD      " DIM "(LOAD, STORE, ADD)\n" RESET);
    printf(BOLD_YELLOW "   P2" RESET " -> Feedback              " DIM "(FBK, SUB, HOLD-OP)\n" RESET);
    printf(BOLD_YELLOW "   P3" RESET " -> Division              " DIM "(DIV, HOLD-OP, Convergence)\n" RESET);
    printf(BOLD_YELLOW "   P4" RESET " -> Multiplication        " DIM "(MUL, HOLD-OP, XXXX-1 rule)\n" RESET);
    printf(BOLD_YELLOW "   P5" RESET " -> Overflow & Recovery   " DIM "(OVRD, overflow detection)\n" RESET);
    printf(BOLD_YELLOW "   P6" RESET " -> Machine Reset         " DIM "(RSTM)\n" RESET);

    print_section("BIT INDEXING CONVENTION (all programs)");
    printf(DIM "   // Bit 0 is MSB (weight 8)\n" RESET);
    printf(DIM "   // Bit 3 is LSB (weight 1)\n" RESET);
    printf(DIM "   // Instruction Data Field Layout:\n" RESET);
    printf(DIM "   // Index  -> [3] [2] [1] [0]\n" RESET);
    printf(DIM "   // Weight ->  1   2   4   8\n" RESET);

    printf(DIM "\n Enter P1 to P6 to view a program.\n" RESET);
    printf("\n");
    print_divider();
}

void sample_p1() {
    printf("\n");
    print_header("P1 - Basic Load & ADD");

    printf(DIM "\n// asm-v0.1 has separate instructions for bringing Data on the Line (LOAD-S-XXXX)\n" RESET);
    printf(DIM "// and then storing it (STORE)\n" RESET);
    printf(DIM "// Will Only Run in asm-v0.1 standard assembler\n" RESET);
    printf(BOLD_GREEN "LOAD-0-1001" RESET DIM " // Load 1001(9) on Data Lines\n" RESET);
    printf(BOLD_GREEN "STORE      " RESET DIM " // Store data in Register A\n" RESET);
    printf(BOLD_GREEN "LOAD-1-1100" RESET DIM " // Load 1100(3) on Data Lines\n" RESET);
    printf(BOLD_GREEN "STORE      " RESET DIM " // Store data in Register B\n" RESET);
    printf(DIM "// asm-v0.2, No STORE mnemonic, abstracted away with LOAD-S-XXXX mnemonic\n" RESET);
    printf(DIM "// Will Run in asm-v0.2 and asm-v0.3 standard assembler\n" RESET);
    printf(BOLD_GREEN "LOAD-0-1001" RESET DIM " // Load 1001(9) on Data Lines and Store in Register A\n" RESET);
    printf(BOLD_GREEN "LOAD-1-1100" RESET DIM " // Load 1100(3) on Data Lines and store in Register B\n" RESET);

    printf(DIM "\n----------------------------------------------------\n" RESET);
    printf(BOLD_WHITE "# EXECUTION TRACE\n" RESET);
    printf(DIM "----------------------------------------------------\n" RESET);
    printf("Initial State:\n");
    printf("A = 0000 (0)\n");
    printf("B = 0000 (0)\n");
    printf("Output = 0000 (0)\n");
    printf(DIM "----------------------------------------------------\n" RESET);
    printf(BOLD_WHITE "asm-v0.1 Execution (LOAD + STORE separated)\n" RESET);
    printf(DIM "----------------------------------------------------\n" RESET);
    printf(BOLD_YELLOW "1) LOAD-0-1001\n" RESET);
    printf("   Data Lines <- 1001 (9)\n");
    printf(BOLD_YELLOW "2) STORE\n" RESET);
    printf("   Register A <- 1001 (9)\n");
    printf("   Current State:\n");
    printf(CYAN "   A = 1001 (9)\n" RESET);
    printf(CYAN "   B = 0000 (0)\n" RESET);
    printf(BOLD_YELLOW "3) LOAD-1-1100\n" RESET);
    printf("   Data Lines <- 1100 (3)\n");
    printf(BOLD_YELLOW "4) STORE\n" RESET);
    printf("   Register B <- 1100 (3)\n");
    printf("   Current State:\n");
    printf(CYAN "   A = 1001 (9)\n" RESET);
    printf(CYAN "   B = 1100 (3)\n" RESET);
    printf(DIM "----------------------------------------------------\n" RESET);
    printf(BOLD_WHITE "asm-v0.2 / asm-v0.3 Execution (STORE abstracted)\n" RESET);
    printf(DIM "----------------------------------------------------\n" RESET);
    printf(BOLD_YELLOW "1) LOAD-0-1001\n" RESET);
    printf("   Register A <- 1001 (9)\n");
    printf(BOLD_YELLOW "2) LOAD-1-1100\n" RESET);
    printf("   Register B <- 1100 (3)\n");
    printf("   Current State:\n");
    printf(CYAN "   A = 1001 (9)\n" RESET);
    printf(CYAN "   B = 1100 (3)\n" RESET);
    printf(DIM "----------------------------------------------------\n" RESET);
    printf(BOLD_WHITE "Arithmetic Operation\n" RESET);
    printf(DIM "----------------------------------------------------\n" RESET);
    printf("Default Operation: ADD\n");
    printf("A + B = 9 + 3 = 12\n");
    printf(BOLD_GREEN "Binary Output = 0011 (12)\n" RESET);
    printf(DIM "----------------------------------------------------\n" RESET);
    printf(BOLD_WHITE "Final System State\n" RESET);
    printf(DIM "----------------------------------------------------\n" RESET);
    printf(CYAN "Register A = 1001 (9)\n" RESET);
    printf(CYAN "Register B = 1100 (3)\n" RESET);
    printf(BOLD_GREEN "Output     = 0011 (12)\n" RESET);
    printf(GREEN "No overflow occurs.\n" RESET);
    printf(GREEN "No error detection triggered.\n" RESET);
    printf(GREEN "Clock continues normally.\n" RESET);
    printf(DIM "----------------------------------------------------\n" RESET);
    printf(DIM "// It is advised to Use asm-v0.3 Standard Assembler:\n" RESET);
    printf(DIM "// Features like Syntax and Semantic Analysis.\n" RESET);
    printf(DIM "// Output Error Statements indicating the error.\n" RESET);
    printf(DIM "// Compatible with asm-v0.2 standard.\n" RESET);

    printf("\n");
    print_divider();
}

void sample_p2() {
    printf("\n");
    print_header("P2 - Feedback");

    printf(DIM "\n// Program follows asm-v0.2 standard\n" RESET);
    printf(DIM "// Will Run in asm-v0.2 and asm-v0.3 standard assembler\n" RESET);
    printf(BOLD_GREEN "LOAD-0-0110" RESET DIM " // Load 0110(6) in Register A\n" RESET);
    printf(BOLD_GREEN "LOAD-1-0001" RESET DIM " // Load 0001(8) in Register B\n" RESET);
    printf(BOLD_GREEN "ADD        " RESET DIM " // ADD Data in Register A and B\n" RESET);
    printf(BOLD_GREEN "FBK        " RESET DIM " // Feedback output back to input (Register A)\n" RESET);
    printf(BOLD_GREEN "SUB        " RESET DIM " // Subtract Data in Register A and B\n" RESET);
    printf(BOLD_GREEN "HOLD-OP    " RESET DIM " // Hold operation/output for arbitrary number of clock cycles\n" RESET);

    printf(DIM "\n---------------------------------------------------\n" RESET);
    printf(BOLD_WHITE "# EXECUTION TRACE\n" RESET);
    printf(DIM "---------------------------------------------------\n" RESET);
    printf("Initial State:\n");
    printf("A = 0000 (0)\n");
    printf("B = 0000 (0)\n");
    printf("Output = 0000 (0)\n");
    printf(DIM "----------------------------------------------------\n" RESET);
    printf(BOLD_WHITE "Program Execution (asm-v0.2 / asm-v0.3)\n" RESET);
    printf(DIM "----------------------------------------------------\n" RESET);
    printf(BOLD_YELLOW "1) LOAD-0-0110\n" RESET);
    printf("   Register A <- 0110 (6)\n");
    printf(BOLD_YELLOW "2) LOAD-1-0001\n" RESET);
    printf("   Register B <- 0001 (8)\n");
    printf("   Current State:\n");
    printf(CYAN "   A = 0110 (6)\n" RESET);
    printf(CYAN "   B = 0001 (8)\n" RESET);
    printf(DIM "----------------------------------------------------\n" RESET);
    printf(BOLD_YELLOW "3) ADD  (Default Operation)\n" RESET);
    printf(DIM "----------------------------------------------------\n" RESET);
    printf("A + B = 6 + 8 = 14\n");
    printf(BOLD_GREEN "Binary Output = 0111 (14)\n" RESET);
    printf(DIM "----------------------------------------------------\n" RESET);
    printf(BOLD_YELLOW "4) FBK  (Feedback)\n" RESET);
    printf(DIM "----------------------------------------------------\n" RESET);
    printf("Register A <- 0111 (14)\n");
    printf("   Current State:\n");
    printf(CYAN "   A = 0111 (14)\n" RESET);
    printf(CYAN "   B = 0001 (8)\n" RESET);
    printf(DIM "----------------------------------------------------\n" RESET);
    printf(BOLD_YELLOW "5) SUB\n" RESET);
    printf(DIM "----------------------------------------------------\n" RESET);
    printf("A - B = 14 - 8 = 6\n");
    printf(BOLD_GREEN "Binary Output = 0110 (6)\n" RESET);
    printf(DIM "----------------------------------------------------\n" RESET);
    printf(BOLD_YELLOW "6) HOLD-OP\n" RESET);
    printf(DIM "----------------------------------------------------\n" RESET);
    printf("Output held constant at:\n");
    printf(BOLD_GREEN "0110 (6)\n" RESET);
    printf("The value remains on the output lines for the specified\n");
    printf("number of clock cycles.\n");
    printf("After HOLD duration expires:\n");
    printf(DIM "System automatically returns to Default Operation (ADD).\n" RESET);
    printf(DIM "----------------------------------------------------\n" RESET);
    printf(BOLD_WHITE "Post-HOLD Default ADD\n" RESET);
    printf(DIM "----------------------------------------------------\n" RESET);
    printf("A + B = 14 + 8 = 22\n");
    printf(BOLD_GREEN "Binary Output = 01101 (22)\n" RESET);
    printf(DIM "----------------------------------------------------\n" RESET);
    printf(BOLD_WHITE "Final System State\n" RESET);
    printf(DIM "----------------------------------------------------\n" RESET);
    printf(CYAN "Register A = 0111 (14)\n" RESET);
    printf(CYAN "Register B = 0001 (8)\n" RESET);
    printf(BOLD_GREEN "Output during HOLD = 0110 (6)\n" RESET);
    printf(BOLD_GREEN "Post-HOLD Output   = 01101 (22)\n" RESET);
    printf(DIM "---------------------------------------------------\n" RESET);
    printf(DIM "// It is advised to Use asm-v0.3 Standard Assembler:\n" RESET);
    printf(DIM "// Features like Syntax and Semantic Analysis.\n" RESET);
    printf(DIM "// Output Error Statements indicating the error.\n" RESET);
    printf(DIM "// Compatible with asm-v0.2 standard.\n" RESET);

    printf("\n");
    print_divider();
}

void sample_p3() {
    printf("\n");
    print_header("P3 - Division");

    printf(DIM "\n// Program Follows asm-v0.2 Standard\n" RESET);
    printf(DIM "// Will Run in asm-v0.2 and asm-v0.3 standard assembler\n" RESET);
    printf(BOLD_GREEN "LOAD-0-0111" RESET DIM " // Load 0111(14) on Data Lines and Store in Register A\n" RESET);
    printf(BOLD_GREEN "LOAD-1-0100" RESET DIM " // Load 0100(2) on Data Lines and Store in Register B\n" RESET);
    printf(BOLD_GREEN "DIV        " RESET DIM " // Divide the Data in Register A from Data in Register B\n" RESET);
    printf(BOLD_GREEN "HOLD-OP    " RESET DIM " // Hold operation/output for arbitrary number of clock cycles\n" RESET);
    printf(DIM "            // HOLD-OP should be sustained for atleast the value of quotient clock cycles\n" RESET);

    printf(DIM "\n---------------------------------------------------\n" RESET);
    printf(BOLD_WHITE "# EXECUTION TRACE\n" RESET);
    printf(DIM "---------------------------------------------------\n" RESET);
    printf("Initial State:\n");
    printf("A = 0000 (0)\n");
    printf("B = 0000 (0)\n");
    printf("Output = 0000 (0)\n");
    printf(DIM "----------------------------------------------------\n" RESET);
    printf(BOLD_WHITE "Program Execution (asm-v0.2 / asm-v0.3)\n" RESET);
    printf(DIM "----------------------------------------------------\n" RESET);
    printf(BOLD_YELLOW "1) LOAD-0-0111\n" RESET);
    printf("   Register A <- 0111 (14)\n");
    printf(BOLD_YELLOW "2) LOAD-1-0100\n" RESET);
    printf("   Register B <- 0100 (2)\n");
    printf("   Current State:\n");
    printf(CYAN "   A = 0111 (14)\n" RESET);
    printf(CYAN "   B = 0100 (2)\n" RESET);
    printf(DIM "----------------------------------------------------\n" RESET);
    printf(BOLD_YELLOW "3) DIV\n" RESET);
    printf(DIM "----------------------------------------------------\n" RESET);
    printf("Operation: A / B\n");
    printf("14 / 2 = 7\n");
    printf("Since division is iterative in hardware,\n");
    printf("the system performs repeated subtraction / convergence\n");
    printf("across multiple clock cycles until a stable quotient is reached.\n");
    printf(DIM "Intermediate Convergence:\n" RESET);
    printf(DIM "Cycle 1: 14 - 2 = 12\n" RESET);
    printf(DIM "Cycle 2: 12 - 2 = 10\n" RESET);
    printf(DIM "Cycle 3: 10 - 2 = 8\n"  RESET);
    printf(DIM "Cycle 4: 8  - 2 = 6\n"  RESET);
    printf(DIM "Cycle 5: 6  - 2 = 4\n"  RESET);
    printf(DIM "Cycle 6: 4  - 2 = 2\n"  RESET);
    printf(DIM "Cycle 7: 2  - 2 = 0\n"  RESET);
    printf("Quotient = 7\n");
    printf(BOLD_GREEN "Binary Output = 1110 (7)\n" RESET);
    printf(CYAN "Divisibility Convergence LED -> ON\n" RESET);
    printf(DIM "(System has reached stable state)\n" RESET);
    printf(DIM "----------------------------------------------------\n" RESET);
    printf(BOLD_YELLOW "4) HOLD-OP\n" RESET);
    printf(DIM "----------------------------------------------------\n" RESET);
    printf("Output held constant at:\n");
    printf(BOLD_GREEN "1110 (7)\n" RESET);
    printf("HOLD-OP must be sustained for at least\n");
    printf("the number of quotient clock cycles to allow\n");
    printf("full convergence and stable output.\n");
    printf("After HOLD duration expires:\n");
    printf(DIM "System automatically returns to Default Operation (ADD)\n" RESET);
    printf(DIM "but Division Output remains latched on the dedicated\n" RESET);
    printf(DIM "division output lines.\n" RESET);
    printf(DIM "----------------------------------------------------\n" RESET);
    printf(BOLD_WHITE "Final System State\n" RESET);
    printf(DIM "----------------------------------------------------\n" RESET);
    printf(CYAN "Register A = 0111 (14)\n" RESET);
    printf(CYAN "Register B = 0100 (2)\n"  RESET);
    printf(BOLD_GREEN "Output     = 1110 (7)\n" RESET);
    printf(CYAN "Divisibility Convergence LED -> ON\n" RESET);
    printf("Indicates quotient stabilization and\n");
    printf("completion of division cycle.\n");
    printf(GREEN "System Stable.\n" RESET);
    printf(GREEN "Clock continues normally.\n" RESET);
    printf(DIM "--------------------------------------------------\n" RESET);
    printf(DIM "// It is advised to Use asm-v0.3 Standard Assembler:\n" RESET);
    printf(DIM "// Features like Syntax and Semantic Analysis.\n" RESET);
    printf(DIM "// Output Error Statements indicating the error.\n" RESET);
    printf(DIM "// Compatible with asm-v0.2 standard.\n" RESET);

    printf("\n");
    print_divider();
}

void sample_p4() {
    printf("\n");
    print_header("P4 - Multiplication");

    printf(DIM "\n// Program Follows asm-v0.2 Standard\n" RESET);
    printf(DIM "// Will Run in asm-v0.2 and asm-v0.3 standard assembler\n" RESET);
    printf(BOLD_GREEN "LOAD-1-0100" RESET DIM " // Load 0100(2) in Register B (Stores Multiplicand)\n" RESET);
    printf(BOLD_GREEN "MUL-0010   " RESET DIM " // Multiply the Multiplicand in Register B from the ( Multiplier - 1 ) -> 3\n" RESET);
    printf(BOLD_GREEN "HOLD-OP    " RESET DIM " // Hold operation/output for arbitrary number of clock cycles\n" RESET);
    printf(DIM "            // HOLD-OP should be sustained for atleast the value of (Multiplier + 1) cycles\n" RESET);
    printf(DIM "# OUTPUT -> Multiplicative Convergance LED will turn ON once the Machine have settled\n" RESET);
    printf(DIM "#           in a stable state indicating successful computation -> 6 (0110)\n" RESET);

    printf(DIM "\n---------------------------------------------------\n" RESET);
    printf(BOLD_WHITE "# EXECUTION TRACE\n" RESET);
    printf(DIM "---------------------------------------------------\n" RESET);
    printf("Initial State:\n");
    printf("A = 0000 (0)\n");
    printf("B = 0000 (0)\n");
    printf("Output = 0000 (0)\n");
    printf(DIM "----------------------------------------------------\n" RESET);
    printf(BOLD_WHITE "Program Execution (asm-v0.2 / asm-v0.3)\n" RESET);
    printf(DIM "----------------------------------------------------\n" RESET);
    printf(BOLD_YELLOW "1) LOAD-1-0100\n" RESET);
    printf("   Register B <- 0100 (2)\n");
    printf("   (Multiplicand stored in Register B)\n");
    printf("   Current State:\n");
    printf(CYAN "   A = 0000 (0)\n" RESET);
    printf(CYAN "   B = 0100 (2)\n" RESET);
    printf(DIM "----------------------------------------------------\n" RESET);
    printf(BOLD_YELLOW "2) MUL-0010\n" RESET);
    printf(DIM "----------------------------------------------------\n" RESET);
    printf("Multiplier Field = 0010 (4)\n");
    printf("Effective Multiplication = B x (Multiplier - 1)\n");
    printf("                         = 2 x 3\n");
    printf("Since multiplication is sequential in hardware,\n");
    printf("the system performs repeated addition / convergence\n");
    printf("across multiple clock cycles until the final product stabilizes.\n");
    printf(DIM "Intermediate Convergence:\n" RESET);
    printf(DIM "Cycle 1: 2\n"         RESET);
    printf(DIM "Cycle 2: 2 + 2 = 4\n" RESET);
    printf(DIM "Cycle 3: 4 + 2 = 6\n" RESET);
    printf("Final Product = 6\n");
    printf(BOLD_GREEN "Binary Output = 0110 (6)\n" RESET);
    printf(CYAN "Multiplicative Convergence LED -> ON\n" RESET);
    printf(DIM "(Indicates product stabilization and completion of multiplication cycle)\n" RESET);
    printf(DIM "----------------------------------------------------\n" RESET);
    printf(BOLD_YELLOW "3) HOLD-OP\n" RESET);
    printf(DIM "----------------------------------------------------\n" RESET);
    printf("Output held constant at:\n");
    printf(BOLD_GREEN "0110 (6)\n" RESET);
    printf("HOLD-OP must be sustained for at least\n");
    printf("(Multiplier + 1) clock cycles to allow\n");
    printf("full convergence and stable output visibility.\n");
    printf("After HOLD duration expires:\n");
    printf(DIM "System automatically returns to Default Operation (ADD).\n" RESET);
    printf(DIM "But MUL Output remains stable after HOLD-OP as multiplication\n" RESET);
    printf(DIM "is implemented using repeated Addition using Register A and B.\n" RESET);
    printf(DIM "----------------------------------------------------\n" RESET);
    printf(BOLD_WHITE "Final System State\n" RESET);
    printf(DIM "----------------------------------------------------\n" RESET);
    printf(CYAN "Register A = 0000 (0)\n" RESET);
    printf(CYAN "Register B = 0100 (2)\n" RESET);
    printf(BOLD_GREEN "Output     = 0110 (6)\n" RESET);
    printf(CYAN "Multiplicative Convergence LED = ON\n" RESET);
    printf(GREEN "System Stable.\n" RESET);
    printf(GREEN "Clock continues normally.\n" RESET);
    printf(DIM "----------------------------------------------------\n" RESET);
    printf(DIM "// It is advised to Use asm-v0.3 Standard Assembler:\n" RESET);
    printf(DIM "// Features like Syntax and Semantic Analysis.\n" RESET);
    printf(DIM "// Output Error Statements indicating the error.\n" RESET);
    printf(DIM "// Compatible with asm-v0.2 standard.\n" RESET);

    printf("\n");
    print_divider();
}

void sample_p5() {
    printf("\n");
    print_header("P5 - Overflow & Recovery");

    printf(DIM "\n// Program Follows asm-v0.2 Standard\n" RESET);
    printf(DIM "// Will Run in asm-v0.2 and asm-v0.3 standard assembler\n" RESET);
    printf(BOLD_GREEN "LOAD-0-0010" RESET DIM " // Load 0010(4) in Register B\n" RESET);
    printf(BOLD_GREEN "LOAD-1-0001" RESET DIM " // Load 0001(8) in Register A\n" RESET);
    printf(BOLD_GREEN "ADD        " RESET DIM " // A + B, Default Operation\n" RESET);
    printf(BOLD_GREEN "FBK        " RESET DIM " // Feed output back to A\n" RESET);
    printf(BOLD_GREEN "ADD        " RESET DIM " // A + B, Default Operation\n" RESET);
    printf(BOLD_GREEN "FBK        " RESET DIM " // Feed output back to A\n" RESET);
    printf(BOLD_GREEN "HOLD-OP    " RESET DIM " // Hold operation/output\n" RESET);
    printf(BOLD_GREEN "OVRD       " RESET DIM " // Override System Halt\n" RESET);
    printf(BOLD_GREEN "FBK        " RESET DIM " // Feed output back to A\n" RESET);

    printf(DIM "\n---------------------------------------------------\n" RESET);
    printf(BOLD_WHITE "# EXECUTION TRACE\n" RESET);
    printf(DIM "---------------------------------------------------\n" RESET);
    printf("Initial State:\n");
    printf(CYAN "A = 0001 (8)\n" RESET);
    printf(CYAN "B = 0010 (4)\n" RESET);
    printf("Output = 0000 (0)\n");
    printf(DIM "----------------------------------------------------\n" RESET);
    printf(BOLD_YELLOW "1) ADD  (Default Operation)\n" RESET);
    printf(DIM "----------------------------------------------------\n" RESET);
    printf("A + B = 8 + 4 = 12\n");
    printf(BOLD_GREEN "Binary Output = 0011 (12)\n" RESET);
    printf(DIM "----------------------------------------------------\n" RESET);
    printf(BOLD_YELLOW "2) FBK  (Feedback)\n" RESET);
    printf(DIM "----------------------------------------------------\n" RESET);
    printf("Register A <- 0011 (12)\n");
    printf("Current State:\n");
    printf(CYAN "A = 0011 (12)\n" RESET);
    printf(CYAN "B = 0010 (4)\n"  RESET);
    printf(DIM "----------------------------------------------------\n" RESET);
    printf(BOLD_YELLOW "3) ADD\n" RESET);
    printf(DIM "----------------------------------------------------\n" RESET);
    printf("A + B = 12 + 4 = 16\n");
    printf(YELLOW "Binary Output = 00001 (16)\n" RESET);
    printf(YELLOW "(5-bit result exceeds 4-bit register width)\n" RESET);
    printf(DIM "----------------------------------------------------\n" RESET);
    printf(BOLD_RED "Overflow Detection\n" RESET);
    printf(DIM "----------------------------------------------------\n" RESET);
    printf("Since the result occupies the 5th bit,\n");
    printf("it cannot be stored within the 4-bit register width\n");
    printf("with feedback.\n");
    printf(YELLOW "Overflow Condition Triggered.\n" RESET);
    printf("System Response:\n");
    printf(YELLOW "- Overflow Detection Logic Activated\n" RESET);
    printf(YELLOW "- Clock Disengaged\n" RESET);
    printf(YELLOW "- System Halted\n" RESET);
    printf(YELLOW "- LEDs ON:\n" RESET);
    printf(YELLOW "    * Clock Disengaged\n" RESET);
    printf(YELLOW "    * System Halted\n" RESET);
    printf(YELLOW "    * Feedback Overflow\n" RESET);
    printf(DIM "Architectural State Preserved.\n" RESET);
    printf(DIM "----------------------------------------------------\n" RESET);
    printf(BOLD_YELLOW "4) HOLD-OP\n" RESET);
    printf(DIM "----------------------------------------------------\n" RESET);
    printf("Output held constant at:\n");
    printf(YELLOW "00001 (16)\n" RESET);
    printf("System remains halted until override.\n");
    printf(DIM "----------------------------------------------------\n" RESET);
    printf(BOLD_YELLOW "5) OVRD  (Override)\n" RESET);
    printf(DIM "----------------------------------------------------\n" RESET);
    printf(CYAN "Clock Re-enabled.\n" RESET);
    printf(CYAN "System resumes from halted state.\n" RESET);
    printf(DIM "----------------------------------------------------\n" RESET);
    printf(BOLD_YELLOW "6) FBK\n" RESET);
    printf(DIM "----------------------------------------------------\n" RESET);
    printf("Feedback attempts to store output into Register A.\n");
    printf("Since only lower 4 bits can be stored:\n");
    printf(YELLOW "00001 -> 0000 (lower 4 bits)\n" RESET);
    printf("Register A <- 0000 (0)\n");
    printf("Current State:\n");
    printf(CYAN "A = 0000 (0)\n" RESET);
    printf(CYAN "B = 0010 (4)\n" RESET);
    printf("Subsequent Default ADD:\n");
    printf("A + B = 0 + 4 = 4\n");
    printf(BOLD_GREEN "Binary Output = 0010 (4)\n" RESET);
    printf(DIM "----------------------------------------------------\n" RESET);
    printf(BOLD_WHITE "Final System State\n" RESET);
    printf(DIM "----------------------------------------------------\n" RESET);
    printf(CYAN "Register A = 0000 (0)\n" RESET);
    printf(CYAN "Register B = 0010 (4)\n" RESET);
    printf(BOLD_GREEN "Output     = 0010 (4)\n" RESET);
    printf(YELLOW "Overflow condition was overridden.\n" RESET);
    printf(YELLOW "Computation integrity lost after OVRD.\n" RESET);
    printf(GREEN "System running normally.\n" RESET);
    printf(DIM "----------------------------------------------------\n" RESET);
    printf(DIM "// It is advised to Use asm-v0.3 Standard Assembler:\n" RESET);
    printf(DIM "// Features like Syntax and Semantic Analysis.\n" RESET);
    printf(DIM "// Output Error Statements indicating the error.\n" RESET);
    printf(DIM "// Compatible with asm-v0.2 standard.\n" RESET);

    printf("\n");
    print_divider();
}

void sample_p6() {
    printf("\n");
    print_header("P6 - Machine Reset");

    printf(DIM "\n// Program Follows asm-v0.2 Standard\n" RESET);
    printf(DIM "// Will Run in asm-v0.2 and asm-v0.3 standard assembler\n" RESET);
    printf(BOLD_GREEN "LOAD-1-1000" RESET DIM " // Load 1000(1) in Register A\n" RESET);
    printf(BOLD_GREEN "LOAD-0-0010" RESET DIM " // Load 0010(4) in Register B\n" RESET);
    printf(BOLD_GREEN "ADD        " RESET DIM " // A + B\n" RESET);
    printf(BOLD_GREEN "RSTM       " RESET DIM " // Clears the Machine\n" RESET);

    printf(DIM "\n---------------------------------------------------\n" RESET);
    printf(BOLD_WHITE "# EXECUTION TRACE\n" RESET);
    printf(DIM "---------------------------------------------------\n" RESET);
    printf("Initial State:\n");
    printf("A = 0000 (0)\n");
    printf("B = 0000 (0)\n");
    printf("Output = 0000 (0)\n");
    printf(DIM "----------------------------------------------------\n" RESET);
    printf(BOLD_YELLOW "1) LOAD-1-1000\n" RESET);
    printf(DIM "----------------------------------------------------\n" RESET);
    printf("Register A <- 1000 (1)\n");
    printf("Current State:\n");
    printf(CYAN "A = 1000 (1)\n" RESET);
    printf(CYAN "B = 0000 (0)\n" RESET);
    printf(DIM "----------------------------------------------------\n" RESET);
    printf(BOLD_YELLOW "2) LOAD-0-0010\n" RESET);
    printf(DIM "----------------------------------------------------\n" RESET);
    printf("Register B <- 0010 (4)\n");
    printf("Current State:\n");
    printf(CYAN "A = 1000 (1)\n" RESET);
    printf(CYAN "B = 0010 (4)\n" RESET);
    printf(DIM "----------------------------------------------------\n" RESET);
    printf(BOLD_YELLOW "3) ADD  (Default Operation)\n" RESET);
    printf(DIM "----------------------------------------------------\n" RESET);
    printf("A + B = 1 + 4 = 5\n");
    printf(BOLD_GREEN "Binary Output = 1010 (5)\n" RESET);
    printf("Current State:\n");
    printf(CYAN "A = 1000 (1)\n" RESET);
    printf(CYAN "B = 0010 (4)\n" RESET);
    printf(BOLD_GREEN "Output = 1010 (5)\n" RESET);
    printf(DIM "----------------------------------------------------\n" RESET);
    printf(BOLD_YELLOW "4) RSTM  (Reset Machine)\n" RESET);
    printf(DIM "----------------------------------------------------\n" RESET);
    printf(CYAN "Machine Reset Triggered.\n" RESET);
    printf("All Registers Cleared:\n");
    printf(CYAN "A = 0000 (0)\n" RESET);
    printf(CYAN "B = 0000 (0)\n" RESET);
    printf("All Output Lines Cleared:\n");
    printf("Output = 0000 (0)\n");
    printf("All Control Flags Cleared:\n");
    printf(DIM "- Overflow = OFF\n" RESET);
    printf(DIM "- Convergence LEDs = OFF\n" RESET);
    printf(DIM "- Halt State = Cleared\n" RESET);
    printf(DIM "Clock continues in normal reset state.\n" RESET);
    printf(DIM "----------------------------------------------------\n" RESET);
    printf(BOLD_WHITE "Final System State\n" RESET);
    printf(DIM "----------------------------------------------------\n" RESET);
    printf(CYAN "Register A = 0000 (0)\n" RESET);
    printf(CYAN "Register B = 0000 (0)\n" RESET);
    printf(BOLD_GREEN "Output     = 0000 (0)\n" RESET);
    printf(GREEN "Machine fully reset.\n" RESET);
    printf(DIM "----------------------------------------------------\n" RESET);
    printf(DIM "// It is advised to Use asm-v0.3 Standard Assembler:\n" RESET);
    printf(DIM "// Features like Syntax and Semantic Analysis.\n" RESET);
    printf(DIM "// Output Error Statements indicating the error.\n" RESET);
    printf(DIM "// Compatible with asm-v0.2 standard.\n" RESET);

    printf("\n");
    print_divider();
}

void manual_samples() {
    samples_index();
}

// ─────────────────────────────────────────
// MAIN
// ─────────────────────────────────────────

int main(int argc, char *argv[]) {

    if (argc >= 3 && strcmp(argv[1], "--search") == 0) {
        search(argv[2]);
        return 0;
    }

    if (argc == 2 && strcmp(argv[1], "--search") == 0) {
        printf(BOLD_WHITE "Usage  : " RESET "./asm-manual --search <mnemonic>\n");
        printf(BOLD_WHITE "Example: " RESET "./asm-manual --search LOAD\n");
        return 1;
    }

    char input[20];

    printf("\n");
    print_divider();
    printf(DIM "|" RESET BOLD_CYAN "  %-52s" RESET DIM "|" RESET "\n", "ASM Language Manual");
    printf(DIM "|" RESET "  %-52s" DIM "|" RESET "\n", "Custom Hardware Assembler Docs");
    print_divider();
    printf(DIM " Tip: " RESET "search a mnemonic directly from terminal:\n");
    printf(CYAN "      ./asm-manual --search LOAD\n" RESET);

    while (1) {
        printf("\n" DIM " Available: " RESET
               CYAN "v0.1" RESET " | "
               CYAN "v0.2" RESET " | "
               CYAN "v0.3" RESET " | "
               CYAN "all"  RESET " | "
               CYAN "samples" RESET " | "
               CYAN "search" RESET " | "
               CYAN "exit" RESET "\n");
        printf(BOLD_WHITE " Enter command: " RESET);
        scanf("%s", input);

        if (strcmp(input, "v0.1") == 0) {
            manual_v01();
        } else if (strcmp(input, "v0.2") == 0) {
            manual_v02();
        } else if (strcmp(input, "v0.3") == 0) {
            manual_v03();
        } else if (strcmp(input, "all") == 0) {
            manual_all();
        } else if (strcmp(input, "samples") == 0) {
            manual_samples();
            printf(BOLD_WHITE " Enter program (P1-P6) or back: " RESET);
            char prog[10];
            scanf("%s", prog);
            if      (strcmp(prog, "P1") == 0 || strcmp(prog, "p1") == 0) sample_p1();
            else if (strcmp(prog, "P2") == 0 || strcmp(prog, "p2") == 0) sample_p2();
            else if (strcmp(prog, "P3") == 0 || strcmp(prog, "p3") == 0) sample_p3();
            else if (strcmp(prog, "P4") == 0 || strcmp(prog, "p4") == 0) sample_p4();
            else if (strcmp(prog, "P5") == 0 || strcmp(prog, "p5") == 0) sample_p5();
            else if (strcmp(prog, "P6") == 0 || strcmp(prog, "p6") == 0) sample_p6();
            else if (strcmp(prog, "back") != 0)
                printf(BOLD_RED "\n [ERROR]" RESET " Unknown program '%s'\n", prog);
        } else if (strcmp(input, "search") == 0) {
            char query[50];
            printf(BOLD_WHITE " Enter mnemonic to search: " RESET);
            scanf("%s", query);
            search(query);
        } else if (strcmp(input, "exit") == 0) {
            printf(BOLD_GREEN "\n Goodbye!\n" RESET);
            break;
        } else {
            printf(BOLD_RED "\n [ERROR]" RESET " Unknown input '%s'\n", input);
            printf(DIM " Try: v0.1, v0.2, v0.3, all, samples, search, exit\n" RESET);
        }
    }

    return 0;
}
