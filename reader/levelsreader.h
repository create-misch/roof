#ifndef LEVELSREADER_H
#define LEVELSREADER_H
#include "../game/level.h"
#include "parser.h"
#include <QXmlStreamReader>
#include <QDebug>
#include <QFile>

typedef QVector<Level> LevelsVector;

class LevelsReader
{
public:
    LevelsReader();
    void read(const QString &file_name);
    void parseLevel(QXmlStreamReader &reader);
    LevelsVector getLevelsVector();

private:
    LevelsVector levelsVector_;
};

#endif // LEVELSREADER_H
