#include "header.h"

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
	struct node INFO;
	strncpy(INFO.name, "INFOMATION\0", sizeof(INFO.name));
	strncpy(INFO.model_name, "XU\0", sizeof(INFO.model_name));
	strncpy(INFO.firmware_version, "1402", sizeof(INFO.firmware_version));
	strncpy(INFO.verifier, "6c3d0216f7fd482cdac2aa054af61065", sizeof(INFO.verifier));
	printf(":: name-%s, model-%s, ver/hash-%s\n", INFO.name, INFO.model_name, INFO.firmware_version);
	
	
	// create nodes //
	struct node DEVICE_info[MAX_NODE];
	for(int i=0; i<MAX_NODE; i++) {
		memcpy(&DEVICE[i], &INFO, sizeof(struct node));
		sprintf(tmp, "%d", i);
		strncpy(DEVICE[i].name, tmp, sizeof(DEVICE[i].name));
	}
	int thread_id;
	pthread_t p_thread[MAX_NODE];
	thread_id = pthread_create(&p_thread[0], NULL, t_function, (void *)&a);
    if (thr_id < 0)
    {
        perror("thread create error : ");
        exit(0);
    }
	//
	printf(":: name-%s, model-%s, ver/hash-%s\n", DEVICE[0].name, DEVICE[0].model_name, DEVICE[0].firmware_version);
	printf(":: name-%s, model-%s, ver/hash-%s\n", DEVICE[1].name, DEVICE[1].model_name, DEVICE[1].firmware_version);
	
	
	// delete list
	while (!SLIST_EMPTY(&head)) { 
		printf(": Delete List");
    	GENESIS = SLIST_FIRST(&head);
        SLIST_REMOVE_HEAD(&head, blocks);
        free(GENESIS);
    }
	// end thread
	pthread_join(p_thread[0], (void **)&status);
    pthread_join(p_thread[1], (void **)&status);

	return 0;
}