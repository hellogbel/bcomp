#include "bheader.h"

// TODO: add mistake handling later
unsigned short get_address(char* title){
	char address[3];
	puts(title);
	/* TODO: fix possible buffer overflow */
	scanf("%s", address);
	/* TODO: fix incorrect casting */
	return ((short) strtol(address, NULL, 16));
}

unsigned short get_data(int* finish_input){
	char data[5];
	puts("Enter data:");
	/* TODO: fix possible buffer overflow */
	scanf("%s", data);
	if (strcmp(data, "quit") == 0 || strcmp(data, "exit") == 0){
		puts("END OF INPUT DATA");
		*finish_input = TRUE;
		return 0;
	}
	/* TODO: fix incorrect casting */
	return ((short) strtol(data, NULL, 16));
}

void push(unsigned short val, unsigned short* mem, unsigned short* top){
	if (*top == MAX_SIZE - 1)
		*top = -1;
	*top = *top + 1;
	mem[*top] = val;
}

void fill_mem(unsigned short* mem, unsigned short* top, int* finish_input){
	unsigned short data = get_data(finish_input);
	if (data != 0){
		push(data, mem, top);
		printf("Address: %03x\tData: %04x\n", *top, data);
	}
}
