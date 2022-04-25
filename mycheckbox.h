#ifndef MYCHECKBOX_H
#define MYCHECKBOX_H
#include <QString>
#include <QCheckBox>


class MyCheckBox : public QCheckBox
{
public:
    MyCheckBox(const QString &text,QWidget *parent = nullptr);
};

#endif // MYCHECKBOX_H
