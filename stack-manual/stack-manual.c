// ============================================================
//  stack-manual.c
// ------------------------------------------------------------
//  This project began from a simple idea: what if the output
//  of an arithmetic operation could be fed back into the
//  input? From that single idea, an entire computing stack
//  was built from scratch.
//
//  Layer 1 - Hardware: The Repeated Arithmetic Machine (RAM)
//  evolved from a proof of concept into a full autonomous
//  computing machine with stored program execution.
//
//  Layer 2 - Software: The Assembly Language was built on top
//  of the RAM machine code. After mapping all machine code
//  instructions to english-like mnemonics, the Assembly
//  Language was born. The Assembler translates it back down.
//
//  This manual covers the full stack. Bottom to top.
//  RAM hardware first. Assembly language on top.
//  One reference for the entire system.
// ------------------------------------------------------------
//  Projects : Computing Machinery from Scratch
//             Assembler for Custom Hardware
//  File     : stack-manual.c
//  Layer 1  : RAM Engine (V0), V1, V2, V3, V4
//  Layer 2  : asm-v0.1, asm-v0.2, asm-v0.3 + Sample Programs
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

void print_bullet(char *text) {
    printf(GREEN "   * " RESET "%s\n", text);
}

void print_limitation(char *text) {
    printf(YELLOW "   ! " RESET "%s\n", text);
}

void print_step(int num, char *text) {
    printf(CYAN "   %d. " RESET "%s\n", num, text);
}

void print_arrow(char *key, char *value) {
    printf("      " CYAN "%s" RESET " -> %s\n", key, value);
}

void print_bit(char *bit, char *value) {
    printf("   " CYAN "%-8s" RESET "-> %s\n", bit, value);
}

void print_field(char *key, char *value) {
    printf(CYAN "   %-12s" RESET ": %s\n", key, value);
}

void print_mnemonic(int num, char *name) {
    printf("\n" BOLD_YELLOW "  [%d] %s" RESET "\n", num, name);
}

void print_mfield(char *key, char *value) {
    printf(CYAN "       %-10s" RESET ": %s\n", key, value);
}

void print_note(char *note) {
    printf(DIM "       Note      : %s" RESET "\n", note);
}

void print_marrow(char *key, char *value) {
    printf("       " CYAN "%s" RESET " -> %s\n", key, value);
}

// ─────────────────────────────────────────
// RAM COMPONENT DATABASE
// ─────────────────────────────────────────

typedef struct {
    char name[40];
    char version[20];
    char function[300];
    char note[300];
} Component;

Component ram_components[] = {
    { "Selector Pin",            "RAM V0+", "Selects the arithmetic operation to perform.", "Selector = 0 -> Addition | Selector = 1 -> Subtraction" },
    { "Feedback Pin",            "RAM V0+", "Feeds the output back into input A for chained operations.", "Core idea of the machine. Output of one operation becomes input of the next." },
    { "Reset Pin",               "RAM V0+", "Resets the machine state.", "Clears registers and output back to initial state." },
    { "Output Pin",              "RAM V0+", "Outputs the result of the arithmetic operation.", "4-bit output. Goes past 15 on overflow in V0 and V1. Handled automatically from V3." },
    { "2s Complement",           "RAM V1+", "Handles negative results from subtraction using 2s complement representation.", "V1: manual B>A pin required. V2: automatic B>A detection via comparator. V3+: fully automated." },
    { "Manual B>A Pin",          "RAM V1",  "Manual pin to indicate B > A before subtraction for correct 2s complement output.", "Only in V1. Removed in V2 where comparator automatically detects B > A condition." },
    { "Comparator",              "RAM V2+", "Automatically detects if B > A before subtraction.", "Removes need for manual B>A pin. Triggers 2s complement correction automatically." },
    { "Overflow Detection",      "RAM V3+", "Detects when result exceeds 4-bit range (above 15 or below 0).", "Triggers automatic halt to prevent data corruption. Overflow type indicators show which kind of overflow occurred." },
    { "Auto Halt",               "RAM V3+", "Automatically halts the machine to prevent data corruption on overflow.", "Part of the self-correction system. Machine stops before bad data propagates." },
    { "Signed Result Handling",  "RAM V3+", "Handles signed results correctly for all arithmetic operations.", "Works with the subtraction output form correction unit for correct signed output." },
    { "Subtraction Correction",  "RAM V3+", "Corrects subtraction output form automatically.", "Works alongside signed result handling. No manual intervention required." },
    { "Flip Flop Detector",      "RAM V3+", "Simultaneous activation detector for series flip flops.", "Prevents race conditions and incorrect state transitions in the sequential logic." },
    { "Overshoot Correction",    "RAM V3+", "Corrects output overshoot during arithmetic operations.", "Catches cases where intermediate results temporarily exceed valid range." },
    { "Convergence Detector",    "RAM V3+", "Multiplicative and Divisibility Convergence detectors.", "Detects when multiplication or division has reached its final converged result." },
    { "Edge Case Handler",       "RAM V3+", "Handles edge cases like division by zero and multiplication by zero.", "Prevents undefined behavior. Machine responds gracefully to invalid mathematical operations." },
    { "Invalid Input Detector",  "RAM V3+", "Detects invalid input forms before processing.", "Catches malformed or out of range inputs before they corrupt machine state." },
    { "Program Memory",          "RAM V4",  "Stores machine code instructions for sequential execution.", "Each module stores 4 instructions of 16 bits each = 8 bytes. Two modules connected = 16 bytes. More modules can be chained for larger programs. Pins labeled Ix_y where x=instruction number, y=bit." },
    { "Interface Module",        "RAM V4",  "D flip-flop set directly connected to machine. Holds currently executing instruction.", "Acts as interface between program memory and machine. Instructions flow from memory through interface module to control the machine." },
    { "Instruction Format",      "RAM V4",  "16-bit instruction format for machine code programming.", "Bit1=Feedback | Bit2=Store | Bit3=Selector | Bit4=Data1 | Bit5=Mode | Bit6=Reset | Bit7=Data2 | Bit8=Multiply | Bit9=Divide | Bit10=Override Halt | Bit11=Data4 | Bit12=Data8 | Bit13=Multiplier1 | Bit14=Multiplier2 | Bit15=Multiplier4 | Bit16=Multiplier8" },
    { "Load Pins",               "RAM V4",  "Initial load pins used to manually enter instructions into program memory.", "Set instruction bits, make Load_Ix high to store. Remove from load pins after storing or machine will keep re-executing that instruction." },
    { "Multiplication",          "RAM V3+", "Repeated addition based multiplication.", "Uses convergence detector to know when result is reached. Edge case: multiply by zero handled." },
    { "Division",                "RAM V3+", "Repeated subtraction based division.", "Uses convergence detector to know when result is reached. Edge case: divide by zero handled." },
    { "Addition",                "RAM V0+", "Default arithmetic operation of the machine.", "Selector = 0. No overflow detection in V0 and V1. Full overflow handling from V3." },
    { "Subtraction",             "RAM V0+", "Arithmetic subtraction. Result may go negative.", "V0: errors below 0. V1: manual B>A correction. V2: auto correction. V3: fully automated signed handling." },
};
int ram_component_count = 24;

