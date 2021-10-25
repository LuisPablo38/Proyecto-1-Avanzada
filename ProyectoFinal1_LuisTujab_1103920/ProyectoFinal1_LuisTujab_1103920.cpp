#include "pch.h"
#include<Windows.h>
#include"Lista.h"
#include"InfoMusica.h"
#include "InfoViewsComparator.h"
#include"InfoNombreComparator.h"
using namespace System;
using std::string; 
void MarshalString(String^ s, string& os) {
	using namespace Runtime::InteropServices;
	const char* chars =
		(const char*)(Marshal::StringToHGlobalAnsi(s)).ToPointer();
	os = chars;
	Marshal::FreeHGlobal(IntPtr((void*)chars));
}

Lista<InfoMusica>* readInformacion(String^ filePath)
{
	Lista<InfoMusica>* infoMusic = new Lista<InfoMusica>();
	array<String^>^ lineas = System::IO::File::ReadAllLines(filePath);
	for (int i = 0; i < lineas->Length; i++)
	{
		array<String^>^ linea = lineas[i]->Split(',');

		string nameCan;
		MarshalString(linea[0], nameCan);

		double views = Double::Parse(linea[1]);
		InfoMusica* InformMu = new InfoMusica( i,nameCan, views );

		infoMusic->add(InformMu);
	}
	return infoMusic;

}
void showInfoMusic(Lista<InfoMusica>* informacion)
{
	
	Console::WriteLine("id\tNombre Cancion-Artista\t\t Views (millones)");
	Console::WriteLine("\n");

	for (int i = 0; i < informacion->getSize(); i++)
	{
		InfoMusica* InformMu = informacion->get(i);

		String^ nombre = gcnew String(InformMu->getnombreCan().c_str());

		Console::WriteLine("{0}\t{1}\t\t\{2}", InformMu->getid(), nombre, InformMu->getviews() );
	}
}

void showNewInfo(Lista<InfoMusica>*informacion)
{
	Console::WriteLine("id\tNombre Cancion-Artista\t\t Views (millones)");
	Console::WriteLine("\n");
	for (int i = 0; i < informacion->getSize(); i++)
	{
		InfoMusica* InformNewMu = informacion->get(i);
		String^ nombre = gcnew String(InformNewMu->getnombreCan().c_str());
		Console::WriteLine("{0}\t{1}\t\t\{2}", InformNewMu->getid(), nombre, InformNewMu->getviews());
	}
}

