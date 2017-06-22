#include "bheader.h"
#include "functions.h"

void get_cycle(struct regs* regs);

micro_command_t microcommands[] = {
            func0,   func1,   func2,   func3,   func4,   func5,
            func6,   func7,   func8,   func9,   func10,  func11,
            func12,  func13,  func14,  func15,  func16,  func17,
            func18,  func19,  func20,  func21,  func22,  func23,
            func24,  func25,  func26,  func27,  func28,  func29,
            func30,  func31,  func32,  func33,  func34,  func35,
            func36,  func37,  func38,  func39,  func40,  func41,
            func42,  func43,  func44,  func45,  func46,  func47,
            func48,  func49,  func50,  func51,  func52,  func53,
            func54,  func55,  func56,  func57,  func58,  func59,
            func60,  func61,  func62,  func63,  func64,  func65,
            func66,  func67,  func68,  func69,  func70,  func71,
            func72,  func73,  func74,  func75,  func76,  func77,
            func78,  func79,  func80,  func81,  func82,  func83,
            func84,  func85,  func86,  func87,  func88,  func89,
            func90,  func91,  func92,  func93,  func94,  func95,
            func96,  func97,  func98,  func99,  func100, func101,
            func102, func103, func104, func105, func106, func107,
            func108, func109, func110, func111, func112, func113,
            func114, func115, func116, func117, func118, func119,
            func120, func121, func122, func123, func124, func125,
            func126, func127, func128, func129, func130, func131,
            func132, func133, func134, func135, func136  /* :( */
};

int main(int c, char *v[]){
	/* ask for init data address */
	unsigned short data_address = get_address("Enter the address");
	unsigned short start_address;
	int finish_input = FALSE; // flag that the input is finished
	unsigned short top = data_address - 1; // as we're simulating stack

	unsigned short tmp;
	
	struct regs regs;
	regs.status_register = 1;
	regs.mic_com_reg = 128;

	/* while != 'exit' or 'quit' getting data */
	while (finish_input == FALSE)
		fill_mem(regs.mem, &top, &finish_input);
	
	/* getting address of the cell with the 1st command */
	start_address = get_address("Enter the address of 1st command");
	printf("START: %u\n", start_address); // debugging
	regs.comm_count = start_address;
	
	/* get our bcomp running */
	while (TRUE) {
		tmp = regs.mem[regs.comm_count];
		puts("\nADDRESS\tCODE\tCK\tРА\tРК\tРД\tA\tC");
		printf("%03x\t%04x\t", regs.comm_count, regs.mem[regs.comm_count]);
		get_cycle(&regs);
		printf("%03x\t%03x\t%04x\t%04x\t%04x\t%01x\n",
			regs.comm_count, regs.address_reg,
			regs.comm_reg, regs.data_reg,
			regs.accum, regs.c_bit);
		if (tmp == 0xf000)
			break; /* if HLT */
	} 

	(void) c, (void) v;
	return EXIT_SUCCESS;
}

void get_cycle(struct regs* regs){
	regs->count_mic_com = 1;
	while (regs->count_mic_com < 137){
		int tmp = regs->count_mic_com;
		microcommands[regs->count_mic_com](regs);
		if (regs->count_mic_com == tmp)
			regs->count_mic_com++;
	}
}