// ─────────────────────────────────────────
// ASM MNEMONIC DATABASE
// ─────────────────────────────────────────

typedef struct {
    char name[20];
    char version[20];
    char syntax[30];
    char function[200];
    char note[200];
} Mnemonic;

Mnemonic mnemonics[] = {
    { "LOAD",  "v0.1+",    "LOAD-S-XXXX", "Loads data onto the data lines. In v0.1 a separate STORE is needed. From v0.2 onward LOAD handles storing automatically.", "S=0 -> Register A | S=1 -> Register B | XXXX = 4 binary bits (weight 8,4,2,1) | Bit 0 is MSB (weight 8), Bit 3 is LSB (weight 1)" },
    { "STORE", "v0.1 only","STORE",        "Stores data on lines to the selected register.", "Only exists in v0.1. From v0.2 onward STORE is abstracted away -- LOAD handles both loading and storing automatically." },
    { "FBK",   "v0.2+",    "FBK",          "Feeds the ALU output back into Register A, overriding its current contents.", "Useful for chaining arithmetic operations using the result of the previous one." },
    { "ADD",   "v0.2+",    "ADD",          "Default arithmetic operation of the machine. Adds Register A and Register B.", "No machine code required. Outputs: DEFAULT ARITHMETIC OPERATION." },
    { "SUB",   "v0.2+",    "SUB",          "Subtracts Register B from Register A.", "Use HOLD-OP after SUB to retain result before default ADD takes over." },
    { "DIV",   "v0.2+",    "DIV",          "Divides Register A by Register B.", "Use HOLD-OP for at least (quotient) clock cycles after DIV." },
    { "MUL",   "v0.2+",    "MUL-XXXX",     "Multiplies Register B by (XXXX value - 1).", "XXXX -> weights 1,2,4,8 | Example: 0010 -> value=4, multiplier=3 | Use HOLD-OP for at least (multiplier+1) cycles." },
    { "OVRD",  "v0.2+",    "OVRD",         "Overrides the system halt caused by overflow errors.", "Use when you want to continue execution despite overflow." },
    { "RSTM",  "v0.2+",    "RSTM",         "Resets the entire machine. All registers and lines go to 0.", "Full hardware reset. Clock cycle counter also resets." },
    { "HOLD",  "v0.2+",    "HOLD-OP",      "Keeps the result of an arithmetic operation on output lines for N clock cycles.", "Critical for synchronizing hardware. For MUL hold (multiplier+1) cycles. For DIV hold (quotient) cycles." },
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
// UNIFIED SEARCH
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

    // Search RAM components
    for (int i = 0; i < ram_component_count; i++) {
        char name_upper[40];
        char func_upper[300];
        char note_upper[300];

        strncpy(name_upper, ram_components[i].name,     39);  name_upper[39]  = '\0';
        strncpy(func_upper, ram_components[i].function, 299); func_upper[299] = '\0';
        strncpy(note_upper, ram_components[i].note,     299); note_upper[299] = '\0';

        to_upper(name_upper);
        to_upper(func_upper);
        to_upper(note_upper);

        if (strstr(name_upper, q) ||
            strstr(func_upper, q) ||
            strstr(note_upper, q)) {

            printf("\n");
            printf(BOLD_YELLOW "  Component" RESET " : " BOLD_WHITE "%s" RESET "\n", ram_components[i].name);
            printf(CYAN        "  Layer    " RESET " : Layer 1 - RAM Hardware\n");
            printf(CYAN        "  Version  " RESET " : %s\n", ram_components[i].version);
            printf(            "  Function  : %s\n", ram_components[i].function);
            printf(DIM         "  Notes     : %s" RESET "\n", ram_components[i].note);
            printf(DIM "\n  ------------------------------------------------------" RESET "\n");
            found++;
        }
    }

    // Search ASM mnemonics
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
            printf(BOLD_YELLOW "  Mnemonic " RESET " : " BOLD_WHITE "%s" RESET "\n", mnemonics[i].name);
            printf(CYAN        "  Layer    " RESET " : Layer 2 - Assembly Language\n");
            printf(CYAN        "  Version  " RESET " : %s\n", mnemonics[i].version);
            printf(CYAN        "  Syntax   " RESET " : %s\n", mnemonics[i].syntax);
            printf(            "  Function  : %s\n", mnemonics[i].function);
            printf(DIM         "  Notes     : %s" RESET "\n", mnemonics[i].note);
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

// ═══════════════════════════════════════════
// LAYER 1 - RAM HARDWARE
// ═══════════════════════════════════════════

void manual_v0() {
    printf("\n");
    print_header("RAM Engine (V0) - Proof of Concept");

    print_section("ABOUT");
    printf(" The very first implementation of the Repeated\n");
    printf(" Arithmetic Machine idea. A proof of concept that\n");
    printf(" repeated arithmetic and feedback could form the\n");
    printf(" basis of a machine.\n");

    print_section("FEATURES");
    print_bullet("Supports Addition and Subtraction");
    print_bullet("Selector pin to choose operation");
    print_bullet("Feedback pin to feed output back to input A");
    print_bullet("Reset pin to clear machine state");
    print_bullet("Output pin for result");

    print_section("HOW TO USE");
    print_step(1, "Feed input to A and B");
    print_step(2, "Choose mode via Selector pin");
    print_arrow("Selector = 0", "Addition");
    print_arrow("Selector = 1", "Subtraction");
    print_step(3, "Read output");
    print_step(4, "Feed output back to A via Feedback pin");
    printf("      for further chained operations\n");

    print_section("LIMITATIONS");
    print_limitation("No error correction");
    print_limitation("No overflow detection");
    print_limitation("Gives errors if result goes below 0 (subtraction)");
    print_limitation("Gives errors if result goes past 15 (addition)");

    print_section("CIRCUIT FILE");
    printf("   r_a_m_Engine.circ\n");

    printf("\n");
    print_divider();
}

void manual_v1() {
    printf("\n");
    print_header("RAM V1 - 2s Complement Handling");

    print_section("ABOUT");
    printf(" A minimal extension to the RAM Engine.\n");
    printf(" Introduces 2s complement result handling for\n");
    printf(" subtraction when result goes negative.\n");

    print_section("FEATURES");
    print_bullet("All features of V0");
    print_bullet("Handles 2s complement result");
    print_bullet("Outputs correct result for negative subtraction");
    print_bullet("Manual B>A pin for subtraction correction");

    print_section("HOW TO USE");
    print_step(1, "Feed input to A and B");
    print_step(2, "If performing subtraction and B > A:");
    printf("      Set the manual B>A pin HIGH before operation\n");
    printf("      This enables 2s complement correction\n");
    print_step(3, "Choose mode via Selector pin");
    print_step(4, "Read corrected output");

    print_section("LIMITATIONS");
    print_limitation("No overflow detection");
    print_limitation("Must manually check and set B>A pin");
    print_limitation("Human intervention still required");

    print_section("CIRCUIT FILE");
    printf("   r_a_mv1.circ  (in RAM_V1 folder)\n");

    printf("\n");
    print_divider();
}

void manual_v2() {
    printf("\n");
    print_header("RAM V2 - Automated 2s Complement");

    print_section("ABOUT");
    printf(" Full automation for 2s complement result handling.\n");
    printf(" Minimal extension to V1 -- now with automatic\n");
    printf(" correction for negative results. No manual\n");
    printf(" intervention needed.\n");

    print_section("FEATURES");
    print_bullet("All features of V1");
    print_bullet("Automatically detects if B > A using comparator");
    print_bullet("Corrects 2s complement output automatically");
    print_bullet("No manual B>A pin required");

    print_section("HOW TO USE");
    print_step(1, "Feed input to A and B");
    print_step(2, "Choose mode via Selector pin");
    print_step(3, "Machine automatically handles B > A case");
    print_step(4, "Read corrected output directly");
    printf("   No manual adjustments needed.\n");

    print_section("LIMITATIONS");
    print_limitation("Overflow detection still not implemented");

    print_section("CIRCUIT FILE");
    printf("   r_a_mv2.circ  (in RAM_V2 folder)\n");

    printf("\n");
    print_divider();
}

void manual_v3() {
    printf("\n");
    print_header("RAM V3 - Full Autonomous Arithmetic Machine");

    print_section("ABOUT");
    printf(" Full-fledged autonomous Repeated Arithmetic Machine.\n");
    printf(" Self-aware, self-correcting and intelligent system\n");
    printf(" with over 400 logic gates.\n");
    printf(" Developed iteratively from Engine through V1 and V2,\n");
    printf(" now incorporating advanced automation and full\n");
    printf(" error handling.\n");

    print_section("FEATURES");
    print_bullet("Output feedback system");
    print_bullet("Overflow error detection system");
    print_bullet("Overflow type indicators");
    print_bullet("Signed result handling");
    print_bullet("Automatic halting to prevent data corruption");
    print_bullet("Subtraction output form correction unit");
    print_bullet("Simultaneous activation detectors for flip flops");
    print_bullet("Output overshoot correction logic");
    print_bullet("Multiplicative convergence detector");
    print_bullet("Divisibility convergence detector");
    print_bullet("Edge case handling (division/multiplication by 0)");
    print_bullet("Invalid input form detector");
    print_bullet("Division, Multiplication, Addition, Subtraction");

    print_section("HOW TO USE");
    print_step(1, "Feed input to A and B");
    print_step(2, "Choose operation");
    printf("      Default: Addition\n");
    printf("      Selector pin: Subtraction\n");
    printf("      Multiply/Divide pins for those operations\n");
    print_step(3, "Machine handles all corrections automatically");
    print_step(4, "Watch output LEDs for feedback and corrections");
    print_step(5, "Overflow indicators will flag if result is");
    printf("      out of valid 4-bit range\n");
    print_step(6, "Machine auto-halts on overflow to prevent");
    printf("      data corruption\n");

    print_section("SIGNIFICANCE");
    printf("   Demonstrates a complete autonomous arithmetic\n");
    printf("   computing system built from first principles\n");
    printf("   using logic gates. Showcases modular design,\n");
    printf("   iterative development and intelligent automation.\n");

    print_section("CIRCUIT FILE");
    printf("   r_a_mv3.circ  (in RAM_V3 folder)\n");

    printf("\n");
    print_divider();
}

void manual_v4() {
    printf("\n");
    print_header("RAM V4 - Stored Program Architecture");

    print_section("ABOUT");
    printf(" Programmable stored instruction system.\n");
    printf(" Instructions in machine code are stored in memory\n");
    printf(" and executed sequentially. Instead of manually\n");
    printf(" controlling each operation, V4 loads and executes\n");
    printf(" a sequence of instructions stored in memory.\n");
    printf(" Bridges the gap between data processing (V3) and\n");
    printf(" instruction processing (V4).\n");

    print_section("FEATURES");
    print_bullet("All features of V3");
    print_bullet("Memory unit to store the program");
    print_bullet("Sequential instruction execution");
    print_bullet("16-bit instruction format");
    print_bullet("Expandable memory via chained modules");
    print_bullet("No intervention needed after program load");

    print_section("16-BIT INSTRUCTION FORMAT");
    print_bit("Bit 1 ", "Feedback");
    print_bit("Bit 2 ", "Store");
    print_bit("Bit 3 ", "Selector");
    print_bit("Bit 4 ", "Data1");
    print_bit("Bit 5 ", "Mode");
    print_bit("Bit 6 ", "Reset");
    print_bit("Bit 7 ", "Data2");
    print_bit("Bit 8 ", "Multiply");
    print_bit("Bit 9 ", "Divide");
    print_bit("Bit 10", "Override System Halt");
    print_bit("Bit 11", "Data4");
    print_bit("Bit 12", "Data8");
    print_bit("Bit 13", "Multiplier = 1");
    print_bit("Bit 14", "Multiplier = 2");
    print_bit("Bit 15", "Multiplier = 4");
    print_bit("Bit 16", "Multiplier = 8");

    print_section("PROGRAM MEMORY");
    printf("   Pins labeled as Ix_y:\n");
    printf("     x = instruction number\n");
    printf("     y = instruction bit\n");
    printf("   Each module: 4 instructions x 16 bits = 8 bytes\n");
    printf("   Two modules connected = 16 bytes total\n");
    printf("   More modules can be chained for larger programs\n");
    printf("   Made up of sets of 16 D-flip flops\n");
    printf("   Interface module holds currently executing instruction\n");

    print_section("LOADING A PROGRAM");
    print_step(1, "Enter instruction bits via initial load pins");
    print_step(2, "Make Load_Ix pin HIGH to store instruction");
    print_step(3, "Remove instruction from load pins after storing");
    printf("      (if not removed, machine keeps re-executing it)\n");
    print_step(4, "Repeat for each instruction");
    print_step(5, "Ix_y where x=1,2,3,4 is execution sequence order");

    print_section("ARITHMETIC OPERATION SIGNALS");
    print_field("Default", "Addition");
    print_field("Subtraction", "Set Bit 5 (Mode) HIGH");
    print_field("Division", "Set Bit 9 HIGH");
    print_field("Multiplication", "Set Bit 8 HIGH");
    printf("               + Set Multiplier bits (13-16)\n");

    print_section("HOW TO USE");
    print_step(1, "Open r_a_mv4.circ in Logisim Evolution");
    print_step(2, "Start with small programs (load data + add)");
    print_step(3, "Understand instruction format before programming");
    print_step(4, "Refer V3 to understand how operations are");
    printf("      implemented in hardware before writing programs\n");
    print_step(5, "Load program via load pins");
    print_step(6, "Initiate execution");
    print_step(7, "Observe sequential autonomous operation");

    print_section("SIGNIFICANCE");
    printf("   Represents a significant step towards understanding\n");
    printf("   and recreating principles behind early programmable\n");
    printf("   computers. Demonstrates how instructions stored in\n");
    printf("   memory and executed sequentially forms the basis\n");
    printf("   of the Stored Program Execution model.\n");

    print_section("CIRCUIT FILE");
    printf("   r_a_mv4.circ  (in RAM_v4 folder)\n");

    printf("\n");
    print_divider();
}

void ram_all() {
    printf("\n");
    print_header("Layer 1: RAM - All Versions");
    printf(CYAN "  V0" RESET " -> Proof of concept, ADD + SUB, no error handling\n");
    printf(CYAN "  V1" RESET " -> 2s complement, manual B>A correction\n");
    printf(CYAN "  V2" RESET " -> Auto B>A detection, automated correction\n");
    printf(CYAN "  V3" RESET " -> Full autonomous machine, 400+ gates\n");
    printf(CYAN "  V4" RESET " -> Stored program architecture, 16-bit instructions\n");
    printf(DIM "\n Showing all RAM versions...\n" RESET);
    manual_v0();
    manual_v1();
    manual_v2();
    manual_v3();
    manual_v4();
}

// ═══════════════════════════════════════════
// LAYER 2 - ASSEMBLY LANGUAGE
// ═══════════════════════════════════════════

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
    print_mfield("Function", "Loads data onto the data lines.");
    print_mfield("S", "Selector pin to choose register.");
    print_marrow("S=0", "Register A");
    print_marrow("S=1", "Register B");
    print_mfield("XXXX", "4 binary bits, weights 1,2,4,8.");
    printf("                Example: 0011 -> 8+4 = 12\n");
    printf("\n" BOLD_WHITE "       Bit Indexing Convention (asm-v0):\n" RESET);
    printf("         Bit 0 = MSB (weight 8)\n");
    printf("         Bit 3 = LSB (weight 1)\n");
    printf("\n" BOLD_WHITE "       Instruction Data Field Layout:\n" RESET);
    printf("         Index  -> [3] [2] [1] [0]\n");
    printf("         Weight ->  1   2   4   8\n");
    print_note("Enter instruction with hyphens as shown.");

    print_mnemonic(2, "STORE");
    print_mfield("Function", "Stores data on lines to registers.");
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
    print_mfield("Function", "Loads AND stores data (combined).");
    printf("                No separate STORE needed from v0.2.\n");
    print_marrow("S=0", "Register A");
    print_marrow("S=1", "Register B");
    printf("       Bit 0 = MSB (weight 8) | Bit 3 = LSB (weight 1)\n");
    printf("       Layout: Index -> [3][2][1][0] | Weight -> 1 2 4 8\n");

    print_mnemonic(2, "FBK");
    print_mfield("Function", "Feeds output back into Register A.");

    print_mnemonic(3, "ADD");
    print_mfield("Function", "Default arithmetic operation.");
    print_mfield("Output", "DEFAULT ARITHMETIC OPERATION");

    print_mnemonic(4, "SUB");
    print_mfield("Function", "Subtracts Register B from Register A.");
    print_note("Use HOLD-OP after to retain result.");

    print_mnemonic(5, "DIV");
    print_mfield("Function", "Divides Register A by Register B.");
    print_note("Use HOLD-OP for (quotient) cycles.");

    print_mnemonic(6, "MUL-XXXX");
    print_mfield("Function", "Multiplies Register B by (XXXX - 1).");
    printf("                Example: 0010 -> value=4, multiplier=3\n");
    print_note("Use HOLD-OP for (multiplier+1) cycles.");

    print_mnemonic(7, "OVRD");
    print_mfield("Function", "Overrides overflow halt.");

    print_mnemonic(8, "RSTM");
    print_mfield("Function", "Resets entire machine to 0.");

    print_mnemonic(9, "HOLD-OP");
    print_mfield("Function", "Holds output for N clock cycles.");
    printf("                MUL -> hold (multiplier+1) cycles\n");
    printf("                DIV -> hold (quotient) cycles\n");

    printf("\n");
    print_divider();
}

