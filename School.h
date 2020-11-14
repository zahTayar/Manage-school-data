#pragma once

#include "Student.h"

typedef enum { text, binary } eFileType;    // to understand in which form to work 


typedef struct {
	int	classCount;
	int countInClass;
	Student** studentArr;
} School;

int createSchoolFromFile(char* fileName, School* theSchool, eFileType type);
int creatCounts(School* theSchool, FILE* f, eFileType type);

void sortEachClassInSchool(School* theSchool, int(*compare)(void*, void*));
int		compareStudentById(const void* s1, const void* s2);
