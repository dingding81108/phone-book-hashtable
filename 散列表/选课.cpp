#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define MAX_COURSES 100
#define MAX_STUDENTS 100

typedef struct 
{ 
	int courseId;
    char courseName[50];
    char courseType[10];
    int totalHours;
    int lectureHours; 
    int labHours;
    int credits;
    int semester;
} Course;

typedef struct { int studentId; char studentName[50];
int totalCredits;
Course selectedCourses[MAX_COURSES]; 
int numSelectedCourses;
} Student;
//int loadCoursesFromFile(Course courses[], int* numCourses, const char* filename);

//int saveCoursesToFile(Course courses[], int numCourses, const char* filename);
void inputCourse(Course* courses, int* numCourses)
{ if (*numCourses < MAX_COURSES)
{
	Course newCourse; printf("请输入课程编号：");
	scanf("%d", &newCourse.courseId);
	printf("请输入课程名称：");
	scanf("%s", newCourse.courseName);
	printf("请输入课程性质（考试课/考查课）：");
	scanf("%s", newCourse.courseType);
	printf("请输入总学时：");
	scanf("%d", &newCourse.totalHours);
	printf("请输入授课学时：");
	scanf("%d", &newCourse.lectureHours);
	printf("请输入实验或上机学时：");
	scanf("%d", &newCourse.labHours);
	printf("请输入学分："); 
	scanf("%d", &newCourse.credits);
	printf("请输入开课学期：");
	scanf("%d", &newCourse.semester);
	courses[*numCourses] = newCourse; 
	(*numCourses)++; printf("课程信息录入成功！\n");
}
else 
{ 
	printf("课程数量已达上限，无法录入更多课程。\n"); 
}
}

void displayCourses(Course* courses, int numCourses)
{ 
	printf("课程列表：\n"); 
	for (int i = 0;
		i < numCourses; i++)
	{
		printf("课程编号：%d\n", courses[i].courseId); 
		printf("课程名称：%s\n", courses[i].courseName); 
		printf("课程性质：%s\n", courses[i].courseType);
		printf("总学时：%d\n", courses[i].totalHours); 
		printf("授课学时：%d\n", courses[i].lectureHours); 
		printf("实验或上机学时：%d\n", courses[i].labHours); 
		printf("学分：%d\n", courses[i].credits);
		printf("开课学期：%d\n", courses[i].semester);
		printf("----------------------\n"); } }

void searchCourseByCredit(Course* courses, int numCourses, int credit)
{ 
	printf("按学分查询结果：\n");
	for (int i = 0; i < numCourses; i++) 
	{ 
		if (courses[i].credits == credit) 
		{ 
			printf("课程编号：%d\n", courses[i].courseId); 
			printf("课程名称：%s\n", courses[i].courseName);
			printf("课程性质：%s\n", courses[i].courseType); 
			printf("总学时：%d\n", courses[i].totalHours);
			printf("授课学时：%d\n", courses[i].lectureHours); 
			printf("实验或上机学时：%d\n", courses[i].labHours); 
			printf("学分：%d\n", courses[i].credits);
			printf("开课学期：%d\n", courses[i].semester);
			printf("----------------------\n"); }
	} 
}

void searchCourseBySemester(Course* courses, int numCourses, int semester)
{
	printf("按学期查询结果：\n");
	for (int i = 0; i < numCourses; i++)
	{ 
		if (courses[i].semester == semester)
		{ 
			printf("课程编号：%d\n", courses[i].courseId);
			printf("课程名称：%s\n", courses[i].courseName);
			printf("课程性质：%s\n", courses[i].courseType); 
			printf("总学时：%d\n", courses[i].totalHours);
			printf("授课学时：%d\n", courses[i].lectureHours);
			printf("实验或上机学时：%d\n", courses[i].labHours); 
			printf("学分：%d\n", courses[i].credits); 
			printf("开课学期：%d\n", courses[i].semester);
			printf("----------------------\n");} 
	} 
}

void searchCourseByType(Course* courses, int numCourses, char* type) 
{
	printf("按课程性质查询结果：\n");
	for (int i = 0; i < numCourses; i++) 
	{ 
		if (strcmp(courses[i].courseType, type) == 0)
		{ 
			printf("课程编号：%d\n", courses[i].courseId);
			printf("课程名称：%s\n", courses[i].courseName); 
			printf("课程性质：%s\n", courses[i].courseType);
			printf("总学时：%d\n", courses[i].totalHours); 
			printf("授课学时：%d\n", courses[i].lectureHours);
			printf("实验或上机学时：%d\n", courses[i].labHours);
			printf("学分：%d\n", courses[i].credits);
			printf("开课学期：%d\n", courses[i].semester);
			printf("----------------------\n"); }
	} 
}

