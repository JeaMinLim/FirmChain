#include "header.h"

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

int request_flag[MAX_NODE_] = {0,};
int lock = 0;

int verify_firmware(struct node *_checking_node) {
	// 만약 블록체인에 있는 responsed 에 6번 이상 같은 번호가 있으면 인증됨.
	int _node_id = atoi(_checking_node->name);
	//printf("::: verify_firmware - %d \n", _node_id);
	//struct block *_tmp = malloc(sizeof(struct block));
	int count = 0;
	
	block_ptr = GENESIS;
	while(block_ptr != block_ptr->ptr) {
		block_ptr = block_ptr->ptr;
		if(block_ptr->verification_log[2] == _node_id) {
			count++;
		}
	}
	//printf("::: verify_firmware - %d node verify count is %d \n", _node_id, count);
	if(count >= 6) {
		printf("::: node %d is verified \n", _node_id);
	} else {
		printf("::: node %d is not verified \n", _node_id);
	}
	
	return 0;
}

int time_stamp() {
    struct timeval val;
    struct tm *ptm;
	char tmp[10] = {0,};
	int time = 0;

    gettimeofday(&val, NULL);
    ptm = localtime(&val.tv_sec);
    // format : ssuuuuuu
    sprintf(tmp, "%d%ld", ptm->tm_sec, val.tv_usec);
	//tmp[6] = '\0';
	time = atoi(tmp);
	
	return time;
}

