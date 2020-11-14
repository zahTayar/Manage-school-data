#pragma once
                                                                                //which degree type 
typedef enum { first, second, eNofTypes } eDegreeType;

static const char* DegreeStr[eNofTypes];

typedef struct {
	int id;
	int	type;
	int grade;
}Student;                                     // regular student

typedef struct {
	unsigned char compId[3];              // binary form for student 
	unsigned char typeGrade;
}StudentCompressed;


int compareStudentDegreeId(void* oneS, void* twoS);
int compareStudentGradeDegree(void* oneS, void* twoS);
int compareById(void* oneS, void* twoS);
