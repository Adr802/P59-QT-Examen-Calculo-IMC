#include "principal.h"
#include "ui_principal.h"

Principal::Principal(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Principal)
{
    ui->setupUi(this);


    QString filename = "D:/Adrian/data.txt";

    QFile file(filename);

    if(file.exists()){
        //qDebug()<<"aaaaaaa";
       if(file.open( QFile::ReadOnly)){
           //qDebug()<<"aaasdfdsdgfd";

            QTextStream entrada(&file);
            while(!entrada.atEnd()){
                //qDebug()<<"asd";

                QString linea = entrada.readLine();
                QVector<QStringRef>datos = linea.splitRef("-");
                QString fecha = datos.at(0).toString();
                QString estatura = datos.at(1).toString();
                QString peso = datos.at(2).toString();
                QString imc = datos.at(3).toString();



                m_lista.append(new IMC(imc.toFloat(),peso.toFloat(),fecha,estatura.toFloat()));

            }
            foreach(IMC *p, m_lista){
                qDebug()<<p->peso()<<endl;
            }

            ordenar();
            qDebug()<<"as"<<endl;
            foreach(IMC *p, m_lista){
                qDebug()<<p->peso()<<endl;
            }

            ui->outPesoMax->setText(QString::number(m_lista.at(m_lista.length()-1)->peso(),'f',2) + " kg");
            ui->outPesoMin->setText(QString::number(m_lista.at(0)->peso(),'f',2) + " kg");
       }
    }
    //qDebug()<<"cccccccc";

}

Principal::~Principal()
{
    delete ui;
}

void Principal::calcular()
{
    qDebug()<<m_peso;
    qDebug()<<m_estatura;


    m_IMC = (m_peso)/qPow(m_estatura,2);

    qDebug()<<m_IMC;

    if(m_IMC < 18.5){
        ui->outIMC->setText("Peso inferior al normal");
    }else if(m_IMC < 24.9){
        ui->outIMC->setText("Normal");
    }else if(m_IMC < 29.9){
        ui->outIMC->setText("Peso superior al normal");
    }else if(m_IMC >=30){
        ui->outIMC->setText("Obesidad");
    }

    qDebug()<<m_fecha;

}

bool Principal::obtenerDatos()
{
    if(ui->inEstatura->text().isEmpty()){
        return false;
    }
    if(ui->inPeso->text().isEmpty()){
        return false;
    }
    m_fecha = ui->inFecha->text();
    m_peso = ui->inPeso->text().toFloat();
    float centi = ui->inEstatura->text().toInt();
    m_estatura = centi/100;

    ui->outPesoActual->setText(QString::number(m_peso) + " kg");
    return true;
}

void Principal::ordenar()
{
    for(int j=0; j < m_lista.length(); j++){
        for(int i=0; i < m_lista.length(); i++){
            if(m_lista[j]->imc() < m_lista[i]->imc()){
                IMC *temp = m_lista[j];
                m_lista[j] = m_lista[i];
                m_lista[i] = temp;
            }
        }
    }
}


void Principal::on_btnCalcular_released()
{

    if(obtenerDatos()){
        calcular();
        m_lista.append(new IMC(m_IMC,m_peso,m_fecha,m_estatura));
        ordenar();
        ui->outPesoMax->setText(QString::number(m_lista.at(m_lista.length()-1)->peso(),'f',2) + " kg");
        ui->outPesoMin->setText(QString::number(m_lista.at(0)->peso(),'f',2) + " kg");
    }else{
        ui->statusbar->showMessage("Campo vacio",3000);
    }

}

