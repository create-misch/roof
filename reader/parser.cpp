#include "parser.h"
#include <QRegExp>

Parser::Parser()
{
    types_.clear();
    walls_.clear();
}

void Parser::parseTypes(const QString &str)
{
    QRegExp rx("(\\d+)");
    int pos = 0;
    while ((pos = rx.indexIn(str, pos)) != -1) {
        types_.push_back(static_cast<TypeObject>(rx.cap(1).toInt()));
        pos += rx.matchedLength();
    }
}

QVector<ValueXY> Parser::parseWalls(const QString &str)
{
    QRegExp rx("\\(\\d+\\,?\\d+\\)");
    int pos  = 0;
    QVector<ValueXY> walls;
    while ((pos = rx.indexIn(str, pos)) != -1) {
        ValueXY xy;
        QString str_rx(rx.cap(0));
        int pos_num = 0;
        QRegExp rx_num("(\\d+)");
        pos_num = rx_num.indexIn(str_rx, pos_num);
        xy.x = rx_num.cap(0).toInt();
        pos_num += rx_num.matchedLength();
        pos_num = rx_num.indexIn(str_rx, pos_num);
        xy.y = rx_num.cap(0).toInt();
        pos += rx.matchedLength();
        walls.push_back(xy);
    }
    return walls;
}

void Parser::parseLineWalls(const QString &str)
{
    QRegExp rx("\\{(\\(\\d+\\,?\\d+\\)\\,?)+\\}");
    int pos  = 0;
    while ((pos = rx.indexIn(str, pos)) != -1) {
        QString str_rx(rx.cap(0));
        QVector<ValueXY> walls = parseWalls(str_rx);
        if(walls.size() > 1){
            int wall_height = Options::instance()->game_option.getWallHeight();
            int wall_width = Options::instance()->game_option.getWallWidth();
            for(int i = 0; i < walls.size() - 1; i++){                
                if((walls[i+1].x > walls[i].x) && (walls[i+1].y == walls[i].y)){
                    int count = (walls[i+1].x - walls[i].x)/wall_width;
                    for(int j = 0; j < count; j++){
                        walls_.push_back(ValueXY(walls[i].x + j*wall_width, walls[i].y));
                    }
                }
                else{
                    qDebug() << "x less previe x wall";
                }

                    if((walls[i+1].y > walls[i].y) && (walls[i+1].x == walls[i].x)){
                        int count = (walls[i+1].y - walls[i].y)/wall_height;
                        for(int j = 0; j < count; j++){
                            walls_.push_back(ValueXY(walls[i].x, walls[i].y  + j*wall_height));
                        }
                    }
                    else{
                        qDebug() << "y less previe y wall";
                    }
                }
            }
        else{
            walls_ += walls;
        }
        pos += rx.matchedLength();
    }
}

QVector<TypeObject> Parser::getTypes() const
{
    if(!types_.isEmpty()){
        return types_;
    }
}

QVector<ValueXY> Parser::getWalls() const
{
    if(!walls_.isEmpty()){
        return walls_;
    }
}
