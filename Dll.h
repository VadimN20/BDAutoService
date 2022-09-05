// Приведенный ниже блок ifdef — это стандартный метод создания макросов, упрощающий процедуру
// экспорта из библиотек DLL. Все файлы данной DLL скомпилированы с использованием символа DLL_EXPORTS
// Символ, определенный в командной строке. Этот символ не должен быть определен в каком-либо проекте,
// использующем данную DLL. Благодаря этому любой другой проект, исходные файлы которого включают данный файл, видит
// функции DLL_API как импортированные из DLL, тогда как данная DLL видит символы,
// определяемые данным макросом, как экспортированные.
#ifdef DLL_EXPORTS
#define DLL_API __declspec(dllexport)
#else
#define DLL_API __declspec(dllimport)
#endif
#include "Сemetery.h"
DLL_API void initializationData();
DLL_API void addRecord(const string& name, const string& date, long price, int category);
DLL_API void sortDataBase(bool isR);
DLL_API void deleteRecord(string& name);
DLL_API void findRecord(string& name);
DLL_API string getRecord(int i);
DLL_API string getSortRecord(int i);
DLL_API int sizeVec();
DLL_API int sizeSortVector();
DLL_API void cleanMemory();