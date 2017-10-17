#include "header.h"

int request_flag[MAX_NODE_] = {0,};
int LOCK_MANAGER = 0;
int LOCK_NODE = 0;
int blockcount = 0;
const int LOCAL_NODE = 0;
const int REMOTE_NODE = 1;

void* remove_blockchain() {
	struct block_v1 *ptr1;
	struct block_v1 *ptr2;
	ptr1 = GENESIS;
	ptr2 = ptr1->ptr;
	while(ptr1 != ptr2) {
		//printf(": free %p \n", ptr1);
		free(ptr1);
		ptr1 = ptr2;
		ptr2 = ptr2->ptr;
	}
	//printf(": free %p \n", ptr1);
	free(ptr1);
}

void remote_hashchain() {
	struct hashchain *ptr_1;
	struct hashchain *ptr_2;
	
	ptr_1 = GENESIS_HASH;
	ptr_2 = ptr_1->ptr;

	while(ptr_1 != ptr_2) {
		free(ptr_1);
		ptr_1 = ptr_2;
		ptr_2 = ptr_2->ptr;
	}
	free(ptr_1);
}

void *create_node(char *_name, char *_model_name, char *_firmware_version, char *_verifier) {
	struct node *NODE_ = (struct node*)malloc(sizeof(struct node));
	//memcpy(NODE_->name, _name, strlen(_name));
	//strncpy(NODE_->name, _name, sizeof(_name));
	strncpy(NODE_->model_name, _model_name, sizeof(NODE_->model_name));
	strncpy(NODE_->firmware_version, _firmware_version, sizeof(NODE_->firmware_version));
	strncpy(NODE_->verifier, _verifier, sizeof(NODE_->verifier));
	return NODE_;
}

void *create_manager(char *_name) {
	struct manager *MANAGER_ = (struct manager *)malloc(sizeof(struct manager ));
	strncpy(MANAGER_->name, _name, sizeof(MANAGER_->name));
	return MANAGER_;
}

void *create_block(float _size, int _version, char *_prev_hash, time_t _time, int _difficalty, int _nonce, int _type, char *_model, int _firmware_version, char *_verifier) {
	// to create GENESIS BLOCK
	struct block_v1 *BLOCK_ = malloc(sizeof(struct block_v1));
	BLOCK_->size = _size;
	BLOCK_->version = _version;
	strncpy(BLOCK_->prev_hash, "GENESIS", sizeof(BLOCK_->prev_hash));
	BLOCK_->time = _time;
	BLOCK_->difficalty = _difficalty;
	BLOCK_->nonce = _nonce;
	BLOCK_->type = _type;
	strncpy(BLOCK_->model, "-", sizeof(BLOCK_->model));
	BLOCK_->firmware_version = _firmware_version;
	strncpy(BLOCK_->verifier, "-", sizeof(BLOCK_->verifier));
	//BLOCK_->ptr = BLOCK_;

	return BLOCK_;
}

void *create_hash(struct block_v1 *_blocks) {
	struct hashchain *HASH_ = malloc(sizeof(struct hashchain));
	
	//memset(_hashchain, 0, (sizeof(_hashchain)));
	
	unsigned char buf[SHA256_BLOCK_SIZE];
	memset(&buf, '\0', sizeof(buf) );
	memset(HASH_, '\0', sizeof(struct hashchain));
	SHA256_CTX ctx;
	
	sha256_init(&ctx);
	sha256_final(&ctx, buf);
	//print_hash(buf);
	//printf("::: %p \n", HASH_);
	
	memcpy(HASH_->hash, buf, sizeof(buf));
	//print_hash(HASH_->hash);
	
	HASH_->ptr = HASH_;
	//printf("::: init: %p, %p \n", HASH_, HASH_->ptr);
	
	return HASH_;
}

void print_hash(unsigned char hash[])
{
   int idx;
   for (idx=0; idx < 32; idx++)
      printf("%02x",hash[idx]);
   //printf("\n");
}