void* remove_blockchain() {
	struct block *ptr1;
	struct block *ptr2;
	
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

struct block *create_block(float _size, int _version, char *_prev_hash, int _merkle_root, int _verification_count, char *_merkle_tree, char *_verification_log, char *_model, int _firmware_version, char *_verifier) {
	// to create GENESIS BLOCK
	struct block *BLOCK_ = malloc(sizeof(struct block));
	BLOCK_->size = _size;
	BLOCK_->version = _version;
	strncpy(BLOCK_->prev_hash, "GENESIS", sizeof(BLOCK_->prev_hash));
	BLOCK_->merkle_root[0] = _merkle_root;
	BLOCK_->verification_count = _verification_count;
	strncpy(BLOCK_->merkle_tree, "-", sizeof(BLOCK_->merkle_tree));
	strncpy(BLOCK_->verification_log, "-", sizeof(BLOCK_->merkle_tree));
	strncpy(BLOCK_->model, "-", sizeof(BLOCK_->model));
	BLOCK_->firmware_version = _firmware_version;
	strncpy(BLOCK_->verifier, "-", sizeof(BLOCK_->verifier));
	//BLOCK_->ptr = BLOCK_;
	return BLOCK_;
}

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

void select_attacker(struct node *data) {
	strncpy(data->firmware_version, "1500", sizeof(data->firmware_version));
}

int firmware_update(struct node *from, struct node *to) {
	//char * strncpy ( char * destination, const char * source, size_t num );
	strncpy(to->firmware_version, from->firmware_version, sizeof(to->firmware_version));
}

int version_check(struct node *local, struct node *remote) {
	lock = 1;
	char local_version[5];
	char remote_version[5];
	//printf(":: name: %s %s\n", local.firmware_version, remote.firmware_version);
	//printf(":: local: %s remote: %s \n", local->name, remote->name);
	strncpy(local_version, local->firmware_version, sizeof(local->firmware_version));
	local_version[5] = '\0';
	strncpy(remote_version, remote->firmware_version, sizeof(remote->firmware_version));
	remote_version[5] = '\0';
	//printf(":: name: %s %s\n", local_version, remote_version);
	int version_local = atoi(local_version);
	int version_remote = atoi(remote_version);
	int num_local = atoi(local->name);
	int num_remote = atoi(remote->name);
	
	if (version_local == version_remote) {
		//printf(":: VERSION_CHECK - firmware version is the same local is %d, remote is %d\n", num_local, num_remote);
		// local create block for remote
		//printf("version_local == version_remote %s, %s, %s \n", remote->model_name, remote_version, remote->verifier);
		add_block(0.0, 1, '\0', 0, 0, '\0', '\0', remote->model_name, version_remote, remote->verifier, num_local, num_remote);
		//block_ptr = add_block(0.1, 0, '\0', 0, 0, '\0', '\0', '\0', 0, '\0', block_ptr);
		//void* add_block(float _size, int _version, char *_prev_hash, int _merkle_root, int _verification_count, char *_merkle_tree, char *_verification_log, char *_model, int _firmware_version, char *_verifier)
		//block_ptr = add_block(0.1, 0, '\0', 0, 0, '\0', '\0', '\0', 0, '\0', block_ptr);
		//add_block(0, 1, '\0', 0, 0, '\0', '\0', local->model_name, version_remote, local->verifier);
		//printf(":: VERSION_CHECK - unset %d, %d \n", num_local, num_remote);
		//request_flag[num_local] = 0;
		//request_flag[num_remote] = 0;
		
		lock = 0;
		return 0;
	} else {
		if (version_local < version_remote) {
			//printf(":: VERSION_CHECK - firmware update: local\n");
			firmware_update(remote, local);
			if (version_check(local, remote) == 0 ) {
				//printf(":: VERSION_CHECK - firmware update complite : FROM remote to local\n");
				version_check(remote, local);
			}
			lock = 0;
			return -1;
		} else if (version_local > version_remote) {
			//printf(":: VERSION_CHECK - firmware update: remote\n");
			firmware_update(local, remote);
			if (version_check(remote, local) == 0 ) {
				//printf(":: VERSION_CHECK - firmware update complite : FROM local to remote\n");
				version_check(local, remote);
			}
			lock = 0;
			return 1;
		}
	}
	lock = 0;
	return -2;	
}

void print_Blockchain() {
	int i = 0;
	struct block *block_ptr_;
	block_ptr_ = GENESIS;
	
	// copy info from block // 
	float _size = block_ptr_->size;
	int _version = block_ptr_->version;
	char _prev_hash[50];
	strncpy(_prev_hash, block_ptr_->prev_hash, sizeof(_prev_hash));
	int _merkle_root[50] = {0,};
	_merkle_root[0] = block_ptr_->merkle_root[0];
	int _verification_count = block_ptr_->verification_count;
	char _merkle_tree[50];
	//strncpy(_merkle_tree, block_ptr_->merkle_tree, sizeof(_merkle_tree));
	strncpy(_merkle_tree, "-", sizeof(_merkle_tree));
	_merkle_tree[2] = '\0';
	//char _verification_log[50];
	// verification_log[0] = timestemp
	// verification_log[1] = requester`s ID
	// verification_log[2] = responser`s ID
	unsigned int _verification_log[3];
	_verification_log[0] = block_ptr_->verification_log[0];
	_verification_log[1] = block_ptr_->verification_log[1];
	_verification_log[2] = block_ptr_->verification_log[2];
	//strncpy(_verification_log, block_ptr_->verification_log, sizeof(_verification_log));
	_verification_log[5] = '\0';
	char _model[50];
	strncpy(_model, block_ptr_->model, sizeof(_model));
	_model[5] = '\0';
	int _firmware_version = block_ptr_->firmware_version;
	char _verifier[50];
	strncpy(_verifier, block_ptr_->verifier, sizeof(_verifier));
	
	///////////////////////
	printf("::: - GENESIS block: %p, %f, %d, %s, %d, %d, %s, %s, %d, %s \n", block_ptr_->ptr, _size, _version, _prev_hash, _merkle_root[0], _verification_count, _merkle_tree, _model, _firmware_version, _verifier);
	block_ptr_ = block_ptr_->ptr;
	while(block_ptr_ != block_ptr_->ptr) {
		i++;
		_size = block_ptr_->size;
		_version = block_ptr_->version;
		strncpy(_prev_hash, block_ptr_->prev_hash, sizeof(block_ptr_->prev_hash));
		_merkle_root[0] = block_ptr_->merkle_root[0];
		_verification_count = block_ptr_->verification_count;
		strncpy(_merkle_tree, "-", sizeof(_merkle_tree));
		_merkle_tree[2] = '\0';
		// verification_log[0] = timestemp
		// verification_log[1] = requester`s ID
		// verification_log[2] = responser`s ID
		_verification_log[0] = block_ptr_->verification_log[0];
		_verification_log[1] = block_ptr_->verification_log[1];
		_verification_log[2] = block_ptr_->verification_log[2];
		//strncpy(_verification_log, block_ptr_->verification_log, sizeof(_verification_log));
		_verification_log[5] = '\0';
		strncpy(_model, block_ptr_->model, sizeof(block_ptr_->model));
		_model[5] = '\0';
		_firmware_version = block_ptr_->firmware_version;
		strncpy(_verifier, block_ptr_->verifier, sizeof(block_ptr_->verifier));
		
		//printf("::: - %d block: %p, %f, %d, %s, %d, %d, %s, %s, %d, %s \n", i, block_ptr_->ptr, _size, _version, _prev_hash, _merkle_root[0], _verification_count, _merkle_tree, _model, _firmware_version, _verifier);
		printf("::: - %d block - time: %d, req: %d, resp: %d - %s, %d, %s \n", i, _verification_log[0], _verification_log[1], _verification_log[2], _model, _firmware_version, _verifier);
		//printf("::: \t\t time: %d, req: %d, resp: %d - \n", );
		block_ptr_ = block_ptr_->ptr;
	}
	
	i++;
	_size = block_ptr_->size;
	_version = block_ptr_->version;
	strncpy(_prev_hash, block_ptr_->prev_hash, sizeof(block_ptr_->prev_hash));
	_merkle_root[0] = block_ptr_->merkle_root[0];
	_verification_count = block_ptr_->verification_count;
	strncpy(_merkle_tree, "-", sizeof(_merkle_tree));
	_merkle_tree[2] = '\0';
	// verification_log[0] = timestemp
	// verification_log[1] = requester`s ID
	// verification_log[2] = responser`s ID
	_verification_log[0] = block_ptr_->verification_log[0];
	_verification_log[1] = block_ptr_->verification_log[1];
	_verification_log[2] = block_ptr_->verification_log[2];
	//strncpy(_verification_log, block_ptr_->verification_log, sizeof(_verification_log));
	_verification_log[5] = '\0';
	strncpy(_model, block_ptr_->model, sizeof(block_ptr_->model));
	_model[5] = '\0';
	_firmware_version = block_ptr_->firmware_version;
	strncpy(_verifier, block_ptr_->verifier, sizeof(block_ptr_->verifier));
	printf("::: - %d block - time: %d, req: %d, resp: %d - %s, %d, %s \n", i, _verification_log[0], _verification_log[1], _verification_log[2], _model, _firmware_version, _verifier);
}

struct node *create_node(char *_name, char *_model_name, char *_firmware_version, char *_verifier) {
	struct node *NODE_ = (struct node*)malloc(sizeof(struct node));
	strncpy(NODE_->name, _name, sizeof(NODE_->name));
	strncpy(NODE_->model_name, _model_name, sizeof(NODE_->model_name));
	strncpy(NODE_->firmware_version, _firmware_version, sizeof(NODE_->firmware_version));
	strncpy(NODE_->verifier, _verifier, sizeof(NODE_->verifier));
	return NODE_;
}

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
}

