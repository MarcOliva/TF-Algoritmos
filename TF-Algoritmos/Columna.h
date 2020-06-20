#pragma once
#include <string>

enum Tipo { none, boolean, integer, decimal, caracter, string };

class Columna
{
private:
    Tipo tipo;
public:
    Columna(Tipo type = Tipo::none) : tipo(type) {}

    Tipo getTipo()
    {
        return this->tipo;
    }
};

class ColumnaInt : public Columna
{
private:
    int dato;
public:
    ColumnaInt(int dat) : Columna(Tipo::integer)
    {
        this->dato = dat;
    }

    int getDato()
    {
        return this->dato;
    }

    void setDato(int _dato)
    {
        this->dato = _dato;
    }

};

class ColumnaBool : public Columna
{
private:
    bool dato;
public:
    ColumnaBool(bool dat) : Columna(Tipo::boolean)
    {
        this->dato = dat;
    }

    bool getDato()
    {
        return this->dato;
    }

    void setDato(bool _dato)
    {
        this->dato = _dato;
    }
};

class ColumnaNombre : public Columna
{
private:
    std::string nombre;
public:
    ColumnaNombre(Tipo type, std::string name) : Columna(type)
    {
        this->nombre = name;
    }

    std::string getNombre()
    {
        return this->nombre;
    }

    void setNombre(std::string nombre)
    {
        this->nombre = nombre;
    }
};

class ColumnaDecimal : public Columna
{
private:
    float dato;
public:
    ColumnaDecimal(float dat) : Columna(Tipo::decimal)
    {
        this->dato = dat;
    }

    float getDato()
    {
        return this->dato;
    }

    void setDato(float _dato)
    {
        this->dato = _dato;
    }
};

class ColumnaCaracter : public Columna
{
private:
    char dato;
public:
    ColumnaCaracter(char dat) : Columna(Tipo::caracter)
    {
        this->dato = dat;
    }

    char getDato()
    {
        return this->dato;
    }

    void setDato(char _dato)
    {
        this->dato = _dato;
    }
};

class ColumnaString : public Columna
{
private:
    std::string dato;
public:
    ColumnaString(std::string dat) : Columna(Tipo::string)
    {
        this->dato = dat;
    }

    std::string getDato()
    {
        return this->dato;
    }

    void setDato(std::string _dato)
    {
        this->dato = _dato;
    }
};