void manual_v03() {
    printf("\n");
    print_header("asm-v0.3 - Syntax & Semantic Analysis");

    print_section("OVERVIEW");
    printf(" The assembler evolves into an early-stage compiler\n");
    printf(" capable of syntax validation and basic semantic\n");
    printf(" checks. All mnemonics from v0.2 are supported.\n");
    printf(" Ensures every instruction follows valid structural\n");
    printf(" rules and operations occur in meaningful order.\n");

    print_section("MNEMONICS");
    printf(" All mnemonics from v0.2 are supported.\n");
    printf(DIM " See v0.2 for the full mnemonic list.\n" RESET);
    printf(DIM " v0.3 adds a validation layer on top of them.\n" RESET);

    print_section("KEY FEATURES");

    printf("\n" BOLD_YELLOW "  [1] SYNTAX ANALYSIS\n" RESET);
    printf(GREEN "     * " RESET "Validates each instruction before translation.\n");
    printf(GREEN "     * " RESET "Detects invalid LOAD structure.\n");
    printf(GREEN "     * " RESET "Detects non-binary selector or data bits.\n");
    printf(GREEN "     * " RESET "Detects incorrect instruction length.\n");

    printf("\n" BOLD_YELLOW "  [2] BASIC SEMANTIC ANALYSIS\n" RESET);
    printf(GREEN "     * " RESET "Prevents arithmetic before any LOAD.\n");
    printf(GREEN "     * " RESET "Detects invalid machine states.\n");
    printf(GREEN "     * " RESET "Halts with descriptive error messages.\n");

    printf("\n" BOLD_YELLOW "  [3] ENHANCED ERROR REPORTING\n" RESET);
    printf(GREEN "     * " RESET "Distinct syntax and semantic error messages.\n");
    printf(GREEN "     * " RESET "Invalid syntax    -> wrong format/structure\n");
    printf(GREEN "     * " RESET "Invalid semantics -> wrong order/context\n");

    print_section("ERROR TYPES DETECTED");
    printf(YELLOW "     ! " RESET "No input detected\n");
    printf(YELLOW "     ! " RESET "Instruction out of order\n");
    printf(YELLOW "     ! " RESET "Malformed mnemonic\n");
    printf(YELLOW "     ! " RESET "Invalid binary fields\n");
    printf(YELLOW "     ! " RESET "Operation before data load\n");

    printf("\n");
    print_divider();
}

