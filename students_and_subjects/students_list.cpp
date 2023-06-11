#include "students_list.h"

students_list::students_list()
{
	_download_from_file();
}

void students_list::show_list()
{
	const size_t count = 119;
	print_symbol('=', count);
	std::cout << std::endl;

	size_t _width = 9;

	std::wcout << "|№" << " |  Фамилия  |    " << std::setw(_width) << "Имя    |   " << std::setw(_width) << "Отчество   |  " << std::setw(_width)
		<< "Группа  |  " << std::setw(_width) << "Средний балл  | " << std::setw(_width) << "Англ. |  " << std::setw(_width)
		<< "Матем. |  " << std::setw(_width) << "Програм. |  " << std::setw(_width) << "Физ. |  " << std::setw(_width)
		<< "БД   |  " << std::endl;

	print_symbol('=', count);
	std::cout << std::endl;
	size_t index = 0;

	for (const auto& it : _students)
	{
		std::wcout << '|' << index + 1;
		print_symbol(' ', 2 - std::to_string(index).size());
		std::wcout << '|' << it.get_family_name();
		print_symbol(' ', 11 - it.get_family_name().size());
		std::wcout << '|' << it.get_name();
		print_symbol(' ', 11 - it.get_name().size());
		std::wcout << '|' << it.get_surname();
		print_symbol(' ', 14 - it.get_surname().size());
		std::wcout << '|' << it.get_group_name();
		print_symbol(' ', 10 - it.get_group_name().size());
		std::wcout << "|      " << it.get_average_GPA() << "           " << it.is_English() << "        "
			<< it.is_Math() << "          " << it.is_Programming() << "          " << it.is_Physical()
			<< "         " << it.is_DataBases() << "  |" << std::endl;
		
		print_symbol('-', count);
		std::cout << std::endl;

		++index;
	}
}

void students_list::sort_by_family_name()
{
	std::sort(_students.begin(), _students.end(), [](const student& stud_1, const student& stud_2)
		{ return stud_1.get_family_name() < stud_2.get_family_name(); });
}

void students_list::sort_by_average_GPA()
{
	std::sort(_students.begin(), _students.end(), [](const student& stud_1, const student& stud_2)
		{ return stud_1.get_average_GPA() > stud_2.get_average_GPA(); });
}

void students_list::sort_by_group_name()
{
	std::sort(_students.begin(), _students.end(), [](const student& stud_1, const student& stud_2)
		{ return stud_1.get_group_name() > stud_2.get_group_name(); });
}

bool students_list::change_students_family_name(const student& stud, const std::wstring& new_fn)
{
	for (std::vector<student>::iterator it = _students.begin(); it != _students.end(); ++it)
	{
		if (*it == stud)
		{
			it->set_family_name(new_fn);
			return true;
		}
	}
	return false;
}

bool students_list::change_students_name(const student& stud, const std::wstring& new_name)
{
	for (std::vector<student>::iterator it = _students.begin(); it != _students.end(); ++it)
	{
		if (*it == stud)
		{
			it->set_name(new_name);
			return true;
		}
	}
	return false;
}

bool students_list::change_students_surname(const student& stud, const std::wstring& new_sn)
{
	for (std::vector<student>::iterator it = _students.begin(); it != _students.end(); ++it)
	{
		if (*it == stud)
		{
			it->set_surname(new_sn);
			return true;
		}
	}
	return false;
}

bool students_list::change_students_group_name(const student& stud, const std::wstring& new_gn)
{
	for (std::vector<student>::iterator it = _students.begin(); it != _students.end(); ++it)
	{
		if (*it == stud)
		{
			it->set_group_name(new_gn);
			return true;
		}
	}
	return false;
}

bool students_list::change_students_average_GPA(const student& stud, const double new_GPA)
{
	for (std::vector<student>::iterator it = _students.begin(); it != _students.end(); ++it)
	{
		if (*it == stud)
		{
			it->set_average_GPA(new_GPA);
			return true;
		}
	}
	return false;
}

bool students_list::change_students_is_english(const student& stud, const bool new_eng)
{
	for (std::vector<student>::iterator it = _students.begin(); it != _students.end(); ++it)
	{
		if (*it == stud)
		{
			it->set_English(new_eng);
			return true;
		}
	}
	return false;
}

bool students_list::change_students_is_math(const student& stud, const bool new_math)
{
	for (std::vector<student>::iterator it = _students.begin(); it != _students.end(); ++it)
	{
		if (*it == stud)
		{
			it->set_Math(new_math);
			return true;
		}
	}
	return false;
}

bool students_list::change_students_is_programming(const student& stud, const bool new_prog)
{
	for (std::vector<student>::iterator it = _students.begin(); it != _students.end(); ++it)
	{
		if (*it == stud)
		{
			it->set_Programming(new_prog);
			return true;
		}
	}
	return false;;
}

bool students_list::change_students_is_physic(const student& stud, const bool new_phys)
{
	for (std::vector<student>::iterator it = _students.begin(); it != _students.end(); ++it)
	{
		if (*it == stud)
		{
			it->set_Physical(new_phys);
			return true;
		}
	}
	return false;
}

bool students_list::change_students_is_databases(const student& stud, const bool new_db)
{
	for (std::vector<student>::iterator it = _students.begin(); it != _students.end(); ++it)
	{
		if (*it == stud)
		{
			it->set_DataBases(new_db);
			return true;
		}
	}
	return false;
}

student students_list::return_copy_of_student(const student& stud)
{
	for (auto& it : _students)
	{
		if (it == stud)
		{
			student copy(it);
			return copy;
		}
	}

	return student();
}

size_t students_list::get_count_of_students() const
{
	return _students.size();
}

const student& students_list::operator[](size_t index) const
{
	return _students[index];
}

void students_list::add_new_student(student&& stud)
{
	_students.push_back(stud);
}

bool students_list::remove_the_student(const student& stud)
{
	for (std::vector<student>::iterator it = _students.begin(); it != _students.end(); ++it)
	{
		if (*it == stud)
		{
			_students.erase(it);
			return true;
		}
	}
	return false;
}

students_list::~students_list()
{
	_upload_to_file();
}

void students_list::print_symbol(char symb, int count)
{
	for (int i{ 0 }; i < count; ++i)
		std::cout << symb;
}

void students_list::_download_from_file()
{
	std::wifstream students_info_file(_FILENAME);
	if (!students_info_file.is_open())
	{
		std::string exception_message = "Your file" + _FILENAME + "has not been opened";
		throw std::exception(exception_message.c_str());
	}

	student::students_buffer buffer;

	while (students_info_file >> buffer._family_name >> buffer._name >> buffer._surname >> buffer._group_name
		>> buffer._average_GPA >> buffer._is_English >> buffer._is_Math >> buffer._is_Programming >> buffer._is_Physical >> buffer._is_DataBases)
	{
		_students.push_back(std::move(buffer));
	}
}

void students_list::_upload_to_file()
{
	std::wofstream students_info_file("new.txt");
	if (!students_info_file.is_open())
	{
		std::string exception_message = "Your file" + _FILENAME + "has not been opened";
		throw std::exception(exception_message.c_str());
	}

	for (auto& it : _students)
		students_info_file << it;

	students_info_file.close();
	std::remove(_FILENAME.c_str());			
	std::rename("new.txt", _FILENAME.c_str());
}
