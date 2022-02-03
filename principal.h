#ifndef PRINCIPAL_H
#define PRINCIPAL_H

#include <QMainWindow>
#include <qmath.h>
#include <QDebug>
#include <QFile>
#include <QMessageBox>

#include "imc.h"
QT_BEGIN_NAMESPACE
namespace Ui { class Principal; }
QT_END_NAMESPACE

class Principal : public QMainWindow
{
    Q_OBJECT

public:
    Principal(QWidget *parent = nullptr);
    ~Principal();

private slots:
    void on_btnCalcular_released();

private:
    Ui::Principal *ui;
    QList<IMC*> m_lista;

    QString curfile;

    void savefile();

    void calcular();
    bool obtenerDatos();
    void ordenar();
    void moverLinea(float imc);

    QString m_Datos;
    QString m_fecha;
    float m_estatura;
    float m_peso;
    float m_IMC;

};
#endif // PRINCIPAL_H
