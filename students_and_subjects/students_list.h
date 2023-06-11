#pragma once

#include <algorithm>
#include <vector>

#include "student.h"

class students_list
{
public:
	students_list();

public:
	void sort_by_family_name();
	void sort_by_average_GPA();
	void sort_by_group_name();

public:
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

public:
	void show_list();

	student return_copy_of_student(const student&);

	size_t get_count_of_students() const;
	const student& operator[](size_t) const;

	void add_new_student(student&&);
	bool remove_the_student(const student&);

	~students_list();

private:
	std::vector<student> _students;

	const std::string _FILENAME = "students_info.txt";

	void print_symbol(char, int);

	void _download_from_file();
	void _upload_to_file();
};

