#ifndef __ERRORS_H__
#define __ERRORS_H__

#include "Main.hpp"

class ArcadeException : public std::exception
{
    protected:
        const std::string _type;
        std::string _error;
    public:
        ArcadeException(std::string error, uint16_t line)
        {
            _error = "[" + _type + "]: " + error + " at line " + std::to_string(line);
        }

        const char *what() const throw()
        {
            return _error.c_str();
        }
};

class InitWindowException : public ArcadeException
{
    protected:
        const std::string _type = "InitWindowException";
    public:
        InitWindowException(std::string error, uint16_t line) : ArcadeException(error, line) {}
};

class InitKeyException : public ArcadeException
{
    protected:
        const std::string _type = "InitKeyException";
    public:
        InitKeyException(std::string error, uint16_t line) : ArcadeException(error, line) {}
};

class InitTextureException : public ArcadeException
{
    protected:
        const std::string _type = "InitTextureException";
    public:
        InitTextureException(std::string error, uint16_t line) : ArcadeException(error, line) {}
};

#endif