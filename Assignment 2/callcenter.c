#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "queue.h"
#include "stack.h"

/*
 * This file is where you should implement a callcenter. Where user is given the option to recieve calls,
 anser calls, check the call queue and etc. This is done throguh the use of our implemented stack and queue codes
 fromt he previous sections.
 *
 * Name: Yaire Aguilar
 * Email:aguilary@oreongstate.edu
 */

 // Define your call struct here.
 
struct Call{
	int ID;
	char name[50];
	char reason[100];
};


void receive_call(struct queue* call_queue){
	struct Call* incoming_call = (struct Call*)malloc(sizeof(struct Call));
	//need to set the id of the incoming caller, and eventually +1 for those incoming later on
	int id_counter = 0;
	id_counter ++;
	incoming_call->ID = id_counter;



	//inputs
	printf("Enter the caller's name: ");
	scanf("%s", incoming_call->name);
	printf("Enter the caller's name: ");
	scanf("%s", incoming_call->reason);

	//adding it into the queue
	queue_enqueue(call_queue, incoming_call);
	printf("Call in queue now\n");
}

void answer_call(struct queue* call_queue, struct stack* answered_calls){
	if(queue_isempty(call_queue)){
		printf("No calls needed to answer");
	}else {
		struct Call* call = queue_dequeue(call_queue);
		stack_push(answered_calls, call);
        printf("The following call has been answered and added to the stack!\n");
        printf("Call ID: %d\n", call->ID);
        printf("Caller's name: %s\n", call->name);
        printf("Call reason: %s\n", call->reason);
	}
}


int main(int argc, char const *argv[]) {

	//making the gloval variables
	struct queue* call_queue = queue_create();
    struct stack* answered_calls = stack_create();

  int choice = 0;
  while (choice != 5){	//as long as the user doesn't want to quit
  	printf("1. Receive a new call\n");
    printf("2. Answer a call\n");
    printf("3. Current state of the stack - answered calls\n");
    printf("4. Current state of the queue - calls to be answered\n");
    printf("5. Quit\n");
    printf("Choose an option: ");
    scanf("%d", &choice);

	if (choice == 1){
		receive_call(call_queue);
		}
	else if (choice == 2){
		answer_call(call_queue, answered_calls);
	}
	else if (choice == 3){
		//display_stack();
		printf("3");
	}
	else if (choice == 4){
		//display_queue();
		printf("4");
	}
	else if (choice == 5){
		printf("Program will exit");
	} 
	else printf("Invalid. Try again");
  
  }

	return 0;
}
