#ifndef INCLUDED_constants
#define  INCLUDED_constants

#define MAX_MEM_SIZE 1000
#define DEFAULT_MEM_SIZE 1024
#define BYTESPERWORD 4
#define HEXPERWORD 8
#define BASEHEX 16
#define BASETEN 10

// Constants for choice numbers for the commands at the shell prompt. 
#define C_LOAD_RUN 1
#define C_RUN_BG  2
#define C_STEP    3
#define C_CPU     4
#define C_MEM     5
#define C_QUIT    6
#define C_INVALID 7
#define C_BAD_COM 8
#define C_QUEUE   9
#define C_FG      10
#define C_JOBS    11
#define C_KILL    12
#define C_SUSPEND 13
#define C_RESTART 14
#define C_PAGETABLE 15

// Constants used in Simulator.cc
#define CONFIG_FILE "machine.conf"
#define DONE_STRING "Done\n" // Used to signal completion
#define C_LOAD_RUN_STRING "Loading and Running.\n" // Does both
#define C_RUN_BG_STRING "Loading and Running in background.\n"
#define LOAD_STRING "Load " // Pre-statement to filename
#define NEW_LINE "\n" // For adding new lines to the prompt
#define ERROR_IN_PROGRAM "Error in program.\n" // Error in prog exec.
#define INVALID_COMMAND "Invalid command sequence.\n"
#define INVALID_FILE "Invalid file.\n" // Invalid command sequence
#define USER_PROMPT_SYMBOL "> " //User prompt
#define END_LOOP "IM DONE FOR NOW" // What the machine says when done

// COMMANDS FOR USER
#define END_PROGRAM "quit" // ends the program
#define CPU_STATE "cpu"    // Lists the state of all registers in cpu
#define MEM_RANGE "mem"    // lists register values in given reg range
#define SHOW_QUEUE "queue" // Shows the queue states to user
#define SUSPEND "suspend"  // Puts the machine into step based execution mode
#define RESTART "restart"  // Resumes normal cpu exectuion
#define PAGE_TABLE "displayPageTable" // Displays page table to user
#define KILL_PID "kill"    // Kills the given process id

#define ARGS_IN_CONFIG 5 // Number of arguments in configure file
#define NUM_WORDS_STRING "memory" // string for numWords argument in .conf
#define STACK_SPACE_STRING "stack" // string for stackSpace argument in .conf
#define TIMESLICE_STRING "timeslice" // string for timeSlice arg in .conf
#define PAGESIZE_STRING "pagesize" // string for pageSize arg in .conf
#define SWAPSPACE_STRING "swapspace" // "" swapSpace arg in .conf
#define NUM_BYTES_ARG 1 // index of numBytes argument in .conf
#define STACK_SPACE_ARG 3 // index of stackSpace argument in .conf
#define TIMESLICE_ARG 5 // index of timeSlice arg in .conf
#define PIPE_COMS 2 // Number of lines on a pipe
#define ERROR_IN_PIPE -1 // Error in pipe code
#define CHILD_PROCESS 0

//Used in both Simulator and Machine
#define LINESIZE 80 // Max user input line size
#define SHELL_PROMPT_MAX 4096      // Maximum number of characters to
				   // shell 
#define WORDS_CONVERSION_FACTOR 32 // How many characters should be
 				   // reserved per byte for a machine
	 			   // to output all of its memory
				   // without exceeding bounds of array
#define PROGRAM_PROMPT "? " // Symbol used to prompt users for machine in

// Constants for Machine.cc
#define OPCODEMASK    0xf0000000
#define OPCODEPOS     28
#define XMASK         0x0f000000
#define XPOS          24
#define YMASK         0x00f00000
#define YPOS          20
#define ZMASK         0x0000000f
#define OFFSETMASK    0x000fffff
#define OFFSETENDMASK 0x00080000
#define ADD           0
#define NAND          1
#define ADDI          2
#define LW            3
#define SW            4
#define BEQ           5
#define JALR          6
#define HALT          7
#define IN            12
#define OUT           13
#define LA            14
#define ST_SIZE       64 // The number of bytes allocated program stack
#define WORD_SIZE     4 // Bytes in a word
#define PAGE_NOT_FOUND -1 // Default index for not finding a page

#define KILLED_PID "AAAHHHHH GURGLE GURGLE DEATH NOISE\n"

#define COMPLETED_Q_HEADER "=== START :::  Information report ===== \nPID  ::  Response Time  ::  Run Time  ::  Wait Time\n"
#define COMPLETED_Q_FOOTER "=== END ::::  Information report =====\n"
#define QUEUE_HEADER "=== START :::  PCB report =====\n"
#define QUEUE_FOOTER "==== END ::::  PCB report =====\n"
#define JOBS_HEADER "=== START :::  JOBS report =====\n"
#define JOBS_FOOTER "==== END ::::  JOBS report =====\n"
#define COMPLETED_Q_REPORT_LENGTH 100
#define COMPLETED_Q_REPORT_STRING "%llu  ::  %llu  ::  %llu  ::  %llu\n"
#define PCB_REPORT_LENGTH 300
#define PCB_REPORT_STRING "---PID: %llu---\nPC: %llu\nFrame Pointer: %llu\nOwnsIO: %d\nEnd Address: %llu\nStart Time: %llu\nEnd Time: %llu\nRun Time: %llu\n::Registers::\n"
#define JOBS_REPORT_LENGTH 200
#define JOBS_REPORT_STRING "%llu  ::  %llu  ::  %s  ::  %s\n"
#define PROCESS_RUNNING "Process Running"
#define PROCESS_WAITING "Process Waiting"
#define CURRENT_PROCESS_INFO "Current:  PID-%llu\n"
#define FREEMEM_STRING "Block %u Start:  %llu  Size:  %llu\n"

#define ULLI_LENGTH 20 // The character length of a ulli
#define STATS_DELIM "  ::  " // The delimeter for statistics
#define STACK_SIZE 64 // Bytes in stack for a program
#define PID_DISPLAY_STR "PID %llu: " // The string for displaying PIDs
#define NO_OFFSET 0 // The no-offset bit for seekg in an ifstream
#define NO_MEM_AVAILABLE "Not enough memory to load program.\n"
#define NO_PID_FOUND "The given PID was not found queue.\n"

// Used in CPU
#define NUMREGONONELINE 4
#define CPU_CODES 400 // Holding all registers in hex
#define NUMREGISTERS 16
#define FP 14
#define SP 13

// Used in Memory
#define HEX_ADDRESS_DECIMAL 200

// =======================
//      Used in PCB.h     
// =======================


// ==========================
//      Used in Choice.h     
// ==========================

#define BACKGROUND_COMMAND "&" // The run-in-bg command ID

typedef unsigned long long int ulli;
 
#endif
