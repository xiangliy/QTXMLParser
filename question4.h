#ifndef QUESTION4_H
#define QUESTION4_H
#include <QList>
#include <QString>
#include <QXmlStreamReader>

class Question4
{
public:

    void parse(const QString& strInputFolderPath, const QString& strOutputFolderPath);

    static Question4& getInstance()
    {
        static Question4 question4;
        return question4;
    }

private:
    Question4();

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
