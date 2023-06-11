#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

class student
{
public:
	struct students_buffer
	{
		std::wstring _family_name = L" ";
		std::wstring _name = L" ";
		std::wstring _surname = L" ";

		std::wstring _group_name = L" ";

		double _average_GPA = 0.0;

		bool _is_English = false;
		bool _is_Math = false;
		bool _is_Programming = false;
		bool _is_Physical = false;
		bool _is_DataBases = false;
	};

public:
	student(std::wstring fn = L" ", std::wstring name = L" ", std::wstring sn = L" ",
		std::wstring gn = L" ", double aGPA = 0.0, bool eng = false, bool math = false, bool prog = false, bool phys = false, bool db = false);
	student(students_buffer&&);

public:
	void set_family_name(std::wstring);
	void set_name(std::wstring);
	void set_surname(std::wstring);
	void set_group_name(std::wstring);

	void set_average_GPA(double);

	void set_English(bool);
	void set_Math(bool);
	void set_Programming(bool);
	void set_Physical(bool);
	void set_DataBases(bool);

public:
	std::wstring get_family_name() const;
	std::wstring get_name() const;
	std::wstring get_surname() const;
	std::wstring get_group_name() const;

	double get_average_GPA() const;

	bool is_English() const;
	bool is_Math() const;
	bool is_Programming() const;
	bool is_Physical() const;
	bool is_DataBases() const;

	bool operator==(const student&) const;

	friend std::wostream& operator<<(std::wostream&, const student&);

private:
	std::wstring _family_name;
	std::wstring _name;
	std::wstring _surname;

	std::wstring _group_name;

	double _average_GPA;

	bool _is_English;
	bool _is_Math;
	bool _is_Programming;
	bool _is_Physical;
	bool _is_DataBases;
};