void selectCourse(Student* student, Course* courses, int numCourses) 
{
	if (student->numSelectedCourses < MAX_COURSES)
	{ 
		int courseId; printf("请输入要选修的课程编号：");
		scanf("%d", &courseId);
		for (int i = 0; i < numCourses; i++) 
		{ 
			if (courses[i].courseId == courseId) 
			{ 
				student->selectedCourses[student->numSelectedCourses] = courses[i]; 
				student->numSelectedCourses++; 
				student->totalCredits += courses[i].credits; printf("选课成功！\n"); return; }
		} printf("未找到该课程编号，请重新输入。\n");
	} else { printf("已选课程数量已达上限，无法选修更多课程。\n"); } }

void displaySelectedCourses(Student* student) { printf("已选课程列表：\n"); 
for (int i = 0; i < student->numSelectedCourses; i++)
{
	printf("课程编号：%d\n", student->selectedCourses[i].courseId); 
	printf("课程名称：%s\n", student->selectedCourses[i].courseName);
	printf("课程性质：%s\n", student->selectedCourses[i].courseType);
	printf("总学时：%d\n", student->selectedCourses[i].totalHours); 
	printf("授课学时：%d\n", student->selectedCourses[i].lectureHours);
	printf("实验或上机学时：%d\n", student->selectedCourses[i].labHours);
	printf("学分：%d\n", student->selectedCourses[i].credits);
	printf("开课学期：%d\n", student->selectedCourses[i].semester);
	printf("----------------------\n"); } }

void searchStudentCourses(Student* students, int numStudents, int studentId) 
{ 
	for (int i = 0; i < numStudents; i++)
	{
		if (students[i].studentId == studentId)
		{ 
			displaySelectedCourses(&students[i]); return; } 
	}
	printf("未找到该学生的选课信息。\n"); }

// FILEPATH: \cloudide\workspace\C\main.c
int main() {
	Course courses[MAX_COURSES];
	int numCourses = 0;
	Student students[MAX_STUDENTS];
	int numStudents = 0;
	int choice;
	int studentIdCounter = 10001; // 假设学生ID从10001开始
	int loadCoursesFromFile;
	int saveCoursesToFile;
	// 从文件加载课程信息（如果文件存在）
	//loadCoursesFromFile(courses, &numCourses, "courses.txt"); //int loadCoursesFromFile(Course courses[], int* numCourses, const char* filename);

	//int saveCoursesToFile(Course courses[], int numCourses, const char* filename);

	while (1) {
		printf("\n学生选修课程系统\n");
		printf("1. 录入课程信息\n");
		printf("2. 浏览课程信息\n");
		printf("3. 查询课程信息\n");
		printf("4. 学生选课\n");
		printf("5. 查询学生选课信息\n");
		printf("6. 退出系统\n");
		printf("请选择操作：");
		scanf("%d", &choice);

		switch (choice) {
		case 1:
			inputCourse(courses, &numCourses);
			//saveCoursesToFile(courses, numCourses, "courses.txt");
			break;
		case 2:
			displayCourses(courses, numCourses);
			break;
		case 3: {
			int subChoice;
			int credit, semester;
			char type[11]; // 课程性质字符串最大长度为10，加上一个'\0'终止符

			printf("选择查询方式：\n");
			printf("1. 按学分查询\n");
			printf("2. 按学期查询\n");
			printf("3. 按课程性质查询\n");
			scanf("%d", &subChoice);

			if (subChoice == 1) {
				printf("请输入学分：");
				scanf("%d", &credit);
				searchCourseByCredit(courses, numCourses, credit);
			}
			else if (subChoice == 2) {
				printf("请输入学期：");
				scanf("%d", &semester);
				searchCourseBySemester(courses, numCourses, semester);
			}
			else if (subChoice == 3) {
				printf("请输入课程性质（考试课/考查课）：");
				scanf("%s", type);
				searchCourseByType(courses, numCourses, type);
			}
			break;
		}
		case 4: {
			if (numStudents < MAX_STUDENTS) {
				Student newStudent;
				newStudent.studentId = studentIdCounter++;
				printf("请输入学生姓名：");
				scanf("%s", newStudent.studentName);
				newStudent.totalCredits = 0;
				newStudent.numSelectedCourses = 0;
				students[numStudents] = newStudent;
				numStudents++;
				printf("请输入要选修的课程编号（按0结束选课）：");
				int courseId;
				while (scanf("%d", &courseId) && courseId != 0) {
					selectCourse(&students[numStudents - 1], courses, numCourses);
					// 检查总学分是否满足要求
					if (students[numStudents - 1].totalCredits < 60 || students[numStudents - 1].totalCredits > 70) {
						printf("选课后的总学分不在60到70之间，请重新选课。\n");
						// 这里可以添加逻辑来清除错误的选课，但为了简化，我们直接退出循环
						break;
					}
					printf("请输入下一个要选修的课程编号（或按0结束选课）：");
				}
			}
			else {
				printf("学生数量已达上限，无法添加更多学生。\n");
			}
			break;
		}
		case 5: {
			int studentId;
			printf("请输入学生ID：");
			scanf("%d", &studentId);
			searchStudentCourses(students, numStudents, studentId);
			break;
		}
		case 6:
			exit(0);
		default:
			printf("无效选择，请重新选择。\n");
		}
	}

	return 0;
}

