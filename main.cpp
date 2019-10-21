#include <vector>
#include <map>
#include <iostream>
#include <iterator>
#include <utility>
#include <algorithm>
#include <ctime>

/*  Тестовое задание компании TrueConf:
 *  1. Заполнить случайными числами от 1 до 9 значения контейнеров vector[i] и map[i];
 *  2. Удалить случайное число элементов (не более 15) в каждом контейнере;
 *  3. После этого провести синхронизацию, чтобы в vector и map остались только 
 *     имеющиеся в обоих контейнерах элементы (дубликаты не удалять).   
 *  Комментарии:
 *	1.Вначале написал все отдельными функциями, под каждый контейнер, но было много дублируемого кода, решил использовать шаблоны.
 *	2.Возможно стоило отказаться от лямбда функции в функции синхронизации, но тут на вкус и цвет.
 *	3.Не использую auto, по крайней мере стараюсь, ибо часто это сильно ухудшает читаемость кода.Исключение range based.
 *	4.В шаблоне удаления, сделал проверку на передаваемый параметр кол-ва удаляемых элементов.В нашем случае ошибки не может быть, но мало ли.
 *	5. Не стал разбивать на разные файлы, хотя мб и стоило бы.
 *	6.В main закоментирован вывод на экран.
 */


//Перегруженные функции для заполнения структур значениями 0-9
void fill_structure(std::map<int,int>& m,int num_values)
{
	for (int j = 0; j < num_values; j++)
	{
		m[j] = rand() % 10;
	}
}

void fill_structure(std::vector<int>& v, int num_values)
{
	for (int j = 0; j < num_values; j++)
	{
		v.push_back(rand() % 10);
	}
}

//Удаление num_to_del - элементов
template <typename T>
int delete_from_struct(T& std_class,int num_to_del)
{
	if (num_to_del <= 0)
	{
		return 0;
	}
	if (num_to_del > std_class.size())
	{
		return -1;
	}
	
	for(int i =0;i <num_to_del;i++)
	{
		auto it = std_class.begin();
		int elem_to_delete = rand() % std_class.size();
		std::advance(it, elem_to_delete);
		std_class.erase(it);
	}
}

//Перегрузка оператора<< для вывода pair
template <typename first, typename second>
std::ostream& operator<<(std::ostream& out,const std::pair<first,second>& p)
{
	out << p.first << " : " << p.second<<std::endl;
	return out;
}

//Шаблон вывода структур на экран
template <typename T>
void print_structure(const T& std_class)
{
	for(auto i:std_class)
	{
		std::cout <<" "<< i;
	}
	std::cout<<std::endl;
}

//Синхронизация вектора и мап
void sync(std::vector<int>& vec,std::map<int,int>& map)
{
	//Удаляем элементы из вектора которые не встречаются в мапе
	vec.erase(std::remove_if(vec.begin(), vec.end(),
		       [&map](const int x)	{
						bool flag = true;
						for(auto item:map)
						{
							if(x == item.second)
								{
									flag = false; 
									break;
								}
						}
					return flag;
					})	,vec.end());
	//Удаляем элементы мап которые не встречаются в векторе
	auto iter = map.begin();
	while (iter != map.end())
	{
		bool flag = true;
		for(auto item:vec)
		{
			if(iter->second==item)
			{
				flag = false;
				break;
			}
		}
		if (flag == true) {
			iter = map.erase(iter);
		} 
		else 
		{
			iter++;
		}
	}
}

int main()
{
	srand(time(NULL));

	int Struct_size = 20;
	//Task1: Заполнение случайными числами и вывод
	std::vector<int> vec;
	std::map<int, int> map;
	fill_structure(vec, Struct_size);
	fill_structure(map, Struct_size);
	
	/*std::cout << "Vector: ";
	print_structure(vec);
	std::cout << "Map: ";
	print_structure(map);*/

	//Task2: Удаление до 15 элементов
	delete_from_struct(vec, rand() % 15 + 1);
	delete_from_struct(map, rand() % 15 + 1);
	
	/*std::cout << "Vector after delete: ";
	print_structure(vec);
	std::cout << "Map after delete: " << std::endl;
	print_structure(map);*/

	//Task3: Синхронизация вектора и мап
	sync(vec, map);
	
	/*std::cout << "Sync: ";
	print_structure(vec);
	print_structure(map);*/

	return 1;
}