#pragma once

#include <algorithm>

#include "subject.h"
#include "students_list.h"

class subjects_list
{
public:
	subjects_list(const students_list&);

	bool add_new_student(const student&);
	bool remove_the_student(const student&);

	bool change_students_family_name(const student&, const std::wstring&);
	bool change_students_name(const student&, const std::wstring&);
	bool change_students_surname(const student&, const std::wstring&);
	bool change_students_group_name(const student&, const std::wstring&);

	bool change_students_average_GPA(const student&, const double);

	bool change_students_is_english(const student&, const bool);
	bool change_students_is_math(const student&, const bool);
	bool change_students_is_programming(const student&, const bool);
	bool change_students_is_physic(const student&, const bool);
	bool change_students_is_databases(const student&, const bool);

	void show() const;
	void personal_task_to_show_after_sorting();

private:
#define ENGLISH     0
#define MATH        1
#define PROGRAMMING 2
#define PHYSICAL    3
#define DATABASES   4

	const size_t count_of_subjects = 5;
	std::vector<subject> _subjects;

};

