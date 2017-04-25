#include "question4.h"
#include <QDir>
#include "qdebug.h"
#include <QXmlStreamReader>
#include <QXmlStreamWriter>
#include <QFile>

Question4::Question4()
{

}

/*
 * * Entry Point for parsing
 *
 * const QString& strFolderPath input folder path
 *
 */
void Question4::parse(const QString& strInputFolderPath, const QString& strOutputFolderPath)
{
    try
    {
        getfiles(strInputFolderPath);

        // parse all the files in folder
        for(QStringList::iterator it = _lstInputFile.begin();
            it != _lstInputFile.end(); ++it)
        {
            QXmlStreamWriter xmlWriter;

            QString strInputFile = strInputFolderPath + "\\" + *it;

            QString strOutputfile(*it);
            strOutputfile.replace(QString(".xml"), QString(""));
            strOutputfile.append("_result.xml");
            strOutputfile = strOutputFolderPath + "\\" + strOutputfile;

            parsefile(strInputFile, strOutputfile);
        }
    }
    catch (...)
    {
        qWarning("exceptions in parse...");
    }

}


/*
 * * Get all files in a given directory
 *
 * const QString& strFolderPath input folder path
 *
 */
void Question4::getfiles(const QString& strInputFolderPath)
{
    QDir fileDir(strInputFolderPath);
    fileDir.setFilter(QDir::Files | QDir::Hidden | QDir::NoSymLinks);

    if(!fileDir.exists())
    {
        qWarning("Cannot find input directory");
    }

    QFileInfoList listFile = fileDir.entryInfoList();

    for (int i = 0; i < listFile.size(); ++i)
    {
        QFileInfo fileInfo = listFile.at(i);
        _lstInputFile.append(fileInfo.fileName());
    }
}


/*
 * * Parse a single xml file
 *
 * const QString& strFile file to be parsed
 *
 */
void Question4::parsefile(const QString& strInputFile, const QString& strOutputFile)
{
    try
    {
        // Open files
        qInfo() << "Parsing file : " + strInputFile;
        qInfo() << "Output file : " + strOutputFile;

        QFile inputfile(strInputFile);
        if(!inputfile.open(QFile::ReadOnly | QFile::Text)){
            qInfo() << "Cannot read file" << inputfile.errorString();
        }

        QFile outputfile(strOutputFile);
        if(!outputfile.open(QFile::WriteOnly | QFile::Text)){
            qInfo() << "Cannot write file" << outputfile.errorString();
        }

        // QXmlStream can avoid too much memory consumption
        QXmlStreamWriter writer(&outputfile);
        QXmlStreamReader reader(&inputfile);

        writer.writeStartDocument();
        writer.writeStartElement("expressions");

        while(!reader.atEnd() && !reader.hasError())
        {
            if(reader.readNextStartElement())
            {
                if (reader.attributes().hasAttribute("id"))
                {
                    QString strID = reader.attributes().value("id").toString();
                    double dTotal = 0.0;

                    if(reader.name() == "addition")
                    {
                        addition(reader, dTotal);
                    }
                    else if(reader.name() == "subtraction")
                    {
                        subtraction(reader, dTotal);
                    }
                    else if(reader.name() == "multiplication")
                    {
                        multiplication(reader, dTotal);
                    }
                    else if(reader.name() == "division")
                    {
                        division(reader, dTotal);
                    }
                    else
                    {
                        qInfo() << "Not supported operation";
                    }

                    // create element in output file and save calculation result
                    writer.writeStartElement("result");
                    writer.writeAttribute("id", strID);
                    writer.writeCharacters(QString::number(dTotal));
                    writer.writeEndElement();
                }
                else
                {
                    qInfo() << "other element:" + reader.name();
                }
            }
        }

        writer.writeEndElement();
        writer.writeEndDocument();
    }
    catch (...)
    {
        qWarning("exceptions in parsefile...");
    }

}

void Question4::addition(QXmlStreamReader& reader, double & dTotal)
{
    try
    {
        reader.readNext();

        while (reader.name() != "addition")
        {
            reader.readNext();

            if (reader.tokenType() == QXmlStreamReader::StartElement && reader.name() == "item")
            {
                dTotal += getItemValue(reader, QString("item"));
            }
        }
        reader.readNext();
    }
    catch (...)
    {
        qWarning("exceptions in addition...");
    }

}

void Question4::subtraction(QXmlStreamReader& reader, double & dTotal)
{
    try
    {
        reader.readNext();

        while (reader.name() != "subtraction")
        {
            reader.readNext();

            if (reader.tokenType() == QXmlStreamReader::StartElement && reader.name() == "minuend")
            {
                dTotal += getItemValue(reader, "minuend");
            }

            if (reader.tokenType() == QXmlStreamReader::StartElement && reader.name() == "subtrahend")
            {
                dTotal -= getItemValue(reader, "subtrahend");
            }
        }
        reader.readNext();
    }
    catch (...)
    {
        qWarning("exceptions in subtraction...");
    }
}

void Question4::multiplication(QXmlStreamReader& reader, double & dTotal)
{
    try
    {
        reader.readNext();
        double dResult = 1;

        while (reader.name() != "multiplication")
        {
            reader.readNext();

            if (reader.tokenType() == QXmlStreamReader::StartElement && reader.name() == "factor")
            {
                dResult *= getItemValue(reader, QString("factor"));
            }
        }
        reader.readNext();

        dTotal = dResult;
    }
    catch (...)
    {
        qWarning("exceptions in multiplication...");
    }

}

void Question4::division(QXmlStreamReader& reader, double & dTotal)
{
    try
    {
        reader.readNext();
        double dResult = 1;

        while (reader.name() != "division")
        {
            reader.readNext();

            if (reader.tokenType() == QXmlStreamReader::StartElement && reader.name() == "dividend")
            {
                dResult *= getItemValue(reader, "dividend");
            }

            if (reader.tokenType() == QXmlStreamReader::StartElement && reader.name() == "divisor")
            {
                dResult /= getItemValue(reader, "divisor");
            }
        }
        reader.readNext();

        dTotal = dResult;
    }
    catch (...)
    {
        qWarning("exceptions in division...");
    }
}


double Question4::getItemValue(QXmlStreamReader& reader, const QString& strKey)
{
    double dValue;
    try
    {
        reader.readNext();
        while (reader.name() != strKey)
        {
            if (reader.tokenType() == QXmlStreamReader::StartElement)
            {
                if (reader.name() == "addition")
                {
                    addition(reader, dValue);
                }
                else if (reader.name() == "subtraction")
                {
                    subtraction(reader, dValue);
                }
                else if (reader.name() == "multiplication")
                {
                    multiplication(reader, dValue);
                }
                else if (reader.name() == "division")
                {
                    division(reader, dValue);
                }
                else
                {
                    qInfo() << "Unsupported Operation";
                }
            }
            else if (reader.tokenType() == QXmlStreamReader::Characters)
            {
                QStringRef strValue = reader.text();
                bool ok = false;
                dValue = strValue.toDouble(&ok);

                if (ok)
                {
                    return dValue;
                }
            }
            else
            {
                qInfo() << "Unsupported Operation";
            }
            reader.readNext();
        }
    }
    catch (...)
    {
        qWarning("exceptions in getItemValue...");
    }

    return dValue;
}
