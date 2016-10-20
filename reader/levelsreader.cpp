#include "levelsreader.h"

LevelsReader::LevelsReader()
{
}

void LevelsReader::read(const QString &file_name){
    QFile f(file_name);
    if(!f.open(QIODevice::ReadOnly | QIODevice::Text)){
        qDebug() << file_name << ":" << f.errorString() ;
    }
    QXmlStreamReader reader(&f);
    while (!reader.atEnd() && !reader.hasError()) {
        reader.readNext();        
        if(reader.isStartDocument())
            continue;
        if (reader.isStartElement()){
            if (reader.name() == "levels"){
                continue;
            }
            if (reader.name() == "level" && reader.isStartElement()){
                parseLevel(reader);
            }
        }
    }
}

void LevelsReader::parseLevel(QXmlStreamReader &reader)
{
    if (reader.isStartElement() && reader.name() == "level"){
        int level_id, max, time;
        Parser parser;
        QXmlStreamAttributes attributes = reader.attributes();
            if (attributes.hasAttribute("id"))
                level_id = attributes.value("id").toInt();
            reader.readNext();            
            while (!(reader.isEndElement() && reader.name() == "level"))
            {
                if (reader.isStartElement())
                {
                    if (reader.name() == "types"){
                        reader.readNext();
                        parser.parseTypes(reader.text().toString());
                    }
                    if (reader.name() == "max"){
                        reader.readNext();
                        max = reader.text().toInt();
                    }
                    if (reader.name() == "time"){
                        reader.readNext();
                        time = reader.text().toInt();
                    }
                    if (reader.name() == "walls"){
                        reader.readNext();
                        parser.parseLineWalls(reader.text().toString());
                    }
                }
                reader.readNext();
            }
        if(reader.isEndElement() && reader.name() == "level"){
            Level level;
            level.max_burned = max;
            level.time_to_burn = time;
            while(max >= parser.getTypes().size()){
                level.types_npc += parser.getTypes();
                max-= parser.getTypes().size();
            }
            if(max > 0){
                QVector<TypeObject> vec(parser.getTypes());
                vec.resize(max);
                level.types_npc += vec;
            }
            level.walls += parser.getWalls();
            levelsVector_.push_back(level);
        }
    }
}

LevelsVector LevelsReader::getLevelsVector()
{
    return levelsVector_;
}

