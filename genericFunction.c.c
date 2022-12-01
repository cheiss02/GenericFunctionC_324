#include<stdio.h>
#include<string.h>
#include<stdbool.h>
#define MAX_STRING 40

typedef struct {
	char name[MAX_STRING];
	int age;
}Person;

void change(void *a, void *b, int width){
    void *t;
    t = malloc(width);
    memcpy(t,a,width);
    memcpy(a,b,width);
    memcpy(b,t,width);
}

void compare_numbers(void* a, void* b,int i, int j, bool reverse) {
	float *aa=(float*)a;
	float *bb=(float*)b;
	
	bool state= reverse? aa[i]<bb[j]:aa[i]>bb[j];
	if(state) change(&aa[i],&bb[j],sizeof(aa[i]));
}

void compare_people(void* a, void* b,int i, int j,bool reverse){
	Person *p1=(Person*)a;
	Person *p2=(Person*)b;

	bool state= reverse==false?p1[i].name[0]>p2[j].name[0] : (p1[i].age>p2[j].age? false:(p1[i].age==p2[j].age?p1[i].name[0]>p2[j].name[0] :true));
	if(state) change(&p1[i],&p2[j],sizeof(p1[i]));	
}

void sortF(void *_arr, int size, void (*funcion_compare)(void*, void*,int, int, bool),bool reverse) {
	int i,j;

	for (i = 0; i < size-1; i++) {
		for(j=i+1; j<size; j++){
			funcion_compare(_arr, _arr,i,j,reverse);
		}
	}
}

int main(){
	int i=0;
	int tNumbers=12;
	int tPeople=17;
	float num[]={645.41f, 37.59f, 76.41f, 5.31f, -34.23f, 1.11f, 1.10f, 23.46f, 635.47f, -876.32f, 467.83f, 62.25f};
	Person people[]={{"Hal", 20},{"Susann",31},{"Dwight",19},{"Kassandra",21},{"Lawrence",25},{"Cindy",22},{"Cory",27},
	{"Mac",19},{"Romana",27},{"Doretha",32},{"Danna",20},{"Zara",23},{"Rosalyn",26},{"Risa",24},{"Benny",28},{"Juan",33},{"Natalie",25}};
	
	
	printf("Order numbers in ascending order by the value\n");
	sortF(num, tNumbers,compare_numbers,false);
	for(i=0; i<tNumbers; i++){
		printf("%.2f ",num[i]);
	}
	
	printf("\n\nOrder people in alphabetical order (lexicographically) by name\n");
	sortF(people, tPeople,compare_people,false);
	for(i=0; i<tPeople; i++){
		printf("(%s,%d) ",people[i].name, people[i].age);
	}
	
	printf("\n\nOrder people in descendent order by age, where a person with the same age should be order in alphabetical order (lexicographically)\n");
	sortF(people, tPeople,compare_people,true);
	for(i=0; i<tPeople; i++){
		printf("(%s,%d) ",people[i].name, people[i].age);
	}

	return 0;
}
