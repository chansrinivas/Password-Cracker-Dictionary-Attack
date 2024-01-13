#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#include "passwords.h"
#include "sha256.h"

#define DIG_BIN_LEN 32
#define DIG_STR_LEN ((DIG_BIN_LEN * 2) + 1)

void sha256(char *dest, char *src) {
	
    // zero out the sha256 context
    struct sha256_ctx ctx;
    memset(&ctx, 0, sizeof(ctx));

    // zero out the binary version of the hash digest
    unsigned char dig_bin[DIG_BIN_LEN];
    memset(dig_bin, 0, DIG_BIN_LEN);

    // zero out the string version of the hash digest
    memset(dest, 0, DIG_STR_LEN);

    // compute the binary hash digest
    __sha256_init_ctx(&ctx);
    __sha256_process_bytes(src, strlen(src), &ctx);
    __sha256_finish_ctx(&ctx, dig_bin);

    // convert it into a string of hexadecimal digits
    for (int i = 0; i < DIG_BIN_LEN; i++) {
        snprintf(dest, 3, "%02x", dig_bin[i]);
        dest += 2;
    }  
}



/* Method clear_text() to hash the clear text passwords through sha256 and compare with input hash
 * Parameters: str = passwords[i], inp_hash = argv[1]
 * strcmp() to compare the two hashes
 */

void clear_text(char *str, char* inp_hash){
	char clear_text_password[DIG_STR_LEN];
	strcpy(clear_text_password, str);
	sha256(clear_text_password, str);
	if(!strcmp(clear_text_password, inp_hash)){
	//printing out the clear text password if there is a match
		printf("%s\n", str);
		exit(0);
	} 
}



/* Method leet_speak() to convert clear text passwords into leet form, and hash them  and finally compare it with input hash
 * Parameters: password = passwords[i], str = argv[1] i.e, input hash
 * strcmp() to compare the two hashes
 */

void leet_speak(char* password, char* str){
	int len=strlen(password);
	char str1[len];
	int i;
	strcpy(str1, password); //str1 = leetified  password
	for(i = 0; i <= len; i++){
  		if(str1[i] == 'e'){
 			str1[i] = '3';
 		}
 		if(str1[i] == 'o'){
 			str1[i] = '0';
 		}
 		if(str1[i] == 'i'){
 			str1[i] = '!';
 		} 
 		if(str1[i] == 'a'){
 			str1[i] = '@';
 		}
 		if(str1[i] == 'h'){
 			str1[i] = '#';
 		}
 		if(str1[i] == 's'){
 			str1[i] = '$';
 		}
 		if(str1[i] == 't'){
 			str1[i] = '+';
 		}
	}
    char leet_speak_password[DIG_STR_LEN];
	sha256(leet_speak_password, str1);
	if(!strcmp(leet_speak_password, str)){
	//printing out leet form password if the match is found
		printf("%s\n", str1);
		exit(0);
	} 

}



/* Method add_one() to hash the added one form  passwords through sha256 and compare with input hash
 * Parameters: str = passwords[i], inp_hash = argv[1]
 * strcmp() to compare the two hashes
 */


int add_one(char *str, char* inp_hash){
	int len=strlen(str);
	char str1[len];
	strcpy(str1, str);
	strcat(str1, "1");
 	char added_one_password[DIG_STR_LEN];
	sha256(added_one_password, str1);
	if(!strcmp(added_one_password, inp_hash)){
	//printing out the added one form password if the match is found
		printf("%s\n", str1);
		exit(0);
	} 
	else {
		return 1;
	}
}


	
int main(int argc, char* argv[]){
	int i;
	//iterating through 10k passwords
	for(i=0; i<10000; i++){
		char str1[DIG_STR_LEN];
		strcpy(str1, argv[1]);
		clear_text(passwords[i], argv[1]);
	    leet_speak(passwords[i], str1);
		int n = add_one(passwords[i], str1);
		//if the last index of the passwords array is reached and there is no match found
		if(i==9999 && n==1){
			printf("not found\n");
			exit(0);
		}
	}
	return 0;
}

