#ifndef PANTHERA_DLL_HPP
#define PANTHERA_DLL_HPP

#ifdef PANTHERA_BUILD_DLL
#define PT_API __declspec(dllexport)
#else
#define PT_API __declspec(dllimport)
#endif


#endif //PANTHERA_DLL_HPP
