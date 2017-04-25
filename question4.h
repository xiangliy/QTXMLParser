#ifndef QUESTION4_H
#define QUESTION4_H
#include <QList>
#include <QString>
#include <QXmlStreamReader>

class Question4
{
public:
    Question4();

    void parse(const QString& strInputFolderPath, const QString& strOutputFolderPath);

private:
    QStringList _lstInputFile;

    void getfiles(const QString& strInputFolderPath);

    void parsefile(const QString& strInputFile, const QString& strOutputFile);

    void addition(QXmlStreamReader& reader, double & dTotal);
    void subtraction(QXmlStreamReader& reader, double & dTotal);
    void multiplication(QXmlStreamReader& reader, double & dTotal);
    void division(QXmlStreamReader& reader, double & dTotal);

    double getItemValue(QXmlStreamReader& reader, const QString& strKey);
};

#endif // QUESTION4_H
