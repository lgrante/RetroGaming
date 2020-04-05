#ifndef __ERRORS_H__
#define __ERRORS_H__

#include "Main.hpp"

class ArcadeException : public std::exception
{
    protected:
        std::string _error;
    public:
        ArcadeException(std::string error, uint16_t line, const char *filename, const std::string &type)
        {
            _error = "[" + type + "]: " + error + " at line " + std::to_string(line) + " in " + std::string(filename);
        }

        const char *what() const throw()
        {
            return _error.c_str();
        }
};

class LoadSharedModuleException : public ArcadeException
{
    public:
        LoadSharedModuleException(std::string error, const char *filename, uint16_t line) 
            : ArcadeException(error, line, filename, "LoadSharedModuleException") {}
};

class InitWindowException : public ArcadeException
{
    public:
        InitWindowException(std::string error, const char *filename, uint16_t line) 
            : ArcadeException(error, line, filename, "InitWindowException") {}
};

class InitKeyException : public ArcadeException
{
    public:
        InitKeyException(std::string error, const char *filename, uint16_t line) 
            : ArcadeException(error, line, filename, "InitKeyException") {}
};

class InitTextureException : public ArcadeException
{
    public:
        InitTextureException(std::string error, const char *filename, uint16_t line) 
            : ArcadeException(error, line, filename, "InitTextureException") {}
};

class InitTextException : public ArcadeException
{
    public:
        InitTextException(std::string error, const char *filename, uint16_t line) 
            : ArcadeException(error, line, filename, "InitTextException") {}
};

#endif