void asm_all() {
    printf("\n");
    print_header("Layer 2: ASM - All Versions");
    printf(CYAN "  v0.1" RESET " -> LOAD-S-XXXX + STORE only\n");
    printf(CYAN "  v0.2" RESET " -> STORE abstracted, full mnemonic set added\n");
    printf(CYAN "  v0.3" RESET " -> Syntax & Primitive Semantic Analysis layer\n");
    printf(DIM "\n Showing all ASM versions...\n" RESET);
    manual_v01();
    manual_v02();
    manual_v03();
}

// ═══════════════════════════════════════════
// SAMPLE PROGRAMS
// ═══════════════════════════════════════════

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
    printf("A = 0000 (0)\nB = 0000 (0)\nOutput = 0000 (0)\n");
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
    printf("Default Operation: ADD\nA + B = 9 + 3 = 12\n");
    printf(BOLD_GREEN "Binary Output = 0011 (12)\n" RESET);
    printf(DIM "----------------------------------------------------\n" RESET);
    printf(BOLD_WHITE "Final System State\n" RESET);
    printf(DIM "----------------------------------------------------\n" RESET);
    printf(CYAN "Register A = 1001 (9)\nRegister B = 1100 (3)\n" RESET);
    printf(BOLD_GREEN "Output     = 0011 (12)\n" RESET);
    printf(GREEN "No overflow occurs.\nNo error detection triggered.\nClock continues normally.\n" RESET);
    printf(DIM "----------------------------------------------------\n" RESET);
    printf(DIM "// It is advised to Use asm-v0.3 Standard Assembler:\n// Features like Syntax and Semantic Analysis.\n// Output Error Statements indicating the error.\n// Compatible with asm-v0.2 standard.\n" RESET);
    printf("\n"); print_divider();
}

