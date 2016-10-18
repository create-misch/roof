#include "object.h"

Object::Object()
{
    x_ = 0;
    y_ = 0;
    width_ = 0;
    height_ = 0;
    angle_ = 0;
    step_ = 0;
    health_ = 0;
    is_life_ = false;
    objects_ = 0;
}

Object::~Object()
{
    objects_ = 0;
}

void Object::setX(const int x)
{
    if(x >= -1000){
        x_ = x;
    }
    else {
        qDebug() << "error(setX) : x < 0";
    }
}
void Object::addX(const int x)
{
    if(x_ + x >= 0){
        x_ += x;
    }
    else{
        qDebug() << "error(addX) : x < 0";
    }
}
int Object::getX() const
{
    return x_;
}
void Object::setY(const int y)
{
    if(y >= -1000){
        y_ = y;
    }
    else{
        qDebug() << "error(setY) : y < 0";
    }
}
void Object::addY(const int y)
{
    if(y_ + y >= 0){
        y_ += y;
    }
    else {
        qDebug() << "error(addY) : y < 0";
    }
}
int Object::getY() const
{
    return y_;
}
void Object::setWidth(const int width)
{
    if(width >=0){
        width_ = width;
    }
    else {
        qDebug() << "error(setWidth) : width < 0";
    }
}
void Object::addWidth(const int width)
{
    if(width_ + width >= 0){
        width_ += width;
    }
    else {
        qDebug() << "error(addWidth) : width < 0";
    }
}
int Object::getWidth() const
{
    return width_;
}
void Object::setHeight(const int height)
{
    if(height >= 0){
        height_ = height;
    }
    else {
        qDebug() << "error(setHeiht) : height < 0";
    }
}
void Object::addHeight(const int height)
{
    if(height_ + height >= 0){
        height_ += height;
    }
    else{
        qDebug() << "error(addHeight) : height < 0";
    }
}
int Object::getHeight() const
{
    return height_;
}
void Object::setAngle(const int angle)
{
    if(angle >= 0){
        angle_ = angle;
    }
    else {
        qDebug() << "error(setAngle) : angle < 0";
    }
}
void Object::addAngle(const int angle)
{
    if(angle_ + angle >= 0){
        angle_ += angle;
    }
    else {
        qDebug() << "error(addAngle) : angle < 0";
    }
}
int Object::getAngle() const
{
    return angle_;
}
void Object::setStep(const int step)
{
    if(step >= 0){
        step_ = step;
    }
    else {
        qDebug() << "error(setStep) : step < 0";
    }
}
void Object::addStep(const int step)
{
    if(step_ + step >= 0){
        step_ += step;
    }
    else{
        qDebug() << "error(addStep) : step < 0";
    }
}
int Object::getStep() const
{
    return step_;
}
void Object::setHealth(const int health){
    if(health >= 0){
        health_ = health;
    }
    else {
        qDebug() << "error(setHealth) : heath < 0";
    }
}
void Object::addHealth(const int health){
    if(health_ + health >= -200){
        health_ += health;
    }
    else {
        qDebug() << "error(addHealth) : heath < 0";
    }
}
int Object::getHealth() const
{
    return health_;
}
void Object::setIsLife(const bool life)
{
    is_life_ = life;
}

void Object::setTypeObject(const TypeObject type)
{
    type_object_ = type;
}

void Object::setObjects(QVector<Object *> *const obj)
{
    if(obj != 0){
        objects_ = obj;
    }
}
bool Object::getIsLife() const
{
    return is_life_;
}

TypeObject Object::getTypeObject() const
{
    return type_object_;
}

QVector<Object *> *Object::getObjects() const
{
    if(objects_ != 0){
        return objects_;
    }
}

bool Object::operator ==(bool rhs)
{
    if(getIsLife() == rhs == true){
        return true;
    }
    else{
        return false;
    }

}

bool intersectOnObjects(const Object *obj, QVector<Object *> *const objects){
    QRect rect_a(obj->getX(), obj->getY(), obj->getWidth(), obj->getHeight());
    for(QVector<Object *>::const_iterator it = objects->begin(); it != objects->end(); it++){
        if(obj != *it){
            QRect rect_b((*it)->getX(), (*it)->getY(), (*it)->getWidth(), (*it)->getHeight());
            if(rect_a.intersects(rect_b)){
                return true;
            }
        }
    }
    return false;
}

bool intersectOnObjects(const int x_next, const int y_next, const Object *obj, QVector<Object *> *const objects){
    QRect rect_a(x_next, y_next, obj->getWidth(), obj->getHeight());
    for(QVector<Object *>::const_iterator it = objects->begin(); it != objects->end(); it++){
        if(obj != *it){
            QRect rect_b((*it)->getX(), (*it)->getY(), (*it)->getWidth(), (*it)->getHeight());
            if(rect_a.intersects(rect_b)){
                return true;
            }
        }
    }
    return false;
}

bool intersectOnObjects(const int x_next, const int y_next, const Object *obj_a, const Object *obj_b){
    QRect rect_a(x_next, y_next, obj_a->getWidth(), obj_a->getHeight());
    QRect rect_b(obj_b->getX(), obj_b->getY(), obj_b->getWidth(), obj_b->getHeight());
    if(rect_a.intersects(rect_b)){
        return true;
    }
    return false;
}

