#include "header.h"

struct node *INFO;
struct block *block_ptr;

/*
int self_check(struct node NODE_INFO) {
	if (strncmp(NODE_INFO.model_name, INFO.model_name, sizeof(INFO.model_name-1))) {
		printf(":: SELF_CHECK - Firmware Info is changed, model_name\n");
		return 1;
	}
	if (strncmp(NODE_INFO.firmware_version, INFO.firmware_version, sizeof(INFO.firmware_version-1))) {
		printf(":: SELF_CHECK - Firmware Info is changed, firmware_version\n");
		return 1;
	}
	if (strncmp(NODE_INFO.verifier, INFO.verifier, sizeof(INFO.verifier-1))) {
		printf(":: SELF_CHECK - Firmware Info is changed, verifier\n");
		return 1;
	}
	printf(":: SELF_CHECK - Firmware Info is NOT changed\n");
	return 0;
}
*/

int request_check(struct node local, struct node remote) {
	if (strncmp(local.model_name, remote.model_name, sizeof(local.model_name-1))) {
		printf(":: REQUEST_CHECK - Firmware Model is different\n");
		return 1;
	} 
	
	char local_version[5];
	char remote_version[5];
	//printf(":: name: %s %s\n", local.firmware_version, remote.firmware_version);
	strncpy(local_version, local.firmware_version, sizeof(local_version)-1);
	strncpy(remote_version, remote.firmware_version, sizeof(remote_version)-1);
	//printf(":: name: %s %s\n", local_version, remote_version);
	int version_local = atoi(local_version);
	int version_remote = atoi(remote_version);
		
	if (version_local == version_remote) {
		printf(":: REQUEST_CHECK - firmware version is the same\n");
		return 1;
	} else {
		if (version_local < version_remote) {
			printf(":: REQUEST_CHECK - firmware update: local\n");
		} else if (version_local > version_remote) {
			printf(":: REQUEST_CHECK - firmware update: remote\n");
		}
	}
	return 0;	
}

struct block *create_block(float _size, int _version, char *_prev_hash, int _merkle_root, int _verification_count, char *_merkle_tree, char *_verification_log, char *_model, int _firmware_version, char *_verifier) {
	// to create GENESIS BLOCK
	struct block *BLOCK_ = malloc(sizeof(struct block));
	BLOCK_->size = _size;
	BLOCK_->version = _version;
	strncpy(BLOCK_->prev_hash, "_prev_hash", sizeof(BLOCK_->prev_hash));
	BLOCK_->merkle_root[0] = _merkle_root;
	BLOCK_->verification_count = _verification_count;
	strncpy(BLOCK_->merkle_tree, "_merkle_tree", sizeof(BLOCK_->merkle_tree));
	strncpy(BLOCK_->verification_log, "_verification_log", sizeof(BLOCK_->merkle_tree));
	strncpy(BLOCK_->model, "_model", sizeof(BLOCK_->model));
	BLOCK_->firmware_version = _firmware_version;
	strncpy(BLOCK_->verifier, "_verifier", sizeof(BLOCK_->verifier));
	//BLOCK_->ptr = BLOCK_;
	return BLOCK_;
}

int add_block(float _size, int _version, char *_prev_hash, int _merkle_root, int _verification_count, char *_merkle_tree, char *_verification_log, char *_model, int _firmware_version, char *_verifier, struct block *_prev_block) { 
	// for adding blocks at the bockchain //
	struct block *BLOCK_ = malloc(sizeof(struct block));
	BLOCK_->size = _size;
	BLOCK_->version = _version;
	strncpy(BLOCK_->prev_hash, "_prev_hash", sizeof(BLOCK_->prev_hash));
	BLOCK_->merkle_root[0] = _merkle_root;
	BLOCK_->verification_count = _verification_count;
	strncpy(BLOCK_->merkle_tree, "_merkle_tree", sizeof(BLOCK_->merkle_tree));
	strncpy(BLOCK_->verification_log, "_verification_log", sizeof(BLOCK_->merkle_tree));
	strncpy(BLOCK_->model, "_model", sizeof(BLOCK_->model));
	BLOCK_->firmware_version = _firmware_version;
	strncpy(BLOCK_->verifier, "_verifier", sizeof(BLOCK_->verifier));
	_prev_block->ptr = BLOCK_;
	BLOCK_->ptr = BLOCK_;
	return BLOCK_;
}

