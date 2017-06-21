#include "bheader.h"

// TODO: add mistake handling later
unsigned short get_address(char* title){
	char address[3];
	printf("%s\n", title);
	scanf("%s", address);
	return ((short) strtol(address, NULL, 16));
}

unsigned short get_data(int* finish_input){
	char data[4];
	printf("Enter data:\n");
	scanf("%s", data);
	if (strcmp(data, "quit") == 0 || strcmp(data, "exit") == 0) {
		printf("END OF INPUT DATA\n");
		*finish_input = TRUE;
		return 0;
	}
	return ((short) strtol(data, NULL, 16));
}

void push(unsigned short val, unsigned short* mem,
	unsigned short* top){
	if (*top == MAX_SIZE - 1){ *top = -1;}
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
