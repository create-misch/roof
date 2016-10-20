#include "engine.h"

bool sortLife_false(Object *lhs, Object *rhs){
    if((lhs->getIsLife() == true) && (rhs->getIsLife() == false)){
        return true;
    }
    else{
        return false;
    }
}

bool isLife_false(Object *o){
    if(o->getIsLife() == false){
        return true;
    }
    else{
        return false;
    }
}

bool isLifeNpc_true(Object *o){
    if((o->getIsLife() == true) &&
        (o->getTypeObject() == BOT ||
         o->getTypeObject() == KAMIKAZE ||
         o->getTypeObject() == FAT_BOT)){
        return true;
    }
    else{
        return false;
    }
}
Engine::Engine(QObject *parent) : QObject(parent)
{

}

Engine::~Engine()
{

}

void Engine::initEngine()
{      
    clearTrash();
    level_ = 0;

    QObject::connect(&timer, SIGNAL(timeout()), SLOT(everyTick_slot()));    
    QObject::connect(this, SIGNAL(sendAction_signal(Action)), &my_object, SLOT(getAction_slot(Action)));
}

void Engine::newSingleGame(const int level)
{
    if(readLevels() == false){
        qDebug() << "no levels";
        return;
    }
    initLevel(level);
    score_ = 0;
    time_end_level = 0;    
    my_object.initMyObject(&objects);
    initWalls();
    start();
}

void Engine::start()
{
     timer.start(100);
     is_running_= true;
}

void Engine::pause()
{
    timer.stop();
    is_running_ = false;
}

bool Engine::isRunning() const
{
    return is_running_;
}

bool Engine::readLevels()
{    
    LevelsReader reader;
    reader.read("./levels.xml");
    levels_ = reader.getLevelsVector();
    if(levels_.isEmpty()){
        return false;
    }
    else{
        return true;
    }

}

void Engine::gameOver()
{
    if(isRunning() == true){
        pause();
    }
}

void Engine::nextLevel()
{
    clearTrash();
    level_++;
    if(level_ > levels_.size() - 1){
        pause();
    }
    initWalls();
}

void Engine::initLevel(const int level)
{
    if(level == 0){
        level_ = 0;
    }
    else{
        level_ = level - 1;
    }
    if(level_ >= levels_.size()){
        level_ = levels_.size() - 1;
    }
}

void Engine::initWalls()
{    
    QVector<ValueXY> *walls = &levels_[level_].walls;
    if(walls->isEmpty() == true){
        return;
    }
    for(QVector<ValueXY>::const_iterator it = walls->begin(); it != walls->end(); it++){
        Wall *wall = new Wall;
        wall->initWall((*it).x,(*it).y);
        objects.push_back(wall);
    }
}

void Engine::clearTrash()
{
    it_object = 0;
    burned_npc_ = 0;
    qDeleteAll(objects);
    objects.clear();
}

void Engine::burnNpc(const int level)
{
    if((time_end_level != 0) && (QDateTime::currentMSecsSinceEpoch() -
                                 time_end_level < Options::instance()->game_option.getTimePrevieFight())){
        return;
    }
    if(burned_npc_ != levels_.at(level).max_burned && levels_.at(level).types_npc.isEmpty() == false){
        if((QDateTime::currentMSecsSinceEpoch()/100)%levels_.at(level).time_to_burn == 0){
            NpcObject *npc;
            QVector<TypeObject> *type_npc =(QVector<TypeObject>*)(&levels_.at(level).types_npc);
            switch(type_npc->first()){
            case BOT:
                npc = new Bot;
                break;
            case KAMIKAZE:
                npc = new Kamikaze;
                break;
            case FAT_BOT:
                npc = new FatBot;
                break;
            default:
                npc = new Bot;
                break;
            }            
            npc->initNpcObject(&my_object, &objects);
            bool can_burn;
            if(burned_npc_%2 == 0){
                can_burn = npc->initPosition(BOTTOM);
                if(can_burn == false){
                    can_burn = npc->initPosition(TOP);
                }
            }
            else{
                can_burn = npc->initPosition(TOP);
                if(can_burn == false){
                    can_burn = npc->initPosition(BOTTOM);
                }
            }
            if(can_burn == true){
                objects.push_back(npc);
                burned_npc_++;
                type_npc->pop_front();
            }
            else{
                delete npc;
            }
        }
    }
    else{
        checkNextLevel(level);
    }
}

void Engine::checkHints()
{
    if(objects.isEmpty() == true){
        return;
    }
    for(it_object = objects.begin(); it_object != objects.end(); it_object++){        
        if((*it_object)->getTypeObject() == BULLET){
            Bullet *bullet = dynamic_cast<Bullet*>(*it_object);
            bullet->checkOnHint();
        }
    }
}

void Engine::checkLife()
{
    if(my_object.getIsLife() == false){
        gameOver();
    }
    if(objects.isEmpty() == true){
        return;
    }
    std::sort(objects.begin(), objects.end(), sortLife_false);

    QVector<Object *>::iterator begin_remove = std::find_if(objects.begin(), objects.end(), isLife_false);
    if(begin_remove != 0){
        for(QVector<Object *>::iterator it = begin_remove; it != objects.end();it++ ){            
            if((*it)->getIsLife() == false){
                if((*it)->getTypeObject() == BOT  || (*it)->getTypeObject() == KAMIKAZE) {
                    score_ += 100;                    
                }
                if((*it)->getTypeObject() == FAT_BOT){
                    score_ += 150;
                }
                delete (*it);
            }

        }
        objects.erase(begin_remove, objects.end());
    }

}

void Engine::checkNextLevel(const int level)
{
    QVector<Object *>::iterator it = std::find_if(objects.begin(),objects.end(), isLifeNpc_true);
    if((*it)->getTypeObject() == BOT || (*it)->getTypeObject() == KAMIKAZE ||
            (*it)->getTypeObject() == FAT_BOT){
        return;
    }
    if(burned_npc_ == levels_.at(level).max_burned){
        time_end_level = QDateTime::currentMSecsSinceEpoch();
        nextLevel();
    }
}

void Engine::moveAll()
{
    for(it_object = objects.begin(); it_object != objects.end(); it_object++){
        if((*it_object)->getIsLife() == true){
            (*it_object)->move();
        }
    }
}

void Engine::everyTick_slot()
{
    memset(&dataEngine, 0, sizeof(DataEngine));
    burnNpc(level_);
    checkHints();
    checkLife();
    moveAll();
    dataEngine.my = &my_object;
    dataEngine.objects  = &objects;
    dataEngine.score = score_;
    dataEngine.level = level_;
    emit sendState_signal(dataEngine);
}

void Engine::getPause_slot()
{
    if(isRunning() == true){
        pause();
    }
    else{
        start();
    }
}