int main(array<System::String ^> ^args)
{
	string palabraIng; 
    int ReadOp ;
	int ReadOp2; 
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, 2);
	Console::WriteLine ( "\t\t----------MIX MUSIC------------\n");
	Console::WriteLine("\n");
	Console::WriteLine(" \t\tPresione 1 para ir a su playlist \n");
	Console::WriteLine("\n");
	regresar_menuPrin:
	Console::WriteLine(" \t\tIngrese la opcion que desea realizar \n");
	try
	{
		ReadOp = Convert::ToInt32(Console::ReadLine());
	}
	catch (const std::string & error)
	{

	}
	switch (ReadOp)
	{
	case 1:
		int ingop; 
		system("cls"); 
		SetConsoleTextAttribute(hConsole, 3);
		Console::WriteLine(" \t\tBienvenido a su playlist \n");
		Console::WriteLine(" \t\tOrden del las ultimas aregadas a las priemas \n");
		Lista<InfoMusica>* InformMu = readInformacion("InfoMusic.csv");
		showInfoMusic(InformMu);
		Console::WriteLine("\n");
		Console::WriteLine("\n");
		Console::WriteLine("Ingrese 1 para ordenar la playlist por views");
		Console::WriteLine("Ingrese 2 para ordenar la playlist por orden alfabetico");
		Console::WriteLine("Ingrese 3 para agregar nueva cancion");
		Console::WriteLine("Ingrese 4 para eliminar cancion");
		try
		{
			ingop = Convert::ToInt32(Console::ReadLine());

		}
		catch (const std::string & error)
		{

		}
		switch (ingop)
		{
		case 1: 
			system("cls"); 
			int menudentro;
			SetConsoleTextAttribute(hConsole, 3);
			Console::WriteLine(" \tOrden por views \n");
			Console::WriteLine("\n");
			InformMu = InformMu->bubbleSort(new InfoViewsComparator());
			showInfoMusic(InformMu);
			Console::WriteLine("\n");
			Console::WriteLine("Ingrese 1 para ordenar la playlist por orden alfabetico");
			Console::WriteLine("Ingrese 2 para ordenar la playlist por orden original");
			try
			{
				menudentro = Convert::ToInt32(Console::ReadLine());
			}
			catch (const std::exception&)
			{
			}
			switch (menudentro)
			{
			case 1:
				system("cls");
				int menudentrodos;
				SetConsoleTextAttribute(hConsole, 3);
				Console::WriteLine(" \tOrden por alfabetico \n");
				InformMu = InformMu->bubbleSort(new InfoNombreComparator());
				showInfoMusic(InformMu);

				break;
			case 2:
				system("cls");
				SetConsoleTextAttribute(hConsole, 3);
				Console::WriteLine(" \tOrden original \n");
				Lista<InfoMusica>* InformMu = readInformacion("InfoMusic.csv");
				showInfoMusic(InformMu);
				Console::WriteLine(" \tPresione 1 para regresar al menu principal \n");
				break;
			} 
			break;

		case 2:
			system("cls");
			int opi;
			SetConsoleTextAttribute(hConsole, 3);
			Console::WriteLine(" \t Orden alfabetico \n");
			Console::WriteLine("\n");
			InformMu = InformMu->bubbleSort(new InfoNombreComparator());
			showInfoMusic(InformMu);
			Console::WriteLine(" \t Ingrese 1 para salir al menu principal \n");
			try
			{
				opi = Convert::ToInt32(Console::ReadLine());
			}
			catch (const std::exception&)
			{
			}
			switch (opi)
			{
			case 1:
				exit; 
				break;
			}
			break; 
		case 3:
			system("cls"); 
			int elim;
			SetConsoleTextAttribute(hConsole, 3);
			Console::WriteLine(" \t Ingrese nombre de la cancion/ nombre del artista , views \n");
		palabraIng : Console::ReadLine(); 
			/*InformMu->add(palabraIng);*/
			Console::WriteLine(" \t Ingrese 1 para guardar y regresar a la lista  \n");
			elim = Convert::ToInt32(Console::ReadLine()); 

			break;
			//////////guardar nueva lista 
			//////////mostrar nueva lista 
			///////// agregar otra cancion?
			//////////salir 


		case 4: 
			system("cls");
			int idelim; 
			Lista<InfoMusica>* InformNewMu = readInformacion("InfoMusic.csv");
			showNewInfo(InformNewMu);
			Console::WriteLine(" \t \nIngrese el ID de la cancion que quiere eliminar  \n");
			idelim = Convert::ToInt32(Console::ReadLine()); 
			if (idelim == 0)
			{
				system("cls");
				int nuewmen; 
				Console::WriteLine(" \t Cancion eliminda  \n");
				InformMu->remove(idelim);
				showInfoMusic(InformMu);
				Console::WriteLine(" \t \n Presione 1  \n");
				nuewmen = Convert::ToInt32(Console::ReadLine()); 
				if (nuewmen == 1)
				{
					system("cls");
					int menuor; 
					Console::WriteLine(" \t PlayList  \n");
					showInfoMusic(InformMu);
					Console::WriteLine(" \t\n Si desea regresar a su playlist anterior sin modificar presione 1  \n");
					Console::WriteLine(" \t\n Si desea ordenar las canciones por views presione 2  \n");
					Console::WriteLine(" \t\n Si desea ordenar las canciones por alfabetopresione 3  \n");
					Console::WriteLine(" \t\n Si desea salir presione 4  \n");
					menuor = Convert::ToInt32(Console::ReadLine()); 
					if (menuor == 2)
					{
						system("cls");
						int opfin;
						Console::WriteLine(" \tOrden por views \n");
						Console::WriteLine("\n");
						InformMu = InformMu->bubbleSort(new InfoViewsComparator());
						showInfoMusic(InformMu);
						Console::WriteLine("\n");
						Console::WriteLine("Ingrese 2 para salir");
						opfin = Convert::ToInt32(Console::ReadLine());
						if (opfin == 2)
						{
							exit(-1);
						}
					}
					if (menuor == 3)
					{
						system("cls");
						int opfin;
						Console::WriteLine(" \tOrden por alfabeto \n");
						Console::WriteLine("\n");
						InformMu = InformMu->bubbleSort(new InfoNombreComparator());
						showInfoMusic(InformMu);
						Console::WriteLine("\n");
						Console::WriteLine("Ingrese 2 para salir");
						opfin = Convert::ToInt32(Console::ReadLine());
						if (opfin == 2)
						{
							exit(-1);
						}
					}
					if (menuor == 4)
					{
						exit(-1);
					}
					if (menuor > 4)
					{
						system("cls");
						Console::WriteLine(" \tOpcion no valida \n");
						Console::WriteLine(" \tIngrese 1 para regresar al menu principal \n");
					}
					
				}
			}
			if (idelim == 1)
			{
				system("cls");
				int nuewmen;
				Console::WriteLine(" \t Cancion eliminda  \n");
				InformMu->remove(idelim);
				showInfoMusic(InformMu);
				Console::WriteLine(" \t \n Presione 1  \n");
				nuewmen = Convert::ToInt32(Console::ReadLine());
				if (nuewmen == 1)
				{
					system("cls");
					int menuor;
					Console::WriteLine(" \t PlayList  \n");
					showInfoMusic(InformMu);
					Console::WriteLine(" \t\n Si desea regresar a su playlist anterior sin modificar presione 1  \n");
					Console::WriteLine(" \t\n Si desea ordenar las canciones por views presione 2  \n");
					Console::WriteLine(" \t\n Si desea ordenar las canciones por alfabetopresione 3  \n");
					Console::WriteLine(" \t\n Si desea salir presione 4  \n");
					menuor = Convert::ToInt32(Console::ReadLine());
					if (menuor==2)
					{
						system("cls");
						int opfin;
						Console::WriteLine(" \tOrden por views \n");
						Console::WriteLine("\n");
						InformMu = InformMu->bubbleSort(new InfoViewsComparator());
						showInfoMusic(InformMu);
						Console::WriteLine("\n");
						Console::WriteLine("Ingrese 2 para salir");
						opfin = Convert::ToInt32(Console::ReadLine());
						if (opfin == 2)
						{
							exit(-1);
						}
					}
					if (menuor == 3 )
					{
						system("cls");
						int opfin;
						Console::WriteLine(" \tOrden por alfabeto \n");
						Console::WriteLine("\n");
						InformMu = InformMu->bubbleSort(new InfoNombreComparator());
						showInfoMusic(InformMu);
						Console::WriteLine("\n");
						Console::WriteLine("Ingrese 2 para salir");
						opfin = Convert::ToInt32(Console::ReadLine());
						if (opfin == 2)
						{
							exit(-1);
						}
					}
					if (menuor == 4)
					{
						exit(-1);
					}
					if (menuor > 4)
					{
						system("cls");
						Console::WriteLine(" \tOpcion no valida \n");
						Console::WriteLine(" \tIngrese 1 para regresar al menu principal \n");
					}
				}
			}
			if (idelim == 2)
			{
				system("cls");
				int nuewmen;
				Console::WriteLine(" \t Cancion eliminda  \n");
				InformMu->remove(idelim);
				showInfoMusic(InformMu);
				Console::WriteLine(" \t \n Presione 1  \n");
				nuewmen = Convert::ToInt32(Console::ReadLine());
				if (nuewmen == 1)
				{
					system("cls");
					int menuor;
					Console::WriteLine(" \t PlayList  \n");
					showInfoMusic(InformMu);
					Console::WriteLine(" \t\n Si desea regresar a su playlist anterior sin modificar presione 1  \n");
					Console::WriteLine(" \t\n Si desea ordenar las canciones por views presione 2  \n");
					Console::WriteLine(" \t\n Si desea ordenar las canciones por alfabetopresione 3  \n");
					Console::WriteLine(" \t\n Si desea salir presione 4  \n");
					menuor = Convert::ToInt32(Console::ReadLine());
					if (menuor == 2)
					{
						system("cls");
						int opfin;
						Console::WriteLine(" \tOrden por views \n");
						Console::WriteLine("\n");
						InformMu = InformMu->bubbleSort(new InfoViewsComparator());
						showInfoMusic(InformMu);
						Console::WriteLine("\n");
						Console::WriteLine("Ingrese 2 para salir");
						opfin = Convert::ToInt32(Console::ReadLine());
						if (opfin == 2)
						{
							exit(-1);
						}
					}
					if (menuor == 3)
					{
						system("cls");
						int opfin;
						Console::WriteLine(" \tOrden por alfabeto \n");
						Console::WriteLine("\n");
						InformMu = InformMu->bubbleSort(new InfoNombreComparator());
						showInfoMusic(InformMu);
						Console::WriteLine("\n");
						Console::WriteLine("Ingrese 2 para salir");
						opfin = Convert::ToInt32(Console::ReadLine());
						if (opfin == 2)
						{
							exit(-1);
						}
					}
					if (menuor == 4)
					{
						exit(-1);
					}
					if (menuor > 4)
					{
						system("cls");
						Console::WriteLine(" \tOpcion no valida \n");
						Console::WriteLine(" \tIngrese 1 para regresar al menu principal \n");
					}
				}
			}
			if (idelim == 3)
			{
				system("cls");
				Console::WriteLine(" \t Cancion eliminda  \n");
				InformMu->remove(idelim);
				showInfoMusic(InformMu);
				Console::WriteLine(" \t \n Presione 1  \n");
				int nuewmen;
				nuewmen = Convert::ToInt32(Console::ReadLine());
				if (nuewmen == 1)
				{
					system("cls");
					int menuor;
					Console::WriteLine(" \t PlayList  \n");
					showInfoMusic(InformMu);
					Console::WriteLine(" \t\n Si desea regresar a su playlist anterior sin modificar presione 1  \n");
					Console::WriteLine(" \t\n Si desea ordenar las canciones por views presione 2  \n");
					Console::WriteLine(" \t\n Si desea ordenar las canciones por alfabetopresione 3  \n");
					Console::WriteLine(" \t\n Si desea salir presione 4  \n");
					menuor = Convert::ToInt32(Console::ReadLine());
					if (menuor == 2)
					{
						system("cls");
						int opfin;
						Console::WriteLine(" \tOrden por views \n");
						Console::WriteLine("\n");
						InformMu = InformMu->bubbleSort(new InfoViewsComparator());
						showInfoMusic(InformMu);
						Console::WriteLine("\n");
						Console::WriteLine("Ingrese 2 para salir");
						opfin = Convert::ToInt32(Console::ReadLine());
						if (opfin == 2)
						{
							exit(-1);
						}
					}
					if (menuor == 3)
					{
						system("cls");
						int opfin;
						Console::WriteLine(" \tOrden por alfabeto \n");
						Console::WriteLine("\n");
						InformMu = InformMu->bubbleSort(new InfoNombreComparator());
						showInfoMusic(InformMu);
						Console::WriteLine("\n");
						Console::WriteLine("Ingrese 2 para salir");
						opfin = Convert::ToInt32(Console::ReadLine());
						if (opfin == 2)
						{
							exit(-1);
						}
					}
					if (menuor == 4)
					{
						exit(-1);
					}
					if (menuor > 4)
					{
						system("cls");
						Console::WriteLine(" \tOpcion no valida \n");
						Console::WriteLine(" \tIngrese 1 para regresar al menu principal \n");
					}
				}
			}
			if (idelim == 4)
			{
				system("cls");
				Console::WriteLine(" \t Cancion eliminda  \n");
				InformMu->remove(idelim);
				showInfoMusic(InformMu);
				Console::WriteLine(" \t \nPresione 1  \n");
				int nuewmen;
				nuewmen = Convert::ToInt32(Console::ReadLine());
				if (nuewmen == 1)
				{
					system("cls");
					int menuor;
					Console::WriteLine(" \t PlayList  \n");
					showInfoMusic(InformMu);
					Console::WriteLine(" \t\n Si desea regresar a su playlist anterior sin modificar presione 1  \n");
					Console::WriteLine(" \t\n Si desea ordenar las canciones por views presione 2  \n");
					Console::WriteLine(" \t\n Si desea ordenar las canciones por alfabetopresione 3  \n");
					Console::WriteLine(" \t\n Si desea salir presione 4  \n");
					menuor = Convert::ToInt32(Console::ReadLine());
					if (menuor == 2)
					{
						system("cls");
						int opfin;
						Console::WriteLine(" \tOrden por views \n");
						Console::WriteLine("\n");
						InformMu = InformMu->bubbleSort(new InfoViewsComparator());
						showInfoMusic(InformMu);
						Console::WriteLine("\n");
						Console::WriteLine("Ingrese 2 para salir");
						opfin = Convert::ToInt32(Console::ReadLine());
						if (opfin == 2)
						{
							exit(-1);
						}
					}
					if (menuor == 3)
					{
						system("cls");
						int opfin;
						Console::WriteLine(" \tOrden por alfabeto \n");
						Console::WriteLine("\n");
						InformMu = InformMu->bubbleSort(new InfoNombreComparator());
						showInfoMusic(InformMu);
						Console::WriteLine("\n");
						Console::WriteLine("Ingrese 2 para salir");
						opfin = Convert::ToInt32(Console::ReadLine());
						if (opfin == 2)
						{
							exit(-1);
						}
					}
					if (menuor == 4)
					{
						exit(-1);
					}
					if (menuor > 4)
					{
						system("cls");
						Console::WriteLine(" \tOpcion no valida \n");
						Console::WriteLine(" \tIngrese 1 para regresar al menu principal \n");
					}
				}
			}
			if (idelim == 5)
			{
				system("cls");
				Console::WriteLine(" \t Cancion eliminda  \n");
				InformMu->remove(idelim);
				showInfoMusic(InformMu);
				Console::WriteLine(" \t Presione 1  \n");
				int nuewmen;
				nuewmen = Convert::ToInt32(Console::ReadLine());
				if (nuewmen == 1)
				{
					system("cls");
					int menuor;
					Console::WriteLine(" \t PlayList  \n");
					showInfoMusic(InformMu);
					Console::WriteLine(" \t\n Si desea regresar a su playlist anterior sin modificar presione 1  \n");
					Console::WriteLine(" \t\n Si desea ordenar las canciones por views presione 2  \n");
					Console::WriteLine(" \t\n Si desea ordenar las canciones por alfabetopresione 3  \n");
					Console::WriteLine(" \t\n Si desea salir presione 4  \n");
					menuor = Convert::ToInt32(Console::ReadLine());
					if (menuor == 2)
					{
						system("cls");
						int opfin;
						Console::WriteLine(" \tOrden por views \n");
						Console::WriteLine("\n");
						InformMu = InformMu->bubbleSort(new InfoViewsComparator());
						showInfoMusic(InformMu);
						Console::WriteLine("\n");
						Console::WriteLine("Ingrese 2 para salir");
						opfin = Convert::ToInt32(Console::ReadLine());
						if (opfin == 2)
						{
							exit(-1);
						}
					}
					if (menuor == 3)
					{
						system("cls");
						int opfin;
						Console::WriteLine(" \tOrden por alfabeto \n");
						Console::WriteLine("\n");
						InformMu = InformMu->bubbleSort(new InfoNombreComparator());
						showInfoMusic(InformMu);
						Console::WriteLine("\n");
						Console::WriteLine("Ingrese 2 para salir");
						opfin = Convert::ToInt32(Console::ReadLine());
						if (opfin == 2)
						{
							exit(-1);
						}
					}
					if (menuor == 4)
					{
						exit(-1);
					}
					if (menuor > 4)
					{
						system("cls");
						Console::WriteLine(" \tOpcion no valida \n");
						Console::WriteLine(" \tIngrese 1 para regresar al menu principal \n");
					}
				}
			}
			if (idelim == 6)
			{
				system("cls");
				Console::WriteLine(" \t Cancion eliminda  \n");
				InformMu->remove(idelim);
				showInfoMusic(InformMu);
				Console::WriteLine(" \t \nPresione 1  \n");
				int nuewmen;
				nuewmen = Convert::ToInt32(Console::ReadLine());
				if (nuewmen == 1)
				{
					system("cls");
					int menuor;
					Console::WriteLine(" \t PlayList  \n");
					showInfoMusic(InformMu);
					Console::WriteLine(" \t\n Si desea regresar a su playlist anterior sin modificar presione 1  \n");
					Console::WriteLine(" \t\n Si desea ordenar las canciones por views presione 2  \n");
					Console::WriteLine(" \t\n Si desea ordenar las canciones por alfabetopresione 3  \n");
					Console::WriteLine(" \t\n Si desea salir presione 4  \n");
					menuor = Convert::ToInt32(Console::ReadLine());
					if (menuor == 2)
					{
						system("cls");
						int opfin;
						Console::WriteLine(" \tOrden por views \n");
						Console::WriteLine("\n");
						InformMu = InformMu->bubbleSort(new InfoViewsComparator());
						showInfoMusic(InformMu);
						Console::WriteLine("\n");
						Console::WriteLine("Ingrese 2 para salir");
						opfin = Convert::ToInt32(Console::ReadLine());
						if (opfin == 2)
						{
							exit(-1);
						}
					}
					if (menuor == 3)
					{
						system("cls");
						int opfin;
						Console::WriteLine(" \tOrden por alfabeto \n");
						Console::WriteLine("\n");
						InformMu = InformMu->bubbleSort(new InfoNombreComparator());
						showInfoMusic(InformMu);
						Console::WriteLine("\n");
						Console::WriteLine("Ingrese 2 para salir");
						opfin = Convert::ToInt32(Console::ReadLine());
						if (opfin == 2)
						{
							exit(-1);
						}
					}
					if (menuor == 4)
					{
						exit(-1);
					}
					if (menuor > 4)
					{
						system("cls");
						Console::WriteLine(" \tOpcion no valida \n");
						Console::WriteLine(" \tIngrese 1 para regresar al menu principal \n");
					}
				}
			}
			if (idelim >=InformMu->getSize())
			{
				system("cls");
				Console::WriteLine(" \t Id no valido  \n");
				Console::WriteLine(" \t Presione 1  \n");
			}
			break; 
		}

		break;
	}
	goto regresar_menuPrin;

	return 0;
}
