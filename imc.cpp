#include "imc.h"

IMC::IMC(QObject *parent) : QObject(parent)
{

}



const QString &IMC::fecha() const
{
    return m_fecha;
}

float IMC::estatura() const
{
    return m_estatura;
}

float IMC::imc() const
{
    return m_imc;
}

float IMC::peso() const
{
    return m_peso;
}

IMC::IMC(float imc, float peso, const QString &fecha, float estatura) : m_imc(imc),
    m_peso(peso),
    m_fecha(fecha),
    m_estatura(estatura)
{}
