#include <Windows.h>
#include <iostream>

void main(void)
{
	setlocale(LC_ALL, "Russian");
	char InputChar = '\0';

	while (InputChar != '0')
	{
		std::cout << std::endl << "Меню:" << std::endl << std::endl;
		std::cout << "1 - получение информации о вычислительной системе;" << std::endl << std::endl;
		std::cout << "2 - определение статуса виртуальной памяти;" << std::endl << std::endl;
		std::cout << "3 - определение состояния конкретного участка памяти\nпо заданному с клавиатуры адресу;" << std::endl << std::endl;
		std::cout << "4 - резервирование региона в автоматическом режиме\nи в режиме ввода адреса начала региона;" << std::endl << std::endl;
		std::cout << "5 - резервирование региона и передача ему физической\nпамяти в автоматическом режиме и в режиме ввода адреса начала региона;" << std::endl << std::endl;
		std::cout << "6 - запись данных в ячейки памяти по заданным с клавиатуры адресам;" << std::endl << std::endl;
		std::cout << "7 - установка защиты доступа для заданного с клавиатуры\nрегиона памяти и её проверка;" << std::endl << std::endl;
		std::cout << "8 - возврат физической памяти и освобождение региона\nадресного пространства, заданного с клавиатуры;" << std::endl << std::endl;
		std::cout << "0 - выход;" << std::endl << std::endl;
		std::cout << ">> ";

		std::cin >> InputChar;
		unsigned int Temp = 0;
		unsigned int Counter = 0;
		unsigned short Cell = 0;
		DWORD ProtectSet = 0;
		DWORD ProtectGet = 0;
		LPVOID BaseAddress = 0;
		LPVOID lpTemp = 0;

		switch (InputChar)
		{
		case '1':
			SYSTEM_INFO info;
			GetSystemInfo(&info);

			//Выводим информацию о вычислительной системе
			std::cout << "Архитектура процессора: ";
			switch (info.wProcessorArchitecture)
			{
			case 0:
				std::cout << "x86." << std::endl;
				break;
			case 5:
				std::cout << "ARM." << std::endl;
				break;
			case 6:
				std::cout << "Intel Itanium-based." << std::endl;
				break;
			case 9:
				std::cout << "x64 (AMD or Intel)." << std::endl;
				break;
			case 65535:
				std::cout << "Неизвестная архитектура." << std::endl;
				break;
			default:
				std::cout << "Ошибка при получении информации об архитектуре процессора." << std::endl;
				break;
			};
			std::cout << std::endl;
			std::cout << "Размер страницы: " << info.dwPageSize << std::endl << std::endl;
			std::cout << "Указатель на наименьший адрес памяти, доступный приложениям\nи библиотекам динамической компоновки (DLL): " << info.lpMinimumApplicationAddress << std::endl << std::endl;
			std::cout << "Указатель на наибольший адрес памяти, доступный приложениям\nи библиотекам динамической компоновки (DLL): " << info.lpMaximumApplicationAddress << std::endl << std::endl;
			std::cout << "Набор процессоров в вычислительной системе:" << std::endl;

			Temp = info.dwActiveProcessorMask;
			Counter = 0;

			while (Temp)
			{
				if (Temp & 1)
					std::cout << "Процессор " << Counter << std::endl;

				Counter++;
				Temp >>= 1;
			};
			std::cout << std::endl;

			std::cout << "Число логических процессоров в текущей группе: " << info.dwNumberOfProcessors << std::endl << std::endl;
			std::cout << "Гранулярность начального адреса, по которому\nможно выделить виртуальную память: " << info.dwAllocationGranularity << std::endl << std::endl;
			std::cout << "Архитектурно-зависимый процессорный уровень: " << info.wProcessorLevel << std::endl << std::endl;
			std::cout << "Версия процессора, зависящая от архитектуры: " << info.wProcessorRevision << std::endl << std::endl;
			std::cout << std::endl;
			break;
		case '2':
			MEMORYSTATUS meminfo;
			GlobalMemoryStatus(&meminfo);

			//Определяем статус виртуальной памяти
			std::cout << "Размер структуры данных MEMORYSTATUS: " << meminfo.dwLength << std::endl << std::endl;
			std::cout << "Приблизительный процент используемой физической памяти: " << meminfo.dwMemoryLoad << std::endl << std::endl;
			std::cout << "Размер физической памяти в байтах: " << meminfo.dwTotalPhys << std::endl << std::endl;
			std::cout << "Размер доступной физической памяти в байтах: " << meminfo.dwAvailPhys << std::endl << std::endl;
			std::cout << "Текущее ограничение выделения памяти в байтах: " << meminfo.dwTotalPageFile << std::endl << std::endl;
			std::cout << "Максимальный размер памяти, который текущий процесс\nможет выделить, в байтах: " << meminfo.dwAvailPageFile << std::endl << std::endl;
			std::cout << "Размер пользовательской части виртуального адресного\nпространства вызывающего процесса в байтах: " << meminfo.dwTotalVirtual << std::endl << std::endl;
			std::cout << "Размер незарезервированной и невыделенной памяти\nпользовательской части виртуального адресного пространства\nвызывающего процесса в байтах: " << meminfo.dwAvailVirtual << std::endl << std::endl;
			std::cout << std::endl;
			break;
		case '3':
			MEMORY_BASIC_INFORMATION minfo;
			std::cout << "Введите адрес участка памяти, состояние которого нужно определить: " << std::endl;
			std::cin >> Temp;

			if (!VirtualQuery(&Temp, &minfo, sizeof(minfo)))
			{
				std::cout << "Ошибка при определении состояния конкретного\n участка памяти." << std::endl;
				std::cin.clear();
				std::cin.sync();
				break;
			};

			//Выводим состояние указанного участка памяти
			std::cout << "Указатель на базовый адрес региона страниц: " << minfo.BaseAddress << std::endl << std::endl;
			std::cout << "Указатель на базовый адрес диапазона страниц,\nвыделенных функцией VirtualAlloc: " << minfo.AllocationBase << std::endl << std::endl;
			std::cout << "Параметр защиты памяти при первоначальном\nвыделении региона: " << std::endl;

			if(minfo.AllocationProtect & 0x10)
				std::cout << "Разрешение доступа выполнения к выделенной области\nстраниц. Попытка записи в выделенный регион приводит к\nнарушению доступа." << std::endl;

			if (minfo.AllocationProtect & 0x20)
				std::cout << "Разрешение доступа выполнения или чтения к выделенной области\nстраниц. Попытка записи в выделенный регион приводит к\nнарушению доступа." << std::endl;

			if (minfo.AllocationProtect & 0x40)
				std::cout << "Разрешение доступа выполнения, чтения или чтения и записи к выделенной области\nстраниц." << std::endl;

			if (minfo.AllocationProtect & 0x80)
				std::cout << "Разрешение доступа выполнения, чтения или копирования во время записи к сопоставленному\nпредставлению файлового объекта." << std::endl;

			if (minfo.AllocationProtect & 0x1)
				std::cout << "Запрет доступа к выделенной области страниц." << std::endl;

			if (minfo.AllocationProtect & 0x2)
				std::cout << "Разрешение доступа чтения к выделенной области страниц. Попытка записи в выделенный регион приводит к\nнарушению доступа." << std::endl;

			if (minfo.AllocationProtect & 0x4)
				std::cout << "Разрешение доступа чтения или чтения и записи к выделенной области страниц." << std::endl;

			if (minfo.AllocationProtect & 0x8)
				std::cout << "Разрешение доступа чтения или копирования при записи к\nсопоставленному представлению файлового объекта." << std::endl;

			if (minfo.AllocationProtect & 0x40000000)
				std::cout << "Все расположения на страницах установлены как недопустимые\nцелевые объекты для cfg." << std::endl;

			if (minfo.AllocationProtect & 0x100)
				std::cout << "Охраняемые страницы в регионе." << std::endl;

			if (minfo.AllocationProtect & 0x200)
				std::cout << "Наборы всех страниц некэшируемые." << std::endl;

			if (minfo.AllocationProtect & 0x400)
				std::cout << "Наборы всех страниц смешанно записываемые." << std::endl;
			std::cout << std::endl;

			std::cout << "Размер области, начинающейся с базового адреса, в которой\nвсе страницы имеют одинаковые атрибуты, в байтах: " << minfo.RegionSize << std::endl << std::endl;

			std::cout << "Состояние страниц региона: " << std::endl;

			if(minfo.State & 0x1000)
				std::cout << "Страницы, для которых выделено физическое хранилище\nлибо в памяти, либо в файле подкачки на диске." << std::endl;

			if (minfo.State & 0x10000)
				std::cout << "Свободные страницы, недоступные для процесса вызова\nи доступные для выделения." << std::endl;

			if (minfo.State & 0x2000)
				std::cout << "Зарезервированные страницы, где диапазон виртуального\nадресного пространства процесса резервируется без какого-либо физического выделения." << std::endl;
			std::cout << std::endl;

			std::cout << "Защита доступа к страницам региона: " << minfo.Protect << std::endl << std::endl;
			std::cout << "Тип страниц региона: " << std::endl;

			if(minfo.Type & 0x1000000)
				std::cout << "Страницы памяти в пределах области сопоставляются\nв представление раздела изображения." << std::endl;

			if (minfo.Type & 0x40000)
				std::cout << "Страницы памяти в области преобразуются в вид участка." << std::endl;

			if (minfo.Type & 0x20000)
				std::cout << "Страницы памяти в регионе являются закрытыми." << std::endl;
			std::cout << std::endl;
			break;
		case '4':
			InputChar = '\0';
			Temp = 0;
			std::cout << "Введите размер региона в байтах: ";
			std::cin >> Temp;

			std::cout << "Введите a, чтобы зарезервировать регион в автоматическом режиме,\nили i, чтобы зарезервировать регион в режиме ввода адреса начала региона: ";
			std::cin >> InputChar;

			if ((InputChar == 'a') || (InputChar == 'A'))
			{
				if ((BaseAddress = VirtualAlloc(NULL, Temp, MEM_RESERVE, PAGE_READWRITE)) == NULL)
				{
					std::cout << "Ошибка при резервировании заданного региона." << std::endl;
					std::cin.clear();
					std::cin.sync();
					break;
				};

				std::cout << "Регион с базовым адресом " << BaseAddress << " успешно зарезервирован." << std::endl << std::endl;
			}
			else
			{
				if ((InputChar == 'i') || (InputChar == 'I'))
				{
					BaseAddress = 0;
					std::cout << "Введите адрес начала региона: ";
					std::cin >> BaseAddress;

					if ((BaseAddress = VirtualAlloc(BaseAddress, Temp, MEM_RESERVE, PAGE_READWRITE)) == NULL)
					{
						std::cout << "Ошибка при резервировании заданного региона." << std::endl;
						std::cin.clear();
						std::cin.sync();
						break;
					};

					std::cout << "Регион с базовым адресом " << BaseAddress << " успешно зарезервирован." << std::endl << std::endl;
				}
				else
				{
					std::cout << "Ошибка! Введён неверный параметр при выборе пункта меню." << std::endl;
					std::cin.clear();
					std::cin.sync();
					break;
				};
			};
			break;
		case '5':
			InputChar = '\0';
			Temp = 0;
			std::cout << "Введите размер региона в байтах: ";
			std::cin >> Temp;

			std::cout << "Введите a, чтобы зарезервировать регион и передать ему физическую память\nв автоматическом режиме, или i, чтобы зарезервировать регион в режиме\nввода адреса начала региона: ";
			std::cin >> InputChar;

			if ((InputChar == 'a') || (InputChar == 'A'))
			{
				if ((BaseAddress = VirtualAlloc(NULL, Temp, MEM_RESERVE|MEM_COMMIT, PAGE_READWRITE)) == NULL)
				{
					std::cout << "Ошибка при резервировании заданного региона." << std::endl;
					std::cin.clear();
					std::cin.sync();
					break;
				};

				//Заполняем регион нулями
				ZeroMemory(BaseAddress, Temp);

				if (!VirtualProtect(BaseAddress, Temp, PAGE_READONLY, &ProtectGet))
				{
					std::cout << "Ошибка при установке параметров защиты заданного региона." << std::endl;
					std::cin.clear();
					std::cin.sync();
					break;
				};

				std::cout << "Регион с базовым адресом " << BaseAddress << " успешно зарезервирован." << std::endl << std::endl;
			}
			else
			{
				if ((InputChar == 'i') || (InputChar == 'I'))
				{
					BaseAddress = 0;
					std::cout << "Введите адрес начала региона: ";
					std::cin >> BaseAddress;

					if ((BaseAddress = VirtualAlloc(BaseAddress, Temp, MEM_RESERVE|MEM_COMMIT, PAGE_READWRITE)) == NULL)
					{
						std::cout << "Ошибка при резервировании заданного региона." << std::endl;
						std::cin.clear();
						std::cin.sync();
						break;
					};

					//Заполняем регион нулями
					ZeroMemory(BaseAddress, Temp);

					if (!VirtualProtect(BaseAddress, Temp, PAGE_READONLY, &ProtectGet))
					{
						std::cout << "Ошибка при установке параметров защиты заданного региона." << std::endl;
						std::cin.clear();
						std::cin.sync();
						break;
					};

					std::cout << "Регион с базовым адресом " << BaseAddress << " успешно зарезервирован." << std::endl << std::endl;
				}
				else
				{
					std::cout << "Ошибка! Введён неверный параметр при выборе пункта меню." << std::endl;
					std::cin.clear();
					std::cin.sync();
					break;
				};
			};
			break;
		case '6':
			lpTemp = 0;
			Cell = 0;
			std::cout << "Введите адрес ячейки памяти, куда будет производиться запись: ";
			std::cin >> lpTemp;
			std::cout << "Введите записываемое значение (от 0 до 65535): ";
			std::cin >> Cell;
			*(unsigned long long*)lpTemp = Cell;			
			std::cout << "Заданное значение успешно записано." << std::endl;
			break;
		case '7':
			MEMORY_BASIC_INFORMATION minfo1;
			BaseAddress = 0;
			Counter = 0;
			ProtectSet = 0;
			ProtectGet = 0;
			std::cout << "Введите начальный адрес региона: ";
			std::cin >> BaseAddress;
			std::cout << "Введите размер региона в байтах: ";
			std::cin >> Counter;
			std::cout << "Введите устанавливаемые параметры защиты региона: ";
			std::cin >> ProtectSet;

			if (!VirtualProtect(BaseAddress, Counter, ProtectSet, &ProtectGet))
			{
				std::cout << "Ошибка при установке параметров защиты заданного региона." << std::endl;
				std::cin.clear();
				std::cin.sync();
				break;
			};

			std::cout << std::endl;
			std::cout << "Проверка состояния заданного участка памяти:" << std::endl;

			//Проверяем установленные параметры защиты региона
			if (!VirtualQuery(&BaseAddress, &minfo1, sizeof(minfo1)))
			{
				std::cout << "Ошибка при определении состояния конкретного\n участка памяти." << std::endl;
				std::cin.clear();
				std::cin.sync();
				break;
			};

			//Выводим состояние указанного участка памяти
			std::cout << "Указатель на базовый адрес региона страниц: " << minfo1.BaseAddress << std::endl << std::endl;
			std::cout << "Указатель на базовый адрес диапазона страниц,\nвыделенных функцией VirtualAlloc: " << minfo1.AllocationBase << std::endl << std::endl;
			std::cout << "Параметр защиты памяти при первоначальном\nвыделении региона: " << std::endl;

			if (minfo1.AllocationProtect & 0x10)
				std::cout << "Разрешение доступа выполнения к выделенной области\nстраниц. Попытка записи в выделенный регион приводит к\nнарушению доступа." << std::endl;

			if (minfo1.AllocationProtect & 0x20)
				std::cout << "Разрешение доступа выполнения или чтения к выделенной области\nстраниц. Попытка записи в выделенный регион приводит к\nнарушению доступа." << std::endl;

			if (minfo1.AllocationProtect & 0x40)
				std::cout << "Разрешение доступа выполнения, чтения или чтения и записи к выделенной области\nстраниц." << std::endl;

			if (minfo1.AllocationProtect & 0x80)
				std::cout << "Разрешение доступа выполнения, чтения или копирования во время записи к сопоставленному\nпредставлению файлового объекта." << std::endl;

			if (minfo1.AllocationProtect & 0x1)
				std::cout << "Запрет доступа к выделенной области страниц." << std::endl;

			if (minfo1.AllocationProtect & 0x2)
				std::cout << "Разрешение доступа чтения к выделенной области страниц. Попытка записи в выделенный регион приводит к\nнарушению доступа." << std::endl;

			if (minfo1.AllocationProtect & 0x4)
				std::cout << "Разрешение доступа чтения или чтения и записи к выделенной области страниц." << std::endl;

			if (minfo1.AllocationProtect & 0x8)
				std::cout << "Разрешение доступа чтения или копирования при записи к\nсопоставленному представлению файлового объекта." << std::endl;

			if (minfo1.AllocationProtect & 0x40000000)
				std::cout << "Все расположения на страницах установлены как недопустимые\nцелевые объекты для cfg." << std::endl;

			if (minfo1.AllocationProtect & 0x100)
				std::cout << "Охраняемые страницы в регионе." << std::endl;

			if (minfo1.AllocationProtect & 0x200)
				std::cout << "Наборы всех страниц некэшируемые." << std::endl;

			if (minfo1.AllocationProtect & 0x400)
				std::cout << "Наборы всех страниц смешанно записываемые." << std::endl;
			std::cout << std::endl;

			std::cout << "Размер области, начинающейся с базового адреса, в которой\nвсе страницы имеют одинаковые атрибуты, в байтах: " << minfo1.RegionSize << std::endl << std::endl;

			std::cout << "Состояние страниц региона: " << std::endl;

			if (minfo1.State & 0x1000)
				std::cout << "Страницы, для которых выделено физическое хранилище\nлибо в памяти, либо в файле подкачки на диске." << std::endl;

			if (minfo1.State & 0x10000)
				std::cout << "Свободные страницы, недоступные для процесса вызова\nи доступные для выделения." << std::endl;

			if (minfo1.State & 0x2000)
				std::cout << "Зарезервированные страницы, где диапазон виртуального\nадресного пространства процесса резервируется без какого-либо физического выделения." << std::endl;
			std::cout << std::endl;

			std::cout << "Защита доступа к страницам региона: " << minfo1.Protect << std::endl << std::endl;
			std::cout << "Тип страниц региона: " << std::endl;

			if (minfo1.Type & 0x1000000)
				std::cout << "Страницы памяти в пределах области сопоставляются\nв представление раздела изображения." << std::endl;

			if (minfo1.Type & 0x40000)
				std::cout << "Страницы памяти в области преобразуются в вид участка." << std::endl;

			if (minfo1.Type & 0x20000)
				std::cout << "Страницы памяти в регионе являются закрытыми." << std::endl;
			std::cout << std::endl;
			break;
		case '8':
			BaseAddress = 0;
			Counter = 0;
			std::cout << "Введите начальный адрес региона: ";
			std::cin >> BaseAddress;
			std::cout << "Введите размер региона в байтах: ";
			std::cin >> Counter;

			if (!VirtualFree(BaseAddress, Counter, MEM_DECOMMIT))
			{
				std::cout << "Ошибка при возврате физической памяти заданного региона." << std::endl;
				std::cin.clear();
				std::cin.sync();
				//break;
			};

			if (!VirtualFree(BaseAddress, NULL, MEM_RELEASE))
			{
				std::cout << "Ошибка при освобождении заданного региона." << std::endl;
				std::cin.clear();
				std::cin.sync();
				break;
			};
			break;
		case '0':
			break;
		default:
			std::cout << "Ошибка! Введён неверный параметр при выборе пункта меню." << std::endl;
			std::cin.clear();
			std::cin.sync();
			break;
		};
	};
};