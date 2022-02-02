#ifndef IMC_H
#define IMC_H

#include <QObject>

class IMC : public QObject
{
    Q_OBJECT
public:
    explicit IMC(QObject *parent = nullptr);
    IMC(float imc, float peso, const QString &fecha, float estatura);



    const QString &fecha() const;
    float estatura() const;
    float imc() const;

    float peso() const;

signals:
private:
    float m_imc;
    float m_peso;
    QString m_fecha;
    float m_estatura;

};

#endif // IMC_H
