#include "principal.h"
#include "ui_principal.h"

Principal::Principal(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Principal)
{
    ui->setupUi(this);


    QString filename = "../data.txt";

    QFile file(filename);
    curfile = filename;
    if(file.exists()){

        qDebug()<<"aaaaaaa";

        //SI EL ARCHIVO EXISTE ENTRA ACA
        if(file.open( QFile::ReadOnly | QFile::Text)){
            qDebug()<<"aaasdfdsdgfd";

            QTextStream entrada(&file);
            while(!entrada.atEnd()){
                qDebug()<<"asd";

                QString linea = entrada.readLine();
                QVector<QStringRef>datos = linea.splitRef("\t");
                qDebug()<<datos.size();
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

    file.close();
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
    ui->outIMCNU->setText(QString::number(m_IMC,'f',2) + " kg");
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

void Principal::moverLinea(float imc)
{

    if(imc <=12){
        ui->outLinea->setGeometry(12,0,4,58);
    }else if(imc <= 14){
        ui->outLinea->setGeometry(33,0,4,58);
    }else if(imc <= 16){
        ui->outLinea->setGeometry(57,0,4,58);
    }else if(imc <= 18.5){
        ui->outLinea->setGeometry(75,0,4,58);


    }else if(imc <= 20){
        ui->outLinea->setGeometry(92,0,4,58);
    }else if(imc <= 22){
        ui->outLinea->setGeometry(110,0,4,58);
    }else if(imc <= 23){
        ui->outLinea->setGeometry(134,0,4,58);
    }else if(imc <= 24.5){
        ui->outLinea->setGeometry(154,0,4,58);



    }else if(imc <= 25){
        ui->outLinea->setGeometry(172,0,4,58);
    }else if(imc <= 26){
        ui->outLinea->setGeometry(194,0,4,58);
    }else if(imc <= 28){
        ui->outLinea->setGeometry(220,0,4,58);
    }else if(imc <= 29.9){
        ui->outLinea->setGeometry(244,0,4,58);


    }else if(imc <= 34){
        ui->outLinea->setGeometry(262,0,4,58);
    }else if(imc <= 38){
        ui->outLinea->setGeometry(280,0,4,58);
    }else if(imc >38){
        ui->outLinea->setGeometry(334,0,4,58);
    }
}


void Principal::on_btnCalcular_released()
{

    if(obtenerDatos()){
        calcular();
        m_lista.append(new IMC(m_IMC,m_peso,m_fecha,m_estatura));
        moverLinea(m_IMC);
        ordenar();
        ui->outPesoMax->setText(QString::number(m_lista.at(m_lista.length()-1)->peso(),'f',2) + " kg");
        ui->outPesoMin->setText(QString::number(m_lista.at(0)->peso(),'f',2) + " kg");


        m_Datos += m_fecha + "\t" + QString::number(m_estatura,'f',2) + "\t" +  QString::number(m_peso,'f',2) + "\t" + QString::number(m_IMC,'f',2) + "\n";
        savefile();

    }else{
        ui->statusbar->showMessage("Campo vacio",3000);
    }

}

void Principal::savefile()
{
    QFile file(curfile);
    if(file.open(QFile::WriteOnly)){
        file.write(m_Datos.toUtf8());
    }else{
        qDebug()<<"N";
    }
    file.close();
}

