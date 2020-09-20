#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef enum { false, true } bool;

bool addContact(char* first, char* last, char* phone, char* address); 
void printAllContact();
void freeMem();

struct Contact {
	char first[20];
	char last[20];
	char phone[20];
	char address[100];
	struct Contact* next;
	struct Contact* prev;
};

struct Contact* head;
struct Contact* tail;
struct Contact* searchContactByPhone(char* phone);
void printOneContact(struct Contact* contact);
void initHeadAndTail();
void removeContactByPhone();

int main() {
	initHeadAndTail();
	char* first = "first1";
	char* last = "last";
	char* phone = "phone";
	char* address = "address";
	char* first2 = "first2";
	char* last2 = "last2";
	char* phone2 = "phone2";
	char* address2 = "address2";

	addContact(first, last, phone, address);
	addContact(first2, last2, phone2, address2);
	removeContactByPhone(phone);
	removeContactByPhone(phone2);
	//printOneContact(searchContactByPhone(phone2));
	printAllContact();
	freeMem();
	return 0;
}

void initHeadAndTail() {
	struct Contact* tempHead = malloc(sizeof(struct Contact));
	struct Contact* tempTail = malloc(sizeof(struct Contact));
	tempHead->next = tempTail;
	tempTail->prev = tempHead;
	head = tempHead;
	tail = tempTail;
}

bool addContact(char* first, char* last, char* phone, char* address) {
	struct Contact* newContact = malloc(sizeof(struct Contact));
	strcpy((*newContact).first, first);
	strcpy((*newContact).last, last);
	strcpy((*newContact).phone, phone);
	strcpy((*newContact).address, address);
	
	struct Contact* lastContact = tail->prev;

	lastContact->next = newContact;
	newContact->prev = lastContact;
	newContact->next = tail;
	tail->prev = newContact;

	return true;
}


void printAllContact() {
	struct Contact* cursor = head->next;
	while (cursor != tail) {
		printOneContact(cursor);
		cursor = (*cursor).next;
	}
}

void freeMem() {
	struct Contact* cursor = head;
	while (cursor != NULL) {
		struct Contact* temp = (*cursor).next;
		free(cursor);
		cursor = temp;
	}
}

struct Contact* searchContactByPhone(char* phone) {
	struct Contact* cursor = head->next;
	while (cursor != tail) {
		if (strcmp((*cursor).phone, phone) == 0) {
			return cursor;
		}
		cursor = (*cursor).next;
	}
	return NULL;
}

void printOneContact(struct Contact* contact) {
	printf("%s\n", (*contact).first);
	printf("%s\n", (*contact).last);
	printf("%s\n", (*contact).phone);
	printf("%s\n", (*contact).address);
	printf("%s\n", "================");
}

void removeContactByPhone(char* phone) {
	struct Contact* res = searchContactByPhone(phone);
	if (res != NULL) {
		struct Contact* prevContact = res->prev;
		struct Contact* nextContact = res->next;
		prevContact->next = nextContact;
		nextContact->prev = prevContact;
		free(res);
	}
}
/*
bool updateContact(struct Contact* contact) {

}


struct* Contact searchContactByFirst(char* first) {
}

struct* Contact searchContactByLast(char* last) {
}

struct* Contact searchContactByPhone(char* phone) {
}

struct* Contact searchContactByAddress(char* address) {
}

bool removeContact(struct Contact* contact) {
}
*/
