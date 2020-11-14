#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "School.h"

void searchStudentInSchool(School* theSchool, int id)
{
	sortEachClassInSchool(theSchool, compareById);
	Student** found;
	Student* tmp = (Student*)malloc(sizeof(Student));
	tmp->id = id;
	int class;
	for (int i = 0; i < theSchool->classCount* theSchool->countInClass; i+=7) {
		found = bsearch(&tmp, theSchool->studentArr+i,  theSchool->countInClass, sizeof(Student*), compareById);
		
		if (found!=NULL) {
			class = ((i%7) + 1);
			printf("student found in class %d\n",class);
			printStudent(*found);
			return;
		}
	}
	free(tmp);
	 printf("student not found");
}


void sortEachClassInSchool(School* theSchool, int(*compare)(void*, void*)) {
	for (int i = 0; i < (theSchool->classCount * theSchool->countInClass); i += 7)
		qsort(theSchool->studentArr + i, 7, sizeof(Student*), compare);
}

void showSchool(School* theSchool) {
	for (int i = 0; i < theSchool->classCount; i++) {
		printf("class number %d\n", (i + 1));
		for (int j = 0; j < theSchool->countInClass; j++) {
			printStudent(*(theSchool->studentArr+((theSchool->countInClass *i)+j)));

		}
	}
 }
int createCounts(School* theSchool, FILE* f, eFileType type) {
	if (type == text) {
		if (!fscanf(f, "%d %d", &theSchool->classCount, &theSchool->countInClass)) { return 0; }
	}
	else {
		if (!fread(&theSchool->classCount, sizeof(int), 1, f)) { return 0; }
		if (!fread(&theSchool->countInClass, sizeof(int), 1, f)) { return 0; }
	}
	return 1;
}

void saveSchoolToBinaryFile(char* fileName,School* theSchool) {
	FILE* f = fopen(fileName, "wb");
	if (!f) { return 0; }
	StudentCompressed** comArr;
	comArr = (StudentCompressed**)malloc(sizeof(StudentCompressed*));
	Student* theStu;
	if (!fwrite(&theSchool->classCount, sizeof(int), 1, f)) { return 0; }
	if (!fwrite(&theSchool->countInClass, sizeof(int), 1, f)) { return 0; }
	for (int i = 0; i < theSchool->classCount * theSchool->countInClass; i++) {
		comArr[i] = (StudentCompressed*)malloc(sizeof(StudentCompressed));
		theStu = theSchool->studentArr[i];
		compressedStudent(theStu, comArr[i]);
		if (!fwrite(comArr[i], sizeof(StudentCompressed), 1, f)) { return 0; }
	}
	
	
	
	fclose(f);


}
int createSchoolFromFile(char* fileName, School* theSchool, eFileType type) {
	FILE* f;
	if (type == text)
		f = fopen(fileName, "r");
	else f = fopen(fileName, "rb");
	if (!f) { printf("Failed to open the file "); return 0; }
	if (!createCounts(theSchool, f, type)) {return 0;}
	int size = (theSchool->classCount * theSchool->countInClass);
	theSchool->studentArr = (Student**)malloc(sizeof(Student*) * size);
	if (!theSchool->studentArr) { return 0; }
	if (type==text)
		 createStudents(theSchool->studentArr, size, f,"text");
	else  createStudents(theSchool->studentArr, size, f,"binary");
	return (!fclose(f));
}