/*
int add_block(float _size, int _version, char *_prev_hash, int _merkle_root, int _verification_count, char *_merkle_tree, int _verification_log, char *_model, int _firmware_version, char *_verifier, int _node_request, int _node_respon) { 
	// for adding blocks at the bockchain //
	struct block *BLOCK_ = malloc(sizeof(struct block));
	//printf("::::: ADD_BLOCK \n");
	BLOCK_->size = _size;
	BLOCK_->version = _version;
	//strncpy(BLOCK_->prev_hash, "_prev_hash", sizeof(BLOCK_->prev_hash));
	strncpy(BLOCK_->prev_hash, "-", sizeof(BLOCK_->prev_hash));
	BLOCK_->merkle_root[0] = _merkle_root;
	BLOCK_->verification_count = _verification_count;
	//strncpy(BLOCK_->merkle_tree, "_merkle_tree", sizeof(BLOCK_->merkle_tree));
	strncpy(BLOCK_->merkle_tree, "-", sizeof(BLOCK_->merkle_tree));
	// verification_log[0] = timestemp
	// verification_log[1] = requester`s ID
	// verification_log[2] = responser`s ID
	BLOCK_->verification_log[0] = time_stamp();
	BLOCK_->verification_log[1] = _node_request;
	BLOCK_->verification_log[2] = _node_respon;
	//strncpy(BLOCK_->verification_log, "-", sizeof(BLOCK_->verification_log));
	strncpy(BLOCK_->model, _model, sizeof(BLOCK_->model));
	//printf("_firmware_version: %d \n", _firmware_version);
	BLOCK_->firmware_version = _firmware_version;
	strncpy(BLOCK_->verifier, _verifier, sizeof(BLOCK_->verifier));
	
	//move to end of Blockchain
	block_ptr = GENESIS;
	while (block_ptr->ptr != block_ptr) {
		block_ptr = block_ptr->ptr;
	}
		
	block_ptr->ptr = BLOCK_;
	BLOCK_->ptr = BLOCK_;
	//return (void *)BLOCK_;
	return 0;
}
*/
/*
void select_attacker(struct node *data) {
	strncpy(data->firmware_version, "1500", sizeof(data->firmware_version));
}

*/
int firmware_update(int _from, int _to) {
	//char * strncpy ( char * destination, const char * source, size_t num );
	strncpy(NODE_info[_to]->firmware_version, NODE_info[_from]->firmware_version, sizeof(NODE_info[_to]->firmware_version));
}

int version_check(int _local, int _remote) {
	LOCK_NODE = 1;
	char local_version[5];
	char remote_version[5];
	strncpy(local_version, NODE_info[_local]->firmware_version, sizeof( NODE_info[_local]->firmware_version));
	local_version[5] = '\0';
	strncpy(remote_version, NODE_info[_remote]->firmware_version, sizeof(NODE_info[_remote]->firmware_version));
	remote_version[5] = '\0';
	int version_local = atoi(local_version);
	int version_remote = atoi(remote_version);
	//int num_local = atoi(local->name);
	//int num_remote = atoi(remote->name);
	int manager = NODE_info[_local]->manager_num;
	
	if (version_local == version_remote) {
		// request verification
		// assume that remote info is arrived to local in this stage
		//printf(":: VERSION_CHECK - firmware verificaiton request %d and %d \n", _local, _remote);
		LOCK_MANAGER = 1;
		// notify version check request to local`s manager
		MANAGER_info[manager]->request_flag[LOCAL_NODE] = _local;
		MANAGER_info[manager]->request_flag[REMOTE_NODE] = _remote;
		//printf(":: VERSION_CHECK - firmware verificaiton request %d and %d \n", MANAGER_info[manager]->request_flag[LOCAL_NODE], MANAGER_info[manager]->request_flag[REMOTE_NODE]);
		
		request_flag[_local] = 0;
		request_flag[_remote] = 0;
		
		LOCK_MANAGER = 0;
		LOCK_NODE = 0;
		
		return 0;
		
	} else { 
		// In case Node need firmware update
		if (version_local < version_remote) {
			//printf(":: VERSION_CHECK - firmware update: local\n");
			firmware_update(_remote, _local);
			if (version_check(_local, _remote) == 0 ) {
				//printf(":: VERSION_CHECK - firmware update complite : FROM remote to local\n");
				version_check(_remote, _local);
			}
			LOCK_NODE = 0;
			return -1;
		} else if (version_local > version_remote) {
			//printf(":: VERSION_CHECK - firmware update: remote\n");
			firmware_update(_local, _remote);
			if (version_check(_remote, _local) == 0 ) {
				//printf(":: VERSION_CHECK - firmware update complite : FROM local to remote\n");
				version_check(_local, _remote);
			}
			LOCK_NODE = 0;
			return 1;
		}
	}
	return -2;	
}
void print_binary(unsigned int integer_) {
	unsigned int i = 32;
	unsigned int num = integer_;
	
	printf("::::: num %d is ", num);
	for(i; i>=0; --i) {
		printf("%d", (num>>i) & 1 );
	}
	printf("\n ");
}

