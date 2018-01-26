#include <assert.h>
#include <string.h>
#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <regex.h>


typedef enum {
	STR2INT_SUCCESS,
	STR2INT_OVER,
	STR2INT_UNDER,
	STR2INT_INCONV,
} str2int_errno;

void handle_mistake(str2int_errno *conv, int *out, char *s, int min,
	int max, int num_digits);
void parse_errno(str2int_errno *conv, int min, int max, int num_digits);
void input(char *buff);

str2int_errno str2int(int *out, char *s, int min, int max, int num_digits) {
	str2int_errno result;
	if (result)
		result = STR2INT_INCONV;
	long tmp;
	regex_t regex;
	int res;
	char msgbuf[100];
	char expr[10];

	/* CONVERTION */
	/* first checking that our string is a number */
	/* creating our regexp */
	sprintf(expr, "^[0-9A-Fa-f]{1,%d}\n", num_digits);
	puts("EXPRESSION:");
	puts(expr);
	/* Compile regexp */
	if (regcomp(&regex, expr, REG_EXTENDED)) {
		printf("Couldnt compile\n");
		exit(2);
	}
	if (!(res = regexec(&regex, s, 0, NULL, 0))) {
		puts("Match");
		result = STR2INT_SUCCESS;
	}
	else if (res == REG_NOMATCH) {
		puts("NO match");
	}
	else {
		regerror(res, &regex, msgbuf, sizeof(msgbuf));
		fprintf(stderr, "Regex match failed: %s\n", msgbuf);
	}
	/* if everything went fine as far */
	if (result == STR2INT_SUCCESS) {
		tmp = strtol(s, NULL, 16);
		printf(">> GOT: %d\n", (int)tmp);
		*out = (int)tmp;
		/* VALIDATION */
		if (tmp < min) {
			result = STR2INT_UNDER;
		}
		if (tmp > max) {
			result = STR2INT_OVER;
		}
	}
	else
	       handle_mistake(&result, out, s, min, max, num_digits);
	return result;
}

void handle_mistake(str2int_errno *conv, int *out, char *s, int min,
			int max, int num_digits){
	char answ[3];
	parse_errno(conv, min, max, num_digits);
	puts("You made a mistake. Wanna enter data again? (y/n)");
	scanf("%s", answ);
	puts(answ);
	if (answ[0] == 'y'){	
		//input(s);
		fgets(s, 5, stdin);
		printf(">> %s\n", s);	
		str2int(out, s, min, max, num_digits);
	}
	else if (answ[0] == 'n'){
		puts("Exiting...");
		exit(2);
	}
	else {
		puts("Unable to parse your answer. Exiting...");
		exit(2);
	}

}

void parse_errno(str2int_errno *conv, int min, int max, int num_digits){
	if (*conv == STR2INT_UNDER)
		puts("Your input is below min");
	if (*conv == STR2INT_OVER)
		puts("Your input is above max");
	if (*conv == STR2INT_INCONV)
		puts("Your input cannot be parsed");
	printf("Value must be in range [%04x..%04x] (max %d digits)\n", min,
			max, num_digits);
}

void input(char *buff){
	puts("ENTER!!!");
	fgets(buff, 5, stdin);
}

int main(){
	char *buff = (char *)malloc(5 * sizeof(char));
	int tmp;
	input(buff);
	//fgets(buff, 5, stdin);
	str2int(&tmp, buff, 0, 0x4ff, 3);
	printf(">> %d\n", tmp);

	return 0;
}