void sample_p2() {
    printf("\n");
    print_header("P2 - Feedback");
    printf(DIM "\n// Program follows asm-v0.2 standard\n// Will Run in asm-v0.2 and asm-v0.3 standard assembler\n" RESET);
    printf(BOLD_GREEN "LOAD-0-0110" RESET DIM " // Load 0110(6) in Register A\n" RESET);
    printf(BOLD_GREEN "LOAD-1-0001" RESET DIM " // Load 0001(8) in Register B\n" RESET);
    printf(BOLD_GREEN "ADD        " RESET DIM " // ADD Data in Register A and B\n" RESET);
    printf(BOLD_GREEN "FBK        " RESET DIM " // Feedback output back to input (Register A)\n" RESET);
    printf(BOLD_GREEN "SUB        " RESET DIM " // Subtract Data in Register A and B\n" RESET);
    printf(BOLD_GREEN "HOLD-OP    " RESET DIM " // Hold operation/output for arbitrary number of clock cycles\n" RESET);
    printf(DIM "\n---------------------------------------------------\n" RESET);
    printf(BOLD_WHITE "# EXECUTION TRACE\n" RESET);
    printf(DIM "---------------------------------------------------\n" RESET);
    printf("Initial State:\nA = 0000 (0)\nB = 0000 (0)\nOutput = 0000 (0)\n");
    printf(DIM "----------------------------------------------------\n" RESET);
    printf(BOLD_WHITE "Program Execution (asm-v0.2 / asm-v0.3)\n" RESET);
    printf(DIM "----------------------------------------------------\n" RESET);
    printf(BOLD_YELLOW "1) LOAD-0-0110\n" RESET);
    printf("   Register A <- 0110 (6)\n");
    printf(BOLD_YELLOW "2) LOAD-1-0001\n" RESET);
    printf("   Register B <- 0001 (8)\n");
    printf("   Current State:\n");
    printf(CYAN "   A = 0110 (6)\n   B = 0001 (8)\n" RESET);
    printf(DIM "----------------------------------------------------\n" RESET);
    printf(BOLD_YELLOW "3) ADD  (Default Operation)\n" RESET);
    printf(DIM "----------------------------------------------------\n" RESET);
    printf("A + B = 6 + 8 = 14\n");
    printf(BOLD_GREEN "Binary Output = 0111 (14)\n" RESET);
    printf(DIM "----------------------------------------------------\n" RESET);
    printf(BOLD_YELLOW "4) FBK  (Feedback)\n" RESET);
    printf(DIM "----------------------------------------------------\n" RESET);
    printf("Register A <- 0111 (14)\n   Current State:\n");
    printf(CYAN "   A = 0111 (14)\n   B = 0001 (8)\n" RESET);
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
    printf("The value remains on the output lines for the specified\nnumber of clock cycles.\nAfter HOLD duration expires:\n");
    printf(DIM "System automatically returns to Default Operation (ADD).\n" RESET);
    printf(DIM "----------------------------------------------------\n" RESET);
    printf(BOLD_WHITE "Post-HOLD Default ADD\n" RESET);
    printf(DIM "----------------------------------------------------\n" RESET);
    printf("A + B = 14 + 8 = 22\n");
    printf(BOLD_GREEN "Binary Output = 01101 (22)\n" RESET);
    printf(DIM "----------------------------------------------------\n" RESET);
    printf(BOLD_WHITE "Final System State\n" RESET);
    printf(DIM "----------------------------------------------------\n" RESET);
    printf(CYAN "Register A = 0111 (14)\nRegister B = 0001 (8)\n" RESET);
    printf(BOLD_GREEN "Output during HOLD = 0110 (6)\nPost-HOLD Output   = 01101 (22)\n" RESET);
    printf(DIM "---------------------------------------------------\n// It is advised to Use asm-v0.3 Standard Assembler:\n// Features like Syntax and Semantic Analysis.\n// Output Error Statements indicating the error.\n// Compatible with asm-v0.2 standard.\n" RESET);
    printf("\n"); print_divider();
}

