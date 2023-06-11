#pragma once

#include <iostream>
#include <vector>

#include "student.h"

class subject
{
public:
	subject(const std::wstring&);

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

	bool is_exist(const student&) const;

	size_t get_count_of_students() const;
	std::wstring get_subject_name() const;

	void show() const;

private:
	std::wstring _subject_name;
	std::vector<student> _students;


	std::vector<student>::iterator find_min_GPA_student();

	void print_symbol(char, int) const;
};

