#ifndef PARSER_H
#define PARSER_H
#include "../game/level.h"
#include "../options.h"

class Parser
{
public:
    Parser();
    void parseTypes(const QString &str);
    QVector<ValueXY> parseWalls(const QString &str);
    void parseLineWalls(const QString &str); //линии блоков рисуются строго с лево на право
    QVector<TypeObject> getTypes() const;
    QVector<ValueXY> getWalls() const;

private:
    QVector<TypeObject> types_;
    QVector<ValueXY> walls_;

};

#endif // PARSER_H