void sample_p3() {
    printf("\n");
    print_header("P3 - Division");
    printf(DIM "\n// Program Follows asm-v0.2 Standard\n// Will Run in asm-v0.2 and asm-v0.3 standard assembler\n" RESET);
    printf(BOLD_GREEN "LOAD-0-0111" RESET DIM " // Load 0111(14) on Data Lines and Store in Register A\n" RESET);
    printf(BOLD_GREEN "LOAD-1-0100" RESET DIM " // Load 0100(2) on Data Lines and Store in Register B\n" RESET);
    printf(BOLD_GREEN "DIV        " RESET DIM " // Divide the Data in Register A from Data in Register B\n" RESET);
    printf(BOLD_GREEN "HOLD-OP    " RESET DIM " // Hold operation/output for arbitrary number of clock cycles\n" RESET);
    printf(DIM "            // HOLD-OP should be sustained for atleast the value of quotient clock cycles\n" RESET);
    printf(DIM "\n---------------------------------------------------\n" RESET);
    printf(BOLD_WHITE "# EXECUTION TRACE\n" RESET);
    printf(DIM "---------------------------------------------------\n" RESET);
    printf("Initial State:\nA = 0000 (0)\nB = 0000 (0)\nOutput = 0000 (0)\n");
    printf(DIM "----------------------------------------------------\n" RESET);
    printf(BOLD_WHITE "Program Execution (asm-v0.2 / asm-v0.3)\n" RESET);
    printf(DIM "----------------------------------------------------\n" RESET);
    printf(BOLD_YELLOW "1) LOAD-0-0111\n" RESET);
    printf("   Register A <- 0111 (14)\n");
    printf(BOLD_YELLOW "2) LOAD-1-0100\n" RESET);
    printf("   Register B <- 0100 (2)\n   Current State:\n");
    printf(CYAN "   A = 0111 (14)\n   B = 0100 (2)\n" RESET);
    printf(DIM "----------------------------------------------------\n" RESET);
    printf(BOLD_YELLOW "3) DIV\n" RESET);
    printf(DIM "----------------------------------------------------\n" RESET);
    printf("Operation: A / B\n14 / 2 = 7\nSince division is iterative in hardware,\nthe system performs repeated subtraction / convergence\nacross multiple clock cycles until a stable quotient is reached.\n");
    printf(DIM "Intermediate Convergence:\nCycle 1: 14 - 2 = 12\nCycle 2: 12 - 2 = 10\nCycle 3: 10 - 2 = 8\nCycle 4: 8  - 2 = 6\nCycle 5: 6  - 2 = 4\nCycle 6: 4  - 2 = 2\nCycle 7: 2  - 2 = 0\n" RESET);
    printf("Quotient = 7\n");
    printf(BOLD_GREEN "Binary Output = 1110 (7)\n" RESET);
    printf(CYAN "Divisibility Convergence LED -> ON\n" RESET);
    printf(DIM "(System has reached stable state)\n----------------------------------------------------\n" RESET);
    printf(BOLD_YELLOW "4) HOLD-OP\n" RESET);
    printf(DIM "----------------------------------------------------\n" RESET);
    printf("Output held constant at:\n");
    printf(BOLD_GREEN "1110 (7)\n" RESET);
    printf("HOLD-OP must be sustained for at least\nthe number of quotient clock cycles to allow\nfull convergence and stable output.\nAfter HOLD duration expires:\n");
    printf(DIM "System automatically returns to Default Operation (ADD)\nbut Division Output remains latched on the dedicated\ndivision output lines.\n----------------------------------------------------\n" RESET);
    printf(BOLD_WHITE "Final System State\n" RESET);
    printf(DIM "----------------------------------------------------\n" RESET);
    printf(CYAN "Register A = 0111 (14)\nRegister B = 0100 (2)\n" RESET);
    printf(BOLD_GREEN "Output     = 1110 (7)\n" RESET);
    printf(CYAN "Divisibility Convergence LED -> ON\n" RESET);
    printf("Indicates quotient stabilization and\ncompletion of division cycle.\n");
    printf(GREEN "System Stable.\nClock continues normally.\n" RESET);
    printf(DIM "--------------------------------------------------\n// It is advised to Use asm-v0.3 Standard Assembler:\n// Features like Syntax and Semantic Analysis.\n// Output Error Statements indicating the error.\n// Compatible with asm-v0.2 standard.\n" RESET);
    printf("\n"); print_divider();
}

void sample_p4() {
    printf("\n");
    print_header("P4 - Multiplication");
    printf(DIM "\n// Program Follows asm-v0.2 Standard\n// Will Run in asm-v0.2 and asm-v0.3 standard assembler\n" RESET);
    printf(BOLD_GREEN "LOAD-1-0100" RESET DIM " // Load 0100(2) in Register B (Stores Multiplicand)\n" RESET);
    printf(BOLD_GREEN "MUL-0010   " RESET DIM " // Multiply the Multiplicand in Register B from the ( Multiplier - 1 ) -> 3\n" RESET);
    printf(BOLD_GREEN "HOLD-OP    " RESET DIM " // Hold operation/output for arbitrary number of clock cycles\n" RESET);
    printf(DIM "            // HOLD-OP should be sustained for atleast the value of (Multiplier + 1) cycles\n" RESET);
    printf(DIM "# OUTPUT -> Multiplicative Convergance LED will turn ON once the Machine have settled\n#           in a stable state indicating successful computation -> 6 (0110)\n" RESET);
    printf(DIM "\n---------------------------------------------------\n" RESET);
    printf(BOLD_WHITE "# EXECUTION TRACE\n" RESET);
    printf(DIM "---------------------------------------------------\n" RESET);
    printf("Initial State:\nA = 0000 (0)\nB = 0000 (0)\nOutput = 0000 (0)\n");
    printf(DIM "----------------------------------------------------\n" RESET);
    printf(BOLD_WHITE "Program Execution (asm-v0.2 / asm-v0.3)\n" RESET);
    printf(DIM "----------------------------------------------------\n" RESET);
    printf(BOLD_YELLOW "1) LOAD-1-0100\n" RESET);
    printf("   Register B <- 0100 (2)\n   (Multiplicand stored in Register B)\n   Current State:\n");
    printf(CYAN "   A = 0000 (0)\n   B = 0100 (2)\n" RESET);
    printf(DIM "----------------------------------------------------\n" RESET);
    printf(BOLD_YELLOW "2) MUL-0010\n" RESET);
    printf(DIM "----------------------------------------------------\n" RESET);
    printf("Multiplier Field = 0010 (4)\nEffective Multiplication = B x (Multiplier - 1)\n                         = 2 x 3\nSince multiplication is sequential in hardware,\nthe system performs repeated addition / convergence\nacross multiple clock cycles until the final product stabilizes.\n");
    printf(DIM "Intermediate Convergence:\nCycle 1: 2\nCycle 2: 2 + 2 = 4\nCycle 3: 4 + 2 = 6\n" RESET);
    printf("Final Product = 6\n");
    printf(BOLD_GREEN "Binary Output = 0110 (6)\n" RESET);
    printf(CYAN "Multiplicative Convergence LED -> ON\n" RESET);
    printf(DIM "(Indicates product stabilization and completion of multiplication cycle)\n----------------------------------------------------\n" RESET);
    printf(BOLD_YELLOW "3) HOLD-OP\n" RESET);
    printf(DIM "----------------------------------------------------\n" RESET);
    printf("Output held constant at:\n");
    printf(BOLD_GREEN "0110 (6)\n" RESET);
    printf("HOLD-OP must be sustained for at least\n(Multiplier + 1) clock cycles to allow\nfull convergence and stable output visibility.\nAfter HOLD duration expires:\n");
    printf(DIM "System automatically returns to Default Operation (ADD).\nBut MUL Output remains stable after HOLD-OP as multiplication\nis implemented using repeated Addition using Register A and B.\n----------------------------------------------------\n" RESET);
    printf(BOLD_WHITE "Final System State\n" RESET);
    printf(DIM "----------------------------------------------------\n" RESET);
    printf(CYAN "Register A = 0000 (0)\nRegister B = 0100 (2)\n" RESET);
    printf(BOLD_GREEN "Output     = 0110 (6)\n" RESET);
    printf(CYAN "Multiplicative Convergence LED = ON\n" RESET);
    printf(GREEN "System Stable.\nClock continues normally.\n" RESET);
    printf(DIM "----------------------------------------------------\n// It is advised to Use asm-v0.3 Standard Assembler:\n// Features like Syntax and Semantic Analysis.\n// Output Error Statements indicating the error.\n// Compatible with asm-v0.2 standard.\n" RESET);
    printf("\n"); print_divider();
}

