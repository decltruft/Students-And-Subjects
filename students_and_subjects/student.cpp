#include "student.h"

student::student(std::wstring fn, std::wstring name, std::wstring sn, 
	std::wstring gn, double aGPA, bool eng, bool math, bool prog, bool phys, bool db) :
	_family_name(fn), _name(name), _surname(sn), _group_name(gn), _average_GPA(aGPA), _is_English(eng), _is_Math(math), 
	_is_Programming(prog), _is_Physical(phys), _is_DataBases(db)
{

}

student::student(students_buffer&& buffer) :
	_family_name(buffer._family_name), _name(buffer._name), _surname(buffer._surname), _group_name(buffer._group_name), 
	_average_GPA(buffer._average_GPA), _is_English(buffer._is_English), _is_Math(buffer._is_Math),
	_is_Programming(buffer._is_Programming), _is_Physical(buffer._is_Physical), _is_DataBases(buffer._is_DataBases)
{

}

void student::set_family_name(std::wstring fn)
{
	_family_name = fn;
}

void student::set_name(std::wstring name)
{
	_name = name;
}

void student::set_surname(std::wstring sn)
{
	_surname = sn;
}

void student::set_group_name(std::wstring gn)
{
	_group_name = gn;
}

void student::set_average_GPA(double aGPA)
{
	_average_GPA = aGPA;
}

void student::set_English(bool eng)
{
	_is_English = eng;
}

void student::set_Math(bool math)
{
	_is_Math = math;
}

void student::set_Programming(bool prog)
{
	_is_Programming = prog;
}

void student::set_Physical(bool phys)
{
	_is_Physical = phys;
}

void student::set_DataBases(bool db)
{
	_is_DataBases = db;
}

std::wstring student::get_family_name() const
{
	return _family_name;
}

std::wstring student::get_name() const
{
	return _name;
}

std::wstring student::get_surname() const
{
	return _surname;
}

std::wstring student::get_group_name() const
{
	return _group_name;
}

double student::get_average_GPA() const
{
	return _average_GPA;
}

bool student::is_English() const
{
	return _is_English;
}

bool student::is_Math() const
{
	return _is_Math;
}

bool student::is_Programming() const
{
	return _is_Programming;
}

bool student::is_Physical() const
{
	return _is_Physical;
}

bool student::is_DataBases() const
{
	return _is_DataBases;
}

bool student::operator==(const student& stud) const
{
	return ((stud._family_name == _family_name) && (stud._name == _name) && (stud._surname == _surname));
}

std::wostream& operator<<(std::wostream& ofs, const student& stud)
{
	ofs << stud.get_family_name() << ' ' << stud.get_name() << ' ' << stud.get_surname() << ' ' << stud.get_group_name() << ' '
		<< stud.get_average_GPA() << ' ' << stud.is_English() << ' ' << stud.is_Math() << ' ' << stud.is_Programming() << ' ' 
		<< stud.is_Physical() << ' ' << stud.is_DataBases() << '\n';
	return ofs;
}
