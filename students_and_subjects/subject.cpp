#include "subject.h"

subject::subject(const std::wstring& name = L"  ") : _subject_name(name)
{
}

bool subject::add_new_student(const student& stud)
{
	for (const auto& it : _students)
	{
		if (it == stud)
			return false;
	}

    if (_students.size() > 15)
    {
        auto min_GPA_student = find_min_GPA_student();

        if (stud.get_average_GPA() > min_GPA_student->get_average_GPA())
            _students.erase(min_GPA_student);
        else
            return false;
    }

    _students.push_back(stud);
    return true;
}

bool subject::remove_the_student(const student& stud)
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

bool subject::change_students_family_name(const student& stud, const std::wstring& new_fn)
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

bool subject::change_students_name(const student& stud, const std::wstring& new_name)
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

bool subject::change_students_surname(const student& stud, const std::wstring& new_sn)
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

bool subject::change_students_group_name(const student& stud, const std::wstring& new_gn)
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

bool subject::change_students_average_GPA(const student& stud, const double new_GPA)
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

bool subject::change_students_is_english(const student& stud, const bool new_eng)
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

bool subject::change_students_is_math(const student& stud, const bool new_math)
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

bool subject::change_students_is_programming(const student& stud, const bool new_prog)
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

bool subject::change_students_is_physic(const student& stud, const bool new_phys)
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

bool subject::change_students_is_databases(const student& stud, const bool new_db)
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

bool subject::is_exist(const student& stud) const
{
	for (const auto& it : _students)
	{
		if (it == stud)
			return true;
	}
	return false;
}

size_t subject::get_count_of_students() const
{
	return _students.size();
}

std::wstring subject::get_subject_name() const
{
	return _subject_name;
}

void subject::show() const
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

std::vector<student>::iterator subject::find_min_GPA_student()
{
    if (_students.empty())
        return _students.end();;

    std::vector<student>::iterator min_GPA_iterator = _students.begin();

    for (std::vector<student>::iterator it = _students.begin(); it != _students.end(); ++it)
    {
        if (it->get_average_GPA() < min_GPA_iterator->get_average_GPA())
            min_GPA_iterator = it;
    }

    return min_GPA_iterator;
}

void subject::print_symbol(char symb, int count) const
{
	for (int i{ 0 }; i < count; ++i)
		std::cout << symb;
}