void sample_p5() {
    printf("\n");
    print_header("P5 - Overflow & Recovery");
    printf(DIM "\n// Program Follows asm-v0.2 Standard\n// Will Run in asm-v0.2 and asm-v0.3 standard assembler\n" RESET);
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
    printf(CYAN "A = 0001 (8)\nB = 0010 (4)\n" RESET);
    printf("Output = 0000 (0)\n");
    printf(DIM "----------------------------------------------------\n" RESET);
    printf(BOLD_YELLOW "1) ADD  (Default Operation)\n" RESET);
    printf(DIM "----------------------------------------------------\n" RESET);
    printf("A + B = 8 + 4 = 12\n");
    printf(BOLD_GREEN "Binary Output = 0011 (12)\n" RESET);
    printf(DIM "----------------------------------------------------\n" RESET);
    printf(BOLD_YELLOW "2) FBK  (Feedback)\n" RESET);
    printf(DIM "----------------------------------------------------\n" RESET);
    printf("Register A <- 0011 (12)\nCurrent State:\n");
    printf(CYAN "A = 0011 (12)\nB = 0010 (4)\n" RESET);
    printf(DIM "----------------------------------------------------\n" RESET);
    printf(BOLD_YELLOW "3) ADD\n" RESET);
    printf(DIM "----------------------------------------------------\n" RESET);
    printf("A + B = 12 + 4 = 16\n");
    printf(YELLOW "Binary Output = 00001 (16)\n(5-bit result exceeds 4-bit register width)\n" RESET);
    printf(DIM "----------------------------------------------------\n" RESET);
    printf(BOLD_RED "Overflow Detection\n" RESET);
    printf(DIM "----------------------------------------------------\n" RESET);
    printf("Since the result occupies the 5th bit,\nit cannot be stored within the 4-bit register width\nwith feedback.\n");
    printf(YELLOW "Overflow Condition Triggered.\n" RESET);
    printf("System Response:\n");
    printf(YELLOW "- Overflow Detection Logic Activated\n- Clock Disengaged\n- System Halted\n- LEDs ON:\n    * Clock Disengaged\n    * System Halted\n    * Feedback Overflow\n" RESET);
    printf(DIM "Architectural State Preserved.\n----------------------------------------------------\n" RESET);
    printf(BOLD_YELLOW "4) HOLD-OP\n" RESET);
    printf(DIM "----------------------------------------------------\n" RESET);
    printf("Output held constant at:\n");
    printf(YELLOW "00001 (16)\n" RESET);
    printf("System remains halted until override.\n");
    printf(DIM "----------------------------------------------------\n" RESET);
    printf(BOLD_YELLOW "5) OVRD  (Override)\n" RESET);
    printf(DIM "----------------------------------------------------\n" RESET);
    printf(CYAN "Clock Re-enabled.\nSystem resumes from halted state.\n" RESET);
    printf(DIM "----------------------------------------------------\n" RESET);
    printf(BOLD_YELLOW "6) FBK\n" RESET);
    printf(DIM "----------------------------------------------------\n" RESET);
    printf("Feedback attempts to store output into Register A.\nSince only lower 4 bits can be stored:\n");
    printf(YELLOW "00001 -> 0000 (lower 4 bits)\n" RESET);
    printf("Register A <- 0000 (0)\nCurrent State:\n");
    printf(CYAN "A = 0000 (0)\nB = 0010 (4)\n" RESET);
    printf("Subsequent Default ADD:\nA + B = 0 + 4 = 4\n");
    printf(BOLD_GREEN "Binary Output = 0010 (4)\n" RESET);
    printf(DIM "----------------------------------------------------\n" RESET);
    printf(BOLD_WHITE "Final System State\n" RESET);
    printf(DIM "----------------------------------------------------\n" RESET);
    printf(CYAN "Register A = 0000 (0)\nRegister B = 0010 (4)\n" RESET);
    printf(BOLD_GREEN "Output     = 0010 (4)\n" RESET);
    printf(YELLOW "Overflow condition was overridden.\nComputation integrity lost after OVRD.\n" RESET);
    printf(GREEN "System running normally.\n" RESET);
    printf(DIM "----------------------------------------------------\n// It is advised to Use asm-v0.3 Standard Assembler:\n// Features like Syntax and Semantic Analysis.\n// Output Error Statements indicating the error.\n// Compatible with asm-v0.2 standard.\n" RESET);
    printf("\n"); print_divider();
}

