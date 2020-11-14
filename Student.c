#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include "Student.h"
//compare function 
int compareById(void* oneS, void* twoS) {
	Student* one = *(Student**)oneS;
	Student* two = *(Student**)twoS;

	return one->id - two->id;
}
int compareStudentGradeDegree(void* oneS, void* twoS) {
	Student* one = *(Student**)oneS;
	Student* two = *(Student**)twoS;

	if (one->grade == two->grade)
		return one->type - two->type;
	else return one->grade - two->grade;
}

int compareStudentDegreeId(void* oneS, void* twoS) {
	Student* one = *(Student**)oneS;
	Student* two = *(Student**)twoS;

	if (one->type == two->type)
		return one->id - two->id;
	else return one->type - two->type;
}
void printStudent(Student* theStu) {
	char* deagree;
	if (theStu->type == 0)
		deagree = "first";
	else deagree = "second";
	printf("studentId: %d , deagree: %s , grade: %d\n", theStu->id, deagree, theStu->grade);
}
//compressed student to struct
void compressedStudent(Student* theStud, StudentCompressed* tmp) {

	memset(tmp, 0, sizeof(StudentCompressed));
	tmp->compId[0] = theStud->id & 0xFF;
	tmp->compId[1] = (theStud->id >> 8) & 0xFF;
	tmp->compId[2] = (theStud->id >> 16) & 0xFF;
	tmp->typeGrade = ((theStud->grade & 0x7F) << 1) | theStud->type;

}
//un compressed it 
void unCompressedStudent(Student* theStud, StudentCompressed* tmp) {

	theStud->type = tmp->typeGrade & 0x1;
	theStud->grade = (tmp->typeGrade >> 1);
	theStud->id = tmp->compId[2];
	theStud->id = (theStud->id << 8) | tmp->compId[1];
	theStud->id = (theStud->id << 8) | tmp->compId[0];
}

int createStudents(Student** Arr, int size,FILE* f, char* type) {
	
	if (!strcmp(type, "text")) {
		for (int i = 0; i < size; i++) {
			Arr[i] = (Student*)malloc(sizeof(Student));
			if (!fscanf(f, "%d %d %d", &Arr[i]->id, &Arr[i]->type, &Arr[i]->grade)) {return 0;}
		}

	}
	else {
		StudentCompressed* tmp;
		tmp = (StudentCompressed*)malloc(sizeof(StudentCompressed));
		for (int i = 0; i < size; i++) {
			memset(tmp, 0, sizeof(StudentCompressed));
			if (!fread(tmp, sizeof(StudentCompressed), 1, f)) { return 0; }
			Arr[i] = (Student*)malloc(sizeof(Student));
			memset(Arr[i], 0, sizeof(Student));
			 unCompressedStudent(Arr[i], tmp);
		}
		
	
	}
	return 1;
}