int main() {
	char tmp[10] = {0,};
	
	//printf(": creating GENESIS Block \n");
	
	// creating genesis block //
	GENESIS = create_block(0.1, 0, '\0', 0, 0, '\0', '\0', '\0', 0, '\0');
	GENESIS->ptr = GENESIS;
	block_ptr = GENESIS;
	//printf(": Genesis Block is ready \n");
	
	//block_ptr = add_block(0.1, 0, '\0', 0, 0, '\0', '\0', '\0', 0, '\0', block_ptr);
	//block_ptr = GENESIS;
	//printf(":::: = %d\n", block_ptr->version);
	//block_ptr = block_ptr->ptr;
	//printf(":::: = %d\n", block_ptr->version);
	//////
	////// FOR DEBUGING BLOCKCHAINS //
	//print_Blockchain();
	// create node info //
	/*
	strncpy(INFO.name, "INFOMATION\0", sizeof(INFO.name));
	strncpy(INFO.model_name, "XU\0", sizeof(INFO.model_name));
	strncpy(INFO.firmware_version, "1402", sizeof(INFO.firmware_version));
	strncpy(INFO.verifier, "6c3d0216f7fd482cdac2aa054af61065", sizeof(INFO.verifier));
	printf(":: name-%s, model-%s, ver/hash-%s\n", INFO.name, INFO.model_name, INFO.firmware_version);
	*/
	
	INFO = create_node("INFOMATION\0", "XU\0", "1402", "6c3d0216f7fd482cdac2aa054af61065");
	//printf(":: name-%s, model-%s, ver/hash-%s\n", INFO->name, INFO->model_name, INFO->firmware_version);
	
	// create nodes //
	for(int i=0; i<MAX_NODE; i++) {
		
		sprintf(tmp, "%d", i);
		DEVICE_info[i] = create_node(tmp, "XU\0", "1402", "6c3d0216f7fd482cdac2aa054af61065");
		//strncpy(DEVICE_info[i].name, tmp, sizeof(DEVICE_info[i].name));
	}
		
	//printf(":: name-%s, model-%s, ver/hash-%s\n", DEVICE_info[0]->name, DEVICE_info[0]->model_name, DEVICE_info[0]->firmware_version);
	//printf(":: name-%s, model-%s, ver/hash-%s\n", DEVICE_info[1]->name, DEVICE_info[1]->model_name, DEVICE_info[1]->firmware_version);

	//////////////////////////////////////
	int thread_id, status;
	pthread_t p_thread[MAX_NODE];
	//int tmp_max_node = 2;
	//pthread_t p_thread[tmp_max_node];
	for(int i=0; i<MAX_NODE; i++) {
		//sleep(1);
		thread_id = pthread_create(&p_thread[i], NULL, t_function, (void *)DEVICE_info[i]);
		if(i != VICTIM_NODE) {
			select_attacker(DEVICE_info[i]);
		}
		//printf("::: Create Thread %d, name is %s \n", i, DEVICE_info[i]->name);
		
	}
	printf("::: create %d threads \n", MAX_NODE-1);
	
	if (thread_id < 0) {
        perror("thread create error : ");
        exit(0);
    }
	printf("::: VICTIM is %d\n", VICTIM_NODE);

	///////////////////////////////////////
	for(int i=0; i<MAX_NODE; i++) {
		pthread_join(p_thread[i], (void **)&status);
		//printf("::: kill Thread %d \n", i);
	}
		
	//printf("::: request result = %d \n", request_check(DEVICE_info[0], DEVICE_info[1]));
		
	//////////////////////////////////////////////////////////////////
	/*
	int thread_id, status;
	
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

	verify_firmware(DEVICE_info[MAX_NODE]);
	print_Blockchain();
	remove_blockchain();
	
	return 0;
}