void print_Blockchain() {
	int block_num = 0;
	struct block_v1 *block_ptr_;
	struct hashchain *hash_ptr_;
	block_ptr_ = GENESIS;
	struct hashchain *blockhash_ptr_;
	hash_ptr_ = GENESIS_HASH;
		
	// print GENESIS Block	
	float _size = block_ptr_->size;
	int _version = block_ptr_->version;
	char _prev_hash[50];
	strncpy(_prev_hash, block_ptr_->prev_hash, sizeof(_prev_hash));
	time_t _time = block_ptr_->time;
	int _difficalty = block_ptr_->difficalty;
	int _nonce = block_ptr_->nonce;
	int _type = block_ptr_->type;
	char _model[50];
	
	strncpy(_model, block_ptr_->model, sizeof(_model));
	_model[5] = '\0';
	int _firmware_version = block_ptr_->firmware_version;
	char _verifier[50];
	strncpy(_verifier, block_ptr_->verifier, sizeof(_verifier));
	
	printf("::: - GENESIS block: ");
	print_hash(GENESIS_HASH->hash);
	printf(", %p, %f, %d, %s\n", block_ptr_->ptr, _size, _version, _prev_hash);
		
	block_ptr_ = block_ptr_->ptr;
	hash_ptr_ = hash_ptr_->ptr;
	
	while(block_ptr_ != block_ptr_->ptr && hash_ptr_!= hash_ptr_->ptr) {
		block_num++;
		//strncpy(_prev_hash, block_ptr_->prev_hash, sizeof(block_ptr_->prev_hash));
		
		strncpy(_model, block_ptr_->model, sizeof(block_ptr_->model));
		_model[5] = '\0';
		_firmware_version = block_ptr_->firmware_version;
		strncpy(_verifier, block_ptr_->verifier, sizeof(block_ptr_->verifier));
		
		printf("::: - %d block: ", block_num);
		print_hash(hash_ptr_->hash);
		printf("%s, %d, %s \n", _model, _firmware_version, _verifier);
		
		block_ptr_ = block_ptr_->ptr;
		hash_ptr_ = hash_ptr_->ptr;
	}	
}

/*

int check_req_version_chk() {
	//printf("::: ! req_version_check, ");
	//for(int i = 0; i < MAX_NODE; i++) {
	//	//printf(" %d", request_flag[i]);
	//}
	//printf(" \n");
	
	for(int i = 0; i < MAX_NODE; i++) {
		//if(request_flag[i] != 0 ) {
		//	return i;
		//} else {
		//	return 0;
		//}
		if(request_flag[i] != 0 ) 
			return i;	
	}
	return 0;
}
*/
/*

void* t_function(void *_data) {
	struct node *NODE_info_ = _data;
	char tmp[4];
	int thr_num = atoi(NODE_info_->name);
	strncpy(tmp, NODE_info_->firmware_version, sizeof(NODE_info_->firmware_version));
	//printf(":::- thread %d is version %d \n", thr_num, atoi(tmp));
	
	while(lock !=0) {
		//printf(":::- thread %d sleep!!!!!! \n", thr_num);
		sleep(1);
	}
	if (thr_num != VICTIM_NODE) {
		// 공격 노드일 경우
		// 1. 펌웨어 업데이트 체크
		// 2. 펌웨어 인증 수행
		//printf(":::- thread thr_num != VICTIM_NODE \n");
		version_check(NODE_info_, DEVICE_info[VICTIM_NODE]);
			
	} else {
		// 자기가 Victim 스레드 일 경우
		// 자기 검증을 수행하지 않도록 예외처리
		//printf(":::- thread else \n");
		int _remote_node = check_req_version_chk();
		if(thr_num != _remote_node) {
			version_check(NODE_info_, DEVICE_info[_remote_node]);
			version_check(DEVICE_info[_remote_node], NODE_info_);
		}
	}
	/*
	if (check_req_version_chk() == 0) {
		//printf("::: setting thread %d as chk req\n", thr_num);
		request_flag[thr_num] = 1;
		
	} else {
		//printf(":::: version check - thr %d req to %d \n", thr_num, check_req_version_chk() );
		version_check(DEVICE_info[thr_num], DEVICE_info[check_req_version_chk()]);
	}
	*/
	/*
	for(int i = 0; i<10; i++) {
		printf(":::- thread %s is version %d \n", NODE_info_->name, atoi(tmp));
	}
	*/
