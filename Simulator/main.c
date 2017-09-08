#include "header.h"

struct node INFO;

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

int main() {
	char tmp[10] = {0,};
	printf("Start test\n");
	printf(": creating GENESIS Block \n");
	
	// creating genesis block //
	SLIST_HEAD(slisthead, block) head = SLIST_HEAD_INITIALIZER(head);
	SLIST_INIT(&head);
	GENESIS = malloc(sizeof(struct block));
	GENESIS->version = 0.1;
	GENESIS->prev_hash[0] = '\0';
	GENESIS->merkle_root[0] = 0;
	GENESIS->verification_count = 0;
	GENESIS->merkle_tree[0] = '\0';
	GENESIS->verification_log[0] = '\0';
	GENESIS->model[0] = '\0';
	GENESIS->firmware_version = 0;
	GENESIS->verifier[0] = '\0';
	printf(": Genesis Block is ready \n");

	// create node info //
	
	strncpy(INFO.name, "INFOMATION\0", sizeof(INFO.name));
	strncpy(INFO.model_name, "XU\0", sizeof(INFO.model_name));
	strncpy(INFO.firmware_version, "1402", sizeof(INFO.firmware_version));
	strncpy(INFO.verifier, "6c3d0216f7fd482cdac2aa054af61065", sizeof(INFO.verifier));
	printf(":: name-%s, model-%s, ver/hash-%s\n", INFO.name, INFO.model_name, INFO.firmware_version);
	
	// create nodes //
	struct node DEVICE_info[MAX_NODE];
	for(int i=0; i<MAX_NODE; i++) {
		memcpy(&DEVICE_info[i], &INFO, sizeof(struct node));
		sprintf(tmp, "%d", i);
		strncpy(DEVICE_info[i].name, tmp, sizeof(DEVICE_info[i].name));
	}
	/*
	int thread_id;
	pthread_t p_thread[MAX_NODE];
	thread_id = pthread_create(&p_thread[0], NULL, t_function, (void *)&a);
    if (thr_id < 0)
    {
        perror("thread create error : ");
        exit(0);
    }
	*/
	//
	printf(":: name-%s, model-%s, ver/hash-%s\n", DEVICE_info[0].name, DEVICE_info[0].model_name, DEVICE_info[0].firmware_version);
	printf(":: name-%s, model-%s, ver/hash-%s\n", DEVICE_info[1].name, DEVICE_info[1].model_name, DEVICE_info[1].firmware_version);

	self_check(DEVICE_info[0]);
	request_check(DEVICE_info[0], DEVICE_info[1]);
	
	// delete list
	while (!SLIST_EMPTY(&head)) { 
		printf(": Delete List");
    	GENESIS = SLIST_FIRST(&head);
        SLIST_REMOVE_HEAD(&head, blocks);
        free(GENESIS);
    }
	// end thread
	//pthread_join(p_thread[0], (void **)&status);
    //pthread_join(p_thread[1], (void **)&status);

	return 0;
}