struct node *create_node(char *_name, char *_model_name, char *_firmware_version, char *_verifier) {
	struct node *NODE_ = (struct node*)malloc(sizeof(struct node));
	strncpy(NODE_->name, _name, sizeof(NODE_->name));
	strncpy(NODE_->model_name, _model_name, sizeof(NODE_->model_name));
	strncpy(NODE_->firmware_version, _firmware_version, sizeof(NODE_->firmware_version));
	strncpy(NODE_->verifier, _verifier, sizeof(NODE_->verifier));
	return NODE_;
}


void* t_function(void *data) {
	int i = 0;
	printf(":::- thread!\n");
}

int main() {
	char tmp[10] = {0,};
	
	printf(": creating GENESIS Block \n");
	
	// creating genesis block //
	GENESIS = create_block(0.1, 0, '\0', 0, 0, '\0', '\0', '\0', 0, '\0');
	block_ptr = GENESIS;
	printf(": Genesis Block is ready \n");
	
	
	////// FOR DEBUGING BLOCKCHAINS //
	/*
	//block_ptr = add_block(0.1, 1, '\0', 0, 0, '\0', '\0', '\0', 0, '\0', block_ptr);
		block_ptr = GENESIS;
	printf(":::: = %d", block_ptr->version);
	block_ptr = block_ptr->ptr;
	printf(":::: = %d", block_ptr->version);
	//////
	*/

	// create node info //
	/*
	strncpy(INFO.name, "INFOMATION\0", sizeof(INFO.name));
	strncpy(INFO.model_name, "XU\0", sizeof(INFO.model_name));
	strncpy(INFO.firmware_version, "1402", sizeof(INFO.firmware_version));
	strncpy(INFO.verifier, "6c3d0216f7fd482cdac2aa054af61065", sizeof(INFO.verifier));
	printf(":: name-%s, model-%s, ver/hash-%s\n", INFO.name, INFO.model_name, INFO.firmware_version);
	*/
	
	INFO = create_node("INFOMATION\0", "XU\0", "1402", "6c3d0216f7fd482cdac2aa054af61065");
	printf(":: name-%s, model-%s, ver/hash-%s\n", INFO->name, INFO->model_name, INFO->firmware_version);
	
	
	// create nodes //
	struct node *DEVICE_info[MAX_NODE];
	for(int i=0; i<MAX_NODE; i++) {
		sprintf(tmp, "%d", i);
		DEVICE_info[i] = create_node(tmp, "XU\0", "1402", "6c3d0216f7fd482cdac2aa054af61065");
		//strncpy(DEVICE_info[i].name, tmp, sizeof(DEVICE_info[i].name));
	}
		
	printf(":: name-%s, model-%s, ver/hash-%s\n", DEVICE_info[0]->name, DEVICE_info[0]->model_name, DEVICE_info[0]->firmware_version);
	printf(":: name-%s, model-%s, ver/hash-%s\n", DEVICE_info[1]->name, DEVICE_info[1]->model_name, DEVICE_info[1]->firmware_version);
	//////////////////////////////////////////////////////////////////
	/*
	int thread_id, status;
	pthread_t p_thread[MAX_NODE];
	int a = 100;
	printf("::: Create Thread \n");
	thread_id = pthread_create(&p_thread[0], NULL, t_function, (void *)&DEVICE_info[0]);
	thread_id = pthread_create(&p_thread[1], NULL, t_function, (void *)&DEVICE_info[1]);
    if (thread_id < 0) {
        perror("thread create error : ");
        exit(0);
    }
	
	pthread_join(p_thread[0], (void *) &status);
	pthread_join(p_thread[1], (void *) &status);
	*/
	//////////////////////////////////////////////////////////////////
	
	//self_check(DEVICE_info[0]);
	//request_check(DEVICE_info[0], DEVICE_info[1]);
	
	// delete list
	/*
	while (!SLIST_EMPTY(&BLOCKCHAIN_LIST)) { 
		printf(": Delete List");
    	GENESIS = SLIST_FIRST(&BLOCKCHAIN_LIST);
        SLIST_REMOVE_HEAD(&BLOCKCHAIN_LIST, BLOCKCHAIN);
        free(GENESIS);
    }
	*/
	// end thread
	//pthread_join(p_thread[0], (void **)&status);
    //pthread_join(p_thread[1], (void **)&status);

	return 0;
}