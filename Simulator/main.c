#include "header.h"

int main() {
	printf("Start test\n");
	printf(": creating GENESIS Block \n");
	// creating genesis block //
	struct block GENESIS;
	GENESIS.version	= 0.1;
	GENESIS.prev_hash[0] = '\0';
	GENESIS.merkle_root[0] = 0;
	GENESIS.verification_count = 0;
	GENESIS.merkle_tree[0] = '\0';
	GENESIS.verification_log[0] = '\0';
	GENESIS.model[0] = '\0';
	GENESIS.firmware_version = 0;
	GENESIS.verifier[0] = '\0';
	printf(": Genesis Block is ready \n");

	// create node info //
	struct node INFO;
	strncpy(INFO.name, "INFOMATION\0", sizeof(INFO.name));
        strncpy(INFO.model_name, "XU\0", sizeof(INFO.model_name));
        strncpy(INFO.firmware_version, "1402", sizeof(INFO.firmware_version));
        strncpy(INFO.verifier, "6c3d0216f7fd482cdac2aa054af61065", sizeof(INFO.verifier));
	printf(":: name-%s, model-%s, ver/hash-%s\n", INFO.name, INFO.model_name, INFO.firmware_version);
		
	// create 6 nodes //
	//struct node DEVICE[6];
	//strncpy(DEVICE[0].name, "no.1\0", sizeof(DEVICE[0].name));
	//strncpy(DEVICE[0].model_name, "XU\0", sizeof(DEVICE[0].model_name));
	//strncpy(DEVICE[0].firmware_version, "1", sizeof(DEVICE[0].firmware_version));
	//strncpy(DEVICE[0].verifier, "6c3d0216f7fd482cdac2aa054af61065", sizeof(DEVICE[0].verifier));
	// DEVICE[1] 	DEVICE[2] 	DEVICE[3] 	DEVICE[4] 	DEVICE[5]
	//
	// end

	return 0;
}