void sample_p6() {
    printf("\n");
    print_header("P6 - Machine Reset");
    printf(DIM "\n// Program Follows asm-v0.2 Standard\n// Will Run in asm-v0.2 and asm-v0.3 standard assembler\n" RESET);
    printf(BOLD_GREEN "LOAD-1-1000" RESET DIM " // Load 1000(1) in Register A\n" RESET);
    printf(BOLD_GREEN "LOAD-0-0010" RESET DIM " // Load 0010(4) in Register B\n" RESET);
    printf(BOLD_GREEN "ADD        " RESET DIM " // A + B\n" RESET);
    printf(BOLD_GREEN "RSTM       " RESET DIM " // Clears the Machine\n" RESET);
    printf(DIM "\n---------------------------------------------------\n" RESET);
    printf(BOLD_WHITE "# EXECUTION TRACE\n" RESET);
    printf(DIM "---------------------------------------------------\n" RESET);
    printf("Initial State:\nA = 0000 (0)\nB = 0000 (0)\nOutput = 0000 (0)\n");
    printf(DIM "----------------------------------------------------\n" RESET);
    printf(BOLD_YELLOW "1) LOAD-1-1000\n" RESET);
    printf(DIM "----------------------------------------------------\n" RESET);
    printf("Register A <- 1000 (1)\nCurrent State:\n");
    printf(CYAN "A = 1000 (1)\nB = 0000 (0)\n" RESET);
    printf(DIM "----------------------------------------------------\n" RESET);
    printf(BOLD_YELLOW "2) LOAD-0-0010\n" RESET);
    printf(DIM "----------------------------------------------------\n" RESET);
    printf("Register B <- 0010 (4)\nCurrent State:\n");
    printf(CYAN "A = 1000 (1)\nB = 0010 (4)\n" RESET);
    printf(DIM "----------------------------------------------------\n" RESET);
    printf(BOLD_YELLOW "3) ADD  (Default Operation)\n" RESET);
    printf(DIM "----------------------------------------------------\n" RESET);
    printf("A + B = 1 + 4 = 5\n");
    printf(BOLD_GREEN "Binary Output = 1010 (5)\n" RESET);
    printf("Current State:\n");
    printf(CYAN "A = 1000 (1)\nB = 0010 (4)\n" RESET);
    printf(BOLD_GREEN "Output = 1010 (5)\n" RESET);
    printf(DIM "----------------------------------------------------\n" RESET);
    printf(BOLD_YELLOW "4) RSTM  (Reset Machine)\n" RESET);
    printf(DIM "----------------------------------------------------\n" RESET);
    printf(CYAN "Machine Reset Triggered.\n" RESET);
    printf("All Registers Cleared:\n");
    printf(CYAN "A = 0000 (0)\nB = 0000 (0)\n" RESET);
    printf("All Output Lines Cleared:\nOutput = 0000 (0)\nAll Control Flags Cleared:\n");
    printf(DIM "- Overflow = OFF\n- Convergence LEDs = OFF\n- Halt State = Cleared\nClock continues in normal reset state.\n----------------------------------------------------\n" RESET);
    printf(BOLD_WHITE "Final System State\n" RESET);
    printf(DIM "----------------------------------------------------\n" RESET);
    printf(CYAN "Register A = 0000 (0)\nRegister B = 0000 (0)\n" RESET);
    printf(BOLD_GREEN "Output     = 0000 (0)\n" RESET);
    printf(GREEN "Machine fully reset.\n" RESET);
    printf(DIM "----------------------------------------------------\n// It is advised to Use asm-v0.3 Standard Assembler:\n// Features like Syntax and Semantic Analysis.\n// Output Error Statements indicating the error.\n// Compatible with asm-v0.2 standard.\n" RESET);
    printf("\n"); print_divider();
}

// ═══════════════════════════════════════════
// MAIN
// ═══════════════════════════════════════════

int main(int argc, char *argv[]) {

    if (argc >= 3 && strcmp(argv[1], "--search") == 0) {
        search(argv[2]);
        return 0;
    }

    if (argc == 2 && strcmp(argv[1], "--search") == 0) {
        printf(BOLD_WHITE "Usage  : " RESET "./stack-manual --search <term>\n");
        printf(BOLD_WHITE "Example: " RESET "./stack-manual --search overflow\n");
        return 1;
    }

    char input[20];

    printf("\n");
    print_divider();
    printf(DIM "|" RESET BOLD_CYAN "  %-52s" RESET DIM "|" RESET "\n", "Full Computing Stack Manual");
    printf(DIM "|" RESET CYAN      "  %-52s" RESET DIM "|" RESET "\n", "Layer 1: RAM Hardware  |  Layer 2: Assembly");
    print_divider();
    printf(DIM " Tip: " RESET "search across both layers from terminal:\n");
    printf(CYAN "      ./stack-manual --search overflow\n" RESET);

    while (1) {
        printf("\n" BOLD_WHITE " [Layer 1 - RAM]" RESET "\n");
        printf(DIM "  Available: " RESET
               CYAN "V0" RESET " | " CYAN "V1" RESET " | " CYAN "V2" RESET " | "
               CYAN "V3" RESET " | " CYAN "V4" RESET " | " CYAN "ram-all" RESET "\n");
        printf("\n" BOLD_WHITE " [Layer 2 - ASM]" RESET "\n");
        printf(DIM "  Available: " RESET
               CYAN "v0.1" RESET " | " CYAN "v0.2" RESET " | " CYAN "v0.3" RESET " | "
               CYAN "asm-all" RESET " | " CYAN "samples" RESET "\n");
        printf("\n" BOLD_WHITE " [Other]" RESET "\n");
        printf(DIM "  Available: " RESET
               CYAN "search" RESET " | " CYAN "exit" RESET "\n");
        printf(BOLD_WHITE "\n Enter command: " RESET);
        scanf("%s", input);

        if      (strcmp(input, "V0") == 0 || strcmp(input, "v0") == 0)   manual_v0();
        else if (strcmp(input, "V1") == 0 || strcmp(input, "v1") == 0)   manual_v1();
        else if (strcmp(input, "V2") == 0 || strcmp(input, "v2") == 0)   manual_v2();
        else if (strcmp(input, "V3") == 0 || strcmp(input, "v3") == 0)   manual_v3();
        else if (strcmp(input, "V4") == 0 || strcmp(input, "v4") == 0)   manual_v4();
        else if (strcmp(input, "ram-all") == 0)                           ram_all();
        else if (strcmp(input, "v0.1") == 0)                              manual_v01();
        else if (strcmp(input, "v0.2") == 0)                              manual_v02();
        else if (strcmp(input, "v0.3") == 0)                              manual_v03();
        else if (strcmp(input, "asm-all") == 0)                           asm_all();
        else if (strcmp(input, "samples") == 0) {
            samples_index();
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
        }
        else if (strcmp(input, "search") == 0) {
            char query[50];
            printf(BOLD_WHITE " Enter term to search: " RESET);
            scanf("%s", query);
            search(query);
        }
        else if (strcmp(input, "exit") == 0) {
            printf(BOLD_GREEN "\n Goodbye!\n" RESET);
            break;
        }
        else {
            printf(BOLD_RED "\n [ERROR]" RESET " Unknown input '%s'\n", input);
            printf(DIM " Try: V0-V4, ram-all, v0.1-v0.3, asm-all, samples, search, exit\n" RESET);
        }
    }

    return 0;
}
