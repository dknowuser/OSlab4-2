#include <Windows.h>
#include <iostream>

void main(void)
{
	setlocale(LC_ALL, "Russian");
	char InputChar = '\0';

	while (InputChar != '0')
	{
		std::cout << std::endl << "����:" << std::endl << std::endl;
		std::cout << "1 - ��������� ���������� � �������������� �������;" << std::endl << std::endl;
		std::cout << "2 - ����������� ������� ����������� ������;" << std::endl << std::endl;
		std::cout << "3 - ����������� ��������� ����������� ������� ������\n�� ��������� � ���������� ������;" << std::endl << std::endl;
		std::cout << "4 - �������������� ������� � �������������� ������\n� � ������ ����� ������ ������ �������;" << std::endl << std::endl;
		std::cout << "5 - �������������� ������� � �������� ��� ����������\n������ � �������������� ������ � � ������ ����� ������ ������ �������;" << std::endl << std::endl;
		std::cout << "6 - ������ ������ � ������ ������ �� �������� � ���������� �������;" << std::endl << std::endl;
		std::cout << "7 - ��������� ������ ������� ��� ��������� � ����������\n������� ������ � � ��������;" << std::endl << std::endl;
		std::cout << "8 - ������� ���������� ������ � ������������ �������\n��������� ������������, ��������� � ����������;" << std::endl << std::endl;
		std::cout << "0 - �����;" << std::endl << std::endl;
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

			//������� ���������� � �������������� �������
			std::cout << "����������� ����������: ";
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
				std::cout << "����������� �����������." << std::endl;
				break;
			default:
				std::cout << "������ ��� ��������� ���������� �� ����������� ����������." << std::endl;
				break;
			};
			std::cout << std::endl;
			std::cout << "������ ��������: " << info.dwPageSize << std::endl << std::endl;
			std::cout << "��������� �� ���������� ����� ������, ��������� �����������\n� ����������� ������������ ���������� (DLL): " << info.lpMinimumApplicationAddress << std::endl << std::endl;
			std::cout << "��������� �� ���������� ����� ������, ��������� �����������\n� ����������� ������������ ���������� (DLL): " << info.lpMaximumApplicationAddress << std::endl << std::endl;
			std::cout << "����� ����������� � �������������� �������:" << std::endl;

			Temp = info.dwActiveProcessorMask;
			Counter = 0;

			while (Temp)
			{
				if (Temp & 1)
					std::cout << "��������� " << Counter << std::endl;

				Counter++;
				Temp >>= 1;
			};
			std::cout << std::endl;

			std::cout << "����� ���������� ����������� � ������� ������: " << info.dwNumberOfProcessors << std::endl << std::endl;
			std::cout << "������������� ���������� ������, �� ��������\n����� �������� ����������� ������: " << info.dwAllocationGranularity << std::endl << std::endl;
			std::cout << "������������-��������� ������������ �������: " << info.wProcessorLevel << std::endl << std::endl;
			std::cout << "������ ����������, ��������� �� �����������: " << info.wProcessorRevision << std::endl << std::endl;
			std::cout << std::endl;
			break;
		case '2':
			MEMORYSTATUS meminfo;
			GlobalMemoryStatus(&meminfo);

			//���������� ������ ����������� ������
			std::cout << "������ ��������� ������ MEMORYSTATUS: " << meminfo.dwLength << std::endl << std::endl;
			std::cout << "��������������� ������� ������������ ���������� ������: " << meminfo.dwMemoryLoad << std::endl << std::endl;
			std::cout << "������ ���������� ������ � ������: " << meminfo.dwTotalPhys << std::endl << std::endl;
			std::cout << "������ ��������� ���������� ������ � ������: " << meminfo.dwAvailPhys << std::endl << std::endl;
			std::cout << "������� ����������� ��������� ������ � ������: " << meminfo.dwTotalPageFile << std::endl << std::endl;
			std::cout << "������������ ������ ������, ������� ������� �������\n����� ��������, � ������: " << meminfo.dwAvailPageFile << std::endl << std::endl;
			std::cout << "������ ���������������� ����� ������������ ���������\n������������ ����������� �������� � ������: " << meminfo.dwTotalVirtual << std::endl << std::endl;
			std::cout << "������ ������������������� � ������������ ������\n���������������� ����� ������������ ��������� ������������\n����������� �������� � ������: " << meminfo.dwAvailVirtual << std::endl << std::endl;
			std::cout << std::endl;
			break;
		case '3':
			MEMORY_BASIC_INFORMATION minfo;
			std::cout << "������� ����� ������� ������, ��������� �������� ����� ����������: " << std::endl;
			std::cin >> Temp;

			if (!VirtualQuery(&Temp, &minfo, sizeof(minfo)))
			{
				std::cout << "������ ��� ����������� ��������� �����������\n ������� ������." << std::endl;
				std::cin.clear();
				std::cin.sync();
				break;
			};

			//������� ��������� ���������� ������� ������
			std::cout << "��������� �� ������� ����� ������� �������: " << minfo.BaseAddress << std::endl << std::endl;
			std::cout << "��������� �� ������� ����� ��������� �������,\n���������� �������� VirtualAlloc: " << minfo.AllocationBase << std::endl << std::endl;
			std::cout << "�������� ������ ������ ��� ��������������\n��������� �������: " << std::endl;

			if(minfo.AllocationProtect & 0x10)
				std::cout << "���������� ������� ���������� � ���������� �������\n�������. ������� ������ � ���������� ������ �������� �\n��������� �������." << std::endl;

			if (minfo.AllocationProtect & 0x20)
				std::cout << "���������� ������� ���������� ��� ������ � ���������� �������\n�������. ������� ������ � ���������� ������ �������� �\n��������� �������." << std::endl;

			if (minfo.AllocationProtect & 0x40)
				std::cout << "���������� ������� ����������, ������ ��� ������ � ������ � ���������� �������\n�������." << std::endl;

			if (minfo.AllocationProtect & 0x80)
				std::cout << "���������� ������� ����������, ������ ��� ����������� �� ����� ������ � ���������������\n������������� ��������� �������." << std::endl;

			if (minfo.AllocationProtect & 0x1)
				std::cout << "������ ������� � ���������� ������� �������." << std::endl;

			if (minfo.AllocationProtect & 0x2)
				std::cout << "���������� ������� ������ � ���������� ������� �������. ������� ������ � ���������� ������ �������� �\n��������� �������." << std::endl;

			if (minfo.AllocationProtect & 0x4)
				std::cout << "���������� ������� ������ ��� ������ � ������ � ���������� ������� �������." << std::endl;

			if (minfo.AllocationProtect & 0x8)
				std::cout << "���������� ������� ������ ��� ����������� ��� ������ �\n��������������� ������������� ��������� �������." << std::endl;

			if (minfo.AllocationProtect & 0x40000000)
				std::cout << "��� ������������ �� ��������� ����������� ��� ������������\n������� ������� ��� cfg." << std::endl;

			if (minfo.AllocationProtect & 0x100)
				std::cout << "���������� �������� � �������." << std::endl;

			if (minfo.AllocationProtect & 0x200)
				std::cout << "������ ���� ������� ������������." << std::endl;

			if (minfo.AllocationProtect & 0x400)
				std::cout << "������ ���� ������� �������� ������������." << std::endl;
			std::cout << std::endl;

			std::cout << "������ �������, ������������ � �������� ������, � �������\n��� �������� ����� ���������� ��������, � ������: " << minfo.RegionSize << std::endl << std::endl;

			std::cout << "��������� ������� �������: " << std::endl;

			if(minfo.State & 0x1000)
				std::cout << "��������, ��� ������� �������� ���������� ���������\n���� � ������, ���� � ����� �������� �� �����." << std::endl;

			if (minfo.State & 0x10000)
				std::cout << "��������� ��������, ����������� ��� �������� ������\n� ��������� ��� ���������." << std::endl;

			if (minfo.State & 0x2000)
				std::cout << "����������������� ��������, ��� �������� ������������\n��������� ������������ �������� ������������� ��� ������-���� ����������� ���������." << std::endl;
			std::cout << std::endl;

			std::cout << "������ ������� � ��������� �������: " << minfo.Protect << std::endl << std::endl;
			std::cout << "��� ������� �������: " << std::endl;

			if(minfo.Type & 0x1000000)
				std::cout << "�������� ������ � �������� ������� ��������������\n� ������������� ������� �����������." << std::endl;

			if (minfo.Type & 0x40000)
				std::cout << "�������� ������ � ������� ������������� � ��� �������." << std::endl;

			if (minfo.Type & 0x20000)
				std::cout << "�������� ������ � ������� �������� ���������." << std::endl;
			std::cout << std::endl;
			break;
		case '4':
			InputChar = '\0';
			Temp = 0;
			std::cout << "������� ������ ������� � ������: ";
			std::cin >> Temp;

			std::cout << "������� a, ����� ��������������� ������ � �������������� ������,\n��� i, ����� ��������������� ������ � ������ ����� ������ ������ �������: ";
			std::cin >> InputChar;

			if ((InputChar == 'a') || (InputChar == 'A'))
			{
				if ((BaseAddress = VirtualAlloc(NULL, Temp, MEM_RESERVE, PAGE_READWRITE)) == NULL)
				{
					std::cout << "������ ��� �������������� ��������� �������." << std::endl;
					std::cin.clear();
					std::cin.sync();
					break;
				};

				std::cout << "������ � ������� ������� " << BaseAddress << " ������� ��������������." << std::endl << std::endl;
			}
			else
			{
				if ((InputChar == 'i') || (InputChar == 'I'))
				{
					BaseAddress = 0;
					std::cout << "������� ����� ������ �������: ";
					std::cin >> BaseAddress;

					if ((BaseAddress = VirtualAlloc(BaseAddress, Temp, MEM_RESERVE, PAGE_READWRITE)) == NULL)
					{
						std::cout << "������ ��� �������������� ��������� �������." << std::endl;
						std::cin.clear();
						std::cin.sync();
						break;
					};

					std::cout << "������ � ������� ������� " << BaseAddress << " ������� ��������������." << std::endl << std::endl;
				}
				else
				{
					std::cout << "������! ����� �������� �������� ��� ������ ������ ����." << std::endl;
					std::cin.clear();
					std::cin.sync();
					break;
				};
			};
			break;
		case '5':
			InputChar = '\0';
			Temp = 0;
			std::cout << "������� ������ ������� � ������: ";
			std::cin >> Temp;

			std::cout << "������� a, ����� ��������������� ������ � �������� ��� ���������� ������\n� �������������� ������, ��� i, ����� ��������������� ������ � ������\n����� ������ ������ �������: ";
			std::cin >> InputChar;

			if ((InputChar == 'a') || (InputChar == 'A'))
			{
				if ((BaseAddress = VirtualAlloc(NULL, Temp, MEM_RESERVE|MEM_COMMIT, PAGE_READWRITE)) == NULL)
				{
					std::cout << "������ ��� �������������� ��������� �������." << std::endl;
					std::cin.clear();
					std::cin.sync();
					break;
				};

				//��������� ������ ������
				ZeroMemory(BaseAddress, Temp);

				if (!VirtualProtect(BaseAddress, Temp, PAGE_READONLY, &ProtectGet))
				{
					std::cout << "������ ��� ��������� ���������� ������ ��������� �������." << std::endl;
					std::cin.clear();
					std::cin.sync();
					break;
				};

				std::cout << "������ � ������� ������� " << BaseAddress << " ������� ��������������." << std::endl << std::endl;
			}
			else
			{
				if ((InputChar == 'i') || (InputChar == 'I'))
				{
					BaseAddress = 0;
					std::cout << "������� ����� ������ �������: ";
					std::cin >> BaseAddress;

					if ((BaseAddress = VirtualAlloc(BaseAddress, Temp, MEM_RESERVE|MEM_COMMIT, PAGE_READWRITE)) == NULL)
					{
						std::cout << "������ ��� �������������� ��������� �������." << std::endl;
						std::cin.clear();
						std::cin.sync();
						break;
					};

					//��������� ������ ������
					ZeroMemory(BaseAddress, Temp);

					if (!VirtualProtect(BaseAddress, Temp, PAGE_READONLY, &ProtectGet))
					{
						std::cout << "������ ��� ��������� ���������� ������ ��������� �������." << std::endl;
						std::cin.clear();
						std::cin.sync();
						break;
					};

					std::cout << "������ � ������� ������� " << BaseAddress << " ������� ��������������." << std::endl << std::endl;
				}
				else
				{
					std::cout << "������! ����� �������� �������� ��� ������ ������ ����." << std::endl;
					std::cin.clear();
					std::cin.sync();
					break;
				};
			};
			break;
		case '6':
			lpTemp = 0;
			Cell = 0;
			std::cout << "������� ����� ������ ������, ���� ����� ������������� ������: ";
			std::cin >> lpTemp;
			std::cout << "������� ������������ �������� (�� 0 �� 65535): ";
			std::cin >> Cell;
			*(unsigned long long*)lpTemp = Cell;			
			std::cout << "�������� �������� ������� ��������." << std::endl;
			break;
		case '7':
			MEMORY_BASIC_INFORMATION minfo1;
			BaseAddress = 0;
			Counter = 0;
			ProtectSet = 0;
			ProtectGet = 0;
			std::cout << "������� ��������� ����� �������: ";
			std::cin >> BaseAddress;
			std::cout << "������� ������ ������� � ������: ";
			std::cin >> Counter;
			std::cout << "������� ��������������� ��������� ������ �������: ";
			std::cin >> ProtectSet;

			if (!VirtualProtect(BaseAddress, Counter, ProtectSet, &ProtectGet))
			{
				std::cout << "������ ��� ��������� ���������� ������ ��������� �������." << std::endl;
				std::cin.clear();
				std::cin.sync();
				break;
			};

			std::cout << std::endl;
			std::cout << "�������� ��������� ��������� ������� ������:" << std::endl;

			//��������� ������������� ��������� ������ �������
			if (!VirtualQuery(&BaseAddress, &minfo1, sizeof(minfo1)))
			{
				std::cout << "������ ��� ����������� ��������� �����������\n ������� ������." << std::endl;
				std::cin.clear();
				std::cin.sync();
				break;
			};

			//������� ��������� ���������� ������� ������
			std::cout << "��������� �� ������� ����� ������� �������: " << minfo1.BaseAddress << std::endl << std::endl;
			std::cout << "��������� �� ������� ����� ��������� �������,\n���������� �������� VirtualAlloc: " << minfo1.AllocationBase << std::endl << std::endl;
			std::cout << "�������� ������ ������ ��� ��������������\n��������� �������: " << std::endl;

			if (minfo1.AllocationProtect & 0x10)
				std::cout << "���������� ������� ���������� � ���������� �������\n�������. ������� ������ � ���������� ������ �������� �\n��������� �������." << std::endl;

			if (minfo1.AllocationProtect & 0x20)
				std::cout << "���������� ������� ���������� ��� ������ � ���������� �������\n�������. ������� ������ � ���������� ������ �������� �\n��������� �������." << std::endl;

			if (minfo1.AllocationProtect & 0x40)
				std::cout << "���������� ������� ����������, ������ ��� ������ � ������ � ���������� �������\n�������." << std::endl;

			if (minfo1.AllocationProtect & 0x80)
				std::cout << "���������� ������� ����������, ������ ��� ����������� �� ����� ������ � ���������������\n������������� ��������� �������." << std::endl;

			if (minfo1.AllocationProtect & 0x1)
				std::cout << "������ ������� � ���������� ������� �������." << std::endl;

			if (minfo1.AllocationProtect & 0x2)
				std::cout << "���������� ������� ������ � ���������� ������� �������. ������� ������ � ���������� ������ �������� �\n��������� �������." << std::endl;

			if (minfo1.AllocationProtect & 0x4)
				std::cout << "���������� ������� ������ ��� ������ � ������ � ���������� ������� �������." << std::endl;

			if (minfo1.AllocationProtect & 0x8)
				std::cout << "���������� ������� ������ ��� ����������� ��� ������ �\n��������������� ������������� ��������� �������." << std::endl;

			if (minfo1.AllocationProtect & 0x40000000)
				std::cout << "��� ������������ �� ��������� ����������� ��� ������������\n������� ������� ��� cfg." << std::endl;

			if (minfo1.AllocationProtect & 0x100)
				std::cout << "���������� �������� � �������." << std::endl;

			if (minfo1.AllocationProtect & 0x200)
				std::cout << "������ ���� ������� ������������." << std::endl;

			if (minfo1.AllocationProtect & 0x400)
				std::cout << "������ ���� ������� �������� ������������." << std::endl;
			std::cout << std::endl;

			std::cout << "������ �������, ������������ � �������� ������, � �������\n��� �������� ����� ���������� ��������, � ������: " << minfo1.RegionSize << std::endl << std::endl;

			std::cout << "��������� ������� �������: " << std::endl;

			if (minfo1.State & 0x1000)
				std::cout << "��������, ��� ������� �������� ���������� ���������\n���� � ������, ���� � ����� �������� �� �����." << std::endl;

			if (minfo1.State & 0x10000)
				std::cout << "��������� ��������, ����������� ��� �������� ������\n� ��������� ��� ���������." << std::endl;

			if (minfo1.State & 0x2000)
				std::cout << "����������������� ��������, ��� �������� ������������\n��������� ������������ �������� ������������� ��� ������-���� ����������� ���������." << std::endl;
			std::cout << std::endl;

			std::cout << "������ ������� � ��������� �������: " << minfo1.Protect << std::endl << std::endl;
			std::cout << "��� ������� �������: " << std::endl;

			if (minfo1.Type & 0x1000000)
				std::cout << "�������� ������ � �������� ������� ��������������\n� ������������� ������� �����������." << std::endl;

			if (minfo1.Type & 0x40000)
				std::cout << "�������� ������ � ������� ������������� � ��� �������." << std::endl;

			if (minfo1.Type & 0x20000)
				std::cout << "�������� ������ � ������� �������� ���������." << std::endl;
			std::cout << std::endl;
			break;
		case '8':
			BaseAddress = 0;
			Counter = 0;
			std::cout << "������� ��������� ����� �������: ";
			std::cin >> BaseAddress;
			std::cout << "������� ������ ������� � ������: ";
			std::cin >> Counter;

			if (!VirtualFree(BaseAddress, Counter, MEM_DECOMMIT))
			{
				std::cout << "������ ��� �������� ���������� ������ ��������� �������." << std::endl;
				std::cin.clear();
				std::cin.sync();
				//break;
			};

			if (!VirtualFree(BaseAddress, NULL, MEM_RELEASE))
			{
				std::cout << "������ ��� ������������ ��������� �������." << std::endl;
				std::cin.clear();
				std::cin.sync();
				break;
			};
			break;
		case '0':
			break;
		default:
			std::cout << "������! ����� �������� �������� ��� ������ ������ ����." << std::endl;
			std::cin.clear();
			std::cin.sync();
			break;
		};
	};
};