/*
}
*/
void* NODE_function(struct node *_NODE_info) {
	//printf("NODE_function\n");
	sleep(1);
	int thr_num = atoi(_NODE_info->name);
	
	srand(time(NULL));
	int MY_MANAGER_NO = rand() % MAX_MANAGER;
	_NODE_info->manager_num = MY_MANAGER_NO;
	//printf("node %d manager is %d \n", thr_num, _NODE_info->manager_num);
	// make firmware request
	// check if there is requester
	
	while(LOCK_NODE == 1) {
		//printf("::thr %d is spinning \n", thr_num);
		sleep(1);
	}
	
	for(int i = 0; i<MAX_NODE; i++) {
		//printf("::thr %d is in for \n", thr_num);
		if(i == thr_num) {
			// just in case the node check by himself
			continue;
		}
		if (request_flag[i] == 1) {
			// verificaiton start 
			//printf("::thr %d is version checking \n", thr_num);
			version_check(thr_num, i);
			break;
		}
		request_flag[thr_num] = 1;
	}
	
	// firmware verification request to Manager // 
	while (LOCK_MANAGER != 0) {
		//checking lock
		//printf("::thr %d spining in lockmanager \n", thr_num);
		sleep(1);
	}
}

void* MANAGER_function(struct manager *_MANAGER_info) {
	//printf("MANAGER_function\n");
	sleep(3);
	int _blockcount = 0;
	int round = 0;
	_MANAGER_info->request_flag[0] = -1;
	_MANAGER_info->request_flag[1] = -1;
	
	while (round != 5) {
		if (blockcount != _blockcount) {
			// assume block is made, knowtice newblock
			_blockcount = blockcount;
			//printf("::: New Block found \n");
		}
		//printf("::: MANAGER %s: flag is %d, %d \n", _MANAGER_info->name ,_MANAGER_info->request_flag[0], _MANAGER_info->request_flag[1]);
		while (LOCK_MANAGER == 1) {
			sleep(1);
		}
		
		if(_MANAGER_info->request_flag[0] >= 0) {
		// calculate PoW
			//printf("::: MANAGER %s: %d, and %d is verifying \n", _MANAGER_info->name ,_MANAGER_info->request_flag[0], _MANAGER_info->request_flag[1]);
		}
		round++;
		sleep(1);
		//printf("::: round : %d \n", round);
	}
}	

int main() {
	char tmp[3] = {0,};
	
	GENESIS = create_block(0.1, 1, '\0', 0, 0, 0, 0, '\0', 0, '\0');
	GENESIS->ptr = GENESIS;
	GENESIS_HASH = create_hash(GENESIS);
	
	block_ptr = GENESIS;
	hash_ptr = GENESIS_HASH;
		
	printf(": Genesis Block is ready \n");
	NODE_INFO = create_node("NODE", "XU", "1402", "6c3d0216f7fd482cdac2aa054af61065");
	MANAGER_INFO = create_manager("MANAGER");
	
	for(int i=0; i<MAX_NODE; i++) {
		sprintf(tmp, "%d", i);
		tmp[2] = '\0';
		NODE_info[i] = create_node(tmp, "XU\0", "1402", "6c3d0216f7fd482cdac2aa054af61065");
	}
	for(int i=0; i<MAX_MANAGER; i++) {
		sprintf(tmp, "%d", i);
		tmp[2] = '\0';
		MANAGER_info[i] = create_manager(tmp);
	}
	
	/////////////////////////////////////////////
	/////////////////////////////////////////////
		
	int NODE_thr_id, NODE_status, MANAGER_thr_id, MANAGER_status;
	pthread_t NODE_thread[MAX_NODE], MANAGER_thread[MAX_MANAGER];
	
	for(int i=0; i<MAX_MANAGER; i++) {
		MANAGER_thr_id = pthread_create(&MANAGER_thread[i], NULL, MANAGER_function, (void *)MANAGER_info[i]);
	}
	
	for(int i=0; i<MAX_NODE; i++) {
		NODE_thr_id = pthread_create(&NODE_thread[i], NULL, NODE_function, (void *)NODE_info[i]);
	} 
	printf("::: create %d NODES \n", MAX_NODE);
	printf("::: create %d MANAGERS \n", MAX_MANAGER);
	
	for(int i=0; i<MAX_NODE; i++) {
		pthread_join(NODE_thread[i], (void **)&NODE_status);
	}
	
	for(int i=0; i<MAX_MANAGER; i++) {
		pthread_join(MANAGER_thread[i], (void **)&MANAGER_status);
	}
	
	print_Blockchain();
	//print_binary(10);
	//remove_blockchain();
	//remote_hashchain();
	
	return 0;
}